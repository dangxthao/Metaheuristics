close all;
clear;
clc;
InitBreach;
addpath('C:\Users\xjin\work\SVN repository\mining_tabu\sitar-tool\sitar-v3');
addpath('C:\Users\xjin\work\SVN repository\mining_tabu\sitar-tool\sitar-v3\examples\RefinementWithBreach');
%
% initial the model

model_name = 'good_for_tabu';
c = 5;
sim_time = 10;

MD_base = BreachSimulinkSystem(model_name);
MD_base.SetTime([0 sim_time]);
MD_system = MD_base.copy();

phi = STL_Formula('check', 'alw_[0.1, sim_time] (Out1[t] > -0.001)'); 
phi = set_params(phi, {'sim_time'}, [sim_time]);

time_run = [];
num_sim = [];
falsify = [];

%%
fprintf('non-uniform\n');

cp_num = 2;
MD_input_gen = fixed_cp_signal_gen({'In1'}, cp_num, {'previous'});
MD_system.SetInputGen(BreachSignalGen({MD_input_gen}));
input_param = {};
input_range = [];
for ii = 0:cp_num-1
    input_param{end+1} =  ['In1_u' num2str(ii)];
    input_range = [input_range; 0 100];
end
MD_system.SetParamRanges(input_param, input_range);
breach_problem = FalsificationProblem(MD_system, phi);
breach_problem.max_obj_eval = 2000;
breach_problem.max_time = inf;
%breach_problem.setup_solver('fminsearch');
breach_problem.setup_solver('cmaes');
t = clock;
breach_problem.solve();
time_run=[time_run etime(clock,t)];
num_sim = [num_sim breach_problem.nb_obj_eval];
falsify = [falsify breach_problem.obj_best<0];
%%
% fals_example = sitar_problem.GetBrSet_False;
% fals_example.RunGUI
%%
fprintf('uniform\n');


cp_num = 4;
MD_system_2 = MD_base.copy();
MD_input_gen_2 = var_cp_signal_gen({'In1'}, cp_num, {'previous'});
MD_system_2.SetInputGen(BreachSignalGen({MD_input_gen_2}));
input_param_2 = {};
input_range_2 = [];
for ii = 0:cp_num-1
    input_param_2{end+1} =  ['In1_u' num2str(ii)];
    input_range_2 = [input_range_2; 0 100];
end
input_param_2{end+1} = 'In1_dt0';
input_range_2 = [input_range_2; 1 4];
time_param_2 = {};
time_value = [];
for ii = 1:cp_num-2
    time_param_2{end+1} = ['In1_dt' num2str(ii)];
    time_value = [time_value 2.5];
end
    
MD_system_2.SetParam(time_param_2, time_value);
MD_system_2.SetInputGen(BreachSignalGen({MD_input_gen_2}));
MD_system_2.SetParamRanges(input_param_2, input_range_2);

breach_problem_2 = FalsificationProblem(MD_system_2, phi);
breach_problem_2.max_obj_eval = 4000;
breach_problem_2.max_time = inf;
%breach_problem_2.setup_solver('fminsearch');
breach_problem_2.setup_solver('cmaes');
t = clock;
breach_problem_2.solve();
time_run=[time_run etime(clock,t)];
num_sim = [num_sim breach_problem_2.nb_obj_eval];
falsify = [falsify breach_problem_2.obj_best<0];
%%
fprintf('uniform\n');

cp_num = 4;
MD_system_3 = MD_base.copy();
MD_input_gen_3 = fixed_cp_signal_gen({'In1'}, cp_num, {'previous'});
MD_system_3.SetInputGen(BreachSignalGen({MD_input_gen_3}));
input_param_3 = {};
input_range_3 = [];
for ii = 0:cp_num-1
    input_param_3{end+1} =  ['In1_u' num2str(ii)];
    input_range_3 = [input_range_3; 0 100];
end

MD_system_3.SetInputGen(BreachSignalGen({MD_input_gen_3}));
MD_system_3.SetParamRanges(input_param_3, input_range_3);
breach_problem_3 = FalsificationProblem(MD_system_3, phi);
breach_problem_3.max_obj_eval = 4000;
breach_problem_3.max_time = inf;
%breach_problem_2.setup_solver('fminsearch');
breach_problem_3.setup_solver('cmaes');
t = clock;
breach_problem_3.solve();
time_run=[time_run etime(clock,t)];
num_sim = [num_sim breach_problem_3.nb_obj_eval];
falsify = [falsify breach_problem_3.obj_best<0];

%%
fprintf('uniform\n');

cp_num = 8;
MD_system_4 = MD_base.copy();
MD_input_gen_4 = fixed_cp_signal_gen({'In1'}, cp_num, {'previous'});
MD_system_4.SetInputGen(BreachSignalGen({MD_input_gen_4}));
input_param_4 = {};
input_range_4 = [];
for ii = 0:cp_num-1
    input_param_4{end+1} =  ['In1_u' num2str(ii)];
    input_range_4 = [input_range_4; 0 100];
end

MD_system_4.SetInputGen(BreachSignalGen({MD_input_gen_4}));
MD_system_4.SetParamRanges(input_param_4, input_range_4);
breach_problem_4 = FalsificationProblem(MD_system_4, phi);
breach_problem_4.max_obj_eval = 4000;
breach_problem_4.max_time = inf;
%breach_problem_2.setup_solver('fminsearch');
breach_problem_4.setup_solver('cmaes');
t = clock;
breach_problem_4.solve();
time_run=[time_run etime(clock,t)];
num_sim = [num_sim breach_problem_4.nb_obj_eval];
falsify = [falsify breach_problem_4.obj_best<0];