%% Init paths and breach
addpath('../../src');
addpath('../../breach-dev');
run('../../breach-dev/InitBreach.m');

%% Setup Simulink model and requirement
PTC_setup;

%% Create Metafalsification problem
MhPb = MetaFalsify(CBr, R);
MhPb.max_obj_eval = 500;

%% Try corners, quasi-random and global-nelder-mead 
MhPb.Run('corners');

%%
MhPb.Run('quasirandom');

%%
MhPb.Run('global_nelder_mead');

%% 
MhPb.PlotResults();


