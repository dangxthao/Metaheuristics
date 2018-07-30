%clear all;
close all;


warning('off', 'ALL')
% Initialize the model 
load('expcon.mat')
load('KD_const_coeffs_0624.mat')
load('pexhat_stuff.mat')
load('thr_ff_map.mat')
%%

% I disable all warning messages to make it clear
warning('off','all')
model = 'KD_cl_harness_tomasso';

load_system(model);


% System Parameters
system.name = 'KD_cl_harness_tomasso';                      % system name
% system.workspace{1} = 'expcon.mat';                 % system's workspace
% system.workspace{2} = 'KD_const_coeffs_0624.mat';
% system.workspace{3} = 'pexhat_stuff.mat';
% system.workspace{4} = 'thr_ff_map.mat';
system.step_time =5;                            % simulation time step
system.max_iter = 10;                              % max number of iterations

system.dynamics = @(NearestNeighbor,tNeigh,x_U)sim_step_Diesel(system.name, system.step_time, NearestNeighbor, tNeigh, x_U);

%[a b c d] = KD_engine_v2_cl([],[],[],'sizes')
system.init_state =1.0e5* [ 1.0130;
    1.0130;
    0.0000;
    0.5000;
    1.0130;
         0;
    0.0000;
         0;
    0.0000];       % initial state
system.input_set{1} = 5:1:45;                                     % input set
system.input_set{2} = 1800:50:3000;


% Sampling parameters
% sample space lower bound
    kd_tree.smpl_low_bd(1,1) = 90;
    kd_tree.smpl_low_bd(1,2) = 50;
    kd_tree.smpl_low_bd(1,3) = 80;
    kd_tree.smpl_low_bd(1,4) = 0;
    kd_tree.smpl_low_bd(1,5) = 0.5;
    kd_tree.smpl_low_bd(1,6) = 0;
    kd_tree.smpl_low_bd(1,7) = -1;
    kd_tree.smpl_low_bd(1,8) = 0;
    kd_tree.smpl_low_bd(1,9) = 20;
%     kd_tree.smpl_low_bd(1,10) = -10;
%     kd_tree.smpl_low_bd(1,11) = -10;
% sample space upper bound  
    kd_tree.smpl_up_bd(1,1) = 110;
    kd_tree.smpl_up_bd(1,2) = 150;
    kd_tree.smpl_up_bd(1,3) = 120;
    kd_tree.smpl_up_bd(1,4) = 10000;
    kd_tree.smpl_up_bd(1,5) = 1.5;
    kd_tree.smpl_up_bd(1,6) = 1;
    kd_tree.smpl_up_bd(1,7) = 1;
    kd_tree.smpl_up_bd(1,8) = 1;
    kd_tree.smpl_up_bd(1,9) = 100;
%     kd_tree.smpl_up_bd(1,10) = 4000;
%     kd_tree.smpl_up_bd(1,11) = 20;
    
    
kd_tree.bucket_size = 5;                % bucket size of kd-tree
kd_tree.force_time_ex = 50000;         % force time exploration
kd_tree.influence_function = 1;         % potential influence function
kd_tree.num_goals = 3;                  % selection of goal points
kd_tree.num_neighbors = 1;              % selection of the neighbors
kd_tree.num_successors = 1;             % find the less robust between n successor 

% Simulation options
options.running_step = 1;
options.store_kd_tree_partition = false;
options.full_trace_method = true;
options.check_output = true;
options.phi =  'alw_[15,30] ( x1[t] < 5 )'; 

% Call SimuRRT
res = mainSimuRRT_Diesel(system, kd_tree, options);


% Plotting options
plot_options.num_plots = 1;
plot_options.kd_tree = 0;
plot_options.kd_tree_partition = 0;
plot_options.traces = 1;

% Plot simulation result
plotRRT(system,kd_tree,res,plot_options);





