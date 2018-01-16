% This code takes as input a coverage breach set object and an STL formula
% and searches for a falsifier of the STL formula.

% The coverage breach object should have an epsilon grid size specified
% with no points initially, i.e. NumPoints = 0 at start.

% Upon running the code, the user will be prompted to enter the following
% parameters.
%   1) The coverage breach set object.
%   2) The STL formula specified in breach.
%   3) The falsification method: a list of choices are displayed.
%   4) A seed for pseudo-random sampling.
%   5) Other parameters specific to the falsification method.

%% Preliminary settings
bdclose all
close all
clear vars
clear global
global start
start = true;

addpath('../../src')
InitBreach

%% Input system and STL formula
disp('choose an example or manual input to run the algorithm')
disp('Press 1:PTC benchmark; Press 2: Auto Transmission; Any other key: Manual input')
setup = input('');
switch setup
    case 1
        PTC_setup
    case 2
        Autotrans_setup
    otherwise
       Sys = input('input the coverage breach set object');
       phi = input('The STL formula to be falsified'); 
end

disp('The system specification is in an object file named CBS')
disp('You selected the following STL formula for falsification')
disp(phi)
disp('press any key to continue')
pause
CBS = Sys.copy();





%% Setting falsification method and parameters
msg1 = sprintf('\nChoose a falsification method\n');
msg2 = sprintf('Press 1 : Classification guided sampling\n');
msg3 = sprintf('Press 2:  Pseudo random sampling\n');
msg4 = sprintf('Press 3:  Global_nelder_mead\n');
msg5 = sprintf('Press 4:  CMA-ES\n');
msg6 = sprintf('Press 5:  simulannealbnd\n');

a = input([msg1,msg2,msg3,msg4,msg5,msg6]);
global Out

switch a 
    
    case 2
        time_lim = input('\n Time limit of computation is %d seconds\n');
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
        Out = StatFalsify(Out,CBS,phi,w_rob,max_sim,max_sim,time_lim);
        time = toc;
        fprintf('Computation time = %f seconds \n',time);
        
    case 1 
        time_lim = inf;
        snap_grid = 'y';
        switch snap_grid
            case 'y'
            CBS.SetSnapToGrid(true);
            case 'n'
            CBS.SetSnapToGrid(false);
            otherwise
                error('no epsilon resolution specified')
        end 
        
        w_rob = input('Enter weightage to robustness information (recommended:0.5)\n');
        
        %time_lim = 2000;
        max_sim = input('\n Enter limit on number of simulations during global search\n');
        
        init_sim = input('\n Enter threshold number of samples for classification\n ');        
        loc_time = input('\n Input time limit for each local iteration (seconds)\n');
         k = input('\n Enter number of local search iterations (recommended: 2)\n');
        r = input('\n Choose a non-negative integer seed for pseudorandom sampling:\n');
        rng(r,'twister');  
        
        % input the solver
        disp('Press 1:CMAES, 2:Simulated Annealing, 3: Nelder Mead')
        
        s = input('solver for local search\n');
        switch s
            case 1
                solver = 'cmaes';
            case 2
                solver = 'simulannealbnd';
            case 3
                solver = 'global_nelder_mead';
            otherwise
                error('not a valid input to solver')
        end
        timervar_1 = tic;
        Out = StatFalsify(Out,CBS,phi,w_rob,init_sim,max_sim,time_lim);
        time_1 = toc(timervar_1);  
        fname = ['cl',num2str(r)];
        save(fname, 'Out')
 %%     
       if isempty(Out.falsifier) 
           timervar_2 = tic;
        % Sort region indices in ascending order of lowest robustness values
        [~,I] = sort(Out.lower_bounds.vals);
        
        
        
         for i = I(1:k)
            delete('var*','outcm*')
            rng(r,'twister');
            % Resetting CBS
            clear CBS;
            CBS = Sys.copy;
            falsif_pb = FalsificationProblem(CBS, phi);  
            falsif_pb.setup_solver(solver);
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
         end
       end
       
      
    case 3
        %%
        time_lim = input('time limit on computation'); 
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
        time_lim = input('time limit on computation'); 
        fprintf('\n Time limit of computation is %d seconds\n',time_lim)
        delete('var*','outcm*')
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('cmaes');
        falsif_pb.solver_options.SaveVariables = 'off';
        fprintf('\n Choose one of the following seeds for pseudorandom sampling:\n')
        r = input('choose a non-negative integer for pseudorandom sampling');
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
        time_lim = input('time limit on computation'); 
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
