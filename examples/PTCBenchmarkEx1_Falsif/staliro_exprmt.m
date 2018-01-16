% This is a demo for the benchmarks presented in the ARCH 2014 workshop
%
% We present the Automatic Transmission Benchmark and the Fault-Tolerant
% Fuel Control System benchmark with various specifications
%
% (C) Bardh Hoxha, 2014, Arizona State University

clear

%% initialization of the model
load('AbstractFuelControl_M1.mat')
%% Display and user feedback
disp(' ')
disp('This is the PTC Benchmark example')

nform  = 1;
phi_nat{nform} = 'The air-fuel ratio never exceeds 0.5';
phi{nform} = '[]p';
%%
opt = staliro_options();
opt.runs = 1;
opt.spec_space = 'Y';
opt.map2line = 0;
opt.n_workers = 1;
opt.optimization_solver = 'SA_Taliro';
opt.optim_params.n_tests = input('\n maximum number of tests (default: 15000):');

timervar = tic;
init_cond = [];
    
input_range = [0 40; 1000 1000; 1 1];
model = 'AbstractFuelControl_M1NFM';

cp_array = [10,2,2];
opt.interpolationtype = {'pconst'};
opt.taliro = 'dp_taliro';
opt.black_box = 1;

%predicate definitions    
ii = 1;
preds(ii).str='p1';
preds(ii).A = [1 0 0];
preds(ii).b = 0.05;

ii = ii+1;
preds(ii).str='p2';
preds(ii).A = [-1 0 0];
preds(ii).b = 0.05;

ii = ii+1;
preds(ii).str='p3';
preds(ii).A = [1 0 0];
preds(ii).b = 0.02;

ii = ii+1;
preds(ii).str='p4';
preds(ii).A = [-1 0 0];
preds(ii).b = 0.02;

m1 = sprintf('Choose one of the following STL formulas described in prop1.stl file.\n Type one of the following\n');
m2 = sprintf('phi26\n');
m3 = sprintf('phi27\n');
m4 = sprintf('phi29\n');
m5 = sprintf('phitest\n');

prop_ind = input([m1,m2,m3,m4,m5],'s');

switch prop_ind
    case 'phi26'
        phi = '[]_(5, 50) (p1 /\ p2)';
    case 'phi27'
        phi = '[]_(5, 50) (p3 /\ p4)';
    case 'phi29'
        phi = '<>_(50,50) p1';
    case 'phitest'
        phi = '[]_(10,50) (p3 /\p4)';
    otherwise
        error('not a valid input')        
end
time = 50

warning off %#ok<*WNOFF>
[results,history] = staliro(model,init_cond,input_range,cp_array,phi,preds,time,opt);

disp(' ')
disp(' See results for for the output of the robustness values of each run')
disp(' See history for the information on all the tests for each run')

%% plot the inputs/outputs for which the system does not satisfy the spec.
% if form_id_1 == 9 || form_id_1 == 10
%     
%     disp(' ')
%     disp(' NOTE: Since the Fault-Tolerant Fuel Control System model exhibits stochastic behaviour,')
%     disp('       simulating the system with the same sample might not necessarily falsify the specification')
%     
%     [T1,XT1,YT1,IT1] = SimSimulinkMdl('stoch_fault_tol_fuelsys',init_cond,input_range,cp_array,results.run(results.optRobIndex).bestSample,time,opt);
%     
%     figure
%     
%     subplot(3,1,1)
%     plot(IT1(:,1),IT1(:,2))
%     axis([0 100 0 25])
%     title('Throttle')
%     
%     subplot(3,1,2)
%     plot(T1(:,1),YT1(:,1))
%     title('Fuel-Flow Rate')
%     axis([0 100 0 2])
%     
%     subplot(3,1,3)
%     plot(T1,YT1(:,2))
%     hold on
%     %plot([0 30],[omega omega],'r');
%     title('Air-Fuel ratio')
%     plot([0 100],[1.1 1.1],'r');
%     plot([0 100],[0.9 0.9],'r');
%     axis([0 100 0 2])
%         
% else
    
    [T1,XT1,YT1,IT1] = SimSimulinkMdl('AbstractFuelControl_M1NFM',init_cond,input_range,cp_array,results.run(results.optRobIndex).bestSample,time,opt);
    
    figure
    
%     subplot(5,1,1)
%     plot(IT1(:,1),IT1(:,2))
%     axis([0 30 0 100])
%     title('Throttle')
%     
%     subplot(5,1,2)
%     plot(IT1(:,1),IT1(:,3))
%     title('Break')
%     axis([0 30 0 500])
%     
%     subplot(5,1,3)
%     plot(T1,YT1(:,2))
%     hold on
%     plot([0 30],[omega omega],'r');
%     title('RPM')
%     axis([0 30 0 6000])
%     
%     subplot(5,1,4)
%     plot(T1,YT1(:,1))
%     hold on
%     plot([0 30],[v v],'r');
%     
%     title('Speed')
%     axis([0 30 0 200])
%     
%     subplot(5,1,5)
%     plot(T1,YT1(:,3))
%     hold on
%     title('Gear')
%     axis([0 30 0 4])
%     
% end
warning on %#ok<*WNON>
fprintf('\n Computation time is %f seconds \n',toc(timervar));