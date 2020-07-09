function [out] = NN_matlab_MQ(in)
%% simulate delays

load('net_object.mat')

% in_net=[0.59;0.47;0.29;0.28;0.17;0.58];
in_rand = in;

in1 = in_rand(1:(end-2));
in2 = in_rand(2:(end-1));
in3 = in_rand(3:(end));

% in4 = in_rand(1:(end-2));
% in5 = in_rand(2:(end-1));
% in6 = in_rand(3:(end));

in_all = [in1; in2; in3; in1; in2; in3];
out1 = sim(net, in_all);
out = out1(end);
end
