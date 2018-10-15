classdef param_gen < handle
    properties
        params
        params_out
        p0  % default values for params
    end
    methods (Abstract)
       p_out = computeParams(this, p_in)
    end   
end