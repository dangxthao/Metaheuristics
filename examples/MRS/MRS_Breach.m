close all;
clear;
clc;
warning('OFF', 'ALL')
InitBreach;
addpath('C:\Users\xjin\work\SVN repository\mining_tabu\sitar-tool\sitar-v3');
addpath('C:\Users\xjin\work\SVN repository\mining_tabu\sitar-tool\sitar-v3\examples\RefinementWithBreach');
%
% initial the model
sim_time = 10;


%opriona.refine_time_add_space_point_max_num = 3;
model_name = 'toy_model_NO1';


MRS_base = BreachSimulinkSystem(model_name);
MRS_base.SetTime([0 sim_time]);
MRS_system = MRS_base.copy();
phi = STL_Formula('toy_check', 'alw_[0.1, sim_time] (Out1[t] > -8)'); 
phi = set_params(phi, {'sim_time'}, [sim_time]);

time_run = [];
num_sim = [];
falsify = [];
input_str = {};
input_cp = [];
input_intp = {};
for ii = 1:9
    input_str{end+1} = ['In' num2str(ii)];
    input_cp = [input_cp 4];
    input_intp{end+1} = 'previous';
end
MRS_input_gen = fixed_cp_signal_gen(input_str, input_cp,input_intp);
MRS_system.SetInputGen(BreachSignalGen({MRS_input_gen}));
input_param = {};
input_range = [];
for ii = 1:9
    if ii < 9 
        for jj = 0:3
            input_param{end+1} = ['In' num2str(ii) '_u' num2str(jj)];
            input_range = [input_range; 0 100];
        end
    else
        for jj = 0:3
            input_param{end+1} = ['In' num2str(ii) '_u' num2str(jj)];
            input_range = [input_range; -5 5];
        end
    end
end
MRS_system.SetParamRanges(input_param, input_range);

fprintf('non-uniform\n');


breach_problem = FalsificationProblem(MRS_system, phi);
breach_problem.max_obj_eval = 3000;
breach_problem.max_time = inf;
%breach_problem.setup_solver('fminsearch');
breach_problem.setup_solver('cmaes');
t = clock;
breach_problem.solve();
time_run=[time_run etime(clock,t)];
num_sim = [num_sim breach_problem.nb_obj_eval];
falsify = [falsify breach_problem.obj_best<0];
%%

fprintf('uniform\n');   
MRS_system_1 = MRS_base.copy();
MRS_input_gen_1 = fixed_cp_signal_gen(input_str, ones(1, length(input_str))*2,input_intp);
input_param_1 = {};
input_range_1 = [];
for ii = 1:9
    if ii < 9 
        for jj = 0:1
            input_param_1{end+1} = ['In' num2str(ii) '_u' num2str(jj)];
            input_range_1 = [input_range_1; 0 100];
        end
    else
        for jj = 0:1
            input_param_1{end+1} = ['In' num2str(ii) '_u' num2str(jj)];
            input_range_1 = [input_range_1; -5 5];
        end
    end
end
MRS_system_1.SetInputGen(BreachSignalGen({MRS_input_gen_1}));
MRS_system_1.SetParamRanges(input_param_1, input_range_1);
breach_problem_2 = FalsificationProblem(MRS_system_1, phi);
breach_problem_2.max_obj_eval = 10000;
breach_problem_2.max_time = inf;
%breach_problem_2.setup_solver('fminsearch');
breach_problem_2.setup_solver('cmaes');
t = clock;
breach_problem_2.solve();
time_run=[time_run etime(clock,t)];
num_sim = [num_sim breach_problem_2.nb_obj_eval];
falsify = [falsify breach_problem_2.obj_best<0];
