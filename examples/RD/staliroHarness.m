clc;
warning('off', 'ALL');
c = 5;
simTime  = 8;
model='good_for_tabu';
load_system(model);

input_range = [0 100]

cp_array = [2]

phi = '[]_[0.1,10](predi)))'

i=1;
preds(i).str='predi';
preds(i).A = [-1];
preds(i).b = [0.001];

time = 10

opt = staliro_options()
%opt.parameterEstimation = 1;
opt.black_box = 0;
opt.SampTime = 0.02;
opt.optimization_solver =  'SA_Taliro';
opt.ode_solver = 'ode15s';
opt.ode_solver = get_param(model, 'SolverName');
opt.spec_space = 'Y';
opt.interpolationtype={'pconst'};
opt.runs = 1;
opt.seed = 2015;  % for repetability
opt.n_workers = 1;
opt.optim_params.n_tests = 4000; % number of tests
disp('Running S-TaLiRo with chosen solver ...')
opt

initial_cond = [];
result_staliro = {};
%%
cp_array = [2];
opt.optim_params.n_tests = 2000;
[result_staliro{end+1}.results, result_staliro{end+1}.history] = staliro(model,initial_cond,input_range,cp_array,phi,preds,simTime,opt);

for i = 2:3
    opt.optim_params.n_tests = 4000;
    cp_array = [2^i];
    [result_staliro{i}.results, result_staliro{i}.history] = staliro(model,initial_cond,input_range,cp_array,phi,preds,simTime,opt);
    %bestSamp = result_staliro{i}.run(1).bestSample(:,1);
end
%%
opt.varying_cp_times = 2;
cp_array = [4];
[result_staliro{end+1}.results, result_staliro{end+1}.history] = staliro(model,initial_cond,input_range,cp_array,phi,preds,simTime,opt);

%%
%     [T1, XT1, YT1, IT1] = SimSimulinkMdl(model,initial_cond,input_range,cp_array,bestSamp,simTime,opt);
%     figure
%     subplot(2,1,1)
%     hold on
%     plot(IT1(:,1), IT1(:,2));
%     subplot(2,1,2)
%     plot(T1, YT1(:,1));

