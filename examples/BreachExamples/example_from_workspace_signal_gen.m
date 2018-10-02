
%%
% First assume we have a model with input blocks, e.g., 
mdl = 'Autotrans_shift';
B = BreachSimulinkSystem(mdl);

%%
% This model has two inputs, namely throttle and brake. 

%% 
% We assume further that data for throttle and brake is given in two arrays
% of size Nx2, where first column is time, stored in csv files, e.g.,  
throttle = csvread('throttle.csv');
brake = csvread('brake.csv');

%%
% 
sg = from_workspace_signal_gen({'throttle', 'brake'});
IG = BreachSignalGen(sg);
B.SetInputGen(IG);

%%
B.Sim();
B.PlotSignals({'throttle', 'brake', 'speed'});





