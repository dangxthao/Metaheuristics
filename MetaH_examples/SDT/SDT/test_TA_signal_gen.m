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
