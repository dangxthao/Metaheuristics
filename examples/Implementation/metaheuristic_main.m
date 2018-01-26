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
disp('Do you want to start a new falsification process?')
disp('Enter <0> if you want to continue the previously started falsification process')
disp('Enter <1> otherwise')
% Answer whether the user wants to reset settings
user_reset = input('');

switch user_reset
    case 1
        bdclose all
        close all
        clear vars
        clear global
        global start
        start = true;

        addpath('../../supp_code')
        addpath('../../src')
        addpath('../../../breach')
        
        InitBreach
        
    otherwise 
        start = true;
end


%% Input system and STL formula
if (user_reset==1)
    disp('Choose an example or manual input to run the algorithm')
    disp('Press 1: PTC benchmark; Press 2: Auto Transmission; Any other key: Manual input')
    setup = input('');
    switch setup
        case 1
            PTC_setup
        case 2
            Autotrans_setup
        otherwise
            Sys = input('Enter the name of the Coverage-Breach-Set object: ');
            phi = input('Enter the STL-formula to be falsified: '); 
    end
end

disp('The system specification is in an object file named CBS')
CBS=Sys.copy();

disp('You selected the following STL formula for falsification')
disp(phi)

% disp('Press any key to continue')
% pause




%% limit on nb of solver calls
%nb_solver_calls = input('Specify Max Nb of Solver Calls: '); 
%fprintf('\n Computation Time Limit is %d seconds\n',nb_solver_calls)
nb_solver_calls = 10


% %% Setting falsification method and parameters
% msg1 = sprintf('\nChoose a falsification method\n');
% msg3 = sprintf('Press 0:  Pseudo random sampling\n');
% msg4 = sprintf('Press 1:  Global_nelder_mead\n');
% msg5 = sprintf('Press 2:  CMA-ES\n');
% msg6 = sprintf('Press 3:  simulannealbnd\n');
% %msg2 = sprintf('Press 1:  Classification guided sampling\n');
% 
% solver_index = input([msg1,msg2,msg3,msg4,msg5,msg6]);

% %% limit on computation time for each solver call
% time_lim = input('Specify Computation Time Limit for each Solver Call in seconds: '); 
% fprintf('\n Computation Time Limit for each Solver Call is %d seconds\n',time_lim)
%time_lim = 10


%% limit on computation time for each solver call
%cov_epsilon = input('Specify coverage increase threshold : '); 
%fprintf('\n Coverage increase threshold is %d \n',cov_epsilon)
cov_epsilon = 1e-2

global Out

% Nb_Optimizers=nb of optimizers other than pseudorandom sampling
Nb_Optimizers=3;

prev_solver_index= 1;
solver_index = 1;
round_count=0;

local_optimum_stuck=false;
cov_monitoring_length = 1;
stagnant_count=0;

rob_stagnant=false;
cov_stagnant=false;
min_robustness=inf;

robustness_graph_data = [];
coverage_graph_data = [];

% xlog_vec: matrix (whose each column vector is a point) to store all the 
%           points explored by all solvers so far
% xbest_vec: Matrix (whose each column vector is a point) to store the 
%          best  solution at each solver call
xbest_vec = [];
xlog_vec = []; 

total_nb_sim = 0; % total number of simulations
current_coverage_value = 0; % current coverage value

