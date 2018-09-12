#include "__cf_KD_cl_harness_forthao_breach.h"
#include "rt_look2d32_normal.h"
real32_T rt_Lookup2D32_Normal ( const real32_T * xVals , const int_T numX ,
const real32_T * yVals , const int_T numY , const real32_T * zVals , const
real32_T x , const real32_T y ) { int_T xIdx , yIdx ; real32_T ylo , yhi ;
real32_T Zx0yhi , Zx0ylo , xlo , xhi ; real32_T corner1 , corner2 ; xIdx =
rt_GetLookupIndex32 ( xVals , numX , x ) ; xlo = xVals [ xIdx ] ; xhi = xVals
[ xIdx + 1 ] ; yIdx = rt_GetLookupIndex32 ( yVals , numY , y ) ; ylo = yVals
[ yIdx ] ; yhi = yVals [ yIdx + 1 ] ; corner1 = * ( zVals + xIdx + ( numX *
yIdx ) ) ; corner2 = * ( zVals + ( xIdx + 1 ) + ( numX * yIdx ) ) ; Zx0ylo =
INTERP ( x , xlo , xhi , corner1 , corner2 ) ; corner1 = * ( zVals + xIdx + (
numX * ( yIdx + 1 ) ) ) ; corner2 = * ( zVals + ( xIdx + 1 ) + ( numX * (
yIdx + 1 ) ) ) ; Zx0yhi = INTERP ( x , xlo , xhi , corner1 , corner2 ) ;
return ( INTERP ( y , ylo , yhi , Zx0ylo , Zx0yhi ) ) ; }
