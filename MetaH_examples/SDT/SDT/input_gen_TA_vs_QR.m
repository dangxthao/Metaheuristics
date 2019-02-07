clear;
init_SDT;


%%
i0 = 3;
st = {};
for ii = 1:6
    st{ii} =  [ 'In1_dt' num2str(ii+i0) '+']; 
end
st{ii} =  [ 'In1_dt' num2str(ii+i0) '> 8e-6']; 
req1 = unsplit(st,'');
st{ii} =  [ 'In1_dt' num2str(ii+i0) '< 16e-6']; 
req2 = unsplit(st,'');

%%
i0 = i0+6;
st = {};
for ii = 1:6
    st{ii} =  [ 'In1_dt' num2str(ii+i0) '+']; 
end
st{ii} =  [ 'In1_dt' num2str(ii+i0) '> 8e-6']; 
req3 = unsplit(st,'');
st{ii} =  [ 'In1_dt' num2str(ii+i0) '< 16e-6']; 
req4 = unsplit(st,'');

%% Nah
i0 = i0+6;
st = {};
for ii = 1:6
    st{ii} =  [ 'In1_dt' num2str(ii+i0) '+']; 
end
st{ii} =  [ 'In1_dt' num2str(ii+i0) '> 8e-6']; 
req5 = unsplit(st,'');
st{ii} =  [ 'In1_dt' num2str(ii+i0) '< 16e-6']; 
req6 = unsplit(st,'');

%% My. After that I'll write a loop, promise.
i0 = i0+6;
st = {};
for ii = 1:6
    st{ii} =  [ 'In1_dt' num2str(ii+i0) '+']; 
end
st{ii} =  [ 'In1_dt' num2str(ii+i0) '> 8e-6']; 
req7 = unsplit(st,'');
st{ii} =  [ 'In1_dt' num2str(ii+i0) '< 16e-6']; 
req8 = unsplit(st,'');


%%
reqs ={req1,req2,req3,req4, req5,req6, req7, req8};
R0 = BreachRequirement(reqs(1:8));

%%
figure;
for ii = 1:5
    R = R0.copy();
    Ms(ii) = MetaFalsifSDT(ii-1);
    Bs(ii) = Ms(ii).Br.copy();
    
    Bs(ii).SimInputsOnly = true;
    
    %Bs(ii).QuasiRandomSample(5);
    
    Bs(ii).Sim();
    [v(ii),V(ii,:)]= R.Eval(Bs(ii));   
    Bs(ii).PlotSignals('In1', [], {'b'});
end
%% Timeless

Mt = MetaFalsifSDT(0,false);
Bt = Mt.Br;

Bt.QuasiRandomSample(100);
Bt.SimInputsOnly = true;
Bt.Sim();
figure;
Bt.PlotSignals('In1', [], {'b'});
R = R0.copy();
R.Eval(Bt)

val = min(R.traces_vals,[], 2)';
ipos = find(val>0);

Bok = Bt.ExtractSubset(ipos);
Bok.PlotSignals('In1',[], {'g'});
BreachSamplesPlot(R);

%% 
return

%%


