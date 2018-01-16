function [retval] = vanish0signal (L,epsilon,T,ind,tset)
% [RETVAL] = VANISH0SIGNAL(L,EPSILON,T,I,TSPAN)  generates the value of a 
% specific signal at a set of time points, from a set of signals having 
% epsilon coverage and vanishing at origin. Epsilon cover of a set of signals $X$ is another set
% collection of sets $(Y_i)_{i=1}^C$, each having diameter 2*epsilon, such 
% that their union $\cup_{i=1}^C (Y_i)$ is equal to $X$.
%
% The following is a list of input parameters.
%
% L:        Lipschitz constant for the class of input signals considered.   
%
% EPSILON:  Defines the degree of inputs space coverage, based on the
%           coverage metric defined above.
%
% T:        Time horizon of the signal.
%
% IND:     The index ranges between 0 and 2^(n-1).   Each signal corresponds 
%          to a boolean vector of length n=floor(T*L/epsilon). Then each 
%          boolean vector can be encoded by an integer by expanding the 
%          boolean vector with base 2.  
%
% TSET:    Monotonically increasing vector corresponding to the time 
%           instants present in the output. 
%
% The following is the output.
%
% RETVAL:       
%
% Example usage:
%
% T = 10; tspan = 0:.01:10; i = 26; L = .1; epsi = 0.1; 
% v= gen_signal(L, epsi,T, i, tspan);
% plot(tspan,v);
%

n=floor(T*L/epsilon);% number of points on the time grid after discretization excluding 0.
C=(2)^n; % number of signal corridors, bound on the index
s=zeros(1,n); %initializing the sequence of slopes for the signal
if ind>=C % bounding the index
  msg='Index out of bounds';
  error(msg)
else
 
    h=ind;
    %below loop generates the value of s
    for p=1:n
        j=n-p;
        [v,h]=qurem(h,(2)^j); %decoding index into a binary vector
        if (v<1) % if the component of binary vector is not one, then -ve slope=-L
            s(1,n-p+1)=(-1)*L;
        else % if the component of binary vector is one, then +ve slope= +L 
            s(1,n-p+1)=(1)*L;
        end
    end
        
    retval = zeros(1, numel(tset)); 
    for it= 1:numel(tset)
        t = tset(it);
        m=floor(t*L/epsilon); % number of discrete time steps until t.
        %below loop integrates to find the reachable point
        if (m<0 || m>n) 
            msg='time point in tset out of range!';
            error(msg)
        end    
        if m>=1
            retval(it)=sum(s(1,1:m))*epsilon/(L); % value of signal until time m steps
        end
        if m>=0&&m<n
             % adding contribution for remaining time after m steps.
            retval(it)=retval(it)+(t-(epsilon/L)*floor(t*L/epsilon)).*s(1,m+1);
        end
    end
end
