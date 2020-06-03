function [] = initializeBreach()
  close all;
  clear;
  clc;
  warning('OFF', 'ALL')
  
  global BrSD
  %% Add the path to $ROOTDIR/breach-dev, better to be absolute
  addpath('../breach-dev')

  InitBreach
  model_name = 'NN';


  %% set the seed
  %rng(15000,'twister');
  BrSD = BreachSimulinkSystem(model_name);
  %, 'all', [], {}, [], 'Verbose',0,'SimInModelsDataFolder', true);

end
