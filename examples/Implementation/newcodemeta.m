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


%% Preliminary settings Commented by Nisha Mishra

% disp('Enter <0> if you want to continue the previously started falsification process')
% disp('Enter <1> otherwise')
% Answer whether the user wants to reset settings
%user_reset = input('');

disp('New falsification process begins')
user_reset=1;

switch user_reset
    case 1
        bdclose all
        close all
        clear all
        clear vars
        clear global
        global start
        start = true;

        addpath('../../supp_code')
        addpath('../../src')
        addpath('../../../breach')
        
        InitBreach
        
        %% Thao uncommented this to allow automatic calls 
        % fprintf('\n Choose one of the following seeds for pseudorandom sampling:\n')
        % r = input('0, 5000, 10000 or 15000\n');
        % r = abs(round(rand*100)+1);
        rng(0,'twister');
        
    otherwise 
        start = true;
end

user_reset=1;

%% Input system and STL formula
if (user_reset==1)
    disp('Choose an example or manual input to run the algorithm- We use the PTC setup')
    % disp('Press 1: PTC benchmark; Press 2: Auto Transmission; Any other
    % key: Manual input')// Commented by Nisha Mishra
    %setup = input('');
    setup = 1;
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
nb_solver_calls = 30 % Edited by Nisha Mishra, initially 30

% %% Setting falsification method and parameters
% msg1 = sprintf('\nChoose a falsification method\n');
% msg3 = sprintf('Press 0:  Pseudo random sampling\n');
% msg5 = sprintf('Press 1:  CMA-ES\n');
% msg6 = sprintf('Press 2:  simulannealbnd\n');
% msg4 = sprintf('Press 3:  Global_nelder_mead\n');
% msg2 = sprintf('Press 4:  Classification guided sampling\n');
% 
% solver_index = input([msg1,msg2,msg3,msg4,msg5,msg6]);

% %% limit on computation time for each solver call
% time_lim = input('Specify Computation Time Limit for each Solver Call in seconds: '); 
% fprintf('\n Computation Time Limit for each Solver Call is %d seconds\n',time_lim)
%time_lim = 10


%% limit on computation time for each solver call
%cov_epsilon = input('Specify coverage increase threshold : '); 
%fprintf('\n Coverage increase threshold is %d \n',cov_epsilon)
cov_epsilon = 8e-2
rob_epsilon_percent = 0.05
rob_stagnant_win = 3

strategy_id = 2; %1 xlog, 2 from xbest
winlen = 1;

% Nb_Optimizers=nb of optimizers other than pseudorandom sampling
Nb_Optimizers=4;

prev_solver_index=0;
solver_index = 1 %cmaes 1, SA 2, GNM 3, CL 4
round_count=1

global Out

local_optimum_stuck=false;
cov_monitoring_win = 1;
stagnant_count=0;
cov_monitoring_length = cov_monitoring_win;

rob_stagnant=false;
cov_stagnant=false;
min_robustness=inf;

robustness_graph_data = [];
coverage_graph_data = [];
solver_index_data = [];

% xlog_vec: matrix (whose each column vector is a point) to store all the 
%           points explored by all solvers so far
% xbest_vec: Matrix (whose each column vector is a point) to store the 
%          best  solution at each solver call
xbest_vec = [];

Xlog = struct('xlogPR',[],'xlogCMAES',[],'xlogSA',[],'xlogGNM',[],'xlogCL',[]); 
Xbest = struct('xbestPR',[],'xbestCMAES',[],'xbestSA',[],'xbestGNM',[],'xbestCL',[]); 
Valbest = struct('PR',[],'CMAES',[],'SA',[],'GNM',[],'CL',[]); 

search_space_dim = numel(Sys.epsgridsize);
            
total_nb_sim = 0; % total number of simulations
current_coverage_value = 0; % current coverage value

fileID = fopen('OutFalsification.txt','w');

TotCompTime = tic;
%%%%%% Falsification Loop %%%%%%%%%
for call_count = 1:nb_solver_calls
    
    switch solver_index % run the chosen solver

        case 0 % pseudo-random sampling
        
             %if strcmp(user_reset,1)
             if call_count==1 
                falsif_pb = FalsificationProblem(CBS, phi); 
                user_reset=0;
              else
                clear CBS;
                CBS = Sys.copy();
                falsif_pb = FalsificationProblem(CBS, phi);
             end  
             
             % r = input('0, 5000, 10000 or 15000\n');
             r = abs(round(rand*100)+1);
             rng(r,'twister');
        
             timervar_pr = tic;
             fprintf(1,'\n *** Running PseudoRandom');
             fprintf(fileID,'\n *** Running PseudoRandom');
            
             time_lim = 600
             
             CallPseudo(CBS, phi, time_lim); %this call updates Out
             
             % adding new points to Sys
             new_pts = transpose(Out.new_samples.pts); % column vectors of newly simulated points.
             Sys = CoverageBreachSet_Add_Pts(Sys, new_pts); 
             
             time_pr = toc(timervar_pr);
             fprintf(1,'\n PseudoRandom time = %f seconds',time_pr);
             fprintf(fileID,'\n PseudoRandom time = %f seconds',time_pr);
                    
             % adding new points to xlog
             Xlog.xlogPR = [Xlog.xlogPR, new_pts];
             
             % adding new points to xbest 
             [new_obj_best, new_best_id] = min(Out.lower_bounds.vals);
              
             if (~isempty(Valbest.PR))
                 valbest_last = Valbest.PR(size(Valbest.PR,2));
                 if (valbest_last > new_obj_best) 
                   Valbest.PR = [Valbest.PR, new_obj_best];
                   new_xbest = (Out.lower_bounds.pts(new_best_id,:))';
                   Xbest.xbestPR = [Xbest.xbestPR, new_xbest];
                 end
             else
                 Valbest.PR = [Valbest.PR, new_obj_best];
                 new_xbest = (Out.lower_bounds.pts(new_best_id,:))';
                 Xbest.xbestPR = [Xbest.xbestPR, new_xbest];
             end
             
        %%%%%%%%%%%%%%%
        %%%%%%%%%%%%%%%
       
        case 1 % CMAES
            %%
            %time_lim = input('Specify time limit on computation in seconds: '); 
            %fprintf('\n Time limit of computation is %d seconds\n',time_lim)
            fprintf(1,'\n **** Running CMAES');
            fprintf(fileID,'\n **** Running CMAES');
            
            r = abs(round(rand*100)+1);
             rng(r,'twister');
             
             
            if (call_count==1) 
                time_lim = 8000
             else
                 time_lim = 300
            end
    
            %delete('var*','outcm*')
            
            %if user_reset==1
            if call_count==1
                falsif_pb = FalsificationProblem(CBS, phi); 
            else
                clear CBS;
                CBS = Sys.copy();
                falsif_pb = FalsificationProblem(CBS, phi); 
            end    
            
            falsif_pb.setup_solver('cmaes');
            falsif_pb.solver_options.SaveVariables = 'off';
            %falsif_pb.solver_options.SaveVariables = 'on';
            
            %fprintf('\n Choose one of the following seeds for cmaes:\n')
            %r = input('Choose a non-negative integer for cmaes: ');
%             r = round(rand*10000000000);
%             falsif_pb.solver_options.Seed = r;
            
            
%             disp('Initialization strategy')
%             disp('Press 0: random from the whole space; Press 1: from xlog; Press 2: from xbest')
%             strategy_id = input('')
            
            
            %falsif_pb.solver_options.Restarts = 3;
            falsif_pb.max_time = time_lim;
            
            % strategy_id=0 to pick randomly from the whole space
            % strategy_id=1 to pick randomly from xlog
            % strategy_id=2 to pick randomly from xbest
            
            %strategy_id=2; 
            if (call_count>1) 
                nbsamples=100;
                if (strategy_id==2)
                    nbsamples=1; %taken from the last xbest point(s)
                end
                
                x0=initSolver(CBS,nbsamples,solver_index,Xlog,Xbest,strategy_id,winlen);
                
                %CBS.QuasiRandomSample(100, 2^10);
                %x0_qrandom = CBS.GetParam(falsif_pb.params);
                %x0 = [ x0, x0_qrandom ];
                %input('') 
                if (strategy_id==0)
                    nbsamplesPR=100;
                    CBS.QuasiRandomSample(nbsamplesPR, 2^10);
                    x0_more = CBS.GetParam(falsif_pb.params);
                    x0 = [ x0, x0_more ];
                    if (~isempty(x0))
                        falsif_pb.x0 = x0';
                    end
                end 
            else
                CBS.QuasiRandomSample(200, 2^10);
                x0 = CBS.GetParam(falsif_pb.params);
                
%                 size(x0,2)
%                 size(x0,1)
                
                falsif_pb.x0 = x0';
            end
            
            
            %falsif_pb.verbose=0;
            
            %falsif_pb
            
            timervar_cmaes = tic;
            falsif_pb.solve();
            
            % adding new points to xlog 
            new_pts = falsif_pb.X_log; % column vectors of newly simulated points.
            Sys = CoverageBreachSet_Add_Pts(Sys, new_pts);
            Xlog.xlogCMAES = [Xlog.xlogCMAES, new_pts];
            
            % adding new points to xbest 
            new_obj_best = falsif_pb.obj_best;
            
            if (~isempty(Valbest.CMAES))
                 valbest_last = Valbest.CMAES(size(Valbest.CMAES,2));
                 if (valbest_last > new_obj_best) 
                   Valbest.CMAES = [Valbest.CMAES, new_obj_best];
                   new_xbest = falsif_pb.x_best;
                   Xbest.xbestCMAES = [Xbest.xbestCMAES, new_xbest];      
                 end
             else
                 Valbest.CMAES = [Valbest.CMAES, new_obj_best];
                 new_xbest = falsif_pb.x_best;
                 Xbest.xbestCMAES = [Xbest.xbestCMAES, new_xbest]; 
            end
             
            
            trace = falsif_pb.GetBrSet_False();
            time_cmaes = toc(timervar_cmaes);
            fprintf(fileID,'\n CMAES time = %f seconds',time_cmaes);
            
            if ~isempty(trace)
                trace.PlotSignals
                fprintf(fileID,'\n Exit from CMAES')
                comptime = toc(TotCompTime);
                fprintf(fileID,'\n  TOTAL Computation time = %f seconds',comptime );
                % error('Falisifier found! Exit normally'); //Commented by
                % Nisha Mishra
            end
 end   % end of switch  
    
    total_nb_sim = total_nb_sim+size(new_pts,2); % update total nb simulations
    
    disp('Current min robustness ')
    min_robustness
    
    
    
   
     fprintf(1,'\n Best Robustness Value of this call = %f', new_obj_best);    
     fprintf(fileID,'\n Best Robustness Value of this call = %f', new_obj_best);
     
     if (new_obj_best<=0)
        fprintf(fileID,'\n Falsifier Found!');
        
        comptime = toc(TotCompTime);
        fprintf(fileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
         error('Falisifier found! Exit normally');
     end
     
     
     if (call_count==1)  
         min_robustness=new_obj_best;
         rob_stagnant = false;
         rob_improved = true;
         rob_stagnant_count=0; 
     else    
         rob_improved = false;
         if min_robustness > new_obj_best
            rob_stagnant = false; 
            rob_change=(min_robustness - new_obj_best)/min_robustness;
            if (rob_change > rob_epsilon_percent)
                rob_improved = true;
            end   
            min_robustness=new_obj_best;
         else 
             if (~(solver_index==0) && ~(solver_index==4))
                 rob_stagnant_count=rob_stagnant_count+1; 
             end
         end
         
         if rob_stagnant_count>rob_stagnant_win
             rob_stagnant = true;
         end
         
     end 
     
     fprintf(1,'\n Best Robustness Value so far = %f', min_robustness);   
     fprintf(fileID,'\n Best Robustness Value so far = %f', min_robustness);
     
     
    robustness_graph_data=...
        [robustness_graph_data; [total_nb_sim min_robustness]]; 
  
    
    % the coverage graph is monotonic, we check the evolution of coverage
    % for non-increase by cov_epsilon
    % recompute current coverage
    current_coverage_value = Sys.ComputeLogCellOccupancyCoverage; 
    % update coverage graph data
    coverage_graph_data= ...
       [coverage_graph_data; [total_nb_sim current_coverage_value]]; 
    
    solver_index_data=[solver_index_data; solver_index]; 
   
   
    fprintf(1,'\n\n\n\n #Call  SolverID  Robustness  Coverage');
    fprintf(fileID,'\n\n\n\n #Call  SolverID  Robustness  Coverage');
    fprintf(1,'\nPseudo-random (0), CMA-ES (1), SA (2), GNM (3)');
    fprintf(fileID,'\nPseudo-random (0), CMA-ES (1), SA (2), GNM (3)');
    for iii  = 1:call_count
      fprintf(1,'\n %d  %d  %12.8f  %12.8f',iii, solver_index_data(iii,1),...
          robustness_graph_data(iii,2),coverage_graph_data(iii,2));
      fprintf(fileID,'\n %d  %d  %12.8f  %12.8f',iii, solver_index_data(iii,1),...
          robustness_graph_data(iii,2),coverage_graph_data(iii,2));     
    end 
    
    
    l = size(coverage_graph_data,1);
    
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
            fprintf(fileID,'\n Coverage stagnant');
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
        cov_monitoring_length=cov_monitoring_win;
        PR_duration=0;
        solver_index = prev_solver_index + 1;
        
% %Thao Edited by Nisha Mishra
%         if (~solver_index==1)
%             solver_index=1;
%         end
%         
        if (solver_index>(Nb_Optimizers-1))
        
            fprintf(1,'\n\n*******\n #%d round(s) of solver calls done', round_count);
            fprintf(fileID,'\n #%d round(s) of solver calls done', round_count);
            solver_index = 1;
            round_count = round_count + 1;
            
 %           rob_stagnant
            
            if rob_stagnant
                %strategy_id = 2 %Thao
                %solver_index=0
                strategy_id = 0
            else
                if rob_improved
                    strategy_id = 2
                else 
                    strategy_id = 1
                end    
            end    
        end
        
    else %if local optima stuck
        solver_index=0; %use pseudorandom sampling to increase coverage
        PR_duration=PR_duration+1;

        cov_monitoring_length=PR_duration;
    end 
    
    fprintf(1,'\n Solver call %d done', call_count);
    fprintf(fileID,'\n Solver call %d done', call_count);

end % end of for-loop call_count


comptime = toc(TotCompTime);
disp('\n Exit! TOTAL Computation time = %f seconds');
comptime
fprintf(fileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
