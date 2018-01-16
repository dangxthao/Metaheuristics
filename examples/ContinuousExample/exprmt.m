
setup
%% Specifying STL formula
phi1 = STL_Formula('a', 'not(ev_[6,7](y1[t] > 3))');
phi2 = STL_Formula('b', 'ev_[7,10](y1[t] < 0.5)');
phi = STL_Formula('phi', 'a or b');


%% Specifying parameters
ulim = [0, 10];

for i = 0:N-1
    signal{1,i+1} = strcat('u_u',num2str(i));
end

%% Setting CBS object parameters
CBS = BrSys.copy;
CBS.SetParamRanges(signal,ones(N,1)*ulim);
CBS.SetEpsGridsize(1*ones(N,1));
CBS.SetDeltaGridsize(2*CBS.epsgridsize);



%% Implementing falsification method

% The weigtage to robustness information during probabilistic sampling is
% set up as
w_rob = 0.5;




time_lim = input('\n Maximum time of computation (seconds) \n'); 

msg1 = sprintf('\nChoose a falsification method\n');
msg2 = sprintf('Press 1 : Pseudorandom sampling\n');
msg3 = sprintf('Press 2:  Classification guided sampling\n');
msg4 = sprintf('Press 3:  Global_nelder_mead\n');
msg5 = sprintf('Press 4:  CMA-ES\n');
msg6 = sprintf('Press 5:  simulannealbnd\n');

a = input([msg1,msg2,msg3,msg4,msg5,msg6]);

switch a 
    
    case 1
        max_sim = inf;
        r = input('\n Choose a seed (positive integer) for random sampling\n');
        rng(r,'twister');  
        tic
        Out = StatFalsify(CBS,phi,w_rob,max_sim,max_sim,time_lim);
        time = toc;
        fprintf('Computation time = %f seconds \n',time);
        
    case 2  
        snap_grid = input(['Ensure epsilon separation [y|n]\n',''],'s');
        switch snap_grid
            case 'y'
            CBS.SetSnapToGrid(true);
            case 'n'
            CBS.SetSnapToGrid(false);
            otherwise
                error('no epsilon resolution specified')
        end       
        max_sim = inf;
        init_sim = input('\n Enter initial number of samples\n');
        r = input('\n Choose a seed (positive integer) for random sampling\n');
        rng(r,'twister');  
        tic
        Out = StatFalsify(CBS,phi,w_rob,init_sim,max_sim,time_lim);
        time = toc;
        fprintf('Computation time = %f seconds \n',time);
        
    case 3
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('global_nelder_mead');
        falsif_pb.max_time = time_lim;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        
    case 4
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('cmaes');
        r = input('\n Choose a seed (positive integer) for random sampling\n');
        falsif_pb.max_time = time_lim;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        
    case 5
        falsif_pb = FalsificationProblem(CBS, phi);  
        falsif_pb.setup_solver('simulannealbnd');
        falsif_pb.max_time = time_lim;
        falsif_pb.solve()
        trace = falsif_pb.GetBrSet_False();
        
    otherwise
            error('no input')
end     
                       