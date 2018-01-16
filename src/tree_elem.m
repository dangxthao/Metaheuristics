classdef tree_elem
     
    properties
        time     
        value
        rob 
    end
    methods
        function elem = tree_elem(time, value)
            elem.time = time;
            elem.value = value;
            elem.rob = [];
        end
        
        function str = num2str(this) % tricks tree.tostring 
          str = [ '(' num2str(this.time) ',' num2str(this.value) ')'];
        end
        
        function b =  eq(this, that)    
            b = this.time == that.time && this.value == this.value;
        end   
    end
    
end