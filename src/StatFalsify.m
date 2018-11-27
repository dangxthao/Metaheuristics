classdef StatFalsify
% STATFALSIFY: Object implementing hyperplane clustering based
% falsification algorithm.
%
% PROPERTIES:
%
% COVERAGEVALUES: 
%   Type: [n*1] array where n is the number of simulations.
%   Description: Vector of coverage values with each new simulation.
%
% REGIONS: TYPE: [a,b], a,b are column vectors, a<=b. DES: Collection of
% subrectangles subdividing parameter space, where 'a' is lower left corner of
% a rectangle and 'b' is upper right corner of a rectangle.
% 
% CLUSTERS: TYPE: struct with fields 'vals' and 'pts'. DES: Collection of
% samples in each subrectangle.
%  clusters.vals: column vector containing list of robustness values in a subrectangle.
%  clusters.pts: Array whose each row is a sampled point in a subrectangle.
%
% NUM_SAMPLES: Total number of samples.
%
% COVERAGE: Column vector containing list of coverage values of all subrectangles.
%
% FALSIFIER: Row vector specifying the falsifier.
%
% FALSIFIER_REGION: Subrectangle containing the falsifier.
%
% LOWER_BOUNDS: Row vector containing the list of lowest robustness values
% in each subrectagle.
%
% all_samples: object with following two fields
%     <>.pts: matrix of of all points specified as its rows.
%     <>.vals: column vector of corresponding robustness values.
%
% new_samples: object with following two fields
%     <>.pts: matrix of of new points specified as its rows.
%     <>.vals: column vector of corresponding robustness values.
%
% METHODS:
%
% SIMSAMPLE: Simulates a sample in a CoverageBreachSet object.
%
% HINGE_LOSS: Computes unnormalized misclassification error.
%
% UPPER_RIGHT_CORNER: Computes upper_right_corner of CoverageBreachSet
% object.
%
% REMSAMPLES: Computes the list of samples contained in a rectangle among a
% given list of samples.
%
% PSEUDORANDSAMP: Pseudo randomly generates a specified number of points
% and computes robustness in a  given rectangle.
%
% OPTIMINTERVAL: Calculates the optimum interval minimizing the
% normalized misclassification error.
%
% OPTIMRECT: Subdivides a given rectangle into two subrectangles, such
% that misclassification error is minimized.
%
% ManualPartition: Constructs a user specified partition.
%
% STATFALSIFY: Class constructor.


  properties
    CoverageValues = []
    regions = {};
    clusters = {};
    num_samples = 0;
    coverage = [];
    falsifier = [];
    falsifier_region = [];
    lower_bounds = [];
    nominal_ranges = [];
    all_samples = [];
    new_samples = [];
    falsified = false;
  end
 
   
    methods (Static)

     function [newsample,falsified] = SimSample(CBS,new_point,param_names,param_ranges,phi)
    % [NEWSAMPLE,FALSIFIED] = SIMSAMPLE(CBS,NEW_POINT,PARAM_NAMES,PARAM_RANGES,PHI)
    % FUNCTION: Simulates and computes robustness of 
    % epsilon_grid point corresponding to newpoint,
    % provided the grid point has not been simulated before.
    %
    % Inputs:
    %
    % CBS: CoverageBreachSet object.
    %
    % NEW_POINT: Vector specifying point in the parameter space to be simulated.
    %
    % PARAM_NAMES: Cellular array of names of parameters.
    %
    % PARAM_RANGES: TYPE: [a,b]: a<=b, a,b are column vectors. DES: Bounds
    % on the ranges of the parameters.
    %
    % PHI: STL formula.
    %
    % Outputs:
    %
    % NEWSAMPLE: TYPE: [struct] with fields '.point' and '.val'
    %  point: vector specifying point to be sampled.
    %  val: robustness value of simulated point.
    %
    % FALSIFIED: Indicates if newsample falsified the property.

     
      % Convert row to column vector
        if isrow(new_point)
            new_point = new_point';
        end

      % Initialize variables
        falsified = false;
        newsample.point = [];
        newsample.val = [];
        CBS.SetParamRanges(param_names,param_ranges);
        
      % Updat new_sample.point and list of points in CBS
          n1 = CBS.NumPoints;
          CBS.AddPoint(new_point);
          n2 = CBS.NumPoints;
        if n2 > n1  
            newsample.point = new_point';
        end           

    % Compute robustness of newsample.
       if ~isempty(newsample.point)
               CBS.SetParam(param_names, newsample.point);
               CBS.Sim();
               newsample.val = CBS.CheckSpec(phi);
               %disp(newsample.val)

     % Updates status of falsified
          if newsample.val<0 
                   disp('Falsified in StatFalsify');
                   new_fig = gcf;
                   CBS.PlotSignals;
                   falsified = true;
                   return;
          end
       end
    end

