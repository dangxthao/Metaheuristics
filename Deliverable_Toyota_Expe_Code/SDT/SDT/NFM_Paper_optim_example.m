%%
% With TA and various simple solvers (no metasquare) 

%% Init Model
init_SDT;

%% Time and requirements
time = 0:1e-10:1e-6;
STL_ReadFile('SDT_req.stl');
R =  BreachRequirement(notsat, [], per);
R.SetParam('sat_val', 2); % just maximize that

%% TA based signal generator setup 
addpath('../../../wordgen');
num_evt = 70;
sg = TA_signal_gen('In1','cycle_8_12.prism',{'a','b','c','d'}, num_evt, 'linear');
S = BreachSignalGen(sg);
S.SetParam({'In1_a_val','In1_b_val','In1_c_val','In1_d_val'}, [0 1 2 1]);

%% Add input to model 
Bta = BP2.copy();
Bta.SetInputGen(S);
Bta.SetTime(time);
ts = 1e-8;
Bta.SetParam('time_scale', ts, true);
params = sg.params(1:num_evt);
ranges = repmat([0,1], numel(params),1);
Bta.SetParamRanges(params, ranges);
Bta.SetupDiskCaching();

method = input('Which method?');

switch method
    case 'corners'
%% Try corners
pb1 = FalsificationProblem(Bta, R);
pb1.max_obj_eval = 10000; 
pb1.StopAtFalse=false;
pb1.solver_options.num_corners = 10000; 
pb1.solve(); 
Rlog1 = pb1.GetLog();
BreachSamplesPlot(Rlog1);
    case 'rand'

%% Try random
pb2 = FalsificationProblem(Bta, R);
pb2.max_obj_eval = 10000;
%pb2.setup_random('rand_seed',1,'num_rand_samples',10000)
pb2.setup_random('rand_seed',100,'num_rand_samples',10000)
pb2.StopAtFalse=false;
pb2.solve(); 
Rlog2 = pb2.GetLog();
BreachSamplesPlot(Rlog2);

    case 'quasi' 
%% Try quasi-random 
pb3 = FalsificationProblem(Bta, R);
pb3.max_obj_eval = 10000; %10000;
pb3.setup_random('rand_seed',100,'num_rand_samples',10000)
pb3.StopAtFalse=false;
pb3.solve(); 
Rlog3 = pb3.GetLog();
BreachSamplesPlot(Rlog3);

    case 'GNM'
%% Try GNM
pb4 = FalsificationProblem(Bta, R);
pb4.max_obj_eval = 10000;
pb4.setup_global_nelder_mead('num_corners',0,'num_quasi_rand_samples',1000, 'local_max_obj_eval',2000)
pb4.StopAtFalse=false;
pb4.solve(); 
Rlog4 = pb4.GetLog();
BreachSamplesPlot(Rlog4);

        
end