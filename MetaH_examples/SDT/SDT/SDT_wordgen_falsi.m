close all;
clear all;
clc;
warning('OFF', 'ALL')

%% Setup DeltaSigma model
init_SDT
phi = STL_Formula('notsaturation', 'alw(OutSat[t]<2)');
R = BreachRequirement(phi); 

%% Wordgen generator

addpath('../../../wordgen');
num_evt = 60;
sg = var_cp_signal_gen('In1',num_evt+2, 'linear');

%% 
pg = TA_param_gen('In1','../../../wordgen/hscc20.json', num_evt);
pg.wordgen_exe = '../../../wordgen/wordgen';
sdt_template = '%g[b]%g[c]%g[d]';
num = 3;
while num<num_evt
    num = num +4;
    sdt_template = [sdt_template '%g[a]%g[b]%g[c]%g[d]']; % template for lasso init
end
sdt_template = sdt_template(1:5*num_evt);
pg.set_template_in(sdt_template);
pg.template_in = regexprep(pg.template_in,'\[(\w+)\]', '\[_\]'); % erase letters 

S = BreachSignalGen(sg);

%% Testing against timescale 
time = linspace(0,2e-6, 10000);
B = BP2.copy();
B.SetInputGen(S);
B.SetParamGen(pg);
B.SetParam('time_scale', [1e-8 : 5e-11 : 2e-8]);
B.SetTime(time);
B.Sim();
B.PlotSignals();
R.Eval(B);
F = BreachSamplesPlot(R); 

%% Testing against events

Be = BP2.copy();
Be.SetInputGen(S);
Be.SetParamGen(pg);
Be.SetParam('time_scale', 1.1e-8);
Be.SetTime(time);

params = pg.params(1:end-3);
ranges = repmat([0,1], numel(params),1);

Be.SetParamRanges(params, ranges);
Be.SampleDomain(params, 100); % random (pseudo not quasi) sampling of 10
%Be.QuasiRandomSample(10);
R = BreachRequirement(phi); 
R.Eval(Be);
F = BreachSamplesPlot(R); 
F.set_y_axis('notsaturation');

%% Falsification Problem
Bpb = BP2.copy();
Bpb.SetInputGen(S);
Bpb.SetParamGen(pg);
Bpb.SetParam('time_scale', 1.2e-8);
Bpb.SetTime(time);
Rpb = BreachRequirement(phi); 
pb = FalsificationProblem(Bpb, Rpb, params, ranges);

pb.max_obj_eval=1000;
pb.solver_options.num_corners = 0; 
pb.solver_options.num_quasi_rand_samples = 50;
pb.solve();






