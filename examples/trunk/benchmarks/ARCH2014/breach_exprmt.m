
breach_setup
%% Specifying STL formula

formula = input('\n Property for falsification: ');

switch formula
    case 1
        f1 = STL_Formula('f1','alw(RPM[t]<2520)');
        f2 = STL_Formula('f2','ev_[0,10](speed[t]>50)');
        phi = STL_Formula('phi1','not(f1 and f2)');   
    case 2
        phi = STL_Formula('phi','alw(RPM[t]<4500)');
    case 3
        f1 = STL_Formula('f1','speed[t]>40');
        f2 = STL_Formula('f2','alw(RPM[t]<4500)');
        phi = STL_Formula('phi','ev_[0,10](f1 and f2)');
end

%% Specifying parameter names
for i=0:N1-1
    signal_u0{1,i+1}=strcat('In1_u',num2str(i));
end

for i=0:N2-1
     signal_u1{1,i+1}=strcat('In2_u',num2str(i));    
end
signal = [signal_u0,signal_u1];

%% Initializing CBS object parameters

% Input ranges
R1 = [35,100];
R2 = [0,40];
CBS = BrSys.copy;
CBS.SetParamRanges(signal,[ones(N1,1)*R1;ones(N2,1)*R2]);
% CBS.SetParamRanges(signal_u0,ones(N1,1)*[0 100]);
% CBS.SetParamRanges(signal_u1,ones(N2,1)*[0,200]);
CBS.SetEpsGridsize([4*ones(N1,1);4*ones(N2,1)]);
CBS.SetDeltaGridsize(2*CBS.epsgridsize);


%% Implementing falsification method

% The weigtage to robustness information during probabilistic sampling is
% set up as
w_rob = 0.5;






msg1 = sprintf('\nChoose a falsification method\n');
msg2 = sprintf('Press 1 : Pseudorandom sampling\n');
msg3 = sprintf('Press 2:  Classification guided sampling\n');
msg4 = sprintf('Press 3:  Global_nelder_mead\n');
msg5 = sprintf('Press 4:  CMA-ES\n');
msg6 = sprintf('Press 5:  simulannealbnd\n');

a = input([msg1,msg2,msg3,msg4,msg5,msg6]);

switch a 
    
    case 1
        time_lim = input('\n Maximum time (seconds) of computation (default: 2000) \n'); 
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
        r = input('\n Choose a seed (non-negative integer) for random sampling\n');
        rng(r,'twister');  
        tic
        Out = StatFalsify(CBS,phi,w_rob,max_sim,max_sim,time_lim);
        time = toc;
        fprintf('Computation time = %f seconds \n',time);
        
    case 2 
        time_lim = input('\n Maximum time (seconds) of computation (default: 1000) \n'); 
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
        init_sim = input('\n Enter initial number of samples (default: 100) \n');
        r = input('\n Choose a seed (non-negative integer) for random sampling\n');
        rng(r,'twister');  
        timervar = tic;
        Out = StatFalsify(CBS,phi,w_rob,init_sim,max_sim,time_lim);
        time_1 = toc(timervar);   
%%      
       if isempty(Out.falsifier)
        % Resetting CBS
        clear CBS;
        CBS = BrSys.copy;
        CBS.SetParamRanges(signal_u0,ones(N1,1)*R1);
        CBS.SetParamRanges(signal_u1,ones(N2,1)*R2);
        CBS.SetEpsGridsize([4*ones(N1,1);4*ones(N2,1)]);
        CBS.SetDeltaGridsize(2*CBS.epsgridsize);

        
        % Sort region indices in ascending order of lowest robustness values
        [~,I] = sort(Out.lower_bounds.vals);
%         x = Out.lower_bounds;
%         avg = mean(x.vals); dev = mean(max(avg-x.vals,0));
%         X = x.pts(x.vals<(avg-dev),:);
        % Specify maximum time for each run
        es_time = input('\n Maximum time (seconds) for each run (default: 500)\n');
        %es_time = 1000;
        timer_var = tic;
      
        % Implement CMAES 
         for i = I
            delete('var*','outcm*')
            rng(r,'twister');
            falsif_pb = FalsificationProblem(CBS, phi);  
            falsif_pb.setup_solver('cmaes');
            falsif_pb.solver_options.SaveVariables = 'off';
            falsif_pb.solver_options.Seed = r;
            falsif_pb.max_time = es_time;
              X = Out.lower_bounds.pts;
            falsif_pb.x0 = X(i,:);
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
       end
      fname = append('cl',num2str(r));
      save(fname,r);
        
    case 3
        time_lim = input('\n Maximum time (seconds) of computation (default: 2000) \n'); 
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('global_nelder_mead');
        falsif_pb.max_time = time_lim;
        timer_var = tic;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        time = toc(timer_var);
        fprintf('Computation time = %f seconds \n',time);
    case 4 
        time_lim = input('\n Maximum time (seconds) of computation (default: 2000) \n'); 
        delete('var*','outcm*')
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('cmaes');
        falsif_pb.solver_options.SaveVariables = 'off';
        r = input('\n Choose a seed (non-negative integer) for random sampling\n');
        falsif_pb.solver_options.Seed = r;
        falsif_pb.max_time = time_lim;
        timer_var = tic;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        time = toc(timer_var);
        fprintf('Computation time = %f seconds \n',time);
        if ~isempty(trace)
            trace.PlotSignals
        end
    case 5
        time_lim = input('\n Maximum time (seconds) of computation (default: 2000) \n'); 
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
                       
                       