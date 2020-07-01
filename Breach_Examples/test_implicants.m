%% Initialization
% The following script creates a default interface with the
% AbstractFuelControl model.
clear; close all;
BrDemo.InitAFC();
BrAFC

%% Creating a Falsification Problem
% Given a requirement R and some parameter range, we want to find a
% parameter value for which the system violates R.

%% 
% First we create the parameter search domain and load specifications. 
AFC_Falsify = BrAFC.copy();
AFC_Falsify.SetParamRanges({'Pedal_Angle_pulse_period', 'Pedal_Angle_pulse_amp'}, [10 20; 10 60]);
STL_ReadFile('AFC_simple_spec.stl');
req = BreachRequirement(AF_alw_ok);

%% 
% Then we create the falsification problem and solve it.
falsif_pb = FalsificationProblem(AFC_Falsify, req);
falsif_pb.solve();

%% 
% That's it. The default solver found a trace violating the specification
% AF_alw_ok. 

%% Extract falsifying trace and explain it
AFC_False = falsif_pb.GetFalse(); % AFC_False contains the falsifying trace

%% Give some explanation of violation
diag = AFC_False.Explain();

for is = 1:numel(AFC_False.signals_in)
    sig = AFC_False.signals_in{is}; 
    if diag.isKey(sig)
        fprintf('Implicants for signal %s\n', sig);
        imp = diag(sig);
        imp.Intervals
    end    
end
