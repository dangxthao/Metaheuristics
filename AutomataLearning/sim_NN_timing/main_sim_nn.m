%% Simulating a standalone NN in Matlab vs Simulink (timing)

% This script aims to report the computational times for the simulation of
% a NN in Simulink and Matlab. The first option is to use Matlab object (network)
% and the second is to use a Simulink block (constructed via gensim).

% Usage: run the entire file
%% Initialization

clear
close
clc

%% Select example net

example=2;
if example==1
    mat_file='nn_2layers.mat';
    model_name='testing_time_net_2layers'
elseif example==2
    mat_file='nn_3layers.mat'
    model_name='testing_time_net_3layers'
end

load(mat_file)
% create net
% gensim(net)

%% simulate with delays


%% find info

view(net)
num_input_layers=net.numInputs;
if num_input_layers==1
    num_inputs=net.inputs{num_input_layers}.size;
else
    for i=1:num_input_layers
        num_inputs=net.inputs{i}.size;
    end
end
fprintf('The num of inputs is %i.\n\n',num_inputs);

%% Timing analysis

no_iterations=20;
for i=1:no_iterations
    tic
    if i==1 && example==1
        in1=[0.59;0.47;0.29;0.28;0.17;0.58];
    elseif i>1 && example==1
        in1=rand(1,6)'*10;
    elseif i==1 && example==2
        in1=[0.04;0.048;0.46;0.82;0.7;0.55;0.2;0.64;0.045;0.72];
    elseif i>1 && example==2
        in1=rand(1,10)'*10;
    end
    out1=sim(net,in1);
    t1=toc;
    
    tic;
    sim(model_name);
    t2=toc;
    
    fprintf('Test %i -- Matlab: %.5f sec vs. Simulink %.5f sec.\n\n',i,t1,t2)
end

%% simulate delays

load('net_object.mat')
tic
% in_net=[0.59;0.47;0.29;0.28;0.17;0.58];
in_rand=rand(10000,1)'*10;
in1=in_rand(1:(end-2));
in2=in_rand(2:(end-1));
in3=in_rand(3:(end));

in_rand=rand(10000,1)'*10;
in4=in_rand(1:(end-2));
in5=in_rand(2:(end-1));
in6=in_rand(3:(end));
in_all=[in1;in2;in3;in4;in5;in6];
out1=sim(net,in_all);
t1=toc

%% bad solution not working
model_name='NN_2019';
model_name='NN_2019_breach';


tic;
%In1=in1;
sim(model_name);
t2=toc