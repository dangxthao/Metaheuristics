%% Setup DeltaSigma model
init_SDT
warning('OFF', 'ALL')

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
time = linspace(0,1.5e-6, 10000);
B = BP2.copy();
B.SetInputGen(S);
B.SetParamGen(pg);
B.SetParam('time_scale', [1e-8 : 2e-11 : 1.1e-8],true);
B.SetTime(time);
B.Sim();
B.PlotSignals();

%% Requirements
STL_ReadFile('SDT_req.stl');
Rsat = BreachRequirement(notsat); 
Rper = BreachRequirement(per); 
R = BreachRequirement({notsat, per});
R.Eval(B);
F = BreachSamplesPlot(R); 
return

%% Testing against events
ts = 1.1e-8;
Be = BP2.copy();
Be.SetInputGen(S);
Be.SetParamGen(pg);
Be.SetParam('time_scale', ts);
Be.SetTime(time);

params = pg.params(1:end-3);
ranges = repmat([0,1], numel(params),1);

Be.SetParamRanges(params, ranges);
Be.SampleDomain(params, 100); % random (pseudo not quasi) sampling of 10
Re = BreachRequirement(per);
Re.Eval(Be);
Fe = BreachSamplesPlot(Re); 
Fe.set_y_axis('per');


%% Testing without wordgen (free dt) 
Bn = BP2.copy();
Bn.SetInputGen(S);
Bn.SetParam('time_scale', ts);
Bn.SetTime(time);
params_dt = Bn.expand_param_name('In1_dt.');
params_u = Bn.expand_param_name('In1_u.');
ranges_dt = repmat([0 4*ts], numel(params_dt), 1);
p0_u = Be.GetParam(params_u);

Bn.SetParamRanges(params_dt, ranges_dt)
Bn.SetParam(params_u, p0_u)
Rn = BreachRequirement(per);

Bn.SampleDomain(params_dt, 100);
Rn.Eval(Bn);
Fn = BreachSamplesPlot(Rn);
Fn.set_y_axis('per');


