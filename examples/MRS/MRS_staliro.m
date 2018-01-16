clc;
clear;
warning('off', 'ALL');
model='toy_model_NO1';
load_system(model);
init_cond = []

input_range = [0 100;0 100;0 100;0 100;0 100;0 100;0 100;0 100;-5 5]

cp_array = [4 4 4 4 4 4 4 4 4]

phi = '[]_[0.1,10](predi1)))'

i=1;
preds(i).str='predi1';
preds(i).A = [-1 0];
preds(i).b = [8]';

time = 10

opt = staliro_options()

% opt.optimization_solver='SA_Taliro';
% opt.ode_solver='default';
% opt.falsification=10;
% opt.interpolationtype={'pchip'};
% opt.black_box=0;
% opt.runs=10;
% opt.n_tests=1000;
% opt.verbosity=0;
% opt.SampTime=0.001024;
% opt.ants_number=30;
% opt.spec_space='Y';
% opt.loc_traj='none';
% opt.ga_cycles=15;
% opt.dispinfo=1;
% opt.taliro_metric='none';
% opt.map2line=1;
% opt.rob_scale=100;
% opt.taliro='dp_taliro';
% opt.hasim_params=[1 0 0 0];
% opt.cross_entropy_num_subdivs=25;
% opt.cross_entropy_num_samples_per_iteration=100;
% opt.cross_entropy_num_iteration=10;

opt.black_box = 0;
opt.SampTime = 0.001024;
opt.optimization_solver =  'SA_Taliro'
opt.ode_solver = get_param(model, 'SolverName')
opt.spec_space = 'Y';
opt.interpolationtype={'pconst'};
opt.runs = 1;
opt.seed = 2016;  % for repetability
opt.n_workers = 1;
opt.optim_params.n_tests = 3000; % number of tests
disp('Running S-TaLiRo with chosen solver ...')



disp(' ')
disp('Running S-TaLiRo ')

tic
results{1} = staliro(model,init_cond,input_range,cp_array,phi,preds,time,opt);
results{1}.time = toc;

opt.optim_params.n_tests = 10000; % number of tests
cp_array = [2 2 2 2 2 2 2 2 2];
tic
results{2} = staliro(model,init_cond,input_range,cp_array,phi,preds,time,opt);
results{2}.time = toc;
% disp(' ')
% display(['Minimum Robustness found in Run 1 = ',num2str(results.run(1).bestRob)])
% display(['Minimum Robustness found in Run 2 = ',num2str(results.run(2).bestRob)])
% display(['Minimum Robustness found in Run 3 = ',num2str(results.run(3).bestRob)])
% display(['Minimum Robustness found in Run 4 = ',num2str(results.run(4).bestRob)])
% display(['Minimum Robustness found in Run 5 = ',num2str(results.run(5).bestRob)])
% display(['Minimum Robustness found in Run 6 = ',num2str(results.run(6).bestRob)])
% display(['Minimum Robustness found in Run 7 = ',num2str(results.run(7).bestRob)])
% display(['Minimum Robustness found in Run 8 = ',num2str(results.run(8).bestRob)])
% display(['Minimum Robustness found in Run 9 = ',num2str(results.run(9).bestRob)])
% display(['Minimum Robustness found in Run 10 = ',num2str(results.run(10).bestRob)])
% 
% [T1,XT1,YT1,IT1] = SimSimulinkMdl(model,init_cond,input_range,cp_array,results.run(1).bestSample,time,opt);
% [T2,XT2,YT2,IT2] = SimSimulinkMdl(model,init_cond,input_range,cp_array,results.run(2).bestSample,time,opt);
% [T3,XT3,YT3,IT3] = SimSimulinkMdl(model,init_cond,input_range,cp_array,results.run(3).bestSample,time,opt);
% [T4,XT4,YT4,IT4] = SimSimulinkMdl(model,init_cond,input_range,cp_array,results.run(4).bestSample,time,opt);
% [T5,XT5,YT5,IT5] = SimSimulinkMdl(model,init_cond,input_range,cp_array,results.run(5).bestSample,time,opt);
% [T6,XT6,YT6,IT6] = SimSimulinkMdl(model,init_cond,input_range,cp_array,results.run(6).bestSample,time,opt);
% [T7,XT7,YT7,IT7] = SimSimulinkMdl(model,init_cond,input_range,cp_array,results.run(7).bestSample,time,opt);
% [T8,XT8,YT8,IT8] = SimSimulinkMdl(model,init_cond,input_range,cp_array,results.run(8).bestSample,time,opt);
% [T9,XT9,YT9,IT9] = SimSimulinkMdl(model,init_cond,input_range,cp_array,results.run(9).bestSample,time,opt);
% [T10,XT10,YT10,IT10] = SimSimulinkMdl(model,init_cond,input_range,cp_array,results.run(10).bestSample,time,opt);
% 
% disp(' ')
% disp('Displaying Simulink model for visualization. ')