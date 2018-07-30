#include "__cf_KD_cl_harness_forthao_breach.h"
#include "rt_logging_mmi.h"
#include "KD_cl_harness_forthao_breach_capi.h"
#include <math.h>
#include "KD_cl_harness_forthao_breach.h"
#include "KD_cl_harness_forthao_breach_private.h"
#include "KD_cl_harness_forthao_breach_dt.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 10 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 6 ; const char_T
* gbl_raccel_Version = "8.5 (R2015a) 09-Feb-2015" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const char * gblSlvrJacPatternFileName =
 "slprj//raccel//KD_cl_harness_forthao_breach//KD_cl_harness_forthao_breach_Jpattern.mat"
; const int_T gblNumRootInportBlks = 2 ; const int_T gblNumModelInputs = 2 ;
extern rtInportTUtable * gblInportTUtables ; extern const char *
gblInportFileName ; const int_T gblInportDataTypeIdx [ ] = { 0 , 0 } ; const
int_T gblInportDims [ ] = { 1 , 1 , 1 , 1 } ; const int_T gblInportComplex [
] = { 0 , 0 } ; const int_T gblInportInterpoFlag [ ] = { 0 , 0 } ; const
int_T gblInportContinuous [ ] = { 1 , 1 } ;
#include "simstruc.h"
#include "fixedpoint.h"
void MdlOutputsParameterSampleTime ( int_T tid ) { UNUSED_PARAMETER ( tid ) ;
} B rtB ; X rtX ; DW rtDW ; ExtU rtU ; ExtY rtY ; static SimStruct model_S ;
SimStruct * const rtS = & model_S ; static real_T fqbwtfdojd ( const real_T x
[ 3 ] ) ; static real_T m0rufl5oqo ( const real_T x [ 3 ] ) ; void
BINARYSEARCH_real32_T ( uint32_T * piLeft , uint32_T * piRght , real32_T u ,
const real32_T * pData , uint32_T iHi ) { * piLeft = 0U ; * piRght = iHi ; if
( u <= pData [ 0 ] ) { * piRght = 0U ; } else if ( u >= pData [ iHi ] ) { *
piLeft = iHi ; } else { uint32_T i ; while ( ( * piRght - * piLeft ) > 1U ) {
i = ( * piLeft + * piRght ) >> 1 ; if ( u < pData [ i ] ) { * piRght = i ; }
else { * piLeft = i ; } } } } void LookUp_real32_T_real32_T ( real32_T * pY ,
const real32_T * pYData , real32_T u , const real32_T * pUData , uint32_T iHi
) { uint32_T iLeft ; uint32_T iRght ; BINARYSEARCH_real32_T ( & ( iLeft ) , &
( iRght ) , u , pUData , iHi ) ; { real32_T lambda ; if ( pUData [ iRght ] >
pUData [ iLeft ] ) { real32_T num ; real32_T den ; den = pUData [ iRght ] ;
den -= pUData [ iLeft ] ; num = u ; num -= pUData [ iLeft ] ; lambda = num /
den ; } else { lambda = 0.0F ; } { real32_T yLeftCast ; real32_T yRghtCast ;
yLeftCast = pYData [ iLeft ] ; yRghtCast = pYData [ iRght ] ; yLeftCast +=
lambda * ( yRghtCast - yLeftCast ) ; ( * pY ) = yLeftCast ; } } } void
Look2D_real32_T_real32_T_real32_T ( real32_T * pY , const real32_T * pYData ,
real32_T u0 , const real32_T * pU0Data , uint32_T iHiU0 , real32_T u1 , const
real32_T * pU1Data , uint32_T iHiU1 ) { uint32_T iLeftU0 , iRghtU0 , iLeftU1
, iRghtU1 ; BINARYSEARCH_real32_T ( & ( iLeftU0 ) , & ( iRghtU0 ) , u0 ,
pU0Data , iHiU0 ) ; BINARYSEARCH_real32_T ( & ( iLeftU1 ) , & ( iRghtU1 ) ,
u1 , pU1Data , iHiU1 ) ; { real32_T u0Left = pU0Data [ iLeftU0 ] ; real32_T
u0Rght = pU0Data [ iRghtU0 ] ; real32_T u1Left = pU1Data [ iLeftU1 ] ;
real32_T u1Rght = pU1Data [ iRghtU1 ] ; real32_T yTemp ; real32_T yLeftLeft ;
real32_T yLeftRght ; real32_T yRghtLeft ; real32_T yRghtRght ; real32_T
u1Lambda ; real32_T u0Lambda ; if ( u1Rght > u1Left ) { real32_T num ;
real32_T den ; den = u1Rght ; den -= u1Left ; num = u1 ; num -= u1Left ;
u1Lambda = num / den ; } else { u1Lambda = 0.0F ; } if ( u0Rght > u0Left ) {
real32_T num ; real32_T den ; den = u0Rght ; den -= u0Left ; num = u0 ; num
-= u0Left ; u0Lambda = num / den ; } else { u0Lambda = 0.0F ; } iHiU0 ++ ;
iLeftU1 *= iHiU0 ; iRghtU1 *= iHiU0 ; yRghtLeft = pYData [ ( iRghtU0 +
iLeftU1 ) ] ; yRghtRght = pYData [ ( iRghtU0 + iRghtU1 ) ] ; yLeftLeft =
pYData [ ( iLeftU0 + iLeftU1 ) ] ; yLeftRght = pYData [ ( iLeftU0 + iRghtU1 )
] ; { real32_T yLeftCast ; real32_T yRghtCast ; yLeftCast = yLeftLeft ;
yRghtCast = yLeftRght ; yLeftCast += u1Lambda * ( yRghtCast - yLeftCast ) ; (
* pY ) = yLeftCast ; } { real32_T yLeftCast ; real32_T yRghtCast ; yLeftCast
= yRghtLeft ; yRghtCast = yRghtRght ; yLeftCast += u1Lambda * ( yRghtCast -
yLeftCast ) ; yTemp = yLeftCast ; } { real32_T yLeftCast ; real32_T yRghtCast
; yLeftCast = ( * pY ) ; yRghtCast = yTemp ; yLeftCast += u0Lambda * (
yRghtCast - yLeftCast ) ; ( * pY ) = yLeftCast ; } } } void etyvz2h2c5 (
real_T j40pt5r01j , real_T bvxdutgsny , real_T lauqw5yggf , const real_T
epk0u0cypb [ 9 ] , const real_T mcjdtgapir [ 18 ] , real_T mdeqkjqoah ,
mbkhwxmspr * localB ) { real_T Kern [ 9 ] ; int32_T n ; real_T tmp ; memset (
& Kern [ 0 ] , 0 , 9U * sizeof ( real_T ) ) ; for ( n = 0 ; n < ( int32_T )
lauqw5yggf ; n ++ ) { Kern [ n ] = muDoubleScalarExp ( ( - ( bvxdutgsny -
mcjdtgapir [ n + 9 ] ) * ( bvxdutgsny - mcjdtgapir [ n + 9 ] ) + - (
j40pt5r01j - mcjdtgapir [ n ] ) * ( j40pt5r01j - mcjdtgapir [ n ] ) ) / (
mdeqkjqoah * mdeqkjqoah * 2.0 * 50.0 ) ) ; } tmp = 0.0 ; for ( n = 0 ; n < 9
; n ++ ) { tmp += epk0u0cypb [ n ] * Kern [ n ] ; } localB -> e2b5x1uxlg =
tmp ; } void nbrxxgteth ( SimStruct * const rtS ) { if ( ssGetTaskTime ( rtS
, 2 ) != ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } void
hldppkqdr4 ( SimStruct * const rtS ) { ssSetSolverNeedsReset ( rtS ) ; } void
pg1kwe2jso ( real32_T egaxndeq0x , int32_T k1cglknueh , real32_T * ddh0mvgbbl
, int32_T * j4vxg2gmyl ) { * ddh0mvgbbl = egaxndeq0x ; * j4vxg2gmyl =
k1cglknueh ; } void ivkef2hmn4 ( jcvtjjdhjy * localDW , ev5xuv0chq * localP )
{ localDW -> afjuedjd2w = localP -> UnitDelay_InitialCondition ; localDW ->
akpttb2uyr = localP -> RateLimiter_IC ; } void masm1qwyo5 ( g4kb1dhx4k *
localB , jcvtjjdhjy * localDW , ev5xuv0chq * localP ) { real_T
rateLimiterRate ; rateLimiterRate = localDW -> afjuedjd2w - localDW ->
akpttb2uyr ; if ( rateLimiterRate > localP -> RateLimiter_RisingLim ) {
localB -> odrmud5052 = localDW -> akpttb2uyr + localP ->
RateLimiter_RisingLim ; } else if ( rateLimiterRate < localP ->
RateLimiter_FallingLim ) { localB -> odrmud5052 = localDW -> akpttb2uyr +
localP -> RateLimiter_FallingLim ; } else { localB -> odrmud5052 = localDW ->
afjuedjd2w ; } localDW -> akpttb2uyr = localB -> odrmud5052 ; } void
foiteff4aq ( real_T ow310q0jgt , jcvtjjdhjy * localDW ) { localDW ->
afjuedjd2w = ow310q0jgt ; } real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u
) { uint32_T lo ; uint32_T hi ; lo = * u % 127773U * 16807U ; hi = * u /
127773U * 2836U ; if ( lo < hi ) { * u = 2147483647U - ( hi - lo ) ; } else {
* u = lo - hi ; } return ( real_T ) * u * 4.6566128752457969E-10 ; } static
real_T fqbwtfdojd ( const real_T x [ 3 ] ) { real_T y ; int8_T idx_idx_1 ;
int8_T idx_idx_2 ; if ( ( x [ 0 ] <= x [ 1 ] ) || muDoubleScalarIsNaN ( x [ 1
] ) ) { if ( ( x [ 1 ] <= x [ 2 ] ) || muDoubleScalarIsNaN ( x [ 2 ] ) ) {
idx_idx_1 = 2 ; idx_idx_2 = 3 ; } else if ( ( x [ 0 ] <= x [ 2 ] ) ||
muDoubleScalarIsNaN ( x [ 2 ] ) ) { idx_idx_1 = 3 ; idx_idx_2 = 2 ; } else {
idx_idx_1 = 1 ; idx_idx_2 = 2 ; } } else if ( ( x [ 0 ] <= x [ 2 ] ) ||
muDoubleScalarIsNaN ( x [ 2 ] ) ) { idx_idx_1 = 1 ; idx_idx_2 = 3 ; } else if
( ( x [ 1 ] <= x [ 2 ] ) || muDoubleScalarIsNaN ( x [ 2 ] ) ) { idx_idx_1 = 3
; idx_idx_2 = 1 ; } else { idx_idx_1 = 2 ; idx_idx_2 = 1 ; } if (
muDoubleScalarIsNaN ( x [ idx_idx_2 - 1 ] ) ) { y = x [ idx_idx_2 - 1 ] ; }
else { y = x [ idx_idx_1 - 1 ] ; } return y ; } static real_T m0rufl5oqo (
const real_T x [ 3 ] ) { real_T y ; int8_T idx_idx_1 ; int8_T idx_idx_2 ; if
( ( x [ 0 ] <= x [ 1 ] ) || muDoubleScalarIsNaN ( x [ 1 ] ) ) { if ( ( x [ 1
] <= x [ 2 ] ) || muDoubleScalarIsNaN ( x [ 2 ] ) ) { idx_idx_1 = 2 ;
idx_idx_2 = 3 ; } else if ( ( x [ 0 ] <= x [ 2 ] ) || muDoubleScalarIsNaN ( x
[ 2 ] ) ) { idx_idx_1 = 3 ; idx_idx_2 = 2 ; } else { idx_idx_1 = 1 ;
idx_idx_2 = 2 ; } } else if ( ( x [ 0 ] <= x [ 2 ] ) || muDoubleScalarIsNaN (
x [ 2 ] ) ) { idx_idx_1 = 1 ; idx_idx_2 = 3 ; } else if ( ( x [ 1 ] <= x [ 2
] ) || muDoubleScalarIsNaN ( x [ 2 ] ) ) { idx_idx_1 = 3 ; idx_idx_2 = 1 ; }
else { idx_idx_1 = 2 ; idx_idx_2 = 1 ; } if ( muDoubleScalarIsNaN ( x [
idx_idx_2 - 1 ] ) ) { y = x [ idx_idx_2 - 1 ] ; } else { y = x [ idx_idx_1 -
1 ] ; } return y ; } void MdlInitialize ( void ) { uint32_T tseed ; int32_T r
; int32_T t ; real_T tmp ; rtX . mupnfilrqo = rtP . Integrator1_IC ; rtX .
huyhg2ps31 = rtP . Integrator2_IC ; rtDW . cc0wkfbxf2 = rtP . Memory_X0 ;
rtDW . eac1jvpkom = rtP . Memory_X0_h1tbtxp2t3 ; ivkef2hmn4 ( & rtDW .
masm1qwyo5u , ( ev5xuv0chq * ) & rtP . masm1qwyo5u ) ; ivkef2hmn4 ( & rtDW .
cdbewnv5xj , ( ev5xuv0chq * ) & rtP . cdbewnv5xj ) ; ivkef2hmn4 ( & rtDW .
lwrmmrtmge , ( ev5xuv0chq * ) & rtP . lwrmmrtmge ) ; rtX . lgbs44xptg = rtP .
p_prethrottlekPa1_IC ; rtX . ka43gmkysq = rtP . Integrator1_IC_mhqedcm0z1 ;
rtX . iqp0o3u0ph = rtP . Integrator_IC ; rtX . iynqfp2xbi = rtP .
Integrator_IC_heumtkcm2e ; rtDW . avtbwzqnkf [ 0 ] = rtP .
UnitDelay1_InitialCondition [ 0 ] ; rtDW . avtbwzqnkf [ 1 ] = rtP .
UnitDelay1_InitialCondition [ 1 ] ; rtDW . poa5fptxm4 = rtP .
Delay1_InitialCondition ; rtDW . bsbxmlf10r = rtP .
UnitDelay4_InitialCondition ; rtDW . pybwwu5s4d = rtP .
UnitDelay3_InitialCondition ; rtDW . j5f3ay4xaq = rtP .
UnitDelay5_InitialCondition ; rtDW . ackerqxqlr = rtP .
UnitDelay5_InitialCondition_kpkvgiix5s ; rtDW . c1qvpfpyqu = rtP .
UnitDelay1_InitialCondition_jptrwhyymm ; rtDW . em10zry3vm = rtP .
UnitDelay2_InitialCondition ; rtDW . cz55ow2si1 [ 0 ] = rtP .
UnitDelay_InitialCondition_ezolpyxjya [ 0 ] ; rtDW . cz55ow2si1 [ 1 ] = rtP .
UnitDelay_InitialCondition_ezolpyxjya [ 1 ] ; rtDW . cz55ow2si1 [ 2 ] = rtP .
UnitDelay_InitialCondition_ezolpyxjya [ 2 ] ; rtDW . h4gbii3cbq = rtP .
UnitDelay3_InitialCondition_ffvh0pkag0 ; rtDW . o04t4yciip = rtP .
UnitDelay2_InitialCondition_pgqysx40c3 ; rtDW . lzwd5z4dbk = rtP .
Delay1_InitialCondition_cabzb21box ; rtDW . dgfekwwlr1 = rtP .
UnitDelay8_InitialCondition ; rtDW . dw2dt5amj1 = rtP .
Delay1_InitialCondition_plljnknkib ; rtDW . letoggxozl = rtP .
UnitDelay9_InitialCondition ; rtDW . frjwyakiph = rtP .
Delay1_InitialCondition_btda0c1p1a ; rtDW . i5yn1movmy = rtP .
UnitDelay1_InitialCondition_lugtrxmixa ; rtDW . diffnla35e = rtP .
UnitDelay3_InitialCondition_dnd305am25 ; rtDW . nqyjhyuvcj = rtP .
Delay11_InitialCondition ; rtDW . fjcoqtw2bx = rtP . Delay21_InitialCondition
; rtDW . iggiejtmqu = rtP . UnitDelay10_InitialCondition ; if (
ssIsFirstInitCond ( rtS ) ) { rtB . fnzk1kwery [ 0 ] = rtP .
Merge_InitialOutput [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
Merge_InitialOutput [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
Merge_InitialOutput [ 2 ] ; } if ( ssIsFirstInitCond ( rtS ) ) { rtB .
dzd1zqtqmx [ 0 ] = rtP . Merge_InitialOutput_iz5qfjawh0 [ 0 ] ; rtB .
dzd1zqtqmx [ 1 ] = rtP . Merge_InitialOutput_iz5qfjawh0 [ 1 ] ; rtB .
dzd1zqtqmx [ 2 ] = rtP . Merge_InitialOutput_iz5qfjawh0 [ 2 ] ; } rtDW .
mvpjwhrzk3 = rtP . UnitDelay6_InitialCondition ; rtDW . mtqhixagy1 = rtP .
UnitDelay7_InitialCondition ; rtDW . fhgbtmls3d = rtP .
Delay1_InitialCondition_ortecfcub3 ; rtDW . l1sigmyvxe = rtP .
Delay1_InitialCondition_enn30ozomz ; rtDW . noqny2ee14 = rtP .
UnitDelay_InitialCondition_jua2isvxie ; rtDW . ljbykua013 = rtP .
UnitDelay1_InitialCondition_onlqmfj3vv ; rtX . cgw3asjtrv = rtP .
Integrator_IC_nxixalf5pn ; rtDW . h1201vgmm4 = rtP . Memory_X0_kgirpjp1em ;
rtX . ge52s03ms5 = rtP . Integrator1_IC_ficjnaw5sq ; tmp =
muDoubleScalarFloor ( rtP . UniformRandomNumber_Seed ) ; if (
muDoubleScalarIsNaN ( tmp ) || muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; }
else { tmp = muDoubleScalarRem ( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0
? ( uint32_T ) - ( int32_T ) ( uint32_T ) - tmp : ( uint32_T ) tmp ; r = (
int32_T ) ( tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( (
( ( tseed - ( ( uint32_T ) r << 16U ) ) + t ) << 16U ) + t ) + r ; if ( tseed
< 1U ) { tseed = 1144108930U ; } else { if ( tseed > 2147483646U ) { tseed =
2147483646U ; } } rtDW . msu4qgbkxt = tseed ; rtDW . beiefj4kfo = ( rtP .
UniformRandomNumber_Maximum - rtP . UniformRandomNumber_Minimum ) *
rt_urand_Upu32_Yd_f_pw_snf ( & rtDW . msu4qgbkxt ) + rtP .
UniformRandomNumber_Minimum ; tmp = muDoubleScalarFloor ( rtP .
UniformRandomNumber1_Seed ) ; if ( muDoubleScalarIsNaN ( tmp ) ||
muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; } else { tmp = muDoubleScalarRem
( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0 ? ( uint32_T ) - ( int32_T ) (
uint32_T ) - tmp : ( uint32_T ) tmp ; r = ( int32_T ) ( tseed >> 16U ) ; t =
( int32_T ) ( tseed & 32768U ) ; tseed = ( ( ( ( tseed - ( ( uint32_T ) r <<
16U ) ) + t ) << 16U ) + t ) + r ; if ( tseed < 1U ) { tseed = 1144108930U ;
} else { if ( tseed > 2147483646U ) { tseed = 2147483646U ; } } rtDW .
grioepryal = tseed ; rtDW . d2tl5o0hel = ( rtP . UniformRandomNumber1_Maximum
- rtP . UniformRandomNumber1_Minimum ) * rt_urand_Upu32_Yd_f_pw_snf ( & rtDW
. grioepryal ) + rtP . UniformRandomNumber1_Minimum ; } void MdlStart ( void
) { { FWksInfo * fromwksInfo ; if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1
, sizeof ( FWksInfo ) ) ) == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "[ECUTIME s2g_eqfine_eqfine]" ;
fromwksInfo -> origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ;
fromwksInfo -> origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T )
; fromwksInfo -> data = ( void * ) rtP . FromWorkspace1_Data0 ; fromwksInfo
-> nDataPoints = 24166 ; fromwksInfo -> time = ( double * ) rtP .
FromWorkspace1_Time0 ; rtDW . hvzkbecm4i . TimePtr = fromwksInfo -> time ;
rtDW . hvzkbecm4i . DataPtr = fromwksInfo -> data ; rtDW . hvzkbecm4i .
RSimInfoPtr = fromwksInfo ; } rtDW . bfsa3u0wlu . PrevIndex = 0 ; } {
FWksInfo * fromwksInfo ; if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1 ,
sizeof ( FWksInfo ) ) ) == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "[ECUTIME s2g_ene_ene]" ; fromwksInfo
-> origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) rtP . FromWorkspace3_Data0 ; fromwksInfo -> nDataPoints
= 24166 ; fromwksInfo -> time = ( double * ) rtP . FromWorkspace3_Time0 ;
rtDW . b2ezf5nkn2 . TimePtr = fromwksInfo -> time ; rtDW . b2ezf5nkn2 .
DataPtr = fromwksInfo -> data ; rtDW . b2ezf5nkn2 . RSimInfoPtr = fromwksInfo
; } rtDW . h4uocsxftg . PrevIndex = 0 ; } { FWksInfo * fromwksInfo ; if ( (
fromwksInfo = ( FWksInfo * ) calloc ( 1 , sizeof ( FWksInfo ) ) ) == ( NULL )
) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "[0   97.4216]" ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) & rtP . FromWorkspace11_Data0 ; fromwksInfo ->
nDataPoints = 1 ; fromwksInfo -> time = ( double * ) & rtP .
FromWorkspace11_Time0 ; rtDW . dlyfy0ipc5 . TimePtr = fromwksInfo -> time ;
rtDW . dlyfy0ipc5 . DataPtr = fromwksInfo -> data ; rtDW . dlyfy0ipc5 .
RSimInfoPtr = fromwksInfo ; } rtDW . fwkxoupfre . PrevIndex = 0 ; } {
FWksInfo * fromwksInfo ; if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1 ,
sizeof ( FWksInfo ) ) ) == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "[0  296.9595]" ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) & rtP . FromWorkspace12_Data0 ; fromwksInfo ->
nDataPoints = 1 ; fromwksInfo -> time = ( double * ) & rtP .
FromWorkspace12_Time0 ; rtDW . oi2egj2zap . TimePtr = fromwksInfo -> time ;
rtDW . oi2egj2zap . DataPtr = fromwksInfo -> data ; rtDW . oi2egj2zap .
RSimInfoPtr = fromwksInfo ; } rtDW . fb1c24lf0o . PrevIndex = 0 ; } rtDW .
ehd3s5jupn = rtP . UnitDelay_InitialCondition ; rtDW . awpbtqxcnq = - 1 ;
rtDW . g0pejldppu = - 1 ; rtDW . owlkbndpg5 = rtP .
UnitDelay_InitialCondition_j4qityl4pb ; rtDW . kqdf0adzeb = - 1 ; rtB .
dgqpk3ff5k = rtP . region_Y0 ; rtDW . dqd4zebieo = - 1 ; rtDW . gme5mt5rhg =
rtP . rv_register_InitialCondition ; rtDW . n4b14msae2 = rtP .
reg_register_InitialCondition ; if ( ssIsFirstInitCond ( rtS ) ) { rtB .
dmnianvpym = rtP . rv_update_merge_InitialOutput ; } if ( ssIsFirstInitCond (
rtS ) ) { rtB . dgqpk3ff5k = rtP . reg_update_merge_InitialOutput ; } rtB .
dgqpk3ff5k = rtP . region_Y0_klozt0y54h ; rtB . dmnianvpym = rtP . rv_Y0 ;
rtDW . kl21dgjfyi = - 1 ; rtDW . loepcnnuit = - 1 ; rtB . fnzk1kwery [ 0 ] =
rtP . Out1_Y0 [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0 [ 1 ] ; rtB .
fnzk1kwery [ 2 ] = rtP . Out1_Y0 [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP .
Out1_Y0_g3ilp1142h [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_g3ilp1142h
[ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_g3ilp1142h [ 2 ] ; rtB .
fnzk1kwery [ 0 ] = rtP . Out1_Y0_o1unubeg55 [ 0 ] ; rtB . fnzk1kwery [ 1 ] =
rtP . Out1_Y0_o1unubeg55 [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
Out1_Y0_o1unubeg55 [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_cfbmbz0s4v
[ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_cfbmbz0s4v [ 1 ] ; rtB .
fnzk1kwery [ 2 ] = rtP . Out1_Y0_cfbmbz0s4v [ 2 ] ; rtB . fnzk1kwery [ 0 ] =
rtP . Out1_Y0_fzdsbyixjn [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
Out1_Y0_fzdsbyixjn [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_fzdsbyixjn
[ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_i20jpg1ssx [ 0 ] ; rtB .
fnzk1kwery [ 1 ] = rtP . Out1_Y0_i20jpg1ssx [ 1 ] ; rtB . fnzk1kwery [ 2 ] =
rtP . Out1_Y0_i20jpg1ssx [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP .
Out1_Y0_et2raie4nn [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_et2raie4nn
[ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_et2raie4nn [ 2 ] ; rtB .
fnzk1kwery [ 0 ] = rtP . Out1_Y0_ky0jsoirgo [ 0 ] ; rtB . fnzk1kwery [ 1 ] =
rtP . Out1_Y0_ky0jsoirgo [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
Out1_Y0_ky0jsoirgo [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_h4dmjfn41x
[ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_h4dmjfn41x [ 1 ] ; rtB .
fnzk1kwery [ 2 ] = rtP . Out1_Y0_h4dmjfn41x [ 2 ] ; rtB . fnzk1kwery [ 0 ] =
rtP . Out1_Y0_an2sth1szw [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
Out1_Y0_an2sth1szw [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_an2sth1szw
[ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_ldubnjtjvb [ 0 ] ; rtB .
fnzk1kwery [ 1 ] = rtP . Out1_Y0_ldubnjtjvb [ 1 ] ; rtB . fnzk1kwery [ 2 ] =
rtP . Out1_Y0_ldubnjtjvb [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP .
Out1_Y0_oszp3rq3fo [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_oszp3rq3fo
[ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_oszp3rq3fo [ 2 ] ; rtB .
fnzk1kwery [ 0 ] = rtP . Out1_Y0_ays1y1015e [ 0 ] ; rtB . fnzk1kwery [ 1 ] =
rtP . Out1_Y0_ays1y1015e [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
Out1_Y0_ays1y1015e [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_cwm0ratokt
[ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_cwm0ratokt [ 1 ] ; rtB .
fnzk1kwery [ 2 ] = rtP . Out1_Y0_cwm0ratokt [ 2 ] ; rtB . fnzk1kwery [ 0 ] =
rtP . Out1_Y0_ib4cx3cul2 [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
Out1_Y0_ib4cx3cul2 [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_ib4cx3cul2
[ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_jbohyy2t2k [ 0 ] ; rtB .
fnzk1kwery [ 1 ] = rtP . Out1_Y0_jbohyy2t2k [ 1 ] ; rtB . fnzk1kwery [ 2 ] =
rtP . Out1_Y0_jbohyy2t2k [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP .
Out1_Y0_fdoepsc2fh [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_fdoepsc2fh
[ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_fdoepsc2fh [ 2 ] ; rtB .
fnzk1kwery [ 0 ] = rtP . Out1_Y0_jjo55kw3ex [ 0 ] ; rtB . fnzk1kwery [ 1 ] =
rtP . Out1_Y0_jjo55kw3ex [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
Out1_Y0_jjo55kw3ex [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_gv2tsfk40f
[ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_gv2tsfk40f [ 1 ] ; rtB .
fnzk1kwery [ 2 ] = rtP . Out1_Y0_gv2tsfk40f [ 2 ] ; rtB . fnzk1kwery [ 0 ] =
rtP . Out1_Y0_lzd5sorf1b [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
Out1_Y0_lzd5sorf1b [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_lzd5sorf1b
[ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_exe1vlznp5 [ 0 ] ; rtB .
fnzk1kwery [ 1 ] = rtP . Out1_Y0_exe1vlznp5 [ 1 ] ; rtB . fnzk1kwery [ 2 ] =
rtP . Out1_Y0_exe1vlznp5 [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP .
Out1_Y0_kda1u3d0rz [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_kda1u3d0rz
[ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_kda1u3d0rz [ 2 ] ; rtB .
fnzk1kwery [ 0 ] = rtP . Out1_Y0_pzvjwx2vmz [ 0 ] ; rtB . fnzk1kwery [ 1 ] =
rtP . Out1_Y0_pzvjwx2vmz [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
Out1_Y0_pzvjwx2vmz [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_fv0ynyqema
[ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_fv0ynyqema [ 1 ] ; rtB .
fnzk1kwery [ 2 ] = rtP . Out1_Y0_fv0ynyqema [ 2 ] ; rtB . fnzk1kwery [ 0 ] =
rtP . Out1_Y0_craatzwyjv [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
Out1_Y0_craatzwyjv [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_craatzwyjv
[ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_mvnq5nqcib [ 0 ] ; rtB .
fnzk1kwery [ 1 ] = rtP . Out1_Y0_mvnq5nqcib [ 1 ] ; rtB . fnzk1kwery [ 2 ] =
rtP . Out1_Y0_mvnq5nqcib [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP .
Out1_Y0_fufsc5q3mt [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_fufsc5q3mt
[ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_fufsc5q3mt [ 2 ] ; rtB .
fnzk1kwery [ 0 ] = rtP . Out1_Y0_hjs1yrsfu4 [ 0 ] ; rtB . fnzk1kwery [ 1 ] =
rtP . Out1_Y0_hjs1yrsfu4 [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
Out1_Y0_hjs1yrsfu4 [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_pppo1wbrr3
[ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_pppo1wbrr3 [ 1 ] ; rtB .
fnzk1kwery [ 2 ] = rtP . Out1_Y0_pppo1wbrr3 [ 2 ] ; rtB . fnzk1kwery [ 0 ] =
rtP . Out1_Y0_fzit3grq2n [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
Out1_Y0_fzit3grq2n [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_fzit3grq2n
[ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_htniehg5e5 [ 0 ] ; rtB .
fnzk1kwery [ 1 ] = rtP . Out1_Y0_htniehg5e5 [ 1 ] ; rtB . fnzk1kwery [ 2 ] =
rtP . Out1_Y0_htniehg5e5 [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP .
Out1_Y0_jw1c5kunqy [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_jw1c5kunqy
[ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_jw1c5kunqy [ 2 ] ; rtB .
fnzk1kwery [ 0 ] = rtP . Out1_Y0_pwzdagqydm [ 0 ] ; rtB . fnzk1kwery [ 1 ] =
rtP . Out1_Y0_pwzdagqydm [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
Out1_Y0_pwzdagqydm [ 2 ] ; rtB . fnzk1kwery [ 0 ] = rtP . Out1_Y0_pehuglceod
[ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP . Out1_Y0_pehuglceod [ 1 ] ; rtB .
fnzk1kwery [ 2 ] = rtP . Out1_Y0_pehuglceod [ 2 ] ; rtB . fnzk1kwery [ 0 ] =
rtP . Out1_Y0_ki3neydkxc [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
Out1_Y0_ki3neydkxc [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . Out1_Y0_ki3neydkxc
[ 2 ] ; rtDW . a1axcz0kbn = - 1 ; rtB . dzd1zqtqmx [ 0 ] = rtP .
Out1_Y0_hmks2vgxo4 [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_hmks2vgxo4
[ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_hmks2vgxo4 [ 2 ] ; rtB .
dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_oneyowtt3q [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] =
rtP . Out1_Y0_oneyowtt3q [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
Out1_Y0_oneyowtt3q [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_eds0rmp0ij
[ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_eds0rmp0ij [ 1 ] ; rtB .
dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_eds0rmp0ij [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] =
rtP . Out1_Y0_bu2mgwj0zv [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
Out1_Y0_bu2mgwj0zv [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_bu2mgwj0zv
[ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_ahmxi3osbt [ 0 ] ; rtB .
dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_ahmxi3osbt [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] =
rtP . Out1_Y0_ahmxi3osbt [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP .
Out1_Y0_mqabdzzuww [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_mqabdzzuww
[ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_mqabdzzuww [ 2 ] ; rtB .
dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_k3deuwitgk [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] =
rtP . Out1_Y0_k3deuwitgk [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
Out1_Y0_k3deuwitgk [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_hlbejplcej
[ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_hlbejplcej [ 1 ] ; rtB .
dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_hlbejplcej [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] =
rtP . Out1_Y0_bb0bagvudq [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
Out1_Y0_bb0bagvudq [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_bb0bagvudq
[ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_huz5txvytd [ 0 ] ; rtB .
dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_huz5txvytd [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] =
rtP . Out1_Y0_huz5txvytd [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP .
Out1_Y0_g4khwpdvgp [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_g4khwpdvgp
[ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_g4khwpdvgp [ 2 ] ; rtB .
dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_gfwj4x0vnc [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] =
rtP . Out1_Y0_gfwj4x0vnc [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
Out1_Y0_gfwj4x0vnc [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_hsoa4pracq
[ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_hsoa4pracq [ 1 ] ; rtB .
dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_hsoa4pracq [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] =
rtP . Out1_Y0_inc00gtcro [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
Out1_Y0_inc00gtcro [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_inc00gtcro
[ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_cdtmzio14w [ 0 ] ; rtB .
dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_cdtmzio14w [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] =
rtP . Out1_Y0_cdtmzio14w [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP .
Out1_Y0_ndyqry4oan [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_ndyqry4oan
[ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_ndyqry4oan [ 2 ] ; rtB .
dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_doti2utdex [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] =
rtP . Out1_Y0_doti2utdex [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
Out1_Y0_doti2utdex [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_lg1jjee3ki
[ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_lg1jjee3ki [ 1 ] ; rtB .
dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_lg1jjee3ki [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] =
rtP . Out1_Y0_jke2qn1f2u [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
Out1_Y0_jke2qn1f2u [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_jke2qn1f2u
[ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_eoiajy4dla [ 0 ] ; rtB .
dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_eoiajy4dla [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] =
rtP . Out1_Y0_eoiajy4dla [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP .
Out1_Y0_ezvh0eoaf3 [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_ezvh0eoaf3
[ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_ezvh0eoaf3 [ 2 ] ; rtB .
dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_lf5joc1kq1 [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] =
rtP . Out1_Y0_lf5joc1kq1 [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
Out1_Y0_lf5joc1kq1 [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_inezqsygfa
[ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_inezqsygfa [ 1 ] ; rtB .
dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_inezqsygfa [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] =
rtP . Out1_Y0_e50mwcz2qh [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
Out1_Y0_e50mwcz2qh [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_e50mwcz2qh
[ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_h5mvojrry4 [ 0 ] ; rtB .
dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_h5mvojrry4 [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] =
rtP . Out1_Y0_h5mvojrry4 [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP .
Out1_Y0_dy01kx4xye [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_dy01kx4xye
[ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_dy01kx4xye [ 2 ] ; rtB .
dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_bhmju4ggll [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] =
rtP . Out1_Y0_bhmju4ggll [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
Out1_Y0_bhmju4ggll [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_ltqatlbxqk
[ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_ltqatlbxqk [ 1 ] ; rtB .
dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_ltqatlbxqk [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] =
rtP . Out1_Y0_jycc30fiih [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
Out1_Y0_jycc30fiih [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_jycc30fiih
[ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_lhqgexa4xs [ 0 ] ; rtB .
dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_lhqgexa4xs [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] =
rtP . Out1_Y0_lhqgexa4xs [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP .
Out1_Y0_d5hs12amdx [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_d5hs12amdx
[ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_d5hs12amdx [ 2 ] ; rtB .
dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_hdbrigas4j [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] =
rtP . Out1_Y0_hdbrigas4j [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
Out1_Y0_hdbrigas4j [ 2 ] ; rtB . dzd1zqtqmx [ 0 ] = rtP . Out1_Y0_av1mg5yp24
[ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP . Out1_Y0_av1mg5yp24 [ 1 ] ; rtB .
dzd1zqtqmx [ 2 ] = rtP . Out1_Y0_av1mg5yp24 [ 2 ] ; { void *
pAobHierarchyNode0 = ( NULL ) ; { char * pathToTopModel = "" ; const char *
sigLogSelectorFileName = rt_GetMatSigLogSelectorFileName ( ) ; void *
pSignalProbeCollection = ( NULL ) ; uint_T signalDimensions0 [ 1 ] = { 1 } ;
rtwAobHierarchyCreateRootNode ( & pAobHierarchyNode0 ) ;
rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1 ) ;
rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" , "pex_hat" ,
pathToTopModel , "KD_cl_harness_forthao_breach/Data Type Conversion21" ,
sigLogSelectorFileName , 1 , & pSignalProbeCollection ) ;
rtwSignalProbeCollectionAddElement ( pSignalProbeCollection , "pex_hat" ,
"zoh" , 1 , 0 , 1 , signalDimensions0 , 0 , "" , "double" ) ;
rtwSignalProbeCollectionVerifyNLeaves ( pSignalProbeCollection , 1 ) ;
rtwSignalProbeCollectionSetAobHierarchy ( pSignalProbeCollection ,
pAobHierarchyNode0 ) ; rtwSignalProbeCollectionFinalizeMetaData (
pSignalProbeCollection ) ; rtDW . jllpsh2lx2 . SignalProbe =
pSignalProbeCollection ; } } { void * pAobHierarchyNode0 = ( NULL ) ; { char
* pathToTopModel = "" ; const char * sigLogSelectorFileName =
rt_GetMatSigLogSelectorFileName ( ) ; void * pSignalProbeCollection = ( NULL
) ; uint_T signalDimensions0 [ 1 ] = { 1 } ; rtwAobHierarchyCreateRootNode (
& pAobHierarchyNode0 ) ; rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1
) ; rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" , "dwdp" ,
pathToTopModel , "KD_cl_harness_forthao_breach/Data Type Conversion22" ,
sigLogSelectorFileName , 1 , & pSignalProbeCollection ) ;
rtwSignalProbeCollectionAddElement ( pSignalProbeCollection , "dwdp" , "zoh"
, 1 , 0 , 1 , signalDimensions0 , 0 , "" , "double" ) ;
rtwSignalProbeCollectionVerifyNLeaves ( pSignalProbeCollection , 1 ) ;
rtwSignalProbeCollectionSetAobHierarchy ( pSignalProbeCollection ,
pAobHierarchyNode0 ) ; rtwSignalProbeCollectionFinalizeMetaData (
pSignalProbeCollection ) ; rtDW . kjuost3l4t . SignalProbe =
pSignalProbeCollection ; } } { void * pAobHierarchyNode0 = ( NULL ) ; { char
* pathToTopModel = "" ; const char * sigLogSelectorFileName =
rt_GetMatSigLogSelectorFileName ( ) ; void * pSignalProbeCollection = ( NULL
) ; uint_T signalDimensions0 [ 1 ] = { 1 } ; rtwAobHierarchyCreateRootNode (
& pAobHierarchyNode0 ) ; rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1
) ; rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" ,
"sim_vnlift" , pathToTopModel , "KD_cl_harness_forthao_breach/From54" ,
sigLogSelectorFileName , 1 , & pSignalProbeCollection ) ;
rtwSignalProbeCollectionAddElement ( pSignalProbeCollection , "sim_vnlift" ,
"zoh" , 1 , 0 , 1 , signalDimensions0 , 0 , "" , "double" ) ;
rtwSignalProbeCollectionVerifyNLeaves ( pSignalProbeCollection , 1 ) ;
rtwSignalProbeCollectionSetAobHierarchy ( pSignalProbeCollection ,
pAobHierarchyNode0 ) ; rtwSignalProbeCollectionFinalizeMetaData (
pSignalProbeCollection ) ; rtDW . gegk3zt5rh . SignalProbe =
pSignalProbeCollection ; } } { void * pAobHierarchyNode0 = ( NULL ) ; { char
* pathToTopModel = "" ; const char * sigLogSelectorFileName =
rt_GetMatSigLogSelectorFileName ( ) ; void * pSignalProbeCollection = ( NULL
) ; uint_T signalDimensions0 [ 1 ] = { 1 } ; rtwAobHierarchyCreateRootNode (
& pAobHierarchyNode0 ) ; rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1
) ; rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" , "In1" ,
pathToTopModel , "KD_cl_harness_forthao_breach/In1" , sigLogSelectorFileName
, 1 , & pSignalProbeCollection ) ; rtwSignalProbeCollectionAddElement (
pSignalProbeCollection , "In1" , "linear" , 1 , 0 , 1 , signalDimensions0 , 0
, "" , "double" ) ; rtwSignalProbeCollectionVerifyNLeaves (
pSignalProbeCollection , 1 ) ; rtwSignalProbeCollectionSetAobHierarchy (
pSignalProbeCollection , pAobHierarchyNode0 ) ;
rtwSignalProbeCollectionFinalizeMetaData ( pSignalProbeCollection ) ; rtDW .
br3dyaxwzn . SignalProbe = pSignalProbeCollection ; } } { void *
pAobHierarchyNode0 = ( NULL ) ; { char * pathToTopModel = "" ; const char *
sigLogSelectorFileName = rt_GetMatSigLogSelectorFileName ( ) ; void *
pSignalProbeCollection = ( NULL ) ; uint_T signalDimensions0 [ 1 ] = { 1 } ;
rtwAobHierarchyCreateRootNode ( & pAobHierarchyNode0 ) ;
rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1 ) ;
rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" , "In2" ,
pathToTopModel , "KD_cl_harness_forthao_breach/In2" , sigLogSelectorFileName
, 1 , & pSignalProbeCollection ) ; rtwSignalProbeCollectionAddElement (
pSignalProbeCollection , "In2" , "linear" , 1 , 0 , 1 , signalDimensions0 , 0
, "" , "double" ) ; rtwSignalProbeCollectionVerifyNLeaves (
pSignalProbeCollection , 1 ) ; rtwSignalProbeCollectionSetAobHierarchy (
pSignalProbeCollection , pAobHierarchyNode0 ) ;
rtwSignalProbeCollectionFinalizeMetaData ( pSignalProbeCollection ) ; rtDW .
msk43x33qs . SignalProbe = pSignalProbeCollection ; } } { void *
pAobHierarchyNode0 = ( NULL ) ; { char * pathToTopModel = "" ; const char *
sigLogSelectorFileName = rt_GetMatSigLogSelectorFileName ( ) ; void *
pSignalProbeCollection = ( NULL ) ; uint_T signalDimensions0 [ 1 ] = { 1 } ;
rtwAobHierarchyCreateRootNode ( & pAobHierarchyNode0 ) ;
rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1 ) ;
rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" , "e_pin" ,
pathToTopModel , "KD_cl_harness_forthao_breach/Sum1" , sigLogSelectorFileName
, 1 , & pSignalProbeCollection ) ; rtwSignalProbeCollectionAddElement (
pSignalProbeCollection , "e_pin" , "linear" , 1 , 0 , 1 , signalDimensions0 ,
0 , "" , "double" ) ; rtwSignalProbeCollectionVerifyNLeaves (
pSignalProbeCollection , 1 ) ; rtwSignalProbeCollectionSetAobHierarchy (
pSignalProbeCollection , pAobHierarchyNode0 ) ;
rtwSignalProbeCollectionFinalizeMetaData ( pSignalProbeCollection ) ; rtDW .
aiqcj0xpj3 . SignalProbe = pSignalProbeCollection ; } } { void *
pAobHierarchyNode0 = ( NULL ) ; { char * pathToTopModel = "" ; const char *
sigLogSelectorFileName = rt_GetMatSigLogSelectorFileName ( ) ; void *
pSignalProbeCollection = ( NULL ) ; uint_T signalDimensions0 [ 1 ] = { 1 } ;
rtwAobHierarchyCreateRootNode ( & pAobHierarchyNode0 ) ;
rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1 ) ;
rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" , "e_egr" ,
pathToTopModel , "KD_cl_harness_forthao_breach/Sum2" , sigLogSelectorFileName
, 1 , & pSignalProbeCollection ) ; rtwSignalProbeCollectionAddElement (
pSignalProbeCollection , "e_egr" , "linear" , 1 , 0 , 1 , signalDimensions0 ,
0 , "" , "double" ) ; rtwSignalProbeCollectionVerifyNLeaves (
pSignalProbeCollection , 1 ) ; rtwSignalProbeCollectionSetAobHierarchy (
pSignalProbeCollection , pAobHierarchyNode0 ) ;
rtwSignalProbeCollectionFinalizeMetaData ( pSignalProbeCollection ) ; rtDW .
imyl4toc4j . SignalProbe = pSignalProbeCollection ; } } { void *
pAobHierarchyNode0 = ( NULL ) ; { char * pathToTopModel = "" ; const char *
sigLogSelectorFileName = rt_GetMatSigLogSelectorFileName ( ) ; void *
pSignalProbeCollection = ( NULL ) ; uint_T signalDimensions0 [ 1 ] = { 13 } ;
rtwAobHierarchyCreateRootNode ( & pAobHierarchyNode0 ) ;
rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1 ) ;
rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" , "expcon_in" ,
pathToTopModel , "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2"
, sigLogSelectorFileName , 14 , & pSignalProbeCollection ) ;
rtwSignalProbeCollectionAddElement ( pSignalProbeCollection , "expcon_in" ,
"zoh" , 1 , 0 , 1 , signalDimensions0 , 0 , "" , "single" ) ;
rtwSignalProbeCollectionVerifyNLeaves ( pSignalProbeCollection , 1 ) ;
rtwSignalProbeCollectionSetAobHierarchy ( pSignalProbeCollection ,
pAobHierarchyNode0 ) ; rtwSignalProbeCollectionFinalizeMetaData (
pSignalProbeCollection ) ; rtDW . juk00hf1bn . SignalProbe =
pSignalProbeCollection ; } } { void * pAobHierarchyNode0 = ( NULL ) ; { char
* pathToTopModel = "" ; const char * sigLogSelectorFileName =
rt_GetMatSigLogSelectorFileName ( ) ; void * pSignalProbeCollection = ( NULL
) ; uint_T signalDimensions0 [ 1 ] = { 3 } ; rtwAobHierarchyCreateRootNode (
& pAobHierarchyNode0 ) ; rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1
) ; rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" ,
"expcon_out" , pathToTopModel ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2" ,
sigLogSelectorFileName , 15 , & pSignalProbeCollection ) ;
rtwSignalProbeCollectionAddElement ( pSignalProbeCollection , "expcon_out" ,
"zoh" , 1 , 0 , 1 , signalDimensions0 , 0 , "" , "single" ) ;
rtwSignalProbeCollectionVerifyNLeaves ( pSignalProbeCollection , 1 ) ;
rtwSignalProbeCollectionSetAobHierarchy ( pSignalProbeCollection ,
pAobHierarchyNode0 ) ; rtwSignalProbeCollectionFinalizeMetaData (
pSignalProbeCollection ) ; rtDW . prcjjqdyp5 . SignalProbe =
pSignalProbeCollection ; } } { void * pAobHierarchyNode0 = ( NULL ) ; { char
* pathToTopModel = "" ; const char * sigLogSelectorFileName =
rt_GetMatSigLogSelectorFileName ( ) ; void * pSignalProbeCollection = ( NULL
) ; uint_T signalDimensions0 [ 1 ] = { 1 } ; rtwAobHierarchyCreateRootNode (
& pAobHierarchyNode0 ) ; rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1
) ; rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" , "region"
, pathToTopModel ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2" ,
sigLogSelectorFileName , 8 , & pSignalProbeCollection ) ;
rtwSignalProbeCollectionAddElement ( pSignalProbeCollection , "region" ,
"zoh" , 1 , 0 , 1 , signalDimensions0 , 0 , "" , "int32" ) ;
rtwSignalProbeCollectionVerifyNLeaves ( pSignalProbeCollection , 1 ) ;
rtwSignalProbeCollectionSetAobHierarchy ( pSignalProbeCollection ,
pAobHierarchyNode0 ) ; rtwSignalProbeCollectionFinalizeMetaData (
pSignalProbeCollection ) ; rtDW . llq51al0ac . SignalProbe =
pSignalProbeCollection ; } } { void * pAobHierarchyNode0 = ( NULL ) ; { char
* pathToTopModel = "" ; const char * sigLogSelectorFileName =
rt_GetMatSigLogSelectorFileName ( ) ; void * pSignalProbeCollection = ( NULL
) ; uint_T signalDimensions0 [ 1 ] = { 1 } ; rtwAobHierarchyCreateRootNode (
& pAobHierarchyNode0 ) ; rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1
) ; rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" ,
"sim_wegr" , pathToTopModel , "KD_cl_harness_forthao_breach/n3" ,
sigLogSelectorFileName , 1 , & pSignalProbeCollection ) ;
rtwSignalProbeCollectionAddElement ( pSignalProbeCollection , "sim_wegr" ,
"linear" , 1 , 0 , 1 , signalDimensions0 , 0 , "" , "double" ) ;
rtwSignalProbeCollectionVerifyNLeaves ( pSignalProbeCollection , 1 ) ;
rtwSignalProbeCollectionSetAobHierarchy ( pSignalProbeCollection ,
pAobHierarchyNode0 ) ; rtwSignalProbeCollectionFinalizeMetaData (
pSignalProbeCollection ) ; rtDW . iz4q3uhlvz . SignalProbe =
pSignalProbeCollection ; } } { RTWLogSignalInfo rt_ScopeSignalInfo ; static
int_T rt_ScopeSignalWidths [ ] = { 2 , 2 , 1 , 1 , 1 } ; static int_T
rt_ScopeSignalNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 2 , 2 , 1 , 1 , 1 } ; static void *
rt_ScopeCurrSigDims [ ] = { ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 , 4 , 4 , 4 , 4 } ;
static const char_T * rt_ScopeSignalLabels [ ] = { "MAP" , "EGR_rate" ,
"u_vnlift" , "u_valve" , "u_throttle" } ; static char_T rt_ScopeSignalTitles
[ ] = "MAPEGR_rateu_vnliftu_valveu_throttle" ; static int_T
rt_ScopeSignalTitleLengths [ ] = { 3 , 8 , 8 , 7 , 10 } ; static boolean_T
rt_ScopeSignalIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 0 , 1 , 0 , 1 , 1 , 1 , 1 } ; BuiltInDTypeId
dTypes [ 5 ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE }
; static char_T rt_ScopeBlockName [ ] = "KD_cl_harness_forthao_breach/Scope"
; rt_ScopeSignalInfo . numSignals = 5 ; rt_ScopeSignalInfo . numCols =
rt_ScopeSignalWidths ; rt_ScopeSignalInfo . numDims =
rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . o02f1axwt1 .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "scope"
, 1 , 0 , 1 , 0.0 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ; if ( rtDW .
o02f1axwt1 . LoggedData == ( NULL ) ) return ; } { RTWLogSignalInfo
rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] = { 3 , 1 , 1 , 1
, 1 } ; static int_T rt_ScopeSignalNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 }
; static int_T rt_ScopeSignalDimensions [ ] = { 3 , 1 , 1 , 1 , 1 } ; static
void * rt_ScopeCurrSigDims [ ] = { ( NULL ) , ( NULL ) , ( NULL ) , ( NULL )
, ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 , 4 , 4 , 4 , 4
} ; static const char_T * rt_ScopeSignalLabels [ ] = { "" , "" , "" , "" , ""
} ; static char_T rt_ScopeSignalTitles [ ] = "" ; static int_T
rt_ScopeSignalTitleLengths [ ] = { 0 , 0 , 0 , 0 , 0 } ; static boolean_T
rt_ScopeSignalIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 0 , 1 , 0 , 0 , 0 , 0 , 0 } ; BuiltInDTypeId
dTypes [ 5 ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE }
; static char_T rt_ScopeBlockName [ ] = "KD_cl_harness_forthao_breach/Scope1"
; rt_ScopeSignalInfo . numSignals = 5 ; rt_ScopeSignalInfo . numCols =
rt_ScopeSignalWidths ; rt_ScopeSignalInfo . numDims =
rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . etcffifed1 .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) ,
"ScopeData" , 1 , 0 , 1 , 0.0 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ;
if ( rtDW . etcffifed1 . LoggedData == ( NULL ) ) return ; } { int_T
dimensions [ 1 ] = { 1 } ; rtDW . ecx5etklyp . LoggedData = rt_CreateLogVar (
ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , (
& ssGetErrorStatus ( rtS ) ) , "sim_wegr" , SS_DOUBLE , 0 , 0 , 0 , 1 , 1 ,
dimensions , NO_LOGVALDIMS , ( NULL ) , ( NULL ) , 0 , 1 , 0.0 , 1 ) ; if (
rtDW . ecx5etklyp . LoggedData == ( NULL ) ) return ; } { int_T dimensions [
1 ] = { 1 } ; rtDW . n4gmz4j4hp . LoggedData = rt_CreateLogVar (
ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , (
& ssGetErrorStatus ( rtS ) ) , "sim_vnlift" , SS_DOUBLE , 0 , 0 , 0 , 1 , 1 ,
dimensions , NO_LOGVALDIMS , ( NULL ) , ( NULL ) , 0 , 1 , 0.016 , 1 ) ; if (
rtDW . n4gmz4j4hp . LoggedData == ( NULL ) ) return ; } { int_T dimensions [
1 ] = { 1 } ; rtDW . cjtu2gvfu3 . LoggedData = rt_CreateLogVar (
ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , (
& ssGetErrorStatus ( rtS ) ) , "e_pin" , SS_DOUBLE , 0 , 0 , 0 , 1 , 1 ,
dimensions , NO_LOGVALDIMS , ( NULL ) , ( NULL ) , 0 , 1 , 0.0 , 1 ) ; if (
rtDW . cjtu2gvfu3 . LoggedData == ( NULL ) ) return ; } { int_T dimensions [
1 ] = { 1 } ; rtDW . kd250x2sgg . LoggedData = rt_CreateLogVar (
ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , (
& ssGetErrorStatus ( rtS ) ) , "e_egr" , SS_DOUBLE , 0 , 0 , 0 , 1 , 1 ,
dimensions , NO_LOGVALDIMS , ( NULL ) , ( NULL ) , 0 , 1 , 0.0 , 1 ) ; if (
rtDW . kd250x2sgg . LoggedData == ( NULL ) ) return ; } { static int_T
rt_ToWksWidths [ ] = { 13 } ; static int_T rt_ToWksNumDimensions [ ] = { 1 }
; static int_T rt_ToWksDimensions [ ] = { 13 } ; static boolean_T
rt_ToWksIsVarDims [ ] = { 0 } ; static void * rt_ToWksCurrSigDims [ ] = { (
NULL ) } ; static int_T rt_ToWksCurrSigDimsSize [ ] = { 4 } ; static
BuiltInDTypeId rt_ToWksDataTypeIds [ ] = { SS_SINGLE } ; static int_T
rt_ToWksComplexSignals [ ] = { 0 } ; static int_T rt_ToWksFrameData [ ] = { 0
} ; static const char_T * rt_ToWksLabels [ ] = { "expcon_in" } ; static
RTWLogSignalInfo rt_ToWksSignalInfo = { 1 , rt_ToWksWidths ,
rt_ToWksNumDimensions , rt_ToWksDimensions , rt_ToWksIsVarDims ,
rt_ToWksCurrSigDims , rt_ToWksCurrSigDimsSize , rt_ToWksDataTypeIds ,
rt_ToWksComplexSignals , rt_ToWksFrameData , { rt_ToWksLabels } , ( NULL ) ,
( NULL ) , ( NULL ) , { ( NULL ) } , { ( NULL ) } , ( NULL ) , ( NULL ) } ;
static const char_T rt_ToWksBlockName [ ] =
"KD_cl_harness_forthao_breach/To Workspace4" ; rtDW . cmlxapjojl . LoggedData
= rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) ,
ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "expcon_in" , 0
, 0 , 1 , 0.016 , & rt_ToWksSignalInfo , rt_ToWksBlockName ) ; if ( rtDW .
cmlxapjojl . LoggedData == ( NULL ) ) return ; } { static int_T
rt_ToWksWidths [ ] = { 3 } ; static int_T rt_ToWksNumDimensions [ ] = { 1 } ;
static int_T rt_ToWksDimensions [ ] = { 3 } ; static boolean_T
rt_ToWksIsVarDims [ ] = { 0 } ; static void * rt_ToWksCurrSigDims [ ] = { (
NULL ) } ; static int_T rt_ToWksCurrSigDimsSize [ ] = { 4 } ; static
BuiltInDTypeId rt_ToWksDataTypeIds [ ] = { SS_SINGLE } ; static int_T
rt_ToWksComplexSignals [ ] = { 0 } ; static int_T rt_ToWksFrameData [ ] = { 0
} ; static const char_T * rt_ToWksLabels [ ] = { "expcon_out" } ; static
RTWLogSignalInfo rt_ToWksSignalInfo = { 1 , rt_ToWksWidths ,
rt_ToWksNumDimensions , rt_ToWksDimensions , rt_ToWksIsVarDims ,
rt_ToWksCurrSigDims , rt_ToWksCurrSigDimsSize , rt_ToWksDataTypeIds ,
rt_ToWksComplexSignals , rt_ToWksFrameData , { rt_ToWksLabels } , ( NULL ) ,
( NULL ) , ( NULL ) , { ( NULL ) } , { ( NULL ) } , ( NULL ) , ( NULL ) } ;
static const char_T rt_ToWksBlockName [ ] =
"KD_cl_harness_forthao_breach/To Workspace5" ; rtDW . fdbzhbhm5w . LoggedData
= rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) ,
ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "expcon_out" , 0
, 0 , 1 , 0.016 , & rt_ToWksSignalInfo , rt_ToWksBlockName ) ; if ( rtDW .
fdbzhbhm5w . LoggedData == ( NULL ) ) return ; } { static int_T
rt_ToWksWidths [ ] = { 1 } ; static int_T rt_ToWksNumDimensions [ ] = { 1 } ;
static int_T rt_ToWksDimensions [ ] = { 1 } ; static boolean_T
rt_ToWksIsVarDims [ ] = { 0 } ; static void * rt_ToWksCurrSigDims [ ] = { (
NULL ) } ; static int_T rt_ToWksCurrSigDimsSize [ ] = { 4 } ; static
BuiltInDTypeId rt_ToWksDataTypeIds [ ] = { SS_INT32 } ; static int_T
rt_ToWksComplexSignals [ ] = { 0 } ; static int_T rt_ToWksFrameData [ ] = { 0
} ; static const char_T * rt_ToWksLabels [ ] = { "region" } ; static
RTWLogSignalInfo rt_ToWksSignalInfo = { 1 , rt_ToWksWidths ,
rt_ToWksNumDimensions , rt_ToWksDimensions , rt_ToWksIsVarDims ,
rt_ToWksCurrSigDims , rt_ToWksCurrSigDimsSize , rt_ToWksDataTypeIds ,
rt_ToWksComplexSignals , rt_ToWksFrameData , { rt_ToWksLabels } , ( NULL ) ,
( NULL ) , ( NULL ) , { ( NULL ) } , { ( NULL ) } , ( NULL ) , ( NULL ) } ;
static const char_T rt_ToWksBlockName [ ] =
"KD_cl_harness_forthao_breach/To Workspace6" ; rtDW . j2kd5bha4b . LoggedData
= rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) ,
ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "region" , 1 , 0
, 1 , 0.016 , & rt_ToWksSignalInfo , rt_ToWksBlockName ) ; if ( rtDW .
j2kd5bha4b . LoggedData == ( NULL ) ) return ; } { static int_T
rt_ToWksWidths [ ] = { 1 } ; static int_T rt_ToWksNumDimensions [ ] = { 1 } ;
static int_T rt_ToWksDimensions [ ] = { 1 } ; static boolean_T
rt_ToWksIsVarDims [ ] = { 0 } ; static void * rt_ToWksCurrSigDims [ ] = { (
NULL ) } ; static int_T rt_ToWksCurrSigDimsSize [ ] = { 4 } ; static
BuiltInDTypeId rt_ToWksDataTypeIds [ ] = { SS_DOUBLE } ; static int_T
rt_ToWksComplexSignals [ ] = { 0 } ; static int_T rt_ToWksFrameData [ ] = { 0
} ; static const char_T * rt_ToWksLabels [ ] = { "pex_hat" } ; static
RTWLogSignalInfo rt_ToWksSignalInfo = { 1 , rt_ToWksWidths ,
rt_ToWksNumDimensions , rt_ToWksDimensions , rt_ToWksIsVarDims ,
rt_ToWksCurrSigDims , rt_ToWksCurrSigDimsSize , rt_ToWksDataTypeIds ,
rt_ToWksComplexSignals , rt_ToWksFrameData , { rt_ToWksLabels } , ( NULL ) ,
( NULL ) , ( NULL ) , { ( NULL ) } , { ( NULL ) } , ( NULL ) , ( NULL ) } ;
static const char_T rt_ToWksBlockName [ ] =
"KD_cl_harness_forthao_breach/To Workspace7" ; rtDW . jcasi5loyb . LoggedData
= rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) ,
ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "pex_hat" , 1 ,
0 , 1 , 0.016 , & rt_ToWksSignalInfo , rt_ToWksBlockName ) ; if ( rtDW .
jcasi5loyb . LoggedData == ( NULL ) ) return ; } { static int_T
rt_ToWksWidths [ ] = { 1 } ; static int_T rt_ToWksNumDimensions [ ] = { 1 } ;
static int_T rt_ToWksDimensions [ ] = { 1 } ; static boolean_T
rt_ToWksIsVarDims [ ] = { 0 } ; static void * rt_ToWksCurrSigDims [ ] = { (
NULL ) } ; static int_T rt_ToWksCurrSigDimsSize [ ] = { 4 } ; static
BuiltInDTypeId rt_ToWksDataTypeIds [ ] = { SS_DOUBLE } ; static int_T
rt_ToWksComplexSignals [ ] = { 0 } ; static int_T rt_ToWksFrameData [ ] = { 0
} ; static const char_T * rt_ToWksLabels [ ] = { "dwdp" } ; static
RTWLogSignalInfo rt_ToWksSignalInfo = { 1 , rt_ToWksWidths ,
rt_ToWksNumDimensions , rt_ToWksDimensions , rt_ToWksIsVarDims ,
rt_ToWksCurrSigDims , rt_ToWksCurrSigDimsSize , rt_ToWksDataTypeIds ,
rt_ToWksComplexSignals , rt_ToWksFrameData , { rt_ToWksLabels } , ( NULL ) ,
( NULL ) , ( NULL ) , { ( NULL ) } , { ( NULL ) } , ( NULL ) , ( NULL ) } ;
static const char_T rt_ToWksBlockName [ ] =
"KD_cl_harness_forthao_breach/To Workspace8" ; rtDW . lscu5irxwr . LoggedData
= rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart ( rtS ) ,
ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "dwdp" , 1 , 0 ,
1 , 0.016 , & rt_ToWksSignalInfo , rt_ToWksBlockName ) ; if ( rtDW .
lscu5irxwr . LoggedData == ( NULL ) ) return ; } { RTWLogSignalInfo
rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] = { 3 } ; static
int_T rt_ScopeSignalNumDimensions [ ] = { 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 3 } ; static void * rt_ScopeCurrSigDims [ ]
= { ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 } ; static
const char_T * rt_ScopeSignalLabels [ ] = { "" } ; static char_T
rt_ScopeSignalTitles [ ] = "" ; static int_T rt_ScopeSignalTitleLengths [ ] =
{ 0 } ; static boolean_T rt_ScopeSignalIsVarDims [ ] = { 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 1 , 1 , 1 } ; BuiltInDTypeId dTypes [ 1 ] =
{ SS_DOUBLE } ; static char_T rt_ScopeBlockName [ ] =
"KD_cl_harness_forthao_breach/egr_cons" ; rt_ScopeSignalInfo . numSignals = 1
; rt_ScopeSignalInfo . numCols = rt_ScopeSignalWidths ; rt_ScopeSignalInfo .
numDims = rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . hnhslp1bvt .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) ,
"egr_cons" , 1 , 0 , 1 , 0.016 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ;
if ( rtDW . hnhslp1bvt . LoggedData == ( NULL ) ) return ; } {
RTWLogSignalInfo rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] =
{ 4 } ; static int_T rt_ScopeSignalNumDimensions [ ] = { 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 4 } ; static void * rt_ScopeCurrSigDims [ ]
= { ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 } ; static
const char_T * rt_ScopeSignalLabels [ ] = { "" } ; static char_T
rt_ScopeSignalTitles [ ] = "" ; static int_T rt_ScopeSignalTitleLengths [ ] =
{ 0 } ; static boolean_T rt_ScopeSignalIsVarDims [ ] = { 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 1 , 1 , 1 , 0 } ; BuiltInDTypeId dTypes [ 1
] = { SS_DOUBLE } ; static char_T rt_ScopeBlockName [ ] =
"KD_cl_harness_forthao_breach/egr_flow_cons" ; rt_ScopeSignalInfo .
numSignals = 1 ; rt_ScopeSignalInfo . numCols = rt_ScopeSignalWidths ;
rt_ScopeSignalInfo . numDims = rt_ScopeSignalNumDimensions ;
rt_ScopeSignalInfo . dims = rt_ScopeSignalDimensions ; rt_ScopeSignalInfo .
isVarDims = rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . moxm2bblwy .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) ,
"egr_flow_cons" , 1 , 0 , 1 , 0.0 , & rt_ScopeSignalInfo , rt_ScopeBlockName
) ; if ( rtDW . moxm2bblwy . LoggedData == ( NULL ) ) return ; } {
RTWLogSignalInfo rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] =
{ 1 } ; static int_T rt_ScopeSignalNumDimensions [ ] = { 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 1 } ; static void * rt_ScopeCurrSigDims [ ]
= { ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 } ; static
const char_T * rt_ScopeSignalLabels [ ] = { "" } ; static char_T
rt_ScopeSignalTitles [ ] = "" ; static int_T rt_ScopeSignalTitleLengths [ ] =
{ 0 } ; static boolean_T rt_ScopeSignalIsVarDims [ ] = { 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 0 } ; BuiltInDTypeId dTypes [ 1 ] = {
SS_DOUBLE } ; static char_T rt_ScopeBlockName [ ] =
"KD_cl_harness_forthao_breach/ene" ; rt_ScopeSignalInfo . numSignals = 1 ;
rt_ScopeSignalInfo . numCols = rt_ScopeSignalWidths ; rt_ScopeSignalInfo .
numDims = rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . auoyy55qok .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) ,
"ene_rpm" , 1 , 0 , 1 , 0.0 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ; if
( rtDW . auoyy55qok . LoggedData == ( NULL ) ) return ; } { RTWLogSignalInfo
rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] = { 1 } ; static
int_T rt_ScopeSignalNumDimensions [ ] = { 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 1 } ; static void * rt_ScopeCurrSigDims [ ]
= { ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 } ; static
const char_T * rt_ScopeSignalLabels [ ] = { "" } ; static char_T
rt_ScopeSignalTitles [ ] = "" ; static int_T rt_ScopeSignalTitleLengths [ ] =
{ 0 } ; static boolean_T rt_ScopeSignalIsVarDims [ ] = { 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 0 } ; BuiltInDTypeId dTypes [ 1 ] = {
SS_DOUBLE } ; static char_T rt_ScopeBlockName [ ] =
"KD_cl_harness_forthao_breach/fuel" ; rt_ScopeSignalInfo . numSignals = 1 ;
rt_ScopeSignalInfo . numCols = rt_ScopeSignalWidths ; rt_ScopeSignalInfo .
numDims = rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . pd2fs1ditr .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) ,
"fuel_gpers" , 1 , 0 , 1 , 0.0 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ;
if ( rtDW . pd2fs1ditr . LoggedData == ( NULL ) ) return ; } {
RTWLogSignalInfo rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] =
{ 2 } ; static int_T rt_ScopeSignalNumDimensions [ ] = { 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 2 } ; static void * rt_ScopeCurrSigDims [ ]
= { ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 } ; static
const char_T * rt_ScopeSignalLabels [ ] = { "" } ; static char_T
rt_ScopeSignalTitles [ ] = "" ; static int_T rt_ScopeSignalTitleLengths [ ] =
{ 0 } ; static boolean_T rt_ScopeSignalIsVarDims [ ] = { 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 1 , 1 } ; BuiltInDTypeId dTypes [ 1 ] = {
SS_DOUBLE } ; static char_T rt_ScopeBlockName [ ] =
"KD_cl_harness_forthao_breach/gs" ; rt_ScopeSignalInfo . numSignals = 1 ;
rt_ScopeSignalInfo . numCols = rt_ScopeSignalWidths ; rt_ScopeSignalInfo .
numDims = rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . lyifwmtiaf .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "gs" , 1
, 0 , 1 , 0.016 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ; if ( rtDW .
lyifwmtiaf . LoggedData == ( NULL ) ) return ; } { RTWLogSignalInfo
rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] = { 3 } ; static
int_T rt_ScopeSignalNumDimensions [ ] = { 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 3 } ; static void * rt_ScopeCurrSigDims [ ]
= { ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 } ; static
const char_T * rt_ScopeSignalLabels [ ] = { "" } ; static char_T
rt_ScopeSignalTitles [ ] = "" ; static int_T rt_ScopeSignalTitleLengths [ ] =
{ 0 } ; static boolean_T rt_ScopeSignalIsVarDims [ ] = { 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 1 , 1 , 1 } ; BuiltInDTypeId dTypes [ 1 ] =
{ SS_DOUBLE } ; static char_T rt_ScopeBlockName [ ] =
"KD_cl_harness_forthao_breach/map_cons" ; rt_ScopeSignalInfo . numSignals = 1
; rt_ScopeSignalInfo . numCols = rt_ScopeSignalWidths ; rt_ScopeSignalInfo .
numDims = rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . n2no12labo .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) ,
"map_cons" , 1 , 0 , 1 , 0.016 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ;
if ( rtDW . n2no12labo . LoggedData == ( NULL ) ) return ; } {
RTWLogSignalInfo rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] =
{ 2 } ; static int_T rt_ScopeSignalNumDimensions [ ] = { 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 2 } ; static void * rt_ScopeCurrSigDims [ ]
= { ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 } ; static
const char_T * rt_ScopeSignalLabels [ ] = { "" } ; static char_T
rt_ScopeSignalTitles [ ] = "" ; static int_T rt_ScopeSignalTitleLengths [ ] =
{ 0 } ; static boolean_T rt_ScopeSignalIsVarDims [ ] = { 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 1 , 1 } ; BuiltInDTypeId dTypes [ 1 ] = {
SS_DOUBLE } ; static char_T rt_ScopeBlockName [ ] =
"KD_cl_harness_forthao_breach/nt_cons" ; rt_ScopeSignalInfo . numSignals = 1
; rt_ScopeSignalInfo . numCols = rt_ScopeSignalWidths ; rt_ScopeSignalInfo .
numDims = rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . jhwi52suok .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) ,
"nt_cons" , 1 , 0 , 1 , 0.016 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ;
if ( rtDW . jhwi52suok . LoggedData == ( NULL ) ) return ; } {
RTWLogSignalInfo rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] =
{ 2 } ; static int_T rt_ScopeSignalNumDimensions [ ] = { 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 2 } ; static void * rt_ScopeCurrSigDims [ ]
= { ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 } ; static
const char_T * rt_ScopeSignalLabels [ ] = { "" } ; static char_T
rt_ScopeSignalTitles [ ] = "" ; static int_T rt_ScopeSignalTitleLengths [ ] =
{ 0 } ; static boolean_T rt_ScopeSignalIsVarDims [ ] = { 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 1 , 1 } ; BuiltInDTypeId dTypes [ 1 ] = {
SS_DOUBLE } ; static char_T rt_ScopeBlockName [ ] =
"KD_cl_harness_forthao_breach/pex_cons" ; rt_ScopeSignalInfo . numSignals = 1
; rt_ScopeSignalInfo . numCols = rt_ScopeSignalWidths ; rt_ScopeSignalInfo .
numDims = rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . iesioivz5z .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) ,
"pex_cons" , 1 , 0 , 1 , 0.016 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ;
if ( rtDW . iesioivz5z . LoggedData == ( NULL ) ) return ; } {
RTWLogSignalInfo rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] =
{ 1 } ; static int_T rt_ScopeSignalNumDimensions [ ] = { 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 1 } ; static void * rt_ScopeCurrSigDims [ ]
= { ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 } ; static
const char_T * rt_ScopeSignalLabels [ ] = { "region" } ; static char_T
rt_ScopeSignalTitles [ ] = "region" ; static int_T rt_ScopeSignalTitleLengths
[ ] = { 6 } ; static boolean_T rt_ScopeSignalIsVarDims [ ] = { 0 } ; static
int_T rt_ScopeSignalPlotStyles [ ] = { 1 } ; BuiltInDTypeId dTypes [ 1 ] = {
SS_INT32 } ; static char_T rt_ScopeBlockName [ ] =
"KD_cl_harness_forthao_breach/region" ; rt_ScopeSignalInfo . numSignals = 1 ;
rt_ScopeSignalInfo . numCols = rt_ScopeSignalWidths ; rt_ScopeSignalInfo .
numDims = rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . jhe31dgiau .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "outs" ,
1 , 0 , 1 , 0.016 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ; if ( rtDW .
jhe31dgiau . LoggedData == ( NULL ) ) return ; } { RTWLogSignalInfo
rt_ScopeSignalInfo ; static int_T rt_ScopeSignalWidths [ ] = { 1 } ; static
int_T rt_ScopeSignalNumDimensions [ ] = { 1 } ; static int_T
rt_ScopeSignalDimensions [ ] = { 1 } ; static void * rt_ScopeCurrSigDims [ ]
= { ( NULL ) } ; static int_T rt_ScopeCurrSigDimsSize [ ] = { 4 } ; static
const char_T * rt_ScopeSignalLabels [ ] = { "" } ; static char_T
rt_ScopeSignalTitles [ ] = "" ; static int_T rt_ScopeSignalTitleLengths [ ] =
{ 0 } ; static boolean_T rt_ScopeSignalIsVarDims [ ] = { 0 } ; static int_T
rt_ScopeSignalPlotStyles [ ] = { 1 } ; BuiltInDTypeId dTypes [ 1 ] = {
SS_DOUBLE } ; static char_T rt_ScopeBlockName [ ] =
"KD_cl_harness_forthao_breach/slack" ; rt_ScopeSignalInfo . numSignals = 1 ;
rt_ScopeSignalInfo . numCols = rt_ScopeSignalWidths ; rt_ScopeSignalInfo .
numDims = rt_ScopeSignalNumDimensions ; rt_ScopeSignalInfo . dims =
rt_ScopeSignalDimensions ; rt_ScopeSignalInfo . isVarDims =
rt_ScopeSignalIsVarDims ; rt_ScopeSignalInfo . currSigDims =
rt_ScopeCurrSigDims ; rt_ScopeSignalInfo . currSigDimsSize =
rt_ScopeCurrSigDimsSize ; rt_ScopeSignalInfo . dataTypes = dTypes ;
rt_ScopeSignalInfo . complexSignals = ( NULL ) ; rt_ScopeSignalInfo .
frameData = ( NULL ) ; rt_ScopeSignalInfo . labels . cptr =
rt_ScopeSignalLabels ; rt_ScopeSignalInfo . titles = rt_ScopeSignalTitles ;
rt_ScopeSignalInfo . titleLengths = rt_ScopeSignalTitleLengths ;
rt_ScopeSignalInfo . plotStyles = rt_ScopeSignalPlotStyles ;
rt_ScopeSignalInfo . blockNames . cptr = ( NULL ) ; rt_ScopeSignalInfo .
stateNames . cptr = ( NULL ) ; rt_ScopeSignalInfo . crossMdlRef = ( NULL ) ;
rt_ScopeSignalInfo . dataTypeConvert = ( NULL ) ; rtDW . ojkakflagz .
LoggedData = rt_CreateStructLogVar ( ssGetRTWLogInfo ( rtS ) , ssGetTStart (
rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS ) ) , "outs1"
, 1 , 0 , 1 , 0.016 , & rt_ScopeSignalInfo , rt_ScopeBlockName ) ; if ( rtDW
. ojkakflagz . LoggedData == ( NULL ) ) return ; } { FWksInfo * fromwksInfo ;
if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1 , sizeof ( FWksInfo ) ) ) == (
NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "[0  300.0250]" ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) & rtP . FromWorkspace6_Data0 ; fromwksInfo ->
nDataPoints = 1 ; fromwksInfo -> time = ( double * ) & rtP .
FromWorkspace6_Time0 ; rtDW . alrdv1eret . TimePtr = fromwksInfo -> time ;
rtDW . alrdv1eret . DataPtr = fromwksInfo -> data ; rtDW . alrdv1eret .
RSimInfoPtr = fromwksInfo ; } rtDW . khael42orb . PrevIndex = 0 ; } {
FWksInfo * fromwksInfo ; if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1 ,
sizeof ( FWksInfo ) ) ) == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "[0  351.4714]" ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) & rtP . FromWorkspace7_Data0 ; fromwksInfo ->
nDataPoints = 1 ; fromwksInfo -> time = ( double * ) & rtP .
FromWorkspace7_Time0 ; rtDW . p1e0b0rkdr . TimePtr = fromwksInfo -> time ;
rtDW . p1e0b0rkdr . DataPtr = fromwksInfo -> data ; rtDW . p1e0b0rkdr .
RSimInfoPtr = fromwksInfo ; } rtDW . bi4mdaymdj . PrevIndex = 0 ; } {
FWksInfo * fromwksInfo ; if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1 ,
sizeof ( FWksInfo ) ) ) == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "[0 3]" ; fromwksInfo -> origDataTypeId
= 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo -> origWidth = 1 ;
fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo -> data = ( void
* ) & rtP . FromWorkspace4_Data0 ; fromwksInfo -> nDataPoints = 1 ;
fromwksInfo -> time = ( double * ) & rtP . FromWorkspace4_Time0 ; rtDW .
clwukip414 . TimePtr = fromwksInfo -> time ; rtDW . clwukip414 . DataPtr =
fromwksInfo -> data ; rtDW . clwukip414 . RSimInfoPtr = fromwksInfo ; } rtDW
. d1tbd3ecab . PrevIndex = 0 ; } { void * pAobHierarchyNode0 = ( NULL ) ; {
char * pathToTopModel = "" ; const char * sigLogSelectorFileName =
rt_GetMatSigLogSelectorFileName ( ) ; void * pSignalProbeCollection = ( NULL
) ; uint_T signalDimensions0 [ 1 ] = { 1 } ; rtwAobHierarchyCreateRootNode (
& pAobHierarchyNode0 ) ; rtwAobHierarchyVerifyNNodes ( pAobHierarchyNode0 , 1
) ; rtwSignalProbeCollectionCreateInstance ( "tmp_raccel_logsout" ,
"Tq_friction" , pathToTopModel ,
"KD_cl_harness_forthao_breach/Turbo Rotational Dynamics/Turbo rot/Tq_friction"
, sigLogSelectorFileName , 1 , & pSignalProbeCollection ) ;
rtwSignalProbeCollectionAddElement ( pSignalProbeCollection , "Tq_friction" ,
"linear" , 1 , 0 , 1 , signalDimensions0 , 0 , "" , "double" ) ;
rtwSignalProbeCollectionVerifyNLeaves ( pSignalProbeCollection , 1 ) ;
rtwSignalProbeCollectionSetAobHierarchy ( pSignalProbeCollection ,
pAobHierarchyNode0 ) ; rtwSignalProbeCollectionFinalizeMetaData (
pSignalProbeCollection ) ; rtDW . dcyih1kpjy . SignalProbe =
pSignalProbeCollection ; } } { int_T dimensions [ 1 ] = { 1 } ; rtDW .
bdj3wmcbnu . LoggedData = rt_CreateLogVar ( ssGetRTWLogInfo ( rtS ) ,
ssGetTStart ( rtS ) , ssGetTFinal ( rtS ) , 0.0 , ( & ssGetErrorStatus ( rtS
) ) , "Tq_friction" , SS_DOUBLE , 0 , 0 , 0 , 1 , 1 , dimensions ,
NO_LOGVALDIMS , ( NULL ) , ( NULL ) , 0 , 1 , 0.0 , 1 ) ; if ( rtDW .
bdj3wmcbnu . LoggedData == ( NULL ) ) return ; } { FWksInfo * fromwksInfo ;
if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1 , sizeof ( FWksInfo ) ) ) == (
NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "[0   97.4450]" ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) & rtP . FromWorkspace5_Data0 ; fromwksInfo ->
nDataPoints = 1 ; fromwksInfo -> time = ( double * ) & rtP .
FromWorkspace5_Time0 ; rtDW . d5tz0vp4gc . TimePtr = fromwksInfo -> time ;
rtDW . d5tz0vp4gc . DataPtr = fromwksInfo -> data ; rtDW . d5tz0vp4gc .
RSimInfoPtr = fromwksInfo ; } rtDW . aloadsnzst . PrevIndex = 0 ; } {
FWksInfo * fromwksInfo ; if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1 ,
sizeof ( FWksInfo ) ) ) == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "[0    3.7702]" ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) & rtP . FromWorkspace8_Data0 ; fromwksInfo ->
nDataPoints = 1 ; fromwksInfo -> time = ( double * ) & rtP .
FromWorkspace8_Time0 ; rtDW . ozs1urzqbb . TimePtr = fromwksInfo -> time ;
rtDW . ozs1urzqbb . DataPtr = fromwksInfo -> data ; rtDW . ozs1urzqbb .
RSimInfoPtr = fromwksInfo ; } rtDW . fzvbkpkm44 . PrevIndex = 0 ; } {
FWksInfo * fromwksInfo ; if ( ( fromwksInfo = ( FWksInfo * ) calloc ( 1 ,
sizeof ( FWksInfo ) ) ) == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"from workspace STRING(Name) memory allocation error" ) ; } else {
fromwksInfo -> origWorkspaceVarName = "[0 5;10 55;20 5]" ; fromwksInfo ->
origDataTypeId = 0 ; fromwksInfo -> origIsComplex = 0 ; fromwksInfo ->
origWidth = 1 ; fromwksInfo -> origElSize = sizeof ( real_T ) ; fromwksInfo
-> data = ( void * ) rtP . FromWorkspace_Data0 ; fromwksInfo -> nDataPoints =
3 ; fromwksInfo -> time = ( double * ) rtP . FromWorkspace_Time0 ; rtDW .
jfbqvyxdrm . TimePtr = fromwksInfo -> time ; rtDW . jfbqvyxdrm . DataPtr =
fromwksInfo -> data ; rtDW . jfbqvyxdrm . RSimInfoPtr = fromwksInfo ; } rtDW
. gyhzvvm031 . PrevIndex = 0 ; } rtDW . dpjpy2bpgy = rtP .
DataStoreMemory1_InitialValue ; rtDW . nqvcv4lcej = rtP .
DataStoreMemory100_InitialValue ; rtDW . mi05525rde = rtP .
DataStoreMemory101_InitialValue ; rtDW . gsy0d3xgez = rtP .
DataStoreMemory102_InitialValue ; rtDW . owcamicoch = rtP .
DataStoreMemory103_InitialValue ; rtDW . o0hytehsup = rtP .
DataStoreMemory104_InitialValue ; rtDW . pelseog20p = rtP .
DataStoreMemory105_InitialValue ; rtDW . nhrhyjvls4 = rtP .
DataStoreMemory106_InitialValue ; rtDW . oobzxswkpo = rtP .
DataStoreMemory107_InitialValue ; rtDW . l0b5hroyaj = rtP .
DataStoreMemory108_InitialValue ; rtDW . fuwbxjmtyy = rtP .
DataStoreMemory2_InitialValue ; rtDW . nq1n5qxeyp = rtP .
DataStoreMemory3_InitialValue ; rtDW . b5t1avpqna = rtP .
DataStoreMemory4_InitialValue ; rtDW . ocojyks2sz = rtP .
DataStoreMemory5_InitialValue ; rtDW . ntmupcyyck = rtP .
DataStoreMemory52_InitialValue ; rtDW . devn1wdclr = rtP .
DataStoreMemory55_InitialValue ; rtDW . ktweu3wugd = rtP .
DataStoreMemory56_InitialValue ; rtDW . o3z1jsmhkx = rtP .
DataStoreMemory57_InitialValue ; rtDW . hptuorf3i3 = rtP .
DataStoreMemory58_InitialValue ; rtDW . nlpxiel2sg = rtP .
DataStoreMemory59_InitialValue ; rtDW . n5tosor5b5 = rtP .
DataStoreMemory60_InitialValue ; rtDW . n5pkawvqdo = rtP .
DataStoreMemory61_InitialValue ; rtDW . c1deueau4e = rtP .
DataStoreMemory62_InitialValue ; rtDW . mi5h1pks4n = rtP .
DataStoreMemory63_InitialValue ; rtDW . bvlm5joqvj = rtP .
DataStoreMemory64_InitialValue ; rtDW . kk4xei3vwx = rtP .
DataStoreMemory65_InitialValue ; rtDW . nwf1nud1fv = rtP .
DataStoreMemory66_InitialValue ; rtDW . mjfdrfawoz = rtP .
DataStoreMemory67_InitialValue ; rtDW . oe1xcqtj2h = rtP .
DataStoreMemory68_InitialValue ; rtDW . fnhncveveb = rtP .
DataStoreMemory69_InitialValue ; rtDW . i5n35h2hi0 = rtP .
DataStoreMemory70_InitialValue ; rtDW . gj1id4inx4 = rtP .
DataStoreMemory71_InitialValue ; rtDW . ar2qj33owm = rtP .
DataStoreMemory72_InitialValue ; rtDW . bakpq4fzl0 = rtP .
DataStoreMemory73_InitialValue ; rtDW . enudnf03vn = rtP .
DataStoreMemory74_InitialValue ; rtDW . gd2xytkseo = rtP .
DataStoreMemory75_InitialValue ; rtDW . axunmck3pg = rtP .
DataStoreMemory76_InitialValue ; rtDW . estlkslffw = rtP .
DataStoreMemory77_InitialValue ; rtDW . gzmuaempqp = rtP .
DataStoreMemory78_InitialValue ; rtDW . pwwmab3rlr = rtP .
DataStoreMemory79_InitialValue ; rtDW . e10toipvv0 = rtP .
DataStoreMemory80_InitialValue ; rtDW . hyhv0echnn = rtP .
DataStoreMemory81_InitialValue ; rtDW . gmsrqeat5h = rtP .
DataStoreMemory82_InitialValue ; rtDW . aupt3qrz3y = rtP .
DataStoreMemory83_InitialValue ; rtDW . jnju4d4o03 = rtP .
DataStoreMemory84_InitialValue ; rtDW . bpo1eig15d = rtP .
DataStoreMemory85_InitialValue ; rtDW . fgc3q11l1t = rtP .
DataStoreMemory86_InitialValue ; rtDW . eppk3q2xfh = rtP .
DataStoreMemory87_InitialValue ; rtDW . dpzir5hccd = rtP .
DataStoreMemory88_InitialValue ; rtDW . ayjpjfupkc = rtP .
DataStoreMemory89_InitialValue ; rtDW . d210tl5n23 = rtP .
DataStoreMemory90_InitialValue ; rtDW . moioiyooa5 = rtP .
DataStoreMemory91_InitialValue ; rtDW . a1ts5brulz = rtP .
DataStoreMemory92_InitialValue ; rtDW . lqempabukg = rtP .
DataStoreMemory93_InitialValue ; rtDW . ecauzxzkhl = rtP .
DataStoreMemory94_InitialValue ; rtDW . fllyhv1jnh = rtP .
DataStoreMemory95_InitialValue ; rtDW . ok4jtsn4bb = rtP .
DataStoreMemory96_InitialValue ; rtDW . pmewcnpxdb = rtP .
DataStoreMemory97_InitialValue ; rtDW . dhb1ak5ywv = rtP .
DataStoreMemory98_InitialValue ; rtDW . psebtvzqlm = rtP .
DataStoreMemory99_InitialValue ; MdlInitialize ( ) ; } void MdlOutputs (
int_T tid ) { real_T g0wrszfna1 ; real_T kcdukwoy0g ; real_T ij2wjykslx ;
real_T nxbnma2b0r ; real_T hm5icraqc0 ; real_T dks5dd4n1g ; real_T dbdkq3qiib
; real_T h3vwhozvjv ; real_T hy0nvl42ff ; real_T alnmoyh0xt ; real_T
iwi45oum3a ; real_T nt2j3jtq0u ; real_T buuq3qgkl1 ; real_T fcjivgpr4n ;
real_T lfikko4x3f ; real_T pcimxyw44x ; real_T csqmlvrkng ; real_T do3ymddtym
; real_T omzt3u0gfx ; real_T edr234t3il ; real_T ebo5aiznrs ; real_T
hribjanxea ; real_T j4ebfdbclg ; real_T gr15gli4w1 ; real_T iet23ldaul ;
real_T g2kaq151q0 ; real_T e4bvnp5vjd ; real_T gsvm4zgv5t ; real_T kd01knh0r3
; real_T mnhajo5ou4 ; real_T aadj45x0pt ; real_T kmz3ui0uz0 ; real32_T
oddbt41ver ; real32_T cswau4wwoj ; real32_T pjzpplkm5e ; real32_T njl1440oaw
; real32_T ikxbbcq2jl ; real32_T c22to2uley ; real32_T cqse1wvpl2 ; int32_T
ikgncxkezn ; int32_T abpgkxy4n5 ; real_T o0swabdreh ; real_T l01ja1voo4 ;
real_T jxyw3fewls ; real32_T pcwwxeoehv ; real32_T pecb1uxa5c ; real32_T
nokdpzhel0 ; real32_T kbpr1j4sdg ; real32_T nyhah3yrmr ; real32_T d45xcqw5zg
; real32_T bmms50o0wz ; real32_T bprhelbqm0 ; real32_T ana05zcqxm ; real32_T
dsl1ro0v01 ; real32_T lx1uc222jj ; real32_T jwc13tgat3 ; real_T W_comp ;
real_T PhiC ; real_T PRcoeffs [ 6 ] ; real_T delta_T_comp ; real_T x [ 3 ] ;
real_T PR ; real32_T p03esja3h2 ; real32_T es40kk5dcp ; real_T bguiqh0znq ;
real_T j1s5yn2ijo ; real_T npiyznthqi ; real_T imz3hxnyez ; real_T jalnkh4fhi
; real_T lgp0omksql ; real_T b11wdxnlxt ; real_T kojspa505o ; real_T
aktecqyana ; real_T gjrh3vhxv1 ; real_T ppxu00rks2 ; real_T exgwciklzi ;
real32_T batdnpsvim ; real32_T g1ekzbu3oi ; real32_T pwkaxiafxx ; real32_T
c2fdcpgrsp ; real32_T fwhtla1rft ; real32_T e2oeg530ux [ 10 ] ; real32_T
lqaourhjqh ; real32_T alqkjudhu3 ; real_T efj5q5ebcq ; real32_T eplcvohihr ;
real32_T fzccphw1bz ; real32_T o3mfdsmmfb ; real_T o5iftc4ajm ; real_T
o5ibp43cp4 ; real_T n4kbehhhau ; real_T lc44cjozax ; boolean_T meppapiqj0 ;
int32_T ffd3q0dmho ; real32_T not4fp11wk ; real32_T orelggziy4 ; real_T
beiewzgadl ; int32_T s60_iter ; real32_T hhjnxjzwip ; real_T gen03hfvbg ;
int32_T i ; real_T tmp [ 3 ] ; real_T tmp_p [ 3 ] ; real_T tmp_e [ 3 ] ;
real_T tmp_i [ 3 ] ; real_T tmp_m [ 3 ] ; real_T tmp_g [ 3 ] ; real_T tmp_j [
3 ] ; real32_T tmp_f [ 2 ] ; real32_T duexjpu5rm_p ; int32_T izertgsvfr ;
int32_T izertgsvfr_p ; int32_T izertgsvfr_e ; int32_T izertgsvfr_i ; int32_T
izertgsvfr_m ; int32_T izertgsvfr_g ; int32_T izertgsvfr_j ; int32_T
izertgsvfr_f ; int32_T izertgsvfr_c ; int32_T izertgsvfr_k ; int32_T
izertgsvfr_b ; int32_T izertgsvfr_n ; real32_T tmp_c [ 3 ] ; real32_T tmp_k [
3 ] ; int32_T cjggagnffi ; real_T ll4keb2h0s_idx_3 ; real32_T
hde10siz3b_idx_0 ; real32_T hde10siz3b_idx_1 ; real_T ppfiifg3xk_idx_1 ;
int8_T idx_idx_1 ; int8_T idx_idx_2 ; real32_T cesfgrkder_idx_0 ; real32_T
cesfgrkder_idx_1 ; real32_T o2wgigs4ap_idx_0 ; real32_T u0 ; real32_T tmp_b ;
if ( gblInportFileName != ( NULL ) ) { int_T currTimeIdx ; int_T i ; if (
gblInportTUtables [ 0 ] . nTimePoints > 0 ) { if ( 1 ) { real_T time =
ssGetTaskTime ( rtS , 0 ) ; currTimeIdx = rt_getTimeIdx ( gblInportTUtables [
0 ] . time , time , gblInportTUtables [ 0 ] . nTimePoints , gblInportTUtables
[ 0 ] . currTimeIdx , 0 , 0 ) ; gblInportTUtables [ 0 ] . currTimeIdx =
currTimeIdx ; for ( i = 0 ; i < 1 ; i ++ ) { if ( currTimeIdx == - 7 ) { rtU
. ch4dzb1x4i = 0.0 ; } else { real_T * realPtr1 = ( real_T * )
gblInportTUtables [ 0 ] . ur + i * gblInportTUtables [ 0 ] . nTimePoints +
currTimeIdx ; rtU . ch4dzb1x4i = * realPtr1 ; } } } } if ( gblInportTUtables
[ 1 ] . nTimePoints > 0 ) { if ( 1 ) { real_T time = ssGetTaskTime ( rtS , 0
) ; currTimeIdx = rt_getTimeIdx ( gblInportTUtables [ 1 ] . time , time ,
gblInportTUtables [ 1 ] . nTimePoints , gblInportTUtables [ 1 ] . currTimeIdx
, 0 , 0 ) ; gblInportTUtables [ 1 ] . currTimeIdx = currTimeIdx ; for ( i = 0
; i < 1 ; i ++ ) { if ( currTimeIdx == - 7 ) { rtU . gm151yhz1l = 0.0 ; }
else { real_T * realPtr1 = ( real_T * ) gblInportTUtables [ 1 ] . ur + i *
gblInportTUtables [ 1 ] . nTimePoints + currTimeIdx ; rtU . gm151yhz1l = *
realPtr1 ; } } } } } srClearBC ( rtDW . lb2gtdwzqd ) ; srClearBC ( rtDW .
hpc0grqivr ) ; srClearBC ( rtDW . l4mofmlly2 ) ; srClearBC ( rtDW .
kltb44md1r ) ; srClearBC ( rtDW . oqqlpwtggt ) ; srClearBC ( rtDW .
hgwa21u3tp ) ; srClearBC ( rtDW . ljedkvx4od ) ; srClearBC ( rtDW .
gdpkwnqxlj ) ; srClearBC ( rtDW . pg1kwe2jsoh . ld1fjkwy01 ) ; srClearBC (
rtDW . ozyefxkqtm ) ; srClearBC ( rtDW . hfnjefvf2v ) ; srClearBC ( rtDW .
o0fqt141qd ) ; srClearBC ( rtDW . h3vqcmc1hz ) ; srClearBC ( rtDW .
pqpqjda5is ) ; srClearBC ( rtDW . bwmwpnvwlf ) ; srClearBC ( rtDW .
hf2ukkb54z ) ; srClearBC ( rtDW . dp2wxggv2y ) ; srClearBC ( rtDW .
ifikoeohu4 ) ; srClearBC ( rtDW . fb2jmsx45b ) ; srClearBC ( rtDW .
gu2pk5utpz ) ; srClearBC ( rtDW . m1sbzn2h1n ) ; srClearBC ( rtDW .
ewylvoz5wx ) ; srClearBC ( rtDW . bzt2b4vlgj ) ; srClearBC ( rtDW .
p5cjuriyjr ) ; srClearBC ( rtDW . klgivly02z ) ; srClearBC ( rtDW .
nlyldhhvyb ) ; srClearBC ( rtDW . k1yann3ya5 ) ; srClearBC ( rtDW .
bubafrutom ) ; srClearBC ( rtDW . ltvu2oc3sf ) ; srClearBC ( rtDW .
li2ivnnt0t ) ; srClearBC ( rtDW . ae1e1itbfy ) ; srClearBC ( rtDW .
dhx34gepf4 ) ; srClearBC ( rtDW . p2atyilds3 ) ; srClearBC ( rtDW .
edw2mgcvx1 ) ; srClearBC ( rtDW . n4uikvdjac ) ; srClearBC ( rtDW .
chxryck3fg ) ; srClearBC ( rtDW . dl0glhtqdr ) ; srClearBC ( rtDW .
adcpzgniuv ) ; srClearBC ( rtDW . ismm4u0kis ) ; srClearBC ( rtDW .
kct4avkdgo ) ; srClearBC ( rtDW . ljqu2i52fc ) ; srClearBC ( rtDW .
lpg4z3lelv ) ; srClearBC ( rtDW . ombi11gse3 ) ; srClearBC ( rtDW .
igzqf1qklf ) ; srClearBC ( rtDW . moze4hcv5c ) ; srClearBC ( rtDW .
kuzwdhnrip ) ; srClearBC ( rtDW . j4ymuqubrw ) ; srClearBC ( rtDW .
kymzzotg2g ) ; srClearBC ( rtDW . maiimsnqs5 ) ; srClearBC ( rtDW .
dyx4tug5h3 ) ; srClearBC ( rtDW . cr2kibgo2j ) ; srClearBC ( rtDW .
pwlmqo3nxm ) ; srClearBC ( rtDW . guuziano0t ) ; srClearBC ( rtDW .
l12omsu2tn ) ; srClearBC ( rtDW . o2zj3fqza1 ) ; srClearBC ( rtDW .
m3gfat1ui0 ) ; srClearBC ( rtDW . dk3vj22y05 ) ; srClearBC ( rtDW .
o3c1lu15ny ) ; srClearBC ( rtDW . j45e0raewi ) ; srClearBC ( rtDW .
o3wc5wwa4p ) ; srClearBC ( rtDW . irsxloeepq ) ; srClearBC ( rtDW .
cp3q1at4o2 ) ; srClearBC ( rtDW . pce44vep3x ) ; srClearBC ( rtDW .
mee1wioe1r ) ; srClearBC ( rtDW . a5nvnya1oe ) ; srClearBC ( rtDW .
dfax004odl ) ; srClearBC ( rtDW . mwuspmm2e1 ) ; srClearBC ( rtDW .
jgu1xgjxem ) ; srClearBC ( rtDW . my15ghhvb1 ) ; srClearBC ( rtDW .
bcd3kgenub ) ; srClearBC ( rtDW . f5k2rzim4a ) ; srClearBC ( rtDW .
nx3flbvahx ) ; srClearBC ( rtDW . lik1wotc2i ) ; srClearBC ( rtDW .
gg02mzoxhc ) ; srClearBC ( rtDW . gwxpzomgjh ) ; srClearBC ( rtDW .
etxqofccji ) ; srClearBC ( rtDW . ljwb0xnabb ) ; srClearBC ( rtDW .
ivkldwkotp ) ; srClearBC ( rtDW . hypqqzrtox ) ; rtB . ezgferlgph = rtX .
mupnfilrqo ; rtB . cwsbtrwpfc = ( real32_T ) rtB . ezgferlgph ; rtB .
ndwlmk3bzn = rtX . huyhg2ps31 ; n4kbehhhau = rtP . Gain2_Gain_ldmywfqo5l *
rtB . ndwlmk3bzn ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . nfipgrtuvr =
rtDW . cc0wkfbxf2 ; rtB . ehhntoamo3 = rtDW . eac1jvpkom ; rtB . glxqot4hmc =
rtP . Gain_Gain_nhdxkrws3j * rtB . ehhntoamo3 ; } if ( ssIsSampleHit ( rtS ,
3 , 0 ) ) { masm1qwyo5 ( & rtB . masm1qwyo5u , & rtDW . masm1qwyo5u , (
ev5xuv0chq * ) & rtP . masm1qwyo5u ) ; masm1qwyo5 ( & rtB . cdbewnv5xj , &
rtDW . cdbewnv5xj , ( ev5xuv0chq * ) & rtP . cdbewnv5xj ) ; masm1qwyo5 ( &
rtB . lwrmmrtmge , & rtDW . lwrmmrtmge , ( ev5xuv0chq * ) & rtP . lwrmmrtmge
) ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { { real_T t = ssGetTaskTime ( rtS
, 2 ) ; real_T * pTimeValues = ( real_T * ) rtDW . hvzkbecm4i . TimePtr ;
real_T * pDataValues = ( real_T * ) rtDW . hvzkbecm4i . DataPtr ; int
numPoints , lastPoint ; FWksInfo * fromwksInfo = ( FWksInfo * ) rtDW .
hvzkbecm4i . RSimInfoPtr ; numPoints = fromwksInfo -> nDataPoints ; lastPoint
= numPoints - 1 ; if ( t < pTimeValues [ 0 ] ) { jxyw3fewls = 0.0 ; } else if
( t >= pTimeValues [ lastPoint ] ) { jxyw3fewls = pDataValues [ lastPoint ] ;
} else { int_T currTimeIndex = rtDW . bfsa3u0wlu . PrevIndex ; if ( t <
pTimeValues [ currTimeIndex ] ) { while ( t < pTimeValues [ currTimeIndex ] )
{ currTimeIndex -- ; } } else { while ( t >= pTimeValues [ currTimeIndex + 1
] ) { currTimeIndex ++ ; } } jxyw3fewls = pDataValues [ currTimeIndex ] ;
rtDW . bfsa3u0wlu . PrevIndex = currTimeIndex ; } } if ( jxyw3fewls > rtP .
Saturation1_UpperSat_fkuqqwyy3e ) { rtB . nucdgci0rr = rtP .
Saturation1_UpperSat_fkuqqwyy3e ; } else if ( jxyw3fewls < rtP .
Saturation1_LowerSat_pr4ywobu3p ) { rtB . nucdgci0rr = rtP .
Saturation1_LowerSat_pr4ywobu3p ; } else { rtB . nucdgci0rr = jxyw3fewls ; }
{ real_T t = ssGetTaskTime ( rtS , 2 ) ; real_T * pTimeValues = ( real_T * )
rtDW . b2ezf5nkn2 . TimePtr ; real_T * pDataValues = ( real_T * ) rtDW .
b2ezf5nkn2 . DataPtr ; int numPoints , lastPoint ; FWksInfo * fromwksInfo = (
FWksInfo * ) rtDW . b2ezf5nkn2 . RSimInfoPtr ; numPoints = fromwksInfo ->
nDataPoints ; lastPoint = numPoints - 1 ; if ( t < pTimeValues [ 0 ] ) {
jxyw3fewls = 0.0 ; } else if ( t >= pTimeValues [ lastPoint ] ) { jxyw3fewls
= pDataValues [ lastPoint ] ; } else { int_T currTimeIndex = rtDW .
h4uocsxftg . PrevIndex ; if ( t < pTimeValues [ currTimeIndex ] ) { while ( t
< pTimeValues [ currTimeIndex ] ) { currTimeIndex -- ; } } else { while ( t
>= pTimeValues [ currTimeIndex + 1 ] ) { currTimeIndex ++ ; } } jxyw3fewls =
pDataValues [ currTimeIndex ] ; rtDW . h4uocsxftg . PrevIndex = currTimeIndex
; } } if ( jxyw3fewls > rtP . Saturation_UpperSat_drcjljjkd1 ) { rtB .
gwkex5211t = rtP . Saturation_UpperSat_drcjljjkd1 ; } else if ( jxyw3fewls <
rtP . Saturation_LowerSat_bfxwgbinrc ) { rtB . gwkex5211t = rtP .
Saturation_LowerSat_bfxwgbinrc ; } else { rtB . gwkex5211t = jxyw3fewls ; } }
if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtP .
ManualSwitch_CurrentSetting_myjoxppklo == 1 ) { if ( rtP .
ManualSwitch1_CurrentSetting == 1 ) { if ( rtP . ManualSwitch_CurrentSetting
== 1 ) { rtB . psdqponccq [ 0 ] = rtP . SliderGain_Gain * rtP .
Constant1_Value ; rtB . psdqponccq [ 1 ] = rtP . SliderGain_Gain_fxl4cn0nhs *
rtP . Constant_Value ; } else { rtB . psdqponccq [ 0 ] = rtB . masm1qwyo5u .
odrmud5052 ; rtB . psdqponccq [ 1 ] = rtB . cdbewnv5xj . odrmud5052 ; } }
else { rtB . psdqponccq [ 0 ] = rtB . lwrmmrtmge . odrmud5052 ; rtB .
psdqponccq [ 1 ] = rtP . Constant2_Value ; } } else { rtB . psdqponccq [ 0 ]
= rtB . nucdgci0rr ; rtB . psdqponccq [ 1 ] = rtB . gwkex5211t ; } } if ( rtP
. ManualSwitch1_CurrentSetting_h0jpqknavp == 1 ) { rtB . p2d41sdffb [ 0 ] =
rtU . ch4dzb1x4i ; rtB . p2d41sdffb [ 1 ] = rtU . gm151yhz1l ; } else { rtB .
p2d41sdffb [ 0 ] = rtB . psdqponccq [ 0 ] ; rtB . p2d41sdffb [ 1 ] = rtB .
psdqponccq [ 1 ] ; } b11wdxnlxt = rtP . Gain7_Gain * rtB . p2d41sdffb [ 1 ] ;
kmz3ui0uz0 = rtP . conversiontoRPM_Gain * b11wdxnlxt ; g0wrszfna1 = rtP .
Gain1_Gain * kmz3ui0uz0 ; etyvz2h2c5 ( rtB . glxqot4hmc , g0wrszfna1 , rtP .
Constant4_Value , rtP . Constant3_Value , rtP . Constant5_Value , rtP .
Constant9_Value , & rtB . haonxcq3pb ) ; o5ibp43cp4 = rtP .
Gain1_Gain_k3z2xphv3w * rtB . ezgferlgph ; if ( ssIsSampleHit ( rtS , 1 , 0 )
) { rtB . i45enf1q3e = rtP . Gain_Gain_bgx0ie0qw3 * rtB . ehhntoamo3 ; }
kcdukwoy0g = rtP . Gain1_Gain_gsz2kuibzm * kmz3ui0uz0 ; etyvz2h2c5 ( rtB .
i45enf1q3e , kcdukwoy0g , rtP . Constant6_Value , rtP .
Constant2_Value_jilhapm4hi , rtP . Constant7_Value , rtP . Constant8_Value ,
& rtB . b5mifpqvp3 ) ; if ( 1.0 / o5ibp43cp4 * n4kbehhhau >= rtP .
Switch_Threshold ) { efj5q5ebcq = o5ibp43cp4 / n4kbehhhau ; if ( efj5q5ebcq >
rtP . Switch1_Threshold_azwyz32q30 ) { if ( efj5q5ebcq > rtP .
Saturation1_UpperSat_l5pty0i0ge ) { efj5q5ebcq = rtP .
Saturation1_UpperSat_l5pty0i0ge ; } else { if ( efj5q5ebcq < rtP .
Saturation1_LowerSat_ov30a1gada ) { efj5q5ebcq = rtP .
Saturation1_LowerSat_ov30a1gada ; } } efj5q5ebcq = ( ( 1.0 - efj5q5ebcq ) *
0.14285714285714282 + efj5q5ebcq ) * ( 1.0 - efj5q5ebcq ) ; if ( efj5q5ebcq <
0.0 ) { o5iftc4ajm = - muDoubleScalarSqrt ( - efj5q5ebcq ) ; } else {
o5iftc4ajm = muDoubleScalarSqrt ( efj5q5ebcq ) ; } } else { o5iftc4ajm = rtP
. Constant1_Value_dtwovyy2kg ; } efj5q5ebcq = n4kbehhhau / rtB . nfipgrtuvr /
rtP . Ra_Value * n4kbehhhau * rtP . Gain2_Gain_ovbataovg4 ; if ( efj5q5ebcq <
0.0 ) { efj5q5ebcq = - muDoubleScalarSqrt ( muDoubleScalarAbs ( efj5q5ebcq )
) ; } else { efj5q5ebcq = muDoubleScalarSqrt ( efj5q5ebcq ) ; } if ( rtB .
haonxcq3pb . e2b5x1uxlg > rtP . Saturation_UpperSat_dzsaidwyzg ) {
ppfiifg3xk_idx_1 = rtP . Saturation_UpperSat_dzsaidwyzg ; } else if ( rtB .
haonxcq3pb . e2b5x1uxlg < rtP . Saturation_LowerSat_l1bt303gva ) {
ppfiifg3xk_idx_1 = rtP . Saturation_LowerSat_l1bt303gva ; } else {
ppfiifg3xk_idx_1 = rtB . haonxcq3pb . e2b5x1uxlg ; } lgp0omksql = efj5q5ebcq
* ppfiifg3xk_idx_1 * o5iftc4ajm * rtP . Gain2_Gain_i3ytcncqtp ; } else {
efj5q5ebcq = 1.0 / o5ibp43cp4 * n4kbehhhau ; if ( efj5q5ebcq > rtP .
Switch1_Threshold_poxw0fzcvi ) { if ( efj5q5ebcq > rtP .
Saturation1_UpperSat_b4sddjbmu4 ) { efj5q5ebcq = rtP .
Saturation1_UpperSat_b4sddjbmu4 ; } else { if ( efj5q5ebcq < rtP .
Saturation1_LowerSat_jzbybanmuo ) { efj5q5ebcq = rtP .
Saturation1_LowerSat_jzbybanmuo ; } } efj5q5ebcq = ( ( 1.0 - efj5q5ebcq ) *
0.14285714285714282 + efj5q5ebcq ) * ( 1.0 - efj5q5ebcq ) ; if ( efj5q5ebcq <
0.0 ) { o5iftc4ajm = - muDoubleScalarSqrt ( - efj5q5ebcq ) ; } else {
o5iftc4ajm = muDoubleScalarSqrt ( efj5q5ebcq ) ; } } else { o5iftc4ajm = rtP
. Constant1_Value_p5hzjcc2mh ; } efj5q5ebcq = o5ibp43cp4 / rtB . nfipgrtuvr /
rtP . Ra_Value * o5ibp43cp4 * rtP . Gain2_Gain_dnatce3asn ; if ( efj5q5ebcq <
0.0 ) { efj5q5ebcq = - muDoubleScalarSqrt ( muDoubleScalarAbs ( efj5q5ebcq )
) ; } else { efj5q5ebcq = muDoubleScalarSqrt ( efj5q5ebcq ) ; } if ( rtB .
b5mifpqvp3 . e2b5x1uxlg > rtP . Saturation_UpperSat_nesqhf0mrq ) {
ppfiifg3xk_idx_1 = rtP . Saturation_UpperSat_nesqhf0mrq ; } else if ( rtB .
b5mifpqvp3 . e2b5x1uxlg < rtP . Saturation_LowerSat_fuvtfoywaf ) {
ppfiifg3xk_idx_1 = rtP . Saturation_LowerSat_fuvtfoywaf ; } else {
ppfiifg3xk_idx_1 = rtB . b5mifpqvp3 . e2b5x1uxlg ; } lgp0omksql = efj5q5ebcq
* ppfiifg3xk_idx_1 * o5iftc4ajm * rtP . Gain2_Gain_giae1yyt3d * rtP .
Gain_Gain_lblkibiobo ; } if ( lgp0omksql > rtP .
Saturation1_UpperSat_ed2d1dsvvu ) { rtB . ixoqjsjjol = rtP .
Saturation1_UpperSat_ed2d1dsvvu ; } else if ( lgp0omksql < rtP .
Saturation1_LowerSat_n0bdrwhesa ) { rtB . ixoqjsjjol = rtP .
Saturation1_LowerSat_n0bdrwhesa ; } else { rtB . ixoqjsjjol = lgp0omksql ; }
{ real_T t = ssGetTaskTime ( rtS , 0 ) ; real_T * pTimeValues = ( real_T * )
rtDW . dlyfy0ipc5 . TimePtr ; real_T * pDataValues = ( real_T * ) rtDW .
dlyfy0ipc5 . DataPtr ; int numPoints , lastPoint ; FWksInfo * fromwksInfo = (
FWksInfo * ) rtDW . dlyfy0ipc5 . RSimInfoPtr ; numPoints = fromwksInfo ->
nDataPoints ; lastPoint = numPoints - 1 ; if ( t < pTimeValues [ 0 ] ) {
kmz3ui0uz0 = 0.0 ; } else if ( t >= pTimeValues [ lastPoint ] ) { kmz3ui0uz0
= pDataValues [ lastPoint ] ; } else { int_T currTimeIndex = rtDW .
fwkxoupfre . PrevIndex ; if ( t < pTimeValues [ currTimeIndex ] ) { while ( t
< pTimeValues [ currTimeIndex ] ) { currTimeIndex -- ; } } else { while ( t
>= pTimeValues [ currTimeIndex + 1 ] ) { currTimeIndex ++ ; } } kmz3ui0uz0 =
pDataValues [ currTimeIndex ] ; rtDW . fwkxoupfre . PrevIndex = currTimeIndex
; } } npiyznthqi = rtX . lgbs44xptg ; o5iftc4ajm = 1.0 / kmz3ui0uz0 * rtX .
lgbs44xptg ; { real_T t = ssGetTaskTime ( rtS , 0 ) ; real_T * pTimeValues =
( real_T * ) rtDW . oi2egj2zap . TimePtr ; real_T * pDataValues = ( real_T *
) rtDW . oi2egj2zap . DataPtr ; int numPoints , lastPoint ; FWksInfo *
fromwksInfo = ( FWksInfo * ) rtDW . oi2egj2zap . RSimInfoPtr ; numPoints =
fromwksInfo -> nDataPoints ; lastPoint = numPoints - 1 ; if ( t < pTimeValues
[ 0 ] ) { ij2wjykslx = 0.0 ; } else if ( t >= pTimeValues [ lastPoint ] ) {
ij2wjykslx = pDataValues [ lastPoint ] ; } else { int_T currTimeIndex = rtDW
. fb1c24lf0o . PrevIndex ; if ( t < pTimeValues [ currTimeIndex ] ) { while (
t < pTimeValues [ currTimeIndex ] ) { currTimeIndex -- ; } } else { while ( t
>= pTimeValues [ currTimeIndex + 1 ] ) { currTimeIndex ++ ; } } ij2wjykslx =
pDataValues [ currTimeIndex ] ; rtDW . fb1c24lf0o . PrevIndex = currTimeIndex
; } } rtB . gurfdczwyr = rtX . ka43gmkysq ; beiewzgadl = rtP .
conversiontoRPM_Gain_aifzn4wkiq * rtB . gurfdczwyr ; ll4keb2h0s_idx_3 = rtP .
Constant1_Value_ar1vpqpi0c ; efj5q5ebcq = ( muDoubleScalarTanh ( ( beiewzgadl
- 25000.0 ) * 2.0 * 3.1415926535897931 / 25000.0 ) + 1.0 ) * 0.5 ; for ( i =
0 ; i < 6 ; i ++ ) { PRcoeffs [ i ] = ( 1.0 - efj5q5ebcq ) * rtP .
Constant5_Value_blirrlxqgk [ i ] + rtP . Constant5_Value_blirrlxqgk [ i + 6 ]
* efj5q5ebcq ; } do3ymddtym = o5iftc4ajm ; efj5q5ebcq = 0.052359877559829883
* rtP . Constant_Value_gwpofekbsw * beiewzgadl ; n4kbehhhau = efj5q5ebcq /
muDoubleScalarSqrt ( rtP . Constant3_Value_jcaewg4fcb * rtP .
Constant4_Value_kguicwhsfv * ij2wjykslx ) ; tmp_j [ 0 ] = 0.0003 ; tmp_j [ 1
] = ( muDoubleScalarPower ( o5iftc4ajm , ( rtP . Constant3_Value_jcaewg4fcb -
1.0 ) / rtP . Constant3_Value_jcaewg4fcb ) - 1.0 ) * ( rtP .
Constant1_Value_ar1vpqpi0c * ij2wjykslx ) / ( 0.5 * efj5q5ebcq * efj5q5ebcq )
; tmp_j [ 2 ] = 10.0 ; o5ibp43cp4 = fqbwtfdojd ( tmp_j ) ; exgwciklzi =
PRcoeffs [ 1 ] * n4kbehhhau + PRcoeffs [ 0 ] ; lc44cjozax = PRcoeffs [ 3 ] *
n4kbehhhau + PRcoeffs [ 2 ] ; PR = PRcoeffs [ 5 ] * n4kbehhhau + PRcoeffs [ 4
] ; PhiC = ( PR * o5ibp43cp4 - exgwciklzi ) / ( lc44cjozax + o5ibp43cp4 ) ;
e4bvnp5vjd = PhiC ; tmp_g [ 0 ] = 0.001 ; tmp_g [ 1 ] = PhiC * rtP .
Constant2_Value_jsvh2omtfu * 0.78539816339744828 * rtP .
Constant_Value_gwpofekbsw * rtP . Constant_Value_gwpofekbsw * efj5q5ebcq ;
tmp_g [ 2 ] = 0.3 ; W_comp = fqbwtfdojd ( tmp_g ) ; ppxu00rks2 = ( rtP .
Constant6_Value_bzlxiqld1i [ 1 ] * n4kbehhhau + rtP .
Constant6_Value_bzlxiqld1i [ 0 ] ) / ( rtP . Constant6_Value_bzlxiqld1i [ 2 ]
- n4kbehhhau ) ; bguiqh0znq = ( rtP . Constant6_Value_bzlxiqld1i [ 4 ] *
n4kbehhhau + rtP . Constant6_Value_bzlxiqld1i [ 3 ] ) / ( rtP .
Constant6_Value_bzlxiqld1i [ 5 ] - n4kbehhhau ) ; gjrh3vhxv1 = ( rtP .
Constant6_Value_bzlxiqld1i [ 7 ] * n4kbehhhau + rtP .
Constant6_Value_bzlxiqld1i [ 6 ] ) / ( rtP . Constant6_Value_bzlxiqld1i [ 8 ]
- n4kbehhhau ) ; aktecqyana = ( PhiC * PhiC * ppxu00rks2 + bguiqh0znq * PhiC
) + gjrh3vhxv1 ; tmp_m [ 0 ] = 7.0 ; tmp_m [ 1 ] = ( muDoubleScalarPower (
o5iftc4ajm , ( rtP . Constant3_Value_jcaewg4fcb - 1.0 ) / rtP .
Constant3_Value_jcaewg4fcb ) - 1.0 ) * ( ij2wjykslx / aktecqyana ) ; tmp_m [
2 ] = 150.0 ; delta_T_comp = fqbwtfdojd ( tmp_m ) ; j1s5yn2ijo = ij2wjykslx +
delta_T_comp ; csqmlvrkng = W_comp * rtP . Constant1_Value_ar1vpqpi0c *
delta_T_comp ; rtB . bxgw3kq3ij = W_comp ; omzt3u0gfx = efj5q5ebcq ;
edr234t3il = n4kbehhhau ; ebo5aiznrs = o5ibp43cp4 ; hribjanxea = exgwciklzi ;
j4ebfdbclg = lc44cjozax ; gr15gli4w1 = PR ; iet23ldaul = PhiC ; g2kaq151q0 =
aktecqyana ; gsvm4zgv5t = ppxu00rks2 ; kd01knh0r3 = bguiqh0znq ; mnhajo5ou4 =
gjrh3vhxv1 ; rtB . pe0kzgwhkx = rtB . ixoqjsjjol / ( rtB . ixoqjsjjol + rtB .
bxgw3kq3ij ) * rtP . Gain2_Gain_atufxtbbsi ; rtB . ffjdcznvkg = ( real32_T )
rtB . pe0kzgwhkx ; rtB . itsvvwrq0a = ( real32_T ) rtB . p2d41sdffb [ 0 ] ;
rtB . ljk4xix01m = ( real32_T ) rtB . p2d41sdffb [ 1 ] ; rtB . eiwdrfcxnn = (
real32_T ) rtB . ndwlmk3bzn ; kmz3ui0uz0 = rtX . iqp0o3u0ph ; imz3hxnyez =
1.0 / ( rtP . R_air1_Gain * kmz3ui0uz0 ) * rtB . ezgferlgph ; rtB .
m3qm5dlk4i = ( real32_T ) imz3hxnyez - rtP . ctok_Value_czyz5znrbb ; rtB .
apexfxt05y = ( real32_T ) ( rtP . Gain3_Gain * rtB . ixoqjsjjol ) ; rtB .
evxrp31n1t = ( real32_T ) ( rtP . Gain4_Gain * rtB . bxgw3kq3ij ) ;
efj5q5ebcq = rtP . conversiontoRPM_Gain_hamejm3o4p * b11wdxnlxt ; gen03hfvbg
= rtX . iynqfp2xbi ; rtB . mnmkwbcoth = 1.0 / ( rtP . R_air_Gain * rtX .
iynqfp2xbi ) * rtB . ndwlmk3bzn ; x [ 0 ] = 100.0 ; x [ 1 ] = rtB .
mnmkwbcoth ; x [ 2 ] = 2000.0 ; if ( ( 100.0 <= rtB . mnmkwbcoth ) ||
muDoubleScalarIsNaN ( rtB . mnmkwbcoth ) ) { if ( rtB . mnmkwbcoth <= 2000.0
) { idx_idx_1 = 2 ; idx_idx_2 = 3 ; } else { idx_idx_1 = 3 ; idx_idx_2 = 2 ;
} } else { idx_idx_1 = 1 ; idx_idx_2 = 3 ; } if ( muDoubleScalarIsNaN ( x [
idx_idx_2 - 1 ] ) ) { ppfiifg3xk_idx_1 = x [ idx_idx_2 - 1 ] ; } else {
ppfiifg3xk_idx_1 = x [ idx_idx_1 - 1 ] ; } o5iftc4ajm = ( ( ( ( rtP .
Constant2_Value_ph0axwg3ul [ 1 ] * efj5q5ebcq + rtP .
Constant2_Value_ph0axwg3ul [ 0 ] ) + efj5q5ebcq * efj5q5ebcq * rtP .
Constant2_Value_ph0axwg3ul [ 2 ] ) + rtP . Constant2_Value_ph0axwg3ul [ 3 ] *
rtB . ndwlmk3bzn ) + rtP . Constant2_Value_ph0axwg3ul [ 4 ] * rtB .
ezgferlgph ) + rtP . Constant2_Value_ph0axwg3ul [ 5 ] * rtB . ndwlmk3bzn /
muDoubleScalarSqrt ( ppfiifg3xk_idx_1 ) ; aadj45x0pt = o5iftc4ajm ;
jalnkh4fhi = o5iftc4ajm * rtB . ezgferlgph * efj5q5ebcq * rtP .
Constant_Value_g3u4sx54dp / ( 120.0 * rtP . Constant1_Value_lma0kogrsm *
imz3hxnyez ) * rtP . Gain_Gain_dlhxvjf4sb ; if ( rtB . p2d41sdffb [ 1 ] > rtP
. Saturation_UpperSat_awfrwwo30m ) { ppfiifg3xk_idx_1 = rtP .
Saturation_UpperSat_awfrwwo30m ; } else if ( rtB . p2d41sdffb [ 1 ] < rtP .
Saturation_LowerSat_ggypqh2rl4 ) { ppfiifg3xk_idx_1 = rtP .
Saturation_LowerSat_ggypqh2rl4 ; } else { ppfiifg3xk_idx_1 = rtB . p2d41sdffb
[ 1 ] ; } rtB . ksaqwiryhv = ( real32_T ) ( rtP . n1_Gain * jalnkh4fhi * rtP
. n2_Gain / ppfiifg3xk_idx_1 ) ; if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB .
j0uztscc4c = rtB . cwsbtrwpfc ; rtB . fllsdcflzq = rtP . mon_map_Gain * rtB .
j0uztscc4c ; rtDW . estlkslffw = rtB . fllsdcflzq ; rtB . ir10qbb2h0 = rtP .
mon_wegr_Gain * rtB . ffjdcznvkg ; rtDW . dpzir5hccd = rtB . ir10qbb2h0 ;
hde10siz3b_idx_0 = rtDW . avtbwzqnkf [ 0 ] ; hde10siz3b_idx_1 = rtDW .
avtbwzqnkf [ 1 ] ; cesfgrkder_idx_0 = rtDW . avtbwzqnkf [ 0 ] - rtP .
ue_Value [ 0 ] ; cesfgrkder_idx_1 = rtDW . avtbwzqnkf [ 1 ] - rtP . ue_Value
[ 1 ] ; o2wgigs4ap_idx_0 = rtP . Gain4_Gain_ff4g3pyzm4 [ 0 ] *
cesfgrkder_idx_0 + rtP . Gain4_Gain_ff4g3pyzm4 [ 2 ] * cesfgrkder_idx_1 ;
lqaourhjqh = rtP . Gain4_Gain_ff4g3pyzm4 [ 1 ] * cesfgrkder_idx_0 + rtP .
Gain4_Gain_ff4g3pyzm4 [ 3 ] * cesfgrkder_idx_1 ; rtB . lgha5fyofj = rtP .
man_tuneFiltalpha1_Gain * rtDW . owcamicoch ; if ( rtB . lgha5fyofj > rtP .
Saturation1_UpperSat_evi3lcggpc ) { tmp_b = rtP .
Saturation1_UpperSat_evi3lcggpc ; } else if ( rtB . lgha5fyofj < rtP .
Saturation1_LowerSat_hvawqdgu0g ) { tmp_b = rtP .
Saturation1_LowerSat_hvawqdgu0g ; } else { tmp_b = rtB . lgha5fyofj ; }
hhjnxjzwip = rtDW . poa5fptxm4 * tmp_b ; rtB . lj0vvkbxsr = rtP .
man_tuneFiltalpha_Gain * rtDW . owcamicoch ; if ( rtB . lj0vvkbxsr > rtP .
Saturation4_UpperSat_ox5ea3vzv2 ) { tmp_b = rtP .
Saturation4_UpperSat_ox5ea3vzv2 ; } else if ( rtB . lj0vvkbxsr < rtP .
Saturation4_LowerSat_fnwk5eluqv ) { tmp_b = rtP .
Saturation4_LowerSat_fnwk5eluqv ; } else { tmp_b = rtB . lj0vvkbxsr ; }
alqkjudhu3 = rtP . zero1_Value - tmp_b ; rtB . m5uqx1qg4p = rtP .
man_wcyl_gperrev_Gain * rtDW . bpo1eig15d ; if ( rtB . m5uqx1qg4p > rtP .
zero3_Value ) { o3mfdsmmfb = rtB . ksaqwiryhv * rtB . ljk4xix01m / rtP .
mintos_Value ; } else { o3mfdsmmfb = rtB . ksaqwiryhv ; } pcwwxeoehv = rtDW .
bsbxmlf10r ; rtB . jofwokwi4b = rtP . man_use_Wcylinterp_Gain * rtDW .
o0hytehsup ; if ( rtB . jofwokwi4b > rtP . zero2_Value ) {
LookUp_real32_T_real32_T ( & ( lx1uc222jj ) , rtP . interp_YData , pcwwxeoehv
, rtP . interp_XData , 1U ) ; o3mfdsmmfb = ( rtP . one_Value_aeususitml -
lx1uc222jj ) * rtB . evxrp31n1t + o3mfdsmmfb * lx1uc222jj ; } rtB .
jendnkkere = rtP . man_wegrhat_gain_Gain * rtDW . jnju4d4o03 ; if ( rtB .
m3qm5dlk4i > rtP . Saturation5_UpperSat_dlhoczu115 ) { es40kk5dcp = rtP .
Saturation5_UpperSat_dlhoczu115 ; } else if ( rtB . m3qm5dlk4i < rtP .
Saturation5_LowerSat_duc145inwk ) { es40kk5dcp = rtP .
Saturation5_LowerSat_duc145inwk ; } else { es40kk5dcp = rtB . m3qm5dlk4i ; }
u0 = rtP . CtoK_Value + es40kk5dcp ; if ( u0 > rtP .
Saturation4_UpperSat_nmdcwefbw5 ) { u0 = rtP .
Saturation4_UpperSat_nmdcwefbw5 ; } else { if ( u0 < rtP .
Saturation4_LowerSat_pc32rj1qgb ) { u0 = rtP .
Saturation4_LowerSat_pc32rj1qgb ; } } if ( rtP . R_Value > rtP .
Saturation2_UpperSat_hskdnsucj5 ) { tmp_b = rtP .
Saturation2_UpperSat_hskdnsucj5 ; } else if ( rtP . R_Value < rtP .
Saturation2_LowerSat_pvcw4rcoue ) { tmp_b = rtP .
Saturation2_LowerSat_pvcw4rcoue ; } else { tmp_b = rtP . R_Value ; }
o3mfdsmmfb += ( rtB . j0uztscc4c - rtDW . pybwwu5s4d ) * rtB . jendnkkere *
rtP . V_Value / u0 / tmp_b - rtB . evxrp31n1t ; if ( o3mfdsmmfb > rtP .
Saturation1_UpperSat_kk32mwbior ) { o3mfdsmmfb = rtP .
Saturation1_UpperSat_kk32mwbior ; } else { if ( o3mfdsmmfb < rtP .
Saturation1_LowerSat_bt1eom2vut ) { o3mfdsmmfb = rtP .
Saturation1_LowerSat_bt1eom2vut ; } } rtB . jnglkal4bm = alqkjudhu3 *
o3mfdsmmfb + hhjnxjzwip ; u0 = rtB . jnglkal4bm + rtB . evxrp31n1t ; if ( u0
> rtP . Saturation3_UpperSat_aodcenepxv ) { u0 = rtP .
Saturation3_UpperSat_aodcenepxv ; } else { if ( u0 < rtP .
Saturation3_LowerSat_dbo42efvqo ) { u0 = rtP .
Saturation3_LowerSat_dbo42efvqo ; } } orelggziy4 = rtB . jnglkal4bm / u0 *
rtP . Gain7_Gain_je5is4zb3m ; rtB . btjw2bwujo = rtP . man_use_wegrhat_Gain *
rtDW . hyhv0echnn ; if ( rtB . btjw2bwujo > rtP . zero3_Value_c4pusxmemm ) {
rtB . asokdz5ql3 = orelggziy4 ; } else { rtB . asokdz5ql3 = rtB . ffjdcznvkg
; } o2wgigs4ap_idx_0 = rtB . j0uztscc4c - o2wgigs4ap_idx_0 ; o2wgigs4ap_idx_0
= ( o2wgigs4ap_idx_0 - rtP . ye_Value [ 0 ] ) - rtP . Gain_Gain_ji33gjxgix [
0 ] * rtDW . j5f3ay4xaq ; rtB . dtnj1tjnn0 = ( ( ( ( ( rtB . asokdz5ql3 -
lqaourhjqh ) - rtP . ye_Value [ 1 ] ) - rtP . Gain_Gain_ji33gjxgix [ 1 ] *
rtDW . j5f3ay4xaq ) * rtP . Gain1_Gain_ktwf12ggqn [ 1 ] + rtP .
Gain1_Gain_ktwf12ggqn [ 0 ] * o2wgigs4ap_idx_0 ) + rtP .
Gain2_Gain_b5usxkmjtz * rtDW . j5f3ay4xaq ) + ( rtP . Gain3_Gain_khxel0hppy [
0 ] * cesfgrkder_idx_0 + rtP . Gain3_Gain_khxel0hppy [ 1 ] * cesfgrkder_idx_1
) ; rtB . lsc4svyhjg = rtB . dtnj1tjnn0 - rtDW . ackerqxqlr ; rtB .
epaoao0ex4 = rtP . man_use_ROO_Gain * rtDW . dhb1ak5ywv ; if ( rtB .
epaoao0ex4 > rtP . zero8_Value_enfwb3sxd4 ) { rtB . kzspe3uhcs [ 0 ] = rtB .
lsc4svyhjg ; rtB . kzspe3uhcs [ 1 ] = rtDW . c1qvpfpyqu ; rtB . kzspe3uhcs [
2 ] = rtDW . em10zry3vm ; } else { rtB . kzspe3uhcs [ 0 ] = rtDW . cz55ow2si1
[ 0 ] ; rtB . kzspe3uhcs [ 1 ] = rtDW . cz55ow2si1 [ 1 ] ; rtB . kzspe3uhcs [
2 ] = rtDW . cz55ow2si1 [ 2 ] ; } rtB . cjbmrximrw = rtP . mon_map_hat_Gain *
rtB . kzspe3uhcs [ 1 ] ; rtDW . n5pkawvqdo = rtB . cjbmrximrw ; rtB .
dlanmxddxv = rtP . mon_egrr_hat_Gain * rtB . kzspe3uhcs [ 2 ] ; rtDW .
c1deueau4e = rtB . dlanmxddxv ; rtB . pidy302dbb = rtP . mon_x1_hat_Gain *
rtB . kzspe3uhcs [ 0 ] ; rtDW . mi5h1pks4n = rtB . pidy302dbb ; rtB .
cqzg3fjzex = rtP . man_use_wegrhat2_Gain * rtDW . hyhv0echnn ; if ( rtB .
cqzg3fjzex > rtP . zero2_Value_mzu0rbqhwf ) { o2wgigs4ap_idx_0 = rtB .
jnglkal4bm ; } else { o2wgigs4ap_idx_0 = rtB . apexfxt05y ; } lqaourhjqh =
rtP . Gain8_Gain * es40kk5dcp + rtP . ctok_Value ; rtB . ompjonegnn = rtP .
man_pexh_adder_Gain * rtDW . fllyhv1jnh ; batdnpsvim = rtB . ompjonegnn + rtB
. eiwdrfcxnn ; rtB . kmhklseyi0 = rtP . man_tuneFiltalpha1_Gain_na2addg3ve *
rtDW . owcamicoch ; rtB . lz1xovijdz = rtP .
man_tuneFiltalpha_Gain_muc2cpzprk * rtDW . owcamicoch ; rtB . o2frmjlatg =
rtB . itsvvwrq0a * rtB . ljk4xix01m * rtP . n9_Gain ; if ( rtB . kmhklseyi0 >
rtP . Saturation1_UpperSat_aiumrxurnx ) { tmp_b = rtP .
Saturation1_UpperSat_aiumrxurnx ; } else if ( rtB . kmhklseyi0 < rtP .
Saturation1_LowerSat_hmzuy5u0pb ) { tmp_b = rtP .
Saturation1_LowerSat_hmzuy5u0pb ; } else { tmp_b = rtB . kmhklseyi0 ; } if (
rtB . lz1xovijdz > rtP . Saturation4_UpperSat_mli4xalwq5 ) { cesfgrkder_idx_0
= rtP . Saturation4_UpperSat_mli4xalwq5 ; } else if ( rtB . lz1xovijdz < rtP
. Saturation4_LowerSat_o1m3sqjmh3 ) { cesfgrkder_idx_0 = rtP .
Saturation4_LowerSat_o1m3sqjmh3 ; } else { cesfgrkder_idx_0 = rtB .
lz1xovijdz ; } rtB . dkpngqys4z = ( rtP . zero1_Value_mjmu52lvvx -
cesfgrkder_idx_0 ) * ( rtB . o2frmjlatg - rtDW . dgfekwwlr1 ) + rtDW .
lzwd5z4dbk * tmp_b ; rtB . h2ldtsrohl = rtP .
man_tuneFiltalpha1_Gain_cqsveg5rxa * rtDW . owcamicoch ; rtB . ittbcftddk =
rtP . man_tuneFiltalpha_Gain_m1s1jazml1 * rtDW . owcamicoch ; if ( rtB .
h2ldtsrohl > rtP . Saturation1_UpperSat_aeygqv5amr ) { tmp_b = rtP .
Saturation1_UpperSat_aeygqv5amr ; } else if ( rtB . h2ldtsrohl < rtP .
Saturation1_LowerSat_imqjfndrcy ) { tmp_b = rtP .
Saturation1_LowerSat_imqjfndrcy ; } else { tmp_b = rtB . h2ldtsrohl ; } if (
rtB . ittbcftddk > rtP . Saturation4_UpperSat_heyzyhtkkx ) { cesfgrkder_idx_0
= rtP . Saturation4_UpperSat_heyzyhtkkx ; } else if ( rtB . ittbcftddk < rtP
. Saturation4_LowerSat_fudpzb5job ) { cesfgrkder_idx_0 = rtP .
Saturation4_LowerSat_fudpzb5job ; } else { cesfgrkder_idx_0 = rtB .
ittbcftddk ; } rtB . ighfnj0qfi = ( rtP . zero1_Value_cfkzinnzed -
cesfgrkder_idx_0 ) * ( rtB . ljk4xix01m - rtDW . letoggxozl ) + rtDW .
dw2dt5amj1 * tmp_b ; for ( i = 0 ; i < 2 ; i ++ ) { tmp_b = rtP .
Gain10_Gain_bwanyq3goq [ i + 6 ] * rtB . ighfnj0qfi + ( rtP .
Gain10_Gain_bwanyq3goq [ i + 4 ] * rtB . dkpngqys4z + ( rtP .
Gain10_Gain_bwanyq3goq [ i + 2 ] * 0.0F + rtP . Gain10_Gain_bwanyq3goq [ i ]
* 0.0F ) ) ; tmp_f [ i ] = tmp_b ; } duexjpu5rm_p = ( ( rtP .
Gain7_Gain_hdbaustsmr [ 0 ] * rtDW . h4gbii3cbq + rtP . Gain7_Gain_hdbaustsmr
[ 2 ] * rtDW . o04t4yciip ) + tmp_f [ 0 ] ) * rtP . Gain11_Gain_o3ain5lccm [
0 ] + ( ( rtP . Gain7_Gain_hdbaustsmr [ 1 ] * rtDW . h4gbii3cbq + rtP .
Gain7_Gain_hdbaustsmr [ 3 ] * rtDW . o04t4yciip ) + tmp_f [ 1 ] ) * rtP .
Gain11_Gain_o3ain5lccm [ 1 ] ; s60_iter = 1 ; meppapiqj0 = ( rtP .
y_cons1_Value != 0.0F ) ; while ( meppapiqj0 && ( s60_iter <= 5 ) ) {
hhjnxjzwip = rtP . Gain10_Gain * pcwwxeoehv ; alqkjudhu3 = rtP . Gain11_Gain
* rtB . ljk4xix01m ; if ( rtB . j0uztscc4c > rtP .
Saturation4_UpperSat_ne3ia3nb0j ) { g1ekzbu3oi = rtP .
Saturation4_UpperSat_ne3ia3nb0j ; } else if ( rtB . j0uztscc4c < rtP .
Saturation4_LowerSat_hbatond2b0 ) { g1ekzbu3oi = rtP .
Saturation4_LowerSat_hbatond2b0 ; } else { g1ekzbu3oi = rtB . j0uztscc4c ; }
es40kk5dcp = rtP . Gain3_Gain_gi5nnsebzm * hhjnxjzwip ; if ( es40kk5dcp > rtP
. Saturation1_UpperSat_mmdkyxpjcy ) { es40kk5dcp = rtP .
Saturation1_UpperSat_mmdkyxpjcy ; } else { if ( es40kk5dcp < rtP .
Saturation1_LowerSat_m5mjtmtt23 ) { es40kk5dcp = rtP .
Saturation1_LowerSat_m5mjtmtt23 ; } } pwkaxiafxx = rtP .
Gain6_Gain_mzhcfliz3a * duexjpu5rm_p ; rtB . ilgb03fx1o = rtP .
man_pex_eps_Gain * rtDW . ayjpjfupkc ; fzccphw1bz = rtP .
Gain1_Gain_ok5bp1tyb1 * rtB . j0uztscc4c ; if ( pwkaxiafxx > rtP .
Saturation5_UpperSat ) { c2fdcpgrsp = rtP . Saturation5_UpperSat ; } else if
( pwkaxiafxx < rtP . Saturation5_LowerSat ) { c2fdcpgrsp = rtP .
Saturation5_LowerSat ; } else { c2fdcpgrsp = pwkaxiafxx ; } if ( rtDW .
dvtr5mddec != 0 ) { ssSetSolverNeedsReset ( rtS ) ; rtDW . ehd3s5jupn = rtP .
UnitDelay_InitialCondition ; } rtDW . dvtr5mddec = 1U ; for ( ffd3q0dmho = 1
; ffd3q0dmho <= rtP . ForIterator_IterationLimit ; ffd3q0dmho ++ ) { if (
ffd3q0dmho > rtP . Saturation1_UpperSat_lrtspvu1in ) { i = rtP .
Saturation1_UpperSat_lrtspvu1in ; } else if ( ffd3q0dmho < rtP .
Saturation1_LowerSat_cp3gsgarn4 ) { i = rtP . Saturation1_LowerSat_cp3gsgarn4
; } else { i = ffd3q0dmho ; } i -- ; o3mfdsmmfb = hhjnxjzwip - rtP .
Constant12_Value_p4sdtff4av [ i ] ; cesfgrkder_idx_1 = o3mfdsmmfb *
o3mfdsmmfb ; o3mfdsmmfb = alqkjudhu3 - rtP . Constant11_Value_dfwxcchqhl [ i
] ; c22to2uley = ( ( 0.0F - cesfgrkder_idx_1 ) - o3mfdsmmfb * o3mfdsmmfb ) /
( rtP . Constant14_Value * rtP . Constant14_Value * rtP .
Gain_Gain_loxnzerzgs ) ; LookUp_real32_T_real32_T ( & ( cqse1wvpl2 ) , rtP .
expLookupTable_YData , c22to2uley , rtP . expLookupTable_XData , 102U ) ; rtB
. arcts1reys = cqse1wvpl2 * rtP . Constant10_Value [ i ] + rtDW . ehd3s5jupn
; rtDW . ehd3s5jupn = rtB . arcts1reys ; } if ( rtP .
Constant7_Value_jx1utvbjk0 > rtP . Saturation4_UpperSat_f5y5vur4ve ) {
hhjnxjzwip = rtP . Saturation4_UpperSat_f5y5vur4ve ; } else if ( rtP .
Constant7_Value_jx1utvbjk0 < rtP . Saturation4_LowerSat_kbnhpimcru ) {
hhjnxjzwip = rtP . Saturation4_LowerSat_kbnhpimcru ; } else { hhjnxjzwip =
rtP . Constant7_Value_jx1utvbjk0 ; } if ( lqaourhjqh > rtP .
Saturation2_UpperSat_fjp1hny0ya ) { cesfgrkder_idx_0 = rtP .
Saturation2_UpperSat_fjp1hny0ya ; } else if ( lqaourhjqh < rtP .
Saturation2_LowerSat_gqdcpi2olt ) { cesfgrkder_idx_0 = rtP .
Saturation2_LowerSat_gqdcpi2olt ; } else { cesfgrkder_idx_0 = lqaourhjqh ; }
hhjnxjzwip = rtP . Constant8_Value_bk5pmdij31 / cesfgrkder_idx_0 / hhjnxjzwip
/ hhjnxjzwip ; if ( hhjnxjzwip > rtP . Saturation_UpperSat_d0ebinhgkh ) {
hhjnxjzwip = rtP . Saturation_UpperSat_d0ebinhgkh ; } else { if ( hhjnxjzwip
< rtP . Saturation_LowerSat_czzo0et5n0 ) { hhjnxjzwip = rtP .
Saturation_LowerSat_czzo0et5n0 ; } } alqkjudhu3 = muSingleScalarSqrt (
hhjnxjzwip ) ; idx_idx_1 = rtDW . awpbtqxcnq ; idx_idx_2 = ( int8_T ) ! (
fzccphw1bz / c2fdcpgrsp <= 0.4167F ) ; rtDW . awpbtqxcnq = idx_idx_2 ; if (
idx_idx_1 != idx_idx_2 ) { switch ( idx_idx_1 ) { case 0 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 1 : ssSetSolverNeedsReset ( rtS
) ; break ; } } switch ( idx_idx_2 ) { case 0 : if ( idx_idx_2 != idx_idx_1 )
{ if ( ssGetTaskTime ( rtS , 2 ) != ssGetTStart ( rtS ) ) {
ssSetSolverNeedsReset ( rtS ) ; } } u0 = ( rtP . one_Value_gh4ygofu0g + rtP .
Constant13_Value_drcxtjpegy ) * rtP . Gain6_Gain_oo3qmk1vhv ; if ( u0 > rtP .
Saturation3_UpperSat_fpowc2uvdu ) { u0 = rtP .
Saturation3_UpperSat_fpowc2uvdu ; } else { if ( u0 < rtP .
Saturation3_LowerSat_b1lgcpn3h4 ) { u0 = rtP .
Saturation3_LowerSat_b1lgcpn3h4 ; } } u0 = rtP . Constant13_Value_drcxtjpegy
/ u0 ; if ( u0 > rtP . Saturation1_UpperSat_jhk0udkkso ) { u0 = rtP .
Saturation1_UpperSat_jhk0udkkso ; } else { if ( u0 < rtP .
Saturation1_LowerSat_aobxdvcimk ) { u0 = rtP .
Saturation1_LowerSat_aobxdvcimk ; } } rtB . arhywgn0ud [ 0 ] = rtB .
arcts1reys * alqkjudhu3 * muSingleScalarSqrt ( u0 ) ; u0 = ( rtP . one1_Value
+ rtP . Constant13_Value_drcxtjpegy ) * rtP . Gain1_Gain_gb423uv2ae ; if ( u0
> rtP . Saturation4_UpperSat_fgk5yexhjk ) { u0 = rtP .
Saturation4_UpperSat_fgk5yexhjk ; } else { if ( u0 < rtP .
Saturation4_LowerSat_o5mois15qj ) { u0 = rtP .
Saturation4_LowerSat_o5mois15qj ; } } u0 = rtP . Constant13_Value_drcxtjpegy
/ u0 ; if ( u0 > rtP . Saturation2_UpperSat_kqxekeh4ne ) { u0 = rtP .
Saturation2_UpperSat_kqxekeh4ne ; } else { if ( u0 < rtP .
Saturation2_LowerSat_cum5140yxb ) { u0 = rtP .
Saturation2_LowerSat_cum5140yxb ; } } rtB . arhywgn0ud [ 1 ] = rtB .
arcts1reys * alqkjudhu3 * muSingleScalarSqrt ( u0 ) * pwkaxiafxx ; rtDW .
l4mofmlly2 = 4 ; break ; case 1 : if ( idx_idx_2 != idx_idx_1 ) { if (
ssGetTaskTime ( rtS , 2 ) != ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset (
rtS ) ; } } if ( pwkaxiafxx > rtP . Saturation4_UpperSat_mvi32mle5a ) {
cesfgrkder_idx_0 = rtP . Saturation4_UpperSat_mvi32mle5a ; } else if (
pwkaxiafxx < rtP . Saturation4_LowerSat_h1tphx4t4v ) { cesfgrkder_idx_0 = rtP
. Saturation4_LowerSat_h1tphx4t4v ; } else { cesfgrkder_idx_0 = pwkaxiafxx ;
} hhjnxjzwip = fzccphw1bz / cesfgrkder_idx_0 ; if ( rtP .
Constant13_Value_drcxtjpegy > rtP . Saturation2_UpperSat_m0obbkx21y ) { tmp_b
= rtP . Saturation2_UpperSat_m0obbkx21y ; } else if ( rtP .
Constant13_Value_drcxtjpegy < rtP . Saturation2_LowerSat_aj21rgvimm ) { tmp_b
= rtP . Saturation2_LowerSat_aj21rgvimm ; } else { tmp_b = rtP .
Constant13_Value_drcxtjpegy ; } u0 = ( ( rtP . Constant13_Value_drcxtjpegy -
rtP . one4_Value_lfqywyfkb1 ) * ( rtP . one3_Value_pho5uxuvjc - hhjnxjzwip )
/ rtP . two_Value_fwe0t422am / tmp_b + hhjnxjzwip ) * ( rtP .
one5_Value_e10f33ajto - hhjnxjzwip ) ; if ( u0 > rtP .
Saturation_UpperSat_bb44f3rn3e ) { u0 = rtP . Saturation_UpperSat_bb44f3rn3e
; } else { if ( u0 < rtP . Saturation_LowerSat_l0ofoykzq5 ) { u0 = rtP .
Saturation_LowerSat_l0ofoykzq5 ; } } rtB . arhywgn0ud [ 1 ] = pwkaxiafxx *
rtB . arcts1reys * alqkjudhu3 * muSingleScalarSqrt ( u0 ) ; u0 = ( ( rtP .
Constant13_Value_drcxtjpegy + rtP . one2_Value ) * fzccphw1bz + ( rtP .
Constant13_Value_drcxtjpegy - rtP . one1_Value_cfbkskxgcs ) * pwkaxiafxx ) *
( rtP . Gain_Gain_pmlstkcmse * rtP . Constant13_Value_drcxtjpegy * (
pwkaxiafxx - fzccphw1bz ) ) ; if ( u0 > rtP . Saturation1_UpperSat_dbmtmwbw0d
) { u0 = rtP . Saturation1_UpperSat_dbmtmwbw0d ; } else { if ( u0 < rtP .
Saturation1_LowerSat_cuwighb455 ) { u0 = rtP .
Saturation1_LowerSat_cuwighb455 ; } } u0 = muSingleScalarSqrt ( u0 ) ; if (
u0 > rtP . Saturation3_UpperSat_eu4nn5aeqt ) { u0 = rtP .
Saturation3_UpperSat_eu4nn5aeqt ; } else { if ( u0 < rtP .
Saturation3_LowerSat_kswln5xcqk ) { u0 = rtP .
Saturation3_LowerSat_kswln5xcqk ; } } rtB . arhywgn0ud [ 0 ] = ( ( rtP .
Constant13_Value_drcxtjpegy - rtP . one_Value_a45lx41rlt ) * pwkaxiafxx +
fzccphw1bz ) / u0 * ( rtB . arcts1reys * alqkjudhu3 ) ; rtDW . kltb44md1r = 4
; break ; } hhjnxjzwip = o2wgigs4ap_idx_0 - rtB . arhywgn0ud [ 1 ] ; rtB .
g0gsnsbc3h = rtP . man_use_LM_Gain * rtDW . nqvcv4lcej ; rtB . gzcrpdyase =
rtP . man_pex_eps1_Gain * rtDW . ayjpjfupkc ; if ( rtB . g0gsnsbc3h > rtP .
zero8_Value ) { u0 = rtB . arhywgn0ud [ 0 ] * rtB . arhywgn0ud [ 0 ] + rtB .
ilgb03fx1o ; if ( u0 > rtP . Saturation3_UpperSat_fyjrms34ap ) { u0 = rtP .
Saturation3_UpperSat_fyjrms34ap ; } else { if ( u0 < rtP .
Saturation3_LowerSat_enydkrbip1 ) { u0 = rtP .
Saturation3_LowerSat_enydkrbip1 ; } } hhjnxjzwip *= 1.0F / u0 * rtB .
arhywgn0ud [ 0 ] ; } else { u0 = rtB . gzcrpdyase + rtB . arhywgn0ud [ 0 ] ;
if ( u0 > rtP . Saturation1_UpperSat_h1az5n4to4 ) { u0 = rtP .
Saturation1_UpperSat_h1az5n4to4 ; } else { if ( u0 < rtP .
Saturation1_LowerSat_cgvkg1cu0s ) { u0 = rtP .
Saturation1_LowerSat_cgvkg1cu0s ; } } hhjnxjzwip *= 1.0F / u0 ; } alqkjudhu3
= ( pwkaxiafxx + hhjnxjzwip ) * rtP . Gain2_Gain_inrigkvibz ; idx_idx_1 =
rtDW . g0pejldppu ; idx_idx_2 = ( int8_T ) ! ( es40kk5dcp < 15.0F ) ; rtDW .
g0pejldppu = idx_idx_2 ; if ( idx_idx_1 != idx_idx_2 ) { switch ( idx_idx_1 )
{ case 0 : ssSetSolverNeedsReset ( rtS ) ; break ; case 1 :
ssSetSolverNeedsReset ( rtS ) ; break ; } } switch ( idx_idx_2 ) { case 0 :
if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) != ssGetTStart
( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } hhjnxjzwip = es40kk5dcp / rtP
. fifteen_Value ; rtB . eznht2b1xz = ( rtP . one_Value_januwcu5ef -
hhjnxjzwip ) * batdnpsvim + alqkjudhu3 * hhjnxjzwip ; rtDW . oqqlpwtggt = 4 ;
break ; case 1 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2
) != ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB .
eznht2b1xz = alqkjudhu3 ; rtDW . hgwa21u3tp = 4 ; break ; } hhjnxjzwip = rtP
. unity2_Value + g1ekzbu3oi ; if ( rtB . eznht2b1xz < hhjnxjzwip ) {
ikxbbcq2jl = hhjnxjzwip ; } else { ikxbbcq2jl = rtB . eznht2b1xz ; } if ( rtB
. eznht2b1xz > rtP . pexmax1_Value ) { rtB . a5xydgx2md = rtP . pexmax1_Value
; } else { rtB . a5xydgx2md = ikxbbcq2jl ; } srUpdateBC ( rtDW . ljedkvx4od )
; meppapiqj0 = rtP . y_cons4_Value ; s60_iter ++ ; } rtB . cdx14uwqgo = rtP .
man_use_PexHat_Gain * rtDW . pmewcnpxdb ; if ( rtB . cdx14uwqgo > rtP .
zero6_Value ) { rtB . e3xygmo5lb = rtB . a5xydgx2md ; } else { rtB .
e3xygmo5lb = batdnpsvim ; } p03esja3h2 = rtP . Gain4_Gain_dbouzguspb * rtB .
e3xygmo5lb ; if ( lqaourhjqh > rtP . Saturation4_UpperSat_epdhn4s0cl ) {
cesfgrkder_idx_0 = rtP . Saturation4_UpperSat_epdhn4s0cl ; } else if (
lqaourhjqh < rtP . Saturation4_LowerSat_av41cx1fh3 ) { cesfgrkder_idx_0 = rtP
. Saturation4_LowerSat_av41cx1fh3 ; } else { cesfgrkder_idx_0 = lqaourhjqh ;
} o3mfdsmmfb = p03esja3h2 / cesfgrkder_idx_0 / rtP . Ra_Value_cq5xpakoe0 *
p03esja3h2 ; if ( p03esja3h2 > rtP . Saturation3_UpperSat_hvmdvvrxvg ) {
p03esja3h2 = rtP . Saturation3_UpperSat_hvmdvvrxvg ; } else { if ( p03esja3h2
< rtP . Saturation3_LowerSat_cbroun1d3t ) { p03esja3h2 = rtP .
Saturation3_LowerSat_cbroun1d3t ; } } hhjnxjzwip = rtP .
Gain2_Gain_jqgsltqvvo * rtB . j0uztscc4c / p03esja3h2 ; if ( hhjnxjzwip > rtP
. Constant5_Value_oine35ovff ) { if ( hhjnxjzwip > rtP .
Saturation1_UpperSat_ojvkrkpnti ) { hhjnxjzwip = rtP .
Saturation1_UpperSat_ojvkrkpnti ; } else { if ( hhjnxjzwip < rtP .
Saturation1_LowerSat_kz22ykzlmo ) { hhjnxjzwip = rtP .
Saturation1_LowerSat_kz22ykzlmo ; } } alqkjudhu3 = rtP .
Constant3_Value_opcmg5klwq - hhjnxjzwip ; alqkjudhu3 *= alqkjudhu3 * rtP .
Constant2_Value_iglpak03on + hhjnxjzwip ; if ( alqkjudhu3 > rtP .
Saturation2_UpperSat ) { alqkjudhu3 = rtP . Saturation2_UpperSat ; } else {
if ( alqkjudhu3 < rtP . Saturation2_LowerSat ) { alqkjudhu3 = rtP .
Saturation2_LowerSat ; } } p03esja3h2 = muSingleScalarSqrt ( alqkjudhu3 ) ; }
else { p03esja3h2 = rtP . Constant4_Value_fcj2xxbxnn ; } rtB . ghtnph5m13 =
rtP . man_egrr_cons_Gain * rtDW . hptuorf3i3 ; es40kk5dcp = rtP .
c_100inv_Gain * rtB . ghtnph5m13 ; if ( es40kk5dcp > rtP .
Saturation1_UpperSat_b2bgfkqzvd ) { es40kk5dcp = rtP .
Saturation1_UpperSat_b2bgfkqzvd ; } else { if ( es40kk5dcp < rtP .
Saturation1_LowerSat_pdrhlonent ) { es40kk5dcp = rtP .
Saturation1_LowerSat_pdrhlonent ; } } u0 = muSingleScalarSqrt (
muSingleScalarAbs ( rtP . Gain2_Gain_f5pp4pdbvl * o3mfdsmmfb ) ) *
rt_Lookup32 ( rtP . LookupTable_XData , 16 , rtB . ljk4xix01m , rtP .
LookupTable_YData ) * p03esja3h2 * rtP . tokgps1_Gain_niett2ztcu ; if ( u0 >
rtP . Saturation_UpperSat_heyubqqqyr ) { u0 = rtP .
Saturation_UpperSat_heyubqqqyr ; } else { if ( u0 < rtP .
Saturation_LowerSat_libsvlbteb ) { u0 = rtP . Saturation_LowerSat_libsvlbteb
; } } duexjpu5rm_p = muSingleScalarMin ( u0 , rtB . evxrp31n1t * es40kk5dcp /
( rtP . rate_max1_Value - es40kk5dcp ) * rtP . n4_Gain ) ; rtB . nkcobpyvlo =
rtP . n6_Gain * duexjpu5rm_p * rtP . mon_flowmax_Gain ; rtDW . bvlm5joqvj =
rtB . nkcobpyvlo ; Look2D_real32_T_real32_T_real32_T ( & ( pecb1uxa5c ) , rtP
. epimbs_map_Table , rtB . ljk4xix01m , rtP . epimbs_map_RowIdx , 19U , rtB .
itsvvwrq0a , rtP . epimbs_map_ColIdx , 19U ) ; rtB . gyr32rwmec = rtP .
man_pinrefadd_Gain * rtDW . enudnf03vn ; g1ekzbu3oi = pecb1uxa5c + rtB .
gyr32rwmec ; rtB . oknjoatyhh = rtB . kzspe3uhcs [ 1 ] - g1ekzbu3oi ;
Look2D_real32_T_real32_T_real32_T ( & ( nokdpzhel0 ) , rtP .
epimbs_map_Table_ievkkvfepo , rtB . ljk4xix01m , rtP .
epimbs_map_RowIdx_hricelzw4c , 19U , rtB . itsvvwrq0a , rtP .
epimbs_map_ColIdx_aw5dr10asn , 19U ) ; rtB . fnbokrjfka = rtP .
man_egrrefadd_Gain * rtDW . bakpq4fzl0 ; fwhtla1rft = rtP .
Gain2_Gain_bqzhmg4lx1 * nokdpzhel0 + rtB . fnbokrjfka ; if ( fwhtla1rft > rtP
. Saturation1_UpperSat_omybqinkw3 ) { fwhtla1rft = rtP .
Saturation1_UpperSat_omybqinkw3 ; } else { if ( fwhtla1rft < rtP .
Saturation1_LowerSat_mdkjykh3qf ) { fwhtla1rft = rtP .
Saturation1_LowerSat_mdkjykh3qf ; } } rtB . hwqwznwhbl = rtB . kzspe3uhcs [ 2
] - fwhtla1rft ; p03esja3h2 = rtB . evxrp31n1t / rtP . thousand_Value ;
fzccphw1bz = rtP . Gain_Gain_nqiwfihzfk * rtB . j0uztscc4c ; if ( rtP .
filt_Value > rtP . Saturation1_UpperSat_myjsita4wq ) { tmp_b = rtP .
Saturation1_UpperSat_myjsita4wq ; } else if ( rtP . filt_Value < rtP .
Saturation1_LowerSat_e3kdxawffw ) { tmp_b = rtP .
Saturation1_LowerSat_e3kdxawffw ; } else { tmp_b = rtP . filt_Value ; } if (
rtP . filt1_Value > rtP . Saturation4_UpperSat_iuohbhcftj ) {
cesfgrkder_idx_0 = rtP . Saturation4_UpperSat_iuohbhcftj ; } else if ( rtP .
filt1_Value < rtP . Saturation4_LowerSat_fp4jygx5yy ) { cesfgrkder_idx_0 =
rtP . Saturation4_LowerSat_fp4jygx5yy ; } else { cesfgrkder_idx_0 = rtP .
filt1_Value ; } rtB . lvfxs442og = ( rtP . one_Value_h01zho5suw -
cesfgrkder_idx_0 ) * p03esja3h2 + rtDW . frjwyakiph * tmp_b ; hhjnxjzwip =
rtP . tokgps2_Gain * rtB . lvfxs442og ; rtB . eem54jmxca = rtP .
man_use_throttleffmap_Gain * rtDW . d210tl5n23 ; rtB . c0a55ctkeh = rtP .
man_throttle_ff_Gain * rtDW . nwf1nud1fv ; if ( rtB . eem54jmxca > rtP .
zero5_Value ) { Look2D_real32_T_real32_T_real32_T ( & ( dsl1ro0v01 ) , rtP .
thr_ff_map_Table , rtB . ljk4xix01m , rtP . thr_ff_map_RowIdx , 19U , rtB .
itsvvwrq0a , rtP . thr_ff_map_ColIdx , 19U ) ; not4fp11wk = dsl1ro0v01 ; }
else { not4fp11wk = rtB . c0a55ctkeh ; } alqkjudhu3 = rtP .
Gain_Gain_jgqj4bq1it * not4fp11wk ; o3mfdsmmfb = rtP . Gain1_Gain_huollvbetb
* rtB . ljk4xix01m ; ssSetSolverNeedsReset ( rtS ) ; rtDW . owlkbndpg5 = rtP
. UnitDelay_InitialCondition_j4qityl4pb ; for ( s60_iter = 1 ; s60_iter <=
rtP . ForIterator_IterationLimit_dfiupsd0in ; s60_iter ++ ) { if ( s60_iter >
rtP . Saturation1_UpperSat_oxxrzmuthi ) { i = rtP .
Saturation1_UpperSat_oxxrzmuthi ; } else if ( s60_iter < rtP .
Saturation1_LowerSat_g2klx1snpo ) { i = rtP . Saturation1_LowerSat_g2klx1snpo
; } else { i = s60_iter ; } ffd3q0dmho = i - 1 ; cesfgrkder_idx_1 =
alqkjudhu3 - rtP . svrthrottle1_Value [ ffd3q0dmho ] ; c2fdcpgrsp =
cesfgrkder_idx_1 * cesfgrkder_idx_1 ; cesfgrkder_idx_1 = o3mfdsmmfb - rtP .
svrthrottle2_Value [ ffd3q0dmho ] ; oddbt41ver = ( ( 0.0F - c2fdcpgrsp ) -
cesfgrkder_idx_1 * cesfgrkder_idx_1 ) / ( rtP . svrthrottlearg_Value * rtP .
svrthrottlearg_Value * rtP . Gain_Gain_nty4sel1wt ) ;
LookUp_real32_T_real32_T ( & ( cswau4wwoj ) , rtP .
expLookupTable_YData_o1u0ravagw , oddbt41ver , rtP .
expLookupTable_XData_jvstrz5tjz , 102U ) ; rtB . o3l2mqkjgp = cswau4wwoj *
rtP . svrthrottleargbeta_Value [ ffd3q0dmho ] + rtDW . owlkbndpg5 ; rtDW .
owlkbndpg5 = rtB . o3l2mqkjgp ; } if ( rtP . tic_Value > rtP .
Saturation5_UpperSat_lsmaqufwep ) { tmp_b = rtP .
Saturation5_UpperSat_lsmaqufwep ; } else if ( rtP . tic_Value < rtP .
Saturation5_LowerSat_inbxi0ty31 ) { tmp_b = rtP .
Saturation5_LowerSat_inbxi0ty31 ; } else { tmp_b = rtP . tic_Value ; } if (
rtP . Ra_Value_lzmtkyahjs > rtP . Saturation1_UpperSat_otpxulmvuy ) {
cesfgrkder_idx_0 = rtP . Saturation1_UpperSat_otpxulmvuy ; } else if ( rtP .
Ra_Value_lzmtkyahjs < rtP . Saturation1_LowerSat_ppefjc3clp ) {
cesfgrkder_idx_0 = rtP . Saturation1_LowerSat_ppefjc3clp ; } else {
cesfgrkder_idx_0 = rtP . Ra_Value_lzmtkyahjs ; } u0 = rtP .
one_Value_j5dpbec4pp / tmp_b / cesfgrkder_idx_0 * rtP . Gain2_Gain_oeyqknfg3u
; if ( u0 > rtP . Saturation_UpperSat_aeqkn4yat2 ) { u0 = rtP .
Saturation_UpperSat_aeqkn4yat2 ; } else { if ( u0 < rtP .
Saturation_LowerSat_eqca1cxjhu ) { u0 = rtP . Saturation_LowerSat_eqca1cxjhu
; } } u0 = muSingleScalarSqrt ( u0 ) ; if ( rtB . o3l2mqkjgp > rtP .
Saturation2_UpperSat_ar3amrrdo0 ) { tmp_b = rtP .
Saturation2_UpperSat_ar3amrrdo0 ; } else if ( rtB . o3l2mqkjgp < rtP .
Saturation2_LowerSat_gcjzh4zwtf ) { tmp_b = rtP .
Saturation2_LowerSat_gcjzh4zwtf ; } else { tmp_b = rtB . o3l2mqkjgp ; } if (
u0 > rtP . Saturation3_UpperSat_e5wb1y1qfm ) { u0 = rtP .
Saturation3_UpperSat_e5wb1y1qfm ; } else { if ( u0 < rtP .
Saturation3_LowerSat_o44sgnqx2m ) { u0 = rtP .
Saturation3_LowerSat_o44sgnqx2m ; } } es40kk5dcp = hhjnxjzwip / tmp_b / u0 ;
hhjnxjzwip = es40kk5dcp * es40kk5dcp ; if ( es40kk5dcp > rtP .
Saturation1_UpperSat_pqesfzc0le ) { es40kk5dcp = rtP .
Saturation1_UpperSat_pqesfzc0le ; } else { if ( es40kk5dcp < rtP .
Saturation1_LowerSat_javhnqsmey ) { es40kk5dcp = rtP .
Saturation1_LowerSat_javhnqsmey ; } } if ( fzccphw1bz / es40kk5dcp > rtP .
c_1d2p4_Value ) { alqkjudhu3 = fzccphw1bz * fzccphw1bz ; hhjnxjzwip = ( ( rtP
. c_km1d2k1_Gain * alqkjudhu3 - alqkjudhu3 ) - hhjnxjzwip ) * rtP .
four_Value * rtP . c_km1d2k_Value ; alqkjudhu3 = fzccphw1bz - rtP .
c_p4d1p4_Gain * fzccphw1bz ; u0 = alqkjudhu3 * alqkjudhu3 - hhjnxjzwip ; if (
u0 > rtP . Saturation_UpperSat_dfiskt0evr ) { u0 = rtP .
Saturation_UpperSat_dfiskt0evr ; } else { if ( u0 < rtP .
Saturation_LowerSat_kkda3f5nhs ) { u0 = rtP . Saturation_LowerSat_kkda3f5nhs
; } } if ( rtP . c_km1d2k_Value > rtP . Saturation7_UpperSat ) { tmp_b = rtP
. Saturation7_UpperSat ; } else if ( rtP . c_km1d2k_Value < rtP .
Saturation7_LowerSat ) { tmp_b = rtP . Saturation7_LowerSat ; } else { tmp_b
= rtP . c_km1d2k_Value ; } if ( rtP . two_Value_ggoksfpb1h > rtP .
Saturation4_UpperSat_fg5ix0ri20 ) { cesfgrkder_idx_0 = rtP .
Saturation4_UpperSat_fg5ix0ri20 ; } else if ( rtP . two_Value_ggoksfpb1h <
rtP . Saturation4_LowerSat_g5gg4j1znz ) { cesfgrkder_idx_0 = rtP .
Saturation4_LowerSat_g5gg4j1znz ; } else { cesfgrkder_idx_0 = rtP .
two_Value_ggoksfpb1h ; } es40kk5dcp = ( muSingleScalarSqrt ( u0 ) -
alqkjudhu3 ) / tmp_b / cesfgrkder_idx_0 ; } else { es40kk5dcp = hhjnxjzwip ;
} es40kk5dcp *= rtP . Gain2_Gain_hgyagoi5x4 ; p03esja3h2 =
rt_Lookup2D32_Normal ( rtP . Lookup_Table_2D_RowIdx , 20 , rtP .
Lookup_Table_2D_ColIdx , 16 , rtP . Lookup_Table_2D_Table , p03esja3h2 , 1.0F
/ rtP . pincomp_Value * es40kk5dcp ) * rtP . conversiontoradpers_Gain ; rtB .
gj05xuhqyp = rtP . Gain1_Gain_p0b0owyvrq * p03esja3h2 ; rtB . fnoycnzxjt =
rtP . man_gsvgt_Gain * rtDW . ntmupcyyck ; if ( rtB . fnoycnzxjt > rtP .
Saturation3_UpperSat_gfw1stpglz ) { pwkaxiafxx = rtP .
Saturation3_UpperSat_gfw1stpglz ; } else if ( rtB . fnoycnzxjt < rtP .
Saturation3_LowerSat_j1w5p5qkgi ) { pwkaxiafxx = rtP .
Saturation3_LowerSat_j1w5p5qkgi ; } else { pwkaxiafxx = rtB . fnoycnzxjt ; }
rtB . jtmcug05p1 = ( rtP . vnliftmax_Value - hde10siz3b_idx_0 ) / pwkaxiafxx
; rtB . lmosmreh2j = ( rtP . vnliftmin_Value - hde10siz3b_idx_0 ) * rtP .
n1_Gain_pvuonpooax * ( 1.0F / pwkaxiafxx ) ; rtB . eq5k4gzitz = rtP .
man_gswegr_Gain * rtDW . devn1wdclr ; if ( rtB . eq5k4gzitz > rtP .
Saturation2_UpperSat_pd4jn2febf ) { fzccphw1bz = rtP .
Saturation2_UpperSat_pd4jn2febf ; } else if ( rtB . eq5k4gzitz < rtP .
Saturation2_LowerSat_na315pjcdo ) { fzccphw1bz = rtP .
Saturation2_LowerSat_na315pjcdo ; } else { fzccphw1bz = rtB . eq5k4gzitz ; }
rtB . f1zcecdgrp = ( rtP . n3_Gain_ddgktxpofx * duexjpu5rm_p -
hde10siz3b_idx_1 ) / fzccphw1bz ; rtB . pik2cpjozq = ( rtP . flowmin_Value -
hde10siz3b_idx_1 ) * rtP . n2_Gain_higq23ggss * ( 1.0F / fzccphw1bz ) ; rtB .
nslfibkrov = rtP . man_map_cons_Gain * rtDW . o3z1jsmhkx ; rtB . l4ddhp1s2y =
rtB . nslfibkrov - g1ekzbu3oi ; rtB . m3gtxwsewc = rtP . y_cons5_Value -
fwhtla1rft ; rtB . gyejnsfev5 = rtP . man_pex_cons_Gain * rtDW . mi05525rde ;
rtB . eacys0hvzp = rtP . man_ntcons_Gain * rtDW . fuwbxjmtyy ; rtB .
fokzlm1wwg = rtP . Gain3_Gain_m5i2an5c5h * rtB . eacys0hvzp ; s60_iter = 1 ;
meppapiqj0 = ( rtP . region_ic_Value != 0 ) ; while ( meppapiqj0 && (
s60_iter <= 103 ) ) { ikgncxkezn = s60_iter ; if ( ikgncxkezn > rtP .
Saturation5_UpperSat_ekawuruosz ) { i = rtP . Saturation5_UpperSat_ekawuruosz
; } else if ( ikgncxkezn < rtP . Saturation5_LowerSat_ihri13muhp ) { i = rtP
. Saturation5_LowerSat_ihri13muhp ; } else { i = ikgncxkezn ; } if ( rtP .
ibigHstart_Value [ i - 1 ] > rtP . Saturation1_UpperSat_jyclkdtald ) {
hhjnxjzwip = rtP . Saturation1_UpperSat_jyclkdtald ; } else if ( rtP .
ibigHstart_Value [ i - 1 ] < rtP . Saturation1_LowerSat_nhdjll5e0q ) {
hhjnxjzwip = rtP . Saturation1_LowerSat_nhdjll5e0q ; } else { hhjnxjzwip =
rtP . ibigHstart_Value [ i - 1 ] ; } ffd3q0dmho = ( int32_T ) hhjnxjzwip ;
izertgsvfr = ( int32_T ) hhjnxjzwip ; izertgsvfr_p = ( int32_T ) hhjnxjzwip ;
izertgsvfr_e = ( int32_T ) hhjnxjzwip ; izertgsvfr_i = ( int32_T ) hhjnxjzwip
; izertgsvfr_m = ( int32_T ) hhjnxjzwip ; izertgsvfr_g = ( int32_T )
hhjnxjzwip ; izertgsvfr_j = ( int32_T ) hhjnxjzwip ; izertgsvfr_f = ( int32_T
) hhjnxjzwip ; izertgsvfr_c = ( int32_T ) hhjnxjzwip ; izertgsvfr_k = (
int32_T ) hhjnxjzwip ; izertgsvfr_b = ( int32_T ) hhjnxjzwip ; izertgsvfr_n =
( int32_T ) hhjnxjzwip ; cjggagnffi = ( int32_T ) hhjnxjzwip ; for ( i = 0 ;
i < 10 ; i ++ ) { e2oeg530ux [ i ] = ( ( ( ( ( ( ( ( ( ( ( ( rtP .
bigH1_Value [ ( i + ffd3q0dmho ) - 1 ] * rtB . kzspe3uhcs [ 0 ] + rtP .
bigH2_Value [ ( i + izertgsvfr ) - 1 ] * rtB . oknjoatyhh ) + rtP .
bigH3_Value [ ( i + izertgsvfr_p ) - 1 ] * rtB . hwqwznwhbl ) + rtP .
bigH4_Value [ ( i + izertgsvfr_e ) - 1 ] * rtB . e3xygmo5lb ) + rtP .
bigH5_Value [ ( i + izertgsvfr_i ) - 1 ] * rtB . gj05xuhqyp ) + rtP .
bigH6_Value [ ( i + izertgsvfr_m ) - 1 ] * rtB . jtmcug05p1 ) + rtP .
bigH7_Value [ ( i + izertgsvfr_g ) - 1 ] * rtB . lmosmreh2j ) + rtP .
bigH8_Value [ ( i + izertgsvfr_j ) - 1 ] * rtB . f1zcecdgrp ) + rtP .
bigH9_Value [ ( i + izertgsvfr_f ) - 1 ] * rtB . pik2cpjozq ) + rtP .
bigH10_Value [ ( i + izertgsvfr_c ) - 1 ] * rtB . l4ddhp1s2y ) + rtP .
bigH11_Value [ ( i + izertgsvfr_k ) - 1 ] * rtB . m3gtxwsewc ) + rtP .
bigH12_Value [ ( i + izertgsvfr_b ) - 1 ] * rtB . gyejnsfev5 ) + rtP .
bigH13_Value [ ( i + izertgsvfr_n ) - 1 ] * rtB . fokzlm1wwg ) - rtP .
bigK_Value [ ( i + cjggagnffi ) - 1 ] ; } hhjnxjzwip = e2oeg530ux [ 0 ] ; for
( ffd3q0dmho = 0 ; ffd3q0dmho < 9 ; ffd3q0dmho ++ ) { hhjnxjzwip =
muSingleScalarMax ( hhjnxjzwip , e2oeg530ux [ ffd3q0dmho + 1 ] ) ; }
pjzpplkm5e = hhjnxjzwip ; njl1440oaw = rtDW . gme5mt5rhg ; abpgkxy4n5 = rtDW
. n4b14msae2 ; idx_idx_1 = rtDW . kqdf0adzeb ; if ( ikgncxkezn == 1 ) {
idx_idx_2 = 0 ; } else { idx_idx_2 = 1 ; } rtDW . kqdf0adzeb = idx_idx_2 ; if
( ( idx_idx_1 != idx_idx_2 ) && ( idx_idx_1 == 1 ) ) { switch ( rtDW .
dqd4zebieo ) { case 0 : hldppkqdr4 ( rtS ) ; break ; case 1 : hldppkqdr4 (
rtS ) ; break ; } rtDW . dqd4zebieo = - 1 ; } switch ( idx_idx_2 ) { case 0 :
if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) != ssGetTStart
( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dmnianvpym = pjzpplkm5e
; rtB . dgqpk3ff5k = rtP . region_1_Value ; rtDW . gdpkwnqxlj = 4 ; break ;
case 1 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } idx_idx_1 = rtDW
. dqd4zebieo ; idx_idx_2 = ( int8_T ) ! ( pjzpplkm5e < njl1440oaw ) ; rtDW .
dqd4zebieo = idx_idx_2 ; if ( idx_idx_1 != idx_idx_2 ) { switch ( idx_idx_1 )
{ case 0 : hldppkqdr4 ( rtS ) ; break ; case 1 : hldppkqdr4 ( rtS ) ; break ;
} } switch ( idx_idx_2 ) { case 0 : if ( idx_idx_2 != idx_idx_1 ) {
nbrxxgteth ( rtS ) ; } pg1kwe2jso ( pjzpplkm5e , ikgncxkezn , & rtB .
dmnianvpym , & rtB . dgqpk3ff5k ) ; rtDW . pg1kwe2jsoh . ld1fjkwy01 = 4 ;
break ; case 1 : if ( idx_idx_2 != idx_idx_1 ) { nbrxxgteth ( rtS ) ; }
pg1kwe2jso ( njl1440oaw , abpgkxy4n5 , & rtB . dmnianvpym , & rtB .
dgqpk3ff5k ) ; rtDW . gmyvhhtxia . ld1fjkwy01 = 4 ; break ; } rtDW .
ozyefxkqtm = 4 ; break ; } meppapiqj0 = ( rtB . dmnianvpym > rtP .
Constant_Value_akx2zsubmt ) ; rtDW . gme5mt5rhg = rtB . dmnianvpym ; rtDW .
n4b14msae2 = rtB . dgqpk3ff5k ; srUpdateBC ( rtDW . hfnjefvf2v ) ; s60_iter
++ ; } if ( rtB . dgqpk3ff5k > rtP . Saturation5_UpperSat_l4y5uubttw ) { i =
rtP . Saturation5_UpperSat_l4y5uubttw ; } else if ( rtB . dgqpk3ff5k < rtP .
Saturation5_LowerSat_muc4d0y3pl ) { i = rtP . Saturation5_LowerSat_muc4d0y3pl
; } else { i = rtB . dgqpk3ff5k ; } if ( rtP . ibigFstart_Value [ i - 1 ] >
rtP . Saturation1_UpperSat_haurxgbsmv ) { o3mfdsmmfb = rtP .
Saturation1_UpperSat_haurxgbsmv ; } else if ( rtP . ibigFstart_Value [ i - 1
] < rtP . Saturation1_LowerSat_ky0lpt3bhz ) { o3mfdsmmfb = rtP .
Saturation1_LowerSat_ky0lpt3bhz ; } else { o3mfdsmmfb = rtP .
ibigFstart_Value [ i - 1 ] ; } i = ( int32_T ) o3mfdsmmfb ; ffd3q0dmho = (
int32_T ) o3mfdsmmfb ; izertgsvfr = ( int32_T ) o3mfdsmmfb ; izertgsvfr_p = (
int32_T ) o3mfdsmmfb ; izertgsvfr_e = ( int32_T ) o3mfdsmmfb ; izertgsvfr_i =
( int32_T ) o3mfdsmmfb ; izertgsvfr_m = ( int32_T ) o3mfdsmmfb ; izertgsvfr_g
= ( int32_T ) o3mfdsmmfb ; izertgsvfr_j = ( int32_T ) o3mfdsmmfb ;
izertgsvfr_f = ( int32_T ) o3mfdsmmfb ; izertgsvfr_c = ( int32_T ) o3mfdsmmfb
; izertgsvfr_k = ( int32_T ) o3mfdsmmfb ; izertgsvfr_b = ( int32_T )
o3mfdsmmfb ; izertgsvfr_n = ( int32_T ) o3mfdsmmfb ; rtB . eu3n5piaim [ 0 ] =
( ( ( ( ( ( ( ( ( ( ( ( rtP . bigF1_Value [ i - 1 ] * rtB . kzspe3uhcs [ 0 ]
+ rtP . bigF2_Value [ ffd3q0dmho - 1 ] * rtB . oknjoatyhh ) + rtP .
bigF3_Value [ izertgsvfr - 1 ] * rtB . hwqwznwhbl ) + rtP . bigF4_Value [
izertgsvfr_p - 1 ] * rtB . e3xygmo5lb ) + rtP . bigF5_Value [ izertgsvfr_e -
1 ] * rtB . gj05xuhqyp ) + rtP . bigF6_Value [ izertgsvfr_i - 1 ] * rtB .
jtmcug05p1 ) + rtP . bigF7_Value [ izertgsvfr_m - 1 ] * rtB . lmosmreh2j ) +
rtP . bigF8_Value [ izertgsvfr_g - 1 ] * rtB . f1zcecdgrp ) + rtP .
bigF9_Value [ izertgsvfr_j - 1 ] * rtB . pik2cpjozq ) + rtP . bigF10_Value [
izertgsvfr_f - 1 ] * rtB . l4ddhp1s2y ) + rtP . bigF11_Value [ izertgsvfr_c -
1 ] * rtB . m3gtxwsewc ) + rtP . bigF12_Value [ izertgsvfr_k - 1 ] * rtB .
gyejnsfev5 ) + rtP . bigF13_Value [ izertgsvfr_b - 1 ] * rtB . fokzlm1wwg ) +
rtP . bigG_Value [ izertgsvfr_n - 1 ] ; rtB . eu3n5piaim [ 1 ] = ( ( ( ( ( (
( ( ( ( ( ( rtP . bigF1_Value [ i ] * rtB . kzspe3uhcs [ 0 ] + rtP .
bigF2_Value [ ffd3q0dmho ] * rtB . oknjoatyhh ) + rtP . bigF3_Value [
izertgsvfr ] * rtB . hwqwznwhbl ) + rtP . bigF4_Value [ izertgsvfr_p ] * rtB
. e3xygmo5lb ) + rtP . bigF5_Value [ izertgsvfr_e ] * rtB . gj05xuhqyp ) +
rtP . bigF6_Value [ izertgsvfr_i ] * rtB . jtmcug05p1 ) + rtP . bigF7_Value [
izertgsvfr_m ] * rtB . lmosmreh2j ) + rtP . bigF8_Value [ izertgsvfr_g ] *
rtB . f1zcecdgrp ) + rtP . bigF9_Value [ izertgsvfr_j ] * rtB . pik2cpjozq )
+ rtP . bigF10_Value [ izertgsvfr_f ] * rtB . l4ddhp1s2y ) + rtP .
bigF11_Value [ izertgsvfr_c ] * rtB . m3gtxwsewc ) + rtP . bigF12_Value [
izertgsvfr_k ] * rtB . gyejnsfev5 ) + rtP . bigF13_Value [ izertgsvfr_b ] *
rtB . fokzlm1wwg ) + rtP . bigG_Value [ izertgsvfr_n ] ; rtB . eu3n5piaim [ 2
] = ( ( ( ( ( ( ( ( ( ( ( ( rtP . bigF1_Value [ i + 1 ] * rtB . kzspe3uhcs [
0 ] + rtP . bigF2_Value [ ffd3q0dmho + 1 ] * rtB . oknjoatyhh ) + rtP .
bigF3_Value [ izertgsvfr + 1 ] * rtB . hwqwznwhbl ) + rtP . bigF4_Value [
izertgsvfr_p + 1 ] * rtB . e3xygmo5lb ) + rtP . bigF5_Value [ izertgsvfr_e +
1 ] * rtB . gj05xuhqyp ) + rtP . bigF6_Value [ izertgsvfr_i + 1 ] * rtB .
jtmcug05p1 ) + rtP . bigF7_Value [ izertgsvfr_m + 1 ] * rtB . lmosmreh2j ) +
rtP . bigF8_Value [ izertgsvfr_g + 1 ] * rtB . f1zcecdgrp ) + rtP .
bigF9_Value [ izertgsvfr_j + 1 ] * rtB . pik2cpjozq ) + rtP . bigF10_Value [
izertgsvfr_f + 1 ] * rtB . l4ddhp1s2y ) + rtP . bigF11_Value [ izertgsvfr_c +
1 ] * rtB . m3gtxwsewc ) + rtP . bigF12_Value [ izertgsvfr_k + 1 ] * rtB .
gyejnsfev5 ) + rtP . bigF13_Value [ izertgsvfr_b + 1 ] * rtB . fokzlm1wwg ) +
rtP . bigG_Value [ izertgsvfr_n + 1 ] ; rtB . moobo5rhbx = rtP .
mon_delvgt_Gain * rtB . eu3n5piaim [ 0 ] ; rtDW . kk4xei3vwx = rtB .
moobo5rhbx ; rtB . mmuzqgowqh = rtP . mon_delflow_Gain * rtB . eu3n5piaim [ 1
] ; rtDW . mjfdrfawoz = rtB . mmuzqgowqh ; rtB . ludldegbkb = rtP .
mon_slack_Gain * rtB . eu3n5piaim [ 2 ] ; rtDW . oe1xcqtj2h = rtB .
ludldegbkb ; rtB . g1hxajyvoh = ( int32_T ) ( ( int64_T ) rtP .
mon_region_Gain * rtB . dgqpk3ff5k >> 30 ) ; rtDW . fnhncveveb = rtB .
g1hxajyvoh ; rtB . pvsewex5ju = rtP . man_vgtff_Gain * rtDW . axunmck3pg ;
o3mfdsmmfb = rtP . n5_Gain * duexjpu5rm_p ; rtB . gcx1li42yu = rtP .
man_wegrff_Gain * rtDW . gzmuaempqp ; kbpr1j4sdg = rtP . Gain9_Gain * rtB .
gcx1li42yu ; if ( kbpr1j4sdg < rtP . zero_Value ) { nyhah3yrmr = rtP .
zero_Value ; } else { nyhah3yrmr = kbpr1j4sdg ; } if ( kbpr1j4sdg >
o3mfdsmmfb ) { d45xcqw5zg = o3mfdsmmfb ; } else { d45xcqw5zg = nyhah3yrmr ; }
rtB . bggc12g3ce = rtP . man_ctrl_Gain * rtDW . gd2xytkseo ; rtB . lqzoneosua
= pwkaxiafxx * rtB . eu3n5piaim [ 0 ] ; rtB . gy1swsl5lp = rtB . eu3n5piaim [
1 ] * fzccphw1bz ; if ( rtB . bggc12g3ce > rtP . zero1_Value_jogrhh3e5m ) {
rtB . dwx51vir01 [ 0 ] = rtB . pvsewex5ju ; rtB . dwx51vir01 [ 1 ] =
d45xcqw5zg ; } else { rtB . dwx51vir01 [ 0 ] = hde10siz3b_idx_0 + rtB .
lqzoneosua ; rtB . dwx51vir01 [ 1 ] = hde10siz3b_idx_1 + rtB . gy1swsl5lp ; }
rtB . luidd34yzh = rtP . mon_vgt_Gain * rtB . dwx51vir01 [ 0 ] ; rtDW .
i5n35h2hi0 = rtB . luidd34yzh ; c2fdcpgrsp = rtP . Gain_Gain_izbq1vn3ay * rtB
. dwx51vir01 [ 1 ] ; rtB . g1n35fyh1r = rtP . n7_Gain * c2fdcpgrsp * rtP .
mon_uwegr_Gain ; rtDW . gj1id4inx4 = rtB . g1n35fyh1r ; rtB . novvn2g13i =
rtP . mon_wf_Gain * rtB . itsvvwrq0a ; rtDW . psebtvzqlm = rtB . novvn2g13i ;
rtB . gl0e32zavt = rtP . man_valveff_Gain * rtDW . eppk3q2xfh ; rtB .
f25tnd03zw = rtP . man_use_valveff_Gain * rtDW . fgc3q11l1t ; meppapiqj0 = (
rtB . f25tnd03zw > rtP . zero4_Value ) ; o3mfdsmmfb = rtP .
Gain_Gain_exnmofkiqk * rtB . e3xygmo5lb ; if ( lqaourhjqh > rtP .
Saturation4_UpperSat_jpf21d0c4s ) { lqaourhjqh = rtP .
Saturation4_UpperSat_jpf21d0c4s ; } else { if ( lqaourhjqh < rtP .
Saturation4_LowerSat_nemejy2x0v ) { lqaourhjqh = rtP .
Saturation4_LowerSat_nemejy2x0v ; } } jwc13tgat3 = o3mfdsmmfb / lqaourhjqh /
rtP . Ra_Value_ml4zxyzp5y * o3mfdsmmfb * rtP . Gain1_Gain_mlwsoiu4wp ;
jwc13tgat3 = muSingleScalarAbs ( jwc13tgat3 ) ; jwc13tgat3 =
muSingleScalarSqrt ( jwc13tgat3 ) ; if ( o3mfdsmmfb > rtP .
Saturation2_UpperSat_eil30qspgi ) { o3mfdsmmfb = rtP .
Saturation2_UpperSat_eil30qspgi ; } else { if ( o3mfdsmmfb < rtP .
Saturation2_LowerSat_pgybggvmgo ) { o3mfdsmmfb = rtP .
Saturation2_LowerSat_pgybggvmgo ; } } hhjnxjzwip = rtP .
Gain1_Gain_nwjp5v2nv4 * rtB . j0uztscc4c / o3mfdsmmfb ; if ( hhjnxjzwip > rtP
. Constant1_Value_m1lei4f355 ) { if ( hhjnxjzwip > rtP .
Saturation1_UpperSat_kb5wgoij0s ) { hhjnxjzwip = rtP .
Saturation1_UpperSat_kb5wgoij0s ; } else { if ( hhjnxjzwip < rtP .
Saturation1_LowerSat_hcztblyabo ) { hhjnxjzwip = rtP .
Saturation1_LowerSat_hcztblyabo ; } } alqkjudhu3 = rtP .
Constant4_Value_j11gk30hoj - hhjnxjzwip ; alqkjudhu3 *= alqkjudhu3 * rtP .
Constant3_Value_py3cg1rapn + hhjnxjzwip ; if ( alqkjudhu3 > rtP .
Saturation3_UpperSat_jgnvlh1trc ) { alqkjudhu3 = rtP .
Saturation3_UpperSat_jgnvlh1trc ; } else { if ( alqkjudhu3 < rtP .
Saturation3_LowerSat_eezjeovjb4 ) { alqkjudhu3 = rtP .
Saturation3_LowerSat_eezjeovjb4 ; } } o3mfdsmmfb = muSingleScalarSqrt (
alqkjudhu3 ) ; } else { o3mfdsmmfb = rtP . Constant5_Value_pvrh0hx004 ; }
jwc13tgat3 *= o3mfdsmmfb ; if ( jwc13tgat3 > rtP .
Saturation4_UpperSat_kyzipinvaz ) { tmp_b = rtP .
Saturation4_UpperSat_kyzipinvaz ; } else if ( jwc13tgat3 < rtP .
Saturation4_LowerSat_b3ugkcddqm ) { tmp_b = rtP .
Saturation4_LowerSat_b3ugkcddqm ; } else { tmp_b = jwc13tgat3 ; } bmms50o0wz
= rtP . togps_Gain * c2fdcpgrsp / tmp_b ; Look2D_real32_T_real32_T_real32_T (
& ( jwc13tgat3 ) , rtP . invert_svr_lut_Table , rtB . ljk4xix01m , rtP .
invert_svr_lut_RowIdx , 15U , bmms50o0wz , rtP . invert_svr_lut_ColIdx , 14U
) ; if ( jwc13tgat3 > rtP . Saturation1_UpperSat_jvb251jt2n ) {
cesfgrkder_idx_1 = rtP . Saturation1_UpperSat_jvb251jt2n ; } else if (
jwc13tgat3 < rtP . Saturation1_LowerSat_iqly2zdexs ) { cesfgrkder_idx_1 = rtP
. Saturation1_LowerSat_iqly2zdexs ; } else { cesfgrkder_idx_1 = jwc13tgat3 ;
} rtB . lhab5ae5gp = rtP . man_wegr_P_Gain * rtDW . a1ts5brulz ; alqkjudhu3 =
rtP . Gain12_Gain * c2fdcpgrsp - o2wgigs4ap_idx_0 ; idx_idx_1 = rtDW .
kl21dgjfyi ; if ( batdnpsvim > rtP . Saturation5_UpperSat_h4urtqtiyp ) {
cesfgrkder_idx_0 = rtP . Saturation5_UpperSat_h4urtqtiyp ; } else if (
batdnpsvim < rtP . Saturation5_LowerSat_aeeskfq3pr ) { cesfgrkder_idx_0 = rtP
. Saturation5_LowerSat_aeeskfq3pr ; } else { cesfgrkder_idx_0 = batdnpsvim ;
} idx_idx_2 = ( int8_T ) ! ( rtB . j0uztscc4c / cesfgrkder_idx_0 <= 0.4167F )
; rtDW . kl21dgjfyi = idx_idx_2 ; if ( idx_idx_1 != idx_idx_2 ) { switch (
idx_idx_1 ) { case 0 : ssSetSolverNeedsReset ( rtS ) ; break ; case 1 :
ssSetSolverNeedsReset ( rtS ) ; break ; } } switch ( idx_idx_2 ) { case 0 :
if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) != ssGetTStart
( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } u0 = ( rtP . one_Value + rtP
. Constant13_Value_nbirv4rghg ) * rtP . Gain6_Gain_eqvrzpdjgj ; if ( u0 > rtP
. Saturation3_UpperSat ) { u0 = rtP . Saturation3_UpperSat ; } else { if ( u0
< rtP . Saturation3_LowerSat ) { u0 = rtP . Saturation3_LowerSat ; } }
eplcvohihr = rtP . Constant13_Value_nbirv4rghg / u0 ; if ( eplcvohihr > rtP .
Saturation1_UpperSat_l0fn5euabx ) { eplcvohihr = rtP .
Saturation1_UpperSat_l0fn5euabx ; } else { if ( eplcvohihr < rtP .
Saturation1_LowerSat_oko05faisu ) { eplcvohihr = rtP .
Saturation1_LowerSat_oko05faisu ; } } srUpdateBC ( rtDW . lb2gtdwzqd ) ;
break ; case 1 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2
) != ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } if (
batdnpsvim > rtP . Saturation4_UpperSat ) { cesfgrkder_idx_0 = rtP .
Saturation4_UpperSat ; } else if ( batdnpsvim < rtP . Saturation4_LowerSat )
{ cesfgrkder_idx_0 = rtP . Saturation4_LowerSat ; } else { cesfgrkder_idx_0 =
batdnpsvim ; } hhjnxjzwip = rtB . j0uztscc4c / cesfgrkder_idx_0 ; if ( rtP .
Constant13_Value_nbirv4rghg > rtP . Saturation2_UpperSat_neszcqhzip ) { tmp_b
= rtP . Saturation2_UpperSat_neszcqhzip ; } else if ( rtP .
Constant13_Value_nbirv4rghg < rtP . Saturation2_LowerSat_ownvik0s0l ) { tmp_b
= rtP . Saturation2_LowerSat_ownvik0s0l ; } else { tmp_b = rtP .
Constant13_Value_nbirv4rghg ; } u0 = ( ( rtP . Constant13_Value_nbirv4rghg -
rtP . one4_Value ) * ( rtP . one3_Value - hhjnxjzwip ) / rtP . two_Value /
tmp_b + hhjnxjzwip ) * ( rtP . one5_Value - hhjnxjzwip ) ; if ( u0 > rtP .
Saturation_UpperSat_phsdj5dg3g ) { u0 = rtP . Saturation_UpperSat_phsdj5dg3g
; } else { if ( u0 < rtP . Saturation_LowerSat_mqpqdfn3am ) { u0 = rtP .
Saturation_LowerSat_mqpqdfn3am ; } } eplcvohihr = muSingleScalarSqrt ( u0 ) ;
srUpdateBC ( rtDW . hpc0grqivr ) ; break ; } rtB . fmwv0d4znx = rtP .
man_use_SG_Gain * rtDW . ok4jtsn4bb ; if ( rtB . fmwv0d4znx > rtP .
zero4_Value_av1gbwxi0k ) { rtB . ntcwr4dn2u = eplcvohihr * alqkjudhu3 ; }
else { rtB . ntcwr4dn2u = alqkjudhu3 ; } rtB . kwlj023pby = rtP .
man_wegr_I_Gain * rtDW . lqempabukg ; alqkjudhu3 = rtDW . i5yn1movmy + rtB .
ntcwr4dn2u ; rtB . n2jcapcy4z = rtP . man_wegr_D_Gain * rtDW . ecauzxzkhl ;
jwc13tgat3 = ( rtB . ntcwr4dn2u - rtDW . diffnla35e ) * rtB . n2jcapcy4z *
rtP . c_100inv_Gain_fusdgx1rvb ; o3mfdsmmfb = ( real32_T ) ( rtP . s_1_Gain *
jwc13tgat3 ) ; rtB . jzzd4u2sum = rtDW . nqyjhyuvcj ; jwc13tgat3 = ( real32_T
) ( rtP . a_2_1_Gain * rtB . jzzd4u2sum ) ; hhjnxjzwip = o3mfdsmmfb -
jwc13tgat3 ; jwc13tgat3 = ( real32_T ) ( rtP . a_3_1_Gain * rtDW . fjcoqtw2bx
) ; rtB . pqqblejffn = hhjnxjzwip - jwc13tgat3 ; rtB . ass1bqlzd1 = rtP .
man_use_PID_Gain * rtDW . moioiyooa5 ; if ( meppapiqj0 ) { rtB . mr2jn5bxm5 =
rtB . gl0e32zavt ; } else if ( rtB . ass1bqlzd1 > rtP . zero7_Value ) { u0 =
( ( rtB . lhab5ae5gp * rtB . ntcwr4dn2u + cesfgrkder_idx_1 ) + rtB .
kwlj023pby * alqkjudhu3 ) + ( ( ( real32_T ) ( rtP . b_2_1_Gain * rtB .
jzzd4u2sum ) + rtB . pqqblejffn ) + rtDW . fjcoqtw2bx ) ; if ( u0 > rtP .
Saturation6_UpperSat ) { rtB . mr2jn5bxm5 = rtP . Saturation6_UpperSat ; }
else if ( u0 < rtP . Saturation6_LowerSat ) { rtB . mr2jn5bxm5 = rtP .
Saturation6_LowerSat ; } else { rtB . mr2jn5bxm5 = u0 ; } } else { rtB .
mr2jn5bxm5 = cesfgrkder_idx_1 ; } rtB . pobddrevcj = rtP . mon_valve_Gain *
rtB . mr2jn5bxm5 ; rtDW . ar2qj33owm = rtB . pobddrevcj ; rtB . nkv11cjkkg =
rtP . mon_pex_hat_Gain * rtB . a5xydgx2md ; rtDW . pwwmab3rlr = rtB .
nkv11cjkkg ; rtB . nskmznxef3 = rtP . mon_wcyl_ecu_Gain * rtB . ksaqwiryhv ;
rtDW . e10toipvv0 = rtB . nskmznxef3 ; rtB . g3lqrwkn4j = rtP .
mon_egrr_est_Gain * orelggziy4 ; rtDW . gmsrqeat5h = rtB . g3lqrwkn4j ; rtB .
lmhrkqqsla = rtP . mon_wegr_est_Gain * rtB . jnglkal4bm ; rtDW . aupt3qrz3y =
rtB . lmhrkqqsla ; rtB . mc4y1a4y4j = rtP . mon_ntest_Gain * p03esja3h2 ;
rtDW . dpjpy2bpgy = rtB . mc4y1a4y4j ; rtB . hf2zl0mcd2 = rtP . mon_ene_Gain
* rtB . ljk4xix01m ; rtDW . pelseog20p = rtB . hf2zl0mcd2 ; rtB . kxt1uasxmv
= rtP . mon_pex_ecu_Gain * batdnpsvim ; rtDW . nhrhyjvls4 = rtB . kxt1uasxmv
; rtB . iw1ygflm02 = rtP . mon_wegr_ecu_Gain * rtB . apexfxt05y ; rtDW .
oobzxswkpo = rtB . iw1ygflm02 ; rtB . kbfvhn1zpd = rtP . mon_tin_Gain * rtB .
m3qm5dlk4i ; rtDW . l0b5hroyaj = rtB . kbfvhn1zpd ; rtB . jdtbjg2wuq = rtP .
mon_maf_ecu_Gain * rtB . evxrp31n1t ; rtDW . ktweu3wugd = rtB . jdtbjg2wuq ;
rtB . iu2eoz2dfq = rtP . mon_map_ref_Gain * g1ekzbu3oi ; rtDW . nlpxiel2sg =
rtB . iu2eoz2dfq ; rtB . nuic2wdm4g = rtP . mon_egrr_ref_Gain * fwhtla1rft ;
rtDW . n5tosor5b5 = rtB . nuic2wdm4g ; rtB . mnaji2ovrg = rtP . mon_pthr_Gain
* es40kk5dcp ; rtDW . nq1n5qxeyp = rtB . mnaji2ovrg ; rtB . ixrjwgdohx = rtP
. man_run2500tp_Gain * rtDW . b5t1avpqna ; meppapiqj0 = ( rtB . ixrjwgdohx >
rtP . zero9_Value ) ; hhjnxjzwip = rtDW . iggiejtmqu ; idx_idx_1 = rtDW .
loepcnnuit ; if ( rtDW . iggiejtmqu < 25.0F ) { idx_idx_2 = 0 ; } else if (
rtDW . iggiejtmqu < 30.0F ) { idx_idx_2 = 1 ; } else if ( rtDW . iggiejtmqu <
35.0F ) { idx_idx_2 = 2 ; } else if ( rtDW . iggiejtmqu < 40.0F ) { idx_idx_2
= 3 ; } else if ( rtDW . iggiejtmqu < 45.0F ) { idx_idx_2 = 4 ; } else if (
rtDW . iggiejtmqu < 50.0F ) { idx_idx_2 = 5 ; } else if ( rtDW . iggiejtmqu <
55.0F ) { idx_idx_2 = 6 ; } else if ( rtDW . iggiejtmqu < 60.0F ) { idx_idx_2
= 7 ; } else if ( rtDW . iggiejtmqu < 65.0F ) { idx_idx_2 = 8 ; } else if (
rtDW . iggiejtmqu < 70.0F ) { idx_idx_2 = 9 ; } else if ( rtDW . iggiejtmqu <
75.0F ) { idx_idx_2 = 10 ; } else if ( rtDW . iggiejtmqu < 80.0F ) {
idx_idx_2 = 11 ; } else if ( rtDW . iggiejtmqu < 85.0F ) { idx_idx_2 = 12 ; }
else if ( rtDW . iggiejtmqu < 90.0F ) { idx_idx_2 = 13 ; } else if ( rtDW .
iggiejtmqu < 95.0F ) { idx_idx_2 = 14 ; } else if ( rtDW . iggiejtmqu <
100.0F ) { idx_idx_2 = 15 ; } else if ( rtDW . iggiejtmqu < 105.0F ) {
idx_idx_2 = 16 ; } else if ( rtDW . iggiejtmqu < 110.0F ) { idx_idx_2 = 17 ;
} else if ( rtDW . iggiejtmqu < 115.0F ) { idx_idx_2 = 18 ; } else if ( rtDW
. iggiejtmqu < 120.0F ) { idx_idx_2 = 19 ; } else if ( rtDW . iggiejtmqu <
125.0F ) { idx_idx_2 = 20 ; } else if ( rtDW . iggiejtmqu < 130.0F ) {
idx_idx_2 = 21 ; } else if ( rtDW . iggiejtmqu < 135.0F ) { idx_idx_2 = 22 ;
} else if ( rtDW . iggiejtmqu < 140.0F ) { idx_idx_2 = 23 ; } else if ( rtDW
. iggiejtmqu < 145.0F ) { idx_idx_2 = 24 ; } else if ( rtDW . iggiejtmqu <
150.0F ) { idx_idx_2 = 25 ; } else if ( rtDW . iggiejtmqu < 155.0F ) {
idx_idx_2 = 26 ; } else if ( rtDW . iggiejtmqu < 160.0F ) { idx_idx_2 = 27 ;
} else if ( rtDW . iggiejtmqu < 165.0F ) { idx_idx_2 = 28 ; } else if ( rtDW
. iggiejtmqu < 170.0F ) { idx_idx_2 = 29 ; } else if ( rtDW . iggiejtmqu <
175.0F ) { idx_idx_2 = 30 ; } else if ( rtDW . iggiejtmqu < 180.0F ) {
idx_idx_2 = 31 ; } else if ( rtDW . iggiejtmqu < 185.0F ) { idx_idx_2 = 32 ;
} else if ( rtDW . iggiejtmqu < 190.0F ) { idx_idx_2 = 33 ; } else {
idx_idx_2 = 34 ; } rtDW . loepcnnuit = idx_idx_2 ; if ( idx_idx_1 !=
idx_idx_2 ) { switch ( idx_idx_1 ) { case 0 : ssSetSolverNeedsReset ( rtS ) ;
break ; case 1 : ssSetSolverNeedsReset ( rtS ) ; break ; case 2 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 3 : ssSetSolverNeedsReset ( rtS
) ; break ; case 4 : ssSetSolverNeedsReset ( rtS ) ; break ; case 5 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 6 : ssSetSolverNeedsReset ( rtS
) ; break ; case 7 : ssSetSolverNeedsReset ( rtS ) ; break ; case 8 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 9 : ssSetSolverNeedsReset ( rtS
) ; break ; case 10 : ssSetSolverNeedsReset ( rtS ) ; break ; case 11 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 12 : ssSetSolverNeedsReset ( rtS
) ; break ; case 13 : ssSetSolverNeedsReset ( rtS ) ; break ; case 14 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 15 : ssSetSolverNeedsReset ( rtS
) ; break ; case 16 : ssSetSolverNeedsReset ( rtS ) ; break ; case 17 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 18 : ssSetSolverNeedsReset ( rtS
) ; break ; case 19 : ssSetSolverNeedsReset ( rtS ) ; break ; case 20 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 21 : ssSetSolverNeedsReset ( rtS
) ; break ; case 22 : ssSetSolverNeedsReset ( rtS ) ; break ; case 23 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 24 : ssSetSolverNeedsReset ( rtS
) ; break ; case 25 : ssSetSolverNeedsReset ( rtS ) ; break ; case 26 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 27 : ssSetSolverNeedsReset ( rtS
) ; break ; case 28 : ssSetSolverNeedsReset ( rtS ) ; break ; case 29 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 30 : ssSetSolverNeedsReset ( rtS
) ; break ; case 31 : ssSetSolverNeedsReset ( rtS ) ; break ; case 32 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 33 : ssSetSolverNeedsReset ( rtS
) ; break ; case 34 : ssSetSolverNeedsReset ( rtS ) ; break ; } } switch (
idx_idx_2 ) { case 0 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime (
rtS , 2 ) != ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB
. fnzk1kwery [ 0 ] = rtP . tp_Value [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP . tp_Value [ 2 ] ; srUpdateBC (
rtDW . o0fqt141qd ) ; break ; case 1 : if ( idx_idx_2 != idx_idx_1 ) { if (
ssGetTaskTime ( rtS , 2 ) != ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset (
rtS ) ; } } rtB . fnzk1kwery [ 0 ] = rtP . tp_Value_mmdc5jjvbq [ 0 ] ; rtB .
fnzk1kwery [ 1 ] = rtP . tp_Value_mmdc5jjvbq [ 1 ] ; rtB . fnzk1kwery [ 2 ] =
rtP . tp_Value_mmdc5jjvbq [ 2 ] ; srUpdateBC ( rtDW . h3vqcmc1hz ) ; break ;
case 2 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_oipiuqzz5m [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_oipiuqzz5m [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_oipiuqzz5m [ 2 ] ; srUpdateBC ( rtDW . pqpqjda5is ) ; break ; case 3
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_d0bqr0adai [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_d0bqr0adai [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_d0bqr0adai [ 2 ] ; srUpdateBC ( rtDW . bwmwpnvwlf ) ; break ; case 4
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_e3hgnntmco [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_e3hgnntmco [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_e3hgnntmco [ 2 ] ; srUpdateBC ( rtDW . hf2ukkb54z ) ; break ; case 5
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_npphduwijc [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_npphduwijc [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_npphduwijc [ 2 ] ; srUpdateBC ( rtDW . dp2wxggv2y ) ; break ; case 6
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_ou5xhjjrog [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_ou5xhjjrog [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_ou5xhjjrog [ 2 ] ; srUpdateBC ( rtDW . ifikoeohu4 ) ; break ; case 7
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_o1owsucjxa [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_o1owsucjxa [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_o1owsucjxa [ 2 ] ; srUpdateBC ( rtDW . fb2jmsx45b ) ; break ; case 8
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_mrn2z15h1h [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_mrn2z15h1h [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_mrn2z15h1h [ 2 ] ; srUpdateBC ( rtDW . gu2pk5utpz ) ; break ; case 9
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_llx05eyp5k [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_llx05eyp5k [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_llx05eyp5k [ 2 ] ; srUpdateBC ( rtDW . m1sbzn2h1n ) ; break ; case
10 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_fue1paeukq [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_fue1paeukq [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_fue1paeukq [ 2 ] ; srUpdateBC ( rtDW . ewylvoz5wx ) ; break ; case
11 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_jfinzetqib [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_jfinzetqib [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_jfinzetqib [ 2 ] ; srUpdateBC ( rtDW . bzt2b4vlgj ) ; break ; case
12 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_ootste3xt4 [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_ootste3xt4 [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_ootste3xt4 [ 2 ] ; srUpdateBC ( rtDW . p5cjuriyjr ) ; break ; case
13 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_glry24veam [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_glry24veam [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_glry24veam [ 2 ] ; srUpdateBC ( rtDW . klgivly02z ) ; break ; case
14 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_a2liswbfky [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_a2liswbfky [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_a2liswbfky [ 2 ] ; srUpdateBC ( rtDW . nlyldhhvyb ) ; break ; case
15 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_f4oghoc422 [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_f4oghoc422 [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_f4oghoc422 [ 2 ] ; srUpdateBC ( rtDW . k1yann3ya5 ) ; break ; case
16 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_mg4ej1dk4c [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_mg4ej1dk4c [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_mg4ej1dk4c [ 2 ] ; srUpdateBC ( rtDW . bubafrutom ) ; break ; case
17 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_io4ywoj4cq [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_io4ywoj4cq [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_io4ywoj4cq [ 2 ] ; srUpdateBC ( rtDW . ltvu2oc3sf ) ; break ; case
18 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_pupcrx2sx4 [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_pupcrx2sx4 [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_pupcrx2sx4 [ 2 ] ; srUpdateBC ( rtDW . li2ivnnt0t ) ; break ; case
19 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_lppwvyte25 [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_lppwvyte25 [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_lppwvyte25 [ 2 ] ; srUpdateBC ( rtDW . ae1e1itbfy ) ; break ; case
20 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_aqtk5tk1ud [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_aqtk5tk1ud [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_aqtk5tk1ud [ 2 ] ; srUpdateBC ( rtDW . dhx34gepf4 ) ; break ; case
21 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_e5rebtcdsl [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_e5rebtcdsl [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_e5rebtcdsl [ 2 ] ; srUpdateBC ( rtDW . p2atyilds3 ) ; break ; case
22 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_ag1b2ln31i [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_ag1b2ln31i [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_ag1b2ln31i [ 2 ] ; srUpdateBC ( rtDW . edw2mgcvx1 ) ; break ; case
23 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_d4yv4borja [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_d4yv4borja [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_d4yv4borja [ 2 ] ; srUpdateBC ( rtDW . n4uikvdjac ) ; break ; case
24 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_fqq5esx3ho [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_fqq5esx3ho [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_fqq5esx3ho [ 2 ] ; srUpdateBC ( rtDW . chxryck3fg ) ; break ; case
25 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_adjdr5el0e [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_adjdr5el0e [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_adjdr5el0e [ 2 ] ; srUpdateBC ( rtDW . dl0glhtqdr ) ; break ; case
26 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_hwfgj3cglx [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_hwfgj3cglx [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_hwfgj3cglx [ 2 ] ; srUpdateBC ( rtDW . adcpzgniuv ) ; break ; case
27 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_hw24qnkg5a [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_hw24qnkg5a [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_hw24qnkg5a [ 2 ] ; srUpdateBC ( rtDW . ismm4u0kis ) ; break ; case
28 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_emdemdcjqw [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_emdemdcjqw [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_emdemdcjqw [ 2 ] ; srUpdateBC ( rtDW . kct4avkdgo ) ; break ; case
29 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_m2pfqecp3r [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_m2pfqecp3r [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_m2pfqecp3r [ 2 ] ; srUpdateBC ( rtDW . ljqu2i52fc ) ; break ; case
30 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_m3vqy1b0ro [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_m3vqy1b0ro [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_m3vqy1b0ro [ 2 ] ; srUpdateBC ( rtDW . lpg4z3lelv ) ; break ; case
31 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_mcbwndmcgn [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_mcbwndmcgn [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_mcbwndmcgn [ 2 ] ; srUpdateBC ( rtDW . ombi11gse3 ) ; break ; case
32 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_lw1gyfl3x2 [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_lw1gyfl3x2 [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_lw1gyfl3x2 [ 2 ] ; srUpdateBC ( rtDW . igzqf1qklf ) ; break ; case
33 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_iqqu53t0m4 [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_iqqu53t0m4 [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_iqqu53t0m4 [ 2 ] ; srUpdateBC ( rtDW . moze4hcv5c ) ; break ; case
34 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . fnzk1kwery
[ 0 ] = rtP . tp_Value_lvdpu0ygf2 [ 0 ] ; rtB . fnzk1kwery [ 1 ] = rtP .
tp_Value_lvdpu0ygf2 [ 1 ] ; rtB . fnzk1kwery [ 2 ] = rtP .
tp_Value_lvdpu0ygf2 [ 2 ] ; srUpdateBC ( rtDW . kuzwdhnrip ) ; break ; }
idx_idx_1 = rtDW . a1axcz0kbn ; if ( hhjnxjzwip < 25.0F ) { idx_idx_2 = 0 ; }
else if ( hhjnxjzwip < 30.0F ) { idx_idx_2 = 1 ; } else if ( hhjnxjzwip <
35.0F ) { idx_idx_2 = 2 ; } else if ( hhjnxjzwip < 40.0F ) { idx_idx_2 = 3 ;
} else if ( hhjnxjzwip < 45.0F ) { idx_idx_2 = 4 ; } else if ( hhjnxjzwip <
50.0F ) { idx_idx_2 = 5 ; } else if ( hhjnxjzwip < 55.0F ) { idx_idx_2 = 6 ;
} else if ( hhjnxjzwip < 60.0F ) { idx_idx_2 = 7 ; } else if ( hhjnxjzwip <
65.0F ) { idx_idx_2 = 8 ; } else if ( hhjnxjzwip < 70.0F ) { idx_idx_2 = 9 ;
} else if ( hhjnxjzwip < 75.0F ) { idx_idx_2 = 10 ; } else if ( hhjnxjzwip <
80.0F ) { idx_idx_2 = 11 ; } else if ( hhjnxjzwip < 85.0F ) { idx_idx_2 = 12
; } else if ( hhjnxjzwip < 90.0F ) { idx_idx_2 = 13 ; } else if ( hhjnxjzwip
< 95.0F ) { idx_idx_2 = 14 ; } else if ( hhjnxjzwip < 100.0F ) { idx_idx_2 =
15 ; } else if ( hhjnxjzwip < 105.0F ) { idx_idx_2 = 16 ; } else if (
hhjnxjzwip < 110.0F ) { idx_idx_2 = 17 ; } else if ( hhjnxjzwip < 115.0F ) {
idx_idx_2 = 18 ; } else if ( hhjnxjzwip < 120.0F ) { idx_idx_2 = 19 ; } else
if ( hhjnxjzwip < 125.0F ) { idx_idx_2 = 20 ; } else if ( hhjnxjzwip < 130.0F
) { idx_idx_2 = 21 ; } else if ( hhjnxjzwip < 135.0F ) { idx_idx_2 = 22 ; }
else if ( hhjnxjzwip < 140.0F ) { idx_idx_2 = 23 ; } else if ( hhjnxjzwip <
145.0F ) { idx_idx_2 = 24 ; } else if ( hhjnxjzwip < 150.0F ) { idx_idx_2 =
25 ; } else if ( hhjnxjzwip < 155.0F ) { idx_idx_2 = 26 ; } else if (
hhjnxjzwip < 160.0F ) { idx_idx_2 = 27 ; } else if ( hhjnxjzwip < 165.0F ) {
idx_idx_2 = 28 ; } else if ( hhjnxjzwip < 170.0F ) { idx_idx_2 = 29 ; } else
if ( hhjnxjzwip < 175.0F ) { idx_idx_2 = 30 ; } else if ( hhjnxjzwip < 180.0F
) { idx_idx_2 = 31 ; } else { idx_idx_2 = 32 ; } rtDW . a1axcz0kbn =
idx_idx_2 ; if ( idx_idx_1 != idx_idx_2 ) { switch ( idx_idx_1 ) { case 0 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 1 : ssSetSolverNeedsReset ( rtS
) ; break ; case 2 : ssSetSolverNeedsReset ( rtS ) ; break ; case 3 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 4 : ssSetSolverNeedsReset ( rtS
) ; break ; case 5 : ssSetSolverNeedsReset ( rtS ) ; break ; case 6 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 7 : ssSetSolverNeedsReset ( rtS
) ; break ; case 8 : ssSetSolverNeedsReset ( rtS ) ; break ; case 9 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 10 : ssSetSolverNeedsReset ( rtS
) ; break ; case 11 : ssSetSolverNeedsReset ( rtS ) ; break ; case 12 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 13 : ssSetSolverNeedsReset ( rtS
) ; break ; case 14 : ssSetSolverNeedsReset ( rtS ) ; break ; case 15 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 16 : ssSetSolverNeedsReset ( rtS
) ; break ; case 17 : ssSetSolverNeedsReset ( rtS ) ; break ; case 18 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 19 : ssSetSolverNeedsReset ( rtS
) ; break ; case 20 : ssSetSolverNeedsReset ( rtS ) ; break ; case 21 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 22 : ssSetSolverNeedsReset ( rtS
) ; break ; case 23 : ssSetSolverNeedsReset ( rtS ) ; break ; case 24 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 25 : ssSetSolverNeedsReset ( rtS
) ; break ; case 26 : ssSetSolverNeedsReset ( rtS ) ; break ; case 27 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 28 : ssSetSolverNeedsReset ( rtS
) ; break ; case 29 : ssSetSolverNeedsReset ( rtS ) ; break ; case 30 :
ssSetSolverNeedsReset ( rtS ) ; break ; case 31 : ssSetSolverNeedsReset ( rtS
) ; break ; case 32 : ssSetSolverNeedsReset ( rtS ) ; break ; } } switch (
idx_idx_2 ) { case 0 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime (
rtS , 2 ) != ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB
. dzd1zqtqmx [ 0 ] = rtP . tp_Value_kncwrbpx0j [ 0 ] ; rtB . dzd1zqtqmx [ 1 ]
= rtP . tp_Value_kncwrbpx0j [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_kncwrbpx0j [ 2 ] ; srUpdateBC ( rtDW . j4ymuqubrw ) ; break ; case 1
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_anpzo5c2vg [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_anpzo5c2vg [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_anpzo5c2vg [ 2 ] ; srUpdateBC ( rtDW . kymzzotg2g ) ; break ; case 2
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_pl0rshtt5z [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_pl0rshtt5z [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_pl0rshtt5z [ 2 ] ; srUpdateBC ( rtDW . maiimsnqs5 ) ; break ; case 3
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_djrhs1sek1 [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_djrhs1sek1 [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_djrhs1sek1 [ 2 ] ; srUpdateBC ( rtDW . dyx4tug5h3 ) ; break ; case 4
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_izulaw4r0j [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_izulaw4r0j [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_izulaw4r0j [ 2 ] ; srUpdateBC ( rtDW . cr2kibgo2j ) ; break ; case 5
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_bljmnhbssi [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_bljmnhbssi [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_bljmnhbssi [ 2 ] ; srUpdateBC ( rtDW . pwlmqo3nxm ) ; break ; case 6
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_atkwrgxtrm [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_atkwrgxtrm [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_atkwrgxtrm [ 2 ] ; srUpdateBC ( rtDW . guuziano0t ) ; break ; case 7
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_mzh3evdrk5 [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_mzh3evdrk5 [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_mzh3evdrk5 [ 2 ] ; srUpdateBC ( rtDW . l12omsu2tn ) ; break ; case 8
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_ljry3t5zvi [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_ljry3t5zvi [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_ljry3t5zvi [ 2 ] ; srUpdateBC ( rtDW . o2zj3fqza1 ) ; break ; case 9
: if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_jwr5rhqyrj [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_jwr5rhqyrj [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_jwr5rhqyrj [ 2 ] ; srUpdateBC ( rtDW . m3gfat1ui0 ) ; break ; case
10 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_id4dgkpbz2 [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_id4dgkpbz2 [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_id4dgkpbz2 [ 2 ] ; srUpdateBC ( rtDW . dk3vj22y05 ) ; break ; case
11 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_b1geh04tje [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_b1geh04tje [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_b1geh04tje [ 2 ] ; srUpdateBC ( rtDW . o3c1lu15ny ) ; break ; case
12 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_gp424rrzsc [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_gp424rrzsc [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_gp424rrzsc [ 2 ] ; srUpdateBC ( rtDW . j45e0raewi ) ; break ; case
13 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_m4cdr3ebrt [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_m4cdr3ebrt [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_m4cdr3ebrt [ 2 ] ; srUpdateBC ( rtDW . o3wc5wwa4p ) ; break ; case
14 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_muv5msoizt [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_muv5msoizt [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_muv5msoizt [ 2 ] ; srUpdateBC ( rtDW . irsxloeepq ) ; break ; case
15 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_feweqckn0h [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_feweqckn0h [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_feweqckn0h [ 2 ] ; srUpdateBC ( rtDW . cp3q1at4o2 ) ; break ; case
16 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_l02eb0qhwx [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_l02eb0qhwx [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_l02eb0qhwx [ 2 ] ; srUpdateBC ( rtDW . pce44vep3x ) ; break ; case
17 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_fntfr5tndb [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_fntfr5tndb [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_fntfr5tndb [ 2 ] ; srUpdateBC ( rtDW . mee1wioe1r ) ; break ; case
18 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_pmklg2ovge [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_pmklg2ovge [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_pmklg2ovge [ 2 ] ; srUpdateBC ( rtDW . a5nvnya1oe ) ; break ; case
19 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_j0jknsqgnc [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_j0jknsqgnc [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_j0jknsqgnc [ 2 ] ; srUpdateBC ( rtDW . dfax004odl ) ; break ; case
20 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_cigkhzn0ua [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_cigkhzn0ua [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_cigkhzn0ua [ 2 ] ; srUpdateBC ( rtDW . mwuspmm2e1 ) ; break ; case
21 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_eqr0fc2ekw [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_eqr0fc2ekw [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_eqr0fc2ekw [ 2 ] ; srUpdateBC ( rtDW . jgu1xgjxem ) ; break ; case
22 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_ltt52ykbaf [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_ltt52ykbaf [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_ltt52ykbaf [ 2 ] ; srUpdateBC ( rtDW . my15ghhvb1 ) ; break ; case
23 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_ieij3u5c0j [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_ieij3u5c0j [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_ieij3u5c0j [ 2 ] ; srUpdateBC ( rtDW . bcd3kgenub ) ; break ; case
24 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_brvneamxcn [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_brvneamxcn [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_brvneamxcn [ 2 ] ; srUpdateBC ( rtDW . f5k2rzim4a ) ; break ; case
25 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_nbyf2qneco [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_nbyf2qneco [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_nbyf2qneco [ 2 ] ; srUpdateBC ( rtDW . nx3flbvahx ) ; break ; case
26 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_hj03giyyop [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_hj03giyyop [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_hj03giyyop [ 2 ] ; srUpdateBC ( rtDW . lik1wotc2i ) ; break ; case
27 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_gezfx3zot5 [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_gezfx3zot5 [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_gezfx3zot5 [ 2 ] ; srUpdateBC ( rtDW . gg02mzoxhc ) ; break ; case
28 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_nssh0jxsrt [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_nssh0jxsrt [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_nssh0jxsrt [ 2 ] ; srUpdateBC ( rtDW . gwxpzomgjh ) ; break ; case
29 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_fddutnl2oo [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_fddutnl2oo [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_fddutnl2oo [ 2 ] ; srUpdateBC ( rtDW . etxqofccji ) ; break ; case
30 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_oaafylj13a [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_oaafylj13a [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_oaafylj13a [ 2 ] ; srUpdateBC ( rtDW . ljwb0xnabb ) ; break ; case
31 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_ovs553bhfy [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_ovs553bhfy [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_ovs553bhfy [ 2 ] ; srUpdateBC ( rtDW . ivkldwkotp ) ; break ; case
32 : if ( idx_idx_2 != idx_idx_1 ) { if ( ssGetTaskTime ( rtS , 2 ) !=
ssGetTStart ( rtS ) ) { ssSetSolverNeedsReset ( rtS ) ; } } rtB . dzd1zqtqmx
[ 0 ] = rtP . tp_Value_hc1bpxti1u [ 0 ] ; rtB . dzd1zqtqmx [ 1 ] = rtP .
tp_Value_hc1bpxti1u [ 1 ] ; rtB . dzd1zqtqmx [ 2 ] = rtP .
tp_Value_hc1bpxti1u [ 2 ] ; srUpdateBC ( rtDW . hypqqzrtox ) ; break ; } if (
meppapiqj0 ) { cesfgrkder_idx_0 = rtB . dzd1zqtqmx [ 0 ] ; cesfgrkder_idx_1 =
rtB . dzd1zqtqmx [ 1 ] ; o2wgigs4ap_idx_0 = rtB . dzd1zqtqmx [ 2 ] ; } else {
cesfgrkder_idx_0 = rtB . fnzk1kwery [ 0 ] ; cesfgrkder_idx_1 = rtB .
fnzk1kwery [ 1 ] ; o2wgigs4ap_idx_0 = rtB . fnzk1kwery [ 2 ] ; } rtB .
modanr3tbz = rtP . man_map_cons1_Gain * cesfgrkder_idx_0 ; rtDW . o3z1jsmhkx
= rtB . modanr3tbz ; rtB . hpemxq4evt = rtP . man_egrr_cons1_Gain *
cesfgrkder_idx_1 ; rtDW . hptuorf3i3 = rtB . hpemxq4evt ; rtB . ppjeb0koux =
rtP . man_pex_cons1_Gain * o2wgigs4ap_idx_0 ; rtDW . mi05525rde = rtB .
ppjeb0koux ; p03esja3h2 *= rtP . Gain5_Gain_jqsodes1v1 ; hde10siz3b_idx_0 =
rtP . Gain6_Gain_hjsd4cpev4 * rtB . fokzlm1wwg ; hde10siz3b_idx_1 = rtP .
Gain6_Gain_hjsd4cpev4 * p03esja3h2 ; if ( rtB . kwlj023pby <= rtP .
zero3_Value_oxiwsglhov ) { rtB . gkalf2lwvh = rtP . zero1_Value_lj4wvitffo ;
} else { rtB . gkalf2lwvh = alqkjudhu3 ; } rtB . iqpuylkhd5 = rtP .
man_tuneFiltalpha_Gain_bfzlu554zk * rtDW . owcamicoch ; rtB . kaoklhu34x =
rtP . man_tuneFiltalpha1_Gain_jgtgdms0x5 * rtDW . owcamicoch ; if ( rtB .
kaoklhu34x > rtP . Saturation1_UpperSat_omkudzerxc ) { tmp_b = rtP .
Saturation1_UpperSat_omkudzerxc ; } else if ( rtB . kaoklhu34x < rtP .
Saturation1_LowerSat_hq5jvogu4t ) { tmp_b = rtP .
Saturation1_LowerSat_hq5jvogu4t ; } else { tmp_b = rtB . kaoklhu34x ; } if (
rtB . iqpuylkhd5 > rtP . Saturation4_UpperSat_fgykekgs25 ) { cesfgrkder_idx_0
= rtP . Saturation4_UpperSat_fgykekgs25 ; } else if ( rtB . iqpuylkhd5 < rtP
. Saturation4_LowerSat_lknp0jneji ) { cesfgrkder_idx_0 = rtP .
Saturation4_LowerSat_lknp0jneji ; } else { cesfgrkder_idx_0 = rtB .
iqpuylkhd5 ; } rtB . lxrst0kqri = ( rtP . zero1_Value_jcxubjmcqw -
cesfgrkder_idx_0 ) * rtDW . mvpjwhrzk3 + rtDW . fhgbtmls3d * tmp_b ; rtB .
i1qmymrrth = rtP . man_tuneFiltalpha_Gain_hlqsioyaw5 * rtDW . owcamicoch ;
rtB . cgkybpq2my = rtP . man_tuneFiltalpha1_Gain_oqdux2lbda * rtDW .
owcamicoch ; if ( rtB . cgkybpq2my > rtP . Saturation1_UpperSat_hyh2idym0z )
{ tmp_b = rtP . Saturation1_UpperSat_hyh2idym0z ; } else if ( rtB .
cgkybpq2my < rtP . Saturation1_LowerSat_hh0hohkue0 ) { tmp_b = rtP .
Saturation1_LowerSat_hh0hohkue0 ; } else { tmp_b = rtB . cgkybpq2my ; } if (
rtB . i1qmymrrth > rtP . Saturation4_UpperSat_hzncksesqh ) { cesfgrkder_idx_0
= rtP . Saturation4_UpperSat_hzncksesqh ; } else if ( rtB . i1qmymrrth < rtP
. Saturation4_LowerSat_hp04ybe0ds ) { cesfgrkder_idx_0 = rtP .
Saturation4_LowerSat_hp04ybe0ds ; } else { cesfgrkder_idx_0 = rtB .
i1qmymrrth ; } rtB . dtn0co1rlo = ( rtP . zero1_Value_cfe22a4fnb -
cesfgrkder_idx_0 ) * rtDW . mtqhixagy1 + rtDW . l1sigmyvxe * tmp_b ;
Look2D_real32_T_real32_T_real32_T ( & ( bprhelbqm0 ) , rtP .
gain_schedule_egr_Table , rtB . itsvvwrq0a , rtP . gain_schedule_egr_RowIdx ,
5U , rtB . ljk4xix01m , rtP . gain_schedule_egr_ColIdx , 6U ) ;
Look2D_real32_T_real32_T_real32_T ( & ( ana05zcqxm ) , rtP .
gain_schedule_uvnlift_Table , rtB . itsvvwrq0a , rtP .
gain_schedule_uvnlift_RowIdx , 5U , rtB . ljk4xix01m , rtP .
gain_schedule_uvnlift_ColIdx , 6U ) ; jwc13tgat3 = rtDW . noqny2ee14 ; for (
i = 0 ; i < 2 ; i ++ ) { tmp_f [ i ] = rtP . Gain_Gain_j24i2xq1z0 [ i + 4 ] *
rtB . kzspe3uhcs [ 2 ] + ( rtP . Gain_Gain_j24i2xq1z0 [ i + 2 ] * rtB .
kzspe3uhcs [ 1 ] + rtP . Gain_Gain_j24i2xq1z0 [ i ] * rtB . kzspe3uhcs [ 0 ]
) ; } cesfgrkder_idx_0 = jwc13tgat3 - tmp_f [ 0 ] ; cesfgrkder_idx_1 = rtDW .
ljbykua013 - tmp_f [ 1 ] ; for ( i = 0 ; i < 3 ; i ++ ) { tmp_c [ i ] = rtP .
Gain1_Gain_nbjizbigxo [ i + 3 ] * cesfgrkder_idx_1 + rtP .
Gain1_Gain_nbjizbigxo [ i ] * cesfgrkder_idx_0 ; } for ( i = 0 ; i < 3 ; i ++
) { tmp_k [ i ] = rtP . Gain2_Gain_oz0f03bs1q [ i + 6 ] * rtB . kzspe3uhcs [
2 ] + ( rtP . Gain2_Gain_oz0f03bs1q [ i + 3 ] * rtB . kzspe3uhcs [ 1 ] + rtP
. Gain2_Gain_oz0f03bs1q [ i ] * rtB . kzspe3uhcs [ 0 ] ) ; } for ( i = 0 ; i
< 3 ; i ++ ) { rtB . mebfpuov3e [ i ] = ( rtP . Gain3_Gain_ibhgrspb4v [ i + 3
] * rtB . eu3n5piaim [ 1 ] + rtP . Gain3_Gain_ibhgrspb4v [ i ] * rtB .
eu3n5piaim [ 0 ] ) + ( tmp_c [ i ] + tmp_k [ i ] ) ; } rtB . hc4pbn1ftr = rtP
. man_start_pattern_Gain * rtDW . ocojyks2sz ; if ( rtB . hc4pbn1ftr > rtP .
zero10_Value ) { jwc13tgat3 = hhjnxjzwip ; } else { jwc13tgat3 = rtP .
zero10_Value ; } rtB . lluxiqhlvi = jwc13tgat3 + rtP . zero11_Value ; rtB .
eh3nc1dwbh = g1ekzbu3oi ; } rtB . gpulvfhg1s = rtB . ezgferlgph - rtB .
eh3nc1dwbh ; rtY . f2pqowb0h2 = rtB . gpulvfhg1s ; if ( ssIsSampleHit ( rtS ,
2 , 0 ) ) { rtB . ixod0recqg = rtB . eznht2b1xz ; if ( ssGetLogOutput ( rtS )
) { { void * pSignalProbeCollection = ( void * ) rtDW . jllpsh2lx2 .
SignalProbe ; if ( rtwSignalProbeCollectionGetLoggingIsOn (
pSignalProbeCollection ) ) { { real_T t ; void * pData ; t = ssGetTaskTime (
rtS , 2 ) ; pData = ( void * ) & rtB . ixod0recqg ;
rtwSignalProbeCollectionAppendSample ( pSignalProbeCollection , 0 , t , pData
) ; } } } } rtB . ptmfmdqmdu = rtB . arhywgn0ud [ 0 ] ; if ( ssGetLogOutput (
rtS ) ) { { void * pSignalProbeCollection = ( void * ) rtDW . kjuost3l4t .
SignalProbe ; if ( rtwSignalProbeCollectionGetLoggingIsOn (
pSignalProbeCollection ) ) { { real_T t ; void * pData ; t = ssGetTaskTime (
rtS , 2 ) ; pData = ( void * ) & rtB . ptmfmdqmdu ;
rtwSignalProbeCollectionAppendSample ( pSignalProbeCollection , 0 , t , pData
) ; } } } } rtB . jg43ge1e1q = rtB . dwx51vir01 [ 0 ] ; if ( ssGetLogOutput (
rtS ) ) { { void * pSignalProbeCollection = ( void * ) rtDW . gegk3zt5rh .
SignalProbe ; if ( rtwSignalProbeCollectionGetLoggingIsOn (
pSignalProbeCollection ) ) { { real_T t ; void * pData ; t = ssGetTaskTime (
rtS , 2 ) ; pData = ( void * ) & rtB . jg43ge1e1q ;
rtwSignalProbeCollectionAppendSample ( pSignalProbeCollection , 0 , t , pData
) ; } } } } } if ( ssGetLogOutput ( rtS ) ) { { void * pSignalProbeCollection
= ( void * ) rtDW . br3dyaxwzn . SignalProbe ; if (
rtwSignalProbeCollectionGetLoggingIsOn ( pSignalProbeCollection ) ) { {
real_T t ; void * pData ; t = ssGetTaskTime ( rtS , 0 ) ; pData = ( void * )
& rtU . ch4dzb1x4i ; rtwSignalProbeCollectionAppendSample (
pSignalProbeCollection , 0 , t , pData ) ; } } } } if ( ssGetLogOutput ( rtS
) ) { { void * pSignalProbeCollection = ( void * ) rtDW . msk43x33qs .
SignalProbe ; if ( rtwSignalProbeCollectionGetLoggingIsOn (
pSignalProbeCollection ) ) { { real_T t ; void * pData ; t = ssGetTaskTime (
rtS , 0 ) ; pData = ( void * ) & rtU . gm151yhz1l ;
rtwSignalProbeCollectionAppendSample ( pSignalProbeCollection , 0 , t , pData
) ; } } } } rtB . eyyzffon51 = rtB . ezgferlgph - rtB . eh3nc1dwbh ; if (
ssGetLogOutput ( rtS ) ) { { void * pSignalProbeCollection = ( void * ) rtDW
. aiqcj0xpj3 . SignalProbe ; if ( rtwSignalProbeCollectionGetLoggingIsOn (
pSignalProbeCollection ) ) { { real_T t ; void * pData ; t = ssGetTaskTime (
rtS , 0 ) ; pData = ( void * ) & rtB . eyyzffon51 ;
rtwSignalProbeCollectionAppendSample ( pSignalProbeCollection , 0 , t , pData
) ; } } } } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB . jaeao5tvyt =
fwhtla1rft ; } rtB . db3aloisol = rtB . pe0kzgwhkx - rtB . jaeao5tvyt ; if (
ssGetLogOutput ( rtS ) ) { { void * pSignalProbeCollection = ( void * ) rtDW
. imyl4toc4j . SignalProbe ; if ( rtwSignalProbeCollectionGetLoggingIsOn (
pSignalProbeCollection ) ) { { real_T t ; void * pData ; t = ssGetTaskTime (
rtS , 0 ) ; pData = ( void * ) & rtB . db3aloisol ;
rtwSignalProbeCollectionAppendSample ( pSignalProbeCollection , 0 , t , pData
) ; } } } } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB . faswnrxfir [ 0 ] =
rtB . kzspe3uhcs [ 0 ] ; rtB . faswnrxfir [ 1 ] = rtB . oknjoatyhh ; rtB .
faswnrxfir [ 2 ] = rtB . hwqwznwhbl ; rtB . faswnrxfir [ 3 ] = rtB .
e3xygmo5lb ; rtB . faswnrxfir [ 4 ] = rtB . gj05xuhqyp ; rtB . faswnrxfir [ 5
] = rtB . jtmcug05p1 ; rtB . faswnrxfir [ 6 ] = rtB . lmosmreh2j ; rtB .
faswnrxfir [ 7 ] = rtB . f1zcecdgrp ; rtB . faswnrxfir [ 8 ] = rtB .
pik2cpjozq ; rtB . faswnrxfir [ 9 ] = rtB . l4ddhp1s2y ; rtB . faswnrxfir [
10 ] = rtB . m3gtxwsewc ; rtB . faswnrxfir [ 11 ] = rtB . gyejnsfev5 ; rtB .
faswnrxfir [ 12 ] = rtB . fokzlm1wwg ; if ( ssGetLogOutput ( rtS ) ) { { void
* pSignalProbeCollection = ( void * ) rtDW . juk00hf1bn . SignalProbe ; if (
rtwSignalProbeCollectionGetLoggingIsOn ( pSignalProbeCollection ) ) { {
real_T t ; void * pData ; t = ssGetTaskTime ( rtS , 2 ) ; pData = ( void * )
& rtB . faswnrxfir [ 0 ] ; rtwSignalProbeCollectionAppendSample (
pSignalProbeCollection , 0 , t , pData ) ; } } } } if ( ssGetLogOutput ( rtS
) ) { { void * pSignalProbeCollection = ( void * ) rtDW . prcjjqdyp5 .
SignalProbe ; if ( rtwSignalProbeCollectionGetLoggingIsOn (
pSignalProbeCollection ) ) { { real_T t ; void * pData ; t = ssGetTaskTime (
rtS , 2 ) ; pData = ( void * ) & rtB . eu3n5piaim [ 0 ] ;
rtwSignalProbeCollectionAppendSample ( pSignalProbeCollection , 0 , t , pData
) ; } } } } if ( ssGetLogOutput ( rtS ) ) { { void * pSignalProbeCollection =
( void * ) rtDW . llq51al0ac . SignalProbe ; if (
rtwSignalProbeCollectionGetLoggingIsOn ( pSignalProbeCollection ) ) { {
real_T t ; void * pData ; t = ssGetTaskTime ( rtS , 2 ) ; pData = ( void * )
& rtB . dgqpk3ff5k ; rtwSignalProbeCollectionAppendSample (
pSignalProbeCollection , 0 , t , pData ) ; } } } } } rtB . jjsej1qngo = rtP .
n3_Gain * rtB . ixoqjsjjol ; if ( ssGetLogOutput ( rtS ) ) { { void *
pSignalProbeCollection = ( void * ) rtDW . iz4q3uhlvz . SignalProbe ; if (
rtwSignalProbeCollectionGetLoggingIsOn ( pSignalProbeCollection ) ) { {
real_T t ; void * pData ; t = ssGetTaskTime ( rtS , 0 ) ; pData = ( void * )
& rtB . jjsej1qngo ; rtwSignalProbeCollectionAppendSample (
pSignalProbeCollection , 0 , t , pData ) ; } } } } if ( ssIsSampleHit ( rtS ,
2 , 0 ) ) { rtB . duoa5br5cp = not4fp11wk ; } if ( ssGetLogOutput ( rtS ) ) {
StructLogVar * svar = ( StructLogVar * ) rtDW . o02f1axwt1 . LoggedData ;
LogVar * var = svar -> signals . values ; { double locTime = ssGetTaskTime (
rtS , 0 ) ; rt_UpdateLogVar ( ( LogVar * ) svar -> time , & locTime , 0 ) ; }
{ real_T up0 [ 2 ] ; up0 [ 0 ] = rtB . ezgferlgph ; up0 [ 1 ] = rtB .
eh3nc1dwbh ; rt_UpdateLogVar ( ( LogVar * ) var , up0 , 0 ) ; var = var ->
next ; } { real_T up1 [ 2 ] ; up1 [ 0 ] = rtB . pe0kzgwhkx ; up1 [ 1 ] = rtB
. jaeao5tvyt ; rt_UpdateLogVar ( ( LogVar * ) var , up1 , 0 ) ; var = var ->
next ; } { real_T up2 [ 1 ] ; up2 [ 0 ] = rtB . jg43ge1e1q ; rt_UpdateLogVar
( ( LogVar * ) var , up2 , 0 ) ; var = var -> next ; } { real_T up3 [ 1 ] ;
up3 [ 0 ] = rtB . ehhntoamo3 ; rt_UpdateLogVar ( ( LogVar * ) var , up3 , 0 )
; var = var -> next ; } { real_T up4 [ 1 ] ; up4 [ 0 ] = rtB . duoa5br5cp ;
rt_UpdateLogVar ( ( LogVar * ) var , up4 , 0 ) ; } } if ( ssGetLogOutput (
rtS ) ) { StructLogVar * svar = ( StructLogVar * ) rtDW . etcffifed1 .
LoggedData ; LogVar * var = svar -> signals . values ; { double locTime =
ssGetTaskTime ( rtS , 0 ) ; rt_UpdateLogVar ( ( LogVar * ) svar -> time , &
locTime , 0 ) ; } { real_T up0 [ 3 ] ; up0 [ 0 ] = rtB . ndwlmk3bzn ; up0 [ 1
] = rtB . ixod0recqg ; up0 [ 2 ] = rtB . ezgferlgph ; rt_UpdateLogVar ( (
LogVar * ) var , up0 , 0 ) ; var = var -> next ; } { real_T up1 [ 1 ] ; up1 [
0 ] = rtB . gurfdczwyr ; rt_UpdateLogVar ( ( LogVar * ) var , up1 , 0 ) ; var
= var -> next ; } { real_T up2 [ 1 ] ; up2 [ 0 ] = rtB . bxgw3kq3ij ;
rt_UpdateLogVar ( ( LogVar * ) var , up2 , 0 ) ; var = var -> next ; } {
real_T up3 [ 1 ] ; up3 [ 0 ] = rtB . ixoqjsjjol ; rt_UpdateLogVar ( ( LogVar
* ) var , up3 , 0 ) ; var = var -> next ; } { real_T up4 [ 1 ] ; up4 [ 0 ] =
rtB . mnmkwbcoth ; rt_UpdateLogVar ( ( LogVar * ) var , up4 , 0 ) ; } } if (
ssGetLogOutput ( rtS ) ) { rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) ( rtDW
. ecx5etklyp . LoggedData ) , & rtB . jjsej1qngo , 0 ) ; } if ( ssIsSampleHit
( rtS , 2 , 0 ) ) { if ( ssGetLogOutput ( rtS ) ) { rt_UpdateLogVar ( (
LogVar * ) ( LogVar * ) ( rtDW . n4gmz4j4hp . LoggedData ) , & rtB .
jg43ge1e1q , 0 ) ; } } if ( ssGetLogOutput ( rtS ) ) { rt_UpdateLogVar ( (
LogVar * ) ( LogVar * ) ( rtDW . cjtu2gvfu3 . LoggedData ) , & rtB .
eyyzffon51 , 0 ) ; } if ( ssGetLogOutput ( rtS ) ) { rt_UpdateLogVar ( (
LogVar * ) ( LogVar * ) ( rtDW . kd250x2sgg . LoggedData ) , & rtB .
db3aloisol , 0 ) ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { if (
ssGetLogOutput ( rtS ) ) { rt_UpdateStructLogVar ( ( StructLogVar * ) rtDW .
cmlxapjojl . LoggedData , ( NULL ) , & rtB . faswnrxfir [ 0 ] ) ; } if (
ssGetLogOutput ( rtS ) ) { rt_UpdateStructLogVar ( ( StructLogVar * ) rtDW .
fdbzhbhm5w . LoggedData , ( NULL ) , & rtB . eu3n5piaim [ 0 ] ) ; } { double
locTime = ssGetTaskTime ( rtS , 2 ) ; if ( ssGetLogOutput ( rtS ) ) {
rt_UpdateStructLogVar ( ( StructLogVar * ) rtDW . j2kd5bha4b . LoggedData , &
locTime , & rtB . dgqpk3ff5k ) ; } } { double locTime = ssGetTaskTime ( rtS ,
2 ) ; if ( ssGetLogOutput ( rtS ) ) { rt_UpdateStructLogVar ( ( StructLogVar
* ) rtDW . jcasi5loyb . LoggedData , & locTime , & rtB . ixod0recqg ) ; } } {
double locTime = ssGetTaskTime ( rtS , 2 ) ; if ( ssGetLogOutput ( rtS ) ) {
rt_UpdateStructLogVar ( ( StructLogVar * ) rtDW . lscu5irxwr . LoggedData , &
locTime , & rtB . ptmfmdqmdu ) ; } } rtB . awinecmsma [ 0 ] = rtB .
asokdz5ql3 ; rtB . awinecmsma [ 1 ] = fwhtla1rft ; rtB . awinecmsma [ 2 ] =
rtB . ghtnph5m13 ; if ( ssGetLogOutput ( rtS ) ) { StructLogVar * svar = (
StructLogVar * ) rtDW . hnhslp1bvt . LoggedData ; LogVar * var = svar ->
signals . values ; { double locTime = ssGetTaskTime ( rtS , 2 ) ;
rt_UpdateLogVar ( ( LogVar * ) svar -> time , & locTime , 0 ) ; } { real_T
up0 [ 3 ] ; up0 [ 0 ] = rtB . awinecmsma [ 0 ] ; up0 [ 1 ] = rtB . awinecmsma
[ 1 ] ; up0 [ 2 ] = rtB . awinecmsma [ 2 ] ; rt_UpdateLogVar ( ( LogVar * )
var , up0 , 0 ) ; } } rtB . bxv0vvreuu [ 0 ] = duexjpu5rm_p ; rtB .
bxv0vvreuu [ 1 ] = c2fdcpgrsp ; rtB . bxv0vvreuu [ 2 ] = rtP . flowmin_Value
; } if ( ssGetLogOutput ( rtS ) ) { StructLogVar * svar = ( StructLogVar * )
rtDW . moxm2bblwy . LoggedData ; LogVar * var = svar -> signals . values ; {
double locTime = ssGetTaskTime ( rtS , 0 ) ; rt_UpdateLogVar ( ( LogVar * )
svar -> time , & locTime , 0 ) ; } { real_T up0 [ 4 ] ; up0 [ 0 ] = rtB .
bxv0vvreuu [ 0 ] ; up0 [ 1 ] = rtB . bxv0vvreuu [ 1 ] ; up0 [ 2 ] = rtB .
bxv0vvreuu [ 2 ] ; up0 [ 3 ] = rtB . ixoqjsjjol ; rt_UpdateLogVar ( ( LogVar
* ) var , up0 , 0 ) ; } } if ( ssGetLogOutput ( rtS ) ) { StructLogVar * svar
= ( StructLogVar * ) rtDW . auoyy55qok . LoggedData ; LogVar * var = svar ->
signals . values ; { double locTime = ssGetTaskTime ( rtS , 0 ) ;
rt_UpdateLogVar ( ( LogVar * ) svar -> time , & locTime , 0 ) ; } { real_T
up0 [ 1 ] ; up0 [ 0 ] = rtB . p2d41sdffb [ 1 ] ; rt_UpdateLogVar ( ( LogVar *
) var , up0 , 0 ) ; } } rtB . crgbyrrs3v = rtB . p2d41sdffb [ 0 ] * rtB .
p2d41sdffb [ 1 ] * rtP . Gain1_Gain_kphh4wmlkt * rtP . Gain5_Gain ; if (
ssGetLogOutput ( rtS ) ) { StructLogVar * svar = ( StructLogVar * ) rtDW .
pd2fs1ditr . LoggedData ; LogVar * var = svar -> signals . values ; { double
locTime = ssGetTaskTime ( rtS , 0 ) ; rt_UpdateLogVar ( ( LogVar * ) svar ->
time , & locTime , 0 ) ; } { real_T up0 [ 1 ] ; up0 [ 0 ] = rtB . crgbyrrs3v
; rt_UpdateLogVar ( ( LogVar * ) var , up0 , 0 ) ; } } if ( ssIsSampleHit (
rtS , 2 , 0 ) ) { rtB . m2zzbwcwm4 [ 0 ] = pwkaxiafxx ; rtB . m2zzbwcwm4 [ 1
] = fzccphw1bz ; if ( ssGetLogOutput ( rtS ) ) { StructLogVar * svar = (
StructLogVar * ) rtDW . lyifwmtiaf . LoggedData ; LogVar * var = svar ->
signals . values ; { double locTime = ssGetTaskTime ( rtS , 2 ) ;
rt_UpdateLogVar ( ( LogVar * ) svar -> time , & locTime , 0 ) ; } { real_T
up0 [ 2 ] ; up0 [ 0 ] = rtB . m2zzbwcwm4 [ 0 ] ; up0 [ 1 ] = rtB . m2zzbwcwm4
[ 1 ] ; rt_UpdateLogVar ( ( LogVar * ) var , up0 , 0 ) ; } } rtB . emjllewz5k
[ 0 ] = rtB . j0uztscc4c ; rtB . emjllewz5k [ 1 ] = g1ekzbu3oi ; rtB .
emjllewz5k [ 2 ] = rtB . nslfibkrov ; if ( ssGetLogOutput ( rtS ) ) {
StructLogVar * svar = ( StructLogVar * ) rtDW . n2no12labo . LoggedData ;
LogVar * var = svar -> signals . values ; { double locTime = ssGetTaskTime (
rtS , 2 ) ; rt_UpdateLogVar ( ( LogVar * ) svar -> time , & locTime , 0 ) ; }
{ real_T up0 [ 3 ] ; up0 [ 0 ] = rtB . emjllewz5k [ 0 ] ; up0 [ 1 ] = rtB .
emjllewz5k [ 1 ] ; up0 [ 2 ] = rtB . emjllewz5k [ 2 ] ; rt_UpdateLogVar ( (
LogVar * ) var , up0 , 0 ) ; } } rtB . aisp4eno0x [ 0 ] = hde10siz3b_idx_0 ;
rtB . aisp4eno0x [ 1 ] = hde10siz3b_idx_1 ; if ( ssGetLogOutput ( rtS ) ) {
StructLogVar * svar = ( StructLogVar * ) rtDW . jhwi52suok . LoggedData ;
LogVar * var = svar -> signals . values ; { double locTime = ssGetTaskTime (
rtS , 2 ) ; rt_UpdateLogVar ( ( LogVar * ) svar -> time , & locTime , 0 ) ; }
{ real_T up0 [ 2 ] ; up0 [ 0 ] = rtB . aisp4eno0x [ 0 ] ; up0 [ 1 ] = rtB .
aisp4eno0x [ 1 ] ; rt_UpdateLogVar ( ( LogVar * ) var , up0 , 0 ) ; } } rtB .
ji51d50do5 [ 0 ] = rtB . gyejnsfev5 ; rtB . ji51d50do5 [ 1 ] = batdnpsvim ;
if ( ssGetLogOutput ( rtS ) ) { StructLogVar * svar = ( StructLogVar * ) rtDW
. iesioivz5z . LoggedData ; LogVar * var = svar -> signals . values ; {
double locTime = ssGetTaskTime ( rtS , 2 ) ; rt_UpdateLogVar ( ( LogVar * )
svar -> time , & locTime , 0 ) ; } { real_T up0 [ 2 ] ; up0 [ 0 ] = rtB .
ji51d50do5 [ 0 ] ; up0 [ 1 ] = rtB . ji51d50do5 [ 1 ] ; rt_UpdateLogVar ( (
LogVar * ) var , up0 , 0 ) ; } } if ( ssGetLogOutput ( rtS ) ) { StructLogVar
* svar = ( StructLogVar * ) rtDW . jhe31dgiau . LoggedData ; LogVar * var =
svar -> signals . values ; { double locTime = ssGetTaskTime ( rtS , 2 ) ;
rt_UpdateLogVar ( ( LogVar * ) svar -> time , & locTime , 0 ) ; } { int32_T
up0 [ 1 ] ; up0 [ 0 ] = rtB . dgqpk3ff5k ; rt_UpdateLogVar ( ( LogVar * ) var
, up0 , 0 ) ; } } rtB . leav20jvu1 = rtB . eu3n5piaim [ 2 ] ; if (
ssGetLogOutput ( rtS ) ) { StructLogVar * svar = ( StructLogVar * ) rtDW .
ojkakflagz . LoggedData ; LogVar * var = svar -> signals . values ; { double
locTime = ssGetTaskTime ( rtS , 2 ) ; rt_UpdateLogVar ( ( LogVar * ) svar ->
time , & locTime , 0 ) ; } { real_T up0 [ 1 ] ; up0 [ 0 ] = rtB . leav20jvu1
; rt_UpdateLogVar ( ( LogVar * ) var , up0 , 0 ) ; } } } exgwciklzi = rtP .
Gain6_Gain * rtB . crgbyrrs3v ; kojspa505o = rtX . cgw3asjtrv ; efj5q5ebcq =
exgwciklzi / ( jalnkh4fhi + exgwciklzi ) ; gjrh3vhxv1 = ( ( rtP .
conversiontoRPM_Gain_jcb4d3q1ao * b11wdxnlxt * rtP .
Constant3_Value_jljz3p1fkf [ 2 ] * efj5q5ebcq + ( rtP .
Constant3_Value_jljz3p1fkf [ 1 ] * efj5q5ebcq + rtP .
Constant3_Value_jljz3p1fkf [ 0 ] ) ) + rtP . Constant3_Value_jljz3p1fkf [ 3 ]
* rtX . cgw3asjtrv ) + imz3hxnyez ; aktecqyana = ( rtX . cgw3asjtrv *
jalnkh4fhi + 15.6 * exgwciklzi ) / ( exgwciklzi + jalnkh4fhi ) ; if (
aktecqyana > rtP . Saturation_UpperSat_mderhtvsta ) { aktecqyana = rtP .
Saturation_UpperSat_mderhtvsta ; } else { if ( aktecqyana < rtP .
Saturation_LowerSat_na0sdh24gx ) { aktecqyana = rtP .
Saturation_LowerSat_na0sdh24gx ; } } nxbnma2b0r = exgwciklzi + jalnkh4fhi ;
if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { o0swabdreh = orelggziy4 ; l01ja1voo4 =
rtB . jnglkal4bm ; rtB . ohwrf1raz0 = rtB . mr2jn5bxm5 ; } n4kbehhhau = rtP .
Gain_Gain_mac0nz3shk * rtB . ezgferlgph ; o5ibp43cp4 = rtP .
Gain1_Gain_nxm3m0oimc * npiyznthqi ; { real_T t = ssGetTaskTime ( rtS , 0 ) ;
real_T * pTimeValues = ( real_T * ) rtDW . alrdv1eret . TimePtr ; real_T *
pDataValues = ( real_T * ) rtDW . alrdv1eret . DataPtr ; int numPoints ,
lastPoint ; FWksInfo * fromwksInfo = ( FWksInfo * ) rtDW . alrdv1eret .
RSimInfoPtr ; numPoints = fromwksInfo -> nDataPoints ; lastPoint = numPoints
- 1 ; if ( t < pTimeValues [ 0 ] ) { hm5icraqc0 = 0.0 ; } else if ( t >=
pTimeValues [ lastPoint ] ) { hm5icraqc0 = pDataValues [ lastPoint ] ; } else
{ int_T currTimeIndex = rtDW . khael42orb . PrevIndex ; if ( t < pTimeValues
[ currTimeIndex ] ) { while ( t < pTimeValues [ currTimeIndex ] ) {
currTimeIndex -- ; } } else { while ( t >= pTimeValues [ currTimeIndex + 1 ]
) { currTimeIndex ++ ; } } hm5icraqc0 = pDataValues [ currTimeIndex ] ; rtDW
. khael42orb . PrevIndex = currTimeIndex ; } } efj5q5ebcq = j1s5yn2ijo -
hm5icraqc0 ; bguiqh0znq = ( efj5q5ebcq * efj5q5ebcq * rtP .
Constant_Value_nytnoeucmv [ 0 ] + rtP . Constant_Value_nytnoeucmv [ 1 ] *
efj5q5ebcq ) + rtP . Constant_Value_nytnoeucmv [ 2 ] ; if ( ssIsSampleHit (
rtS , 2 , 0 ) ) { rtB . ejc4fyifu5 = rtP . Gain_Gain_hyiakb1knr * rtB .
duoa5br5cp ; } npiyznthqi = rtP . conversiontoRPM_Gain_mcxghe0z0j *
b11wdxnlxt ; dks5dd4n1g = rtP . Gain1_Gain_jsikeibefk * npiyznthqi ;
etyvz2h2c5 ( rtB . ejc4fyifu5 , dks5dd4n1g , rtP . Constant6_Value_mf5czz2ry0
, rtP . Constant2_Value_famev12dvd , rtP . Constant7_Value_ev42suj2mv , rtP .
Constant8_Value_jnqtvlutwj , & rtB . eso2sg3fe3 ) ; if ( ssIsSampleHit ( rtS
, 2 , 0 ) ) { rtB . pfzxy051h0 = rtP . Gain_Gain_c04eta5jei * rtB .
duoa5br5cp ; } dbdkq3qiib = rtP . Gain1_Gain_i3scwfulpa * npiyznthqi ;
etyvz2h2c5 ( rtB . pfzxy051h0 , dbdkq3qiib , rtP . Constant6_Value_k0ew1yhaa2
, rtP . Constant2_Value_ldq5tfox0g , rtP . Constant7_Value_c5zkgrzq1z , rtP .
Constant8_Value_jpnyl202ps , & rtB . k511l1m2xq ) ; if ( 1.0 / n4kbehhhau *
o5ibp43cp4 >= rtP . Switch_Threshold_l51av4ct4h ) { efj5q5ebcq = n4kbehhhau /
o5ibp43cp4 ; if ( efj5q5ebcq > rtP . Switch1_Threshold_l55imt4c03 ) { if (
efj5q5ebcq > rtP . Saturation1_UpperSat_f1otdzijdo ) { efj5q5ebcq = rtP .
Saturation1_UpperSat_f1otdzijdo ; } else { if ( efj5q5ebcq < rtP .
Saturation1_LowerSat_cp0nvaxf44 ) { efj5q5ebcq = rtP .
Saturation1_LowerSat_cp0nvaxf44 ; } } efj5q5ebcq = ( ( 1.0 - efj5q5ebcq ) *
0.14285714285714282 + efj5q5ebcq ) * ( 1.0 - efj5q5ebcq ) ; if ( efj5q5ebcq <
0.0 ) { o5iftc4ajm = - muDoubleScalarSqrt ( - efj5q5ebcq ) ; } else {
o5iftc4ajm = muDoubleScalarSqrt ( efj5q5ebcq ) ; } } else { o5iftc4ajm = rtP
. Constant1_Value_imn1hkkgc1 ; } efj5q5ebcq = o5ibp43cp4 / bguiqh0znq / rtP .
Ra_Value_kj3pmm4raq * o5ibp43cp4 * rtP . Gain2_Gain_euknr0ejrc ; if (
efj5q5ebcq < 0.0 ) { efj5q5ebcq = - muDoubleScalarSqrt ( muDoubleScalarAbs (
efj5q5ebcq ) ) ; } else { efj5q5ebcq = muDoubleScalarSqrt ( efj5q5ebcq ) ; }
if ( rtB . eso2sg3fe3 . e2b5x1uxlg > rtP . Saturation_UpperSat_c3vbgn0h23 ) {
ppfiifg3xk_idx_1 = rtP . Saturation_UpperSat_c3vbgn0h23 ; } else if ( rtB .
eso2sg3fe3 . e2b5x1uxlg < rtP . Saturation_LowerSat_oqjcpbpiw2 ) {
ppfiifg3xk_idx_1 = rtP . Saturation_LowerSat_oqjcpbpiw2 ; } else {
ppfiifg3xk_idx_1 = rtB . eso2sg3fe3 . e2b5x1uxlg ; } npiyznthqi = efj5q5ebcq
* ppfiifg3xk_idx_1 * o5iftc4ajm * rtP . tokgps1_Gain_ieeppbarz5 ; } else {
efj5q5ebcq = 1.0 / n4kbehhhau * o5ibp43cp4 ; if ( efj5q5ebcq > rtP .
Switch1_Threshold ) { if ( efj5q5ebcq > rtP . Saturation1_UpperSat ) {
efj5q5ebcq = rtP . Saturation1_UpperSat ; } else { if ( efj5q5ebcq < rtP .
Saturation1_LowerSat ) { efj5q5ebcq = rtP . Saturation1_LowerSat ; } }
efj5q5ebcq = ( ( 1.0 - efj5q5ebcq ) * 0.14285714285714282 + efj5q5ebcq ) * (
1.0 - efj5q5ebcq ) ; if ( efj5q5ebcq < 0.0 ) { o5iftc4ajm = -
muDoubleScalarSqrt ( - efj5q5ebcq ) ; } else { o5iftc4ajm =
muDoubleScalarSqrt ( efj5q5ebcq ) ; } } else { o5iftc4ajm = rtP .
Constant1_Value_fu0eog2bs5 ; } efj5q5ebcq = n4kbehhhau / bguiqh0znq / rtP .
Ra_Value_kj3pmm4raq * n4kbehhhau * rtP . Gain2_Gain ; if ( efj5q5ebcq < 0.0 )
{ efj5q5ebcq = - muDoubleScalarSqrt ( muDoubleScalarAbs ( efj5q5ebcq ) ) ; }
else { efj5q5ebcq = muDoubleScalarSqrt ( efj5q5ebcq ) ; } if ( rtB .
k511l1m2xq . e2b5x1uxlg > rtP . Saturation_UpperSat ) { ppfiifg3xk_idx_1 =
rtP . Saturation_UpperSat ; } else if ( rtB . k511l1m2xq . e2b5x1uxlg < rtP .
Saturation_LowerSat ) { ppfiifg3xk_idx_1 = rtP . Saturation_LowerSat ; } else
{ ppfiifg3xk_idx_1 = rtB . k511l1m2xq . e2b5x1uxlg ; } npiyznthqi =
efj5q5ebcq * ppfiifg3xk_idx_1 * o5iftc4ajm * rtP . tokgps1_Gain * rtP .
Gain_Gain ; } if ( npiyznthqi > rtP . Saturation_UpperSat_ar1iwsjf3t ) {
npiyznthqi = rtP . Saturation_UpperSat_ar1iwsjf3t ; } else { if ( npiyznthqi
< rtP . Saturation_LowerSat_idpgnii55n ) { npiyznthqi = rtP .
Saturation_LowerSat_idpgnii55n ; } } ppxu00rks2 = rtP . gain_Gain *
lgp0omksql ; o5iftc4ajm = ( ( ( ( 0.43860691 * rtB . mnmkwbcoth + - 1283.1169
) + 10.249443 * ppxu00rks2 ) + 4.7302501 * hm5icraqc0 ) + 4.3259397e-5 *
muDoubleScalarPower ( rtB . mnmkwbcoth , 2.0 ) ) + - 0.13127391 *
muDoubleScalarPower ( ppxu00rks2 , 2.0 ) ; { real_T t = ssGetTaskTime ( rtS ,
0 ) ; real_T * pTimeValues = ( real_T * ) rtDW . p1e0b0rkdr . TimePtr ;
real_T * pDataValues = ( real_T * ) rtDW . p1e0b0rkdr . DataPtr ; int
numPoints , lastPoint ; FWksInfo * fromwksInfo = ( FWksInfo * ) rtDW .
p1e0b0rkdr . RSimInfoPtr ; numPoints = fromwksInfo -> nDataPoints ; lastPoint
= numPoints - 1 ; if ( t < pTimeValues [ 0 ] ) { h3vwhozvjv = 0.0 ; } else if
( t >= pTimeValues [ lastPoint ] ) { h3vwhozvjv = pDataValues [ lastPoint ] ;
} else { int_T currTimeIndex = rtDW . bi4mdaymdj . PrevIndex ; if ( t <
pTimeValues [ currTimeIndex ] ) { while ( t < pTimeValues [ currTimeIndex ] )
{ currTimeIndex -- ; } } else { while ( t >= pTimeValues [ currTimeIndex + 1
] ) { currTimeIndex ++ ; } } h3vwhozvjv = pDataValues [ currTimeIndex ] ;
rtDW . bi4mdaymdj . PrevIndex = currTimeIndex ; } } { real_T t =
ssGetTaskTime ( rtS , 0 ) ; real_T * pTimeValues = ( real_T * ) rtDW .
clwukip414 . TimePtr ; real_T * pDataValues = ( real_T * ) rtDW . clwukip414
. DataPtr ; int numPoints , lastPoint ; FWksInfo * fromwksInfo = ( FWksInfo *
) rtDW . clwukip414 . RSimInfoPtr ; numPoints = fromwksInfo -> nDataPoints ;
lastPoint = numPoints - 1 ; if ( t < pTimeValues [ 0 ] ) { hy0nvl42ff = 0.0 ;
} else if ( t >= pTimeValues [ lastPoint ] ) { hy0nvl42ff = pDataValues [
lastPoint ] ; } else { int_T currTimeIndex = rtDW . d1tbd3ecab . PrevIndex ;
if ( t < pTimeValues [ currTimeIndex ] ) { while ( t < pTimeValues [
currTimeIndex ] ) { currTimeIndex -- ; } } else { while ( t >= pTimeValues [
currTimeIndex + 1 ] ) { currTimeIndex ++ ; } } hy0nvl42ff = pDataValues [
currTimeIndex ] ; rtDW . d1tbd3ecab . PrevIndex = currTimeIndex ; } }
efj5q5ebcq = rtP . conversiontoRPM1_Gain * b11wdxnlxt ; if ( hy0nvl42ff > 1.5
) { rtB . ivmstlzdxm = ( ( ( ( ( ( rtP . Constant_Value_hjtsi0eo30 [ 1 ] *
o5iftc4ajm + rtP . Constant_Value_hjtsi0eo30 [ 0 ] ) + rtP .
Constant_Value_hjtsi0eo30 [ 2 ] * lgp0omksql ) + rtP .
Constant_Value_hjtsi0eo30 [ 3 ] * efj5q5ebcq ) + o5iftc4ajm * o5iftc4ajm *
rtP . Constant_Value_hjtsi0eo30 [ 4 ] ) + lgp0omksql * lgp0omksql * rtP .
Constant_Value_hjtsi0eo30 [ 5 ] ) + efj5q5ebcq * efj5q5ebcq * rtP .
Constant_Value_hjtsi0eo30 [ 6 ] ) * ( h3vwhozvjv - o5iftc4ajm ) / 100.0 +
o5iftc4ajm ; } else { rtB . ivmstlzdxm = rtP . Constant1_Value_dfgbihyjmh [ 1
] * o5iftc4ajm + rtP . Constant1_Value_dfgbihyjmh [ 0 ] ; } ppxu00rks2 =
jalnkh4fhi + exgwciklzi ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB .
ikbnonbcrn = ( 1369.19425815691 * muDoubleScalarPower ( rtDW . h1201vgmm4 ,
2.0 ) + 35.4540616064791 * rtDW . h1201vgmm4 ) + 97.0096843671075 ; }
lc44cjozax = rtP . conversiontoRPM_Gain_c31itt1fpi * rtB . gurfdczwyr ;
ppfiifg3xk_idx_1 = rtP . Constant13_Value ; tmp_i [ 0 ] = 0.0001 ; tmp_i [ 1
] = rtB . ikbnonbcrn / rtB . ndwlmk3bzn ; tmp_i [ 2 ] = 0.97 ; PR =
m0rufl5oqo ( tmp_i ) ; PhiC = ( ( ( rtP . Constant8_Value_oi5cuui1pe [ 1 ] *
rtB . jg43ge1e1q + rtP . Constant8_Value_oi5cuui1pe [ 0 ] ) + rtP .
Constant8_Value_oi5cuui1pe [ 2 ] * lc44cjozax ) + rtB . jg43ge1e1q * rtB .
jg43ge1e1q * rtP . Constant8_Value_oi5cuui1pe [ 3 ] ) + lc44cjozax *
lc44cjozax * rtP . Constant8_Value_oi5cuui1pe [ 4 ] ; if ( PR >
muDoubleScalarPower ( ( rtP . Constant11_Value + 1.0 ) / 2.0 , rtP .
Constant11_Value / ( 1.0 - rtP . Constant11_Value ) ) ) { efj5q5ebcq =
muDoubleScalarSqrt ( ( muDoubleScalarPower ( PR , 2.0 / rtP .
Constant11_Value ) - muDoubleScalarPower ( PR , ( rtP . Constant11_Value +
1.0 ) / rtP . Constant11_Value ) ) * ( 2.0 * rtP . Constant11_Value / ( rtP .
Constant11_Value - 1.0 ) ) ) ; } else { efj5q5ebcq = 0.6847 ; } tmp_e [ 0 ] =
1.0E-5 ; tmp_e [ 1 ] = efj5q5ebcq * PhiC ; tmp_e [ 2 ] = 0.2 ; n4kbehhhau =
m0rufl5oqo ( tmp_e ) ; tmp_p [ 0 ] = 100.0 ; tmp_p [ 1 ] = rtB . mnmkwbcoth ;
tmp_p [ 2 ] = 2000.0 ; o5ibp43cp4 = m0rufl5oqo ( tmp_p ) ; tmp [ 0 ] = 50.0 ;
tmp [ 1 ] = rtB . ndwlmk3bzn ; tmp [ 2 ] = 1000.0 ; exgwciklzi = n4kbehhhau *
m0rufl5oqo ( tmp ) / muDoubleScalarSqrt ( o5ibp43cp4 ) ; efj5q5ebcq =
3.1415926535897931 * rtP . Constant7_Value_lsrcvwaode * lc44cjozax / (
muDoubleScalarSqrt ( ( 1.0 - muDoubleScalarPower ( PR , ( rtP .
Constant11_Value - 1.0 ) / rtP . Constant11_Value ) ) * ( 2.0 * rtP .
Constant13_Value * o5ibp43cp4 ) ) * 60.0 ) ; efj5q5ebcq = ( ( ( ( ( rtP .
Constant9_Value_jt0hblxo1l [ 1 ] * efj5q5ebcq + rtP .
Constant9_Value_jt0hblxo1l [ 0 ] ) + rtP . Constant9_Value_jt0hblxo1l [ 2 ] *
PR ) + rtP . Constant9_Value_jt0hblxo1l [ 3 ] * rtB . jg43ge1e1q ) +
efj5q5ebcq * efj5q5ebcq * rtP . Constant9_Value_jt0hblxo1l [ 4 ] ) + PR * PR
* rtP . Constant9_Value_jt0hblxo1l [ 5 ] ) + rtB . jg43ge1e1q * rtB .
jg43ge1e1q * rtP . Constant9_Value_jt0hblxo1l [ 6 ] ; o5iftc4ajm = o5ibp43cp4
- efj5q5ebcq ; buuq3qgkl1 = ( 1.0 - o5iftc4ajm / o5ibp43cp4 ) / ( 1.0 -
muDoubleScalarPower ( PR , 0.2857 ) ) ; rtB . kdbgmjpooy = exgwciklzi ;
nt2j3jtq0u = o5iftc4ajm ; fcjivgpr4n = PhiC ; lfikko4x3f = n4kbehhhau ;
pcimxyw44x = efj5q5ebcq ; rtB . pl42gnrwz2 = ( ( ppxu00rks2 - rtB .
kdbgmjpooy ) - lgp0omksql ) * rtP . exhaustmanifoldvolume_Gain ; rtB .
bfvor2h2qz = 1.0 / ( rtP . exhaustmanifoldvolume_Gain_bcvpqqb1p5 * gen03hfvbg
) * ( ( aktecqyana - rtX . ge52s03ms5 ) * ppxu00rks2 ) ; ppxu00rks2 = ( (
ppxu00rks2 * gjrh3vhxv1 - rtB . kdbgmjpooy * rtB . mnmkwbcoth ) - lgp0omksql
* rtB . mnmkwbcoth ) - ( gjrh3vhxv1 - hm5icraqc0 ) * ppxu00rks2 * rtP .
k_heat_W_Gain / 1.004 ; rtB . e1xcvnjj5g = rtP . gammaR_air_Gain * ppxu00rks2
/ rtP . exhaust_manifold_vol_Value ; rtB . loievit34u = ( ( npiyznthqi +
lgp0omksql ) - jalnkh4fhi ) * rtP . intakemanifoldvolume_Gain ; rtB .
eplj1scayr = ( ( rtX . ge52s03ms5 - kojspa505o ) * lgp0omksql - npiyznthqi *
kojspa505o ) * ( 1.0 / ( rtP . intakemanifoldvolume1_Gain * kmz3ui0uz0 ) ) ;
rtB . b54muslow1 = ( ( npiyznthqi * bguiqh0znq + lgp0omksql * rtB .
ivmstlzdxm ) - imz3hxnyez * jalnkh4fhi ) * rtP . gammaR_air_Gain_gxlwxkgn4a /
rtP . Intake_manifold_vol_Value ; rtB . oe0tyrtgj3 = ( 1.6e-9 *
muDoubleScalarPower ( rtB . gurfdczwyr , 2.0 ) + - 1.82444404829743e-6 * rtB
. gurfdczwyr ) + 0.002 ; if ( ssGetLogOutput ( rtS ) ) { { void *
pSignalProbeCollection = ( void * ) rtDW . dcyih1kpjy . SignalProbe ; if (
rtwSignalProbeCollectionGetLoggingIsOn ( pSignalProbeCollection ) ) { {
real_T t ; void * pData ; t = ssGetTaskTime ( rtS , 0 ) ; pData = ( void * )
& rtB . oe0tyrtgj3 ; rtwSignalProbeCollectionAppendSample (
pSignalProbeCollection , 0 , t , pData ) ; } } } } rtB . aebqkvtnky = ( rtB .
gurfdczwyr <= rtP . Constant_Value_hh24nrqhdu ) ; if ( ssIsSampleHit ( rtS ,
1 , 0 ) && rtB . aebqkvtnky ) { ssSetStopRequested ( rtS , 1 ) ; } if (
ssGetLogOutput ( rtS ) ) { rt_UpdateLogVar ( ( LogVar * ) ( LogVar * ) ( rtDW
. bdj3wmcbnu . LoggedData ) , & rtB . oe0tyrtgj3 , 0 ) ; } rtB . jkv43wgavw =
( ( ppfiifg3xk_idx_1 * exgwciklzi * efj5q5ebcq * 60.0 / ( 6.2831853071795862
* lc44cjozax ) - rtB . oe0tyrtgj3 ) - ll4keb2h0s_idx_3 * W_comp *
delta_T_comp * 60.0 / ( 6.2831853071795862 * beiewzgadl ) ) * rtP .
J_turbo_Gain ; { real_T t = ssGetTaskTime ( rtS , 0 ) ; real_T * pTimeValues
= ( real_T * ) rtDW . d5tz0vp4gc . TimePtr ; real_T * pDataValues = ( real_T
* ) rtDW . d5tz0vp4gc . DataPtr ; int numPoints , lastPoint ; FWksInfo *
fromwksInfo = ( FWksInfo * ) rtDW . d5tz0vp4gc . RSimInfoPtr ; numPoints =
fromwksInfo -> nDataPoints ; lastPoint = numPoints - 1 ; if ( t < pTimeValues
[ 0 ] ) { alnmoyh0xt = 0.0 ; } else if ( t >= pTimeValues [ lastPoint ] ) {
alnmoyh0xt = pDataValues [ lastPoint ] ; } else { int_T currTimeIndex = rtDW
. aloadsnzst . PrevIndex ; if ( t < pTimeValues [ currTimeIndex ] ) { while (
t < pTimeValues [ currTimeIndex ] ) { currTimeIndex -- ; } } else { while ( t
>= pTimeValues [ currTimeIndex + 1 ] ) { currTimeIndex ++ ; } } alnmoyh0xt =
pDataValues [ currTimeIndex ] ; rtDW . aloadsnzst . PrevIndex = currTimeIndex
; } } { real_T t = ssGetTaskTime ( rtS , 0 ) ; real_T * pTimeValues = (
real_T * ) rtDW . ozs1urzqbb . TimePtr ; real_T * pDataValues = ( real_T * )
rtDW . ozs1urzqbb . DataPtr ; int numPoints , lastPoint ; FWksInfo *
fromwksInfo = ( FWksInfo * ) rtDW . ozs1urzqbb . RSimInfoPtr ; numPoints =
fromwksInfo -> nDataPoints ; lastPoint = numPoints - 1 ; if ( t < pTimeValues
[ 0 ] ) { iwi45oum3a = 0.0 ; } else if ( t >= pTimeValues [ lastPoint ] ) {
iwi45oum3a = pDataValues [ lastPoint ] ; } else { int_T currTimeIndex = rtDW
. fzvbkpkm44 . PrevIndex ; if ( t < pTimeValues [ currTimeIndex ] ) { while (
t < pTimeValues [ currTimeIndex ] ) { currTimeIndex -- ; } } else { while ( t
>= pTimeValues [ currTimeIndex + 1 ] ) { currTimeIndex ++ ; } } iwi45oum3a =
pDataValues [ currTimeIndex ] ; rtDW . fzvbkpkm44 . PrevIndex = currTimeIndex
; } } rtB . cuwv2nwel5 = ( rtB . bxgw3kq3ij - npiyznthqi ) * bguiqh0znq * rtP
. gammaRV_preThrottle_Gain ; { real_T t = ssGetTaskTime ( rtS , 0 ) ; real_T
* pTimeValues = ( real_T * ) rtDW . jfbqvyxdrm . TimePtr ; real_T *
pDataValues = ( real_T * ) rtDW . jfbqvyxdrm . DataPtr ; int numPoints ,
lastPoint ; FWksInfo * fromwksInfo = ( FWksInfo * ) rtDW . jfbqvyxdrm .
RSimInfoPtr ; numPoints = fromwksInfo -> nDataPoints ; lastPoint = numPoints
- 1 ; if ( t < pTimeValues [ 0 ] ) { rtB . py5osja1pm = 0.0 ; } else if ( t
>= pTimeValues [ lastPoint ] ) { rtB . py5osja1pm = pDataValues [ lastPoint ]
; } else { int_T currTimeIndex = rtDW . gyhzvvm031 . PrevIndex ; if ( t <
pTimeValues [ currTimeIndex ] ) { while ( t < pTimeValues [ currTimeIndex ] )
{ currTimeIndex -- ; } } else { while ( t >= pTimeValues [ currTimeIndex + 1
] ) { currTimeIndex ++ ; } } rtB . py5osja1pm = pDataValues [ currTimeIndex ]
; rtDW . gyhzvvm031 . PrevIndex = currTimeIndex ; } } if ( ssIsSampleHit (
rtS , 4 , 0 ) ) { rtB . fto5rqjonq = rtDW . beiefj4kfo ; } if ( ssIsSampleHit
( rtS , 5 , 0 ) ) { rtB . ndy320v1c1 = rtDW . d2tl5o0hel ; } UNUSED_PARAMETER
( tid ) ; } void MdlUpdate ( int_T tid ) { if ( ssIsSampleHit ( rtS , 1 , 0 )
) { rtDW . cc0wkfbxf2 = rtB . ivmstlzdxm ; rtDW . eac1jvpkom = rtB .
ohwrf1raz0 ; } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { foiteff4aq ( rtB .
fto5rqjonq , & rtDW . masm1qwyo5u ) ; foiteff4aq ( rtB . ndy320v1c1 , & rtDW
. cdbewnv5xj ) ; foiteff4aq ( rtB . py5osja1pm , & rtDW . lwrmmrtmge ) ; } if
( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW . avtbwzqnkf [ 0 ] = rtB .
dwx51vir01 [ 0 ] ; rtDW . avtbwzqnkf [ 1 ] = rtB . dwx51vir01 [ 1 ] ; rtDW .
poa5fptxm4 = rtB . jnglkal4bm ; rtDW . bsbxmlf10r = rtB . mr2jn5bxm5 ; rtDW .
pybwwu5s4d = rtB . j0uztscc4c ; rtDW . j5f3ay4xaq = rtB . dtnj1tjnn0 ; rtDW .
ackerqxqlr = rtB . dtnj1tjnn0 ; rtDW . c1qvpfpyqu = rtB . j0uztscc4c ; rtDW .
em10zry3vm = rtB . asokdz5ql3 ; rtDW . cz55ow2si1 [ 0 ] = rtB . mebfpuov3e [
0 ] ; rtDW . cz55ow2si1 [ 1 ] = rtB . mebfpuov3e [ 1 ] ; rtDW . cz55ow2si1 [
2 ] = rtB . mebfpuov3e [ 2 ] ; rtDW . h4gbii3cbq = rtB . lsc4svyhjg ; rtDW .
o04t4yciip = rtB . a5xydgx2md ; rtDW . lzwd5z4dbk = rtB . dkpngqys4z ; rtDW .
dgfekwwlr1 = rtB . o2frmjlatg ; rtDW . dw2dt5amj1 = rtB . ighfnj0qfi ; rtDW .
letoggxozl = rtB . ljk4xix01m ; rtDW . frjwyakiph = rtB . lvfxs442og ; rtDW .
i5yn1movmy = rtB . gkalf2lwvh ; rtDW . diffnla35e = rtB . ntcwr4dn2u ; rtDW .
nqyjhyuvcj = rtB . pqqblejffn ; rtDW . fjcoqtw2bx = rtB . jzzd4u2sum ; rtDW .
iggiejtmqu = rtB . lluxiqhlvi ; rtDW . mvpjwhrzk3 = rtB . lqzoneosua ; rtDW .
mtqhixagy1 = rtB . gy1swsl5lp ; rtDW . fhgbtmls3d = rtB . lxrst0kqri ; rtDW .
l1sigmyvxe = rtB . dtn0co1rlo ; rtDW . noqny2ee14 = rtB . j0uztscc4c ; rtDW .
ljbykua013 = rtB . asokdz5ql3 ; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW
. h1201vgmm4 = rtB . kdbgmjpooy ; } if ( ssIsSampleHit ( rtS , 4 , 0 ) ) {
rtDW . beiefj4kfo = ( rtP . UniformRandomNumber_Maximum - rtP .
UniformRandomNumber_Minimum ) * rt_urand_Upu32_Yd_f_pw_snf ( & rtDW .
msu4qgbkxt ) + rtP . UniformRandomNumber_Minimum ; } if ( ssIsSampleHit ( rtS
, 5 , 0 ) ) { rtDW . d2tl5o0hel = ( rtP . UniformRandomNumber1_Maximum - rtP
. UniformRandomNumber1_Minimum ) * rt_urand_Upu32_Yd_f_pw_snf ( & rtDW .
grioepryal ) + rtP . UniformRandomNumber1_Minimum ; } UNUSED_PARAMETER ( tid
) ; } void MdlDerivatives ( void ) { XDot * _rtXdot ; _rtXdot = ( ( XDot * )
ssGetdX ( rtS ) ) ; _rtXdot -> mupnfilrqo = rtB . b54muslow1 ; _rtXdot ->
huyhg2ps31 = rtB . e1xcvnjj5g ; _rtXdot -> lgbs44xptg = rtB . cuwv2nwel5 ;
_rtXdot -> ka43gmkysq = rtB . jkv43wgavw ; _rtXdot -> iqp0o3u0ph = rtB .
loievit34u ; _rtXdot -> iynqfp2xbi = rtB . pl42gnrwz2 ; _rtXdot -> cgw3asjtrv
= rtB . eplj1scayr ; _rtXdot -> ge52s03ms5 = rtB . bfvor2h2qz ; } void
MdlProjection ( void ) { } void MdlTerminate ( void ) { rt_FREE ( rtDW .
hvzkbecm4i . RSimInfoPtr ) ; rt_FREE ( rtDW . b2ezf5nkn2 . RSimInfoPtr ) ;
rt_FREE ( rtDW . dlyfy0ipc5 . RSimInfoPtr ) ; rt_FREE ( rtDW . oi2egj2zap .
RSimInfoPtr ) ; { void * pSignalProbeCollection = ( void * ) rtDW .
jllpsh2lx2 . SignalProbe ; const char * fileName =
rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } { void * pSignalProbeCollection = ( void * ) rtDW . kjuost3l4t .
SignalProbe ; const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } { void * pSignalProbeCollection = ( void * ) rtDW . gegk3zt5rh .
SignalProbe ; const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } { void * pSignalProbeCollection = ( void * ) rtDW . br3dyaxwzn .
SignalProbe ; const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } { void * pSignalProbeCollection = ( void * ) rtDW . msk43x33qs .
SignalProbe ; const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } { void * pSignalProbeCollection = ( void * ) rtDW . aiqcj0xpj3 .
SignalProbe ; const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } { void * pSignalProbeCollection = ( void * ) rtDW . imyl4toc4j .
SignalProbe ; const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } { void * pSignalProbeCollection = ( void * ) rtDW . juk00hf1bn .
SignalProbe ; const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } { void * pSignalProbeCollection = ( void * ) rtDW . prcjjqdyp5 .
SignalProbe ; const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } { void * pSignalProbeCollection = ( void * ) rtDW . llq51al0ac .
SignalProbe ; const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } { void * pSignalProbeCollection = ( void * ) rtDW . iz4q3uhlvz .
SignalProbe ; const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } rt_FREE ( rtDW . alrdv1eret . RSimInfoPtr ) ; rt_FREE ( rtDW .
p1e0b0rkdr . RSimInfoPtr ) ; rt_FREE ( rtDW . clwukip414 . RSimInfoPtr ) ; {
void * pSignalProbeCollection = ( void * ) rtDW . dcyih1kpjy . SignalProbe ;
const char * fileName = rt_GetMatSignalLoggingFileName ( ) ;
rtwSignalProbeCollectionSaveDatasetMatFile ( pSignalProbeCollection ,
fileName ) ; rtwSignalProbeCollectionDestroyInstance ( pSignalProbeCollection
) ; } rt_FREE ( rtDW . d5tz0vp4gc . RSimInfoPtr ) ; rt_FREE ( rtDW .
ozs1urzqbb . RSimInfoPtr ) ; rt_FREE ( rtDW . jfbqvyxdrm . RSimInfoPtr ) ; }
void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 8 ) ;
ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 1 ) ; ssSetNumU (
rtS , 2 ) ; ssSetDirectFeedThrough ( rtS , 1 ) ; ssSetNumSampleTimes ( rtS ,
6 ) ; ssSetNumBlocks ( rtS , 1328 ) ; ssSetNumBlockIO ( rtS , 185 ) ;
ssSetNumBlockParams ( rtS , 119443 ) ; } void MdlInitializeSampleTimes ( void
) { ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetSampleTime ( rtS , 1 , 0.0 ) ;
ssSetSampleTime ( rtS , 2 , 0.016 ) ; ssSetSampleTime ( rtS , 3 , 0.032 ) ;
ssSetSampleTime ( rtS , 4 , 5.0 ) ; ssSetSampleTime ( rtS , 5 , 50.0 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 1.0 ) ;
ssSetOffsetTime ( rtS , 2 , 0.0 ) ; ssSetOffsetTime ( rtS , 3 , 0.0 ) ;
ssSetOffsetTime ( rtS , 4 , 0.0 ) ; ssSetOffsetTime ( rtS , 5 , 0.0 ) ; }
void raccel_set_checksum ( SimStruct * rtS ) { ssSetChecksumVal ( rtS , 0 ,
4193934334U ) ; ssSetChecksumVal ( rtS , 1 , 1491268519U ) ; ssSetChecksumVal
( rtS , 2 , 2603397843U ) ; ssSetChecksumVal ( rtS , 3 , 2580903672U ) ; }
SimStruct * raccel_register_model ( void ) { static struct _ssMdlInfo mdlInfo
; ( void ) memset ( ( char * ) rtS , 0 , sizeof ( SimStruct ) ) ; ( void )
memset ( ( char * ) & mdlInfo , 0 , sizeof ( struct _ssMdlInfo ) ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { ssSetU ( rtS , ( ( void * ) & rtU ) ) ; ( void ) memset ( (
void * ) & rtU , 0 , sizeof ( ExtU ) ) ; } { ssSetY ( rtS , & rtY ) ; rtY .
f2pqowb0h2 = 0.0 ; } ssSetDefaultParam ( rtS , ( real_T * ) & rtP ) ; {
real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ; ( void )
memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = ( void * ) &
rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork , 0 , sizeof
( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset ( ( char_T *
) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS , & dtInfo
) ; dtInfo . numDataTypes = 15 ; dtInfo . dataTypeSizes = & rtDataTypeSizes [
0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ; dtInfo . B = &
rtBTransTable ; dtInfo . P = & rtPTransTable ; }
KD_cl_harness_forthao_breach_InitializeDataMapInfo ( rtS ) ;
ssSetIsRapidAcceleratorActive ( rtS , true ) ; ssSetRootSS ( rtS , rtS ) ;
ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS ,
"KD_cl_harness_forthao_breach" ) ; ssSetPath ( rtS ,
"KD_cl_harness_forthao_breach" ) ; ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal (
rtS , 2.2204460492503131E-16 ) ; { static RTWLogInfo rt_DataLoggingInfo ;
ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; } { { static int_T
rt_LoggedStateWidths [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 1 , 1 , 1 ,
1 , 1 , 1 , 1 , 3 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static int_T
rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static int_T
rt_LoggedStateDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 1 , 1 ,
1 , 1 , 1 , 1 , 1 , 3 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE ,
SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_SINGLE , SS_INT32 ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE } ; static int_T
rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static const char_T *
rt_LoggedStateLabels [ ] = { "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" ,
"CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" } ; static const char_T *
rt_LoggedStateBlockNames [ ] = {
 "KD_cl_harness_forthao_breach/Intake Manifold/Intake_manifold/Cus_integrator2/Integrator1"
,
 "KD_cl_harness_forthao_breach/Exhaust Manifold/Exhaust Manifold/Cus_integrator2/Integrator2"
,
 "KD_cl_harness_forthao_breach/pre-throttle manifold/p_preThrottle/Cus_integrator/p_prethrottle (kPa)1"
,
 "KD_cl_harness_forthao_breach/Turbo Rotational Dynamics/Turbo rot/Cus_integrator/Integrator1"
,
 "KD_cl_harness_forthao_breach/Intake Manifold/Intake_manifold/Cus_integrator/Integrator"
,
 "KD_cl_harness_forthao_breach/Exhaust Manifold/Exhaust Manifold/Cus_integrator/Integrator"
,
 "KD_cl_harness_forthao_breach/Intake Manifold/Intake_manifold/Cus_integrator1/Integrator"
,
 "KD_cl_harness_forthao_breach/Exhaust Manifold/Exhaust Manifold/Cus_integrator1/Integrator1"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay1" ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/custom_filter/Delay1"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay4" ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/Unit Delay3"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay5" ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/reduced_obs/Unit Delay5"
,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/reduced_obs/Unit Delay1"
,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/reduced_obs/Unit Delay2"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay" ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay3" ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay2" ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter/Delay1"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay8" ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter1/Delay1"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay9" ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/ntestimator/custom_filter/Delay1"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Unit Delay1"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Unit Delay3"
,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Filter1/Delay11"
,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Filter1/Delay21"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay10" ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay6" ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Unit Delay7" ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter2/Delay1"
,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter3/Delay1"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/obs/Unit Delay"
, "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/obs/Unit Delay1"
,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/ntestimator/Throttle_Model/Air_Model_map_use/Forward_Flow/For_Iterator_Subsystem/Unit Delay"
,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/expcon/find_region/find_region/rv_register"
,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/While_Iterator_Subsystem/newton/For_Iterator_Subsystem/Unit Delay"
,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/expcon/find_region/find_region/reg_register"
, "KD_cl_harness_forthao_breach/steps/Subsystem2/Unit Delay" ,
"KD_cl_harness_forthao_breach/steps/Subsystem1/Unit Delay" ,
"KD_cl_harness_forthao_breach/steps/Subsystem/Unit Delay" } ; static const
char_T * rt_LoggedStateNames [ ] = { "" , "" , "" , "" , "" , "" , "" , "" ,
"" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , ""
, "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" , "" ,
"" , "" , "" } ; static boolean_T rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
} ; static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_SINGLE , SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE ,
SS_SINGLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_SINGLE , SS_SINGLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_INT32 , SS_INT32 , 0 , 0 , 0 , 1.0 , 0 , 0.0
} , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static RTWLogSignalInfo
rt_LoggedStateSignalInfo = { 42 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , { rt_LoggedStateLabels } , ( NULL )
, ( NULL ) , ( NULL ) , { rt_LoggedStateBlockNames } , { rt_LoggedStateNames
} , rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert } ; static void *
rt_LoggedStateSignalPtrs [ 42 ] ; rtliSetLogXSignalPtrs ( ssGetRTWLogInfo (
rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . mupnfilrqo ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . huyhg2ps31 ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtX . lgbs44xptg ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtX . ka43gmkysq ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtX . iqp0o3u0ph ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) & rtX . iynqfp2xbi ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) & rtX . cgw3asjtrv ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) & rtX . ge52s03ms5 ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) rtDW . avtbwzqnkf ;
rt_LoggedStateSignalPtrs [ 9 ] = ( void * ) & rtDW . poa5fptxm4 ;
rt_LoggedStateSignalPtrs [ 10 ] = ( void * ) & rtDW . bsbxmlf10r ;
rt_LoggedStateSignalPtrs [ 11 ] = ( void * ) & rtDW . pybwwu5s4d ;
rt_LoggedStateSignalPtrs [ 12 ] = ( void * ) & rtDW . j5f3ay4xaq ;
rt_LoggedStateSignalPtrs [ 13 ] = ( void * ) & rtDW . ackerqxqlr ;
rt_LoggedStateSignalPtrs [ 14 ] = ( void * ) & rtDW . c1qvpfpyqu ;
rt_LoggedStateSignalPtrs [ 15 ] = ( void * ) & rtDW . em10zry3vm ;
rt_LoggedStateSignalPtrs [ 16 ] = ( void * ) rtDW . cz55ow2si1 ;
rt_LoggedStateSignalPtrs [ 17 ] = ( void * ) & rtDW . h4gbii3cbq ;
rt_LoggedStateSignalPtrs [ 18 ] = ( void * ) & rtDW . o04t4yciip ;
rt_LoggedStateSignalPtrs [ 19 ] = ( void * ) & rtDW . lzwd5z4dbk ;
rt_LoggedStateSignalPtrs [ 20 ] = ( void * ) & rtDW . dgfekwwlr1 ;
rt_LoggedStateSignalPtrs [ 21 ] = ( void * ) & rtDW . dw2dt5amj1 ;
rt_LoggedStateSignalPtrs [ 22 ] = ( void * ) & rtDW . letoggxozl ;
rt_LoggedStateSignalPtrs [ 23 ] = ( void * ) & rtDW . frjwyakiph ;
rt_LoggedStateSignalPtrs [ 24 ] = ( void * ) & rtDW . i5yn1movmy ;
rt_LoggedStateSignalPtrs [ 25 ] = ( void * ) & rtDW . diffnla35e ;
rt_LoggedStateSignalPtrs [ 26 ] = ( void * ) & rtDW . nqyjhyuvcj ;
rt_LoggedStateSignalPtrs [ 27 ] = ( void * ) & rtDW . fjcoqtw2bx ;
rt_LoggedStateSignalPtrs [ 28 ] = ( void * ) & rtDW . iggiejtmqu ;
rt_LoggedStateSignalPtrs [ 29 ] = ( void * ) & rtDW . mvpjwhrzk3 ;
rt_LoggedStateSignalPtrs [ 30 ] = ( void * ) & rtDW . mtqhixagy1 ;
rt_LoggedStateSignalPtrs [ 31 ] = ( void * ) & rtDW . fhgbtmls3d ;
rt_LoggedStateSignalPtrs [ 32 ] = ( void * ) & rtDW . l1sigmyvxe ;
rt_LoggedStateSignalPtrs [ 33 ] = ( void * ) & rtDW . noqny2ee14 ;
rt_LoggedStateSignalPtrs [ 34 ] = ( void * ) & rtDW . ljbykua013 ;
rt_LoggedStateSignalPtrs [ 35 ] = ( void * ) & rtDW . owlkbndpg5 ;
rt_LoggedStateSignalPtrs [ 36 ] = ( void * ) & rtDW . gme5mt5rhg ;
rt_LoggedStateSignalPtrs [ 37 ] = ( void * ) & rtDW . ehd3s5jupn ;
rt_LoggedStateSignalPtrs [ 38 ] = ( void * ) & rtDW . n4b14msae2 ;
rt_LoggedStateSignalPtrs [ 39 ] = ( void * ) & rtDW . lwrmmrtmge . afjuedjd2w
; rt_LoggedStateSignalPtrs [ 40 ] = ( void * ) & rtDW . cdbewnv5xj .
afjuedjd2w ; rt_LoggedStateSignalPtrs [ 41 ] = ( void * ) & rtDW .
masm1qwyo5u . afjuedjd2w ; } rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" )
; rtliSetLogX ( ssGetRTWLogInfo ( rtS ) , "tmp_raccel_xout" ) ;
rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) , "xFinal" ) ;
rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 2 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; { static void * rt_LoggedOutputSignalPtrs [ ] = { & rtY .
f2pqowb0h2 } ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( (
LogSignalPtrsType ) rt_LoggedOutputSignalPtrs ) ) ; } { static int_T
rt_LoggedOutputWidths [ ] = { 1 } ; static int_T rt_LoggedOutputNumDimensions
[ ] = { 1 } ; static int_T rt_LoggedOutputDimensions [ ] = { 1 } ; static
boolean_T rt_LoggedOutputIsVarDims [ ] = { 0 } ; static void *
rt_LoggedCurrentSignalDimensions [ ] = { ( NULL ) } ; static int_T
rt_LoggedCurrentSignalDimensionsSize [ ] = { 4 } ; static BuiltInDTypeId
rt_LoggedOutputDataTypeIds [ ] = { SS_DOUBLE } ; static int_T
rt_LoggedOutputComplexSignals [ ] = { 0 } ; static const char_T *
rt_LoggedOutputLabels [ ] = { "Out1" } ; static const char_T *
rt_LoggedOutputBlockNames [ ] = { "KD_cl_harness_forthao_breach/Out1" } ;
static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE
, SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static RTWLogSignalInfo
rt_LoggedOutputSignalInfo [ ] = { { 1 , rt_LoggedOutputWidths ,
rt_LoggedOutputNumDimensions , rt_LoggedOutputDimensions ,
rt_LoggedOutputIsVarDims , rt_LoggedCurrentSignalDimensions ,
rt_LoggedCurrentSignalDimensionsSize , rt_LoggedOutputDataTypeIds ,
rt_LoggedOutputComplexSignals , ( NULL ) , { rt_LoggedOutputLabels } , ( NULL
) , ( NULL ) , ( NULL ) , { rt_LoggedOutputBlockNames } , { ( NULL ) } , (
NULL ) , rt_RTWLogDataTypeConvert } } ; rtliSetLogYSignalInfo (
ssGetRTWLogInfo ( rtS ) , rt_LoggedOutputSignalInfo ) ;
rt_LoggedCurrentSignalDimensions [ 0 ] = & rt_LoggedOutputWidths [ 0 ] ; }
rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "tmp_raccel_yout1" ) ; } { static
struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 )
; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 8 ] ; static
real_T absTol [ 8 ] = { 0.0001 , 0.0001 , 0.0001 , 0.0001 , 0.0001 , 0.0001 ,
0.0001 , 0.0001 } ; static uint8_T absTolControl [ 8 ] = { 2U , 2U , 2U , 2U
, 2U , 2U , 2U , 2U } ; static ssNonContDerivSigInfo nonContDerivSigInfo [ 8
] = { { 1 * sizeof ( real_T ) , ( char * ) ( & rtB . ikbnonbcrn ) , ( NULL )
} , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB . pfzxy051h0 ) , ( NULL ) }
, { 1 * sizeof ( real_T ) , ( char * ) ( & rtB . ejc4fyifu5 ) , ( NULL ) } ,
{ 1 * sizeof ( real_T ) , ( char * ) ( & rtB . jg43ge1e1q ) , ( NULL ) } , {
1 * sizeof ( real_T ) , ( char * ) ( & rtB . i45enf1q3e ) , ( NULL ) } , { 2
* sizeof ( real_T ) , ( char * ) ( & rtB . psdqponccq [ 0 ] ) , ( NULL ) } ,
{ 1 * sizeof ( real_T ) , ( char * ) ( & rtB . glxqot4hmc ) , ( NULL ) } , {
1 * sizeof ( real_T ) , ( char * ) ( & rtB . nfipgrtuvr ) , ( NULL ) } } ;
ssSetSolverRelTol ( rtS , 0.0001 ) ; ssSetStepSize ( rtS , 0.0 ) ;
ssSetMinStepSize ( rtS , 0.0 ) ; ssSetMaxNumMinSteps ( rtS , - 1 ) ;
ssSetMinStepViolatedError ( rtS , 0 ) ; ssSetMaxStepSize ( rtS , 0.005 ) ;
ssSetSolverMaxOrder ( rtS , - 1 ) ; ssSetSolverRefineFactor ( rtS , 1 ) ;
ssSetOutputTimes ( rtS , ( NULL ) ) ; ssSetNumOutputTimes ( rtS , 0 ) ;
ssSetOutputTimesOnly ( rtS , 0 ) ; ssSetOutputTimesIndex ( rtS , 0 ) ;
ssSetZCCacheNeedsReset ( rtS , 0 ) ; ssSetDerivCacheNeedsReset ( rtS , 0 ) ;
ssSetNumNonContDerivSigInfos ( rtS , 8 ) ; ssSetNonContDerivSigInfos ( rtS ,
nonContDerivSigInfo ) ; ssSetSolverInfo ( rtS , & slvrInfo ) ;
ssSetSolverName ( rtS , "ode45" ) ; ssSetVariableStepSolver ( rtS , 1 ) ;
ssSetSolverConsistencyChecking ( rtS , 0 ) ; ssSetSolverAdaptiveZcDetection (
rtS , 0 ) ; ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetAbsTolVector (
rtS , absTol ) ; ssSetAbsTolControlVector ( rtS , absTolControl ) ;
ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetSolverStateProjection ( rtS , 0 ) ; ssSetSolverMassMatrixType ( rtS , (
ssMatrixType ) 0 ) ; ssSetSolverMassMatrixNzMax ( rtS , 0 ) ;
ssSetModelOutputs ( rtS , MdlOutputs ) ; ssSetModelLogData ( rtS ,
rt_UpdateTXYLogVars ) ; ssSetModelUpdate ( rtS , MdlUpdate ) ;
ssSetModelDerivatives ( rtS , MdlDerivatives ) ;
ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 0 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 4193934334U ) ; ssSetChecksumVal ( rtS , 1 ,
1491268519U ) ; ssSetChecksumVal ( rtS , 2 , 2603397843U ) ; ssSetChecksumVal
( rtS , 3 , 2580903672U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 123 ] ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = &
rtAlwaysEnabled ; systemRan [ 2 ] = & rtAlwaysEnabled ; systemRan [ 3 ] = &
rtAlwaysEnabled ; systemRan [ 4 ] = & rtAlwaysEnabled ; systemRan [ 5 ] = &
rtAlwaysEnabled ; systemRan [ 6 ] = & rtAlwaysEnabled ; systemRan [ 7 ] = &
rtAlwaysEnabled ; systemRan [ 8 ] = & rtAlwaysEnabled ; systemRan [ 9 ] = &
rtAlwaysEnabled ; systemRan [ 10 ] = & rtAlwaysEnabled ; systemRan [ 11 ] = &
rtAlwaysEnabled ; systemRan [ 12 ] = & rtAlwaysEnabled ; systemRan [ 13 ] = &
rtAlwaysEnabled ; systemRan [ 14 ] = & rtAlwaysEnabled ; systemRan [ 15 ] = &
rtAlwaysEnabled ; systemRan [ 16 ] = & rtAlwaysEnabled ; systemRan [ 17 ] = &
rtAlwaysEnabled ; systemRan [ 18 ] = & rtAlwaysEnabled ; systemRan [ 19 ] = &
rtAlwaysEnabled ; systemRan [ 20 ] = & rtAlwaysEnabled ; systemRan [ 21 ] = &
rtAlwaysEnabled ; systemRan [ 22 ] = & rtAlwaysEnabled ; systemRan [ 23 ] = &
rtAlwaysEnabled ; systemRan [ 24 ] = & rtAlwaysEnabled ; systemRan [ 25 ] = &
rtAlwaysEnabled ; systemRan [ 26 ] = & rtAlwaysEnabled ; systemRan [ 27 ] = &
rtAlwaysEnabled ; systemRan [ 28 ] = & rtAlwaysEnabled ; systemRan [ 29 ] = &
rtAlwaysEnabled ; systemRan [ 30 ] = ( sysRanDType * ) & rtDW . lb2gtdwzqd ;
systemRan [ 31 ] = ( sysRanDType * ) & rtDW . hpc0grqivr ; systemRan [ 32 ] =
( sysRanDType * ) & rtDW . ljedkvx4od ; systemRan [ 33 ] = ( sysRanDType * )
& rtDW . l4mofmlly2 ; systemRan [ 34 ] = ( sysRanDType * ) & rtDW .
kltb44md1r ; systemRan [ 35 ] = ( sysRanDType * ) & rtDW . hgwa21u3tp ;
systemRan [ 36 ] = ( sysRanDType * ) & rtDW . oqqlpwtggt ; systemRan [ 37 ] =
( sysRanDType * ) & rtDW . ljedkvx4od ; systemRan [ 38 ] = ( sysRanDType * )
& rtDW . ljedkvx4od ; systemRan [ 39 ] = ( sysRanDType * ) & rtDW .
ljedkvx4od ; systemRan [ 40 ] = & rtAlwaysEnabled ; systemRan [ 41 ] = &
rtAlwaysEnabled ; systemRan [ 42 ] = ( sysRanDType * ) & rtDW . pg1kwe2jsoh .
ld1fjkwy01 ; systemRan [ 43 ] = ( sysRanDType * ) & rtDW . gmyvhhtxia .
ld1fjkwy01 ; systemRan [ 44 ] = ( sysRanDType * ) & rtDW . ozyefxkqtm ;
systemRan [ 45 ] = ( sysRanDType * ) & rtDW . gdpkwnqxlj ; systemRan [ 46 ] =
( sysRanDType * ) & rtDW . hfnjefvf2v ; systemRan [ 47 ] = & rtAlwaysEnabled
; systemRan [ 48 ] = & rtAlwaysEnabled ; systemRan [ 49 ] = & rtAlwaysEnabled
; systemRan [ 50 ] = & rtAlwaysEnabled ; systemRan [ 51 ] = ( sysRanDType * )
& rtDW . o0fqt141qd ; systemRan [ 52 ] = ( sysRanDType * ) & rtDW .
h3vqcmc1hz ; systemRan [ 53 ] = ( sysRanDType * ) & rtDW . ewylvoz5wx ;
systemRan [ 54 ] = ( sysRanDType * ) & rtDW . bzt2b4vlgj ; systemRan [ 55 ] =
( sysRanDType * ) & rtDW . p5cjuriyjr ; systemRan [ 56 ] = ( sysRanDType * )
& rtDW . klgivly02z ; systemRan [ 57 ] = ( sysRanDType * ) & rtDW .
nlyldhhvyb ; systemRan [ 58 ] = ( sysRanDType * ) & rtDW . k1yann3ya5 ;
systemRan [ 59 ] = ( sysRanDType * ) & rtDW . bubafrutom ; systemRan [ 60 ] =
( sysRanDType * ) & rtDW . ltvu2oc3sf ; systemRan [ 61 ] = ( sysRanDType * )
& rtDW . adcpzgniuv ; systemRan [ 62 ] = ( sysRanDType * ) & rtDW .
ismm4u0kis ; systemRan [ 63 ] = ( sysRanDType * ) & rtDW . pqpqjda5is ;
systemRan [ 64 ] = ( sysRanDType * ) & rtDW . kct4avkdgo ; systemRan [ 65 ] =
( sysRanDType * ) & rtDW . ljqu2i52fc ; systemRan [ 66 ] = ( sysRanDType * )
& rtDW . lpg4z3lelv ; systemRan [ 67 ] = ( sysRanDType * ) & rtDW .
ombi11gse3 ; systemRan [ 68 ] = ( sysRanDType * ) & rtDW . li2ivnnt0t ;
systemRan [ 69 ] = ( sysRanDType * ) & rtDW . ae1e1itbfy ; systemRan [ 70 ] =
( sysRanDType * ) & rtDW . dhx34gepf4 ; systemRan [ 71 ] = ( sysRanDType * )
& rtDW . p2atyilds3 ; systemRan [ 72 ] = ( sysRanDType * ) & rtDW .
edw2mgcvx1 ; systemRan [ 73 ] = ( sysRanDType * ) & rtDW . n4uikvdjac ;
systemRan [ 74 ] = ( sysRanDType * ) & rtDW . bwmwpnvwlf ; systemRan [ 75 ] =
( sysRanDType * ) & rtDW . chxryck3fg ; systemRan [ 76 ] = ( sysRanDType * )
& rtDW . dl0glhtqdr ; systemRan [ 77 ] = ( sysRanDType * ) & rtDW .
igzqf1qklf ; systemRan [ 78 ] = ( sysRanDType * ) & rtDW . moze4hcv5c ;
systemRan [ 79 ] = ( sysRanDType * ) & rtDW . kuzwdhnrip ; systemRan [ 80 ] =
( sysRanDType * ) & rtDW . hf2ukkb54z ; systemRan [ 81 ] = ( sysRanDType * )
& rtDW . dp2wxggv2y ; systemRan [ 82 ] = ( sysRanDType * ) & rtDW .
ifikoeohu4 ; systemRan [ 83 ] = ( sysRanDType * ) & rtDW . fb2jmsx45b ;
systemRan [ 84 ] = ( sysRanDType * ) & rtDW . gu2pk5utpz ; systemRan [ 85 ] =
( sysRanDType * ) & rtDW . m1sbzn2h1n ; systemRan [ 86 ] = ( sysRanDType * )
& rtDW . j4ymuqubrw ; systemRan [ 87 ] = ( sysRanDType * ) & rtDW .
kymzzotg2g ; systemRan [ 88 ] = ( sysRanDType * ) & rtDW . dk3vj22y05 ;
systemRan [ 89 ] = ( sysRanDType * ) & rtDW . o3c1lu15ny ; systemRan [ 90 ] =
( sysRanDType * ) & rtDW . j45e0raewi ; systemRan [ 91 ] = ( sysRanDType * )
& rtDW . o3wc5wwa4p ; systemRan [ 92 ] = ( sysRanDType * ) & rtDW .
irsxloeepq ; systemRan [ 93 ] = ( sysRanDType * ) & rtDW . cp3q1at4o2 ;
systemRan [ 94 ] = ( sysRanDType * ) & rtDW . pce44vep3x ; systemRan [ 95 ] =
( sysRanDType * ) & rtDW . mee1wioe1r ; systemRan [ 96 ] = ( sysRanDType * )
& rtDW . lik1wotc2i ; systemRan [ 97 ] = ( sysRanDType * ) & rtDW .
gg02mzoxhc ; systemRan [ 98 ] = ( sysRanDType * ) & rtDW . maiimsnqs5 ;
systemRan [ 99 ] = ( sysRanDType * ) & rtDW . gwxpzomgjh ; systemRan [ 100 ]
= ( sysRanDType * ) & rtDW . etxqofccji ; systemRan [ 101 ] = ( sysRanDType *
) & rtDW . ljwb0xnabb ; systemRan [ 102 ] = ( sysRanDType * ) & rtDW .
ivkldwkotp ; systemRan [ 103 ] = ( sysRanDType * ) & rtDW . a5nvnya1oe ;
systemRan [ 104 ] = ( sysRanDType * ) & rtDW . dfax004odl ; systemRan [ 105 ]
= ( sysRanDType * ) & rtDW . mwuspmm2e1 ; systemRan [ 106 ] = ( sysRanDType *
) & rtDW . jgu1xgjxem ; systemRan [ 107 ] = ( sysRanDType * ) & rtDW .
my15ghhvb1 ; systemRan [ 108 ] = ( sysRanDType * ) & rtDW . bcd3kgenub ;
systemRan [ 109 ] = ( sysRanDType * ) & rtDW . dyx4tug5h3 ; systemRan [ 110 ]
= ( sysRanDType * ) & rtDW . f5k2rzim4a ; systemRan [ 111 ] = ( sysRanDType *
) & rtDW . nx3flbvahx ; systemRan [ 112 ] = ( sysRanDType * ) & rtDW .
hypqqzrtox ; systemRan [ 113 ] = ( sysRanDType * ) & rtDW . cr2kibgo2j ;
systemRan [ 114 ] = ( sysRanDType * ) & rtDW . pwlmqo3nxm ; systemRan [ 115 ]
= ( sysRanDType * ) & rtDW . guuziano0t ; systemRan [ 116 ] = ( sysRanDType *
) & rtDW . l12omsu2tn ; systemRan [ 117 ] = ( sysRanDType * ) & rtDW .
o2zj3fqza1 ; systemRan [ 118 ] = ( sysRanDType * ) & rtDW . m3gfat1ui0 ;
systemRan [ 119 ] = & rtAlwaysEnabled ; systemRan [ 120 ] = & rtAlwaysEnabled
; systemRan [ 121 ] = & rtAlwaysEnabled ; systemRan [ 122 ] = &
rtAlwaysEnabled ; rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) ,
& ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo
( rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS
) , ssGetTPtr ( rtS ) ) ; } rtP . Saturation_UpperSat = rtInf ; rtP .
Saturation_UpperSat_c3vbgn0h23 = rtInf ; rtP . Saturation_UpperSat_nesqhf0mrq
= rtInf ; rtP . Saturation_UpperSat_dzsaidwyzg = rtInf ; rtP .
Saturation1_UpperSat_fkuqqwyy3e = rtInf ; rtP .
Saturation_UpperSat_drcjljjkd1 = rtInf ; rtP .
Saturation1_UpperSat_ed2d1dsvvu = rtInf ; rtP . Saturation2_UpperSat = rtInfF
; rtP . Saturation3_UpperSat = rtInfF ; rtP . Saturation1_UpperSat_l0fn5euabx
= rtInfF ; rtP . Saturation4_UpperSat = rtInfF ; rtP .
Saturation2_UpperSat_neszcqhzip = rtInfF ; rtP .
Saturation_UpperSat_phsdj5dg3g = rtInfF ; rtP .
Saturation3_UpperSat_fpowc2uvdu = rtInfF ; rtP .
Saturation1_UpperSat_jhk0udkkso = rtInfF ; rtP .
Saturation4_UpperSat_fgk5yexhjk = rtInfF ; rtP .
Saturation2_UpperSat_kqxekeh4ne = rtInfF ; rtP .
Saturation4_UpperSat_mvi32mle5a = rtInfF ; rtP .
Saturation2_UpperSat_m0obbkx21y = rtInfF ; rtP .
Saturation_UpperSat_bb44f3rn3e = rtInfF ; rtP .
Saturation1_UpperSat_dbmtmwbw0d = rtInfF ; rtP .
Saturation3_UpperSat_eu4nn5aeqt = rtInfF ; rtP .
Saturation1_UpperSat_h1az5n4to4 = rtInfF ; rtP .
Saturation3_UpperSat_fyjrms34ap = rtInfF ; rtP .
Saturation4_UpperSat_ne3ia3nb0j = rtInfF ; rtP .
Saturation1_UpperSat_mmdkyxpjcy = rtInfF ; rtP . Saturation5_UpperSat =
rtInfF ; rtP . Saturation2_UpperSat_fjp1hny0ya = rtInfF ; rtP .
Saturation4_UpperSat_f5y5vur4ve = rtInfF ; rtP .
Saturation_UpperSat_d0ebinhgkh = rtInfF ; rtP .
Saturation3_UpperSat_jgnvlh1trc = rtInfF ; rtP .
Saturation4_UpperSat_fg5ix0ri20 = rtInfF ; rtP . Saturation7_UpperSat =
rtInfF ; rtP . Saturation_UpperSat_dfiskt0evr = rtInfF ; rtP .
Saturation5_UpperSat_dlhoczu115 = rtInfF ; rtP .
Saturation4_UpperSat_nmdcwefbw5 = rtInfF ; rtP .
Saturation2_UpperSat_hskdnsucj5 = rtInfF ; rtP .
Saturation1_UpperSat_kk32mwbior = rtInfF ; rtP .
Saturation3_UpperSat_aodcenepxv = rtInfF ; rtP .
Saturation4_UpperSat_epdhn4s0cl = rtInfF ; rtP .
Saturation3_UpperSat_hvmdvvrxvg = rtInfF ; rtP .
Saturation_UpperSat_heyubqqqyr = rtInfF ; rtP .
Saturation1_UpperSat_omybqinkw3 = rtInfF ; rtP .
Saturation2_UpperSat_ar3amrrdo0 = rtInfF ; rtP .
Saturation5_UpperSat_lsmaqufwep = rtInfF ; rtP .
Saturation1_UpperSat_otpxulmvuy = rtInfF ; rtP .
Saturation_UpperSat_aeqkn4yat2 = rtInfF ; rtP .
Saturation3_UpperSat_e5wb1y1qfm = rtInfF ; rtP .
Saturation1_UpperSat_pqesfzc0le = rtInfF ; rtP .
Saturation3_UpperSat_gfw1stpglz = rtInfF ; rtP .
Saturation2_UpperSat_pd4jn2febf = rtInfF ; rtP .
Saturation4_UpperSat_jpf21d0c4s = rtInfF ; rtP .
Saturation2_UpperSat_eil30qspgi = rtInfF ; rtP .
Saturation4_UpperSat_kyzipinvaz = rtInfF ; rtP .
Saturation5_UpperSat_h4urtqtiyp = rtInfF ; return rtS ; }
