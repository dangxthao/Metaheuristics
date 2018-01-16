bdclose all
close all
clear
InitBreach


%% Breach Interface Object Creation
model_name = 'autotrans_mod04';

% total simulation time
simTime = 30 ; 
BrSys = CoverageBreachSet(model_name,{});
BrSys.SetTime([0 simTime]);

%% Set input signals
input_gen.type = 'UniStep';
N1 = 7; N2 = 3;
input_gen.cp = [N1 N2];
input_gen.method = {'previous','previous'};
BrSys.SetInputGen(input_gen);