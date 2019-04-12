function x0 = initSolver(CBS,nbsamples,solver_index,num_solvers,SolverInfo,strategy_id,winlen)
 % initSolver(xlog_vec, xbest_vec)
 % function: pick an initial point for solvers 
 %
 % Inputs:
 % xlog_vec: explored points
 % xbest_vec: best points from previous solver runnings 
 % strategy_id: choice of strategy
 % winlen: window of choice from xbest 
 
rand_idvec = [];
x0 = [];
xlog_vec = [];
xbest_vec= [];


    switch strategy_id
        case 0 %init from xlogPR  
                
                %xlogPR_vec = Xlog.xlogPR;
                xlogPR_vec = SolverInfo(1).Xlog;
                nb_pt_xlogPR =size(xlogPR_vec,2);
                if (nbsamples>nb_pt_xlogPR)
                    nbsamples = nb_pt_xlogPR;
                end
                i=1; 
                itrial=1;
                while (i<=nbsamples && itrial<=2*nbsamples)
                    rand_id = max(1, floor(rand*nb_pt_xlogPR));
                    if (i==1)
                        rand_idvec = [rand_idvec; rand_id];
                        i=i+1;
                    else
                        if (isempty(find(rand_idvec == rand_id)))
                           i=i+1;
                           rand_idvec = [rand_idvec; rand_id];
                           x0i = xlogPR_vec(:,rand_id);
                           inRange = CBS.TestPointInRange(x0i);
                           if (inRange) 
                            x0 = [x0, x0i];
                           end
                        end    
                    end
                    if (rand_id<1 || rand_id>nb_pt_xlogPR)
                        error('Error in rand_id_xlogPR');
                    end
                    itrial=itrial+1;
                end %end while
                
        case 1 %init from xlog 
%                 if (solver_index == 1 ) 
%                     %xlog_vec = [xlog_vec, Xlog.xlogSA, Xlog.xlogGNM];
%                     xlog_vec = [xlog_vec, Xlog(2,:), Xlog(3,:)];
%                 end
%                 if (solver_index == 2 ) 
%                     %xlog_vec = [xlog_vec, Xlog.xlogCMAES, Xlog.xlogGNM];
%                     xlog_vec = [xlog_vec, Xlog(1,:), Xlog(3,:)];
%                 end
%                 if (solver_index == 3 ) 
%                     %xlog_vec = [xlog_vec, Xlog.xlogCMAES, Xlog.xlogSA];
%                     xlog_vec = [xlog_vec, Xlog(1,:), Xlog(2,:)];
%                 end
                
                %%% collecting xlog but not from the current solver
                for (ii=1:1:num_solvers)
                    if (~(ii==solver_index)) 
                      xlog_vec = [xlog_vec, SolverInfo(ii).Xlog];
                    end
                end
                
                nb_pt_xlog=size(xlog_vec,2);
                if (nbsamples>nb_pt_xlog)
                    nbsamples = nb_pt_xlog;
                end
                i=1;
                itrial=1;
                while (i<=nbsamples && itrial<=2*nbsamples)
                    rand_id = max(1, floor(rand*nb_pt_xlog));
                    if (i==1)
                        rand_idvec = [rand_idvec; rand_id];
                        x0i = xlog_vec(:,rand_id);
                        inRange = CBS.TestPointInRange(x0i);
                        if (inRange) 
                          x0 = [x0, x0i];
                        end
                        i=i+1;
                    else
                        if (isempty(find(rand_idvec == rand_id)))
                           i=i+1;
                           rand_idvec = [rand_idvec; rand_id];
                           x0i = xlog_vec(:,rand_id);
                           inRange = CBS.TestPointInRange(x0i);
                           if (inRange) 
                            x0 = [x0, x0i];
                           end
                        end    
                    end
                    if (rand_id<1 || rand_id>nb_pt_xlog) 
                        error('Error in rand_id_xlog');
                    end
                    itrial=itrial+1;
                end %end while
                
        case 2 %init from xbest of one solver chosen randomly                               
