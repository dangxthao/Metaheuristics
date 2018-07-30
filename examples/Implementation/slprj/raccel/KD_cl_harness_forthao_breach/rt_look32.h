#include "__cf_KD_cl_harness_forthao_breach.h"
#ifndef RTW_HEADER_rt_look32_h_
#define RTW_HEADER_rt_look32_h_
#include "rtwtypes.h"
#ifdef DOINTERPSEARCH
#include <float.h>
#endif
#ifndef INTERP
#define INTERP(x,x1,x2,y1,y2)         ( (y1)+(((y2) - (y1))/((x2) - (x1)))*((x)-(x1)) )
#endif
#ifndef ZEROTECHNIQUE
#define ZEROTECHNIQUE
typedef enum { NORMAL_INTERP , AVERAGE_VALUE , MIDDLE_VALUE } ZeroTechnique ;
#endif
extern int_T rt_GetLookupIndex32 ( const real32_T * x , int_T xlen , real32_T
u ) ;
#endif
