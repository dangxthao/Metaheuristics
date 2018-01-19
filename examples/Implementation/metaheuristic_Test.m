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
% disp('Do you want to start a new falsification process?')
% disp('Enter <0> if you want to continue the previously started falsification process')
% disp('Enter <1> otherwise')
% % Answer whether the user wants to reset settings
% 
% user_reset = input('');

user_reset = 1;
switch user_reset
    case 1
        bdclose all
        close all
        clear vars
        clear global
        global start
        start = true;
        user_reset = 1;

        addpath('../../src')
        addpath('../../../breach')
    otherwise 
        start = true;
end
InitBreach

%% Input system and STL formula
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

disp('The system specification is in an object file named CBS')
CBS=Sys.copy();

disp('You selected the following STL formula for falsification')
disp(phi)

disp('Press any key to continue')
pause




%% limit on nb of solver calls
nb_solver_calls = input('Specify Max Nb of Solver Calls: '); 
fprintf('\n Computation Time Limit is %d seconds\n',nb_solver_calls)

%% limit on computation time for each solver call
time_lim = input('Specify Computation Time Limit for each Solver Call in seconds: '); 
fprintf('\n Computation Time Limit for each Solver Call is %d seconds\n',time_lim)

%% limit on computation time for each solver call
cov_epsilon = input('Specify coverage increase threshold : '); 
fprintf('\n Coverage increase threshold is %d \n',cov_epsilon)

%% Setting falsification method and parameters
msg1 = sprintf('\nChoose a falsification method\n');
msg2 = sprintf('Press 1:  Classification guided sampling\n');
msg3 = sprintf('Press 2:  Pseudo random sampling\n');
msg4 = sprintf('Press 3:  Global_nelder_mead\n');
msg5 = sprintf('Press 4:  CMA-ES\n');
msg6 = sprintf('Press 5:  simulannealbnd\n');

solver_index = input([msg1,msg2,msg3,msg4,msg5,msg6]);


global Out

cov_monitoring_length = 1;
stagnant_count=0;
min_robustness=inf;

robustness_graph_data = [];
coverage_graph_data = [];
xbest_vec = [];

total_num_simulations = 0; % total number of simulations
current_coverage_value = 0; % current coverage value

