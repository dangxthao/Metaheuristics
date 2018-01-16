% This script demostrates how to use the coverage computation features in
% the CoverageBreachSet class. The purpose is to be able to include a
% collection of points from the input signal space and compute various
% coverage measures, based on the distribution of points.
%
% J. Kapinski
% Toyota
% 4-2017
%

clear all
bdclose all
close all
InitBreach

%% Breach Interface Object Creation
model_name = 'ContinuousExample';

% total simulation time
simTime = 10 ; 
BrSys = CoverageBreachSet(model_name,{});
BrSys.SetTime([0 simTime]);

%% Set input signals
InputGen.type = 'UniStep';
N = 2; % Number of control points
InputGen.cp = N;
BrSys.SetInputGen(InputGen);

%% Specifying parameters
ulim = [0, 10];

for i = 0:N-1
    signal{1,i+1} = strcat('u_u',num2str(i));
end

BrSys.SetSnapToGrid(false);

BrSys.SetParamRanges(signal,ones(N,1)*ulim);
BrSys.SetEpsGridsize(1*ones(N,1));
BrSys.SetDeltaGridsize(2*BrSys.epsgridsize);

%% Add points to space and plot coverage measures

rng(1);

EntropyIters = [];
LogCellOccupancyIters = [];
CellOccupancyIters = [];

figure; hold on;

for ind = 1:100
    newpoint = 10*rand(2,1);
    BrSys.AddPoint(newpoint);
    plot(newpoint(1),newpoint(2),'k.');
    EntropyIters = [EntropyIters BrSys.ComputeEntropyCoverage];
    LogCellOccupancyIters = [LogCellOccupancyIters BrSys.ComputeLogCellOccupancyCoverage];
    CellOccupancyIters = [CellOccupancyIters BrSys.ComputeCellOccupancyCoverage];
end

% Plot delta grid over plot of points
for xdim = 0:BrSys.deltagridsize(1):10
    plot([xdim xdim],[0 10],'k');
end
for ydim = 0:BrSys.deltagridsize(2):10
    plot([0 10],[ydim ydim],'k');
end
xlabel('u_0');
ylabel('u_1');
title('Test Points Added to 2D Space');

figure;
subplot(3,1,1)
title('Comparison Between Several Coverage Measures');
plot(EntropyIters,'.')
ylabel('Entropy Coverage')
subplot(3,1,2)
plot(CellOccupancyIters,'.')
ylabel('Cell Occupancy Coverage')
subplot(3,1,3)
plot(LogCellOccupancyIters,'.')
ylabel('Log Cell Occupancy Coverage')
xlabel('Iteration');

fontsize=15;
set(findall(gcf,'type','text'),'fontSize',fontsize,'fontWeight','bold');
set(findall(gcf,'type','axes'),'fontSize',fontsize,'fontWeight','bold');

