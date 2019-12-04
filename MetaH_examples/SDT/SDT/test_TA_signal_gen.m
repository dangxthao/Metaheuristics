%% Setup DeltaSigma model

%% 
num_evt = 10;
sg = TA_signal_gen('In1','cycle_8_12.prism',{'a','b','c','d'}, num_evt);

%% Time and requirements
S = BreachSignalGen(sg);
ts = 1;
time = 0:.01:20;
S.SetParam('time_scale',ts);
S.SetParam({'In1_a_val','In1_b_val','In1_c_val','In1_d_val'}, [1 2 3 4]);
S.SetTime(time);

%% 
sg2 = TA_signal_gen2({'throttle', 'brake'},'cycle_8_12.prism',{'a','b','c','d'}, num_evt);
S2 = BreachSignalGen(sg2);
ts = 1;
time = 0:.01:20;
S2.SetParam('time_scale',ts);
S2.SetTime(time);

%%  Assign values
p_throttle_a = S2.expand_param_name('.*throttle_a_val');
p_brake_a = S2.expand_param_name('.*brake_a_val');

p_throttle_b = S2.expand_param_name('.*throttle_b_val');
p_brake_b = S2.expand_param_name('.*brake_b_val');

p_throttle_c = S2.expand_param_name('.*throttle_c_val');
p_brake_c = S2.expand_param_name('.*brake_c_val');

p_throttle_d = S2.expand_param_name('.*throttle_d_val');
p_brake_d = S2.expand_param_name('.*brake_d_val');


%%
S2.SetParamRanges(p_throttle_c, [0 100]);
S2.SetParam(p_brake_c, 0);

S2.SetParam(p_throttle_b, 0);
S2.SetParam(p_brake_b, 0);

S2.SetParam(p_throttle_d, 0);
S2.SetParamRanges(p_brake_d, [0 325]);

S2.SetParam(p_throttle_a, 0);
S2.SetParam(p_brake_a, 0);

pvar = S2.GetVariables();
S2.SampleDomain(pvar,10)
S2.Sim();

figure;
S2.PlotSignals();


