addpath('./Functions')
addpath('./ExampleBand-Pass')
addpath('./ExampleLow-Pass')
addpath('./periodic.signals')
addpath('./periodic_6.signals')
%addpath('/Users/thaodang/Metaheuristics/breach-dev')
%addpath('/Users/thaodang/Metaheuristics/src')
addpath('/Users/thaodang/Metaheuristics/wordgen')        

InitBreach
BP2param
model_name = 'BP2_in';
IO_signal_names = {'In1','OutSat'};
BP2 = BreachSimulinkSystem(model_name, {}, [],  IO_signal_names);

warning('OFF', 'Simulink:blocks:NonPositiveIntegerValueSeed');
