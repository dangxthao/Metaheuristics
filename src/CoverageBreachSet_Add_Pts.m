function NewSys = CoverageBreachSet_Add_Pts(Sys,new_pts)
 % NewSys = add_pts(Sys,new_pts)
 % function: Adds points to a CoverageBreachSet object.
 %
 % Inputs:
 % Sys: CoverageBreachSet object to which points have to be added.
 % new_pts: Matrix whose column vectors are the set of all new points to be
 %          added.
 % Output
 % NewSys: New CoverageBreachSet object after adding all the new points.
 
    num_iterations = size(new_pts,2);
    NewSys = Sys.copy();
    for i = 1:num_iterations
       %new_pts(:,i) 
       NewSys.AddPoint(new_pts(:,i));
    end

 %coverage = CBS.ComputeLogCellOccupancyCoverage;