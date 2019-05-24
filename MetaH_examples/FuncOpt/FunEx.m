clear all;
init_instance;


%% plotting the function
% Bgrid = B_ripple.copy();
% Bgrid.GridSample(50);
% Rgrid = BreachRequirement('y[t]>-10');
% Rgrid.Eval(Bgrid);

% x1 = Rgrid.GetParam('x1')';
% x2 = Rgrid.GetParam('x2')';
% v = Rgrid.traces_vals';
% [x1q,x2q] = meshgrid(0:.01:1, 0:.01:1);
% vq = griddata(x1,x2,v,x1q,x2q);
% surf(x1q,x2q,vq)


%% Falsification problem 
R = BreachRequirement('y[t]>-0.003791');
%B = B_ackley2.copy();
%B = B_ackley3.copy(); %%-186.4112, exact -195
%B = B_ackley4.copy(); %% Min found -3.9173, exact ?3.917275
%B = B_beale.copy(); %found 0.00000027, exact 0 at (3,0.5)
%B = B_bohachevskyn1fcn.copy(); %found 0, exact 0
%B = B_booth.copy(); %found 0.00005306, exact 0
%B = B_brentfcn.copy(); %found 0 exact e^(-200)
%B = B_bukinn6fcn.copy(); %found 0.02546057, exact 0
%B = B_crossintrayfcn.copy(); %found -2.0626 min ?2.06261218
%B = B_easomfcn.copy(); %found 1, exact -1 ****** DIFFICULT
%B = B_holdertablefcn.copy(); %found -19.1553 min -19.2085
%B = B_levin13fcn.copy(); %found 0.00000000   min 0
%B = B_TesttubeHolder.copy(); %found -2.0100 min ?10.872300 ****** DIFFICULT
%B = B_Trefethen.copy(); %found  -1.3547 min ?3.30686865 ****** DIFFICULT
%B= B_WWavy.copy(); %found 0.50000000  min 0
B= B_Zettl.copy(); %found ?0.003791  min ?0.003791
        
          
          
Pb = FalsificationProblem(B, R);
Pb.StopAtFalse = 0;


% Pb.max_obj_eval = 50000;
% %Pb.setup_solver('cmaes');
% Pb.setup_solver('simulannealbnd');
% %Pb.setup_global_nelder_mead();
% 
% Pb.solver_options.MaxFunEvals = 1000;
% Pb.solver_options.FunctionTolerance = 1e-12;
% Pb.solver_options.OptimalityTolerance = 1e-20;
% Pb.solver_options.TolFun = 1e-16;
% Pb.solver_options.InitialTemperature = 100;
% Pb.solve();


% grid size collumn on the range of each input signal
gridsize_vector = [ 4; 4 ];
nb_ctr_pts = [ 1; 1 ];

%%%% Once the above system specifications and falsification options are given,
%%%% the following part of the code need not be modified by the user
%MetaObj = MetaFalsify(B_ripple, R, Pb);
MetaObj = MetaFalsify(B, R, Pb);


% % specify the simulation time
% MetaObj.SimTimeSetUp(simTime);
% 
% % specify the class of input signals
% MetaObj.InputSignalSetUp(input_signal_names,signal_gen_method,nb_ctr_pts,input_ranges);
% 
% % specify the property to falsify
% MetaObj.STLFormulaSetUp(phi);

% set up a grid on the input ranges, to estimate coverage
MetaObj.GridSetUp(gridsize_vector,nb_ctr_pts);        


%% Start the falsification process
%%%[r,falsified,total_nb_sim,falsi_point] = MetaObj.MetaCall();

%%% Set up falsification options

    %%%% Search Monitoring Parameters 
    %% cov_epsilon = input('Specify coverage increase threshold : '); 
    MetaObj.cov_epsilon = 1e-3;
    %% min robustness decrease in percentage
    MetaObj.rob_epsilon_percent = 0.05;
    %% min robustness stagnant monitoring window
    MetaObj.rob_stagnant_win = 1 
    %% coverage stagnant monitoring window
    MetaObj.cov_monitoring_win = 1;

    %%% Options for picking initial conditions
    MetaObj.re_init_strategy = 2; %2; 
    % re_init_strategy=0 to pick randomly from the whole space
    % re_init_strategy=1 to pick randomly from xlog
    % re_init_strategy=2 to pick randomly from xbest
            
    % re_init_num_xbest: window of choice from xbest, for picking initial point         
    MetaObj.re_init_num_xbest = 200;

    % num_solvers=nb of solvers %%other than pseudorandom sampling
    % TODO add solver_list, and init num_solver as numel(solver_list)
    MetaObj.num_solvers=4; 
    
    %% limit on nb of solver calls
    MetaObj.nb_solver_calls = 10  %1 %30
    
    MetaObj.start_solver_index = 0; %3; %1; %PR 0, cmaes 1, SA 2, GNM 3 
    
    MetaObj.solver_time =  [1000 1000 100 200];
    MetaObj.max_obj_eval = [1000 2000 200 100];
    MetaObj.seed = 100;
    
    
fprintf('\n The falsification problem by metaheuristics is\n ')
MetaObj

%%%% Run the falsification
MetaObj.MetaCall();

%MetaObj.MetaSetupRun(Sys, phi)
%MetaObj.MetaSetupRun(MetaObj.Br, phi)


%% Plotting Log
%R = Pb.GetLog();
%F = BreachSamplesPlot(R);

