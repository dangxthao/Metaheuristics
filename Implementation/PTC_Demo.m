
bdclose all
close all
clear vars
global start
start = true;

addpath('../../src')
InitBreach


%% Breach Interface Object Creation

model_name = 'AbstractFuelControl_M1NFM';
load('AbstractFuelControl_M1.mat')
fprintf('\n Creating breach interface with simulink model %s\n',model_name)

simTime = 50 ; 
fprintf('\n Simulation time horizon is %d seconds\n',simTime)

fprintf('\n Press any key to continue')
pause

BrSys = CoverageBreachSet(model_name,{});
BrSys.SetTime([0 simTime]);

%% Set input signals

fprintf('\n Parametrizing input signal Pedal Angle as piecewise constant....\n')
Input_Gen.type = 'UniStep';

N = 10; % Number of control points
Input_Gen.cp = N;
BrSys.SetInputGen(Input_Gen);
fprintf('Number of control points is %d\n',N)

fprintf('\n Press any key to continue\n')
pause

%% Specifying parameter names
for i=0:N-1
    signal_u0{1,i+1}=strcat('Pedal_Angle_u',num2str(i));
    signal_u1{1,i+1}=strcat('Engine_Speed__rpm__u',num2str(i));
    signal_u2{1,i+1}=strcat('AF_Sensor_Offset_u',num2str(i));
end

%% Initializing CBS object parameters

% Input ranges
fprintf('\n Range of Pedal Angle is [0, 40]\n')
fprintf('Engine Speed is constant at 1000\n')
fprintf('AF-Sensor Offset is constant at 1')
fprintf('\n Grid discretization unit for Pedal Angle signal value range is 4 units\n')
Sys = BrSys.copy;
Sys.SetParamRanges(signal_u0,ones(N,1)*[0 40]);
Sys.SetParam(signal_u1,ones(N,1)*1000);
Sys.SetParam(signal_u2,ones(N,1)*1);
Sys.SetEpsGridsize(4*ones(N,1));
Sys.SetDeltaGridsize(2*Sys.epsgridsize);
CBS = Sys.copy();

fprintf('\n Press any key to continue\n ')
pause


%% Specifying STL formula
formulas = STL_ReadFile('prop1.stl');
phi = phi26;

fprintf('\n The STL formula is\n ')
disp(phi)

fprintf('\n Press any key to continue\n')
pause

%% Setting falsification method and parameters
msg1 = sprintf('\nChoose a falsification method\n');
msg2 = sprintf('Press 1 : Classification guided sampling\n');
msg3 = sprintf('Press 2:  Pseudo random sampling\n');
msg4 = sprintf('Press 3:  Global_nelder_mead\n');
msg5 = sprintf('Press 4:  CMA-ES\n');
msg6 = sprintf('Press 5:  simulannealbnd\n');

a = input([msg1,msg2,msg3,msg4,msg5,msg6]);

switch a 
    
    case 2
        time_lim = 5000; 
        fprintf('\n Time limit of computation is %d seconds\n',time_lim)
        snap_grid = 'y';
        switch snap_grid
            case 'y'
            CBS.SetSnapToGrid(true);
            case 'n'
            CBS.SetSnapToGrid(false);
            otherwise
                error('no epsilon resolution specified')
        end
        max_sim = inf;
        fprintf('\n Choose one of the following seeds for pseudorandom sampling:\n')
        r = input('0, 5000, 10000 or 15000\n');
        rng(r,'twister');  
        tic
        Out = StatFalsify(CBS,phi,w_rob,max_sim,max_sim,time_lim);
        time = toc;
        fprintf('Computation time = %f seconds \n',time);
        
    case 1 
        time_lim = 2000;
        snap_grid = 'y';
        switch snap_grid
            case 'y'
            CBS.SetSnapToGrid(true);
            case 'n'
            CBS.SetSnapToGrid(false);
            otherwise
                error('no epsilon resolution specified')
        end 
        
        w_rob = 0.5;
        fprintf('\n Weightage to robustness information is %f\n',w_rob)
        
        time_lim = 2000;
        max_sim = 2100;
        %max_sim = 100;
        fprintf('\n Limit on number of simulations during global search is %d.\n',max_sim) 
        
        %init_sim = 20;
        fprintf('\n Threshold number of samples for classification is %d\n ',init_sim)                
        
        loc_time = 1500;
        fprintf('\n Time limit on each local search iteration is %d seconds \n',loc_time);
        
        k = 2;
        fprintf('\n Limit on number of local search iterations is %d\n',k)
        
        fprintf('\n Press any key to continue\n')
        pause
        
        fprintf('\n Choose one of the following seeds for pseudorandom sampling:\n')
        r = input('0, 5000, 10000 or 15000\n');
        rng(r,'twister');  
        timervar_1 = tic;
        Out = StatFalsify([],CBS,phi,w_rob,init_sim,max_sim,time_lim);
        time_1 = toc(timervar_1);  
        fname = ['cl',num2str(r)];
        save(fname, 'Out')
 %%     
       if isempty(Out.falsifier) 
           timervar_2 = tic;
        % Sort region indices in ascending order of lowest robustness values
        [~,I] = sort(Out.lower_bounds.vals);
         for i = I
            delete('var*','outcm*')
            rng(r,'twister');
            % Resetting CBS
            clear CBS;
            CBS = Sys.copy;
            falsif_pb = FalsificationProblem(CBS, phi);  
            falsif_pb.setup_solver('cmaes');
            falsif_pb.solver_options.SaveVariables = 'off';
            falsif_pb.solver_options.Seed = r;
            Y = Out.lower_bounds.pts;
            falsif_pb.x0 = Y(i,:);
            falsif_pb.max_time = loc_time;
            falsif_pb.solve()
            trace = falsif_pb.GetBrSet_False();
            if ~isempty(trace)
                fprintf('falsified')
                time_2 = toc(timervar_2);
                fprintf('\n Computation time = %f seconds \n',time_1+time_2);
                trace.PlotSignals
                break;
            end 
            %best = [best,falsif_pb.obj_best];
         end
       end
       
      
    case 3
        %%
        time_lim = 5000; 
        fprintf('\n Time limit of computation is %d seconds\n',time_lim)
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('global_nelder_mead');
        falsif_pb.max_time = time_lim;
        timervar_2 = tic;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        time = toc(timervar_2);
        fprintf('Computation time = %f seconds \n',time);
      
    case 4 
        %%
        time_lim = 5000; 
        fprintf('\n Time limit of computation is %d seconds\n',time_lim)
        delete('var*','outcm*')
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('cmaes');
        falsif_pb.solver_options.SaveVariables = 'off';
        fprintf('\n Choose one of the following seeds for pseudorandom sampling:\n')
        r = input('0, 5000, 10000 or 15000\n');
        falsif_pb.solver_options.Seed = r;
        falsif_pb.max_time = time_lim;
        timervar_2 = tic;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        time = toc(timervar_2);
        fprintf('Computation time = %f seconds \n',time);
        if ~isempty(trace)
            trace.PlotSignals
        end
    case 5
        %%
        time_lim = 5000; 
        fprintf('\n Time limit of computation is %d seconds\n',time_lim)
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('simulannealbnd');
        falsif_pb.max_time = time_lim;
        timervar_2 = tic;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        time = toc(timervar_2);
        fprintf('Computation time = %f seconds \n',time);
    otherwise
            error('no input')
end     
