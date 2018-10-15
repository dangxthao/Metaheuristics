classdef enum_idx_param_gen < param_gen
    % equal_param_gen enforces one param_out to be always equal to param_in
    
    properties
        enum
    end
    
    methods
        function this = enum_idx_param_gen(param, domain)
            this.params = {[param '_enum_idx']};
            this.enum = domain.enum;
            this.params_out = {param};
            this.p0 =1;
        end
        
        function p_out = computeParams(this, p_in)
            p_out = this.enum(p_in); 
        end
    end
     
end