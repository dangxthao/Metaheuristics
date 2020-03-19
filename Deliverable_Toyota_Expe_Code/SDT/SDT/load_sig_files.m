init_SDT;
sigfilenames = {};
for sigId = 0:10
        if (sigId < 10)
                sigfilenames{sigId+1} = strcat('s_0', num2str(sigId));
        else
                sigfilenames{sigId+1} = strcat('s_', num2str(sigId));
        end
end

Insig_org = load(sigfilenames{1}, '-ascii');

scaling=1e-6;
nb_ctr_pts = 30; %10;
input_ranges = [Insig_org(1:nb_ctr_pts,2)-0.3 Insig_org(1:nb_ctr_pts,2)+0.3];
%input_ranges = [0 3];

Insig(:,1) = scaling*Insig_org(1:nb_ctr_pts, 1);
timepoints = Insig(:,1);
simTime = Insig(end,1);
input_signal_names = {'In1'};
signal_gen_method = {'linear'};

%%%% grid size column on the range of each input signal
gridsize_vector = [ 4  ];
MetaObj = MetaFalsify(model_name,IO_signal_names);

% specify the simulation time
MetaObj.SimTimeSetUp(0:1e-9:simTime);

% specify the class of input signals
MetaObj.InputSignalSetUp(input_signal_names,signal_gen_method,nb_ctr_pts,input_ranges,timepoints);

