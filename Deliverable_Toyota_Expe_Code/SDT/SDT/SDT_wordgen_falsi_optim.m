close all;
clear all;
clc;
warning('OFF', 'ALL')

%% Setup DeltaSigma model
init_SDT

%% Time and requirements
time = 0:1e-10:1e-6;
% STL_ReadFile('SDT_req.stl');
% R =  BreachRequirement(notsat, [], per);
% R.SetParam('sat_val', 0.1); % just maximize that

%% Wordgen generator
addpath('/Users/thaodang/Metaheuristics/wordgen');
addpath('/Users/thaodang/Metaheuristics/src');
num_evt = 70;
sg = TA_signal_gen('In1','cycle_8_12.prism',{'a','b','c','d'}, num_evt, 'linear');
S = BreachSignalGen(sg);
S.SetParam({'In1_a_val','In1_b_val','In1_c_val','In1_d_val'}, [0 1 2 1]);


%% Add input to model 
Bta = BP2.copy();
Bta.SetInputGen(S);
Bta.SetTime(time);
ts = 1e-8;
Bta.SetParam('time_scale', ts, true);
params = sg.params(1:num_evt);
ranges = repmat([0.0001,0.9999], numel(params),1);
Bta.SetParamRanges(params, ranges);
%Bta.SetupDiskCaching();

%Rwg = BreachRequirement(notsat, {}, per); 
formuleSt = 'alw(abs(OutSat[t])<2.325)';                        
phi = STL_Formula('notsaturation', formuleSt);
%phi = STL_Formula('notsaturation', 'alw(OutSat[t]<1.145)');
R = BreachRequirement(phi); 

%pb1 = FalsificationProblem(Bta, R);
%pbwg = FalsificationProblem(Bwg, Rwg, params_evt, ranges);

% grid size collumn on the range of each var param
nb_varying_params = size(Bta.VaryingParamList(),2);
gridnb_vector = [];
for ii = 1:nb_varying_params
   gridnb_vector = [ gridnb_vector 10  ];
end


%%%% Once the above system specifications and falsification options are given,
%%%% the following part of the code need not be modified by the user
MetaObj = MetaFalsify(Bta, R, params, ranges);
%MetaObj = MetaFalsify(Bwg, R, pbwg);


% fprintf('\n The falsification problem by metaheuristics is\n ')
% MetaObj.Pbs

% set up a grid on the input ranges, to estimate coverage
MetaObj.GridNbSetUp(gridnb_vector);        


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
    MetaObj.cov_monitoring_win = 2;
    
    %%%% Problem-specific computation parameters
    %%% Options for picking initial conditions
    MetaObj.re_init_strategy = 2;  
    % re_init_strategy=0 to pick randomly from the whole space
    % re_init_strategy=1 to pick randomly from xlog
    % re_init_strategy=2 to pick randomly from xbest
    % re_init_strategy=3 to pick probilistically from xlog
    % re_init_strategy=4 to pick probilistically from xbest
    % re_init_strategy=5 to pick randomly from xbest of a random solver
    
    MetaObj.re_init_num_xbest = 20;  
    MetaObj.re_init_num_xlog = 200;  
    MetaObj.re_init_num_rand = 200; 
    MetaObj.re_init_num_xprobbest = 20; 
    MetaObj.re_init_num_xproblog = 20;
    
    % num_solvers=nb of solvers %%other than pseudorandom sampling
    % TODO add solver_list, and init num_solver as numel(solver_list)
    MetaObj.num_solvers = 5; 
    
    %% limit on nb of solver calls
    MetaObj.nb_solver_calls = 1; 
    
    %PR 0, cmaes 1, SA 2, GNMLausen 3, GNM 4
    MetaObj.start_solver_index = 4;  
    MetaObj.solver_time =  [100 100 100 100 100];
    MetaObj.max_obj_eval = [10000 10000 100 100 10000];
    MetaObj.seed = 1;
          
Plot_signal_names = {'In1','OutSat'};;
MetaObj.Plot_signal_names = Plot_signal_names;
    
% fprintf('\n The falsification problem by metaheuristics is\n ')
% MetaObj
% Open file to save intermediate results
fileID = fopen('Meta_v32_s1_GNM.txt','w');
MetaObj.OutFileID = fileID;

fprintf(1,'\n STL_Formula %s', formuleSt);
fprintf(fileID,'\n STL_Formula %s', formuleSt);
fprintf(1, '\n Model name is %s \n', model_name);
fprintf(fileID, '\n Model name is %s \n', model_name);

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
