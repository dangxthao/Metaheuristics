% This script demonstrates the input coverage-based testing procedure on
% a powertrain control (PTC) benchmark example. The model is described in
% the following:
%
% "Powertrain Control Verification Benchmark", X. Jin, J. V. Deshmukh, 
% J. Kapinski, K. Ueda, K. Butts. In Hybrid Systems: Computation and 
% Control (HSCC) 2014.
%
% J. Kapinski
% Toyota Technical Center
% Last modified: 6-22-2016
%

clear all
bdclose all

ticpointer = tic;

currentPath = pwd;
temp = strsplit(currentPath,'\');
parentDir = strjoin(temp(1:length(temp)-2),filesep);

addpath([ parentDir filesep 'tb' filesep 'tinevez_tree']);
addpath([ parentDir filesep 'src']);


%% 3. Breach Interface Object Creation
model_name = 'AbstractFuelControl_M1';
% total simulation time
simTime = 50 ; 
% time to introduce sensor failure (default sensor failure won't happen)
fault_time = 100; 
% Simulink initialization phase
measureTime = 1;  
spec_num = 1; %specification measurement
fuel_inj_tol = 1.0; 
MAF_sensor_tol = 1.0;
AF_sensor_tol = 1.0;

BrFC = BreachSimulinkSystem(model_name,{});

BrFC.SetTime([0 simTime]);

%% Jim K doodles/experiments----------------------------------------


FC_Nominal= BrFC.copy();%Creates a copy of the interface object

%% Requirement Setup

% setting time
eta = 1;
taus = 10 + eta;
Ut = 0.05;

phi = ['alw_[' num2str(taus) ', ' num2str(simTime) '] verification_measurement[t]>=-0.5 and verification_measurement[t]<=0.5'];
MaxError_Spec = STL_Formula('Test_Spec',phi);

% Print the parameters interfaced with Breach
FC_Nominal.PrintParams();
% Print the signals interfaced with Breach
FC_Nominal.PrintSignals();
% % Example of how to set one of the parameters
% FC_Nominal.SetParam('C_u0',50);

setuptime = toc(ticpointer);
fprintf('\nSetup time: %f sec.\n',setuptime);

%% Run input space coverage process

% Create initial collection of input traces
L = 0.5;
epsilon=20;
tset = 0:.1:50;
ulim = [0 61.19]; % Pedal angle range for "normal" mode. 
% Note that 61.2 would send the system into "power" mode. So this range
% keeps you in "normal" mode after "startup".

% Fix the engine speed input, for now.
engsp_inputs = 1000*ones(length(tset),1);

% Create tree
sig_tree = signal_tree(ulim, L, epsilon,tset);
% Grow complete tree
sig_tree = sig_tree.grow_epsi_tree();

leaves = sig_tree.findleaves();
inpSignals = {};
for ind = leaves
    inpSignals{end+1} = sig_tree.get_signal_from_leaf(ind);
end

for indrefinements = 1:2

    Traces = [];
    worst_case_rob = inf;
    
    % Run simulations using current collection of input traces
    
    for indi = 1:length(inpSignals)
        BrNew = FC_Nominal.copy();
        BrNew.Sim(tset,[tset' inpSignals{indi}' engsp_inputs]);
        
        % Check the specification
        fprintf('\nCheck test spec:\n');
        rob = BrNew.CheckSpec(MaxError_Spec)
        if rob<worst_case_rob
            worst_case_rob = rob;
            worst_case_ind = indi;
        end
        if rob<0
            break;
        end
        
        if isempty(Traces)
            Traces= BrNew.copy();
        else
            Traces.Concat(BrNew);  % Add new trace
        end
    end
    
    if rob<0
        break;
    end
    
    temptime = toc(ticpointer);
    fprintf('\nTotal time at end of iter. %i: %f sec.\n',indrefinements,temptime);
    fprintf('Worst case robustness: %f, Index: %d\n',worst_case_rob,worst_case_ind);
    
    % save([ mfilename '_iter_' num2str(indrefinements) '_' datestr(now,30)]);
    
    %% Plot results from this iteration
    Traces.PlotSignals;
    subplot(4,1,1)
    title(['PTC benchmark test results, Iteration ' num2str(indrefinements)]);
    
    epsilon = epsilon/2;
    % Create tree
    sig_tree = signal_tree(ulim, L, epsilon,tset);
    % Grow complete tree
    sig_tree = sig_tree.grow_epsi_tree();
    
    leaves = sig_tree.findleaves();
    inpSignals = {};
    for ind = leaves
        inpSignals{end+1} = sig_tree.get_signal_from_leaf(ind);
    end
    
end

