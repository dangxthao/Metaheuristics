classdef signal_tree < tree
    
    properties
        u_lim           % Bounds on signals values
        L               % Lipshitz bound
        epsilon         % epsilon-coverage achieved by the tree
        tset            % sets of time values for signal generation
        T
    end
    
    methods
        %% Constructor
        function this = signal_tree(u_lim, L, epsilon,tset)
            % SIGNAL_TREE Constructs a signal_tree with bounds u_lim on values, lipshitz L,  coverage epsilon and on a given time set tset
            
            this= this@tree(tree_elem(NaN, NaN));
            this.u_lim = u_lim;
            this.L = L;
            this.epsilon = epsilon;
            this.tset = tset;
            this.T = tset(end);
            init_vals = [this.u_lim(1):2*this.epsilon:(this.u_lim(2)-this.epsilon)] + this.epsilon;
            this=this.add_init_val(init_vals);
            
        end
        
        function this = add_init_val(this,init_vals)
            % ADD_INIT_VAL initialize initial values with coverage epsilon
            
            u_max = this.u_lim(2);
            u_min = this.u_lim(1);
            
            for init_val = init_vals
                
                % Sanity check
                if init_val >u_max || init_val < u_min
                    error('signal_tree:init_val_out_of_bounds', 'init_val must be within u_lim.' )
                end
                
                this=this.addnode(1, tree_elem(0., init_val));
                
            end
        end
        
        %% Grows a complete initial tree
        function this = grow_epsi_tree(this)
            %GROW_EPSI_TREE Grows a complete tree with epsilon coverage
            
            % At this point, leaves are initial values
            leaves_id = this.findleaves();
            
            while ~isempty(leaves_id) % we treat leaves_id as a dequeue - maybe checks if matlab has dequeues..
                
                % pop front
                leaf = leaves_id(1);
                leaves_id = leaves_id(2:end);
                
                [this, done] = this.grow_up(leaf);
                if ~done
                    leaves_id(end+1) = this.nnodes; % path has not reached final time => push_back
                end
                
                [this, done] = this.grow_down(leaf);
                if ~done
                    leaves_id(end+1) = this.nnodes; % push_back
                end
                
            end
        end
        
        
        %% Grows tree by nodes and path
        function [this, done] = grow_down(this, node, epsilon)
            % grow_DOWN adds a node with negative slope. If lower bound is reached, complete constant to the end time.
            if nargin == 2
                epsilon = this.epsilon;
            end
            
            u_min = this.u_lim(1);
            elem = this.get(node);
            
            dt = min(epsilon/this.L, this.T-elem.time);
            % grows down
            next_value_down = elem.value - this.L*dt;
            if next_value_down < u_min
                % Reached bottom
                next_value_down = u_min;
                 if (elem.value-u_min~=0) % Only add this node if time has progressed
                    next_time= elem.time + (elem.value-u_min)/this.L;
                    this = this.addnode(node, tree_elem(next_time,next_value_down));
                    this = this.addnode(this.nnodes, tree_elem(this.T, next_value_down));
                 else
                    this = this.addnode(node, tree_elem(this.T, next_value_down));
                 end
            else
                next_time = elem.time + dt;
                this = this.addnode(node, tree_elem(next_time,next_value_down));
            end
            
            new_elem = this.get(this.nnodes);
            done =  new_elem.time >= this.T;
            
        end
        
        function [this, done] = grow_up(this, node, epsilon)
            % grow_UP adds a node with negative slope. If lower bound is reached, complete constant to the end.
            
            if nargin == 2
                epsilon = this.epsilon;
            end
            
            u_max = this.u_lim(2);
            elem = this.get(node);
           
            dt = min(epsilon/this.L, this.T-elem.time);
            % grows up
            next_value_up = elem.value + this.L*dt;
            if next_value_up > u_max
                % Reached top
                next_value_up = u_max;
                if (u_max-elem.value~=0) % Only add this node if time has progressed
                    next_time= elem.time + (u_max-elem.value)/this.L;
                    this = this.addnode(node, tree_elem(next_time,next_value_up));
                    this = this.addnode(this.nnodes, tree_elem(this.T, next_value_up));
                else
                    this = this.addnode(node, tree_elem(this.T, next_value_up));
                end
            else
                next_time = elem.time + dt;
                this = this.addnode(node, tree_elem(next_time,next_value_up));
            end
            
            new_elem = this.get(this.nnodes);
            done =  new_elem.time >= this.T;
            
        end
        
        function this = grow_random_path(this, node_id, epsi)
            % grow_RANDOM_PATH TODO 
            
            % note: one idea is to grow leaves along the path, so that
            % picking new path will reduce to picking a leave with time
            % smaller than T 
           
            
            elem  = this.get(node_id);
            while elem.time < this.T;
                % TODO
                
                
                
            end
        end
        
        
        %% Generate signals from path
        function path = path_to_root(this, inode)
            %PATH_TO_ROOT gets a path from a node to root
            
            path.times = zeros(1,this.depth);
            path.values = zeros(1,this.depth);
            
            cur_node = inode;
            i_path =this.depth+1;
            while cur_node ~=0
                elem = this.get(cur_node);
                path.times(i_path) = elem.time;
                path.values(i_path) = elem.value;
                cur_node = this.getparent(cur_node);
                i_path= i_path-1;
            end
            path.times = path.times(i_path+2:end);
            path.values = path.values(i_path+2:end);
            
        end
        
        function U = get_signal_from_leaf(this,leaf_id )
                path = this.path_to_root(leaf_id);
                U = interp1(path.times, path.values, this.tset); 
        end    
            
        %% Misc (display, plot, etc)
        function show(this)
            disp(this.tostring)
        end
        
        
        function h = plot_all(this, h)
            % PLOT_ALL get all paths and plots corresponding signals
            
            if nargin == 1
                h = figure; hold on;
            else
                figure(h);
            end
            
            leaves_id = this.findleaves();
            
            for leaf = leaves_id
                path = this.path_to_root(leaf);
                plot(path.times, path.values)
            end
            
        end
        
        
    end
    
end


