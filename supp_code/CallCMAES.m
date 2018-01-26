function CallCMAES(falsif_pb, phi, time_lim)
 % CallCMAES(falsif_pb, phi, time_lim)
 % function: run CMAES 
 %
 % Inputs/Outputs:
 % falsif_pb: falsification problem class 
 % phi: STL formula 
 % time_lim: limit on computation time
 
 
%time_lim = input('\n Specify time limit of computation in seconds\n');
%time_limit = inf; %computation time limit

falsif_pb.solver_options.SaveVariables = 'off';
%falsif_pb.solver_options.SaveVariables = 'on';

max_sim = inf; %maximal number of simulations

%% Thao uncommented this to allow automatic calls 
% fprintf('\n Choose one of the following seeds for pseudorandom sampling:\n')
% r = input('0, 5000, 10000 or 15000\n');
r = abs(round(rand*100)+1)
rng(r,'twister');  
tic

%fprintf('\n Choose one of the following seeds for cmaes:\n')
%r = input('Choose a non-negative integer for cmaes: ');
r = round(rand*10000000000);
falsif_pb.solver_options.Seed = r;


disp('Initialize from current points')
disp('Press 1: Yes; Press 0: No')
init_from_xlog = input('');

falsif_pb.solver_options.Restarts = 3;
falsif_pb.max_time = time_lim;

if (call_count>1 && init_from_xlog==1)
    rand_id_xlog = max(1, floor(rand*call_count))

    if rand_id_xlog>call_count 
     error('Error in rand_id_xlog');
    end
    
    xlog_vec(:,rand_id_xlog)
    falsif_pb.x0 = (xlog_vec(:,rand_id_xlog))';
end

timervar_2 = tic;
falsif_pb.solve()

%ctime = toc(timervar_2);
fprintf('Computation time = %f seconds \n',toc(timervar_2));