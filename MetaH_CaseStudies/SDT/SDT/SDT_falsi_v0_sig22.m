close all;
clear all;
%clc;
warning('OFF', 'ALL')

%% This script set up the falsification problem 
%% for the SDT model

addpath('./Functions')
addpath('./ExampleBand-Pass')
addpath('./ExampleLow-Pass')
addpath('./periodic.signals')
addpath('/Users/thaodang/breach-dev')


addpath('/Users/thaodang/Metaheuristics/supp_code')
addpath('/Users/thaodang/Metaheuristics/src')
addpath('/Users/thaodang/Metaheuristics/breach-dev')
addpath('.')
        
InitBreach('/Users/thaodang/Metaheuristics/breach-dev',true); % forces initialization from folder in Metaheuristics
BP2param

model_name = 'BP2_in';
fprintf('\n Creating breach interface with simulink model %s\n',model_name)


IO_signal_names = {'In1','OutSat'};

%% Specifying STL formula
%fprintf('\n The STL formula is\n ')
%phi = STL_Formula('notsaturation', 'alw(OutSat[t]<1)');
    phi = STL_Formula('notsaturation', 'alw(OutSat[t]<1.145)');

%% Set input signals

%%%%
for sigId = 0:51
        %sigId = 1 %sigId = 0:51
        if (sigId < 10)
                sigfilename = strcat('s_0', num2str(sigId));
        else
                sigfilename = strcat('s_', num2str(sigId));
        end
        if (sigId < 10)
                sigfilename = strcat('s_0', num2str(sigId));
        else
                sigfilename = strcat('s_', num2str(sigId));
        end

        Insig_org = load(sigfilename, '-ascii');
        %scaling=0.65e-7; 
            scaling=1e-6; 


        nb_ctr_pts = 30; %10;
        input_ranges = [Insig_org(1:nb_ctr_pts,2)-0.3 Insig_org(1:nb_ctr_pts,2)+0.3];
        %input_ranges = [0 3];



        Insig(:,1) = scaling*Insig_org(1:nb_ctr_pts, 1);
        timepoints = Insig(:,1);


        simTime = Insig(end,1);
        fprintf('\n Simulation time horizon is %d seconds\n',simTime)

        %signal_types = { 'UniStep', 'UniStep' };
        %%%% thao signal_types = { 'VarStep', 'VarStep' };
        input_signal_names = {'In1'};
        signal_gen_method = {'linear'}; 


        %%%% grid size collumn on the range of each input signal
        gridsize_vector = [ 4 ];


        %%%% Once the above system specifications and falsification options are given,
        %%%% the following part of the code need not be modified by the user
        MetaObj = MetaFalsify(model_name,IO_signal_names);
        % specify the simulation time
        %%%MetaObj.SimTimeSetUp(0:1e-9:simTime);
        MetaObj.SimTimeSetUp(0:1e-9:simTime);



        % specify the class of input signals
        % time pattern fixed
        timeFixed = true;
        MetaObj.InputSignalSetUp(input_signal_names,signal_gen_method,nb_ctr_pts,input_ranges,timepoints,timeFixed);

        % specify the property to falsify
        MetaObj.STLFormulaSetUp(phi);

        % set up a grid on the input ranges, to estimate coverage
        MetaObj.GridSetUp(gridsize_vector,nb_ctr_pts,timeFixed);        


        %% Start the falsification process
        %%%[r,falsified,total_nb_sim,falsi_point] = MetaObj.MetaCall();

        %%% Set up falsification options

            %%%% Search Monitoring Parameters 
            %% cov_epsilon = input('Specify coverage increase threshold : '); 
            MetaObj.cov_epsilon = 1e-3;
            %% min robustness decrease in percentage
            MetaObj.rob_epsilon_percent = 0.05;
            %% min robustness stagnant monitoring window
            MetaObj.rob_stagnant_win = 1 
            %% coverage stagnant monitoring window
            MetaObj.cov_monitoring_win = 1;

            %%% Options for picking initial conditions
            MetaObj.re_init_strategy = 2; %2; 
            % re_init_strategy=0 to pick randomly from the whole space
            % re_init_strategy=1 to pick randomly from xlog
            % re_init_strategy=2 to pick randomly from xbest

            % re_init_num_xbest: window of choice from xbest, for picking initial point         
            MetaObj.re_init_num_xbest = 200;

            % num_solvers=nb of solvers %%other than pseudorandom sampling
            % TODO add solver_list, and init num_solver as numel(solver_list)
            MetaObj.num_solvers=4; 

            %% limit on nb of solver calls
            MetaObj.nb_solver_calls = 2  %1 %30

            MetaObj.start_solver_index = 2; %3; %1; %PR 0, cmaes 1, SA 2, GNM 3 

            MetaObj.solver_time = [ 300 300 300 300 ];
            MetaObj.max_obj_eval = [ 200 200 200 200 ];
            MetaObj.seed = 5000;


        fprintf('\n The falsification problem by metaheuristics is\n ')
        MetaObj

        fprintf('\n sigId is \n ')
        sigId
        
        
        %%%% Run the falsification
        MetaObj.MetaCall();

        %MetaObj.MetaSetupRun(Sys, phi)
        %MetaObj.MetaSetupRun(MetaObj.Br, phi)

end
        







