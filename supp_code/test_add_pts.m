
new_pts = falsif_pb.X_log;
num_iterations = size(new_pts,2);

for i = 1:num_iterations
   CBS.AddPoint(new_pts(:,i));
end

coverage = CBS.ComputeLogCellOccupancyCoverage;