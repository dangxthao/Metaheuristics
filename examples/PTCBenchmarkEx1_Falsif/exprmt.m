
setup
%% Specifying STL formula
formulas = STL_ReadFile('prop1.stl');


%% Specifying parameter names
for i=0:N-1
    signal_u0{1,i+1}=strcat('Pedal_Angle_u',num2str(i));
    signal_u1{1,i+1}=strcat('Engine_Speed__rpm__u',num2str(i));
    signal_u2{1,i+1}=strcat('AF_Sensor_Offset_u',num2str(i));
end

%% Initializing CBS object parameters
% Pedal_Angle range: [0 60.9]
% Engine_Speed_rpm range: [900 1100]
% AF_Sensor_Offset range: [0.99 1.01]
CBS = BrSys.copy;
CBS.SetParamRanges(signal_u0,ones(N,1)*[0 40]);
CBS.SetParam(signal_u1,ones(N,1)*1000);
CBS.SetParam(signal_u2,ones(N,1)*1);
Sys.SetEpsGridsize(4*ones(N,1));
Sys.SetDeltaGridsize(2*Sys.epsgridsize);



%% Implementing falsification method
m1 = sprintf('Choose one of the following STL formulas described in prop1.stl file.\n Type one of the following\n');
m2 = sprintf('phi26\n');
m3 = sprintf('phi27\n');
m4 = sprintf('phi29\n');
m5 = sprintf('phitest\n');

prop_ind = input([m1,m2,m3,m4,m5],'s');

switch prop_ind
    case 'phi26'
        phi = phi26;
    case 'phi27'
        phi = phi27;
    case 'phi29'
        phi = phi29;
    case 'phitest'
        phi = phitest;
    otherwise
        error('not a valid input')        
end



%% Implementing falsification method

% The weigtage to robustness information during probabilistic sampling is
% set up as
w_rob = 0.5;




%time_lim = input('\n Maximum time of computation (seconds) \n'); 

msg1 = sprintf('\nChoose a falsification method\n');
msg2 = sprintf('Press 1 : Pseudorandom sampling\n');
msg3 = sprintf('Press 2:  Classification guided sampling\n');
msg4 = sprintf('Press 3:  Global_nelder_mead\n');
msg5 = sprintf('Press 4:  CMA-ES\n');
msg6 = sprintf('Press 5:  simulannealbnd\n');

a = input([msg1,msg2,msg3,msg4,msg5,msg6]);

switch a 
    
    case 1
        time_lim = input('\n Maximum time of computation (seconds) \n'); 
        snap_grid = input(['Ensure epsilon separation [y|n]\n',''],'s');
        switch snap_grid
            case 'y'
            CBS.SetSnapToGrid(true);
            case 'n'
            CBS.SetSnapToGrid(false);
            otherwise
                error('no epsilon resolution specified')
        end
        max_sim = inf;
        r = input('\n Choose a seed (positive integer) for random sampling\n');
        rng(r,'twister');  
        tic
        Out = StatFalsify(CBS,phi,w_rob,max_sim,max_sim,time_lim);
        time = toc;
        fprintf('Computation time = %f seconds \n',time);
        
    case 2 
        %time_lim = input('\n Maximum time of computation (seconds) \n'); 
        time_lim = 2000;
        snap_grid = input(['Ensure epsilon separation [y|n]\n',''],'s');
        switch snap_grid
            case 'y'
            CBS.SetSnapToGrid(true);
            case 'n'
            CBS.SetSnapToGrid(false);
            otherwise
                error('no epsilon resolution specified')
        end       
        max_sim = inf;
        init_sim = input('\n Enter initial number of samples\n');
        r = input('\n Choose a seed (positive integer) for random sampling\n');
        rng(r,'twister');  
        timervar = tic;
        Out = StatFalsify(CBS,phi,w_rob,init_sim,max_sim,time_lim);
        time_1 = toc(timervar);
        fname = ['cl',num2str(r)];
%%        
        x = Out.lower_bounds;
        avg = mean(x.vals); dev = mean(max(avg-x.vals,0));
        X = x.pts(x.vals<avg,:);
        save(fname, 'Out','X','avg','dev')
        
