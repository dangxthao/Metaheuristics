#include "__cf_KD_cl_harness_forthao_breach.h"
#ifndef RTW_HEADER_KD_cl_harness_forthao_breach_acc_private_h_
#define RTW_HEADER_KD_cl_harness_forthao_breach_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#if !defined(ss_VALIDATE_MEMORY)
#define ss_VALIDATE_MEMORY(S, ptr)   if(!(ptr)) {\
  ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
  }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((ptr));\
  (ptr) = (NULL);\
  }
#else
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((void *)(ptr));\
  (ptr) = (NULL);\
  }
#endif
#endif
#ifndef UCHAR_MAX
#include <limits.h>
#endif
#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if 0
#if ( ULONG_MAX != (0xFFFFFFFFFFFFFFFFUL) ) || ( LONG_MAX != (0x7FFFFFFFFFFFFFFFL) )
#error Code was generated for compiler with different sized ulong/long. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#endif
#if 0
#if ( ULLONG_MAX != (0xFFFFFFFFFFFFFFFFUL) ) || ( LLONG_MAX != (0x7FFFFFFFFFFFFFFFL) )
#error Code was generated for compiler with different sized ulong_long/long_long. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#endif
#ifndef rtInterpolate
#define rtInterpolate(v1,v2,f1,f2)   (((v1)==(v2))?((double)(v1)):  (((f1)*((double)(v1)))+((f2)*((double)(v2)))))
#endif
#ifndef rtRound
#define rtRound(v) ( ((v) >= 0) ?   muDoubleScalarFloor((v) + 0.5) :   muDoubleScalarCeil((v) - 0.5) )
#endif
extern real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) ; void
KD_cl_harness_forthao_breach_acc_BINARYSEARCH_real32_T ( uint32_T * piLeft ,
uint32_T * piRght , real32_T u , const real32_T * pData , uint32_T iHi ) ;
void KD_cl_harness_forthao_breach_acc_LookUp_real32_T_real32_T ( real32_T *
pY , const real32_T * pYData , real32_T u , const real32_T * pUData ,
uint32_T iHi ) ; void
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( real32_T
* pY , const real32_T * pYData , real32_T u0 , const real32_T * pU0Data ,
uint32_T iHiU0 , real32_T u1 , const real32_T * pU1Data , uint32_T iHiU1 ) ;
void nbrxxgteth ( SimStruct * const S ) ; void hldppkqdr4 ( SimStruct * const
S ) ; void pg1kwe2jso ( real32_T egaxndeq0x , int32_T k1cglknueh , real32_T *
ddh0mvgbbl , int32_T * j4vxg2gmyl ) ; void ivkef2hmn4 ( jcvtjjdhjy * localDW
, ev5xuv0chq * localP ) ; void foiteff4aq ( real_T ow310q0jgt , jcvtjjdhjy *
localDW ) ; void masm1qwyo5 ( g4kb1dhx4k * localB , jcvtjjdhjy * localDW ,
ev5xuv0chq * localP ) ;
#endif
