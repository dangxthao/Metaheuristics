#include "__cf_KD_cl_harness_forthao_breach.h"
#include "rt_look1d32.h"
real32_T rt_Lookup32 ( const real32_T * x , int_T xlen , real32_T u , const
real32_T * y ) { int_T idx = rt_GetLookupIndex32 ( x , xlen , u ) ; real32_T
num = y [ idx + 1 ] - y [ idx ] ; real32_T den = x [ idx + 1 ] - x [ idx ] ;
real32_T m = num / den ; return ( y [ idx ] + m * ( u - x [ idx ] ) ) ; }
