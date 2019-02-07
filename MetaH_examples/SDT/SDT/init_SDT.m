addpath('./Functions')
addpath('./ExampleBand-Pass')
addpath('./ExampleLow-Pass')
addpath('./periodic.signals')
addpath('./periodic_6.signals')
addpath('../../../breach-dev')

addpath('../../../supp_code')
addpath('../../../src')
addpath('../../../breach-dev')
addpath('.')
        
InitBreach
BP2param
model_name = 'BP2_in';
IO_signal_names = {'In1','OutSat'};


