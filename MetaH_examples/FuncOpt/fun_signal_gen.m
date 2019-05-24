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
    
      function y = ripple(X) %ripple 1
          x1 = X(1);
          x2 = X(2);
          res1 = - exp( - 2*log(2)*((x1 - 0.1)/0.8)^2 ) * ((sin(5*pi*x1))^6 + 0.1*( cos(500*pi*x1))^2 );
          y = res1 - exp( - 2*log(2)*((x2 - 0.1)/0.8)^2 ) * (( sin(5*pi*x2))^6 + 0.1*(cos(500*pi*x2))^2 );
      end
       
      function y = holder(X) %egg holder
          x1 = X(1);
          x2 = X(2);
         y = -(x2 + 47) * sin(sqrt(abs(x2 + x1 / 2.0 + 47))) - x1 * sin(sqrt(abs(x1 - (x2 + 47)))); 
      end
      
      function y = ackley2(X)
          x1 = X(1);
          x2 = X(2);
           y = -200*exp(-0.02*sqrt(x1*x1+ x2*x2)); 
      end
      
      function y = ackleyN3(X)
          x1 = X(1);
          x2 = X(2);
           y = -200*exp(-0.2*sqrt(x1*x1+ x2*x2)) + 5*exp(cos(3*x1)+sin(3*x2)); 
      end
      
      function y = ackley4(X)
          x1 = X(1);
          x2 = X(2);
          D=2;
          y = 0.0;
          for i=1:1:(D-1)
            y= y + exp(0.2)*sqrt((X(i))^2 + (X(i+1))^2) + 3.0*(cos(2*X(i)) + sin(2*X(i+1)));
          end 
      end
      
      function y = beale(X)
         x1 = X(1);
         x2 = X(2);
         y = (1.5 - x1 + (x1 .* x2)).^2 + ...
             (2.25 - x1 + (x1 .* (x2.^2))).^2 + ...
             (2.625 - x1 + (x1 .* (x2.^3))).^2;
      end
      
      function scores = bohachevskyn1fcn(x)        
        X = x(1);
        Y = x(2);
        scores = (X .^ 2) + (2 * Y .^ 2) - (0.3 * cos(3 * pi * X)) - (0.4 * cos(4 * pi * Y)) + 0.7;
      end
      
      function scores = booth(x)
        X = x(1);
        Y = x(2);
        scores = (X + (2 * Y) - 7).^2 + ( (2 * X) + Y - 5).^2;
      end
      
      function scores = brentfcn(x)    
        X = x(1);
        Y = x(2);
        scores = (X + 10).^2 + (Y + 10).^2 + exp(-X.^2 - Y.^2);
      end
      
      function scores = bukinn6fcn(x)
          %[-15,-5][-3 3], min 0
        X = x(1);
        X2 = X .^ 2;
        Y = x(2);
        scores = 100 * sqrt(abs(Y - 0.01 * X2)) + 0.01 * abs(X  + 10);
      end
      
      
      function scores = crossintrayfcn(x)
          %[-10 10], min ?2.06261218
        X = x(1);
        Y = x(2);
        expcomponent = abs(100 - (sqrt(X .^2 + Y .^2) / pi));   
        scores = -0.0001 * ((abs(sin(X) .* sin(Y) .* exp(expcomponent)) + 1) .^ 0.1);
      end
      
      function scores = easomfcn(x)
          %[-100 100], min -1
        X = x(1);
        Y = x(2);
        scores = -cos(X) .* cos(Y) .* exp(-( ((X - pi) .^2) + ((Y - pi) .^ 2)) );
      end
     
      function scores = holdertablefcn(x)
          %[-10 10], min -19.2085
        X = x(1);
        Y = x(2);
        expcomponent = exp( abs(1 - (sqrt(X .^2 + Y .^ 2) / pi)) );    
        scores = -abs(sin(X) .* cos(Y) .* expcomponent);
      end
      
      function scores = levin13fcn(x)
          %[-10 10], min 0
        X = x(1);
        Y = x(2);
        scores = sin(3 * pi * X) .^ 2 + ...
        ((X - 1).^2) .* (1 + sin(3 * pi * Y) .^ 2) + ...
        ((Y - 1).^2) .* (1 + sin(2 * pi * Y) .^ 2);
      end
      
      function y = SchafferF6(X)
          %[-100 100], min 0
        d=2;
        y = 0.5;
          for i=1:1:(d-1)
            y= y + ((sin(sqrt((X(i))^2 + (X(i+1))^2)))^2 - 0.5)/...
                (1 + 0.001*( (X(i))^2 + (X(i+1))^2 ));
          end
      end
      
      function y = TesttubeHolder(x)
          %[-10 10], min ?10.872300
        x1 = x(1);
        x2 = x(2);
        y = -4*abs( sin(x1)*cos(x1)*...
            exp( abs(cos( (x1)^2 + (x2)^2 )/200) ) );
      end
      
      function y = Trefethen(x)
          %[-10 10], min ?3.30686865
        x1 = x(1);
        x2 = x(2);
        y = exp(sin(50*x1)) +sin(60*exp(x2)) +sin(70+sin(x1)) + sin(sin(80*x2))...
          -sin(10*(x1 + x2)) + ((x1)^2 + (x2)^2)/4;
      end
     
      function y = WWavy(X)
          %[-pi pi], min 0
        d=2;
        k=10;
        y = 1;
          for i=1:1:(d-1)
            y = y - (1/d)*cos(k*X(i))*exp( -0.5*(X(i))^2 );
          end
      end
      
      function y = Zettl(x)
          %[-5 10], min ?0.003791
        x1 = x(1);
        x2 = x(2);
        y = (x1+x1 + x2*x2 - 2*x1)^2 + 0.25*x1;
      end
   end
end