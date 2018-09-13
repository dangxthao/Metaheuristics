%%
% From  STL_Formula to BreachRequirement ...

phi = STL_Formula('phi',  'alw_[0, 10] (speed[t]<100)' );
R = BreachRequirement(phi);

%%
% ... and back
phi_from_R =  R.req_monitors{1}.formula;