%%
        if isempty(Out.falsifier)
        % Resetting CBS
        clear CBS;
        CBS = BrSys.copy;
        CBS.SetParamRanges(signal_u0,ones(N,1)*[0 40]);
CBS.SetParam(signal_u1,ones(N,1)*1000);
CBS.SetParam(signal_u2,ones(N,1)*1);
CBS.SetEpsGridsize(2*ones(N,1));
CBS.SetDeltaGridsize(2*CBS.epsgridsize);
        
        % Sort region indices in ascending order of lowest robustness values
        [~,I] = sort(Out.lower_bounds.vals);
         x = Out.lower_bounds;
         avg = mean(x.vals); dev = mean(max(avg-x.vals,0));
         X = x.pts(x.vals<avg,:);
        % Specify maximum time for each run
        %es_time = input('\n Maximum time (seconds) for each run (default: 500)\n');
        %es_time = 1000;
        timer_var = tic;
        best = [];
        % Implement CMAES 
         for i = I(1)
            delete('var*','outcm*')
            rng(r,'twister');
            falsif_pb = FalsificationProblem(CBS, phi);  
            falsif_pb.setup_solver('cmaes');
            falsif_pb.solver_options.SaveVariables = 'off';
            falsif_pb.solver_options.Seed = r;
            falsif_pb.max_time = 1000;
            Y = Out.lower_bounds.pts;
            falsif_pb.x0 = X;
            falsif_pb.solve()
            trace = falsif_pb.GetBrSet_False();
            if ~isempty(trace)
                fprintf('falsified')
                time_2 = toc(timer_var);
                fprintf('\n Computation time = %f seconds \n',time_1+time_2);
                trace.PlotSignals
                break;
            end           
            best = [best,falsif_pb.obj_best];
         end
         end
      
%%      
        timervar = tic;
        
        % Resetting CBS
        clear CBS; CBS = BrSys.copy;
         CBS.SetParamRanges(signal_u0,ones(N,1)*[0 40]);
CBS.SetParam(signal_u1,ones(N,1)*1000);
CBS.SetParam(signal_u2,ones(N,1)*1);
CBS.SetEpsGridsize(2*ones(N,1));
CBS.SetDeltaGridsize(2*CBS.epsgridsize);
        
        % Sort region indices in ascending order of lowest robustness values
        %[~,J] = min(best);
        
        % Specify maximum time for each run
        %es_time = input('\n Maximum time for each run \n');
        es_time = 1000;
        % Implement CMAES 
        for i = I(1)
            delete('var*','outcm*')
            falsif_pb = FalsificationProblem(CBS, phi);  
            falsif_pb.setup_solver('cmaes');
            falsif_pb.solver_options.SaveVariables = 'off';
            falsif_pb.solver_options.Seed = r;
            falsif_pb.max_time = es_time;
            falsif_pb.x0 = (Out.lower_bounds.pts(i,:))';
            timer_var = tic;
            falsif_pb.solve()
            trace = falsif_pb.GetBrSet_False();
            if ~isempty(trace)
                fprintf('falsified')
                time_2 = toc(timer_var);
                fprintf('\n Computation time = %f seconds \n',time_1+time_2);
                trace.PlotSignals
                break;
            end           
        end
        
    case 3
       
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('global_nelder_mead');
        falsif_pb.max_time = time_lim;
        timer_var = tic;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        time = toc(timer_var);
        fprintf('Computation time = %f seconds \n',time);
    case 4      
        delete('var*','outcm*')
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('cmaes');
        falsif_pb.solver_options.SaveVariables = 'off';
        r = input('\n Choose a seed (positive integer) for random sampling\n');
        falsif_pb.solver_options.Seed = r;
        falsif_pb.max_time = time_lim;
        timer_var = tic;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        time = toc(timer_var);
        fprintf('Computation time = %f seconds \n',time);
    case 5
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('simulannealbnd');
        falsif_pb.max_time = time_lim;
        timer_var = tic;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        time = toc(timer_var);
        fprintf('Computation time = %f seconds \n',time);
    otherwise
            error('no input')
end     
                       
                       