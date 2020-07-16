function [out] = quad_mem_NN(p2, p3)

load('quad_NN_mem/net_for_hadi_memory.mat')

p1 = 0.5 * ones(1, length(p2));

p_all_1=[p1;[0,p1(1:(end-1))];[0,0,p1(1:(end-2))];[0,0,0,p1(1:(end-3))]];
p_all_2=[p2;p3];
p_all_3=[[0,p2(1:(end-1))];[0,p3(1:(end-1))]];
p_all_4=[[0,0,p2(1:(end-2))];[0,0,p3(1:(end-2))]];
p_all_5=[[0,0,0,p3(1:(end-3))];[0,0,0,p3(1:(end-3))]];

p_all=[p_all_1;p_all_2;p_all_3;p_all_4;p_all_5];

y_out=sim(net,p_all);

out = y_out(end);

end