%%%%%% Falsification Loop %%%%%%%%%
for call_count = 1:nb_solver_calls
    
    switch solver_index % run the chosen solver

        case 0 % pseudo-random sampling
        
             %if strcmp(user_reset,1)
             if call_count==1 
                falsif_pb = FalsificationProblem(CBS, phi); 
                user_reset=0;
             end
            
             time_lim = 100
             
             CallPseudo(CBS, phi, time_lim); %this call updates Out
             
             % adding new points to Sys
             new_pts = transpose(Out.new_samples.pts); % column vectors of newly simulated points.
             Sys = CoverageBreachSet_Add_Pts(Sys, new_pts); 
             
             % adding new points to xlog
             xlog_vec = [xlog_vec, new_pts];
             
             % adding the best point to xbest
             [new_xbest, new_best_id] = min(Out.lower_bounds.vals);
             new_xbest = (Out.lower_bounds.pts(new_best_id,:))'
             xbest_vec = [xbest_vec, new_xbest'];
             
        %%%%%%%%%%%%%%%
        %%%%%%%%%%%%%%%
        case 4 %classification-based
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
                falsif_pb = FalsificationProblem(CBS, phi); %%Breach search object  
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


        case 1
            %%
            %time_lim = input('\n Specify time limit of computation in seconds\n');
            %time_lim = 100; %computation time limit
            %fprintf('\n Time limit of computation is %d seconds\n',time_lim)
            time_lim = 50

%             nb_local_iter = input('\n Specify nb of local iterations for each solver call\n');
%             fprintf('\n Specify nb of local iterations for each solver call %d \n',max_sim)
            nb_local_iter = 20;
            
            % reset falsif_pb if user_reset = 'yes'
            %if strcmp(user_reset,1)
            %if call_count==1 
                falsif_pb = FalsificationProblem(CBS, phi); 
            %end
            
            falsif_pb.setup_solver('global_nelder_mead');
            falsif_pb.max_time = time_lim;
            falsif_pb.solver_options.nb_local_iter = nb_local_iter;
            falsif_pb.verbose=0;
            
            timervar_2 = tic;
            falsif_pb.solve();
            
            new_pts = falsif_pb.X_log; % column vectors of newly simulated points
            Sys = CoverageBreachSet_Add_Pts(Sys, new_pts); 
            xlog_vec = [xlog_vec, new_pts];
            
            trace = falsif_pb.GetBrSet_False();
            time = toc(timervar_2);
            fprintf('Computation time = %f seconds \n',time);
            
            
        %%%%%%%%%
        %%%%%%%%%
        case 2 % CMAES
            %%
            %time_lim = input('Specify time limit on computation in seconds: '); 
            %fprintf('\n Time limit of computation is %d seconds\n',time_lim)
            
            time_lim = 100
            
            delete('var*','outcm*')
            
            %if user_reset==1
            %if call_count==1
                falsif_pb = FalsificationProblem(CBS, phi); 
            %end
            
            falsif_pb.setup_solver('cmaes');
            %falsif_pb.solver_options.SaveVariables = 'off';
            %falsif_pb.solver_options.SaveVariables = 'on';
            
            %fprintf('\n Choose one of the following seeds for cmaes:\n')
            %r = input('Choose a non-negative integer for cmaes: ');
            r = round(rand*10000000000);
            falsif_pb.solver_options.Seed = r;
            
            
%             disp('Initialization strategy')
%             disp('Press 0: random from the whole space; Press 1: from xlog; Press 2: from xbest')
%             strategy_id = input('')
            strategy_id = 1;
            
            falsif_pb.solver_options.Restarts = 3;
            falsif_pb.max_time = time_lim;
            
            % strategy_id=0 to pick randomly from the whole space
            % strategy_id=1 to pick randomly from xlog
            % strategy_id=2 to pick randomly from xbest
            winlen = 5;
            %strategy_id=2; 
            if (call_count>1 && strategy_id>0) 
                x0 = initSolver(xlog_vec, xbest_vec, strategy_id, winlen)
                falsif_pb.x0 = x0;
            end 
            falsif_pb.verbose=0;
            
            timervar_2 = tic;
            falsif_pb.solve();
            
            new_pts = falsif_pb.X_log; % column vectors of newly simulated points.
            Sys = CoverageBreachSet_Add_Pts(Sys, new_pts);
            xlog_vec = [xlog_vec, new_pts];
            
            trace = falsif_pb.GetBrSet_False();
            time = toc(timervar_2);
            fprintf('Computation time = %f seconds \n',time);
            
            if ~isempty(trace)
                trace.PlotSignals
            end
            
        case 3 %Simulated Annealing 
            %%
            %time_lim = input('Specify time limit on computation: '); 
            %fprintf('\n Time limit of computation is %d seconds\n',time_lim)
            
            time_lim = 100
            %if strcmp(user_reset,1)
            %if user_reset==1
            
            %if call_count==1
                falsif_pb = FalsificationProblem(CBS, phi); 
            %end
            falsif_pb.setup_solver('simulannealbnd');
            falsif_pb.max_time = time_lim;
            
            % strategy_id=0 to pick randomly from the whole space
            % strategy_id=1 to pick randomly from xlog
            % strategy_id=2 to pick randomly from xbest
            winlen = 5;
            %strategy_id=2; 
            if (call_count>1 && strategy_id>0) 
                x0 = initSolver(xlog_vec, xbest_vec, strategy_id, winlen)
                falsif_pb.x0 = x0;
                %input('') 
            end 
            
            falsif_pb.verbose=0;
            timervar_2 = tic;
            falsif_pb.solve();
            
            new_pts = falsif_pb.X_log; % column vectors of newly simulated points.
            Sys = CoverageBreachSet_Add_Pts(Sys, new_pts);
            xlog_vec = [xlog_vec, new_pts];
            
            trace = falsif_pb.GetBrSet_False();
            time = toc(timervar_2);
            fprintf('Computation time = %f seconds \n',time);
            
        otherwise
                error('no input')
    end   % end of switch  
    
    total_nb_sim = total_nb_sim+size(new_pts,2); % update total nb simulations
    
    %disp('Current min robustness ')
    %min_robustness
    
    
    
    % update best robustness value vector 
     if solver_index == 0 % pseudorandom sampling
         [new_obj_best, new_best_id] = min(Out.lower_bounds.vals);
         new_xbest = (Out.lower_bounds.pts(new_best_id,:))';
     else
         new_obj_best = falsif_pb.obj_best;
         new_xbest = falsif_pb.x_best;
         xbest_vec = [xbest_vec, new_xbest'];
     end
    
     if (min_robustness<=0)
        error('Falsifier Found!');
     end
     
     if (call_count==1)  
         min_robustness=new_obj_best;
     end     
     
     
     if min_robustness > new_obj_best
         min_robustness=new_obj_best
         rob_stagnant = false;
     else
         rob_stagnant = true;
     end    
     
    robustness_graph_data=...
        [robustness_graph_data; [total_nb_sim min_robustness]] 
  
    
    % the coverage graph is monotonic, we check the evolution of coverage
    % for non-increase by cov_epsilon
    % recompute current coverage
    current_coverage_value = Sys.ComputeLogCellOccupancyCoverage; 
    % update coverage graph data
    coverage_graph_data= ...
       [coverage_graph_data; [total_nb_sim current_coverage_value]] 
  
    l = size(coverage_graph_data,1);
    
    %pause
    
    
    if (l>cov_monitoring_length)
        cov_diff = current_coverage_value - ...
            coverage_graph_data(l-cov_monitoring_length,2);
        
        if (cov_diff<cov_epsilon)
           stagnant_count = stagnant_count + 1; 
           %coverage does not increases sufficiently
        else
           %coverage increases sufficiently
           stagnant_count=0;
        end 
    
        if (stagnant_count>cov_monitoring_length) 
            cov_stagnant=true;
            disp('Coverage stagnant')
        else
            stagnant_count=stagnant_count+1;
        end
    end
    
    % memorizing the previous optimizer
    if (~(solver_index==0)) 
        prev_solver_index = solver_index;
    end  
    
    local_optimum_stuck=(stagnant_count>cov_monitoring_length) && rob_stagnant;
    
    
    if (~local_optimum_stuck)
        if (prev_solver_index~=0) 
            solver_index = prev_solver_index + 1;
            if (solver_index>Nb_Optimizers) 
                disp('ONE ROUND of solver calls is done')
                solver_index = 1;
                round_count = round_count + 1; 
            end
        end
    else
        solver_index = 0 %use pseudorandom sampling to increase coverage
    end    

     
    
    
    disp('Curent solver call done!')


end % end of for-loop call_count