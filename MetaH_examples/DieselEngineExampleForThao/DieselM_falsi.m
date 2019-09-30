%% This script set up the falsification problem 
%% for the Diesel model

close all
clear all
dbstop error

if 0
warning('off', 'ALL')
addpath('/Users/thaodang/Metaheuristics/src')
addpath('/Users/thaodang/Metaheuristics/breach-dev')
addpath('.')
        
InitBreach('/Users/thaodang/Metaheuristics/breach-dev',true); % forces initialization from folder in Metaheuristics
else
    addpath('../../src');
    InitBreach
end

model_name = 'KD_cl_harness_forthao';
load('expcon.mat')
load('KD_const_coeffs_0624.mat')
load('pexhat_stuff.mat')
load('thr_ff_map.mat')

fprintf('\n Setting up a falsification process for the Simulink model %s\n',model_name)

simTime = 50; 
fprintf('\n Simulation time horizon is %d seconds\n',simTime);

IO_signal_names = {'In1','In2','Out1'};


%% Specifying STL formula
phi = STL_Formula('phi','alw_[15,30] (Out1[t] < 41.1)')
% phi = STL_Formula('phi','alw_[15,30](Out1[t]<5)');
% phi = set_params(phi, {'sim_time'}, [simTime]);
% phitest1 = STL_Formula('phitest1','ev(RPM[t]>2520)');
% phi = STL_Formula('check', 'alw_[0.1, sim_time] (Out1[t] > -0.001)'); 
% phi = set_params(phi, {'sim_time'}, [sim_time]);

%% Specifying the class of input signals
nb_ctr_pts = [10; 10];
input_ranges = [ 0 40; 1800 3000 ];
%signal_types = [ 'UniStep'; 'UniStep' ];
signal_gen_method = {'previous','previous'};
input_signal_names = {'In1','In2'};

% grid size collumn on the range of each input signal
gridsize_vector = [ 4; 4 ];


%%%% Once the above system specifications and falsification options are given,
%%%% the following part of the code need not be modified by the user
MetaObj = MetaFalsify(model_name,IO_signal_names);
% specify the simulation time
MetaObj.SimTimeSetUp(simTime);

% specify the class of input signals
MetaObj.InputSignalSetUp(input_signal_names,signal_gen_method,nb_ctr_pts,input_ranges);

% specify the property to falsify
MetaObj.STLFormulaSetUp(phi);

% set up a grid on the input ranges, to estimate coverage
MetaObj.GridSetUp(gridsize_vector,nb_ctr_pts);        


%% Start the falsification process
[r,falsified,total_nb_sim,falsi_point] = MetaObj.MetaCall();


