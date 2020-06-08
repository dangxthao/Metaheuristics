%% Setup DeltaSigma model
init_SDT
warning('OFF', 'ALL')

%% Wordgen generator
addpath('../../../wordgen');
num_evt = 70;
sg = TA_signal_gen('In1','cycle_8_12.prism',{'a','b','c','d'}, num_evt, 'linear');

%% Time and requirements
S = BreachSignalGen(sg);
S.SetParam({'In1_a_val','In1_b_val','In1_c_val','In1_d_val'}, [0 1 2 1]);
time = 0:1e-10:1.5e-6;
STL_ReadFile('SDT_req.stl');

%% Testing against corners
Bc = BP2.copy();
Bc.SetInputGen(S);
Bc.SetTime(time);

params = sg.params(1:num_evt);
ranges = repmat([0,1], numel(params),1);
Bc.SetParamRanges(params, ranges);
%pg.verbose = true
Bc.CornerSample(100);
ts = [.7:.05:1]*1e-8;
Bc.SetParam('time_scale', ts, 'combine');

%% 

%Rper = BreachRequirement(per);
%Rper.Eval(Bc);


%%
Rsat = BreachRequirement(notsat, {}, per);
Rsat.Eval(Bc);

%% 
BreachSamplesPlot(Rsat)
