function x0 = initSolver(xlog_vec, xbest_vec, strategy_id, winlen)
 % initSolver(xlog_vec, xbest_vec)
 % function: pick an initial point for solvers 
 %
 % Inputs:
 % xlog_vec: explored points
 % xbest_vec: best points from previous solver runnings 
 % strategy_id: choice of strategy
 % winlen: window of choice from xbest 

    switch strategy_id
        case 1 %init from xlog 
                nb_pt_xlog=size(xlog_vec,2);
                rand_id_xlog = max(1, floor(rand*nb_pt_xlog));
                if (rand_id_xlog<1 || rand_id_xlog>nb_pt_xlog) 
                 error('Error in rand_id_xlog');
                end
                %xlog_vec 
                x0 = xlog_vec(:,rand_id_xlog);
                
        case 2 %init from the last segment of size winlen of xbest 
                nb_pt_xbest=size(xbest_vec,2); 
                
                winlen1 = winlen;
                if (nb_pt_xbest<winlen)
                    winlen1 = nb_pt_xbest;
                end 
                
                rand_id_xbest = nb_pt_xbest - floor(rand*winlen1);  

                if (rand_id_xbest<0 || rand_id_xbest>nb_pt_xbest)
                 error('Error in rand_id_xbest');
                end

                x0 = xbest_vec(:,rand_id_xbest);

        otherwise
            error('error in strategy_id')
    disp('Initial point :');
    x0
    
    end %end of switch

    