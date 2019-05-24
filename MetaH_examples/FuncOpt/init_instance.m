addpath ../../src
addpath ../../breach-dev
InitBreach 

% B_ripple =  BreachSignalGen(fun_signal_gen());
% B_ripple.dt_default =1; 
% B_ripple.SetParamRanges({'x1', 'x2'}, [0 1]);
% 
% R_ripple = BreachRequirement('y[t]>0');
% Pb_ripple = FalsificationProblem(B_ripple,R_ripple);
% Pb_ripple.StopAtFalse=0;
% 
% R_holder = BreachRequirement('y[t]>0');
% B_holder = BreachSignalGen(fun_signal_gen('holder'));
% B_holder.dt_default =1; 
% B_holder.SetParamRanges({'x1', 'x2'}, [-512 512]);
% Pb_holder = FalsificationProblem(B_holder,R_holder);
% Pb_holder.StopAtFalse=0;
% 
% B_ackley2 = BreachSignalGen(fun_signal_gen('ackley2'));
% B_ackley2.dt_default =1; 
% B_ackley2.SetParamRanges({'x1', 'x2'}, [-32 32]);
% 
% 
% B_ackleyN3 = BreachSignalGen(fun_signal_gen('ackleyN3'));
% B_ackleyN3.dt_default =1; 
% B_ackleyN3.SetParamRanges({'x1', 'x2'}, [-32 32]);
% 
% B_ackley4 = BreachSignalGen(fun_signal_gen('ackley4'));
% B_ackley4.dt_default =1; 
% B_ackley4.SetParamRanges({'x1', 'x2'}, [-35 35]);
% 
% B_beale = BreachSignalGen(fun_signal_gen('beale'));
% B_beale.dt_default =1; 
% B_beale.SetParamRanges({'x1', 'x2'}, [-4.5 4.5]);

% B_bohachevskyn1fcn = BreachSignalGen(fun_signal_gen('bohachevskyn1fcn'));
% B_bohachevskyn1fcn.dt_default =1; 
% B_bohachevskyn1fcn.SetParamRanges({'x1', 'x2'}, [-100 100]);

% B_booth = BreachSignalGen(fun_signal_gen('booth'));
% B_booth.dt_default =1; 
% B_booth.SetParamRanges({'x1', 'x2'}, [-10 10]);

% B_brentfcn = BreachSignalGen(fun_signal_gen('brentfcn'));
% B_brentfcn.dt_default =1; 
% B_brentfcn.SetParamRanges({'x1', 'x2'}, [-10 10]);

% B_bukinn6fcn = BreachSignalGen(fun_signal_gen('bukinn6fcn'));
% B_bukinn6fcn.dt_default =1; 
% B_bukinn6fcn.SetParamRanges({'x1'}, [-15 -5]);
% B_bukinn6fcn.SetParamRanges({'x2'}, [-3 3]);

% B_crossintrayfcn = BreachSignalGen(fun_signal_gen('crossintrayfcn'));
% B_crossintrayfcn.dt_default =1; 
% B_crossintrayfcn.SetParamRanges({'x1', 'x2'}, [-10 10]);

B_easomfcn = BreachSignalGen(fun_signal_gen('easomfcn'));
B_easomfcn.dt_default =1; 
B_easomfcn.SetParamRanges({'x1', 'x2'}, [-100 100]);

          