classdef FalsifTreeProblem < FalsificationProblem
    % FalsificationProblem using signal_tree
    % Works for 1D signal so far, no refinement, no robustness guidance
    
    properties
        sig_tree
    end
    
    methods
        function this = FalsifTreeProblem(BrSys, phi, sig_tree)
            this = this@FalsificationProblem(BrSys, phi); % calls parent constructor
            this.sig_tree = sig_tree;
        end
        
        function setup_solver(this)
            %SETUP_SOLVER will set up strategies and parameters for signals exploration here
            this.solver_options = struct;
            
            
        end
        
        % custom objective function - here x is leaf_id ...
        function fval = objective_fn(this,x)
            tset = this.sig_tree.tset;
            U = this.sig_tree.get_signal_from_leaf(x);
            BrNew = this.BrSys.copy();
            BrNew.Sim(tset, [tset' U']);
            fval = BrNew.CheckSpec(this.Spec);
            
            if isempty(this.res.Traces)
                this.res.Traces= BrNew.copy();
            else
                this.res.Traces.Concat(BrNew);  % Add new trace
            end
            
        end
        
        
        function res = solve(this)
            
            leaves_id = this.sig_tree.findleaves();

            % display header
            fprintf('Eval property on %d input signals\n', numel(leaves_id));
            fprintf('#signal      obj              best           time spent\n');
            rfprintf_reset();
            
            this.res.Traces = [];
            
            isignal= 0;
            for leaf_id = leaves_id
                isignal=isignal+1;
                fval = this.objective(leaf_id);
                
                if ~this.stopping
                    st__= sprintf('%5d      %+5.5e      %+5.5e      %7.1f\n', isignal, fval, this.obj_best, this.time_spent);
                    rfprintf(st__);
                else
                    break
                end
            end
            
            
            res = this.res;
            this.DispResultMsg;
        end
        
    end
    
end