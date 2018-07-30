% Created by Xiaoqing Jin (xiaoqing.jin@tema.toyota.com)
% Toyota Technical Center 
% July 18  2014

close all
warning('off', 'ALL')
% Initialize the model 
load('expcon.mat')
load('KD_const_coeffs_0624.mat')
load('pexhat_stuff.mat')
load('thr_ff_map.mat')
%%

% I disable all warning messages to make it clear
warning('off','all')
model = 'KD_cl_harness_tomasso';

load_system(model);

%%
disp(' ')
disp('Initial conditions')
init_cond = []

disp(' ')
disp('Input signals:')
input_range = [5.0,45.0;1800, 3000] % input signal range for fuel; engine speed
cp_array = [10,10] % control points for interpolating signal

t_final = 50;  % set simulation time

povershoot = 10;
disp(' ')
disp('The specification:');

i = 1;
preds(i).str = 'testMAP';  % A simple predicate 
preds(i).A = [1];
preds(i).b = povershoot; % the value of the output signal never exceed povershoot

phi = '[]_[1,50]testMAP'; 
disp(' ')
disp('Total Simulation time:')

opt = staliro_options(); % fill all default options
opt.runs = 1; % number of runs
opt.optimization_solver='SA_Taliro'; % Monte Carlo sampling
opt.sa_params.n_tests = 1000; % number of tests for each run
opt.spec_space = 'Y';  % spec is against output signal
opt.n_workers = 1;
opt.seed = 2013;
opt.interpolationtype = {'pconst','pconst'};
opt.falsification = 1; % falsfiying the model



opt
tic
[results, history] = staliro(model,init_cond,input_range,cp_array,phi,...
    preds,t_final,opt);
staliroTtime = toc

%%

% disp(['The best robustness value = ' ...
%     num2str(results.run(results.optRobIndex).bestRob)])
% % Run the simulation using the input value to generate the best robustness
% % value
% [T,XT,YT,IT] = SimSimulinkMdl(model,init_cond,input_range,cp_array,...
%     results.run(results.optRobIndex).bestSample(:,1),t_final,opt);
% 
% 
% figure
% plot(IT(:,1), IT(:,2:end));
% title('Input')
% figure
% plot(T, YT);
% title('Output')

