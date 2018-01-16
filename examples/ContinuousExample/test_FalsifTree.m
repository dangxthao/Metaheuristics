% test script for FalsifTreeProblem

%% Initialize system
mdl = 'ContinuousExample';
Br = BreachSimulinkSystem(mdl);

%% Initialize specification
phi = STL_Formula('phi', 'alw (y1[t]<5)');

%% Initialize Input tree 
L = .5; 
epsilon=2;
tset = 0:.01:10; 
ulim = [0, 10];

% Create tree 
sig_tree = signal_tree(ulim, L, epsilon,tset);
% Grow complete tree
sig_tree = sig_tree.grow_epsi_tree();

%% Create problem and run 
FalsifTree = FalsifTreeProblem(Br, phi, sig_tree);
res = FalsifTree.solve();

%%
res.Traces.PlotSignals({'u','y1', 'y2'});

