% TODO: convert this file into a file that takes an array of floats (input),
% converts it to a timeseries by adding the time column, calls the Neural net,
% and returns the last outputted float

function [] = NNteacher_test2()
  In1 = [0 1 2 3 4 5; 20 4 6 -2 -4 -6]';
  assignin('base', 'In1', In1)
  timeSim = In1(:,1);
  timeSim= timeSim-timeSim(1);
  sg_in = from_workspace_signal_gen({'In1'});

  global BrSD
  BrSD_temp=BrSD.copy();
  BrSD_temp.SetInputGen({sg_in});
  BrSD_temp.Sim(timeSim);
  BrSD_temp.PlotSignals({'In1', 'Out1'});

  %get the index of the ouput signal in the Log
  output_name='Out1';
  index_output=find(strcmp(BrSD_temp.P.ParamList,...
                                       output_name));
  word=[ BrSD_temp.P.traj{1, 1}.time'...
                  BrSD_temp.P.traj{1, 1}.X(index_output,:)' ];

  word
end


