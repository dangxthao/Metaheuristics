Bripple =  BreachSignalGen(fun_signal_gen());
Bripple.dt_default =1; 
Bripple.SetParamRanges({'x1', 'x2'}, [0 1]);
B = Bripple.copy();
B.GridSample(50);


%% plotting the function
Rgrid = BreachRequirement('y[t]>-2');
Rgrid.Eval(B);
%%
x1 = Rgrid.GetParam('x1')';
x2 = Rgrid.GetParam('x2')';
v = Rgrid.traces_vals';
[x1q,x2q] = meshgrid(0:.01:1, 0:.01:1);
vq = griddata(x1,x2,v,x1q,x2q);
surf(x1q,x2q,vq)

%% Falsification problem 
R = BreachRequirement('y[t]>-2.2');
Pb = FalsificationProblem(Bripple,R);
Pb.setup_global_nelder_mead();
Pb.max_obj_eval = 1000;
Pb.solve();

%% Plotting Log
R = Pb.GetLog();
F = BreachSamplesPlot(R);

