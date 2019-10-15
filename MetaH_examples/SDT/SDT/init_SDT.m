addpath('./Functions')
addpath('./ExampleBand-Pass')
addpath('./ExampleLow-Pass')
addpath('./periodic.signals')
addpath('./periodic_6.signals')
%addpath('../../../breach-dev')
addpath('../../../src')
addpath('../../../wordgen')        

InitBreach
BP2param
model_name = 'BP2_in';
IO_signal_names = {'In1','OutSat'};
BP2 = BreachSimulinkSystem(model_name, {}, [],  IO_signal_names);

