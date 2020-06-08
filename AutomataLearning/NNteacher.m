close all;
clear;
clc;
warning('OFF', 'ALL')

%% Add the path to $ROOTDIR/breach-dev, better to be absolute
addpath('../breach-dev')
        
InitBreach
model_name = 'NN';


%% set the seed
%rng(15000,'twister');
BrSD = BreachSimulinkSystem(model_name);
%, 'all', [], {}, [], 'Verbose',0,'SimInModelsDataFolder', true); 

nbSig=10;

% We assume that the input words are in files named s_01, s_02...
% Input words are stored as time series

for sigId = 1:nbSig
    if (sigId < 10)
        sigfilename = strcat('s_0', num2str(sigId));
    else
        sigfilename = strcat('s_', num2str(sigId));
    end
    
    In1 = load(sigfilename, '-ascii');
    timeSim = In1(:,1);
    timeSim= timeSim-timeSim(1);
    sg_in = from_workspace_signal_gen({'In1'});
    
% We can even define an STL formula,
% phi = STL_Formula('bounded', 'alw_[0, 10] (Out1[t] < 0.1)'); 
     
    BrSD_temp=BrSD.copy();
    BrSD_temp.SetInputGen({sg_in});
    BrSD_temp.Sim(timeSim);
    BrSD_temp.PlotSignals({'In1', 'Out1'});
     
%     rob = BrSD_temp.CheckSpec(phi);
%     if rob<0 
%        disp('Falsified the Property');
%        BrSD.PlotSignals;
%        return;
%     end


    %get the index of the ouput signal in the Log
    output_name='Out1';
    index_output=find(strcmp(BrSD_temp.P.ParamList,...
                                         output_name));
    word=[ BrSD_temp.P.traj{i}.time'...
                    BrSD_temp.P.traj{i}.X(index_output,:)' ];

    output_words = [output_words word];

end

output_words
    
               
