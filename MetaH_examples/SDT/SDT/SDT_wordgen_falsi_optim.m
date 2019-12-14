close all;
clear all;
clc;
warning('OFF', 'ALL')

%% Setup DeltaSigma model
init_SDT

%% Wordgen generator
addpath('/Users/thaodang/Metaheuristics/wordgen');
num_evt = 70;
sg = var_cp_signal_gen('In1', num_evt+1, 'linear');

pg = TA_param_gen('In1','cycle_8_12.prism', num_evt);
pg.wordgen_exe = '/Users/thaodang/Metaheuristics/wordgen/wordgen';
sdt_template = '%g[b]%g[c]%g[d]';
num = 3;
while num<num_evt
    num = num +4;
    sdt_template = [sdt_template '%g[a]%g[b]%g[c]%g[d]']; % template for lasso init
end

sdt_template = sdt_template(1:5*num_evt);
pg.set_template_in(sdt_template);
pg.template_in = regexprep(pg.template_in,'\[(\w+)\]', '\[0.5\]'); % erase letters 

params_evt = pg.params(1:end-3);
ranges = repmat([0,1], numel(params_evt),1);
S = BreachSignalGen(sg);


%% Time and requirements
S = BreachSignalGen(sg);
time = 0:1e-10:1.5e-6;
ts = .8e-8;
STL_ReadFile('SDT_req.stl');


%% Falsification Problem
Bwg = BP2.copy();
Bwg.SetInputGen(S);
Bwg.SetParamGen(pg);
Bwg.SetParam('time_scale', ts);
Bwg.SetTime(time);

%Rwg = BreachRequirement(notsat, {}, per); 
formuleSt = 'alw(abs(OutSat[t])<1.73977)';                        
phi = STL_Formula('notsaturation', formuleSt);
%phi = STL_Formula('notsaturation', 'alw(OutSat[t]<1.145)');
R = BreachRequirement(phi); 

%pbwg = FalsificationProblem(Bwg, Rwg, params_evt, ranges);

% grid size collumn on the range of each var param
nb_varying_params = size(Bwg.VaryingParamList(),2);
gridnb_vector = [];
for ii = 1:nb_varying_params
   gridnb_vector = [ gridnb_vector 10  ];
end


%%%% Once the above system specifications and falsification options are given,
%%%% the following part of the code need not be modified by the user
MetaObj = MetaFalsify(Bwg, R, params_evt, ranges);
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
            
    MetaObj.re_init_num_xbest = 10;  
    MetaObj.re_init_num_xlog = 200;  
    MetaObj.re_init_num_rand = 100; 

    % num_solvers=nb of solvers %%other than pseudorandom sampling
    % TODO add solver_list, and init num_solver as numel(solver_list)
    MetaObj.num_solvers = 4; 
    
    %% limit on nb of solver calls
    MetaObj.nb_solver_calls = 1; 
    
    MetaObj.start_solver_index = 3;  %PR 0, cmaes 1, SA 2, GNM 3 
    MetaObj.solver_time =  [100 100 100 100];
    MetaObj.max_obj_eval = [200 500 0 1000];
    MetaObj.seed = 100;
          
Plot_signal_names = {'In1','OutSat'};;
MetaObj.Plot_signal_names = Plot_signal_names;
    
% fprintf('\n The falsification problem by metaheuristics is\n ')
% MetaObj
% Open file to save intermediate results
fileID = fopen('Meta_v1.txt','w');
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
