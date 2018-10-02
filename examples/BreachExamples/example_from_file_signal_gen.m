
%%
% First assume we have a model with input blocks, e.g., 
mdl = 'Autotrans_shift';
B = BreachSimulinkSystem(mdl);

%%
% This model has two inputs, namely throttle and brake. 

%% 
% We assume further that data for throttle and brake is given in two arrays
% of size N, where N can be different for brake and throttle, and at different time instants t_throttle and t_brake.  

t_throttle =  0:.1:30;
throttle = 50*cos(t_throttle')+50;

%% 
%
t_brake = 0:.21:30;
brake = 25*sin(t_brake')+25;

%%
% To use from_file_signal_gen, we save the data in two different files.
% Note: we could use one file if time values were the same. 

time = t_brake; 
save('brake_data.mat', 'time' , 'brake');

%%
time = t_throttle; 
save('throttle_data.mat', 'time' , 'throttle');


%%
% 
sg1 = from_file_signal_gen('throttle', 'throttle_data.mat');

%%
sg2 = from_file_signal_gen('brake', 'brake_data.mat');

IG = BreachSignalGen({sg1, sg2});
B.SetInputGen(IG);

%%
B.Sim();
B.PlotSignals({'throttle', 'brake', 'speed'});





