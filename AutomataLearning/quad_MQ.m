function [out] = NN_matlab_MQ(in2, in3)
%% simulate delays

load('nets_for_hadi.mat')

in1 = 0.5 * ones(1, length(in2));

in_all = [in1; in2; in3];

out1 = sim(net_hadi_1_layer, in_all);

out = out1(end);

end