%                 
%                 nb_pt_xbest=size(xbest_vec,2)              
%                 winlen1 = winlen;
%                 if (nb_pt_xbest<winlen)
%                     winlen1 = nb_pt_xbest;
%                 end 
%                 
%                 if (nbsamples>nb_pt_xbest)
%                     nbsamples = nb_pt_xbest;
%                 end
                
                %nbsamples
                %strategy_id
                
                solversdone= zeros(num_solvers);  %[ 0 0 0 ];
                nbsolversdone = 0;
%                 if (size(Xbest.xbestCMAES,2)>0) 
%                     solversdone(1) = 1;
%                     nbsolversdone = nbsolversdone + 1;
%                 end
%                 if (size(Xbest.xbestSA,2)>0) 
%                     solversdone(2) = 1;
%                     nbsolversdone = nbsolversdone + 1;
%                 end
%                 if (size(Xbest.xbestGNM,2)>0) 
%                     solversdone(3) = 1;
%                     nbsolversdone = nbsolversdone + 1;
%                 end
                
%                 if (size(Xbest(2,:),2)>0) 
%                     solversdone(1) = 1;
%                     nbsolversdone = nbsolversdone + 1;
%                 end
%                 if (size(Xbest(3,:),2)>0) 
%                     solversdone(2) = 1;
%                     nbsolversdone = nbsolversdone + 1;
%                 end
%                 if (size(Xbest(4,:),2)>0) 
%                     solversdone(3) = 1;
%                     nbsolversdone = nbsolversdone + 1;
%                 end

                for ii = 1:1:(num_solvers)
                    if (size(SolverInfo(ii).Xbest,2)>0) 
                      solversdone(1) = 1;
                      nbsolversdone = nbsolversdone + 1;
                    end
                end
                
                
                itrial=1;
                while (itrial<=nbsamples && nbsolversdone>0)
                    %rand_id = nb_pt_xbest - floor(rand*winlen1); 
                    rand_solverid = randi(3); 
                    %rand_solverid = 3;
                    
                    %do not use xbest of the same solver
%                     if (rand_solverid==solver_index) 
%                         break
%                     end
                    
                    if (solversdone(rand_solverid) >0)
%                         switch rand_solverid 
%                             case 1 
                                nb_pt_xbest=size(SolverInfo(rand_solverid+1).Xbest,2);
                                if nb_pt_xbest>0
                                    rand_id = randi(nb_pt_xbest);
                                    if (rand_id<0 || rand_id>nb_pt_xbest)
                                        error('Error in rand_id_xbest');
                                    end
                                    xbest_vec = SolverInfo(rand_solverid+1).Xbest;
                                    x0i = xbest_vec(:,rand_id);
                                    xbest_vec(:,rand_id) = [];
                                    SolverInfo(rand_solverid+1).Xbest = xbest_vec;
                                end

%                             case 2  
%                                 nb_pt_xbest=size(Xbest.xbestSA,2);
%                                 if nb_pt_xbest>0
%                                     rand_id = randi(nb_pt_xbest);
%                                     if (rand_id<0 || rand_id>nb_pt_xbest)
%                                         error('Error in rand_id_xbest');
%                                     end
%                                     x0i = Xbest.xbestSA(:,rand_id);
%                                     Xbest.xbestSA(:,rand_id) = [];
%                                 end
%                             case 3
%                                 nb_pt_xbest=size(Xbest.xbestGNM,2);
%                                 if nb_pt_xbest>0
%                                     rand_id = randi(nb_pt_xbest);
%                                     if (rand_id<0 || rand_id>nb_pt_xbest)
%                                         error('Error in rand_id_xbest');
%                                     end
%                                     x0i = Xbest.xbestGNM(:,rand_id);
%                                     Xbest.xbestGNM(:,rand_id) = [];
%                                 end
%                             otherwise
%                                 error('rand_id')
%                         end

                        if nb_pt_xbest>0
    %                         rand_id
    %                         x0i
    %                         Xbest.xbestGNM
                            inRange = CBS.TestPointInRange(x0i);
                            if (inRange) 
                               x0 = [x0, x0i];
                            end
                        end
                        
                    end %if (nbsolversdone(rand_solverid) >0)
                    
                    itrial=itrial+1;
                end %end while

                

        otherwise
            error('error in reinit_strategy')
    
    
    end %end of switch
    
 
    