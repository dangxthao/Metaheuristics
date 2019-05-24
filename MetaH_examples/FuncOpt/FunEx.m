clear all;
init_instance;


%% plotting the function
Bgrid = B_ripple.copy();
Bgrid.GridSample(50);
Rgrid = BreachRequirement('y[t]>-10');
Rgrid.Eval(Bgrid);

%%
% x1 = Rgrid.GetParam('x1')';
% x2 = Rgrid.GetParam('x2')';
% v = Rgrid.traces_vals';
% [x1q,x2q] = meshgrid(0:.01:1, 0:.01:1);
% vq = griddata(x1,x2,v,x1q,x2q);
% surf(x1q,x2q,vq)

%% Falsification problem 
R = BreachRequirement('y[t]>-200');
B = B_ackley2.copy();
%Pb = FalsificationProblem(B_ripple,R);
Pb = FalsificationProblem(B_ackley2,R);
Pb.StopAtFalse = 1;
% Pb
% 
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
    MetaObj.nb_solver_calls = 30  %1 %30
    
    MetaObj.start_solver_index = 2; %3; %1; %PR 0, cmaes 1, SA 2, GNM 3 
    
    MetaObj.solver_time =  [500  1000 1000 2000];
    MetaObj.max_obj_eval = [1000 2000 2000 1000];
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

