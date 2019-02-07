classdef MetaFalsifSDT < MetaFalsify
    
    methods
        
        function this=MetaFalsifSDT(sigId, timeFixed) 
            init_SDT;
            phi = STL_Formula('notsaturation', 'alw(OutSat[t]<1.145)');
                if (sigId < 10)
                    sigfilename = strcat('s_0', num2str(sigId));
                else
                    sigfilename = strcat('s_', num2str(sigId));
                end
                
                
                Insig_org = load(sigfilename, '-ascii');
                
                scaling=1e-6;
                nb_ctr_pts = 60; %10;
                input_ranges = [Insig_org(1:nb_ctr_pts,2)-0.3 Insig_org(1:nb_ctr_pts,2)+0.3];
                %input_ranges = [0 3];
                
                Insig(:,1) = scaling*Insig_org(1:nb_ctr_pts, 1);
                timepoints = Insig(:,1);
                simTime = 6e-5;
                input_signal_names = {'In1'};
                signal_gen_method = {'linear'};
                
                %%%% grid size column on the range of each input signal
                gridsize_vector = [ 4  ];
                this = this@MetaFalsify(model_name,IO_signal_names);
                
                % specify the simulation time
                this.SimTimeSetUp(0:1e-9:simTime);
                
                % specify the class of input signals
                if nargin==1
                    this.InputSignalSetUp(input_signal_names,signal_gen_method,nb_ctr_pts,input_ranges,timepoints);
                    this.GridSetUp(gridsize_vector,nb_ctr_pts);
                else
                    this.InputSignalSetUp(input_signal_names,signal_gen_method,nb_ctr_pts,input_ranges,timepoints, timeFixed);
                    this.GridSetUp(gridsize_vector,2*nb_ctr_pts-1);
                end
                this.STLFormulaSetUp(phi);
                
                % set up a grid on the input ranges, to estimate coverage
            
            
        end
    end
end