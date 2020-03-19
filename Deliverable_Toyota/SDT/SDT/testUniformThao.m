close all;
clear;
clc;
warning('OFF', 'ALL')

addpath('/Users/thaodang/GIT/discrepancy/SDT/SDT/Functions')
addpath('/Users/thaodang/GIT/discrepancy/SDT/SDT/ExampleBand-Pass')
addpath('/Users/thaodang/GIT/discrepancy/SDT/SDT/ExampleLow-Pass')
addpath('/Users/thaodang/GIT/discrepancy/SDT/SDT/periodic.signals')
addpath('/Users/thaodang/breach-dev')
        
InitBreach
BP2param

model_name = 'BP2_in';

%rng(15000,'twister');
BrSD = BreachSimulinkSystem(model_name);
%, 'all', [], {}, [], 'Verbose',0,'SimInModelsDataFolder', true); 


for sigId = 10:10
    if (sigId < 10)
        sigfilename = strcat('s_0', num2str(sigId));
    else
        sigfilename = strcat('s_', num2str(sigId));
    end
    
%     A = load(sigfilename, '-ascii');
%     time = A(:,1);
%     tpoint = time.*(1e-7)
%     sz = size(time)
%     sz(1)
%     sim_time = time(sz(2))
   
    
    %p0 = A(:,2);
    %sz = size(A);
    %sg_in= fixed_cp_signal_gen({'In1'}, sz(1), 'linear', p0');
    %sg_in= var_cp_signal_gen({'In1'}, sz(1), 'linear', p0)
    
%     In1 = [ p0 ] 
%     save('sMat.mat', 'time', 'In1');
%     sg_in = from_file_signal_gen({'In1'}, 'sMat.mat', 'In1')
%     
%     tpoint
%     p0 = A(:,2);
%     In1 = cat(2, tpoint,  p0); %A(1:2,:)
%     sg_in = from_workspace_signal_gen({'In1'})
%     
%     BrSD_temp=BrSD.copy();
%     BrSD_temp.SetInputGen({sg_in});
    
    
    %BrSD.SetTime([0 sim_time]);
    
   
%BrSD_temp.PrintParams();
%BrSD_temp.Sim(0:Ts/10:3*Ts);
%     BrSD_temp.Sim();
%     BrSD_temp.PlotSignals({'In1', 'Out1'});
    %input('Press ENTER to continue');




    In1 = load(sigfilename, '-ascii');
    In1(:,1) = 1e-7*In1(:,1); 
    time = In1(:,1);
    time= time-time(1);
    sg_in = from_workspace_signal_gen({'In1'});
    
%     sz = size(time)
%     time
%     sim_time = time(sz(1))
%     %phi = STL_Formula('saturation', 'alw_[0, 2.4e-05] (Out1[t] < 0.1)'); 
%     phi = STL_Formula('saturation', 'alw_[0, 2.4e-5] (OutSat[t] < Vref)'); 
%     %phi = set_params(phi, {'sim_time'}, [sim_time]);
%     
%     
    BrSD_temp=BrSD.copy();
    BrSD_temp.SetInputGen({sg_in});
    BrSD_temp.Sim(time);
    BrSD_temp.PlotSignals({'In1', 'OutSat'});
     
%     rob = BrSD_temp.CheckSpec(phi);
%     if rob<0 
%                    disp('Falsified in StatFalsify');
%                    new_fig = gcf;
%                    BrSD.PlotSignals;
%                    falsified = true;
%                    return;
%     end

end
    
               
