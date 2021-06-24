function [out] = NN_matlab_MQ(in)
%% simulate delays

load('quad_NN/nets_for_hadi.mat')

in1 = 0.5 * ones(1, length(in) - 1);
in2 = in(1:end-1);
in3 = in(2:end);

in_all = [in1; in2; in3];

out1 = sim(net_hadi_1_layer, in_all);

out = out1(end);

end