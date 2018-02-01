function CallPseudo(CBS, phi, time_lim)
 % NewSys = CallPseudo(Sys, xlog_vec, xbest_vec)
 % function: run pseudo-random sampling
 %
 % Inputs/Outputs:
 % Sys: CoverageBreachSet object to which new samples are added.
 % Outputs:
 % NewSys: New CoverageBreachSet object after adding all the new points.
 
 
 global Out
 
%time_lim = input('\n Specify time limit of computation in seconds\n');
%time_limit = inf; %computation time limit

snap_grid = 'y';
switch snap_grid
    case 'y'
    CBS.SetSnapToGrid(true);
    case 'n'
    CBS.SetSnapToGrid(false);
    otherwise
        error('no epsilon resolution specified')
end

max_sim = inf; %maximal number of simulations

tic

w_rob=0.5; % weight for robustness

% since this is pseudo-random sampling only, without classification
% we call this function with init_sim = max_sim 
% init_sim=nb sim required for classification
Out = StatFalsify(Out,CBS,phi,w_rob,max_sim,max_sim,time_lim);

time = toc;
fprintf('Computation time = %f seconds \n',time);