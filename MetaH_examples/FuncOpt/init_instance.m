addpath ../../src
addpath ../../breach-dev
InitBreach 

B_ripple =  BreachSignalGen(fun_signal_gen());
B_ripple.dt_default =1; 
B_ripple.SetParamRanges({'x1', 'x2'}, [0 1]);

R_ripple = BreachRequirement('y[t]>0');
Pb_ripple = FalsificationProblem(B_ripple,R_ripple);
Pb_ripple.StopAtFalse=0;

R_holder = BreachRequirement('y[t]>0');
B_holder = BreachSignalGen(fun_signal_gen('holder'));
B_holder.dt_default =1; 
B_holder.SetParamRanges({'x1', 'x2'}, [-512 512]);
Pb_holder = FalsificationProblem(B_holder,R_holder);
Pb_holder.StopAtFalse=0;


R_ackley2 = BreachRequirement('y[t]>-200');
B_ackley2 = BreachSignalGen(fun_signal_gen('ackley2'));
B_ackley2.dt_default =1; 
B_ackley2.SetParamRanges({'x1', 'x2'}, [-32 32]);


B_ackley3 = BreachSignalGen(fun_signal_gen('ackley2'));
B_ackley3.dt_default =1; 
B_ackley3.SetParamRanges({'x1', 'x2'}, [-32 32]);