%%       
    function [tot_err] = hinge_loss(cut,polarity,list_proj,list_vals,sep_val)
    % [TOT_ERROR] = HINGE_LOSS (CUT, POLARITY, LIST_PROJ, LIST_VALS, SEP_VAL)
    % Computes the sum of unnormalized miscalassication errors due to all
    % samples in some dimension for which the projections of sampled points
    % and corresponding robustness values are given.
    %
    % INPUTS:
    %
    % CUT: Point on the axis at which hyperplane is drawn.
    %
    % POLARITY: Determines whether selected interval is greater than
    % cut (+1) or less than cut (-1).
    %
    % LIST_PROJ: Row vector containing projections of the points on the dimension of
    % interest.
    %
    % LIST_VALS: Row vector containing robustness values of the samples.
    %
    % SEP_VAL: Threshold robustness value demarkating two clusters of
    % samples.
    %
    % OUTPUTS:
    %
    % TOT_ERROR: Sum of unnormalized misclassification errors of all samples.
    
        tot_err = 0; % Initialize total error.
        
     % Compute misclassification error due to each sample and add them to total error.
        for i = 1:length(list_vals)
           rho = list_vals(i,1);
           err = max(0,(list_proj(i)-cut)*polarity*(rho-sep_val));                          
           tot_err = tot_err+err;  
        end
    end
 
%%
    function upper_right_corner=UpperRightCorner(CBS)
     % Find the "upper right" corner of CBS object.
        varying_parameter_indices = CBS.VaryingParamList;
        upper_right_corner = [];
        for ip = varying_parameter_indices
            %upper_right_corner = [upper_right_corner; CBS.ParamRanges(ip-CBS.P.DimX,2)];
            upper_right_corner = [upper_right_corner; CBS.Domains(ip).domain(2)];
        end
    end
    
%%
    function [samples] = RemSamples(bounds,all_samples)
    % [SAMPLES] = REMSAMPLES(BOUNDS,ALL_SAMPLES)
    % FUNCTION: Computes the samples contained in a rectagle among a given
    % list of samples.
    %
    % INPUTS:
    %
    % BOUNDS: TYPE: [a,b], a,b are column vectors, a<=b.  DES: Upper and
    % lower bounds of a rectangle.
    %
    % ALL_SAMPLES: TYPE: [struct] with fields 'pts' and 'vals'.
    %  pts: Array whose rows are points of all_samples.
    %  vals: Column vector containing robustness values of all_samples.
    
        n = length(all_samples.vals);
        m = size(bounds,1);
        l = true(n,1);
        for i = 1:m
            l = l & (all_samples.pts(:,i)<bounds(i,2)) & (all_samples.pts(:,i)>bounds(i,1));
        end
        samples.pts = all_samples.pts(l,:); samples.vals = all_samples.vals(l);
    end

    end   
   
     
  methods   
        
 %%  
    function [this,list,falsified,nb,falsi_point] = PseudoRandSamp(this,CBS,param_names,...
                                                  param_ranges,phi,nb_samples,max_time,hits)

    % [LIST, FALSIFIED, NB, FALSI_POINT] = THIS.PSEUDORANDSAMP(CBS, PARAM_NAMES,...
    %                                       PARAM_RANGES, PHI, NB_SAMPLES, HITS)
    % FUNCTION: Generates pseudorandomly a list of points and computes the
    % robustness values 
    %
    % INPUTS:
    % CBS: CoverageBreachSet object.
    %
    % PARAM_NAMES: Cellular array of names of parameters.
    %
    % PARAM_RANGES: TYPE: [a,b]: a<=b, a,b are column vectors. DES: Bounds
    % on the ranges of the parameters.
    %
    % PHI: STL formula.
    %
    % NB_SAMPLES: Number of pseudorandom samples to be generated.
    %
    % MAX_TIME: maximum time for pseudorandom simulation.
    %
    % HITS: Maximum number of pseudorandom attempts.
    % 
    % OUTPUTS:
    %
    % LIST:  TYPE: [struct] with fields 'pts' and 'vals'. DES: List of
    % simulated samples.
    %  pts: Array whose rows are points that are simulated.
    %  vals: Robustness values of simulated points.
    %
    % FALSIFIED: Boolean value indicating if property is falsified.
    %
    % NB: Number of simulations.

    % Initialize the variables
      tStart = tic;
      list.pts=[]; 
      list.vals=[]; 
      nb=0; % counter for number of simulated points
      num_params = length(param_names); % number of parameters
      nb_attempts = 0;
      falsified = this.falsified; falsi_point = [];
      if num_params ~= size(param_ranges,1)
        error('Number of parameters not equal to number of range intervals');
      end
      time = toc(tStart);
      
    % Loop until maximum number of simulations or maximum number of random
    % attemps.
     
    
    while (nb<nb_samples && time<max_time && ~falsified && nb_attempts<hits )