%%%%%% Falsification Loop %%%%%%%%%
for call_count = 1:nb_solver_calls
    
    switch solver_index % run the chosen solver

        case 2 % pseudo-random sampling
            %time_lim = input('\n Specify time limit of computation in seconds\n');
            %time_limit = inf; %computation time limit

            snap_grid = 'y';
            switch snap_grid
                case 'y'
                CBS.SetSnapToGrid(true);
                case 'n'
                CBS.SetSnapToGrid(false);
                otherwise
                    error('no epsilon resolution specified')
            end

            max_sim = inf; %maximal number of simulations

            fprintf('\n Choose one of the following seeds for pseudorandom sampling:\n')
            r = input('0, 5000, 10000 or 15000\n');
            rng(r,'twister');  
            tic

            w_rob=0.5; % weight for robustness

            % since this is pseudo-random sampling only, without classification
            % init_sim = max_sim (init_sim=nb sim required for classification
            Out = StatFalsify(Out,CBS,phi,w_rob,max_sim,max_sim,time_lim);
            new_pts = transpose(Out.new_samples.pts); % column vectors of newly simulated points.
            % Sys = CoverageBreachSet_Add_Pts(Sys, new_pts); 
            Sys.AddPoints(new_pts); 

            
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


        case 3
            %%
            %time_lim = input('\n Specify time limit of computation in seconds\n');
            %time_lim = 100; %computation time limit
            %fprintf('\n Time limit of computation is %d seconds\n',time_lim)

            nb_local_iter = input('\n Specify nb of local iterations for each solver call\n');
            fprintf('\n Specify nb of local iterations for each solver call %d \n',max_sim)

            % reset falsif_pb if user_reset = 'yes'
            if strcmp(user_reset,1)
                falsif_pb = FalsificationProblem(CBS, phi); 
            end
            falsif_pb.setup_solver('global_nelder_mead');
            falsif_pb.max_time = time_lim;
            falsif_pb.solver_options.nb_local_iter = nb_local_iter;

            timervar_2 = tic;
            falsif_pb.solve()
            new_pts = falsif_pb.X_log; % column vectors of newly simulated points

            % Sys = CoverageBreachSet_Add_Pts(Sys, new_pts); 
            Sys.AddPoints(new_pts); 
            trace = falsif_pb.GetBrSet_False();
            time = toc(timervar_2);
            fprintf('Computation time = %f seconds \n',time);

        case 4 
            %%
            %time_lim = input('Specify time limit on computation in seconds: '); 
            %fprintf('\n Time limit of computation is %d seconds\n',time_lim)
            delete('var*','outcm*')
            if user_reset==1
                falsif_pb = FalsificationProblem(CBS, phi); 
            end
            falsif_pb.setup_solver('cmaes');
            %falsif_pb.solver_options.SaveVariables = 'off';
            falsif_pb.solver_options.SaveVariables = 'on';
            
            
            
            %fprintf('\n Choose one of the following seeds for cmaes:\n')
            %r = input('Choose a non-negative integer for cmaes: ');
            r = round(rand*10000000000);
            falsif_pb.solver_options.Seed = r;
            
            
            disp('Initialize from currently best points')
            disp('Press 1: Yes; Press 0: No')
            init_from_xbest = input('');
            
            falsif_pb.solver_options.Restarts = 3;
            falsif_pb.max_time = time_lim;
            
            if (call_count>1 && init_from_xbest==1)
                rand_id_xbest = max(1, floor(rand*call_count))
            
                if rand_id_xbest> call_count 
                 error('Error in rand_id_xbest');
                end
                xbest_vec(:,rand_id_xbest)
                falsif_pb.x0 = (xbest_vec(:,rand_id_xbest))';
            end
            
            
            timervar_2 = tic;
            falsif_pb.solve()
            new_pts = falsif_pb.X_log; % column vectors of newly simulated points.
            % Sys = CoverageBreachSet_Add_Pts(Sys, new_pts);
            Sys.AddPoints(new_pts); 
            trace = falsif_pb.GetBrSet_False();
            time = toc(timervar_2);
            fprintf('Computation time = %f seconds \n',time);
            if ~isempty(trace)
                trace.PlotSignals
            end
        case 5
            %%
            %time_lim = input('Specify time limit on computation: '); 
            %fprintf('\n Time limit of computation is %d seconds\n',time_lim)
            if strcmp(user_reset,1)
                falsif_pb = FalsificationProblem(CBS, phi); 
            end
            falsif_pb.setup_solver('simulannealbnd');
            falsif_pb.max_time = time_lim;
            timervar_2 = tic;
            falsif_pb.solve()
            new_pts = falsif_pb.X_log; % column vectors of newly simulated points.
            % Sys = CoverageBreachSet_Add_Pts(Sys, new_pts);
            Sys.AddPoints(new_pts); 
            trace = falsif_pb.GetBrSet_False();
            time = toc(timervar_2);
            fprintf('Computation time = %f seconds \n',time);
        otherwise
                error('no input')
    end   % end of switch  
    
    total_num_simulations = total_num_simulations+size(new_pts,2); % update total nb simulations
    
    %disp('Current min robustness ')
    %min_robustness
    
    
    
    % update best robustness value
     if solver_index == 2 % pseudorandom sampling
         [new_obj_best, new_best_id] = min(Out.lower_bounds.vals)
         new_xbest = (Out.lower_bounds.pts(new_best_id,:))';
     else
         new_obj_best = falsif_pb.obj_best
         new_xbest = falsif_pb.x_best;
     end
    

     
     xbest_vec = [xbest_vec, new_xbest]
   
     robustness_diff =  min_robustness - new_obj_best
     if min_robustness > new_obj_best
         min_robustness=new_obj_best
     end
     
    robustness_graph_data =...
        [robustness_graph_data; [total_num_simulations min_robustness]] 
  
    
    % the coverage graph is monotonic, we check the evolution of coverage
    % for non-increase by cov_epsilon
    % recompute current coverage
    current_coverage_value = Sys.ComputeLogCellOccupancyCoverage; 
    % update coverage graph data
    coverage_graph_data = ...
    [coverage_graph_data; [total_num_simulations current_coverage_value]] 
  
    l = size(coverage_graph_data,1);
    
    %pause
    
    solver_index
    
    if (l>cov_monitoring_length)
        cov_diff = current_coverage_value - ...
            coverage_graph_data(l-cov_monitoring_length,2);

        cov_not_stagnant = cov_diff > cov_epsilon;
        
        
      
        cov_not_stagnant
        
        if (~cov_not_stagnant)
            stagnant_count = stagnant_count + 1; 
        end
    
        if (stagnant_count>cov_monitoring_length)            
%             solver_index = 2; % switch to pseudo-random sampling
            stagnant_count=0;
            disp('Coverage stagnant \n')
            %msg1 = sprintf('\nCoverage stagnant - Choose a falsification method\n');
%             msg2 = sprintf('Press 1:  Classification guided sampling\n');
%             msg3 = sprintf('Press 2:  Pseudo random sampling\n');
%             msg4 = sprintf('Press 3:  Global_nelder_mead\n');
%             msg5 = sprintf('Press 4:  CMA-ES\n');
%             msg6 = sprintf('Press 5:  simulannealbnd\n');
% 
%             solver_index = input([msg1,msg2,msg3,msg4,msg5,msg6]);
%             disp('Pseudo-sampling is used to improve coverage')
%             disp('Press any key to continue')
%             pause         
        else
            stagnant_count=stagnant_count+1;
            %% Pick another falsification method and parameters
%             msg1 = sprintf('\nChoose a falsification method\n');
%             msg2 = sprintf('Press 1:  Classification guided sampling\n');
%             msg3 = sprintf('Press 2:  Pseudo random sampling\n');
%             msg4 = sprintf('Press 3:  Global_nelder_mead\n');
%             msg5 = sprintf('Press 4:  CMA-ES\n');
%             msg6 = sprintf('Press 5:  simulannealbnd\n');
% 
%             solver_index = input([msg1,msg2,msg3,msg4,msg5,msg6]);
        
        end
        
       
    end
    
disp('Curent solver call done! Press any key to continue')

%% Pick another falsification method and parameters
msg1 = sprintf('\nChoose a falsification method\n');
msg2 = sprintf('Press 1:  Classification guided sampling\n');
msg3 = sprintf('Press 2:  Pseudo random sampling\n');
msg4 = sprintf('Press 3:  Global_nelder_mead\n');
msg5 = sprintf('Press 4:  CMA-ES\n');
msg6 = sprintf('Press 5:  simulannealbnd\n');

solver_index = input([msg1,msg2,msg3,msg4,msg5,msg6]);   

%% limit on computation time for each solver call
time_lim = input('Specify Computation Time Limit for each Solver Call in seconds: '); 
fprintf('\n Computation Time Limit for Next Solver Call is %d seconds\n',time_lim)

end % end of for-loop call_count