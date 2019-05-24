classdef MetaFalsify < handle
    % METAFALSIFY: Class implementing combined metaheuristics falsification
    
    properties

        model_name % = 'KD_cl_harness_forthao';
        simTime % = 50;
        IO_signal_names % = {'In1','In2','Out1'};
        input_signal_names % = {'In1','In2'};
        signal_gen_method % = {'previous','previous'};
        %signal_types = { 'UniStep', 'UniStep'} ;
        nb_ctr_pts % = [ 10; 10 ] ;
        input_ranges
        %CoverageBreachSet Br;
        
        %% Problem definition and logging
        
        %%
        Br % BreachSystem
        R  % Requirement to falsify
        Pbs % (sequence of) falsification problem(s)
        
        max_time = inf         % one hour default max time
        max_total_obj_eval = 3000
        
        %% properties for combined metaheuristics algo
        
        seed = 5000
        %% limit on nb of solver calls
        nb_solver_calls = 30 %1 
        
        %%%% Search Monitoring Parameters
        %% cov_epsilon = input('Specify coverage increase threshold : ');
        cov_epsilon = 1e-3
        %% min robustness decrease in percentage
        rob_epsilon_percent = 0.05
        %% min robustness stagnant monitoring window
        rob_stagnant_win = 1
        %% coverage stagnant monitoring window
        cov_monitoring_win = 1;
        
        %%% Options for picking initial conditions
        re_init_strategy = 2;
        % re_init_strategy=0 to pick randomly from the whole space
        % re_init_strategy=1 to pick randomly from xlog
        % re_init_strategy=2 to pick randomly from xbest
        
        % re_init_num_xbest: window of choice from xbest, for picking initial point
        re_init_num_xbest = 1;
        
        % num_solvers=nb of solvers other than pseudorandom sampling
        % TODO add solver_list, and init num_solver as numel(solver_list)
        num_solvers = 4;
        
        %solver_time = [ 100 500 400 200 ]; % default for diesel model
        solver_time = [ inf inf inf inf];
        max_obj_eval = [ 100 100 100 100 ]; % default for diesel model
        
        start_solver_index = 0; %1; %PR 0, cmaes 1, SA 2, GNM 3
    end
    
    
    methods
        %% Simple constructor
                
        function this = MetaFalsify(Br, R, Pbs)
            this.Br = Br.copy();
            this.R = R;
            this.Pbs = Pbs.copy();
        end 
        
        
        function this = MetaFalsifyCreate(model_name,IO_signal_names)
            if nargin == 2
                this.CoverageBreachSetCreation(model_name,IO_signal_names);
            else
                this.CoverageBreachSetCreation(model_name);                
            end
        end   
        
        function this = CoverageBreachSetCreation(this,model_name,IO_signal_names)
            
            this.Br = CoverageBreachSet(model_name,{});
            this.IO_signal_names=IO_signal_names;
            this.model_name=model_name;
            
        end
        
        function SimTimeSetUp(this,simTime)
            this.Br.SetTime(simTime);
            this.simTime=simTime;
        end
        
        function this = InputSignalSetUp(this,input_signal_names,signal_gen_method,nb_ctr_pts,input_ranges,timepoints,timeFixed)
            nb_signals = numel(input_signal_names);
            this.input_signal_names=input_signal_names;
            this.signal_gen_method=signal_gen_method;
            this.nb_ctr_pts=nb_ctr_pts;
            this.input_ranges=input_ranges;
            
            %fprintf('\n Parametrizing input signal as piecewise constant....\n')
            %nb_signals;
            
            Input_Gen.cp = nb_ctr_pts'; %transposed
            %Input_Gen.type = 'UniStep'; %signal_types;
            Input_Gen.type = 'VarStep'; %signal_types;
            %signal_gen_method
            Input_Gen.method = signal_gen_method; %{'previous','previous'};
            this.Br.SetInputGen(Input_Gen);
            
            signal_u = [];
            for ii=1:nb_signals
                %signal_types(ii,1)
                %Input_Gen.type = 'UniStep'; %signal_types(ii,1) %'UniStep'
                %Input_Gen.cp = nb_ctr_pts(ii,1);
                %this.Br.SetInputGen(Input_Gen);
                
                % Specifying parameter names
                signal_uii = {};
                for i=0:nb_ctr_pts(ii,1)-1
                    par_name_prefix = input_signal_names{ii};
                    par_name_prefix = strcat(par_name_prefix,'_u');
                    signal_uii{1,i+1}=strcat(par_name_prefix,num2str(i));
                end
                %signal_uii
                signal_u = [ signal_u, signal_uii ];
            end
            %signal_u
            
            
            %%%% signal_gen_method = {'linear','linear'};
            %%%% In1_u0 =
            %%%% In1_dt0 = time(2) - time(1)
            %%%% no final interval dt
            signal_dt = [];
            for ii=1:nb_signals
                % Specifying parameter names for time points
                signal_dtii = {};
                for i=0:nb_ctr_pts(ii,1)-2
                    par_name_prefix = input_signal_names{ii};
                    par_name_prefix = strcat(par_name_prefix,'_dt');
                    signal_dtii{1,i+1}=strcat(par_name_prefix,num2str(i));
                end
                %signal_uii
                signal_dt = [ signal_dt, signal_dtii ];
            end
            %signal_dt
            
            %         range_matrix = ones(nb_ctr_pts(1,1),1)*input_ranges(1,:);
            %         for ii=2:nb_signals
            %           range_matrix = [range_matrix; ones(nb_ctr_pts(ii,1),1)*input_ranges(ii,:)];
            %         end
            %
            
            %this.Br.SetParamRanges(signal_u,range_matrix);
            this.Br.SetParamRanges(signal_u,input_ranges);
            
            if ~exist('timeFixed','var')
                timeFixed = true;
            end
            
            if (timeFixed)
                this.Br.SetParam(signal_dt, diff(timepoints)');
            else
                starttime=zeros(nb_ctr_pts,1);
                endtime=timepoints(size(timepoints,1))*ones(nb_ctr_pts,1);
                
                %time_ranges = [starttime endtime];
                time_ranges = [1e-6 3e-6];
                this.Br.SetParamRanges(signal_dt, time_ranges);
            end
            
            %         [~, varying_parameter_indices] = this.Br.GetBoundedDomains();
            %         varying_parameter_indices
            %         this.Br
            
            disp('Done with signal setup');
            
        end
                
        function x0= InitSolver(this,nbsamples,solver_index,num_solvers,SolverInfo,strategy_id,winlen)
            CBS = this.Br;
            % InitSolver(xlog_vec, xbest_vec)
            % function: pick an initial point for solvers
            %
            % Inputs:
            % xlog_vec: explored points
            % xbest_vec: best points from previous solver runnings
            % strategy_id: choice of strategy
            % winlen: window of choice from xbest
            
            rand_idvec = [];
            x0 = [];
            xlog_vec = [];
            xbest_vec= [];
            
            switch strategy_id
                case 0 %init from xlogPR
                    
                    %xlogPR_vec = Xlog.xlogPR;
                    xlogPR_vec = SolverInfo(1).Xlog;
                    nb_pt_xlogPR =size(xlogPR_vec,2);
                    if (nbsamples>nb_pt_xlogPR)
                        nbsamples = nb_pt_xlogPR;
                    end
                    i=1;
                    itrial=1;
                    while (i<=nbsamples && itrial<=2*nbsamples)
                        rand_id = max(1, floor(rand*nb_pt_xlogPR));
                        if (i==1)
                            rand_idvec = [rand_idvec; rand_id];
                            i=i+1;
                        else
                            if (isempty(find(rand_idvec == rand_id)))
                                i=i+1;
                                rand_idvec = [rand_idvec; rand_id];
                                x0i = xlogPR_vec(:,rand_id);
                                inRange = CBS.TestPointInRange(x0i);
                                if (inRange)
                                    x0 = [x0, x0i];
                                end
                            end
                        end
                        if (rand_id<1 || rand_id>nb_pt_xlogPR)
                            error('Error in rand_id_xlogPR');
                        end
                        itrial=itrial+1;
                    end %end while
                    
                case 1 %init from xlog
                    
                    %%% collecting xlog but not from the current solver
                    for (ii=1:1:num_solvers)
                        if (~(ii==solver_index))
                            xlog_vec = [xlog_vec, SolverInfo(ii).Xlog];
                        end
                    end
                    
                    nb_pt_xlog=size(xlog_vec,2);
                    if (nbsamples>nb_pt_xlog)
                        nbsamples = nb_pt_xlog;
                    end
                    i=1;
                    itrial=1;
                    while (i<=nbsamples && itrial<=2*nbsamples)
                        rand_id = max(1, floor(rand*nb_pt_xlog));
                        if (i==1)
                            rand_idvec = [rand_idvec; rand_id];
                            x0i = xlog_vec(:,rand_id);
                            inRange = CBS.TestPointInRange(x0i);
                            if (inRange)
                                x0 = [x0, x0i];
                            end
                            i=i+1;
                        else
                            if (isempty(find(rand_idvec == rand_id)))
                                i=i+1;
                                rand_idvec = [rand_idvec; rand_id];
                                x0i = xlog_vec(:,rand_id);
                                inRange = CBS.TestPointInRange(x0i);
                                if (inRange)
                                    x0 = [x0, x0i];
                                end
                            end
                        end
                        if (rand_id<1 || rand_id>nb_pt_xlog)
                            error('Error in rand_id_xlog');
                        end
                        itrial=itrial+1;
                    end %end while
                    
                case 2 %init from xbest of one solver chosen randomly
                    
                    solversdone= zeros(num_solvers);  %[ 0 0 0 ];
                    nbsolversdone = 0;

                    for ii = 1:1:(num_solvers)
                        if (size(SolverInfo(ii).Xbest,2)>0)
                            solversdone(1) = 1;
                            nbsolversdone = nbsolversdone + 1;
                        end
                    end
                    
                    
                    itrial=1;
                    while (itrial<=nbsamples && nbsolversdone>0)
                        %rand_id = nb_pt_xbest - floor(rand*winlen1);
                        rand_solverid = randi(3);
                        %rand_solverid = 3;
                        
                        %do not use xbest of the same solver
                        %                     if (rand_solverid==solver_index)
                        %                         break
                        %                     end
                        
                        if (solversdone(rand_solverid) >0)
                            %                         switch rand_solverid
                            %                             case 1
                            nb_pt_xbest=size(SolverInfo(rand_solverid+1).Xbest,2);
                            if nb_pt_xbest>0
                                rand_id = randi(nb_pt_xbest);
                                if (rand_id<0 || rand_id>nb_pt_xbest)
                                    error('Error in rand_id_xbest');
                                end
                                xbest_vec = SolverInfo(rand_solverid+1).Xbest;
                                x0i = xbest_vec(:,rand_id);
                                xbest_vec(:,rand_id) = [];
                                SolverInfo(rand_solverid+1).Xbest = xbest_vec;
                            end
                            
                            
                            if nb_pt_xbest>0
                                inRange = CBS.TestPointInRange(x0i);
                                if (inRange)
                                    x0 = [x0, x0i];
                                end
                            end
                            
                        end %if (nbsolversdone(rand_solverid) >0)
                        
                        itrial=itrial+1;
                    end %end while
                otherwise
                    error('error in reinit_strategy')
            end %end of switch
        end
        
        function this = GridSetUp(this,gridsize_vector,nb_ctr_pts,timeFixed)
            
            if ~exist('timeFixed','var')
                timeFixed = true;
            end
            
            gridsizeMat = [];
            size(gridsize_vector,1)
            for ii = 1:size(gridsize_vector,1)
                gridsizeMat = [ gridsizeMat; gridsize_vector(ii,1)*ones(nb_ctr_pts(ii,1),1) ];
            end
            %         fprintf('\n Grid discretization unit for signal value range is\n');
            %         gridsize_vector;
            
            % add this grid size for time parameters, # = nb_ctr_pts(ii,1)-1
            if (timeFixed==false)
                gridsizeMat = [ gridsizeMat; gridsize_vector(1,1)*ones(nb_ctr_pts(ii,1)-1,1) ];
            end
            
            this.Br.SetEpsGridsize(gridsizeMat);
            this.Br.SetDeltaGridsize(2*this.Br.epsgridsize);
            disp('Done with grid setup');

        end        
        
        function this = STLFormulaSetUp(this,phi)
            %% Specifying STL formula or Breach requirement
            if isa(this.R, 'STL_Formula')
                R = BreachRequirement(this.R);
            else
                this.R = phi;
            end
            disp('Done with STL setup');
        end
     
        function this = MetaFalsifySetup(model_name,IO_signal_names)
            disp('Creating Coverage Breach Set');
            this.CoverageBreachSetCreation(model_name,IO_signal_names);
            disp('Done Creating Coverage Breach Set');
        end
        
        function this = MetaSetupRun(this, Br, R)
            this.Br = Br.copy();
            this.R = R;
            %           if nargin >= 3
            %               this.Run(solver)
            %           end
            this.MetaCall();
            
        end                
        
        %%
        function this = Run(this, solver)
            
            switch solver
                
                case 'corners'
                    disp('Running corners ...')
                    B = this.Br.copy();
                    B.CornerSample(this.max_obj_eval);
                    Pb = FalsificationProblem(B, this.R);
                    Pb.setup_init();
                    Pb.max_obj_eval = this.max_obj_eval;
                    Pb.max_time = this.max_time;
                    Pb.solve();
                    this.Pbs{end+1} = Pb;
                    
                case 'quasirandom'
                    disp('Running quasirandom ...')
                    B = this.Br.copy();
                    B.QuasiRandomSample(this.max_obj_eval);
                    Pb = FalsificationProblem(B, this.R);
                    Pb.setup_init();
                    Pb.max_obj_eval = this.max_obj_eval;
                    Pb.max_time = this.max_time;
                    Pb.solve();
                    this.Pbs{end+1} = Pb;
                    
                case 'global_nelder_mead'
                    disp('Running global-nelder-mead ...')
                    Pb = FalsificationProblem(this.Br, this.R);
                    Pb.setup_global_nelder_mead();
                    Pb.max_obj_eval = this.max_obj_eval;
                    Pb.max_time = this.max_time;
                    Pb.solve();
                    this.Pbs{end+1} = Pb;
                    
                case 'cmaes'
                    % configure and run a CMAES falsification problem
                    
                case 'meta'
                    % run a metaheuristic combined approach (should call
                    % MetaCall
            end
            
            
            
            
        end
        %%
        
        %%
        function h = PlotResults(this)
            % collect logs of falsification runs and open figures
            
            for ipb = 1:numel(this.Pbs)
                pb = this.Pbs{ipb};
                Rlog = pb.GetLog();
                h(ipb) = BreachSamplesPlot(Rlog);
            end
            
        end
        
        %% Combined metaheuristics main algo
        function [this,falsified,total_nb_sim,falsi_point] = MetaCall(this)
            % [FALSIFIED, NB, FALSI_POINT] = THIS.METACALL(Br, PHI, NB_SAMPLES, HITS)
            % FUNCTION: Call the metaheuristics to optimize the
            % robustness values
            %
            % INPUTS:
            % Br: CoverageBreachSet object.
            %
            % phi: STL formula or BreachRequirement
            %
            % OUTPUTS:
            %
            % falsified: Boolean value indicating if property is falsified.
            %
            % total_nb_sim: Number of function evaluations (simulation+robustness)
            
            %%%%%%% Method 'MetaCall' starts here            
            rng(this.seed,'twister');            
            
            %% Transform the STL formula into Breach Requirement
            if isa(this.R, 'STL_Formula')
                disp('You selected the following STL formula for falsification')
                this.R
                this.R = BreachRequirement(this.R);
            end
            
            prev_solver_index=0;
            solver_index = this.start_solver_index; %PR 0, cmaes 1, SA 2, GNM 3
            
            %% local variables for search monitoring
            falsified = false;
            stagnant_count=0;
            cov_monitoring_length = this.cov_monitoring_win;
            rob_stagnant=false;
            min_robustness=inf;
            
            %% Variables to store search intermediate results
            robustness_graph_data = [];
            coverage_graph_data = [];
            solver_index_data = [];
            
            for (ii=1:1:this.num_solvers)
                SolverInfo(ii).Xlog=[];
                SolverInfo(ii).Xbest=[];
                SolverInfo(ii).Valbest=[];
            end
            
            search_space_dim = numel(this.Br.epsgridsize);
            % search_space_dim is used to estimate the number of initial points
            
            total_nb_sim = 0; % current total number of simulations
            
            % file to save intermediate results
            fileID = fopen('OutFalsification.txt','w');
                        
            round_count=1;
            TotCompTime = tic;            
            
            %%%%%% Falsification Loop %%%%%%%%%
            for call_count = 1:this.nb_solver_calls
                
                
                %% Make a working copy of the original coverage breach set object
                if call_count>1
                    CBS = this.Br.copy();
                else
                    CBS = this.Br.copy();
                end
                
                %% Initialize the falsification problem with the system and the requirement
                falsif_pb = FalsificationProblem(CBS, this.R);
                %falsif_pb = this.Pbs %%%Thao temporily set this
                falsif_pb.StopAtFalse = 0;
                
                %% start counting computation time for each solver
                timervar_solver = tic;                                
                StatFalsObj = StatFalsify();
                
                switch solver_index
                    
                    case 0 % quasi-random sampling
                        
                        fprintf(1,'\n *** Running QuasiRandom');
                        fprintf(fileID,'\n *** Running QuasiRandom');
                        
                        time_lim = this.solver_time(1,solver_index +1); %100; %500;
                        eval_lim = this.max_obj_eval(1,solver_index +1);
%                         nb_samples = 10;
%                         nb_hits = 20;
                        fprintf(1, '\n Time limit of computation is %d seconds\n',time_lim);
                        fprintf(fileID, '\n Time limit of computation is %d seconds\n',time_lim);
%                         fprintf(1, 'nb_samples for PR is %d seconds\n',nb_samples);
%                         fprintf(fileID, 'nb_samples for PR is %d \n',nb_samples);
%                         fprintf(1, 'nb_hits for PR %d \n',nb_hits);
%                         fprintf(fileID, 'nb_hits for PR is %d \n',nb_hits);
                        
                        fprintf(1, '\n Max eval number is %d seconds\n',eval_lim);
                        fprintf(fileID, '\n Max eval number is %d seconds\n',eval_lim);
%                      
                        
                        
                        CBS.QuasiRandomSample(this.max_obj_eval(1,solver_index +1));
                        falsif_pb = FalsificationProblem(CBS, this.R);
                        falsif_pb.setup_init();
                        falsif_pb.max_obj_eval = this.max_obj_eval(1,solver_index +1);
                        falsif_pb.max_time = this.solver_time(1,solver_index +1); 
                        falsif_pb.solve();
                        
                        
                        % adding new points to xlog
                        new_pts = falsif_pb.X_log % column vectors of newly simulated points.
                        %                     Br = CoverageBreachSet_Add_Pts(Br, new_pts);
                        %                     Xlog.xlogCMAES = [Xlog.xlogCMAES, new_pts];
                        
                        % adding new points to xbest
                        new_obj_best = falsif_pb.obj_best;
                        
                        
%                         StatFalsObj=PseudoRandomCall(StatFalsObj,CBS,this.R,nb_samples,time_lim,nb_hits);
%                         
%                         % adding new points to Br
%                         new_pts = transpose(StatFalsObj.new_samples.pts); % column vectors of newly simulated points.
%                         %Br = CoverageBreachSet_Add_Pts(Br, new_pts);
%                         % adding new points to xlog
%                         %Xlog.xlogPR = [Xlog.xlogPR, new_pts];
%                         
%                         time_solver = toc(timervar_solver);
%                         
%                         fprintf(1,'\n PseudoRandom time = %f seconds',time_solver);
%                         fprintf(fileID,'\n PseudoRandom time = %f seconds',time_solver);
%                         
%                         % adding new points to xbest
%                         [new_obj_best,new_best_id]=min(StatFalsObj.lower_bounds.vals);
                                                
                        %%%%%%%%%
                    case 1 % CMAES
                        %%
                        fprintf(1,'\n **** Running CMAES');
                        fprintf(fileID,'\n **** Running CMAES');
                        
                        if (call_count==1)
                            time_lim = this.solver_time(1,solver_index +1); %2000; %2000 %800
                        else
                            time_lim = this.solver_time(1,solver_index +1); %2000; %500 %2000 %400
                        end
                        
                        fprintf(1, '\n Time limit of computation is %d seconds\n',time_lim);
                        fprintf(fileID, '\n Time limit of computation is %d seconds\n',time_lim);
                        
                        falsif_pb.setup_solver('cmaes');
                        falsif_pb.solver_options.SaveVariables = 'off';
                        falsif_pb.solver_options.MaxFunEvals=this.max_obj_eval(1,solver_index +1);
                        falsif_pb.max_obj_eval=this.max_obj_eval(1,solver_index +1);
                        
                        %falsif_pb.solver_options.Restarts = 3;
                        falsif_pb.max_time = time_lim;
                        
                        %this.re_init_strategy=2;
                        if (call_count>1)
                            nbsamples=200;
                            if (this.re_init_strategy==2)
                                nbsamples=this.re_init_num_xbest; %taken from the last xbest point(s)
                            end
                            
                            x0= this.InitSolver(nbsamples,solver_index,this.num_solvers,SolverInfo,this.re_init_strategy,this.re_init_num_xbest);
                            
                            if (this.re_init_strategy==0)
                                nbsamplesPR=1000; %100
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
                            falsif_pb.x0 = x0';
                        end
                        
                        
                        falsif_pb.solve();
                        
                        % adding new points to xlog
                        new_pts = falsif_pb.X_log; % column vectors of newly simulated points.
                        %                     Br = CoverageBreachSet_Add_Pts(Br, new_pts);
                        %                     Xlog.xlogCMAES = [Xlog.xlogCMAES, new_pts];
                        
                        new_pts
                        
                        
                        % adding new points to xbest
                        
                        new_obj_best = falsif_pb.obj_best;
                        
                        %%%%%%%%%%
                        %%%%%%%%%%
                    case 2 %Simulated Annealing
                        fprintf(1,'\n *** Running Simulated Annealing');
                        fprintf(fileID,'\n *** Running Simulated Annealing');
                        
                        time_lim = this.solver_time(1,solver_index +1); %1000;
                        fprintf(1, '\n Time limit of computation is %d seconds\n',time_lim);
                        fprintf(fileID, '\n Time limit of computation is %d seconds\n',time_lim);
                        
                        
                        falsif_pb.setup_solver('simulannealbnd');
                        falsif_pb.max_time = time_lim;
                        
                        % this.re_init_strategy=0 to pick randomly from the whole space
                        % this.re_init_strategy=1 to pick randomly from xlog
                        % this.re_init_strategy=2 to pick randomly from xbest
                        
                        %this.re_init_strategy=1;
                        if (call_count>1)
                            %                           nbsamples=100;
                            %                           if (this.re_init_strategy==2)
                            %                               nbsamples=1; %taken from the last xbest point(s)
                            %                           end
                            nbsamples=1;
                            x0 = this.InitSolver(nbsamples,solver_index,this.num_solvers,SolverInfo,this.re_init_strategy,this.re_init_num_xbest);
                            
                            %                           nbsamplesPR=0;
                            %                           CBS.QuasiRandomSample(nbsamplesPR, 2^10);
                            %                           x0_more = CBS.GetParam(falsif_pb.params);
                            %                           x0 = [ x0, x0_more ];
                            %
                            if (~isempty(x0))
                                falsif_pb.x0 = x0;
                            end
                        else
                            %CBS.QuasiRandomSample(100, 2^10);
                            nbsamples=1;
                            CBS.QuasiRandomSample(nbsamples, 2^10);
                            x0 = CBS.GetParam(falsif_pb.params);
                            falsif_pb.x0 = x0;
                        end
                        
                        falsif_pb.verbose=0;
                        falsif_pb.solver_options.FunctionTolerance = 1e-3;
                        falsif_pb.solver_options.OptimalityTolerance = 1e-3;
                        falsif_pb.solver_options.MaxFunEvals = 1000;
                        falsif_pb.solver_options.InitialTemperature = 100;
                        falsif_pb.max_obj_eval=this.max_obj_eval(1,solver_index +1);
                        
                        falsif_pb.solve();
                        
                        new_pts = falsif_pb.X_log; % column vectors of newly simulated points
                        %                     Br = CoverageBreachSet_Add_Pts(Br, new_pts);
                        %                     Xlog.xlogSA = [Xlog.xlogSA, new_pts];
                        
                        %             new_obj_val = falsif_pb.obj_log;
                        %             Vlog.objlogSA = [Vlog.objlogSA, new_obj_val];
                        
                        new_obj_best = falsif_pb.obj_best;
                        
                        
                    case 3 %global_nelder_mead
                        %%
                        
                        fprintf(1,'\n *** Running Global Nelder Mead');
                        fprintf(fileID,'\n *** Running Global Nelder Mead');
                        
                        
                        time_lim = this.solver_time(1,solver_index +1); %1000; %100
                        fprintf(1, '\n Time limit of computation is %d seconds\n',time_lim);
                        fprintf(fileID, '\n Time limit of computation is %d seconds\n',time_lim);
                        
                        nb_local_iter = 100;
                        fprintf(fileID, '\n Nb of local iterations %d \n', nb_local_iter);
                        fprintf(1, '\n Nb of local iterations %d \n', nb_local_iter);
                        
                        falsif_pb.setup_solver('global_nelder_mead');
                        falsif_pb.max_time = time_lim;
                        falsif_pb.solver_options.nb_local_iter = nb_local_iter;
                        falsif_pb.max_obj_eval=this.max_obj_eval(1,solver_index +1);
                        %search_space_dim
                        falsif_pb.solver_options.start_at_trial=2^search_space_dim;
                        falsif_pb.solver_options.nb_new_trials=2^(search_space_dim/2);
                        
                        %this.re_init_strategy=2;
                        if (call_count>1)
                            nbsamples=100;
                            if (this.re_init_strategy==2)
                                nbsamples=call_count; %taken from the last xbest point(s)
                            end
                            
                            x0 = this.InitSolver(nbsamples,solver_index,this.num_solvers,SolverInfo,this.re_init_strategy,this.re_init_num_xbest);
                            
                            %CBS.QuasiRandomSample(100, 2^10);
                            %x0_qrandom = CBS.GetParam(falsif_pb.params);
                            %x0 = [ x0, x0_qrandom ];
                            %input('')
                            
                            %                 nbsamplesPR=0;
                            %                 CBS.QuasiRandomSample(nbsamplesPR, 2^10);
                            %                 x0_more = CBS.GetParam(falsif_pb.params);
                            %                 x0 = [ x0, x0_more ];
                            
                            if (~isempty(x0))
                                falsif_pb.x0 = x0;
                            end
                        else
                            nbsamplesPR=500; %200
                            CBS.QuasiRandomSample(nbsamplesPR, 2^37);
                            x0 = CBS.GetParam(falsif_pb.params);
                            falsif_pb.x0 = x0;
                            %size(x0,2)
                        end
                        
                        falsif_pb.verbose=0;
                        falsif_pb.solve();
                        
                        new_pts = falsif_pb.X_log; % column vectors of newly simulated points
                        %                     Br = CoverageBreachSet_Add_Pts(Br, new_pts);
                        %                     Xlog.xlogGNM = [Xlog.xlogGNM, new_pts];
                        
                        new_obj_best = falsif_pb.obj_best;
                        
                        
                    otherwise
                        error('no input')
                end   % end of switch
                
                
                %% Updating visited points in the current CoverageBreachSet Br
                this.Br = CoverageBreachSet_Add_Pts(this.Br, new_pts);
                
                
                %% Updating SolverInfo to store xlog, xbest, valbest
                %% updating xlog of the current solver
                if ( ~isempty( SolverInfo(solver_index+1).Xlog ) )
                    SolverInfo(solver_index+1).Xlog=[SolverInfo(solver_index+1).Xlog, new_pts];
                else
                    SolverInfo(solver_index+1).Xlog=new_pts;
                end
                
                %% get the new xbest of the current solver
                if (solver_index==0) %%PR solver stores results in StatFalsObj
                    %new_xbest = (StatFalsObj.lower_bounds.pts(new_best_id,:))';
                    new_xbest = falsif_pb.x_best;
                else
                    new_xbest = falsif_pb.x_best;
                end
                
                %% update xbest if smaller than the xbest of the current solver
                if (~isempty(SolverInfo(solver_index+1).Valbest))
                    valbest_vec = SolverInfo(solver_index+1).Valbest;
                    valbest_last = valbest_vec(size(valbest_vec,2));
                    if (valbest_last > new_obj_best)
                        SolverInfo(solver_index+1).Valbest=[SolverInfo(solver_index+1).Valbest, new_obj_best];
                        SolverInfo(solver_index+1).Xbest=[SolverInfo(solver_index+1).Xbest, new_xbest];
                    end
                else
                    SolverInfo(solver_index+1).Valbest=new_obj_best;
                    SolverInfo(solver_index+1).Xbest=new_xbest;
                end
                %% End of updating SolverInfo
                
                time_solver = toc(timervar_solver);
                fprintf(fileID,'\n This solver time = %f seconds',time_solver);
                fprintf(1,'\n This solver time = %f seconds',time_solver);
                
                trace = falsif_pb.GetBrSet_False();
                if ~isempty(trace)
                    falsified = true;
                    falsi_point = new_xbest;
                    trace.PlotSignals
                    fprintf(fileID,'\n Exit from Solver %d ', solver_index);
                    comptime = toc(TotCompTime);
                    fprintf(fileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
                    error('Falsifier found! Exit normally');
                end
                
                total_nb_sim = total_nb_sim+size(new_pts,2); % update total nb simulations
                
                %disp('Current min robustness ')
                %min_robustness
                
                
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
                        if (rob_change > this.rob_epsilon_percent)
                            rob_improved = true;
                        end
                        min_robustness=new_obj_best;
                    else
                        if (~(solver_index==0) && ~(solver_index==4))
                            rob_stagnant_count=rob_stagnant_count+1;
                        end
                    end
                    
                    if rob_stagnant_count>this.rob_stagnant_win
                        rob_stagnant = true;
                    end
                    
                end
                
                fprintf(1,'\n Best Robustness Value so far = %f', min_robustness);
                fprintf(fileID,'\n Best Robustness Value so far = %f', min_robustness);
                
                
                robustness_graph_data=...
                    [robustness_graph_data; [total_nb_sim min_robustness]];
                
                
                % the coverage graph is monotonic, we check the evolution of coverage
                % for non-increase by this.cov_epsilon
                % recompute current coverage
                current_coverage_value = this.Br.ComputeLogCellOccupancyCoverage;
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
                    
                    if (cov_diff<this.cov_epsilon)
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
                
                fprintf(1,'\n stagnant_count = %d', stagnant_count);
                fprintf(fileID,'\n rob_stagnant = %d', rob_stagnant);
                fprintf(fileID,'\n cov_monitoring_length = %d', cov_monitoring_length);
                
                local_optimum_stuck=(stagnant_count>=cov_monitoring_length) && rob_stagnant
                
                
                if (~local_optimum_stuck)
                    cov_monitoring_length=this.cov_monitoring_win;
                    PR_duration=0;
                    
                    if (prev_solver_index==0)
                        this.re_init_strategy = 1 %pick from xlog, if previously pseudorandon
                    end
                    
                    solver_index = prev_solver_index + 1;
                    
                    if (solver_index==3)
                        solver_index=4; %skip SA, %GNM
                    end
                    
                    if (solver_index>(this.num_solvers-1))
                        fprintf(1,'\n\n*******\n #%d round(s) of solver calls done', round_count);
                        fprintf(fileID,'\n #%d round(s) of solver calls done', round_count);
                        solver_index = 1;
                        round_count = round_count + 1;
                         
                        rob_stagnant
                        
                        if rob_stagnant
                            %this.re_init_strategy = 2 %Thao
                            %solver_index=0
                            this.re_init_strategy = 0
                        else
                            if rob_improved
                                this.re_init_strategy = 2
                            else
                                this.re_init_strategy = 1
                            end
                        end
                    end %end if (solver_index>(this.num_solvers-1))
                    
                else %if local optima stuck
                    solver_index=0; %use pseudorandom sampling to increase coverage
                    PR_duration=PR_duration+1;
                    
                    cov_monitoring_length=PR_duration;
                end
                
                fprintf(1,'\n Solver call %d done', call_count);
                fprintf(fileID,'\n Solver call %d done', call_count);
                
            end % end of for-loop call_count
            
            
            comptime = toc(TotCompTime);
            fprintf(fileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
            fprintf(1,'\n Exit! TOTAL Computation time = %f seconds \n',comptime );
            
            plot(coverage_graph_data, 'Coverage');
            plot(robustness_graph_data, 'Robustness');
        end %end function
        
        
    end %%end method
end %end classdef