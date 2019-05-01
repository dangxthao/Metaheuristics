addpath ../../src

Bripple =  BreachSignalGen(fun_signal_gen());
Bripple.dt_default =1; 
Bripple.SetParamRanges({'x1', 'x2'}, [0 1]);

R = BreachRequirement('y[t]>-2.2');
Pb = FalsificationProblem(Bripple,R);
