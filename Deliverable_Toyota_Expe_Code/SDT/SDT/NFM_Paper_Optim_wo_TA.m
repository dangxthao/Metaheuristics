%%
% Without TA - tries to generate a valid input through optimization first. 


%% Init Model
init_SDT;

%% Time and requirements
time = 0:1e-10:1e-6;
STL_ReadFile('SDT_req.stl');
R =  BreachRequirement(notsat, [], per);
R.SetParam('sat_val', 0); % just maximize that
ts = 1e-8;


%% Testing without wordgen (free dt) 
Bva = BP2.copy();
sg_va = var_cp_signal_gen('In1',num_evt+2, 'pchip');
Bva.SetInputGen(sg_va);
Bva.SetTime(time);
Bva.SetParam('time_scale', ts,true);
params_dt = Bva.expand_param_name('In1_dt.');
params_u = Bva.expand_param_name('In1_u.');
ranges_dt = repmat([0 8*ts], numel(params_dt), 1);

%
idx_u = FindParam(Bva.P, params_u);

%
p0_u = repmat([1 2 1 0]', round(71/4), 1);

%
Bva.SetParamRanges(params_dt, ranges_dt)
Bva.SetParam(params_u, p0_u)

%%
pb = FalsificationProblem(Bva, R);
pb.max_obj_eval = 10000;
pb.max_consecutive_constraints_failed= 10000;
pb.setup_global_nelder_mead('num_corners',0,'num_quasi_rand_samples',100, 'local_max_obj_eval',10000)
pb.StopAtFalse=false;
pb.solve(); 
Rva = pb.GetLog();

%%
BreachSamplesPlot(Rva);
