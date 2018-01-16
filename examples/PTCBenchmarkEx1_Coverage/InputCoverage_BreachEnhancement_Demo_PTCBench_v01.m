% This script demonstrates the input coverage-based testing procedure on
% a powertrain control (PTC) benchmark example. The model is described in
% the following:
%
% "Powertrain Control Verification Benchmark", X. Jin, J. V. Deshmukh, 
% J. Kapinski, K. Ueda, K. Butts. In Hybrid Systems: Computation and 
% Control (HSCC) 2014.
%
% J. Kapinski
% Toyota Technical Center
% Last modified: 8-2016
%

clear all
bdclose all
close all

ticpointer = tic;

currentPath = pwd;
temp = strsplit(currentPath,'\');
parentDir = strjoin(temp(1:length(temp)-2),filesep);

%% Breach Interface Object Creation
model_name = 'AbstractFuelControl_M1';
% total simulation time
simTime = 50 ; 
% time to introduce sensor failure (default sensor failure won't happen)
fault_time = 100; 
% Simulink initialization phase
measureTime = 1;  
spec_num = 1; %specification measurement
fuel_inj_tol = 1.0; 
MAF_sensor_tol = 1.0;
AF_sensor_tol = 1.0;

BrFC = CoverageBreachSet(model_name,{});
BrFC.SetTime([0 simTime]);

%% Make 2D parameter space and plot coverage as points are added

% First, plot coverage measures for the case where we don't snap to grid
Br2D = BrFC.copy();

pedal_gen = var_cp_signal_gen({'In1'},1,{'previous'});
engine_gen = fixed_cp_signal_gen({'In2'},1,{'previous'});
InputGen = BreachSignalGen({pedal_gen, engine_gen});
InputGen.PrintParams();
Br2D.SetInputGen(InputGen);
Br2D.SetParam({'In2_u0'},[5]);
Br2D.SetParam({'In1_u0'},[5]);
rangemax = 10; epsi = 1; delta = 5;
Br2D.SetParamRanges({'In1_u0','In2_u0'},[0 rangemax;0 rangemax]);
Br2D.SetEpsGridsize([epsi epsi]);
Br2D.SetDeltaGridsize([delta delta]);
Br2D.SetSnapToGrid(true);

num_cells_per_dim = ceil(rangemax/epsi);
h1 = figure; hold on;
for ind = 1:num_cells_per_dim+1
    line_pos = (ind-1)*epsi;
    plot([0 10],[line_pos line_pos],':b');
    plot([line_pos line_pos],[0 10],':b');
end
num_cells_per_dim = ceil(rangemax/delta);
for ind = 1:num_cells_per_dim+1
    line_pos = (ind-1)*delta;
    plot([0 10],[line_pos line_pos],'-b');
    plot([line_pos line_pos],[0 10],'-b');
end
title('Parameter Space');
xlabel('p1');
ylabel('p2');

h2 = figure; hold on;
subplot(3,1,1); hold on;
title('Cell Occupancy Coverage')
xlabel('Sample number'); ylabel('Coverage');
subplot(3,1,2); hold on;
title('Log Cell Occupancy Coverage')
xlabel('Sample number'); ylabel('Coverage');
subplot(3,1,3); hold on;
title('Entropy Coverage')
xlabel('Sample number'); ylabel('Coverage');

% Reset random number generator to produce repeatable results
rng(1);
for ind = 1:100;
    new_point = rand(2,1)*rangemax;
    [added_flag,new_point] = Br2D.AddPoint(new_point);
    if added_flag
        figure(h1); plot(new_point(1),new_point(2),'xk');
        figure(h2); subplot(3,1,1); plot(Br2D.NumPoints,Br2D.ComputeCellOccupancyCoverage,'.k');
        subplot(3,1,2); plot(Br2D.NumPoints,Br2D.ComputeLogCellOccupancyCoverage,'.k');
        subplot(3,1,3); plot(Br2D.NumPoints,Br2D.ComputeEntropyCoverage,'.k');
    end
end

% Next, plot coverage measures for the case where we do snap to grid


clear all

currentPath = pwd;
temp = strsplit(currentPath,'\');
parentDir = strjoin(temp(1:length(temp)-2),filesep);

%% Breach Interface Object Creation
model_name = 'AbstractFuelControl_M1';
% total simulation time
simTime = 50 ; 
% time to introduce sensor failure (default sensor failure won't happen)
fault_time = 100; 
% Simulink initialization phase
measureTime = 1;  
spec_num = 1; %specification measurement
fuel_inj_tol = 1.0; 
MAF_sensor_tol = 1.0;
AF_sensor_tol = 1.0;

BrFC = CoverageBreachSet(model_name,{});
BrFC.SetTime([0 simTime]);
Br2D = BrFC.copy();

% Consider this to do a deep copy:
% http://undocumentedmatlab.com/blog/general-use-object-copy

pedal_gen = var_cp_signal_gen({'In1'},1,{'previous'});
engine_gen = fixed_cp_signal_gen({'In2'},1,{'previous'});
InputGen = BreachSignalGen({pedal_gen, engine_gen});
InputGen.PrintParams();
Br2D.SetInputGen(InputGen);
Br2D.SetParam({'In2_u0'},[5]);
Br2D.SetParam({'In1_u0'},[5]);
rangemax = 10; epsi = 1; delta = 5;
Br2D.SetParamRanges({'In1_u0','In2_u0'},[0 rangemax;0 rangemax]);
Br2D.SetEpsGridsize([epsi epsi]);
Br2D.SetDeltaGridsize([delta delta]);
Br2D.SetSnapToGrid(false);

num_cells_per_dim = ceil(rangemax/epsi);
h1 = figure; hold on;
for ind = 1:num_cells_per_dim+1
    line_pos = (ind-1)*epsi;
    plot([0 10],[line_pos line_pos],':b');
    plot([line_pos line_pos],[0 10],':b');
end
num_cells_per_dim = ceil(rangemax/delta);
for ind = 1:num_cells_per_dim+1
    line_pos = (ind-1)*delta;
    plot([0 10],[line_pos line_pos],'-b');
    plot([line_pos line_pos],[0 10],'-b');
end
title('Parameter Space');
xlabel('p1');
ylabel('p2');

h2 = figure; hold on;
subplot(3,1,1); hold on;
title('Cell Occupancy Coverage')
xlabel('Sample number'); ylabel('Coverage');
subplot(3,1,2); hold on;
title('Log Cell Occupancy Coverage')
xlabel('Sample number'); ylabel('Coverage');
subplot(3,1,3); hold on;
title('Entropy Coverage')
xlabel('Sample number'); ylabel('Coverage');

% Reset random number generator to produce repeatable results
rng(1);
for ind = 1:100;
    new_point = rand(2,1)*rangemax;
    [added_flag,new_point] = Br2D.AddPoint(new_point);
    if added_flag
        figure(h1); plot(new_point(1),new_point(2),'xk');
        figure(h2); subplot(3,1,1); plot(ind,Br2D.ComputeCellOccupancyCoverage,'.k');
        subplot(3,1,2); plot(ind,Br2D.ComputeLogCellOccupancyCoverage,'.k');
        subplot(3,1,3); plot(ind,Br2D.ComputeEntropyCoverage,'.k');
    end
end


%% Run model and check coverage

pedal_gen = var_cp_signal_gen({'In1'},3,{'linear'});
engine_gen = fixed_cp_signal_gen({'In2'},3,{'previous'});
InputGen = BreachSignalGen({pedal_gen, engine_gen});
InputGen.PrintParams();

BrFC.SetInputGen(InputGen);
BrFC.SetParam({'In2_u0','In2_u1','In2_u2'},[1000 1000 1000]);
BrFC.SetParam({'In1_u0','In1_dt0','In1_u1','In1_dt1','In1_u2'},[30 40 30 10 30]);
%BrFC.SetParamRanges({'In1_u0','In1_u1','In1_u2'},[0 61.19;0 61.19;0 61.19]);
BrFC.SetParamRanges({'In1_u0','In1_u1','In1_u2'},[-1 61.19;-1 61.19;-1 61.19]);

BrFC.SetEpsGridsize([10 15 5]);
BrFC.SetDeltaGridsize([10 20 20]);
BrFC.SetSnapToGrid(true);

% Test the case where you don't snap to grid:
% BrFC.AddPoint([1 1 1]);
% BrFC.AddPoint([1.3 1.2 1.1]);

BrFC.NewRun({'In1_u0','In1_dt0','In1_u1','In1_dt1','In1_u2','In2_u0','In2_u1','In2_u2'},[30 40 30 10 30 1000 1000 1000]);
BrFC.NewRun({'In1_u0','In1_dt0','In1_u1','In1_dt1','In1_u2','In2_u0','In2_u1','In2_u2'},[1 40 1 10 1 1000 1000 1000]);

% Set the SnapToGrid flag and add two points

fprintf('Number of populated cells: %i \n',BrFC.NumPoints);
BrFC.DisplayPoints;
fprintf('Cell Occupancy Coverage: %f \n',BrFC.ComputeCellOccupancyCoverage);
fprintf('Log of Cell Occupancy Coverage: %f \n',BrFC.ComputeLogCellOccupancyCoverage);
fprintf('Entropy Coverage: %f \n',BrFC.ComputeEntropyCoverage);






