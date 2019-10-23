close all;
clear all;
clc;
warning('OFF', 'ALL')

%% Setup DeltaSigma model
init_SDT

%% Wordgen generator
addpath('../../../wordgen');
num_evt = 60;
sg = var_cp_signal_gen('In1',num_evt+2, 'linear');

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
params_evt = pg.params(1:end-3);
ranges = repmat([0,1], numel(params_evt),1);

S = BreachSignalGen(sg);


%% Time and requirements
time = linspace(0,1.5e-6, 10000);
ts = .9e-8; % time scale
STL_ReadFile('SDT_req.stl');


%% Falsification Problem

Bwg = BP2.copy();
Bwg.SetInputGen(S);
Bwg.SetParamGen(pg);
Bwg.SetParam('time_scale', ts);
Bwg.SetTime(time);

Rwg = BreachRequirement(notsat, {}, per); 
pbwg = FalsificationProblem(Bwg, Rwg, params_evt, ranges);

%%
pbwg.max_obj_eval=1000;
pbwg.solver_options.num_corners = 0; 
pbwg.solver_options.num_quasi_rand_samples = 50;
pbwg.solve();
Rpb= pbwg.GetLog();

%%
Fwg = BreachSamplesPlot(Rpb); 
Fwg.set_y_axis('notsaturation');

%% Testing without wordgen (free dt)
Bn = BP2.copy();
Bn.SetInputGen(S);
Bn.SetParam('time_scale', ts);
Bn.SetTime(time);
Rn = BreachRequirement(notsat, {}, per);
params_dt = Bn.expand_param_name('In1_dt.');
params_u = Bn.expand_param_name('In1_u.');
ranges_dt = repmat([0 4*ts], numel(params_dt), 1);
p0_u = Bwg.GetParam(params_u);
Bn.SetParamRanges(params_dt, ranges_dt)
Bn.SetParam(params_u, p0_u)

pbn = FalsificationProblem(Bn, Rn, params_dt, ranges_dt);
pbn.max_obj_eval=10;
pbn.solver_options.num_corners = 0; 
pbn.solver_options.num_quasi_rand_samples = 50;
pbn.solve();
Rpb= pbn.GetLog();


