for ii = 1:50
        %sigId = 1 %sigId = 0:51
        if (ii < 11)
                sigfilename = strcat('s_0', num2str(ii-1));
        else
                sigfilename = strcat('s_', num2str(ii-1));
        end
        tr  =        load(sigfilename, '-ascii');
        t = tr(:,1);
        dt = diff(t); 
        min_dt(ii) = min(dt);
        max_dt(ii) = max(dt);
        
        min_diff1(ii) = min(diff(t(1:6:end)));
        max_diff1(ii) = max(diff(t(1:6:end)));
        
        min_diff5(ii) = min(diff(t(5:6:end)));
        max_diff5(ii) = max(diff(t(5:6:end)));
        ts{ii} = t;
        
end

