


load('s_00', '-ascii');
p0 = A(:,2);
sz = size(A);
mysig= fixed_cp_signal_gen({'InSig'}, s(1), 'linear', p0);
mysig1= cp_signal_gen({'InSig'}, s(1), 'linear', p0)
