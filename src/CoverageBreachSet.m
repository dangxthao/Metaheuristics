classdef CoverageBreachSet < BreachSimulinkSystem
    % CoverageBreachSet Main class to interface Breach with Simulink
    % systems, using finitely parameterized input signals. This class has
    % the ability to provide coverage measures based on the traces that are
    % used to test the Simulink system. The coverage measures indicate "how
    % well" or "how thoroughly" the system was tested, with respect to the
    % selected class of input signals, where the class is determined by the
    % number of control points, the interpretation of the control points,
    % and the value ranges of the signals.
    %    
    %   CoverageBreachSet Constructor
    %
    %   BrSys = CoverageBreachSet(mdl_name [,params, p0])
    %
    %   Creates a BreachSystem interface to a Simulink model.
    %
    %   Arguments:
    %   mdl_name  -  a string naming a Simulink model.
    %   params    -  cell array of strings | 'all'
    %   p0        -  (optional) default values for parameters
    %
    %   If params is not given or equal to 'all', the constructor will try
    %   to discover automatically the tunable parameters in the model.
    %   If params is empty, then the only parameters for the model will be
    %   input parameters (i.e., parameters used to generate input signals).
    %
    %   The constructor interfaces inputs, outputs and logged signals.
    %   Note that a CoverageBreachSet is a BreachSimulinkSystem, which is
    %   a BreachOpenSystem, i.e., a
    %   systems that can be composed with a BreachSignalGenerator for input
    %   generation. By default, a constant input generator is created for
    %   each input of the model. Use SetInputGen method to set a different input.
    %
    %    
    %   CoverageBreachSet Methods
    %
    %       Addpoint -  Adds a point to the hash map that stores the list of 
    %                   points in parameter space. Input is a vector that
    %                   whose length is the number of parameters in the
    %                   model that are allowed to vary. There are two
    %                   potential outputs to the function. The first is a
    %                   flag that indicates whether the point was added to
    %                   the set, and the second is a vector that indicates
    %                   the point that was added (the added point may
    %                   differ from the point provided as input in the case
    %                   were the "snap_to_grid" flag is set).
    %       Addpoints -  Adds multiple points via the Addpoint method.
    %
    %
    %       SetEpsGridsize -  Sets the "eps" grid size for the parameter
    %                         set, which is the width of the (rectangular) 
    %                         bins used to store the points in the hash
    %                         map. This should only be called once, at the
    %                         beginning of the analysis.
    %
    %       SetDeltaGridsize - Sets the "delta" grid size for the parameter
    %                          set. This is the width of the (rectangular)
    %                          bins used to compute the entropy coverage.
    %                          This should only be called once, at the
    %                          beginning of the analysis.
    %
    %       SetSnapToGrid - Sets/clears a flag that indicates whether
    %                       points added to the parameter set should be
    %                       always lie on vertices of the "eps" grid. This
    %                       should only be called once, at the beginning of
    %                       the analysis.
    
    %       NewRun - Takes a set of parameter values, runs a simulation
    %                using the given values, and adds the new parameter to
    %                the hash maps. Takes as input a cell array containing 
    %                the names of the parameters and a corresponding vector
    %                whose elements contain the value of the parameters to
    %                be used for the simulation.
    %
    %       ComputeCellOccupancyCoverage - Computes the ratio of occupied
    %                                      "eps" grid elements to total
    %                                      "eps" grid elements.
    %
    %       ComputeLogCellOccupancyCoverage - Computes the ratio of the 
    %                                         logarithm of occupied "eps" 
    %                                         grid elements to the 
    %                                         logarithm of the total number
    %                                         of "eps" grid elements.
    %
    %       ComputeEntropyCoverage - Computes the entropy of the
    %                                distribution of points in the 
    %                                parameter space, based on the "delta" 
    %                                grid. 
    %
    %       DisplayPoints - List all of the points in the parameter set.
    %
    %       TotalCellCount - Returns the total number of cells in the "eps" 
    %                        grid of the parameter space. 
    %
    %       NumPoints - Returns the total number of points in the "eps"
    %                   grid of the parameter space.
    %
    %       VaryingParamList - Returns the indices of the system parameters
    %                          that are allowed to vary.
    %
    %       LowerLeftCorner - Returns the coordinate of the lower left
    %                         corner of the parameter space.
    %
    %See also BreachSimulinkSystem, BreachOpenSystem, signal_gen
    
    properties
        % Gridsize is a vector that contains one value for each dimension,
        % where each value corresponds to the length of a grid element in
        % the corresponding dimension. The eps value for each
        % dimension corresponds to the smallest distance allowed
        % between any two points in the parameter space.
        epsgridsize = [];
        
        % Gridsize is a vector that contains one value for each dimension,
        % where each value corresponds to the length of a grid element in
        % the corresponding dimension. The delta value for each
        % dimension corresponds to the grid element size that is used to
        % measure the cell count and entropy coverage measures.
        deltagridsize = [];
        
        % The following flag determines whether all points should be
        % shifted to the center of the appropriate grid element. If the
        % flag is set, then this class will assume that only one point
        % should occupy any given grid element, and that point will be in
        % the center of the grid element.
        snap_to_grid = false;
        
        % Will use containers for now. This will be an efficient
        % representation to a.) allow the query of any cell and b.) know
        % the total number of cells that are populated with points.
        % This DOES NOT permit an easy way to check a region (e.g., a
        % hybperbox) that contains points.
        % In the future, we can switch this for BDDs. A BDD representation
        % will allow us to do things like use an SMT query to determine
        % whether points in a region (hyperbox) are populated.
        EpsGridMapObj = containers.Map('UniformValues',false);
        DeltaGridMapObj = containers.Map('KeyType','char','ValueType','int32');
    end
    
    methods
        
        function this = CoverageBreachSet(varargin)
            this@BreachSimulinkSystem(varargin{:});
        end
        
        function SetEpsGridsize(this,eps_size_vector)
            % Assign a grid sizes for each parameter dimension. The eps
            % grid size indicates the length of grid elements for each of
            % the dimensions in parameter space. The eps value for each
            % dimension corresponds to the smallest distance allowed
            % between any two points in the parameter space.
            
            if ~isempty(this.epsgridsize)
                error('Eps grid size already set. You cannot change the grid size after it has been defined.');
            end
            
            if isrow(eps_size_vector)
                eps_size_vector = eps_size_vector';
            end
            
            % Number of parameters with ranges associated with them.
            varying_parameter_indices = this.VaryingParamList();
            
            if length(eps_size_vector)~=length(varying_parameter_indices)
                error('Length of the size vector does not match the number of parameters wth ranges associated with them.');
            end
            this.epsgridsize = eps_size_vector;
        end
        
        function SetDeltaGridsize(this,delta_size_vector)
            % Assign a grid sizes for each parameter dimension. The eps
            % grid size indicates the length of grid elements for each of
            % the dimensions in parameter space. The delta value for each
            % dimension corresponds to the grid element size that is used to
            % measure the cell count and entropy coverage measures.
            
            if ~isempty(this.deltagridsize)
                error('Delta grid size already set. You cannot change the grid size after it has been defined.');
            end
            if isrow(delta_size_vector)
                delta_size_vector = delta_size_vector';
            end
            % Number of parameters with ranges associated with them.
            
            varying_parameter_indices = this.VaryingParamList;
            if length(delta_size_vector)~=length(varying_parameter_indices)
                error('Length of the size vector does not match the number of parameters wth ranges associated with them.');
            end
            this.deltagridsize = delta_size_vector;
        end
        
        function SetSnapToGrid(this,snapflag)
            this.snap_to_grid = snapflag;
        end
        
        function inRange = TestPointInRange(this,new_point)
            % Identify the "lower, left" and "upper, right" corners of the
            % parameter set
            if isrow(new_point)
                new_point = new_point';
            end
            inRange = true;
            varying_parameter_indices = this.VaryingParamList;
            lower_left_corner = [];
            upper_right_corner = [];
            for ip = varying_parameter_indices
                lower_left_corner = [lower_left_corner; this.Domains(ip).domain(1)];
                upper_right_corner = [upper_right_corner; this.Domains(ip).domain(2)];
            end

            if any(new_point < lower_left_corner)||any(new_point>upper_right_corner)
                %fprintf('\nNew point out of range.\n');
                inRange = false;
            end
        end
        
        function lower_left_corner = LowerLeftCorner(this)
            % Identify the "lower, left" corner of the parameter set
            varying_parameter_indices = this.VaryingParamList;
            lower_left_corner = [];
            for ip = varying_parameter_indices
                lower_left_corner = [lower_left_corner; this.Domains(ip).domain(1)];
            end
        end
        function upper_right_corner = UpperRightCorner(this)
            % Identify the "upper, right" corner of the parameter set
            varying_parameter_indices = this.VaryingParamList;
            upper_right_corner = [];
            for ip = varying_parameter_indices
                upper_right_corner = [upper_right_corner; this.Domains(ip).domain(2)];
            end
        end
        
        function [varargout] = AddPoints(this,new_points)
            
            % Add a collection of new points to the space.
            
            % Assume that for an "row x col" matrix that represents the new points,
            % each col represents a unique point.
            num_points = size(new_points,2);
            for ind = 1:num_points
                thisPoint = new_points(:,ind);
                this.AddPoint(thisPoint);
            end
            
        end
        
        function [varargout] = AddPoint(this,new_point)
            % Add a point to the data structure
            
            if nargout>0
                varargout{1} = true;
            end
            if nargout>1
                varargout{2} = [];
            end
            
            if ~this.TestPointInRange(new_point)
                %fprintf('\nPoint not in range, so it was not added.\n');
                if nargout>0
                    varargout{1} = false;
                end
                return
            end
            
            epsgridsize = this.epsgridsize;
            deltagridsize = this.deltagridsize;
            
            if isrow(new_point)
                new_point = new_point';
            end
            
            if nargout>1
                varargout{2} = new_point;
            end
            
            % Identify the "lower, left" corner of the parameter set
            lower_left_corner = this.LowerLeftCorner();
            
            shifted_point = new_point - lower_left_corner;
            
            % First, identify corresponding eps grid element
            shifted_grid_element = diag(epsgridsize)*floor(shifted_point./epsgridsize);
            eps_grid_element = shifted_grid_element + lower_left_corner;
            
            % Also, identify delta grid element
            shifted_grid_element = diag(deltagridsize)*floor(shifted_point./deltagridsize);
            delta_grid_element = shifted_grid_element + lower_left_corner;
            
            if this.snap_to_grid
                if this.EpsGridMapObj.isKey(mat2str(eps_grid_element))
                    % fprintf('\nValue already present in grid element %s.\n',mat2str(eps_grid_element));
                    if nargout>0
                        varargout{1} = false;
                    end
                    if nargout>1
                        varargout{2} = [];
                    end
                else
                    if this.DeltaGridMapObj.isKey(mat2str(delta_grid_element))
                        previous_grid_members = this.DeltaGridMapObj(mat2str(delta_grid_element));
                        this.DeltaGridMapObj(mat2str(delta_grid_element)) = previous_grid_members + 1;
                    else
                        this.DeltaGridMapObj(mat2str(delta_grid_element)) = 1;
                    end
                    this.EpsGridMapObj(mat2str(eps_grid_element)) = 1;
                    if nargout>1
                        varargout{2} = eps_grid_element;
                    end
                end
            else
                % For this case, create a list for each grid
                % element that is populated by at least one point.
                if this.EpsGridMapObj.isKey(mat2str(eps_grid_element))
                    previous_grid_members = this.EpsGridMapObj(mat2str(eps_grid_element));
                    this.EpsGridMapObj(mat2str(eps_grid_element)) = [previous_grid_members new_point];
                else
                    this.EpsGridMapObj(mat2str(eps_grid_element)) = [new_point];
                end
                if this.DeltaGridMapObj.isKey(mat2str(delta_grid_element))
                    previous_grid_members = this.DeltaGridMapObj(mat2str(delta_grid_element));
                    this.DeltaGridMapObj(mat2str(delta_grid_element)) = previous_grid_members + 1;
                else
                    this.DeltaGridMapObj(mat2str(delta_grid_element)) = 1;
                end
            end
            
        end
        
        function varying_parameter_indices = VaryingParamList(this)
            % Determine the indices into the SimulinkSystem parameters that
            % correspond to parameters that are allowed to vary (i.e., that
            % have a range assocaited with them).
            
            [~, varying_parameter_indices] = this.GetBoundedDomains();
            
        end
        
        function NewRun(this,param_names,param_values)
            % Adds new point to list and runs the simulation
            
            epsgridsize = this.epsgridsize;
            
            lower_left_corner = this.LowerLeftCorner();
            
            new_point = [];
            param_dimen = 0;
            varying_parameter_indices = this.VaryingParamList;
            for ip = varying_parameter_indices
                param_dimen = param_dimen+1;
                % Find the index into the input parameter values that
                % corresponds to "this" parameter, which should allow a
                % range of values.
                [~,paramindex]=ismember(this.P.ParamList{ip},param_names);
                if this.snap_to_grid
                    % Shift value based on lower-left corner of parameter space
                    shifted_point = param_values(paramindex) - lower_left_corner(param_dimen);
                    % Snap to the appropriate grid element in the shifted grid
                    shifted_grid_element = epsgridsize(param_dimen)*floor(shifted_point/epsgridsize(param_dimen));
                    % Translate the grid element back to the original parameter space
                    grid_element = shifted_grid_element + lower_left_corner(param_dimen);
                    
                    param_values(paramindex) = grid_element;
                    new_point(param_dimen) = grid_element;
                else
                    new_point(param_dimen) = param_values(paramindex);
                end
            end
            
            if ~this.TestPointInRange(new_point)
                %fprintf('\nPoint not in range, so it was not added.\n');
                return
            end
            
            this.SetParam(param_names,param_values,'manual');
            this.Sim();
            
            this.AddPoint(new_point);
            
        end
        
        function num_points = NumPoints(this)
            % Return number of points in the list
            num_points = double(this.EpsGridMapObj.Count);
        end
        
        function DisplayPoints(this)
            % Display all points in the list
            KeysSet = this.EpsGridMapObj.keys;
            fprintf('\nCell: Occupancy\n');
            for ind = 1:length(KeysSet);
                ValueTemp = this.EpsGridMapObj(KeysSet{ind});
                fprintf('%s: %i \n',KeysSet{ind},ValueTemp);
            end
        end
        
        function total_cells = TotalCellCount(this)
            % Total number of cells in the parameter space
            %
            % First, compute the width of the range for each dimension in
            % the parameter space.
            varying_parameter_indices = this.VaryingParamList;
            rg = [];
            for ip = varying_parameter_indices
                rg = [rg; this.Domains(ip).domain(2)-this.Domains(ip).domain(1)];
            end
            total_cells = prod(ceil(rg./this.epsgridsize));
        end
        
        function coverage = ComputeLogCellOccupancyCoverage(this)
            % Compute the log of the cell occupancy
            % for the parameter space
            
            % Total number of cells in the parameter space
            total_cells = this.TotalCellCount;
            % Next, obtain the total number of populated cells
            pop_cells = this.NumPoints;
            coverage = log(pop_cells)/log(total_cells);
        end
        
        function coverage = ComputeCellOccupancyCoverage(this)
            % Compute the cell occupancy for the parameter space
            
            % Total number of cells in the parameter space
            total_cells = this.TotalCellCount;
            % Next, obtain the total number of populated cells
            pop_cells = this.NumPoints;
            coverage = pop_cells/total_cells;
        end
        
        function coverage = ComputeEntropyCoverage(this)
            % Compute the combinatorial entropy (also known as the
            % coarse-grained Boltzmann entropy).
            
            % The entropy measure is given by the following:
            %
            % G(D) = p!/(n_1!\cdots n_c!)
            %
            % S_B(D) = log(G(D)),
            %
            % where p is the total number of points, and n_i is the number
            % of points in cell i.
            
            % Collect the number of points in each cell and compute the
            % denominator of G(D). At the same time, compute the total
            % number of points p.
            delta_cell_labels = this.DeltaGridMapObj.keys;
            numpoints = 0;
            GD_denominator = 1;
            for ind = 1:length(delta_cell_labels)
                n_i = double(this.DeltaGridMapObj(delta_cell_labels{ind}));
                numpoints = numpoints + n_i;
                GD_denominator = GD_denominator*(factorial(n_i));
            end
            
            GD_numerator = factorial(numpoints);
            
            GD = GD_numerator/GD_denominator;
            
            coverage = log(GD);
        end
        
    end
    
end
