addpath('/Users/dang/Metaheuristics/breach-dev')

%addpath('/Users/dang/Metaheuristics/src')
addpath('.')

addpath('/Users/dang/Metaheuristics/wordgen')
InitBreach('/Users/dang/Metaheuristics/breach-dev',true);

%% TA based signal generator setup 
%
num_evt=25;
init_TA_signal_gen;


%%  Checking reachable labels
STL_ReadFile('Autotrans_req.stl');

%% 

S2 = S0.copy();
mdl = 'Autotrans_wordgen';
Ba = BreachSimulinkSystem(mdl);
Ba.SetTime(time);
Ba.SetInputGen(S2);
Ba.SetParamRanges([pevts pbranching], [0.01 0.99]);
% Ba.Sim();


%% 
R = BreachRequirement(never_gear3_and_speed_low);
falsif_pb = FalsificationProblem(Ba, R);
nb_varying_params = size(Ba.VaryingParamList(),2)

% falsif_pb.solver_options.num_corners = 100;
% falsif_pb.solver_options.num_quasi_rand_samples = 100;
% falsif_pb.max_obj_eval = 1000;
%falsif_pb.SetupDiskCaching();

%falsif_pb.solve();

%% Initial Counter-example
%%BFalse = falsif_pb.BrSet_False;
%BFalse = falsif_pb.GetFalse();;

%% Fix Specification
% param_pb = ParamSynthProblem(BFalse, never_gear3_and_speed_low, 'v_low', [0 30]);
% param_pb.solver_options.monotony = -1;
% param_pb.solve();


%% Requirement mining: Iterate 
%mining_pb = ReqMiningProblem(param_pb, falsif_pb);
%mining_pb.solve();



% grid size collumn on the range of each var param
gridsize_vector = [];
nb_ctr_pts = [ nb_varying_params ];
for ii = 1:nb_varying_params
   gridsize_vector = [ gridsize_vector 100  ];
end

%%%% Once the above system specifications and falsification options are given,
%%%% the following part of the code need not be modified by the user
%MetaObj = MetaFalsify(B, R, params, ranges);
MetaObj = MetaFalsify(Ba, R, falsif_pb);


% fprintf('\n The falsification problem by metaheuristics is\n ')
% MetaObj.Pbs


% set up a grid on the input ranges, to estimate coverage
% in this example time points ar
MetaObj.GridSetUp(gridsize_vector,nb_ctr_pts,true);        


%% Start the falsification process
%%%[r,falsified,total_nb_sim,falsi_point] = MetaObj.MetaCall();

%%% Set up falsification options

    %%%% Search Monitoring Parameters 
    %% cov_epsilon = input('Specify coverage increase threshold : '); 
    MetaObj.cov_epsilon = 1e-3; %1e-3;
    %% min robustness decrease in percentage
    MetaObj.rob_epsilon_percent = 1e-2; %0.05;
    %% min robustness stagnant monitoring window
    MetaObj.rob_stagnant_win = 1 
    %% coverage stagnant monitoring window
    MetaObj.cov_monitoring_win = 1;
    
    %%%% Problem-specific computation parameters
    %%% Options for picking initial conditions
    MetaObj.re_init_strategy = 2; %2; %1; 
    % re_init_strategy=0 to pick randomly from the whole space
    % re_init_strategy=1 to pick randomly from xlog
    % re_init_strategy=2 to pick randomly from xbest
            
    % re_init_num_xbest: window of choice from xbest, for picking initial point         
    MetaObj.re_init_num_xbest = 20; %10;

    % num_solvers=nb of solvers %%other than pseudorandom sampling
    % TODO add solver_list, and init num_solver as numel(solver_list)
    MetaObj.num_solvers=4; 
    
    %% limit on nb of solver calls
    MetaObj.nb_solver_calls = 1; %30;
    
    MetaObj.start_solver_index = 1;  %PR 0, cmaes 1, SA 2, GNM 3 
    MetaObj.solver_time =  [200 100 100 100];
    MetaObj.max_obj_eval = [100 10 200 20];
    MetaObj.seed = 100;
          
    
    
% fprintf('\n The falsification problem by metaheuristics is\n ')
% MetaObj
% Open file to save intermediate results
fileID = fopen('OutFalsification.txt','w');
MetaObj.OutFileID = fileID;

%fprintf(1,'\n STL_Formula %', formuleSt);
%fprintf(fileID,'\n STL_Formula %', formuleSt);
%fprintf(1, '\n Model name is %s \n', model_name);
%fprintf(fileID, '\n Model name is %s \n', model_name);

MetaObj.MetaShortFilePrint(fileID); 

%%%% Run the falsification
MetaObj.MetaCall();

%MetaObj.MetaSetupRun(Sys, phi)
%MetaObj.MetaSetupRun(MetaObj.Br, phi)


%% Plotting Log
% Rpb= pb.GetLog();
% Fpb = BreachSamplesPlot(Rpb); 
% Fpb.set_y_axis('notsaturation');


%% closing output file 
fclose(fileID);