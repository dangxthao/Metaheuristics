clear
bdclose all
close all
InitBreach


%% Breach Interface Object Creation
model_name = 'ContinuousExample';

% total simulation time
simTime = 10 ; 
BrSys = CoverageBreachSet(model_name,{});
BrSys.SetTime([0 simTime]);

%% Set input signals
InputGen.type = 'UniStep';
N = 10; % Number of control points
InputGen.cp = N;
BrSys.SetInputGen(InputGen);


