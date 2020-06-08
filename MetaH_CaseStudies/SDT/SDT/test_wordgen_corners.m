%% Setup DeltaSigma model
init_SDT
warning('OFF', 'ALL')

%% Wordgen generator
addpath('../../../wordgen');
num_evt = 70;
sg = var_cp_signal_gen('In1',num_evt+1, 'linear');

%% 
pg = TA_param_gen('In1','cycle_8_12.prism', num_evt);
pg.wordgen_exe = './wordgen';

%% Create template
sdt_template = '%g[b]%g[c]%g[d]';
num = 3;
while num<=num_evt
    num = num +4;
    sdt_template = [sdt_template '%g[a]%g[b]%g[c]%g[d]']; % template for lasso init
end
sdt_template = sdt_template(1:5*num_evt);
pg.set_template_in(sdt_template);
pg.template_in = regexprep(pg.template_in,'\[(\w+)\]', '\[0.1\]'); % erase letters 

%% Time and requirements
S = BreachSignalGen(sg);
time = 0:1e-10:1.5e-6;
ts = 1e-8;
STL_ReadFile('SDT_req.stl');

%% Testing against corners
Bc = BP2.copy();
Bc.SetInputGen(S);
Bc.SetParamGen(pg);
Bc.SetParam('time_scale', ts);
Bc.SetTime(time);

params = pg.params(1:end-3);
ranges = repmat([0,1], numel(params),1);
Bc.SetParamRanges(params, ranges);
%pg.verbose = true
Bc.CornerSample(100);
%% 
Bc.ResetSimulations;
Rper = BreachRequirement(per);
Rper.Eval(Bc)

%% 
BreachSamplesPlot(Rper)
