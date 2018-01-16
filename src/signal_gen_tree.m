function [ retval ] = signal_gen( Y,L,epsilon,T,ind_1,ind_2,tset )
%[ RETVAL ] = SIGNAL_GEN( Y,L,EPSILON,T,X,IND,tset ) generates the 
% values of a specific signal at a set of time points, from a set of signals 
% having epsilon coverage and its initial value ranges in a symmetric
% interval around zero.
%   
% The following is the list of input parameters
%
% Y:        The length of interval containing initial values of the signal
%
% L:        Lipschitz constant for the class of input signals considered.   
%
% EPSILON:  Defines the degree of inputs space coverage, based on the
%           coverage metric defined above.
%
% T:        Time horizon of the signal.
%
% IND1:     Index determining the initial value of the signal,
%           
%           The interval [-Y,Y] is divided into subintervals of size
%           2*epsilon. The middle interval is [-epsilon,epsilon] which is 
%           centered around 0. Thus the number of other subintervals in 
%           [epsilon,Y] and [-Y, -epsilon] is 2(Y-epsilon)/(2epsilon)=
%           =Y/epsilon-1
%
%           Thus, the initial value index IND1 lies between 0 and 
%           floor(Y/epsilon-1).
%
% IND2:     This signal index ranges between 0 and 2^(n-1), where each signal 
%           corresponds to a Boolean vector of length 
%           n=floor(T*L/epsilon+1). Then each boolean vector can be encoded
%           by an integer by expanding the boolean vector with base 2.  
%
% TSET:     Monotonically increasing vector corresponding to the time 
%           instants present in the output. 
%
% The following is the output.
%
% RETVAL:       
%
% Example usage:
%
% Y= 2, T= 10; tspan = 0:.01:10; ind_1= 11, ind_2 = 26; L = .1; epsi = 0.1; 
% v= signal_gen( Y, L, epsi,T, ind_1,ind_2, tspan );
% plot(tspan,v);
%
C_1 = floor(Y/epsilon-1); % bound on IND_1
C_2 = 2^(floor(T*L/epsilon+1)); % bound on IND_2
if (ind_1>C_1)  % bounding the index
  msg1='Initial value index out of bounds';
  error(msg1)
else
    if (ind_2>=C_2)
        msg2='Corridor index out of bounds';
        error(msg2)
else
retval= -(Y-epsilon) + ind_1*2*epsilon + vanish0signal(L,epsilon, T+epsilon ,ind_2, tset+epsilon/L);
    end
end

