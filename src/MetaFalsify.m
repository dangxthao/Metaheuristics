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
        OutFileID
        Plot_signal_names
        
        params
        ranges
        
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
        
        % re_init_num_xbest: nb ofinitial points picked from xbest
        re_init_num_xbest = 1;
        
        % re_init_num_xlog: nb ofinitial points picked from xbest
        re_init_num_xlog = 1;
        
        % re_init_num_xlog: nb ofinitial points picked from xbest
        re_init_num_rand = 1;
        
        % num_solvers=nb of solvers other than random sampling
        % TODO add solver_list, and init num_solver as numel(solver_list)
        num_solvers = 4;
        solver_list = {'PRandom', 'cmaes', 'SA', 'GNM'};
        
        %solver_time = [ 100 500 400 200 ]; % default for diesel model
        solver_time = [ inf inf inf inf];
        max_obj_eval = [ 100 100 100 100 ]; % default for diesel model
        
        start_solver_index = 0; %1; %PR 0, cmaes 1, SA 2, GNM 3
    end
    
    
    methods
        %% Simple constructor
                
         function this = MetaFalsifyPb(Br, R, Pbs)
            this.Br = Br.copy();
            
            %% Transform the STL formula into Breach Requirement
            if isa(R, 'STL_Formula')
                disp('You selected the following STL formula for falsification')
                this.R
                this.R = BreachRequirement(this.R);
            else
                this.R = R;
            end
 
            this.Pbs = Pbs.copy();
            this.params = Pbs.params;
            
            varying_domains = Pbs.domains;
            
            if (numel(varying_domains)~=numel(this.params))
              error('Len of varying par vec do not match in MetaFalsify(Br, R, Pbs)');
            end
            ranges = [];
            for i=1:numel(varying_domains)
              ranges=[ranges;[varying_domains(i).domain(1) varying_domains(i).domain(2)]];
            end  
            
            this.ranges = ranges;
         end
        
        function this = MetaFalsify(Br, R, params, ranges)
            this.Br = Br.copy();
            
            %% Transform the STL formula into Breach Requirement
            if isa(R, 'STL_Formula')
                disp('You selected the following STL formula for falsification')
                this.R
                this.R = BreachRequirement(this.R);
            else
                this.R = R;
            end
            
            this.params = params;
            this.ranges = ranges;
            
            Pbs = FalsificationProblem(Br, R, params, ranges);
            this.Pbs = Pbs.copy();
        end 
        
        
        function this = MetaFalsifyCreate(model_name,IO_signal_names)
            if nargin == 2
                this.BreachSetCreation(model_name,IO_signal_names);
            else
                this.BreachSetCreation(model_name);                
            end
        end   
        
        function this = BreachSetCreation(this,model_name,IO_signal_names)
            this.Br = BreachSimulinkSystem(model_name,{},[],IO_signal_names);        
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
                this.Br.SetParamRanges(signal_uii,input_ranges(ii, :));

            end           
            
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
            
            if ~exist('timeFixed','var')
                timeFixed = true;
            end
            
            if (timeFixed)
                this.Br.SetParam(signal_dt, diff(timepoints)');
            else
                starttime=zeros(nb_ctr_pts,1);
                endtime=timepoints(size(timepoints,1))*ones(nb_ctr_pts,1);
                
                time_ranges = [starttime endtime];
                this.Br.SetParamRanges(signal_dt, time_ranges);
            end
            
            %         [~, varying_parameter_indices] = this.Br.GetBoundedDomains();
            %         varying_parameter_indices
            %         this.Br
            
            disp('Done with signal setup');
            
        end
                
        function x0= InitSolver(this,nbsamples,solver_index,num_solvers,SolverInfo,strategy_id,winlen)
            % Pick an initial point for solvers
            % Inputs:
            % strategy_id: choice of strategy
            % winlen: window of choice from xbest
            CBS = this.Br.copy();
            
            rand_idvec = [];
            x0 = [];
            xlog_vec = [];
            xbest_vec= [];
            
            switch strategy_id
                case 0 %init from xlogPR                    
                    xlogPR_vec = SolverInfo(1).Xlog;
                    nb_pt_xlogPR =size(xlogPR_vec,2);
                    if (nbsamples>nb_pt_xlogPR)
                        nbsamples = nb_pt_xlogPR;
                    end
                    
                    if (nbsamples<=0)
                        return;
                    end
                    
                    rand_id = randi(nb_pt_xlogPR,[nbsamples,1]);
                    %nbsamples random integers in [1,nb_pt_xlog]
                    [rand_id,~,~] = unique(rand_id);
                        
                    for (ii=1:1:size(rand_id,1)) 
                       if (rand_id(ii,1)<1 || rand_id(ii,1)>nb_pt_xlogPR)
                          error('Error in rand_id_xlogPR');
                       end
                       x0i = xlogPR_vec(:,rand_id(ii,1));
                       inRange = CBS.TestPointInRange(x0i);
                       if (inRange)
                          x0 = [x0, x0i];
                       end
                     end
                    
                    
                case 1 %init from Xlog of not-current solvers
                    for (ii=1:1:num_solvers)
                       if (~(ii==(solver_index+1)))
                         xlog_vec =[xlog_vec SolverInfo(ii).Xlog];
                       end
                    end
                    
                    nb_pt_xlog = size(xlog_vec,2);
                    if (nbsamples>nb_pt_xlog)
                        nbsamples = nb_pt_xlog;
                    end 
                    
                    if (nbsamples<=0)
                        return;
                    end
                    
                    rand_id = randi(nb_pt_xlog,[nbsamples,1]);
                    %nbsamples random integers in [1,nb_pt_xlog]
                    [rand_id,~,~] = unique(rand_id);
                        
                    for (ii=1:1:size(rand_id,1)) 
                         if (rand_id(ii,1)<1 || rand_id(ii,1)>nb_pt_xlog)
                            error('Error in rand_id_xlog');
                         end
                         x0i = xlog_vec(:,rand_id(ii,1));
                         inRange = CBS.TestPointInRange(x0i);
                         if (inRange)
                            x0 = [x0, x0i];
                         end
                     end
                    
                    
                case 2 %init from Xbest of one solver chosen randomly
                    solversdone= zeros(num_solvers,1);  %[0 0 0 0];
                    nbsolversdone = 0;
                    nbxbest_available = 0;
                    for ii = 1:1:(num_solvers)
                        if (size(SolverInfo(ii).Xbest,2)>0)
                           solversdone(ii,1) = 1;
                           nbsolversdone = nbsolversdone + 1;
                           nbxbest_available = nbxbest_available +...
                                size(SolverInfo(ii).Xbest,2);
                        end
                    end
                    
                    if (nbsamples > nbxbest_available) 
                        nbsamples = nbxbest_available; 
                    end
                    
                    if (nbsamples<=0)
                        return;
                    end
                    
                    nbpt = 0;
                    while (nbpt<nbsamples && nbsolversdone>0)
                        rand_solverid = randi(4,1); %random integer in [1,3] 
                        
                        if (solversdone(rand_solverid,1) >0)
                            nb_pt_xbest=size(SolverInfo(rand_solverid).Xbest,2);
                            if nb_pt_xbest>0
                                rand_id = randi(nb_pt_xbest,1);
                                if (rand_id<0 || rand_id>nb_pt_xbest)
                                    error('Error in rand_id_xbest');
                                end
                                xbest_vec = SolverInfo(rand_solverid).Xbest;
                                x0i = xbest_vec(:,rand_id);
                                xbest_vec(:,rand_id) = [];
                                SolverInfo(rand_solverid).Xbest = xbest_vec;
                            end
                            
                            if nb_pt_xbest>0
                                inRange = CBS.TestPointInRange(x0i);
                                if (inRange)
                                    x0 = [x0, x0i];
                                    nbpt=nbpt+1;
                                end
                            end
                            
                        end %if (nbsolversdone(rand_solverid) >0)
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
        
        function this = GridNbSetUp(this,gridnb_vector)                      
            varying_param_names = this.Br.GetVariables();
            varying_domains = this.Br.GetDomain(varying_param_names)
            
            size(gridnb_vector,2)
            size(varying_param_names,2)
            
            gridsizeMat = [];
            
            for ii = 1:size(gridnb_vector,2)
                varying_domains_size = varying_domains(ii).domain(2) -...
                    varying_domains(ii).domain(1);
                gridsizeMat = [ gridsizeMat;...
                    (varying_domains_size/gridnb_vector(1,ii)) ];
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
        
        
        function this = MetaShortFilePrint(this, fileID)                 
          fprintf(fileID, '\n seed is %d \n', this.seed); 
          fprintf(fileID, '\n nb_solver_calls is %d \n', this.nb_solver_calls);
          fprintf(fileID, '\n cov_epsilon is %d \n', this.cov_epsilon);
          fprintf(fileID, '\n rob_epsilon_percent is %d \n', this.rob_epsilon_percent);
          fprintf(fileID, '\n rob_stagnant_win is %d \n', this.rob_stagnant_win);
          fprintf(fileID, '\n cov_monitoring_win is %d \n', this.cov_monitoring_win);
          fprintf(fileID, '\n re_init_strategy is %d \n', this.re_init_strategy);
          fprintf(fileID, '\n re_init_num_xbest is %d \n', this.re_init_num_xbest);
          fprintf(fileID, '\n re_init_num_xlog is %d \n', this.re_init_num_xlog);
          fprintf(fileID, '\n re_init_num_rand is %d \n', this.re_init_num_rand);
          fprintf(fileID, '\n num_solvers is %d \n', this.num_solvers);
          
          fprintf(fileID, '\n solver_time is [');
          for (i=1:1:this.num_solvers)
            fprintf(fileID, '%d ', this.solver_time(1,i));
          end
          fprintf(fileID, '] \n');
          
          fprintf(fileID, '\n max_obj_eval is [');
          for (i=1:1:this.num_solvers)
            fprintf(fileID, '%d ', this.max_obj_eval(1,i));
          end
          fprintf(fileID, '] \n');
          
          fprintf(fileID, '\n start_solver_index is %d \n', this.start_solver_index);
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
            % [FALSIFIED, NB, FALSI_POINT] = THIS.METACALL()
            % FUNCTION: Call the metaheuristics to optimize the
            % robustness values
            % OUTPUTS:
            % falsified: Boolean value indicating if property is falsified.
            % total_nb_sim: Number of function evaluations (simulation+robustness)
            
            %%           
            rng(this.seed,'twister');            
            
            %% Transform the STL formula into Breach Requirement
            if isa(this.R, 'STL_Formula')
                disp('You selected the following STL formula for falsification')
                this.R
                this.R = BreachRequirement(this.R);
            end
            
            prev_solver_index=0; %initial value has no effect
            solver_index = this.start_solver_index; %PR 0, cmaes 1, SA 2, GNM 3
            re_init_strategy = this.re_init_strategy;
            
            %% Set local variables for search monitoring
            falsified = false;
            stagnant_count = 0;
            cov_monitoring_length = this.cov_monitoring_win;
            rob_stagnant = false;
            min_robustness=inf;
            
            %% Variables to store search intermediate results
            robustness_graph_data = [];
            coverage_graph_data = [];
            solver_index_data = [];
            
            %% Initialize Solver Log Information
            for (ii=1:1:this.num_solvers)
                SolverInfo(ii).Xlog=[];
                SolverInfo(ii).Xbest=[];
                SolverInfo(ii).Valbest=[];
            end
            
            search_space_dim = numel(this.Br.epsgridsize);
            %search_space_dim is used to estimate the number of initial points
            
            total_nb_sim = 0; % current total number of simulations
                        
            round_count=1;
            TotCompTime = tic;            
            
            
            %%%%%% Falsification Loop %%%%%%%%%
            call_count = 1;
            while call_count<=this.nb_solver_calls
                %%
                if (call_count>1 && solver_index==3)
	              solver_index = 1; %skip calling GNM the second time
                end
                eval_lim = this.max_obj_eval(1,solver_index +1);
                if (eval_lim <= 0)
                  solver_index = solver_index + 1;
                  if (solver_index>this.num_solvers)
                    solver_index = 1;
                  end
                  continue;
                end
                
                
                %% Make a working copy of the original breach set object
                CBS = this.Br.copy();
                
                %% start counting computation time for each solver
                timervar_solver = tic;                                
                
                time_lim = this.solver_time(1,solver_index +1); %100; %500;
                fprintf(1, '\n Max eval number is %d \n',eval_lim);
                fprintf(this.OutFileID, '\n Max eval number is %d \n',eval_lim);  
                
                
                %% Initialize the falsification problem 
%                 if (solver_index==1)
%                     CBS.SetParamRanges([pevts pbranching], [0.001 0.999]);
%                 end
                if isempty(this.Pbs)
                    falsif_pb = FalsificationProblem(CBS,this.R,this.params,this.ranges); 
                 else
                    falsif_pb = this.Pbs.copy();
                end
                
                %% Set parameters common to all solvers
                falsif_pb.StopAtFalse = 1;
                %falsif_pb.max_time = time_lim;
                falsif_pb.max_obj_eval = eval_lim;    
                
                fprintf(1, '\n re_init_strategy %d \n', re_init_strategy);
                nbinitsamples=1;
                switch re_init_strategy
                  case 0
                     nbinitsamples=this.re_init_num_rand; 
                  case 1
                     nbinitsamples=this.re_init_num_xlog;
                  case 2
                     nbinitsamples=this.re_init_num_xbest;
                  otherwise
                     error('Error in reinitialisation strategy choice');
                end
                            
                %% Call the current solver
                switch solver_index
                    
                    case 0 % quasi-random sampling                     
                        fprintf(1,'\n *** Running QuasiRandom');
                        fprintf(this.OutFileID,'\n *** Running QuasiRandom');
                        
                        %%Thao removed quasi-random
                        %CBS.QuasiRandomSample(this.max_obj_eval(1,solver_index+1));
                        
                        %% Set initial points
                        ip = CBS.VaryingParamList;
                        var = CBS.P.ParamList(1,ip); %check these are actually the variables we want
                        CBS.SampleDomain(var,eval_lim,'rand'); %default sampling is pseudo random                      
                        
                        
                        %% Call this solver by evaluating sampled points
                        falsif_pb.setup_init();
                        falsif_pb.solve();
                        
                        %% Xlog contains sampled points
                        new_pts = CBS.GetParam(falsif_pb.params);
                        
                   %%%%%%%%%
                   %%%%%%%%%
                    case 1 % CMAES
                        fprintf(1,'\n **** Running CMAES\n');
                        fprintf(this.OutFileID,'\n **** Running CMAES\n');           
                        
                        falsif_pb.setup_solver('cmaes');
                        
                        %% Set solver-specific parameters
                        falsif_pb.solver_options.SaveVariables = 'off';
                        falsif_pb.solver_options.MaxFunEvals=this.max_obj_eval(1,solver_index +1);
                        %falsif_pb.solver_options.StopOnStagnation = 'off';
                        %falsif_pb.solver_options.FunctionTolerance = 1e-12;
                        %falsif_pb.solver_options.OptimalityTolerance = 1e-20;
                        %falsif_pb.solver_options.TolFun = 1e-16;
                        %falsif_pb.solver_options.Restarts = 3;
                        
                        %% Set initial points
                        if (call_count>1)
%                             if (nbinitsamples < search_space_dim)
%                                 nbinitsamples = search_space_dim;
%                             end
                            
                            x0=this.InitSolver(nbinitsamples,solver_index,this.num_solvers,...
                                SolverInfo,re_init_strategy,this.re_init_num_xbest);
                            
                            if (re_init_strategy==0)
                                if (size(x0,2) < search_space_dim)
                                    nbsamples_more = search_space_dim - size(x0,2);
                                    CBS.QuasiRandomSample(nbsamplesPR, 2^10);
                                    x0_more = CBS.GetParam(falsif_pb.params);
                                    x0 = [ x0, x0_more ];
                                end
                            end
                        else
                            nbinitsamples=this.re_init_num_rand;
                            if (nbinitsamples < search_space_dim)
                                nbinitsamples = search_space_dim;
                            end
                            CBS.QuasiRandomSample(nbinitsamples, 2^10);
                            x0 = CBS.GetParam(falsif_pb.params);
                        end
                        fprintf(1, '\n nb x0: %d \n', size(x0, 2));
                        if (~isempty(x0))
                          falsif_pb.x0 = x0';
                        end
                        
                        %% Call this solver
                        falsif_pb.solve();
                        
                        
                    %%%%%%%%%%
                    %%%%%%%%%%
                    case 2 %Simulated Annealing
                        fprintf(1,'\n *** Running Simulated Annealing\n');
                        fprintf(this.OutFileID,'\n *** Running Simulated Annealing\n');
                        
                        falsif_pb.setup_solver('simulannealbnd');
                        
                        %% Set initial points
                        % this.re_init_strategy=0 to pick randomly from the whole space
                        % this.re_init_strategy=1 to pick randomly from xlog
                        % this.re_init_strategy=2 to pick randomly from xbest
                        if (call_count>1)
                           re_init_strategySA = 2; %always use one xbest
                           nbinitsamples=1; %cannot wotk with population of points
                           x0=this.InitSolver(nbinitsamples,solver_index,this.num_solvers,...
                                   SolverInfo,re_init_strategySA,this.re_init_num_xbest);                
                           
                        else
                           nbinitsamples=1;
                           CBS.QuasiRandomSample(nbinitsamples, 2^10);
                           x0 = CBS.GetParam(falsif_pb.params);
                        end
                        fprintf(1, '\n nb x0: %d \n', size(x0, 2));
                        if (~isempty(x0))
                            falsif_pb.x0 = x0;
                        end
                        
                        %% Set solver-specific parameters
                        falsif_pb.verbose=0;
                        %falsif_pb.solver_options.FunctionTolerance = 1e-3;
                        %falsif_pb.solver_options.OptimalityTolerance = 1e-3;
                        falsif_pb.solver_options.MaxFunEvals=this.max_obj_eval(1,solver_index +1);
                        falsif_pb.solver_options.InitialTemperature = 100;
                        falsif_pb.solver_options.FunctionTolerance = 1e-12;
                        falsif_pb.solver_options.OptimalityTolerance = 1e-20;
                        falsif_pb.solver_options.TolFun = 1e-16;
                        
                        %% Call this solver
                        falsif_pb.solve();
                        
                    
                    %%%%%%
                    %%%%%%
                    case 3 %global_nelder_mead
                        fprintf(1,'\n *** Running Global Nelder Mead');
                        fprintf(this.OutFileID,'\n *** Running Global Nelder Mead');
                        
                        falsif_pb.setup_solver('global_nelder_mead');
                        %falsif_pb.setup_global_nelder_mead();
                        
                        
                        %% Set solver-specific parameters
                        %nb_local_iter = 100;
                        %fprintf(this.OutFileID, '\n Nb of local iterations %d \n', nb_local_iter);
                        %fprintf(1, '\n Nb of local iterations %d \n', nb_local_iter);
                        %falsif_pb.solver_options.nb_local_iter = nb_local_iter;
                        %falsif_pb.solver_options.start_at_trial=2^search_space_dim;
                        %falsif_pb.solver_options.nb_new_trials=2^(search_space_dim/2);
                        %falsif_pb.verbose=0;
                        
                        %% Set initial points
                        if (call_count>1)
                            x0 = this.InitSolver(nbinitsamples,solver_index,...
                                    this.num_solvers,SolverInfo,re_init_strategy,this.re_init_num_xbest);                
                        else
                            nbsamplesPR=this.re_init_num_rand; %200
                            CBS.QuasiRandomSample(nbsamplesPR, 2^37);
                            x0 = CBS.GetParam(falsif_pb.params);
                        end
                        fprintf(1, '\n nb x0: %d \n', size(x0, 2));
                        if (~isempty(x0))
                            falsif_pb.x0 = x0;
                        end
                        
                        %% call the solver
                        falsif_pb.solve();
                        
                    %%%%%%%%    
                    %%%%%%%%
                    otherwise
                        error('solver index does not match')
                end   % end of switch
                
                
                %% Adding new points to xlog for solvers other than random
                if (solver_index~=0)
                    new_pts = falsif_pb.X_log; %col vectors of newly simulated points.
                end
                fprintf(1,'\n Nb of new points added to Xlog = %d', size(new_pts,2));
                                        
                %% Updating visited points in the current CoverageBreachSet Br
                this.Br.AddPoints(new_pts);
                
                %% Get xbest
                new_obj_best = falsif_pb.obj_best;

                
                %% Updating SolverInfo to store xlog, xbest, valbest
                %% updating Xlog of the current solver
                if ( ~isempty( SolverInfo(solver_index+1).Xlog ) )
                    SolverInfo(solver_index+1).Xlog=[SolverInfo(solver_index+1).Xlog, new_pts];
                else
                    SolverInfo(solver_index+1).Xlog=new_pts;
                end
                
                %% get the new Xbest of the current solver
                new_xbest = falsif_pb.x_best;
                
                %% update Xbest if smaller than xbest of current solver
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
                %% end of updating SolverInfo
                
                %% Get execution time
                time_solver = toc(timervar_solver);
                fprintf(this.OutFileID,'\n This solver time = %f seconds',time_solver);
                fprintf(1,'\n This solver time = %f seconds',time_solver);
                
                %% If falsifying trace is found, plot and exit
                trace = falsif_pb.GetBrSet_False();
                if (~isempty(trace))
                    falsified = true;
                    falsi_point = new_xbest;
                    
                    trace_False = falsif_pb.GetFalse(); 
                    % trace_False contains the falsifying trace
                    trace_False.PlotSignals(this.Plot_signal_names);                   
                    %trace.PlotSignals
                    
                    fprintf(this.OutFileID,'\n Exit from Solver %d ', solver_index);
                    comptime = toc(TotCompTime);
                    fprintf(this.OutFileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
                    %disp('Falsifier found! Exit normally');
                    error('Falsifier found! Exit normally');
                end
                
                %% update total nb simulations
                total_nb_sim = total_nb_sim+size(new_pts,2); 
                
                
                fprintf(1,'\n Best Robustness Value of this call = %f', new_obj_best);
                fprintf(this.OutFileID,'\n Best Robustness Value of this call = %f', new_obj_best);
                
%                 if (new_obj_best<=0)
%                     fprintf(this.OutFileID,'\n Falsifier Found!');
%                     
%                     comptime = toc(TotCompTime);
%                     fprintf(this.OutFileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
%                     %error('Falisifier found! Exit normally');
%                 end
                
                %% Monitoring robustness
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
                fprintf(this.OutFileID,'\n Best Robustness Value so far = %f', min_robustness);
                
                
                robustness_graph_data=...
                    [robustness_graph_data; [total_nb_sim min_robustness]];
                
                %% Monitoring coverage
                % the coverage graph is monotonic, we check the evolution of coverage
                % for non-increase by this.cov_epsilon
                % recompute current coverage
                disp('\nCurrent coverage');
                current_coverage_value = this.Br.ComputeLogCellOccupancyCoverage
                %current_coverage_value = CBS.ComputeLogCellOccupancyCoverage
                
                %% Update coverage graph data
                coverage_graph_data= ...
                    [coverage_graph_data; [total_nb_sim current_coverage_value]];
                
                %% Update sequence of called solvers
                solver_index_data=[solver_index_data; solver_index];
                
                
                fprintf(1,'\n\n\n\n #Call  SolverID  Robustness  Coverage');
                fprintf(this.OutFileID,'\n\n\n\n #Call  SolverID  Robustness  Coverage');
                fprintf(1,'\nQuasi-random (0), CMA-ES (1), SA (2), GNM (3)');
                fprintf(this.OutFileID,'\nQuasi-random (0), CMA-ES (1), SA (2), GNM (3)');
                for iii  = 1:call_count
                    fprintf(1,'\n %d  %d  %12.8f  %12.8f',iii, solver_index_data(iii,1),...
                        robustness_graph_data(iii,2),coverage_graph_data(iii,2));
                    fprintf(this.OutFileID,'\n %d  %d  %12.8f  %12.8f',iii, solver_index_data(iii,1),...
                        robustness_graph_data(iii,2),coverage_graph_data(iii,2));
                end
                
                %% Check local optima
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
                        fprintf(this.OutFileID,'\n Coverage stagnant');
                    else
                        stagnant_count=stagnant_count+1;
                    end
                end
                
                % memorizing the previous optimizer
                prev_solver_index = solver_index;
                
                fprintf(this.OutFileID,'\n stagnant_count = %d', stagnant_count);
                fprintf(this.OutFileID,'\n rob_stagnant = %d', rob_stagnant);
                fprintf(this.OutFileID,'\n cov_monitoring_length = %d', cov_monitoring_length);
                
                local_optimum_stuck=(stagnant_count>=cov_monitoring_length) && rob_stagnant;
                fprintf(1, '\n local_optimum_stuck: %d \n', local_optimum_stuck);
                
                %% Decide next solver based on coverage and robustness evolution
                if (~local_optimum_stuck)
                    cov_monitoring_length=this.cov_monitoring_win;
                    PR_duration=0;
                    
                    if (prev_solver_index==0)
                        re_init_strategy = 0; %pick from xlog, if previously random
                    else
                        re_init_strategy = this.re_init_strategy;
                    end
                    
                    solver_index = prev_solver_index + 1;
                    
                    if (call_count>1 && solver_index==3)
	                  solver_index=1; %skip calling GNM the second time
                    end
                    
                    %% If end of the current round
                    % check if random sampling is needed
                    if (solver_index>(this.num_solvers-1))
                        fprintf(1,'\n\n*******\n #%d round(s) of solver calls done', round_count);
                        fprintf(this.OutFileID,'\n #%d round(s) of solver calls done', round_count);
                        solver_index = 1;
                        round_count = round_count + 1;
                        
                        if rob_stagnant
                            re_init_strategy = 0
                        else
                            if rob_improved
                                re_init_strategy = 2
                            else
                                re_init_strategy = 1
                            end
                        end
                    end %end if (solver_index>(this.num_solvers-1))
                    
                else %if local optima stuck
                    solver_index=0; %use random sampling to increase coverage
                    PR_duration=PR_duration+1; % PR_duration is set to 0 if out of local optimum
                    cov_monitoring_length=PR_duration;
                end
                
                fprintf(1,'\n Solver call %d done', call_count);
                fprintf(this.OutFileID,'\n Solver call %d done', call_count);
                
                %%
                call_count = call_count + 1;
                
            end % end of for-loop call_count
            
            %% Report results
            comptime = toc(TotCompTime);
            fprintf(this.OutFileID,'\n Exit! TOTAL Computation time = %f seconds',comptime );
            fprintf(1,'\n Exit! TOTAL Computation time = %f seconds \n',comptime );
            figure('Name','Coverage');
            plot(coverage_graph_data(:,2));
            figure('Name','Robustness');
            plot(robustness_graph_data(:,2));
            
        end %end function
        
        
    end %%end method
end %end classdef