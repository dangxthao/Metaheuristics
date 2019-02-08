function StatFalsObj=PseudoRandomCall(StatFalsObj, CBS, phi, time_lim, nb_samples, nb_hits)
 % NewSys = CallPseudo(Sys, xlog_vec, xbest_vec)
 % function: run pseudo-random sampling
 %
 % Inputs/Outputs:
 % Sys: CoverageBreachSet object to which new samples are added.
 % Outputs:
 % NewSys: New CoverageBreachSet object after adding all the new points.
 
 
 %global Out
 


CBS.SetSnapToGrid(true);
    
max_sim = inf; %maximal number of simulations

%tic

%w_rob=0.5; % weight for robustness

% since this is pseudo-random sampling only, without classification
% we call this function with init_sim = max_sim 
% init_sim=nb sim required for classification



ip = CBS.VaryingParamList;
param_names = CBS.P.ParamList(1,ip);
param_ranges = [CBS.LowerLeftCorner(),CBS.UpperRightCorner()];  
StatFalsObj.nominal_ranges = param_ranges;
            
[StatFalsObj,list,falsified,nb,falsi_point] = StatFalsObj.PseudoRandSamp(CBS,param_names,param_ranges,phi,nb_samples,time_lim,nb_hits);

if nb>0
   StatFalsObj.new_samples=list;
   
   [newminrob, min_id] = min(list.vals)
   
   if (~isempty(StatFalsObj.lower_bounds)) 
     if ( StatFalsObj.lower_bounds.vals(1,:) > newminrob )
       StatFalsObj.lower_bounds.vals(1,:) = newminrob;
       StatFalsObj.lower_bounds.pts(1,:) = list.pts(min_id,:);
     end
   else
     StatFalsObj.lower_bounds.vals(1,:) = newminrob;
     StatFalsObj.lower_bounds.pts(1,:) = list.pts(min_id,:); 
   end
end




%StatFalsify([],CBS,phi,w_rob,max_sim,max_sim,time_lim);

% time = toc;
% fprintf(1, 'Computation time = %f seconds \n',time);