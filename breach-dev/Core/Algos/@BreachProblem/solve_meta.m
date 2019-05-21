function res = solve_meta(this)

% display header
if ~strcmp(this.display,'off')
    fprintf('Running Metaheuristics\n');   
end

opt = this.solver_options;

if opt.num_corners>0
    res= this.solve_corners();
end

if ~strcmp(this.display,'off')
    this.display_status();
    this.Display_Best_Results(res.fval, res.x);
end

qr_step = 1;
while true
    
    %% Quasi-random phase
    this.setup_quasi_random('quasi_rand_seed',qr_step,'num_quasi_rand_samples',opt.num_quasi_rand_samples);
    res = this.solve_quasi_random();
    qr_step = qr_step+ opt.num_quasi_rand_samples;    
    
    %% Local phase
    x0 = res.x; % best x from last quasi-random phase
    this.setup_nelder_mead(x0, 'MaxFunEvals', opt.local_max_obj_eval);
    res = this.solve_nelder_mead();
    
    %% Disp 
    if this.stopping()
        break;
    else
        this.Display_Best_Results(res.fval, res.x);        
    end
end
end




