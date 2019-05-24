addpath('/Users/thaodang/Metaheuristics/supp_code')
addpath('/Users/thaodang/Metaheuristics/src')
addpath('/Users/thaodang/Metaheuristics/breach-dev')
addpath('.')
        
InitBreach('/Users/thaodang/Metaheuristics/breach-dev',true); % forces initialization from folder in Metaheuristics


init_instance;


%% plotting the function
Bgrid = B_ripple.copy();
Bgrid.GridSample(50);
Rgrid = BreachRequirement('y[t]>-2');
Rgrid.Eval(Bgrid);

%%
x1 = Rgrid.GetParam('x1')';
x2 = Rgrid.GetParam('x2')';
v = Rgrid.traces_vals';
[x1q,x2q] = meshgrid(0:.01:1, 0:.01:1);
vq = griddata(x1,x2,v,x1q,x2q);
surf(x1q,x2q,vq)

%% Falsification problem 
R = BreachRequirement('y[t]>0');
Pb = FalsificationProblem(B_ripple,R);
Pb.StopAtFalse = 0;

Pb.max_obj_eval = 2000;
%Pb.setup_solver('cmaes');
Pb.setup_solver('simulannealbnd');
%Pb.setup_global_nelder_mead();

%Pb.solver_options.MaxFunEvals = 1000;
%Pb.solver_options.FunctionTolerance = 1e-12;
%Pb.solver_options.OptimalityTolerance = 1e-20;
%Pb.solver_options.TolFun = 1e-16;
Pb.solver_options.InitialTemperature = 100;
Pb.solve();

%% Plotting Log
R = Pb.GetLog();
F = BreachSamplesPlot(R);

