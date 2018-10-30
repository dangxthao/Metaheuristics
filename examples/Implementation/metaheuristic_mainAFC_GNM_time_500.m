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
%user_reset = input('');

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
    disp('Choose an example or manual input to run the algorithm')
    disp('Press 1: PTC benchmark; Press 2: Auto Transmission; Any other key: Manual input')
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
% nb_solver_calls = 30
nb_solver_calls = 1 % (Nisha Mishra)


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
solver_index = 3; %cmaes 1, SA 2, GNM 3
round_count=1;

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
             r = abs(round(rand*100)+1);
             rng(0,'twister');
             %if strcmp(user_reset,1)
             if call_count==1 
                falsif_pb = FalsificationProblem(CBS, phi); 
                user_reset=0;
              else
                clear CBS;
                CBS = Sys.copy();
                falsif_pb = FalsificationProblem(CBS, phi);
             end  
             
             timervar_pr = tic;
             fprintf(1,'\n *** Running PseudoRandom');
             fprintf(fileID,'\n *** Running PseudoRandom');
            
%           time_lim = 400
            time_lim = 500 %Nisha Mishra
             
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
        case 4 %classification-based
             r = abs(round(rand*100)+1);
             rng(0,'twister');
            
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

            w_rob = 0.5;
            %input('Enter weightage to robustness information (recommended:0.5)\n');

            time_lim = 500;
            max_sim = 2000
            %input('\n Enter limit on number of simulations during global search\n');

            init_sim = 30
            %input('\n Enter threshold number of samples for classification\n ');    
            
            loc_time = 100; %not used 
            %input('\n Input time limit for each local iteration
            %(seconds)\n');
            k = 2; %not used 
            %input('\n Enter number of local search iterations (recommended: 2)\n');
            
%             r = input('\n Choose a non-negative integer seed for pseudorandom sampling:\n');
%             rng(r,'twister');  

%             disp('Press 1:CMAES, 2:Simulated Annealing, 3: Nelder Mead')
%             s = input('solver for local search\n');
%             switch s
%                 case 1
%                     solver = 'cmaes';
%                 case 2
%                     solver = 'simulannealbnd';
%                 case 3
%                     solver = 'global_nelder_mead';
%                 otherwise
%                     error('not a valid input to solver')
%             end
            s = 1; %not used
            
            timervar_cl  = tic;
            Out = StatFalsify(Out,CBS,phi,w_rob,init_sim,max_sim,time_lim);
            
            time_cl = toc(timervar_cl);
            fprintf(fileID,'\n Classification time = %f seconds',time_cl);
            fprintf(1,'\n Classification time = %f seconds',time_cl); 
            
            % adding new points to Sys
            new_pts = transpose(Out.new_samples.pts); % column vectors of newly simulated points.
            Sys = CoverageBreachSet_Add_Pts(Sys, new_pts); 
            
            % adding new points to xbest 
            
            [new_obj_best, new_best_id] = min(Out.lower_bounds.vals);
            
            if (~isempty(Valbest.CL))
                 valbest_last = Valbest.CL(size(Valbest.CL,2));
                 if (valbest_last > new_obj_best) 
                   Valbest.CL = [Valbest.CL, new_obj_best];
                   new_xbest = transpose(Out.lower_bounds.pts);
                   Xbest.xbestCL = [Xbest.xbestCL, new_xbest];
                 end
             else
                 Valbest.CL = [Valbest.CL, new_obj_best];
                 new_xbest = transpose(Out.lower_bounds.pts);
                 Xbest.xbestCL = [Xbest.xbestCL, new_xbest];
             end
             
%             time_1 = toc(timervar_1);  
%             fname = ['cl',num2str(r)];
%             save(fname, 'Out')
     %%     
%            if isempty(Out.falsifier) 
%              timervar_2 = tic;
%              % Sort region indices in ascending order of lowest robustness values
%              [~,I] = sort(Out.lower_bounds.vals);
% 
%              for i = I(1:k)
%                 delete('var*','outcm*')
%                 rng(r,'twister');
%                 % Resetting CBS
%                 clear CBS;
%                 CBS = Sys.copy;
%                 falsif_pb = FalsificationProblem(CBS, phi); %%Breach search object  
%                 falsif_pb.setup_solver(solver);
%                 falsif_pb.solver_options.SaveVariables = 'off';
%                 falsif_pb.solver_options.Seed = r;
%                 Y = Out.lower_bounds.pts;
%                 falsif_pb.x0 = Y(i,:);
%                 falsif_pb.max_time = loc_time;
%                 falsif_pb.solve()
%                 trace = falsif_pb.GetBrSet_False();
%                 if ~isempty(trace)
%                     fprintf(fileID,'\n Classification: falsified')
%                     time_2 = toc(timervar_2);
%                     fprintf(fileID,'\n Classification time = %f seconds',time_1+time_2);
%                     trace.PlotSignals
%                     break;
%                 end 
%              end % end for i = I(1:k)
%            end %if isempty(Out.falsifier) 

        
    
        %%%%%%%%%
        %%%%%%%%%
        case 1 % CMAES
            %%
            
             r = abs(round(rand*100)+1);
             rng(0,'twister');

            
            %time_lim = input('Specify time limit on computation in seconds: '); 
            %fprintf('\n Time limit of computation is %d seconds\n',time_lim)
            
            fprintf(1,'\n **** Running CMAES');
            fprintf(fileID,'\n **** Running CMAES');
            
            if (call_count==1)  
                time_lim = 500  % Changing time limit here (Nisha)
                
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
            %falsif_pb.max_time 
            
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
                %CBS.QuasiRandomSample(200, 2^10);
                CBS.QuasiRandomSample(5000, 2^10) % changing the values of samples here (Nisha)
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
                fprintf(fileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
%                 error('Falisifier found! Exit normally'); Nisha Mishra
            end
        
        %%%%%%%%%%    
        %%%%%%%%%% Commented by Nisha Mishra
%         case 2 %Simulated Annealing 
%              r = abs(round(rand*100)+1);
%              rng(0,'twister');

%             fprintf(1,'\n *** Running Simulated Annealing');
%             fprintf(fileID,'\n *** Running Simulated Annealing');
%             %%
%             %time_lim = input('Specify time limit on computation: '); 
%             %fprintf('\n Time limit of computation is %d seconds\n',time_lim)
%             
%             time_lim = 400
%             %if strcmp(user_reset,1)
%             %if user_reset==1
%             
%             if call_count==1
%                 falsif_pb = FalsificationProblem(CBS, phi); 
%             else
%                 clear CBS;
%                 CBS = Sys.copy();
%                 falsif_pb = FalsificationProblem(CBS, phi); 
%             end  
%             
%             falsif_pb.setup_solver('simulannealbnd');
%             falsif_pb.max_time = time_lim;
%             
%             % strategy_id=0 to pick randomly from the whole space
%             % strategy_id=1 to pick randomly from xlog
%             % strategy_id=2 to pick randomly from xbest
%             
%             %strategy_id=1; 
%             if (call_count>1) 
%                 nbsamples=100;
%                 if (strategy_id==2)
%                     nbsamples=1; %taken from the last xbest point(s)
%                 end
%                 
%                 x0 = initSolver(CBS,nbsamples,solver_index,Xlog,Xbest,strategy_id,winlen);
%                                 
%                 nbsamplesPR=0;
%                 CBS.QuasiRandomSample(nbsamplesPR, 2^10);
%                 x0_more = CBS.GetParam(falsif_pb.params);
%                 x0 = [ x0, x0_more ];
%                 
%                 if (~isempty(x0))
%                     falsif_pb.x0 = x0;
%                 end
%                 
% %                 size(x0,2)
% %                 x0
%             else
%                 CBS.QuasiRandomSample(100, 2^10);
%                 x0 = CBS.GetParam(falsif_pb.params);
%                 
% %                 size(x0,2)
% %                 size(x0,1)
%                 
%                 falsif_pb.x0 = x0;
%                 %size(x0,2)
%             end
%             
%             falsif_pb.verbose=0;
%             falsif_pb.solver_options.FunctionTolerance = 1e-3;
%             falsif_pb.solver_options.OptimalityTolerance = 1e-3;
%             falsif_pb.solver_options.MaxFunEvals = 1000;
%             falsif_pb.solver_options.InitialTemperature = 100;
%             
%             timervar_sa = tic;
%             falsif_pb.solve();
%             
%             new_pts = falsif_pb.X_log; % column vectors of newly simulated points.
%             Sys = CoverageBreachSet_Add_Pts(Sys, new_pts);
%             Xlog.xlogSA = [Xlog.xlogSA, new_pts];
%             
%             new_obj_best = falsif_pb.obj_best;
%             
%             if (~isempty(Valbest.SA))
%                  valbest_last = Valbest.SA(size(Valbest.SA,2));
%                  if (valbest_last > new_obj_best) 
%                    Valbest.SA = [Valbest.SA,new_obj_best];
%                    new_xbest = falsif_pb.x_best;
%                    Xbest.xbestSA = [Xbest.xbestSA, new_xbest];
%                  end
%              else
%                  Valbest.SA = [Valbest.SA,new_obj_best];
%                  new_xbest = falsif_pb.x_best;
%                  Xbest.xbestSA = [Xbest.xbestSA, new_xbest];
%             end
%             
%             time_sa = toc(timervar_sa);
%             fprintf(fileID,'\n Simulated Annealing time = %f seconds',time_sa);
%             
%             trace = falsif_pb.GetBrSet_False();
%             if ~isempty(trace)
%                 trace.PlotSignals
%                 fprintf(fileID,'\n Exit from Simulated Annealing')
%                 comptime = toc(TotCompTime);
%                 fprintf(fileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
%                 error('Falisifier found! Exit normally');
%             end
%         
%             
            
        case 3 %global_nelder_mead
            %%
             r = abs(round(rand*100)+1);
             rng(0,'twister');

            fprintf(1,'\n *** Running Global Nelder Mead');
            fprintf(fileID,'\n *** Running Global Nelder Mead');
             
            %time_lim = input('\n Specify time limit of computation in seconds\n');
            %time_lim = 100; %computation time limit
            %fprintf('\n Time limit of computation is %d seconds\n',time_lim)
%           time_lim = 200
            time_lim = 500 % Nisha Mishra 
            
            
%             nb_local_iter = input('\n Specify nb of local iterations for each solver call\n');
%             fprintf('\n Specify nb of local iterations for each solver call %d \n',max_sim)
            nb_local_iter = 100;
%              nb_local_iter = 1000;
            
            % reset falsif_pb if user_reset = 'yes'
            %if strcmp(user_reset,1)
            if call_count==1 
                falsif_pb = FalsificationProblem(CBS, phi); 
            else
                clear CBS;
                CBS = Sys.copy();
                falsif_pb = FalsificationProblem(CBS, phi); 
            end  
            
            falsif_pb.setup_solver('global_nelder_mead');
            falsif_pb.max_time = time_lim;
            falsif_pb.solver_options.nb_local_iter = nb_local_iter;
            %search_space_dim
            falsif_pb.solver_options.start_at_trial=2^search_space_dim;
            falsif_pb.solver_options.nb_new_trials=2^(search_space_dim/2);
            
             %strategy_id=2; 
            if (call_count>1) 
                nbsamples=100;
                if (strategy_id==2)
                    nbsamples=call_count; %taken from the last xbest point(s)
                end
                
                x0 = initSolver(CBS,nbsamples,solver_index,Xlog,Xbest,strategy_id,winlen);
                
                %CBS.QuasiRandomSample(100, 2^10);
                %x0_qrandom = CBS.GetParam(falsif_pb.params);
                %x0 = [ x0, x0_qrandom ];
                %input('') 
                
                nbsamplesPR=0;
                CBS.QuasiRandomSample(nbsamplesPR, 2^10);
                x0_more = CBS.GetParam(falsif_pb.params);
                x0 = [ x0, x0_more ];
                if (~isempty(x0))
                    falsif_pb.x0 = x0;
                end
            else
%               nbsamplesPR=200;
                nbsamplesPR=100; % Edited by Nisha Mishra
                CBS.QuasiRandomSample(nbsamplesPR, 2^10);
                x0 = CBS.GetParam(falsif_pb.params);
                falsif_pb.x0 = x0;
                %size(x0,2)
            end
            
            falsif_pb.verbose=0;
            
%             falsif_pb
            
            timervar_gnm = tic;
            falsif_pb.solve();
            
            new_pts = falsif_pb.X_log; % column vectors of newly simulated points
            Sys = CoverageBreachSet_Add_Pts(Sys, new_pts); 
            Xlog.xlogGNM = [Xlog.xlogGNM, new_pts];
            
            new_obj_best = falsif_pb.obj_best;
            
            if (~isempty(Valbest.GNM))
                 valbest_last = Valbest.GNM(size(Valbest.GNM,2));
                 if (valbest_last > new_obj_best) 
                   Valbest.GNM = [Valbest.GNM, new_obj_best];
                   new_xbest = falsif_pb.x_best;
                   Xbest.xbestGNM = [Xbest.xbestGNM, new_xbest];
                 end
             else
                 Valbest.GNM = [Valbest.GNM, new_obj_best];
                 new_xbest = falsif_pb.x_best;
                 Xbest.xbestGNM = [Xbest.xbestGNM, new_xbest];
            end
            
            
            trace = falsif_pb.GetBrSet_False();
            
            time_gnm = toc(timervar_gnm);
            fprintf(fileID,'\n Global Nelder Mead time = %f seconds',time_gnm);
            fprintf(1,'\n Global Nelder Mead time = %f seconds',time_gnm);
            
            
            
            if ~isempty(trace)
                trace.PlotSignals
                fprintf(fileID,'\n Exit from Global Nelder Mead')
                comptime = toc(TotCompTime);
                fprintf(fileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
                error('Falisifier found! Exit normally');
            end
            
        otherwise
                error('no input')
    end   % end of switch  
    
    total_nb_sim = total_nb_sim+size(new_pts,2); % update total nb simulations
    
    %disp('Current min robustness ')
    %min_robustness
    
    
    
   
     fprintf(1,'\n Best Robustness Value of this call = %f', new_obj_best);    
     fprintf(fileID,'\n Best Robustness Value of this call = %f', new_obj_best);
     
     if (new_obj_best<=0)
        fprintf(fileID,'\n Falsifier Found!');
        
        comptime = toc(TotCompTime);
        fprintf(fileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
%         error('Falisifier found! Exit normally'); Commented by Nisha
%         Mishra
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
        
        if(solver_index==2)
            solver_index=3; 
        end % skip SA (Nisha Mishra)
        
%             if (solver_index==3) 
%                 solver_index=1; %skip GNM
%             end    
        if (solver_index>(Nb_Optimizers-1)) 
            fprintf(1,'\n\n*******\n #%d round(s) of solver calls done', round_count);
            fprintf(fileID,'\n #%d round(s) of solver calls done', round_count);
            solver_index = 1;
            round_count = round_count + 1;
            
            rob_stagnant
            
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
