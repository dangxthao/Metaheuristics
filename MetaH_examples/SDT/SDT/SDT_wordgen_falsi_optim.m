close all;
clear all;
clc;
warning('OFF', 'ALL')

addpath('./Functions')
addpath('./ExampleBand-Pass')
addpath('./ExampleLow-Pass')
addpath('./periodic.signals')
addpath('../../../breach-dev')

addpath('../../../supp_code')
addpath('../../../src')
addpath('../../../breach-dev')
addpath('.')

InitBreach


%% Setup DeltaSigma model
init_SDT
phi = STL_Formula('notsaturation', 'alw(OutSat[t]<2)');
R = BreachRequirement(phi); 

%% Wordgen generator

addpath('/Users/thaodang/Metaheuristics/wordgen');
num_evt = 50;
sg = var_cp_signal_gen('In1', num_evt+2, 'linear');

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
pg.template_in = regexprep(pg.template_in,'\[(\w+)\]', '\[_\]'); % erase letters 

%pg

% TA_file: '../../../wordgen/hscc20.json'
%       num_events: 50
%      wordgen_exe: '../../../wordgen/wordgen'
%             poly: 5
%      template_in: '%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]%g[_]'
%     template_out: '%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g'
%          val_map: [5×1 containers.Map]
%           p0_out: [101×1 double]
%           params: {1×53 cell}
%           domain: [1×53 BreachDomain]
%       domain_out: [1×101 BreachDomain]
%       params_out: {1×101 cell}
%               p0: [53×1 double]

pg.params
% pg.domain
% 
% pg.params_out
% pg.domain_out

%input('Press ENTER');

%%

time = linspace(0, 1e-5, 10000);
S = BreachSignalGen(sg);

S
%input('Press ENTER');

%%
B = BP2.copy();
B.SetInputGen(S);
B.SetParamGen(pg);

%%
%% Testing against frequency
B.SetParam({'time_scale'}, [ 3e-8 ]);
B.SetParamRanges(pg.params(1:end-3), [0 1]);

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

%%CODE de Thao
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




% %%% Problem-specific computation parameters
  
SDT_seed = 100;

SDT_re_init_strategy = 2; %1;
SDT_solver_time =  [1000 2000 2000 2000];
SDT_max_obj_eval = [1000 2000 2000 2000];
SDT_nb_solver_calls = 1; %1 %30
SDT_start_solver_index = 2;  %PR 0, cmaes 1, SA 2, GNM 3 


%%%%%% Assigning to global computation parameters
nb_solver_calls = SDT_nb_solver_calls
start_solver_index = SDT_start_solver_index;
re_init_strategy = SDT_re_init_strategy;
solver_time =  SDT_solver_time;
max_obj_eval = SDT_max_obj_eval;
seed = SDT_seed;
          

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
gridsize_vector = [ 0.01  ];
nb_ctr_pts = [ 50 ];

%%%% Once the above system specifications and falsification options are given,
%%%% the following part of the code need not be modified by the user
%MetaObj = MetaFalsify(B_ripple, R, Pb);
MetaObj = MetaFalsify(B, R, Pb);

fprintf('\n The falsification problem by metaheuristics is\n ')
Pb

% % specify the simulation time
% MetaObj.SimTimeSetUp(simTime);
% 
% % specify the class of input signals
% MetaObj.InputSignalSetUp(input_signal_names,signal_gen_method,nb_ctr_pts,input_ranges);
% 
% % specify the property to falsify
% MetaObj.STLFormulaSetUp(phi);

% set up a grid on the input ranges, to estimate coverage
%MetaObj.GridSetUp(gridsize_vector,nb_ctr_pts);        


%% Start the falsification process
%%%[r,falsified,total_nb_sim,falsi_point] = MetaObj.MetaCall();

%%% Set up falsification options

    %%%% Search Monitoring Parameters 
    %% cov_epsilon = input('Specify coverage increase threshold : '); 
    MetaObj.cov_epsilon = 1e-5; %1e-3;
    %% min robustness decrease in percentage
    MetaObj.rob_epsilon_percent = 1e-2; %0.05;
    %% min robustness stagnant monitoring window
    MetaObj.rob_stagnant_win = 1 
    %% coverage stagnant monitoring window
    MetaObj.cov_monitoring_win = 1;

    %%% Options for picking initial conditions
    MetaObj.re_init_strategy = re_init_strategy; %2; 
    % re_init_strategy=0 to pick randomly from the whole space
    % re_init_strategy=1 to pick randomly from xlog
    % re_init_strategy=2 to pick randomly from xbest
            
    % re_init_num_xbest: window of choice from xbest, for picking initial point         
    MetaObj.re_init_num_xbest = 200;

    % num_solvers=nb of solvers %%other than pseudorandom sampling
    % TODO add solver_list, and init num_solver as numel(solver_list)
    MetaObj.num_solvers=4; 
    
    %% limit on nb of solver calls
    MetaObj.nb_solver_calls = nb_solver_calls; %1 %30
    
    MetaObj.start_solver_index = start_solver_index; %3; %1; %PR 0, cmaes 1, SA 2, GNM 3 
    
    MetaObj.solver_time =  solver_time;
    MetaObj.max_obj_eval = max_obj_eval;
    MetaObj.seed = seed;
    
    
fprintf('\n The falsification problem by metaheuristics is\n ')
MetaObj

%%%% Run the falsification
MetaObj.MetaCall();

%MetaObj.MetaSetupRun(Sys, phi)
%MetaObj.MetaSetupRun(MetaObj.Br, phi)


%% Plotting Log
%R = Pb.GetLog();
%F = BreachSamplesPlot(R);






