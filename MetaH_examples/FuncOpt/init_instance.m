addpath ../../src

B_ripple =  BreachSignalGen(fun_signal_gen());
B_ripple.dt_default =1; 
B_ripple.SetParamRanges({'x1', 'x2'}, [0 1]);

R = BreachRequirement('y[t]>0');
Pb_ripple = FalsificationProblem(Bripple,R);
Pb_ripple.StopAtFalse=0;

B_holder = BreachSignalGen(fun_signal_gen('holder'));
B_holder.dt_default =1; 
B_holder.SetParamRanges({'x1', 'x2'}, [-512 512]);
Pb_holder = FalsificationProblem(B_holder,R);
Pb_holder.StopAtFalse=0;