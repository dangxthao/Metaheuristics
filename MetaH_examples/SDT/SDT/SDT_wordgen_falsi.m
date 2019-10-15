close all;
clear all;
clc;
warning('OFF', 'ALL')

%% Setup DeltaSigma model
init_SDT
phi = STL_Formula('notsaturation', 'alw(OutSat[t]<2)');
R = BreachRequirement(phi); 

%% Wordgen generator

addpath('../../../wordgen');
num_evt = 50;
sg = var_cp_signal_gen('In1',num_evt+2, 'linear');

%% 
pg = TA_param_gen('In1','../../../wordgen/hscc20.json', num_evt);
pg.wordgen_exe = '../../../wordgen/wordgen';
sdt_template = '%g[b]%g[c]%g[d]';
num = 3;
while num<num_evt
    num = num +4;
    sdt_template = [sdt_template '%g[a]%g[b]%g[c]%g[d]']; % template for lasso init
end
sdt_template = sdt_template(1:5*num_evt);
pg.set_template_in(sdt_template);
pg.template_in = regexprep(pg.template_in,'\[(\w+)\]', '\[_\]'); % erase letters 


%%

time = linspace(0,1e-5, 10000);
S = BreachSignalGen(sg);

%%
B = BP2.copy();
B.SetInputGen(S);
B.SetParamGen(pg);

%%
%% Testing against frequency
B.SetParam({'time_scale'}, [1e-8 : 1e-8 : 1e-7]);
B.SetParam({'beta'}, [-3 : 1 : 0], 'combine');
B.SetParam({'alpha'}, [.1 1 10], 'combine');





%%
B.SetTime(time);
B.Sim();
B.PlotSignals();

R.Eval(B);
%%
F = BreachSamplesPlot(R); 
F.set_y_axis('alpha');
F.set_x_axis('time_scale');
F.set_z_axis('beta');



