
bdclose all
close all
% clear
InitBreach


%% Breach Interface Object Creation

model_name = 'autotrans_mod04';
fprintf('\n Creating breach interface with simulink model %s\n',model_name)

simTime = 30 ; 
fprintf('\n Simulation time horizon is %d seconds\n',simTime)

% fprintf('\n Press any key to continue')
% pause

BrSys = CoverageBreachSet(model_name,{});
BrSys.SetTime([0 simTime]);

%% Set input signals

fprintf('\n Parametrizing input signals throttle and break....\n')
fprintf('\n Input signals are parametrized as piecewise constant\n ')
input_gen.type = 'UniStep';

N1 = 7; N2 = 3;
fprintf('Number of control points for throttle input is %d\n',N1)
fprintf('Number of control points for break input is %d\n',N2 )
input_gen.cp = [N1 N2];
input_gen.method = {'previous','previous'};
BrSys.SetInputGen(input_gen);

%% Specifying parameter names
for i=0:N1-1
    signal_u0{1,i+1}=strcat('In1_u',num2str(i));
end

for i=0:N2-1
     signal_u1{1,i+1}=strcat('In2_u',num2str(i));    
end
signal = [signal_u0,signal_u1];

%% Initializing CBS object parameters

% Input ranges
fprintf('\n Range of throttle is [35,100]\n')
fprintf('Range of break is [0,40] \n')
fprintf('\n Grid discretization unit for both signal ranges is 4 units\n')
R1 = [35,100];
R2 = [0,40];
Sys = BrSys.copy;
signal
Sys.SetParamRanges(signal,[ones(N1,1)*R1;ones(N2,1)*R2]);
Sys.SetEpsGridsize([4*ones(N1,1);4*ones(N2,1)]);
Sys.SetDeltaGridsize(2*Sys.epsgridsize);


%% Specifying STL formula
fprintf('\n The STL formula is\n ')
f1 = STL_Formula('f1','alw(RPM[t]<2520)');
f2 = STL_Formula('f2','ev_[0,10](speed[t]>50)');
phi = STL_Formula('phi1','not(f1 and f2)');

% Can rewrite formula: [f1 => phitest2] where
phitest1 = STL_Formula('phitest1','ev(RPM[t]>2520)'); % not(f1)
phitest2 = STL_Formula('phitest2','alw_[0,10](speed[t]<50)'); % not(f2)

