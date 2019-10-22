close all;
clear all;
clc;
warning('OFF', 'ALL')

addpath('./Functions')
addpath('./ExampleBand-Pass')
addpath('./ExampleLow-Pass')
addpath('./periodic.signals')
addpath('./periodic_6.signals')
addpath('../../../breach-dev')

addpath('./../../../src')
addpath('./../../../breach-dev')
addpath('.')

addpath('../../../wordgen')


%% Initialize Breach
InitBreach('./../../../breach-dev',true);
%InitBreach


%% Setup DeltaSigma model
%init_SDT_lowpass
init_SDT

phi = STL_Formula('notsaturation', 'alw(abs(OutSat[t])<1.73978)'); %1.74 falsified
%phi = STL_Formula('notsaturation', 'alw(OutSat[t]<1.145)');
R = BreachRequirement(phi); 




%% Wordgen generator
num_evt = 50;
sg = var_cp_signal_gen('In1', num_evt+2, 'linear')

%% 
pg = TA_param_gen('In1','/Users/thaodang/Metaheuristics/wordgen/hscc20.json', num_evt);
pg.wordgen_exe = '/Users/thaodang/Metaheuristics/wordgen/wordgen';
sdt_template = '%g[b]%g[c]%g[d]';
num = 3;
while num<num_evt
    num = num +4;
    sdt_template = [sdt_template '%g[a]%g[b]%g[c]%g[d]']; % template for lasso init
end
sdt_template = sdt_template(1:5*num_evt);
pg.set_template_in(sdt_template);
pg.template_in = regexprep(pg.template_in,'\[(\w+)\]', '\[_\]') % erase letters 
%pg
%input('Press ENTER');

%time = linspace(0, 1e-5, 10000);
time = linspace(0, 2e-6, 10000);
S = BreachSignalGen(sg);

%%
B = BP2.copy();
B.SetInputGen(S);
B.SetParamGen(pg);

%%
B.SetParamRanges(pg.params(1:end-3), [0 1]);
%% Testing against frequency
B.SetParam({'time_scale'}, [ 10e-8 ]);
B.SetParam({'beta'}, [ -2 ]);
%B.SetParam({'alpha'}, [ 1 0.5 0 ]);
    %%Passband 0.4e-7 Oui les deux -- 0.5e-7 Oui les deux -- 
    %0.6e-7 discrepance 19 Oui, uni NON -- %0.8e-7 NON les deux
    
    %%Lowpass
    %%0.4e-4;
    
    

params = pg.params(1:end-3);
ranges = repmat([0,1], numel(params),1);
num=1;
B.SetParamRanges(params, ranges);
B.SetTime(time);

%input('Press ENTER');


%% CODE dÁlexandre
% % B.SetTime(time);
% % B.Sim();
% % B.PlotSignals();
% % 
% % R.Eval(B);
% % %%
% % F = BreachSamplesPlot(R); 
% % F.set_y_axis('alpha');
% % F.set_x_axis('time_scale');
% % F.set_z_axis('beta');


% grid size collumn on the range of each input signal
gridsize_vector = [ 0.01  ];
nb_ctr_pts = [ num_evt ];

%%%% Once the above system specifications and falsification options are given,
%%%% the following part of the code need not be modified by the user
MetaObj = MetaFalsify(B, R, params, ranges);

%fprintf('\n The falsification problem by metaheuristics is\n ')
%MetaObj.Pbs


% set up a grid on the input ranges, to estimate coverage
MetaObj.GridSetUp(gridsize_vector,nb_ctr_pts);        


%% Start the falsification process
%%%[r,falsified,total_nb_sim,falsi_point] = MetaObj.MetaCall();

%%% Set up falsification options

    %%%% Search Monitoring Parameters 
    %% cov_epsilon = input('Specify coverage increase threshold : '); 
    MetaObj.cov_epsilon = 1e-5; %1e-3;
    %% min robustness decrease in percentage
    MetaObj.rob_epsilon_percent = 1e-3; %0.05;
    %% min robustness stagnant monitoring window
    MetaObj.rob_stagnant_win = 1 
    %% coverage stagnant monitoring window
    MetaObj.cov_monitoring_win = 1;
    
    %%%% Problem-specific computation parameters
    %%% Options for picking initial conditions
    MetaObj.re_init_strategy = 2 %2; %1; 
    % re_init_strategy=0 to pick randomly from the whole space
    % re_init_strategy=1 to pick randomly from xlog
    % re_init_strategy=2 to pick randomly from xbest
            
    % re_init_num_xbest: window of choice from xbest, for picking initial point         
    MetaObj.re_init_num_xbest = 10;

    % num_solvers=nb of solvers %%other than pseudorandom sampling
    % TODO add solver_list, and init num_solver as numel(solver_list)
    MetaObj.num_solvers=4; 
    
    %% limit on nb of solver calls
    MetaObj.nb_solver_calls = 10; %30;
    
    MetaObj.start_solver_index = 2;  %PR 0, cmaes 1, SA 2, GNM 3 
    MetaObj.solver_time =  [200 100 100 100];
    MetaObj.max_obj_eval = [200 200 200 200];
    MetaObj.seed = 100;
          
    
    
% fprintf('\n The falsification problem by metaheuristics is\n ')
% MetaObj

%%%% Run the falsification
MetaObj.MetaCall();

%MetaObj.MetaSetupRun(Sys, phi)
%MetaObj.MetaSetupRun(MetaObj.Br, phi)


%% Plotting Log
% Rpb= pb.GetLog();
% Fpb = BreachSamplesPlot(Rpb); 
% Fpb.set_y_axis('notsaturation');





