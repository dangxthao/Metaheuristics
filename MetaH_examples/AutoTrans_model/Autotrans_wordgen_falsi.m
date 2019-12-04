%% TA based signal generator setup 
%
init_TA_signal_gen;


%%  Checking reachable labels
STL_ReadFile('Autotrans_req.stl');

%% 

S2 = S0.copy();
mdl = 'Autotrans_wordgen';
Ba = BreachSimulinkSystem(mdl);
Ba.SetTime(time);
Ba.SetInputGen(S2);
Ba.SetParamRanges([pevts pbranching], [0 1]);
Ba.Sim();


%% 
R = BreachRequirement(never_gear3_and_speed_low);
pb = FalsificationProblem(Ba, R);

pb.solve();
