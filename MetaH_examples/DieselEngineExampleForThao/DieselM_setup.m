%% Breach Interface Object Creation
close all
clear all
warning('off', 'ALL')

addpath('/Users/thaodang/Metaheuristics/supp_code')
addpath('/Users/thaodang/Metaheuristics/src')
addpath('/Users/thaodang/Metaheuristics/breach-dev')
addpath('.')
        
InitBreach('/Users/thaodang/Metaheuristics/breach-dev',true); % forces initialization from folder in Metaheuristics



model_name = 'KD_cl_harness_forthao';
load('expcon.mat')
load('KD_const_coeffs_0624.mat')
load('pexhat_stuff.mat')
load('thr_ff_map.mat')

fprintf('\n Creating breach interface with simulink model %s\n',model_name)

simTime = 50; 
fprintf('\n Simulation time horizon is %d seconds\n',simTime);

IOsignal_names = {'In1','In2','Out1'};

BrSys = CoverageBreachSet(model_name,{},[], IOsignal_names);
BrSys.SetTime([0 simTime]);



%% Set input signals

fprintf('\n Parametrizing input signal as piecewise constant....\n')
Input_Gen.type = 'UniStep';

N = 10; % Number of control points
fprintf('Number of control points is %d\n',N)

%%%%% old set up %%%%%%
Input_Gen.cp = N;
BrSys.SetInputGen(Input_Gen);
% Specifying parameter names
for i=0:N-1
    signal_u0{1,i+1}=strcat('In1_u',num2str(i));
    signal_u1{1,i+1}=strcat('In2_u',num2str(i));
end

%% Initializing CBS object parameters

%input_range = [5.0,45.0;1800, 3000]
% Input ranges
fprintf('\n Range of In1 is [5.0,45.0]\n')
fprintf('\n Range of In2 is [1800, 3000]\n')
fprintf('\n Grid discretization unit for In1 signal value range is 4 units\n')
InputSys = BrSys.copy();
InputSys.SetParamRanges(signal_u0,ones(N,1)*[0 40]);
InputSys.SetParamRanges(signal_u1,ones(N,1)*[1800 3000]);

%%%%%%%%%%%%%%%%%%


% input_str = {};
% input_cp = [];
% input_intp = {};
% for ii = 1:2
%     
%     input_str{end+1} = ['In' num2str(ii)]
%     input_cp = [input_cp N]
%     input_intp{end+1} = 'previous'
%     
%     input_str
%     fprintf('\n Press any key to continue')
%     pause
% end
% Diesel_input_gen = fixed_cp_signal_gen(input_str, input_cp, input_intp)
% %MRS_system.SetInputGen(BreachSignalGen({MRS_input_gen}));
% BrSys.SetInputGen(BreachSignalGen({Diesel_input_gen}));
% 
% input_param = {};
% input_range = [];
% for ii = 1:2
%     if ii < 2 
%         for jj = 0:9
%             input_param{end+1} = ['In' num2str(ii) '_u' num2str(jj)];
%             input_range = [input_range; 5.0 45.0];
%         end
%     else
%         for jj = 0:9
%             input_param{end+1} = ['In' num2str(ii) '_u' num2str(jj)];
%             input_range = [input_range; 1800.0 3000.0];
%         end
%     end
% end
% Sys = BrSys.copy();
% Sys.SetParamRanges(input_param, input_range);
% input_param
% input_range



gridsizeMat = [];
for ii = 1:2
    gridsizeMat = [ gridsizeMat; 4*ones(N,1) ];
end
InputSys.SetEpsGridsize(gridsizeMat);
InputSys.SetDeltaGridsize(2*InputSys.epsgridsize);


% InputSys.SetEpsGridsize(4*ones(N,1));
% InputSys.SetDeltaGridsize(2*InputSys.epsgridsize);

%% Specifying STL formula
phi = STL_Formula('phi','alw_[15,30] (Out1[t] < 41)')
% phi = STL_Formula('phi','alw_[15,30](Out1[t]<5)');
% phi = set_params(phi, {'sim_time'}, [simTime]);
% phitest1 = STL_Formula('phitest1','ev(RPM[t]>2520)');
% phi = STL_Formula('check', 'alw_[0.1, sim_time] (Out1[t] > -0.001)'); 
% phi = set_params(phi, {'sim_time'}, [sim_time]);

MetaObj = MetaFalsify(InputSys,phi);

[r,falsified,total_nb_sim,falsi_point] = MetaObj.MetaCall(InputSys,phi);