%       while (nb<nb_samples && time<max_time && ~falsified && nb_attempts<hits)

    % Generate a pseudo random point lying within the parameter ranges.                  
      new_point = rand(num_params,1).*(param_ranges(:,2)...
                                       -param_ranges(:,1))+param_ranges(:,1);
    % Update time.
      time = toc(tStart);
      
    % Update number of attempts.
      nb_attempts = nb_attempts+1;

    % Simulate the point.
      [newsample,falsified] = this.SimSample(CBS,new_point,param_names,this.nominal_ranges...
                                             ,phi);
    % Update the list of samples.
      if ~isempty(newsample.val)
          this.CoverageValues = [this.CoverageValues; CBS.ComputeLogCellOccupancyCoverage];
          nb = nb+1;
          list.pts = [list.pts;newsample.point];
          list.vals = [list.vals;newsample.val];            
      end
      
    % Update the status of falsified and break loop if falsified.
       if falsified
           falsi_point = newsample.point;
           disp('Falsified')
           return;
       end
    end
end  

 %%
    function [best_interval,comp_interval,min_error] = OptimInterval(this,list,interval,...
                                                            dim,sep_val)
      % [BEST_INTERVAL,COMP_INTERVAL,MIN_ERROR] = THIS.OPTIMINTERVAL(LIST,INTERVAL,DIM,SEP_VAL)
      % FUNCTION: Computes the optimal interval that minimizes
      % "normalized" misclassification error of samples.
      % 
      % INPUTS:
      %
      % LIST: TYPE: [struct] with fields 'pts' and 'vals'. DES: List of
      % simulated samples.
      %  pts: Array whose rows are points that are simulated.
      %  vals: Robustness values of simulated points.
      %
      % PARAM_RANGES: TYPE: [a,b]: a<=b, a,b are column vectors. DES: Bounds
      % on the ranges of the parameters.
      %
      % SEP_VAL: Threshold robustness value demarkating two clusters of
      % samples.
      %
      % OUTPUTS:
      %
      % BEST_INTERVAL: Interval minimizing the misclassification error.
      %
      % COMP_INTERVAL: Complementary interval of best_interval.
      %
      % MIN_ERROR: Misclassification error corresponding to best_interval.
      
      
      % Initializing variables.
        proj(:,1) = list.pts(:,dim); %projections of list_pts on dim axis
        min_error = inf; 
        polarity = 1; % indicates the positioning on which best_interval (right: +1, left:-1).
        cuts = unique(proj'); % the set of values at which separating hyperplane can be drawn.
        cuts = [interval(1,1),cuts,interval(1,2)];
        ind = 1; % index of value in cuts that corresponds to the best_interval.

      if any(list.vals >= sep_val)

     % Find the interval minimizing the misclassification error.
        for i=1:length(cuts)
            for pol=[-1,1]
     % Compute the misclassification error
              [err] = this.hinge_loss(cuts(i),pol,proj,list.vals,sep_val)/...
                                       (interval(1,2)-interval(1,1));
               if err < min_error
                  min_error = err;
                  ind = i;
                  polarity = pol;
                end
            end
        end
     
     % Update the best_interval and comp_interval.
        if polarity>0
            best_interval = [min(interval(1,2)-10^-10,cuts(ind)),interval(1,2)];
            comp_interval = [interval(1,1),max(interval(1,1)+10^-10,cuts(ind))];
        else 
            best_interval = [interval(1,1),max(interval(1,1)+10^-10,cuts(ind))];
            comp_interval = [min(interval(1,2)-10^-10,cuts(ind)),interval(1,2)];
        end
        
      else
          best_interval = interval;
          comp_interval = [interval(1,2)-10^-10,interval(1,2)];
      end
          
    end
      
%%        
       function [new_rect,comp_rect,dim] = OptimRect(this,list,param_ranges,sep_val)
        % [NEW_RECT, COMP_RECT, NEW_LIST] = THIS.OPTIMRECT (LIST, PARAM_RANGES, SEP_VAL)
        % FUNCTION: Computes two subrectangles forming two clusters of
        % samples such that misclassification error is minimized.
        %
        % Inputs: 
        % LIST: TYPE: [struct] with fields 'pts' and 'vals'. DES: List of
        % simulated samples.
        %  pts: Array whose rows are points that are simulated.
        %  vals: Robustness values of simulated points.
        %
        % PARAM_RANGES: TYPE: [a,b]: a<=b, a,b are column vectors. DES: Bounds
        % on the ranges of the parameters.
        %
        % OUTPUTS:
        %
        % NEW_RECT: Bounds on optimal rectangle.
        % COMP_RECT: Complement of new_rect.
        %
        % DIM: Dimension along which misclassification error is minimized.
        
         % Initializing variables
            new_rect = param_ranges; 
            comp_rect = param_ranges;
            new_list = list; indices = 1:size(param_ranges,1);
            min_err = inf;
            min_ind = indices(1); % allignment axis of optimial separating hyperplane.
            best_intv = new_rect(min_ind,:);
            comp_intv = new_rect(min_ind,:);
         
         % Compute the minimum misclassification error for the best separating hyperplane
         % along each dimension and update the optimal rectangle corresponding to the lowest 
         % misclassification error.
            for i=indices
             [range,comp_range,cl_err] = this.OptimInterval(new_list, new_rect(i,:), i,...
                                               sep_val);
                if cl_err == 0 
                    new_rect (i,:) = range;
                    comp_rect(i,:) = comp_range;
                end

                if cl_err < min_err
                   min_ind = i;
                   min_err = cl_err;
                   best_intv = range;
                   comp_intv = comp_range;
                end
            end
                
         % Update the optimal rectangle and its complementary rectangle.
            new_rect(min_ind,:) = best_intv; comp_rect(min_ind,:) = comp_intv;
            dim = min_ind;
       end
       
 %%
 function this = ManualPartition(this,RegionIndex,dim,position)
     % THIS = THIS.MANUALPARTITON(REGIONINDEX,DIM,POSITION)
     %
     % Constructs a new user specified partiton.
     % 
     % Inputs:
     % 
     % REGIONINDEX: 
     %  Type: Integer which ranges between 1 and the number of surectangle
     %        in the partition.
     %  Description: Index of the subrectangle which has to be partitioned.
     % DIM: 
     %  Type: Integer among the range of dimensions of search space.
     %  Description: Dimension/Axis along which partition is constructed.
     %
     % POSITION: 
     %  Type: Real value within the parameter values of the axis along
     %        which partition is constructed.
     %  Description: Position at which partition line is drawn.
     
     N = numel(this.regions); % compute total number of regions
     
     % Partition specified region into two new regions.
     r = this.regions{RegionIndex};
     r(dim,1) = position;
     this.regions{N+1} = r;
     this.regions{RegionIndex}(dim,2) = position;
     
     % Seperate the corresponding cluster into two new clusters.
     samples = this.clusters{RegionIndex};
     this.clusters{N+1} = this.RemSamples(this.regions{N+1},samples); 
     this.clusters{RegionIndex} = this.RemSamples(this.regions{RegionIndex},samples); 
     
     % Update coverage and lower bounds
     for i = 1:numel(this.regions)
                 if ~isempty(this.clusters{i}.pts)
                     bounds = this.regions{i};
                     samples = this.clusters{i};
                     this.coverage(i) = log(numel(samples.vals)+1)/...
                                         max(1,sum(log((bounds(:,2)-bounds(:,1))./eps+1)));
                     [~,ind] = min(samples.vals);
                     this.lower_bounds.pts(i,:) = samples.pts(ind,:);
                     this.lower_bounds.vals(i) = samples.vals(ind,:);                     
                 else
                  this.lower_bounds.pts(i,:) = [];
                  this.lower_bounds.vals(i) = inf;
                 end                
     end
             
 end
          
 %%       
   function this = StatFalsify(obj,CBS,phi,rob_wt,init_samples,max_simulations,max_time)                              
     % THIS = STATFALSIFY(CBS, PHI, ROB_WT, INIT_SAMPLES, MAX_SIMULATIONS, MAX_TIME)
     %         
     % Constructs the output of implementing hyperplane
     % clustering based falsification algorithm.
     %
     % INPUTS:
     %
     % OBJ: Statfalsify object to begin with.
     % CBS: CoverageBreachSet Object.
     % PHI: STL formula.
     %
     % INIT_SAMPLES: Minimum number of samples required for
     % classification.
     %
     % MAX_SIMULATIONS: Limit on maximum number of simulations.
     %
     % MAX_TIME: Limit on computation time.

     if nargin==0
         return;
     end
     
      global start

     
        tic;

        % Initializing variables.
        eps = CBS.epsgridsize;  
        ip = CBS.VaryingParamList;
        global param_names param_ranges
        if isempty(obj)
            param_names = CBS.P.ParamList(1,ip);
            N = numel(param_names);
            param_ranges = [CBS.LowerLeftCorner(),this.UpperRightCorner(CBS)];  
            this.all_samples.pts = []; this.all_samples.vals = [];  
            this.new_samples.pts = []; this.new_samples.vals = [];
            this.regions{1} = param_ranges;
            this.nominal_ranges = param_ranges;
        % Pseudorandomly sample "init_samples" number of points in the originial
        % parameter space.       
            [this,cluster,this.falsified,nb_added,this.falsifier] =...
               this.PseudoRandSamp(CBS,param_names,...
              param_ranges,phi,init_samples,max_time,init_samples);
            num_sim = nb_added;
            this.clusters{1} = cluster;
            this.all_samples = this.clusters{1};
            this.new_samples = this.clusters{1};
            [~,idmin] = min(this.clusters{1}.vals);
            this.lower_bounds.vals = this.clusters{1}.vals(idmin);
            this.lower_bounds.pts = this.clusters{1}.pts(idmin,:);
            lb = this.lower_bounds.vals;
        else
            N = numel(param_names);
            this = obj;
            obj.new_samples = [];
            lb = this.lower_bounds.vals;
            this.falsified = obj.falsified;
            num_sim = 0;
        end       

        time = toc;

 
            
        run = (time<max_time) && num_sim<max_simulations && ~this.falsified ;        
        while run % && start == 1 Thao
%         disp('num_sim =')   
%         disp(num_sim)
       % Perform classification.
       % Find new subrectangles, clusters and compute the vector of lowest robustness
       % values for the collection of clusters. 
       
       numel(this.regions) %Thao
       
        for i = 1:numel(this.regions);
              bounds = this.regions{i};
              samples = this.clusters{i};
              sep_val = mean(samples.vals);
              k = numel(this.regions);
             if  (numel(samples.vals)>=init_samples)
                  k = k+1;
                 [this.regions{i},this.regions{k}] = this.OptimRect(samples,bounds,sep_val);
                 this.clusters{i} = this.RemSamples(this.regions{i},samples);
                 this.clusters{k} = this.RemSamples(this.regions{k},samples);
                 if ~isempty(this.clusters{i}.vals)
                 lb(i) = min(this.clusters{i}.vals);
                 end
                 if ~isempty(this.clusters{k}.vals)
                 lb(k) = min(this.clusters{k}.vals);
                 else
                  lb(k) = lb(i);
                 end
             end       
        end


          
        % For each rectangle, compute coverage and (mean-expected deviation
        % below mean).
          for i = 1:numel(this.regions)
              bounds = this.regions{i};
              samples = this.clusters{i};
              c(i) = log(numel(samples.vals)+1)/...
                         max(1,sum(log((bounds(:,2)-bounds(:,1))./eps+1)));
              if ~isempty(samples.pts)
                  list = samples.vals;
                  avg = mean(list);
                  v(i) = avg-mean(max(0, avg-list));
              else 
                  avg(i) = 1;
                  v(i) = 1;
              end
          end
          
        % Compute probabilities of sampling.
         P_c = (1-c)/sum(1-c); % Coverage based probability.            
         P_r = (1./v)/sum(1./v); % Robustness based probability.
         P_total = rob_wt*P_r + (1-rob_wt)*P_c; % Weighted probability.
         
       % Distribute the number of sampling points according to sampling
       % probability.
         samp_nums = max(floor(P_total*init_samples),1);
         
       % Find singular regions.
         avg_lb = mean(lb); dev_lb = mean(max(avg_lb-lb,0));         
         singular = min(lb-dev_lb,lb-avg_lb+3*dev_lb)<=0; % logic vector indicating singular region.
         
       
       % Sample according to samp_nums and update the clusters.  If a
       % falsifier is located, then stop and return the falsifier value
       % and region containing falsifier.
         for i = 1:numel(this.regions) 
           bounds = this.regions{i};
           samples = this.clusters{i};
           time = toc;
           run = (time<max_time) && num_sim<max_simulations && ~this.falsified;
           if run
        % Perform probability based sampling
           sim_num = min(samp_nums(i),max_simulations-num_sim);
           [this,list,this.falsified,nb_added,this.falsifier] =... 
           this.PseudoRandSamp(CBS,param_names,bounds,phi,sim_num,max_time,init_samples);
                                                      
           num_sim = num_sim+nb_added;
              if nb_added>0
                 samples.pts = [samples.pts; list.pts];
                 samples.vals = [samples.vals; list.vals];
                 this.all_samples.pts = [this.all_samples.pts; list.pts];
                 this.all_samples.vals = [this.all_samples.vals; list.vals];
                 this.new_samples.pts = [this.all_samples.pts; list.pts];
                 this.new_samples.vals = [this.all_samples.vals; list.vals];
                 lb(i) = min(samples.vals);
              end
           end
           
           run = (time<max_time) && num_sim<max_simulations && ~this.falsified;
           %this.falsified
           
          if (singular(i)) && run
          % Perform singularity based sampling
               disp('singlular')
               nb = init_samples-numel(samples.vals);
               sim_num = min(nb,max_simulations-num_sim);
              [this,list,this.falsified,nb_added,this.falsifier] = ...
              this.PseudoRandSamp(CBS,param_names,bounds,phi,sim_num,max_time,4*init_samples);
          
               if ~isempty(list)
                  samples.pts = [samples.pts; list.pts];
                  samples.vals = [samples.vals; list.vals];
                  num_sim = num_sim+nb_added;
                  this.all_samples.pts = [this.all_samples.pts; list.pts];
                  this.all_samples.vals = [this.all_samples.vals; list.vals];
                  this.new_samples.pts = [this.all_samples.pts; list.pts];
                  this.new_samples.vals = [this.all_samples.vals; list.vals];
                  try
                  lb(i) = min(samples.vals);  
                  catch
                      tempJPK = 1;
                  end
               end
                                               
              end
              
              this.clusters{i} = samples;
              if this.falsified
                  this.falsifier_region = this.regions{i};
                  disp('Falsified (and exit from StatFalsify')
                  return;
                  %break;
              end
              
         end
         run = (time<max_time) && num_sim<max_simulations && ~this.falsified ; 
        end
             this.num_samples = size(this.all_samples.vals);
             for i = 1:numel(this.regions)
                 if ~isempty(this.clusters{i}.pts)
                     bounds = this.regions{i};
                     samples = this.clusters{i};
                     this.coverage(i) = log(numel(samples.vals)+1)/...
                                         max(1,sum(log((bounds(:,2)-bounds(:,1))./eps+1)));
                     [~,ind] = min(samples.vals);
                     this.lower_bounds.pts(i,:) = samples.pts(ind,:);
                     this.lower_bounds.vals(i) = samples.vals(ind,:);                     
                 else
                  this.lower_bounds.pts(i,:) = [];
                  this.lower_bounds.vals(i) = inf;
                 end                
             end
             
   end
         
   end
 
end
        
        