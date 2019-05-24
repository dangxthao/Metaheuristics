classdef fun_signal_gen < signal_gen
   
    properties
        fun
    end
    
   methods
       
       function this = fun_signal_gen(f)
           this.signals = {'y'};
           if nargin<1
             f = 'ripple';
           end
           this.fun = eval(['@this.' f ]);
           this.params = {'x1', 'x2'};
           this.p0 = [0  0];
       end
       
       function  X = computeSignals(this, pin, t)
           
           y = this.fun(pin);
           X = y*ones(1, numel(t));
           
       end
   end
   
   methods (Static)
    
      function y = ripple(X)
          x1 = X(1);
          x2 = X(2);
          res1 = - exp( - 2*log(2)*((x1 - 0.1)/0.8)^2 ) * ((sin(5*pi*x1))^6 + 0.1*( cos(500*pi*x1))^2 );
          y = res1 - exp( - 2*log(2)*((x2 - 0.1)/0.8)^2 ) * (( sin(5*pi*x2))^6 + 0.1*(cos(500*pi*x2))^2 );
      end
       
      function y = holder(X)
          x1 = X(1);
          x2 = X(2);
         y = -(x2 + 47) * sin(sqrt(abs(x2 + x1 / 2.0 + 47))) - x1 * sin(sqrt(abs(x1 - (x2 + 47)))); 
      end
      
      function y = ackley2(X)
          x1 = X(1);
          x2 = X(2);
           y = - 200*exp(-0.02*sqrt(x1*x1+ x2*x2)); 
      end
   
   end
end