#include "__cf_KD_cl_harness_forthao_breach.h"
#if 0
This file is not available for use in any application other than as a MATLAB
( R ) MEX file for use with the Simulink ( R ) product . If you do not have
the Simulink Coder licensed , this file contains encrypted block names , etc
. If you purchase the Simulink Coder , this file will contain full block
descriptions and improved variable names .
#endif
#include <math.h>
#include "KD_cl_harness_forthao_breach_acc.h"
#include "KD_cl_harness_forthao_breach_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
void KD_cl_harness_forthao_breach_acc_BINARYSEARCH_real32_T ( uint32_T *
piLeft , uint32_T * piRght , real32_T u , const real32_T * pData , uint32_T
iHi ) { * piLeft = 0U ; * piRght = iHi ; if ( u <= pData [ 0 ] ) { * piRght =
0U ; } else if ( u >= pData [ iHi ] ) { * piLeft = iHi ; } else { uint32_T i
; while ( ( * piRght - * piLeft ) > 1U ) { i = ( * piLeft + * piRght ) >> 1 ;
if ( u < pData [ i ] ) { * piRght = i ; } else { * piLeft = i ; } } } } void
KD_cl_harness_forthao_breach_acc_LookUp_real32_T_real32_T ( real32_T * pY ,
const real32_T * pYData , real32_T u , const real32_T * pUData , uint32_T iHi
) { uint32_T iLeft ; uint32_T iRght ;
KD_cl_harness_forthao_breach_acc_BINARYSEARCH_real32_T ( & ( iLeft ) , & (
iRght ) , u , pUData , iHi ) ; { real32_T lambda ; if ( pUData [ iRght ] >
pUData [ iLeft ] ) { real32_T num ; real32_T den ; den = pUData [ iRght ] ;
den -= pUData [ iLeft ] ; num = u ; num -= pUData [ iLeft ] ; lambda = num /
den ; } else { lambda = 0.0F ; } { real32_T yLeftCast ; real32_T yRghtCast ;
yLeftCast = pYData [ iLeft ] ; yRghtCast = pYData [ iRght ] ; yLeftCast +=
lambda * ( yRghtCast - yLeftCast ) ; ( * pY ) = yLeftCast ; } } } void
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( real32_T
* pY , const real32_T * pYData , real32_T u0 , const real32_T * pU0Data ,
uint32_T iHiU0 , real32_T u1 , const real32_T * pU1Data , uint32_T iHiU1 ) {
uint32_T iLeftU0 , iRghtU0 , iLeftU1 , iRghtU1 ;
KD_cl_harness_forthao_breach_acc_BINARYSEARCH_real32_T ( & ( iLeftU0 ) , & (
iRghtU0 ) , u0 , pU0Data , iHiU0 ) ;
KD_cl_harness_forthao_breach_acc_BINARYSEARCH_real32_T ( & ( iLeftU1 ) , & (
iRghtU1 ) , u1 , pU1Data , iHiU1 ) ; { real32_T u0Left = pU0Data [ iLeftU0 ]
; real32_T u0Rght = pU0Data [ iRghtU0 ] ; real32_T u1Left = pU1Data [ iLeftU1
] ; real32_T u1Rght = pU1Data [ iRghtU1 ] ; real32_T yTemp ; real32_T
yLeftLeft ; real32_T yLeftRght ; real32_T yRghtLeft ; real32_T yRghtRght ;
real32_T u1Lambda ; real32_T u0Lambda ; if ( u1Rght > u1Left ) { real32_T num
; real32_T den ; den = u1Rght ; den -= u1Left ; num = u1 ; num -= u1Left ;
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
yRghtCast - yLeftCast ) ; ( * pY ) = yLeftCast ; } } } void nbrxxgteth (
SimStruct * const S ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } void hldppkqdr4 ( SimStruct * const S ) {
ssSetSolverNeedsReset ( S ) ; } void pg1kwe2jso ( real32_T egaxndeq0x ,
int32_T k1cglknueh , real32_T * ddh0mvgbbl , int32_T * j4vxg2gmyl ) { *
ddh0mvgbbl = egaxndeq0x ; * j4vxg2gmyl = k1cglknueh ; } void oupeszqoej (
SimStruct * const S ) { } void ivkef2hmn4 ( jcvtjjdhjy * localDW , ev5xuv0chq
* localP ) { localDW -> afjuedjd2w = localP -> P_0 ; localDW -> akpttb2uyr =
localP -> P_3 ; } void masm1qwyo5 ( g4kb1dhx4k * localB , jcvtjjdhjy *
localDW , ev5xuv0chq * localP ) { real_T rateLimiterRate ; rateLimiterRate =
localDW -> afjuedjd2w - localDW -> akpttb2uyr ; if ( rateLimiterRate > localP
-> P_1 ) { localB -> ffs1ididcx = localDW -> akpttb2uyr + localP -> P_1 ; }
else if ( rateLimiterRate < localP -> P_2 ) { localB -> ffs1ididcx = localDW
-> akpttb2uyr + localP -> P_2 ; } else { localB -> ffs1ididcx = localDW ->
afjuedjd2w ; } localDW -> akpttb2uyr = localB -> ffs1ididcx ; } void
foiteff4aq ( real_T ow310q0jgt , jcvtjjdhjy * localDW ) { localDW ->
afjuedjd2w = ow310q0jgt ; } void bszt5tkyfa ( SimStruct * const S ) { }
real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { uint32_T lo ; uint32_T
hi ; lo = * u % 127773U * 16807U ; hi = * u / 127773U * 2836U ; if ( lo < hi
) { * u = 2147483647U - ( hi - lo ) ; } else { * u = lo - hi ; } return (
real_T ) * u * 4.6566128752457969E-10 ; } static void mdlOutputs ( SimStruct
* S , int_T tid ) { real_T kyy20toyut ; real32_T iou1bb3prl ; real32_T
omfw35sfyk ; real32_T j5z4rdmkwv ; real32_T ase2d1biln ; real32_T awl0z0b3sb
; real32_T a3jnflwpkj ; real32_T ckkx05hfhz ; int32_T esndn1d5qn ; int32_T
mldy4xfo0l ; real_T loi4w1jrb4 ; real_T f1qa0udy3j ; real32_T e4orw3vqsn ;
real32_T cl24d41ibh ; real32_T e51a0t11ia ; real32_T j5cdf5jml5 ; real32_T
am2jzeb44a ; real32_T gnrscbmka5 ; real32_T a3l10a5g2s ; real32_T br0btxcgmo
; real32_T bsmjlt2qqy ; real32_T dbt3uojgmq ; real32_T emptrcbnkv ; real32_T
jfmtdksnh0 ; real_T n4kbehhhau ; real_T b11wdxnlxt ; real_T npiyznthqi ;
real_T o5ibp43cp4 ; real_T c4l11istf0 ; real_T gen03hfvbg ; real_T aktecqyana
; real32_T g1ekzbu3oi ; real32_T fwhtla1rft ; real32_T not4fp11wk ; real32_T
orelggziy4 ; real32_T btosikvjyf [ 2 ] ; real32_T cbpfnq4pxd ; real32_T
e0r0t533ao ; real32_T finyivsrdi ; real32_T kaqx4nados ; real32_T alqkjudhu3
; boolean_T meppapiqj0 ; int32_T s60_iter ; real32_T jjkfbyaomr ; real32_T
fij5klqz0n ; real32_T dift4gyrha [ 309 ] ; real32_T hsiahk1nnd [ 103 ] ;
real32_T fzccphw1bz ; real32_T ehyje10v1p ; real32_T frrr5abd2i [ 9 ] ;
real32_T fbk03eccj1 [ 9 ] ; real32_T phcrozezwb [ 9 ] ; real32_T o3cuzyoqg5 ;
real32_T pwkaxiafxx ; real32_T km03xn13id ; real32_T plknkmyedj ; real32_T
jmuta2homi ; real32_T fvhzusu422 ; real32_T pyabwb0ags ; real32_T hn15keiut1
; real32_T byk21oesq1 ; real32_T a1jrsglzzi ; real32_T c2fdcpgrsp ; real32_T
batdnpsvim ; int8_T rtPrevAction ; int8_T rtAction ; real32_T o3mfdsmmfb ;
int32_T ffd3q0dmho ; real32_T cfpabnsfkw [ 10 ] ; real32_T dqg1fl5gyp [ 10 ]
; real32_T n4vetwv3qv [ 10 ] ; real32_T np1ecrs5jr [ 10 ] ; real32_T
klzvh1ekin [ 10 ] ; real32_T ebqfsagx32 [ 10 ] ; real32_T cxofaf120r [ 10 ] ;
real32_T bfa5h0zq23 [ 10 ] ; real32_T fa4aelt32d [ 10 ] ; real32_T p22ala5lq4
[ 10 ] ; real32_T galtyeac1e [ 10 ] ; real32_T hgfxoibhl0 [ 10 ] ; real32_T
iqq1rbnkkz [ 10 ] ; real32_T eplcvohihr ; real_T efj5q5ebcq ; real32_T
e2oeg530ux [ 10 ] ; real_T tmp ; int32_T i ; int32_T i_p ; real32_T
gwzyst3ou3_p ; int32_T tmp_p ; int32_T tmp_e ; int32_T tmp_i ; int32_T tmp_m
; int32_T tmp_g ; int32_T tmp_j ; int32_T tmp_f ; int32_T tmp_c ; int32_T
tmp_k ; int32_T tmp_b ; real32_T tmp_n [ 3 ] ; real32_T tmp_l [ 3 ] ;
real32_T ic3wqfpram_idx_0 ; real32_T ic3wqfpram_idx_1 ; real32_T
exrgmvycyf_idx_0 ; real32_T exrgmvycyf_idx_1 ; real32_T exrgmvycyf_idx_2 ;
real32_T pn0idallhu_idx_0 ; real32_T pn0idallhu_idx_1 ; real32_T
dpajlxfdyx_idx_0 ; real32_T jsgk2hka41_idx_0 ; real32_T jsgk2hka41_idx_1 ;
real32_T u0 ; dxuu1n0atf * _rtB ; nka5ekiiij * _rtP ; ixqofizoey * _rtX ;
cet3mqzt35 * _rtDW ; _rtDW = ( ( cet3mqzt35 * ) ssGetRootDWork ( S ) ) ; _rtX
= ( ( ixqofizoey * ) ssGetContStates ( S ) ) ; _rtP = ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) ; _rtB = ( ( dxuu1n0atf * ) _ssGetBlockIO ( S ) ) ;
_rtB -> bchvsczbjy = _rtX -> mupnfilrqo ; _rtB -> ipni0rpjg1 = ( real32_T )
_rtB -> bchvsczbjy ; _rtB -> b2luvekoek = _rtX -> huyhg2ps31 ; n4kbehhhau =
_rtP -> P_36 * _rtB -> b2luvekoek ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB
-> lcox2cqw1x = _rtDW -> cc0wkfbxf2 ; _rtB -> cfjfxf2th0 = _rtP -> P_38 ;
_rtB -> ircgfqnvid = _rtDW -> eac1jvpkom ; _rtB -> fh2qfrkpzp = _rtP -> P_40
* _rtB -> ircgfqnvid ; } if ( ( ( dq45bcq35i * ) ssGetU ( S ) ) -> ch4dzb1x4i
> _rtP -> P_41 ) { _rtB -> owjgmyz3gk = _rtP -> P_41 ; } else if ( ( (
dq45bcq35i * ) ssGetU ( S ) ) -> ch4dzb1x4i < _rtP -> P_42 ) { _rtB ->
owjgmyz3gk = _rtP -> P_42 ; } else { _rtB -> owjgmyz3gk = ( ( dq45bcq35i * )
ssGetU ( S ) ) -> ch4dzb1x4i ; } if ( ( ( dq45bcq35i * ) ssGetU ( S ) ) ->
gm151yhz1l > _rtP -> P_43 ) { _rtB -> p0ej2ncygl = _rtP -> P_43 ; } else if (
( ( dq45bcq35i * ) ssGetU ( S ) ) -> gm151yhz1l < _rtP -> P_44 ) { _rtB ->
p0ej2ncygl = _rtP -> P_44 ; } else { _rtB -> p0ej2ncygl = ( ( dq45bcq35i * )
ssGetU ( S ) ) -> gm151yhz1l ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
pm0z41xakx = _rtP -> P_46 * _rtP -> P_45 ; _rtB -> j530vib5xo = _rtP -> P_48
* _rtP -> P_47 ; } if ( ssIsSampleHit ( S , 3 , 0 ) ) { masm1qwyo5 ( & _rtB
-> masm1qwyo5u , & _rtDW -> masm1qwyo5u , ( ev5xuv0chq * ) & _rtP ->
masm1qwyo5u ) ; masm1qwyo5 ( & _rtB -> cdbewnv5xj , & _rtDW -> cdbewnv5xj , (
ev5xuv0chq * ) & _rtP -> cdbewnv5xj ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) )
{ ssCallAccelRunBlock ( S , 118 , 16 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 3 , 0 ) ) { masm1qwyo5 ( & _rtB -> lwrmmrtmge , & _rtDW
-> lwrmmrtmge , ( ev5xuv0chq * ) & _rtP -> lwrmmrtmge ) ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> j530vib5xo = _rtP -> P_49 ;
ssCallAccelRunBlock ( S , 118 , 19 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 2 , 0 ) ) { ssCallAccelRunBlock ( S , 118 , 20 ,
SS_CALL_MDL_OUTPUTS ) ; if ( _rtB -> ij1u0goevc > _rtP -> P_50 ) { _rtB ->
jsa1yl3ihn = _rtP -> P_50 ; } else if ( _rtB -> ij1u0goevc < _rtP -> P_51 ) {
_rtB -> jsa1yl3ihn = _rtP -> P_51 ; } else { _rtB -> jsa1yl3ihn = _rtB ->
ij1u0goevc ; } ssCallAccelRunBlock ( S , 118 , 22 , SS_CALL_MDL_OUTPUTS ) ;
if ( _rtB -> ij1u0goevc > _rtP -> P_52 ) { _rtB -> nyafgwhtcb = _rtP -> P_52
; } else if ( _rtB -> ij1u0goevc < _rtP -> P_53 ) { _rtB -> nyafgwhtcb = _rtP
-> P_53 ; } else { _rtB -> nyafgwhtcb = _rtB -> ij1u0goevc ; } } if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 118 , 24 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 118 , 25 ,
SS_CALL_MDL_OUTPUTS ) ; b11wdxnlxt = _rtP -> P_54 * _rtB -> eebr3qqx0u [ 1 ]
; npiyznthqi = _rtP -> P_55 * b11wdxnlxt ; if ( ssIsSampleHit ( S , 1 , 0 ) )
{ _rtB -> bpcgvzdmyu = _rtP -> P_57 ; memcpy ( & _rtB -> pn1xztdhen [ 0 ] , &
_rtP -> P_58 [ 0 ] , 9U * sizeof ( real_T ) ) ; memcpy ( & _rtB -> e3udxmtmba
[ 0 ] , & _rtP -> P_59 [ 0 ] , 18U * sizeof ( real_T ) ) ; _rtB -> g5arga1zpg
= _rtP -> P_60 ; } _rtB -> burpslxsjz [ 0 ] = _rtB -> fh2qfrkpzp ; _rtB ->
burpslxsjz [ 1 ] = _rtP -> P_56 * npiyznthqi ; ssCallAccelRunBlock ( S , 14 ,
1 , SS_CALL_MDL_OUTPUTS ) ; o5ibp43cp4 = _rtP -> P_61 * _rtB -> bchvsczbjy ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> kssh3anhn0 = _rtP -> P_62 ; _rtB
-> dlh2uazjka = _rtP -> P_63 * _rtB -> ircgfqnvid ; _rtB -> itws422pzw = _rtP
-> P_65 ; memcpy ( & _rtB -> f0xqjtllb0 [ 0 ] , & _rtP -> P_66 [ 0 ] , 9U *
sizeof ( real_T ) ) ; memcpy ( & _rtB -> cc3qif3qin [ 0 ] , & _rtP -> P_67 [
0 ] , 18U * sizeof ( real_T ) ) ; _rtB -> oegy1whsp5 = _rtP -> P_68 ; } _rtB
-> mqekmji2jy [ 0 ] = _rtB -> dlh2uazjka ; _rtB -> mqekmji2jy [ 1 ] = _rtP ->
P_64 * npiyznthqi ; ssCallAccelRunBlock ( S , 13 , 1 , SS_CALL_MDL_OUTPUTS )
; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> jr4hsifv1f = _rtP -> P_69 ; }
if ( 1.0 / o5ibp43cp4 * n4kbehhhau >= _rtP -> P_70 ) { efj5q5ebcq =
o5ibp43cp4 / n4kbehhhau ; if ( efj5q5ebcq > _rtP -> P_25 ) { if ( efj5q5ebcq
> _rtP -> P_23 ) { efj5q5ebcq = _rtP -> P_23 ; } else { if ( efj5q5ebcq <
_rtP -> P_24 ) { efj5q5ebcq = _rtP -> P_24 ; } } tmp = ( ( 1.0 - efj5q5ebcq )
* 0.14285714285714282 + efj5q5ebcq ) * ( 1.0 - efj5q5ebcq ) ; if ( tmp < 0.0
) { npiyznthqi = - muDoubleScalarSqrt ( - tmp ) ; } else { npiyznthqi =
muDoubleScalarSqrt ( tmp ) ; } } else { npiyznthqi = _rtB -> kssh3anhn0 ; }
efj5q5ebcq = n4kbehhhau / _rtB -> lcox2cqw1x / _rtB -> cfjfxf2th0 *
n4kbehhhau * _rtP -> P_28 ; if ( efj5q5ebcq < 0.0 ) { efj5q5ebcq = -
muDoubleScalarSqrt ( muDoubleScalarAbs ( efj5q5ebcq ) ) ; } else { efj5q5ebcq
= muDoubleScalarSqrt ( efj5q5ebcq ) ; } if ( _rtB -> clgr4b120z > _rtP ->
P_26 ) { tmp = _rtP -> P_26 ; } else if ( _rtB -> clgr4b120z < _rtP -> P_27 )
{ tmp = _rtP -> P_27 ; } else { tmp = _rtB -> clgr4b120z ; } _rtB ->
oyqyzhhm42 = efj5q5ebcq * tmp * npiyznthqi * _rtP -> P_29 ; } else {
efj5q5ebcq = 1.0 / o5ibp43cp4 * n4kbehhhau ; if ( efj5q5ebcq > _rtP -> P_17 )
{ if ( efj5q5ebcq > _rtP -> P_15 ) { efj5q5ebcq = _rtP -> P_15 ; } else { if
( efj5q5ebcq < _rtP -> P_16 ) { efj5q5ebcq = _rtP -> P_16 ; } } tmp = ( ( 1.0
- efj5q5ebcq ) * 0.14285714285714282 + efj5q5ebcq ) * ( 1.0 - efj5q5ebcq ) ;
if ( tmp < 0.0 ) { npiyznthqi = - muDoubleScalarSqrt ( - tmp ) ; } else {
npiyznthqi = muDoubleScalarSqrt ( tmp ) ; } } else { npiyznthqi = _rtB ->
jr4hsifv1f ; } efj5q5ebcq = o5ibp43cp4 / _rtB -> lcox2cqw1x / _rtB ->
cfjfxf2th0 * o5ibp43cp4 * _rtP -> P_20 ; if ( efj5q5ebcq < 0.0 ) { efj5q5ebcq
= - muDoubleScalarSqrt ( muDoubleScalarAbs ( efj5q5ebcq ) ) ; } else {
efj5q5ebcq = muDoubleScalarSqrt ( efj5q5ebcq ) ; } if ( _rtB -> pm03vr5zrk >
_rtP -> P_18 ) { tmp = _rtP -> P_18 ; } else if ( _rtB -> pm03vr5zrk < _rtP
-> P_19 ) { tmp = _rtP -> P_19 ; } else { tmp = _rtB -> pm03vr5zrk ; } _rtB
-> oyqyzhhm42 = efj5q5ebcq * tmp * npiyznthqi * _rtP -> P_21 * _rtP -> P_22 ;
} if ( _rtB -> oyqyzhhm42 > _rtP -> P_71 ) { _rtB -> p0ej2ncygl = _rtP ->
P_71 ; } else if ( _rtB -> oyqyzhhm42 < _rtP -> P_72 ) { _rtB -> p0ej2ncygl =
_rtP -> P_72 ; } else { _rtB -> p0ej2ncygl = _rtB -> oyqyzhhm42 ; }
ssCallAccelRunBlock ( S , 118 , 49 , SS_CALL_MDL_OUTPUTS ) ; npiyznthqi =
_rtX -> lgbs44xptg ; _rtB -> mszdqvtbos = 1.0 / _rtB -> owjgmyz3gk * _rtX ->
lgbs44xptg ; ssCallAccelRunBlock ( S , 118 , 52 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> owjgmyz3gk = _rtX -> ka43gmkysq ; _rtB -> fx4chyks5v = _rtP -> P_75 *
_rtB -> owjgmyz3gk ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> me5ntqjay1
= _rtP -> P_76 ; _rtB -> no2daczgbz = _rtP -> P_77 ; _rtB -> jkfud5t4pc =
_rtP -> P_78 ; _rtB -> ob0cjycwpc = _rtP -> P_79 ; _rtB -> hsnhugj0z4 = _rtP
-> P_80 ; memcpy ( & _rtB -> edadxgndrq [ 0 ] , & _rtP -> P_81 [ 0 ] , 12U *
sizeof ( real_T ) ) ; memcpy ( & _rtB -> i2lcod32yb [ 0 ] , & _rtP -> P_82 [
0 ] , 9U * sizeof ( real_T ) ) ; } _rtB -> mwi40jynvr [ 0 ] = _rtB ->
me5ntqjay1 ; _rtB -> mwi40jynvr [ 1 ] = _rtB -> no2daczgbz ; _rtB ->
mwi40jynvr [ 2 ] = _rtB -> jkfud5t4pc ; _rtB -> mwi40jynvr [ 3 ] = _rtB ->
ob0cjycwpc ; _rtB -> mwi40jynvr [ 4 ] = _rtB -> hsnhugj0z4 ;
ssCallAccelRunBlock ( S , 2 , 1 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> bzbb3dscs0
= _rtB -> p0ej2ncygl / ( _rtB -> p0ej2ncygl + _rtB -> o4etjyeod5 ) * _rtP ->
P_83 ; _rtB -> bxrb3pjgcb = ( real32_T ) _rtB -> bzbb3dscs0 ; _rtB ->
fh1ao455t3 = ( real32_T ) _rtB -> eebr3qqx0u [ 0 ] ; _rtB -> aeal0w25ez = (
real32_T ) _rtB -> eebr3qqx0u [ 1 ] ; _rtB -> bkpnl3pb55 = ( real32_T ) _rtB
-> b2luvekoek ; c4l11istf0 = _rtX -> iqp0o3u0ph ; _rtB -> ho1qnfguxm = 1.0 /
( _rtP -> P_85 * _rtX -> iqp0o3u0ph ) * _rtB -> bchvsczbjy ; if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> js1uavffvq = _rtP -> P_747 ; } _rtB
-> pmiqvnd0gh = ( real32_T ) _rtB -> ho1qnfguxm - _rtB -> js1uavffvq ; _rtB
-> pnx1tnohqx = ( real32_T ) ( _rtP -> P_86 * _rtB -> p0ej2ncygl ) ; _rtB ->
ddovbhztt5 = ( real32_T ) ( _rtP -> P_87 * _rtB -> o4etjyeod5 ) ; _rtB ->
ijl3bksril = _rtP -> P_88 * b11wdxnlxt ; gen03hfvbg = _rtX -> iynqfp2xbi ;
_rtB -> n103e0ixee = 1.0 / ( _rtP -> P_90 * _rtX -> iynqfp2xbi ) * _rtB ->
b2luvekoek ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> ki4oi3drci = _rtP
-> P_91 ; _rtB -> jmttaom2rf = _rtP -> P_92 ; for ( i = 0 ; i < 6 ; i ++ ) {
_rtB -> cp01qk3mjv [ i ] = _rtP -> P_93 [ i ] ; } } _rtB -> jzkasgtoic [ 0 ]
= _rtB -> ki4oi3drci ; _rtB -> jzkasgtoic [ 1 ] = _rtB -> jmttaom2rf ;
ssCallAccelRunBlock ( S , 1 , 1 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> indhq4wak4
= _rtP -> P_94 * _rtB -> lsyc0sxhxh ; if ( _rtB -> eebr3qqx0u [ 1 ] > _rtP ->
P_97 ) { tmp = _rtP -> P_97 ; } else if ( _rtB -> eebr3qqx0u [ 1 ] < _rtP ->
P_98 ) { tmp = _rtP -> P_98 ; } else { tmp = _rtB -> eebr3qqx0u [ 1 ] ; }
_rtB -> le0kdrwsw5 = ( real32_T ) ( _rtP -> P_95 * _rtB -> indhq4wak4 * _rtP
-> P_96 / tmp ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> ldjrvtlkq4 =
_rtB -> ipni0rpjg1 ; _rtB -> hscm1hdjfm = _rtP -> P_439 * _rtB -> ldjrvtlkq4
; _rtDW -> estlkslffw = _rtB -> hscm1hdjfm ; ssWriteToDataStoreWithPath ( S ,
_rtDW -> ofu0g31ksp ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write"
, NULL ) ; _rtB -> lfhmjay0c0 = _rtP -> P_440 * _rtB -> bxrb3pjgcb ; _rtDW ->
dpzir5hccd = _rtB -> lfhmjay0c0 ; ssWriteToDataStoreWithPath ( S , _rtDW ->
mogcuu34yn ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write1"
, NULL ) ; ic3wqfpram_idx_0 = _rtP -> P_441 [ 0 ] ; ic3wqfpram_idx_1 = _rtP
-> P_441 [ 1 ] ; pn0idallhu_idx_0 = _rtDW -> avtbwzqnkf [ 0 ] ;
pn0idallhu_idx_1 = _rtDW -> avtbwzqnkf [ 1 ] ; jsgk2hka41_idx_0 = _rtDW ->
avtbwzqnkf [ 0 ] - _rtP -> P_442 [ 0 ] ; jsgk2hka41_idx_1 = _rtDW ->
avtbwzqnkf [ 1 ] - _rtP -> P_442 [ 1 ] ; btosikvjyf [ 0 ] = _rtP -> P_444 [ 0
] * jsgk2hka41_idx_0 + _rtP -> P_444 [ 2 ] * jsgk2hka41_idx_1 ; btosikvjyf [
1 ] = _rtP -> P_444 [ 1 ] * jsgk2hka41_idx_0 + _rtP -> P_444 [ 3 ] *
jsgk2hka41_idx_1 ; finyivsrdi = _rtDW -> poa5fptxm4 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/custom_filter/Data Store Read8"
, NULL ) ; _rtB -> la1bi141vb = _rtP -> P_446 * _rtDW -> owcamicoch ; if (
_rtB -> la1bi141vb > _rtP -> P_447 ) { e0r0t533ao = _rtP -> P_447 ; } else if
( _rtB -> la1bi141vb < _rtP -> P_448 ) { e0r0t533ao = _rtP -> P_448 ; } else
{ e0r0t533ao = _rtB -> la1bi141vb ; } cbpfnq4pxd = _rtP -> P_449 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/custom_filter/Data Store Read1"
, NULL ) ; _rtB -> blsiovdtlr = _rtP -> P_450 * _rtDW -> owcamicoch ; if (
_rtB -> blsiovdtlr > _rtP -> P_451 ) { dpajlxfdyx_idx_0 = _rtP -> P_451 ; }
else if ( _rtB -> blsiovdtlr < _rtP -> P_452 ) { dpajlxfdyx_idx_0 = _rtP ->
P_452 ; } else { dpajlxfdyx_idx_0 = _rtB -> blsiovdtlr ; } alqkjudhu3 =
cbpfnq4pxd - dpajlxfdyx_idx_0 ; ssReadFromDataStoreWithPath ( S , _rtDW ->
ess4wlwley ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/Data Store Read1"
, NULL ) ; _rtB -> o5smpqnaet = _rtP -> P_453 * _rtDW -> bpo1eig15d ; if (
_rtB -> o5smpqnaet > _rtP -> P_454 ) { o3mfdsmmfb = _rtB -> le0kdrwsw5 * _rtB
-> aeal0w25ez / _rtP -> P_262 ; } else { o3mfdsmmfb = _rtB -> le0kdrwsw5 ; }
e4orw3vqsn = _rtDW -> bsbxmlf10r ; cbpfnq4pxd = _rtP -> P_456 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> ourjtqa0v4 ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/Data Store Read3"
, NULL ) ; _rtB -> dnzxvrt3hi = _rtP -> P_457 * _rtDW -> o0hytehsup ; if (
_rtB -> dnzxvrt3hi > _rtP -> P_458 ) {
KD_cl_harness_forthao_breach_acc_LookUp_real32_T_real32_T ( & ( emptrcbnkv )
, _rtP -> P_261 , e4orw3vqsn , _rtP -> P_260 , 1U ) ; o3mfdsmmfb = (
cbpfnq4pxd - emptrcbnkv ) * _rtB -> ddovbhztt5 + o3mfdsmmfb * emptrcbnkv ; }
ssReadFromDataStoreWithPath ( S , _rtDW -> gl5aakmwtq ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/Data Store Read8"
, NULL ) ; _rtB -> k2jykilip4 = _rtP -> P_459 * _rtDW -> jnju4d4o03 ;
jfmtdksnh0 = _rtP -> P_462 ; if ( _rtB -> pmiqvnd0gh > _rtP -> P_463 ) {
kaqx4nados = _rtP -> P_463 ; } else if ( _rtB -> pmiqvnd0gh < _rtP -> P_464 )
{ kaqx4nados = _rtP -> P_464 ; } else { kaqx4nados = _rtB -> pmiqvnd0gh ; }
jfmtdksnh0 += kaqx4nados ; u0 = jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_467 ; if
( u0 > _rtP -> P_465 ) { u0 = _rtP -> P_465 ; } else { if ( u0 < _rtP ->
P_466 ) { u0 = _rtP -> P_466 ; } } if ( jfmtdksnh0 > _rtP -> P_468 ) {
dpajlxfdyx_idx_0 = _rtP -> P_468 ; } else if ( jfmtdksnh0 < _rtP -> P_469 ) {
dpajlxfdyx_idx_0 = _rtP -> P_469 ; } else { dpajlxfdyx_idx_0 = jfmtdksnh0 ; }
o3mfdsmmfb += ( _rtB -> ldjrvtlkq4 - _rtDW -> pybwwu5s4d ) * _rtB ->
k2jykilip4 * _rtP -> P_461 / u0 / dpajlxfdyx_idx_0 - _rtB -> ddovbhztt5 ; if
( o3mfdsmmfb > _rtP -> P_470 ) { o3mfdsmmfb = _rtP -> P_470 ; } else { if (
o3mfdsmmfb < _rtP -> P_471 ) { o3mfdsmmfb = _rtP -> P_471 ; } } _rtB ->
cytczbxazy = finyivsrdi * e0r0t533ao + alqkjudhu3 * o3mfdsmmfb ; jfmtdksnh0 =
_rtB -> cytczbxazy + _rtB -> ddovbhztt5 ; if ( jfmtdksnh0 > _rtP -> P_472 ) {
dpajlxfdyx_idx_0 = _rtP -> P_472 ; } else if ( jfmtdksnh0 < _rtP -> P_473 ) {
dpajlxfdyx_idx_0 = _rtP -> P_473 ; } else { dpajlxfdyx_idx_0 = jfmtdksnh0 ; }
orelggziy4 = _rtB -> cytczbxazy / dpajlxfdyx_idx_0 * _rtP -> P_474 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> h5rpc5xiyn ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read8"
, NULL ) ; jfmtdksnh0 = _rtDW -> hyhv0echnn ; _rtB -> hqg1hpmaaw = _rtP ->
P_475 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_476 ; if ( _rtB -> hqg1hpmaaw >
jfmtdksnh0 ) { _rtB -> dobwfafcm0 = orelggziy4 ; } else { _rtB -> dobwfafcm0
= _rtB -> bxrb3pjgcb ; } btosikvjyf [ 0 ] = _rtB -> ldjrvtlkq4 - btosikvjyf [
0 ] ; jfmtdksnh0 = _rtDW -> j5f3ay4xaq ; ic3wqfpram_idx_0 = ( btosikvjyf [ 0
] - ic3wqfpram_idx_0 ) - _rtP -> P_478 [ 0 ] * jfmtdksnh0 ; dpajlxfdyx_idx_0
= ( ( _rtB -> dobwfafcm0 - btosikvjyf [ 1 ] ) - ic3wqfpram_idx_1 ) - _rtP ->
P_478 [ 1 ] * jfmtdksnh0 ; cbpfnq4pxd = _rtP -> P_480 * jfmtdksnh0 ;
jfmtdksnh0 = _rtP -> P_481 [ 0 ] * jsgk2hka41_idx_0 + _rtP -> P_481 [ 1 ] *
jsgk2hka41_idx_1 ; _rtB -> ic0xftdx3y = ( ( _rtP -> P_479 [ 0 ] *
ic3wqfpram_idx_0 + _rtP -> P_479 [ 1 ] * dpajlxfdyx_idx_0 ) + cbpfnq4pxd ) +
jfmtdksnh0 ; _rtB -> khafhjxib1 = _rtB -> ic0xftdx3y - _rtDW -> ackerqxqlr ;
jfmtdksnh0 = _rtDW -> c1qvpfpyqu ; o3mfdsmmfb = _rtDW -> em10zry3vm ;
ssReadFromDataStoreWithPath ( S , _rtDW -> nqxydshzsv ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read16"
, NULL ) ; _rtB -> dxbeigwbxl = _rtP -> P_485 * _rtDW -> dhb1ak5ywv ; if (
_rtB -> dxbeigwbxl > _rtP -> P_486 ) { exrgmvycyf_idx_0 = _rtB -> khafhjxib1
; exrgmvycyf_idx_1 = jfmtdksnh0 ; exrgmvycyf_idx_2 = o3mfdsmmfb ; } else {
exrgmvycyf_idx_0 = _rtDW -> cz55ow2si1 [ 0 ] ; exrgmvycyf_idx_1 = _rtDW ->
cz55ow2si1 [ 1 ] ; exrgmvycyf_idx_2 = _rtDW -> cz55ow2si1 [ 2 ] ; } _rtB ->
pbopc5e2xk = _rtP -> P_488 * exrgmvycyf_idx_1 ; _rtDW -> n5pkawvqdo = _rtB ->
pbopc5e2xk ; ssWriteToDataStoreWithPath ( S , _rtDW -> i5qc0rf4ul ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write10"
, NULL ) ; _rtB -> fhegodw1bv = _rtP -> P_489 * exrgmvycyf_idx_2 ; _rtDW ->
c1deueau4e = _rtB -> fhegodw1bv ; ssWriteToDataStoreWithPath ( S , _rtDW ->
jl3aimob5t ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write11"
, NULL ) ; _rtB -> k2xoaosf3f = _rtP -> P_490 * exrgmvycyf_idx_0 ; _rtDW ->
mi5h1pks4n = _rtB -> k2xoaosf3f ; ssWriteToDataStoreWithPath ( S , _rtDW ->
jzhsquaa0d ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write12"
, NULL ) ; ssReadFromDataStoreWithPath ( S , _rtDW -> h5rpc5xiyn ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read9"
, NULL ) ; jfmtdksnh0 = _rtDW -> hyhv0echnn ; _rtB -> m3engjean1 = _rtP ->
P_491 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_492 ; if ( _rtB -> m3engjean1 >
jfmtdksnh0 ) { ic3wqfpram_idx_1 = _rtB -> cytczbxazy ; } else {
ic3wqfpram_idx_1 = _rtB -> pnx1tnohqx ; } ic3wqfpram_idx_0 = _rtP -> P_493 *
kaqx4nados + _rtP -> P_494 ; ssReadFromDataStoreWithPath ( S , _rtDW ->
drhj21kmpw ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read14"
, NULL ) ; _rtB -> gkhrttsbg1 = _rtP -> P_495 * _rtDW -> fllyhv1jnh ;
batdnpsvim = _rtB -> gkhrttsbg1 + _rtB -> bkpnl3pb55 ; finyivsrdi = _rtP ->
P_496 ; jfmtdksnh0 = _rtDW -> o04t4yciip ; btosikvjyf [ 0 ] = _rtP -> P_499 [
0 ] * _rtDW -> h4gbii3cbq + _rtP -> P_499 [ 2 ] * jfmtdksnh0 ; btosikvjyf [ 1
] = _rtP -> P_499 [ 1 ] * _rtDW -> h4gbii3cbq ; btosikvjyf [ 1 ] += _rtP ->
P_499 [ 3 ] * jfmtdksnh0 ; cbpfnq4pxd = _rtDW -> lzwd5z4dbk ;
ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter/Data Store Read8"
, NULL ) ; _rtB -> cefzy5i3uw = _rtP -> P_501 * _rtDW -> owcamicoch ; if (
_rtB -> cefzy5i3uw > _rtP -> P_502 ) { alqkjudhu3 = _rtP -> P_502 ; } else if
( _rtB -> cefzy5i3uw < _rtP -> P_503 ) { alqkjudhu3 = _rtP -> P_503 ; } else
{ alqkjudhu3 = _rtB -> cefzy5i3uw ; } kaqx4nados = _rtP -> P_504 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter/Data Store Read1"
, NULL ) ; jfmtdksnh0 = _rtDW -> owcamicoch ; _rtB -> pyz3jksooh = _rtP ->
P_505 * jfmtdksnh0 ; _rtB -> em05kjxq5f = _rtB -> fh1ao455t3 * _rtB ->
aeal0w25ez * _rtP -> P_508 ; if ( _rtB -> pyz3jksooh > _rtP -> P_506 ) {
dpajlxfdyx_idx_0 = _rtP -> P_506 ; } else if ( _rtB -> pyz3jksooh < _rtP ->
P_507 ) { dpajlxfdyx_idx_0 = _rtP -> P_507 ; } else { dpajlxfdyx_idx_0 = _rtB
-> pyz3jksooh ; } _rtB -> bb2txpcrdw = ( kaqx4nados - dpajlxfdyx_idx_0 ) * (
_rtB -> em05kjxq5f - _rtDW -> dgfekwwlr1 ) + cbpfnq4pxd * alqkjudhu3 ;
cbpfnq4pxd = _rtDW -> dw2dt5amj1 ; ssReadFromDataStoreWithPath ( S , _rtDW ->
iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter1/Data Store Read8"
, NULL ) ; _rtB -> fbsgkm3jsf = _rtP -> P_511 * _rtDW -> owcamicoch ; if (
_rtB -> fbsgkm3jsf > _rtP -> P_512 ) { alqkjudhu3 = _rtP -> P_512 ; } else if
( _rtB -> fbsgkm3jsf < _rtP -> P_513 ) { alqkjudhu3 = _rtP -> P_513 ; } else
{ alqkjudhu3 = _rtB -> fbsgkm3jsf ; } kaqx4nados = _rtP -> P_514 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter1/Data Store Read1"
, NULL ) ; jfmtdksnh0 = _rtDW -> owcamicoch ; _rtB -> mtwomkip2g = _rtP ->
P_515 * jfmtdksnh0 ; if ( _rtB -> mtwomkip2g > _rtP -> P_516 ) {
dpajlxfdyx_idx_0 = _rtP -> P_516 ; } else if ( _rtB -> mtwomkip2g < _rtP ->
P_517 ) { dpajlxfdyx_idx_0 = _rtP -> P_517 ; } else { dpajlxfdyx_idx_0 = _rtB
-> mtwomkip2g ; } _rtB -> czspnnf2wz = ( kaqx4nados - dpajlxfdyx_idx_0 ) * (
_rtB -> aeal0w25ez - _rtDW -> letoggxozl ) + cbpfnq4pxd * alqkjudhu3 ; for (
i_p = 0 ; i_p < 2 ; i_p ++ ) { btosikvjyf [ i_p ] += ( ( _rtP -> P_519 [ i_p
+ 2 ] * 0.0F + _rtP -> P_519 [ i_p ] * 0.0F ) + _rtP -> P_519 [ i_p + 4 ] *
_rtB -> bb2txpcrdw ) + _rtP -> P_519 [ i_p + 6 ] * _rtB -> czspnnf2wz ; }
gwzyst3ou3_p = _rtP -> P_520 [ 0 ] * btosikvjyf [ 0 ] + _rtP -> P_520 [ 1 ] *
btosikvjyf [ 1 ] ; s60_iter = 1 ; meppapiqj0 = ( finyivsrdi != 0.0F ) ; while
( meppapiqj0 && ( s60_iter <= 5 ) ) { for ( i = 0 ; i < 9 ; i ++ ) {
frrr5abd2i [ i ] = _rtP -> P_229 [ i ] ; fbk03eccj1 [ i ] = _rtP -> P_230 [ i
] ; phcrozezwb [ i ] = _rtP -> P_231 [ i ] ; } jmuta2homi = _rtP -> P_232 ;
cbpfnq4pxd = _rtP -> P_233 ; alqkjudhu3 = _rtP -> P_234 ; finyivsrdi = _rtP
-> P_235 ; e0r0t533ao = _rtP -> P_236 * e4orw3vqsn ; jsgk2hka41_idx_1 = _rtP
-> P_237 * _rtB -> aeal0w25ez ; if ( _rtB -> ldjrvtlkq4 > _rtP -> P_238 ) {
km03xn13id = _rtP -> P_238 ; } else if ( _rtB -> ldjrvtlkq4 < _rtP -> P_239 )
{ km03xn13id = _rtP -> P_239 ; } else { km03xn13id = _rtB -> ldjrvtlkq4 ; }
plknkmyedj = _rtP -> P_240 ; pyabwb0ags = _rtP -> P_241 * e0r0t533ao ; if (
pyabwb0ags > _rtP -> P_242 ) { pyabwb0ags = _rtP -> P_242 ; } else { if (
pyabwb0ags < _rtP -> P_243 ) { pyabwb0ags = _rtP -> P_243 ; } } a1jrsglzzi =
_rtP -> P_244 * gwzyst3ou3_p ; ssReadFromDataStoreWithPath ( S , _rtDW ->
drfkeqzjbb ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/While_Iterator_Subsystem/newton/update/Data Store Read11"
, NULL ) ; _rtB -> crbbi2ic45 = _rtP -> P_245 * _rtDW -> ayjpjfupkc ;
fvhzusu422 = _rtP -> P_246 * _rtB -> ldjrvtlkq4 ; if ( a1jrsglzzi > _rtP ->
P_247 ) { fzccphw1bz = _rtP -> P_247 ; } else if ( a1jrsglzzi < _rtP -> P_248
) { fzccphw1bz = _rtP -> P_248 ; } else { fzccphw1bz = a1jrsglzzi ; } if (
_rtDW -> dvtr5mddec != 0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW ->
ehd3s5jupn = _rtP -> P_192 ; } _rtDW -> dvtr5mddec = 1U ; for ( ffd3q0dmho =
1 ; ffd3q0dmho <= _rtP -> P_807 ; ffd3q0dmho ++ ) { if ( ffd3q0dmho > _rtP ->
P_808 ) { i = _rtP -> P_808 ; } else if ( ffd3q0dmho < _rtP -> P_809 ) { i =
_rtP -> P_809 ; } else { i = ffd3q0dmho ; } i -- ; c2fdcpgrsp = e0r0t533ao -
phcrozezwb [ i ] ; ehyje10v1p = c2fdcpgrsp * c2fdcpgrsp ; c2fdcpgrsp =
jsgk2hka41_idx_1 - fbk03eccj1 [ i ] ; a3jnflwpkj = ( ( 0.0F - ehyje10v1p ) -
c2fdcpgrsp * c2fdcpgrsp ) / ( cbpfnq4pxd * cbpfnq4pxd * _rtP -> P_189 ) ;
KD_cl_harness_forthao_breach_acc_LookUp_real32_T_real32_T ( & ( ckkx05hfhz )
, _rtP -> P_191 , a3jnflwpkj , _rtP -> P_190 , 102U ) ; _rtB -> eprfrytaac =
ckkx05hfhz * frrr5abd2i [ i ] + _rtDW -> ehd3s5jupn ; _rtDW -> ehd3s5jupn =
_rtB -> eprfrytaac ; } if ( alqkjudhu3 > _rtP -> P_251 ) { alqkjudhu3 = _rtP
-> P_251 ; } else { if ( alqkjudhu3 < _rtP -> P_252 ) { alqkjudhu3 = _rtP ->
P_252 ; } } if ( ic3wqfpram_idx_0 > _rtP -> P_249 ) { dpajlxfdyx_idx_0 = _rtP
-> P_249 ; } else if ( ic3wqfpram_idx_0 < _rtP -> P_250 ) { dpajlxfdyx_idx_0
= _rtP -> P_250 ; } else { dpajlxfdyx_idx_0 = ic3wqfpram_idx_0 ; } finyivsrdi
= finyivsrdi / dpajlxfdyx_idx_0 / alqkjudhu3 / alqkjudhu3 ; if ( finyivsrdi >
_rtP -> P_253 ) { finyivsrdi = _rtP -> P_253 ; } else { if ( finyivsrdi <
_rtP -> P_254 ) { finyivsrdi = _rtP -> P_254 ; } } alqkjudhu3 =
muSingleScalarSqrt ( finyivsrdi ) ; rtPrevAction = _rtDW -> awpbtqxcnq ;
rtAction = ( int8_T ) ! ( fvhzusu422 / fzccphw1bz <= 0.4167F ) ; _rtDW ->
awpbtqxcnq = rtAction ; if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
ssSetSolverNeedsReset ( S ) ; break ; } } switch ( rtAction ) { case 0 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } u0 = ( _rtP -> P_195 + jmuta2homi ) *
_rtP -> P_196 ; if ( u0 > _rtP -> P_197 ) { u0 = _rtP -> P_197 ; } else { if
( u0 < _rtP -> P_198 ) { u0 = _rtP -> P_198 ; } } u0 = jmuta2homi / u0 ; if (
u0 > _rtP -> P_199 ) { u0 = _rtP -> P_199 ; } else { if ( u0 < _rtP -> P_200
) { u0 = _rtP -> P_200 ; } } _rtB -> bihzjyslyy [ 0 ] = _rtB -> eprfrytaac *
alqkjudhu3 * muSingleScalarSqrt ( u0 ) ; u0 = ( _rtP -> P_193 + jmuta2homi )
* _rtP -> P_194 ; if ( u0 > _rtP -> P_201 ) { u0 = _rtP -> P_201 ; } else {
if ( u0 < _rtP -> P_202 ) { u0 = _rtP -> P_202 ; } } u0 = jmuta2homi / u0 ;
if ( u0 > _rtP -> P_203 ) { u0 = _rtP -> P_203 ; } else { if ( u0 < _rtP ->
P_204 ) { u0 = _rtP -> P_204 ; } } _rtB -> bihzjyslyy [ 1 ] = _rtB ->
eprfrytaac * alqkjudhu3 * muSingleScalarSqrt ( u0 ) * a1jrsglzzi ; _rtDW ->
l4mofmlly2 = 4 ; break ; case 1 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } if ( a1jrsglzzi > _rtP -> P_209 ) { dpajlxfdyx_idx_0 = _rtP -> P_209 ;
} else if ( a1jrsglzzi < _rtP -> P_210 ) { dpajlxfdyx_idx_0 = _rtP -> P_210 ;
} else { dpajlxfdyx_idx_0 = a1jrsglzzi ; } cbpfnq4pxd = fvhzusu422 /
dpajlxfdyx_idx_0 ; if ( jmuta2homi > _rtP -> P_212 ) { dpajlxfdyx_idx_0 =
_rtP -> P_212 ; } else if ( jmuta2homi < _rtP -> P_213 ) { dpajlxfdyx_idx_0 =
_rtP -> P_213 ; } else { dpajlxfdyx_idx_0 = jmuta2homi ; } u0 = ( (
jmuta2homi - _rtP -> P_207 ) * ( _rtP -> P_208 - cbpfnq4pxd ) / _rtP -> P_211
/ dpajlxfdyx_idx_0 + cbpfnq4pxd ) * ( _rtP -> P_214 - cbpfnq4pxd ) ; if ( u0
> _rtP -> P_215 ) { u0 = _rtP -> P_215 ; } else { if ( u0 < _rtP -> P_216 ) {
u0 = _rtP -> P_216 ; } } _rtB -> bihzjyslyy [ 1 ] = a1jrsglzzi * _rtB ->
eprfrytaac * alqkjudhu3 * muSingleScalarSqrt ( u0 ) ; u0 = ( ( jmuta2homi +
_rtP -> P_217 ) * fvhzusu422 + ( jmuta2homi - _rtP -> P_218 ) * a1jrsglzzi )
* ( _rtP -> P_205 * jmuta2homi * ( a1jrsglzzi - fvhzusu422 ) ) ; if ( u0 >
_rtP -> P_219 ) { u0 = _rtP -> P_219 ; } else { if ( u0 < _rtP -> P_220 ) {
u0 = _rtP -> P_220 ; } } u0 = muSingleScalarSqrt ( u0 ) ; if ( u0 > _rtP ->
P_221 ) { u0 = _rtP -> P_221 ; } else { if ( u0 < _rtP -> P_222 ) { u0 = _rtP
-> P_222 ; } } _rtB -> bihzjyslyy [ 0 ] = ( ( jmuta2homi - _rtP -> P_206 ) *
a1jrsglzzi + fvhzusu422 ) / u0 * ( _rtB -> eprfrytaac * alqkjudhu3 ) ; _rtDW
-> kltb44md1r = 4 ; break ; } cbpfnq4pxd = ic3wqfpram_idx_1 - _rtB ->
bihzjyslyy [ 1 ] ; ssReadFromDataStoreWithPath ( S , _rtDW -> ko2ysb3l22 ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/While_Iterator_Subsystem/newton/update/Data Store Read16"
, NULL ) ; _rtB -> mzt0y0nfo5 = _rtP -> P_255 * _rtDW -> nqvcv4lcej ;
meppapiqj0 = ( _rtB -> mzt0y0nfo5 > _rtP -> P_256 ) ;
ssReadFromDataStoreWithPath ( S , _rtDW -> drfkeqzjbb ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/While_Iterator_Subsystem/newton/update/Data Store Read1"
, NULL ) ; _rtB -> iwz44y4cr5 = _rtP -> P_257 * _rtDW -> ayjpjfupkc ; if (
meppapiqj0 ) { u0 = _rtB -> bihzjyslyy [ 0 ] * _rtB -> bihzjyslyy [ 0 ] +
_rtB -> crbbi2ic45 ; if ( u0 > _rtP -> P_227 ) { u0 = _rtP -> P_227 ; } else
{ if ( u0 < _rtP -> P_228 ) { u0 = _rtP -> P_228 ; } } cbpfnq4pxd *= 1.0F /
u0 * _rtB -> bihzjyslyy [ 0 ] ; } else { u0 = _rtB -> iwz44y4cr5 + _rtB ->
bihzjyslyy [ 0 ] ; if ( u0 > _rtP -> P_225 ) { u0 = _rtP -> P_225 ; } else {
if ( u0 < _rtP -> P_226 ) { u0 = _rtP -> P_226 ; } } cbpfnq4pxd *= 1.0F / u0
; } alqkjudhu3 = ( a1jrsglzzi + cbpfnq4pxd ) * _rtP -> P_258 ; rtPrevAction =
_rtDW -> g0pejldppu ; rtAction = ( int8_T ) ! ( pyabwb0ags < 15.0F ) ; _rtDW
-> g0pejldppu = rtAction ; if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
ssSetSolverNeedsReset ( S ) ; break ; } } switch ( rtAction ) { case 0 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } cbpfnq4pxd = pyabwb0ags / _rtP ->
P_223 ; _rtB -> hrv5myfmi5 = ( _rtP -> P_224 - cbpfnq4pxd ) * batdnpsvim +
alqkjudhu3 * cbpfnq4pxd ; _rtDW -> oqqlpwtggt = 4 ; break ; case 1 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> hrv5myfmi5 = alqkjudhu3 ;
_rtDW -> hgwa21u3tp = 4 ; break ; } cbpfnq4pxd = _rtP -> P_259 + km03xn13id ;
if ( _rtB -> hrv5myfmi5 < cbpfnq4pxd ) { awl0z0b3sb = cbpfnq4pxd ; } else {
awl0z0b3sb = _rtB -> hrv5myfmi5 ; } if ( _rtB -> hrv5myfmi5 > plknkmyedj ) {
_rtB -> lbwa3jpkws = plknkmyedj ; } else { _rtB -> lbwa3jpkws = awl0z0b3sb ;
} meppapiqj0 = _rtP -> P_837 ; srUpdateBC ( _rtDW -> ljedkvx4od ) ; s60_iter
++ ; } ssReadFromDataStoreWithPath ( S , _rtDW -> i0oacsu105 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read13"
, NULL ) ; _rtB -> hiqxaf3x1i = _rtP -> P_521 * _rtDW -> pmewcnpxdb ; if (
_rtB -> hiqxaf3x1i > _rtP -> P_522 ) { jjkfbyaomr = _rtB -> lbwa3jpkws ; }
else { jjkfbyaomr = batdnpsvim ; } kaqx4nados = _rtP -> P_523 * jjkfbyaomr ;
jfmtdksnh0 = _rtP -> P_526 ; if ( ic3wqfpram_idx_0 > _rtP -> P_524 ) {
dpajlxfdyx_idx_0 = _rtP -> P_524 ; } else if ( ic3wqfpram_idx_0 < _rtP ->
P_525 ) { dpajlxfdyx_idx_0 = _rtP -> P_525 ; } else { dpajlxfdyx_idx_0 =
ic3wqfpram_idx_0 ; } jfmtdksnh0 = kaqx4nados / dpajlxfdyx_idx_0 / jfmtdksnh0
* kaqx4nados * _rtP -> P_527 ; jfmtdksnh0 = muSingleScalarAbs ( jfmtdksnh0 )
; jfmtdksnh0 = muSingleScalarSqrt ( jfmtdksnh0 ) ; if ( kaqx4nados > _rtP ->
P_531 ) { kaqx4nados = _rtP -> P_531 ; } else { if ( kaqx4nados < _rtP ->
P_532 ) { kaqx4nados = _rtP -> P_532 ; } } cbpfnq4pxd = _rtP -> P_530 * _rtB
-> ldjrvtlkq4 / kaqx4nados ; if ( cbpfnq4pxd > _rtP -> P_533 ) { if (
cbpfnq4pxd > _rtP -> P_168 ) { cbpfnq4pxd = _rtP -> P_168 ; } else { if (
cbpfnq4pxd < _rtP -> P_169 ) { cbpfnq4pxd = _rtP -> P_169 ; } } alqkjudhu3 =
_rtP -> P_170 - cbpfnq4pxd ; alqkjudhu3 *= alqkjudhu3 * _rtP -> P_167 +
cbpfnq4pxd ; if ( alqkjudhu3 > _rtP -> P_171 ) { alqkjudhu3 = _rtP -> P_171 ;
} else { if ( alqkjudhu3 < _rtP -> P_172 ) { alqkjudhu3 = _rtP -> P_172 ; } }
kaqx4nados = muSingleScalarSqrt ( alqkjudhu3 ) ; } else { kaqx4nados = _rtP
-> P_166 ; } kaqx4nados = jfmtdksnh0 * rt_Lookup32 ( _rtP -> P_528 , 16 ,
_rtB -> aeal0w25ez , _rtP -> P_529 ) * kaqx4nados * _rtP -> P_534 ; if (
kaqx4nados > _rtP -> P_535 ) { kaqx4nados = _rtP -> P_535 ; } else { if (
kaqx4nados < _rtP -> P_536 ) { kaqx4nados = _rtP -> P_536 ; } }
ssReadFromDataStoreWithPath ( S , _rtDW -> angozbvvee ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read4"
, NULL ) ; jfmtdksnh0 = _rtDW -> hptuorf3i3 ; _rtB -> g50cgr2ero = _rtP ->
P_537 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_538 * _rtB -> g50cgr2ero ; if (
jfmtdksnh0 > _rtP -> P_539 ) { jfmtdksnh0 = _rtP -> P_539 ; } else { if (
jfmtdksnh0 < _rtP -> P_540 ) { jfmtdksnh0 = _rtP -> P_540 ; } } jfmtdksnh0 =
_rtB -> ddovbhztt5 * jfmtdksnh0 / ( _rtP -> P_541 - jfmtdksnh0 ) * _rtP ->
P_542 ; fij5klqz0n = muSingleScalarMin ( kaqx4nados , jfmtdksnh0 ) ; _rtB ->
hvx1cvumuq = _rtP -> P_543 * fij5klqz0n * _rtP -> P_544 ; _rtDW -> bvlm5joqvj
= _rtB -> hvx1cvumuq ; ssWriteToDataStoreWithPath ( S , _rtDW -> o3fzpatiqj ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write13"
, NULL ) ; memcpy ( & dift4gyrha [ 0 ] , & _rtP -> P_545 [ 0 ] , 309U *
sizeof ( real32_T ) ) ; memcpy ( & hsiahk1nnd [ 0 ] , & _rtP -> P_546 [ 0 ] ,
103U * sizeof ( real32_T ) ) ;
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
cl24d41ibh ) , _rtP -> P_549 , _rtB -> aeal0w25ez , _rtP -> P_547 , 19U ,
_rtB -> fh1ao455t3 , _rtP -> P_548 , 19U ) ; ssReadFromDataStoreWithPath ( S
, _rtDW -> lbc21h24p2 ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/set_point_maps/Data Store Read3"
, NULL ) ; _rtB -> hcepujpuwf = _rtP -> P_550 * _rtDW -> enudnf03vn ;
g1ekzbu3oi = cl24d41ibh + _rtB -> hcepujpuwf ; hn15keiut1 = exrgmvycyf_idx_1
- g1ekzbu3oi ;
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
e51a0t11ia ) , _rtP -> P_553 , _rtB -> aeal0w25ez , _rtP -> P_551 , 19U ,
_rtB -> fh1ao455t3 , _rtP -> P_552 , 19U ) ; cbpfnq4pxd = _rtP -> P_554 *
e51a0t11ia ; ssReadFromDataStoreWithPath ( S , _rtDW -> iibzcraycn ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/set_point_maps/Data Store Read1"
, NULL ) ; _rtB -> ardfej0rww = _rtP -> P_555 * _rtDW -> bakpq4fzl0 ;
fwhtla1rft = cbpfnq4pxd + _rtB -> ardfej0rww ; if ( fwhtla1rft > _rtP ->
P_556 ) { fwhtla1rft = _rtP -> P_556 ; } else { if ( fwhtla1rft < _rtP ->
P_557 ) { fwhtla1rft = _rtP -> P_557 ; } } byk21oesq1 = exrgmvycyf_idx_2 -
fwhtla1rft ; kaqx4nados = _rtB -> ddovbhztt5 / _rtP -> P_558 ; jfmtdksnh0 =
_rtP -> P_559 ; fzccphw1bz = _rtP -> P_560 * _rtB -> ldjrvtlkq4 ; ehyje10v1p
= _rtP -> P_561 ; if ( _rtP -> P_563 > _rtP -> P_564 ) { dpajlxfdyx_idx_0 =
_rtP -> P_564 ; } else if ( _rtP -> P_563 < _rtP -> P_565 ) {
dpajlxfdyx_idx_0 = _rtP -> P_565 ; } else { dpajlxfdyx_idx_0 = _rtP -> P_563
; } if ( _rtP -> P_567 > _rtP -> P_568 ) { jsgk2hka41_idx_0 = _rtP -> P_568 ;
} else if ( _rtP -> P_567 < _rtP -> P_569 ) { jsgk2hka41_idx_0 = _rtP ->
P_569 ; } else { jsgk2hka41_idx_0 = _rtP -> P_567 ; } _rtB -> iqg1nj4hwf = (
_rtP -> P_566 - jsgk2hka41_idx_0 ) * kaqx4nados + _rtDW -> frjwyakiph *
dpajlxfdyx_idx_0 ; cbpfnq4pxd = _rtP -> P_570 * _rtB -> iqg1nj4hwf ;
ssReadFromDataStoreWithPath ( S , _rtDW -> dxbshoizcp ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read12"
, NULL ) ; _rtB -> fkwa0nrbz3 = _rtP -> P_571 * _rtDW -> d210tl5n23 ;
meppapiqj0 = ( _rtB -> fkwa0nrbz3 > _rtP -> P_572 ) ;
ssReadFromDataStoreWithPath ( S , _rtDW -> cutqc2g2te ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read2"
, NULL ) ; _rtB -> gkcuuaqdia = _rtP -> P_573 * _rtDW -> nwf1nud1fv ; if (
meppapiqj0 ) {
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
dbt3uojgmq ) , _rtP -> P_163 , _rtB -> aeal0w25ez , _rtP -> P_161 , 19U ,
_rtB -> fh1ao455t3 , _rtP -> P_162 , 19U ) ; not4fp11wk = dbt3uojgmq ; } else
{ not4fp11wk = _rtB -> gkcuuaqdia ; } alqkjudhu3 = _rtP -> P_574 * not4fp11wk
; finyivsrdi = _rtP -> P_575 * _rtB -> aeal0w25ez ; e0r0t533ao = _rtP ->
P_578 ; for ( i = 0 ; i < 9 ; i ++ ) { frrr5abd2i [ i ] = _rtP -> P_576 [ i ]
; fbk03eccj1 [ i ] = _rtP -> P_577 [ i ] ; phcrozezwb [ i ] = _rtP -> P_579 [
i ] ; } ssSetSolverNeedsReset ( S ) ; _rtDW -> owlkbndpg5 = _rtP -> P_302 ;
for ( s60_iter = 1 ; s60_iter <= _rtP -> P_817 ; s60_iter ++ ) { if (
s60_iter > _rtP -> P_818 ) { i = _rtP -> P_818 ; } else if ( s60_iter < _rtP
-> P_819 ) { i = _rtP -> P_819 ; } else { i = s60_iter ; } ffd3q0dmho = i - 1
; jsgk2hka41_idx_1 = alqkjudhu3 - frrr5abd2i [ ffd3q0dmho ] ; c2fdcpgrsp =
jsgk2hka41_idx_1 * jsgk2hka41_idx_1 ; jsgk2hka41_idx_1 = finyivsrdi -
fbk03eccj1 [ ffd3q0dmho ] ; iou1bb3prl = ( ( 0.0F - c2fdcpgrsp ) -
jsgk2hka41_idx_1 * jsgk2hka41_idx_1 ) / ( e0r0t533ao * e0r0t533ao * _rtP ->
P_299 ) ; KD_cl_harness_forthao_breach_acc_LookUp_real32_T_real32_T ( & (
omfw35sfyk ) , _rtP -> P_301 , iou1bb3prl , _rtP -> P_300 , 102U ) ; _rtB ->
o5df4vinc5 = omfw35sfyk * phcrozezwb [ ffd3q0dmho ] + _rtDW -> owlkbndpg5 ;
_rtDW -> owlkbndpg5 = _rtB -> o5df4vinc5 ; } if ( _rtP -> P_583 > _rtP ->
P_584 ) { dpajlxfdyx_idx_0 = _rtP -> P_584 ; } else if ( _rtP -> P_583 < _rtP
-> P_585 ) { dpajlxfdyx_idx_0 = _rtP -> P_585 ; } else { dpajlxfdyx_idx_0 =
_rtP -> P_583 ; } if ( _rtP -> P_586 > _rtP -> P_587 ) { jsgk2hka41_idx_0 =
_rtP -> P_587 ; } else if ( _rtP -> P_586 < _rtP -> P_588 ) {
jsgk2hka41_idx_0 = _rtP -> P_588 ; } else { jsgk2hka41_idx_0 = _rtP -> P_586
; } u0 = _rtP -> P_582 / dpajlxfdyx_idx_0 / jsgk2hka41_idx_0 * _rtP -> P_589
; if ( u0 > _rtP -> P_590 ) { u0 = _rtP -> P_590 ; } else { if ( u0 < _rtP ->
P_591 ) { u0 = _rtP -> P_591 ; } } u0 = muSingleScalarSqrt ( u0 ) ; if ( _rtB
-> o5df4vinc5 > _rtP -> P_580 ) { dpajlxfdyx_idx_0 = _rtP -> P_580 ; } else
if ( _rtB -> o5df4vinc5 < _rtP -> P_581 ) { dpajlxfdyx_idx_0 = _rtP -> P_581
; } else { dpajlxfdyx_idx_0 = _rtB -> o5df4vinc5 ; } if ( u0 > _rtP -> P_592
) { u0 = _rtP -> P_592 ; } else { if ( u0 < _rtP -> P_593 ) { u0 = _rtP ->
P_593 ; } } o3mfdsmmfb = cbpfnq4pxd / dpajlxfdyx_idx_0 / u0 ; cbpfnq4pxd =
o3mfdsmmfb * o3mfdsmmfb ; if ( o3mfdsmmfb > _rtP -> P_596 ) { o3mfdsmmfb =
_rtP -> P_596 ; } else { if ( o3mfdsmmfb < _rtP -> P_597 ) { o3mfdsmmfb =
_rtP -> P_597 ; } } if ( fzccphw1bz / o3mfdsmmfb > _rtP -> P_598 ) {
alqkjudhu3 = fzccphw1bz * fzccphw1bz ; cbpfnq4pxd = ( ( _rtP -> P_295 *
alqkjudhu3 - alqkjudhu3 ) - cbpfnq4pxd ) * ehyje10v1p * _rtP -> P_594 ;
alqkjudhu3 = fzccphw1bz - _rtP -> P_296 * fzccphw1bz ; u0 = alqkjudhu3 *
alqkjudhu3 - cbpfnq4pxd ; if ( u0 > _rtP -> P_297 ) { u0 = _rtP -> P_297 ; }
else { if ( u0 < _rtP -> P_298 ) { u0 = _rtP -> P_298 ; } } if ( _rtP ->
P_594 > _rtP -> P_293 ) { dpajlxfdyx_idx_0 = _rtP -> P_293 ; } else if ( _rtP
-> P_594 < _rtP -> P_294 ) { dpajlxfdyx_idx_0 = _rtP -> P_294 ; } else {
dpajlxfdyx_idx_0 = _rtP -> P_594 ; } if ( _rtP -> P_595 > _rtP -> P_291 ) {
jsgk2hka41_idx_0 = _rtP -> P_291 ; } else if ( _rtP -> P_595 < _rtP -> P_292
) { jsgk2hka41_idx_0 = _rtP -> P_292 ; } else { jsgk2hka41_idx_0 = _rtP ->
P_595 ; } o3mfdsmmfb = ( muSingleScalarSqrt ( u0 ) - alqkjudhu3 ) /
dpajlxfdyx_idx_0 / jsgk2hka41_idx_0 ; } else { o3mfdsmmfb = cbpfnq4pxd ; }
o3mfdsmmfb *= _rtP -> P_599 ; kaqx4nados = rt_Lookup2D32_Normal ( _rtP ->
P_600 , 20 , _rtP -> P_601 , 16 , _rtP -> P_602 , kaqx4nados , 1.0F /
jfmtdksnh0 * o3mfdsmmfb ) * _rtP -> P_603 ; o3cuzyoqg5 = _rtP -> P_604 *
kaqx4nados ; jfmtdksnh0 = _rtP -> P_605 ; cbpfnq4pxd = jfmtdksnh0 -
pn0idallhu_idx_0 ; ssReadFromDataStoreWithPath ( S , _rtDW -> elilh0acjp ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read" ,
NULL ) ; jfmtdksnh0 = _rtDW -> ntmupcyyck ; _rtB -> hasrpixfyh = _rtP ->
P_606 * jfmtdksnh0 ; if ( _rtB -> hasrpixfyh > _rtP -> P_607 ) { pwkaxiafxx =
_rtP -> P_607 ; } else if ( _rtB -> hasrpixfyh < _rtP -> P_608 ) { pwkaxiafxx
= _rtP -> P_608 ; } else { pwkaxiafxx = _rtB -> hasrpixfyh ; } km03xn13id =
cbpfnq4pxd / pwkaxiafxx ; jfmtdksnh0 = _rtP -> P_609 ; plknkmyedj = (
jfmtdksnh0 - pn0idallhu_idx_0 ) * _rtP -> P_610 * ( 1.0F / pwkaxiafxx ) ;
cbpfnq4pxd = _rtP -> P_611 * fij5klqz0n ; ssReadFromDataStoreWithPath ( S ,
_rtDW -> f00eda2bjz ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read1"
, NULL ) ; jfmtdksnh0 = _rtDW -> devn1wdclr ; _rtB -> kzf3qrbzkj = _rtP ->
P_612 * jfmtdksnh0 ; if ( _rtB -> kzf3qrbzkj > _rtP -> P_613 ) { gwzyst3ou3_p
= _rtP -> P_613 ; } else if ( _rtB -> kzf3qrbzkj < _rtP -> P_614 ) {
gwzyst3ou3_p = _rtP -> P_614 ; } else { gwzyst3ou3_p = _rtB -> kzf3qrbzkj ; }
jmuta2homi = ( cbpfnq4pxd - pn0idallhu_idx_1 ) / gwzyst3ou3_p ; fvhzusu422 =
_rtP -> P_615 ; ehyje10v1p = ( _rtP -> P_615 - pn0idallhu_idx_1 ) * _rtP ->
P_616 * ( 1.0F / gwzyst3ou3_p ) ; ssReadFromDataStoreWithPath ( S , _rtDW ->
fnxjjp2lme ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read3"
, NULL ) ; jfmtdksnh0 = _rtDW -> o3z1jsmhkx ; _rtB -> p4ek3tnerm = _rtP ->
P_617 * jfmtdksnh0 ; a1jrsglzzi = _rtB -> p4ek3tnerm - g1ekzbu3oi ;
jfmtdksnh0 = _rtP -> P_618 ; fzccphw1bz = jfmtdksnh0 - fwhtla1rft ;
ssReadFromDataStoreWithPath ( S , _rtDW -> mzsuxn1hbm ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read17"
, NULL ) ; jfmtdksnh0 = _rtDW -> mi05525rde ; _rtB -> cqertkbhh1 = _rtP ->
P_619 * jfmtdksnh0 ; ssReadFromDataStoreWithPath ( S , _rtDW -> a02t5mvtkd ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read18"
, NULL ) ; jfmtdksnh0 = _rtDW -> fuwbxjmtyy ; _rtB -> lqin2qgn0v = _rtP ->
P_620 * jfmtdksnh0 ; pyabwb0ags = _rtP -> P_621 * _rtB -> lqin2qgn0v ;
s60_iter = 1 ; meppapiqj0 = ( _rtP -> P_820 != 0 ) ; while ( meppapiqj0 && (
s60_iter <= 103 ) ) { esndn1d5qn = s60_iter ; alqkjudhu3 = _rtP -> P_264 ;
memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_265 [ 0 ] , 1030U * sizeof
( real32_T ) ) ; if ( esndn1d5qn > _rtP -> P_813 ) { i = _rtP -> P_813 ; }
else if ( esndn1d5qn < _rtP -> P_814 ) { i = _rtP -> P_814 ; } else { i =
esndn1d5qn ; } if ( _rtP -> P_266 [ i - 1 ] > _rtP -> P_267 ) { cbpfnq4pxd =
_rtP -> P_267 ; } else if ( _rtP -> P_266 [ i - 1 ] < _rtP -> P_268 ) {
cbpfnq4pxd = _rtP -> P_268 ; } else { cbpfnq4pxd = _rtP -> P_266 [ i - 1 ] ;
} i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) {
cfpabnsfkw [ i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] *
exrgmvycyf_idx_0 ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_269 [
0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p
= 0 ; i_p < 10 ; i_p ++ ) { dqg1fl5gyp [ i_p ] = _rtB -> l2buyyse4x [ ( i_p +
i ) - 1 ] * hn15keiut1 ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP ->
P_270 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ;
for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { n4vetwv3qv [ i_p ] = _rtB -> l2buyyse4x
[ ( i_p + i ) - 1 ] * byk21oesq1 ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , &
_rtP -> P_271 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T )
cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { np1ecrs5jr [ i_p ] = _rtB
-> l2buyyse4x [ ( i_p + i ) - 1 ] * jjkfbyaomr ; } memcpy ( & _rtB ->
l2buyyse4x [ 0 ] , & _rtP -> P_272 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i
= ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { klzvh1ekin [
i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] * o3cuzyoqg5 ; } memcpy ( &
_rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_273 [ 0 ] , 1030U * sizeof ( real32_T
) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) {
ebqfsagx32 [ i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] * km03xn13id ; }
memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_274 [ 0 ] , 1030U * sizeof
( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p
++ ) { cxofaf120r [ i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] *
plknkmyedj ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_275 [ 0 ] ,
1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ;
i_p < 10 ; i_p ++ ) { bfa5h0zq23 [ i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) -
1 ] * jmuta2homi ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_276 [
0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p
= 0 ; i_p < 10 ; i_p ++ ) { fa4aelt32d [ i_p ] = _rtB -> l2buyyse4x [ ( i_p +
i ) - 1 ] * ehyje10v1p ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP ->
P_277 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ;
for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { p22ala5lq4 [ i_p ] = _rtB -> l2buyyse4x
[ ( i_p + i ) - 1 ] * a1jrsglzzi ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , &
_rtP -> P_278 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T )
cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { galtyeac1e [ i_p ] = _rtB
-> l2buyyse4x [ ( i_p + i ) - 1 ] * fzccphw1bz ; } memcpy ( & _rtB ->
l2buyyse4x [ 0 ] , & _rtP -> P_279 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i
= ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { hgfxoibhl0 [
i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] * _rtB -> cqertkbhh1 ; }
memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_280 [ 0 ] , 1030U * sizeof
( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p
++ ) { iqq1rbnkkz [ i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] *
pyabwb0ags ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_281 [ 0 ] ,
1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ;
i_p < 10 ; i_p ++ ) { e2oeg530ux [ i_p ] = ( ( ( ( ( ( ( ( ( ( ( ( cfpabnsfkw
[ i_p ] + dqg1fl5gyp [ i_p ] ) + n4vetwv3qv [ i_p ] ) + np1ecrs5jr [ i_p ] )
+ klzvh1ekin [ i_p ] ) + ebqfsagx32 [ i_p ] ) + cxofaf120r [ i_p ] ) +
bfa5h0zq23 [ i_p ] ) + fa4aelt32d [ i_p ] ) + p22ala5lq4 [ i_p ] ) +
galtyeac1e [ i_p ] ) + hgfxoibhl0 [ i_p ] ) + iqq1rbnkkz [ i_p ] ) - _rtB ->
l2buyyse4x [ ( i_p + i ) - 1 ] ; } cbpfnq4pxd = e2oeg530ux [ 0 ] ; for (
ffd3q0dmho = 0 ; ffd3q0dmho < 9 ; ffd3q0dmho ++ ) { cbpfnq4pxd =
muSingleScalarMax ( cbpfnq4pxd , e2oeg530ux [ ffd3q0dmho + 1 ] ) ; }
j5z4rdmkwv = cbpfnq4pxd ; ase2d1biln = _rtDW -> gme5mt5rhg ; mldy4xfo0l =
_rtDW -> n4b14msae2 ; rtPrevAction = _rtDW -> kqdf0adzeb ; if ( esndn1d5qn ==
1 ) { rtAction = 0 ; } else { rtAction = 1 ; } _rtDW -> kqdf0adzeb = rtAction
; if ( ( rtPrevAction != rtAction ) && ( rtPrevAction == 1 ) ) { switch (
_rtDW -> dqd4zebieo ) { case 0 : hldppkqdr4 ( S ) ; break ; case 1 :
hldppkqdr4 ( S ) ; break ; } _rtDW -> dqd4zebieo = - 1 ; } switch ( rtAction
) { case 0 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 )
!= ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> ms14ozm0qw
= j5z4rdmkwv ; _rtB -> mgx4ixsnsf = _rtP -> P_811 ; _rtDW -> gdpkwnqxlj = 4 ;
break ; case 1 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2
) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } rtPrevAction =
_rtDW -> dqd4zebieo ; rtAction = ( int8_T ) ! ( j5z4rdmkwv < ase2d1biln ) ;
_rtDW -> dqd4zebieo = rtAction ; if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : hldppkqdr4 ( S ) ; break ; case 1 : hldppkqdr4 ( S
) ; break ; } } switch ( rtAction ) { case 0 : if ( rtAction != rtPrevAction
) { nbrxxgteth ( S ) ; } pg1kwe2jso ( j5z4rdmkwv , esndn1d5qn , & _rtB ->
ms14ozm0qw , & _rtB -> mgx4ixsnsf ) ; _rtDW -> pg1kwe2jsoh . ld1fjkwy01 = 4 ;
break ; case 1 : if ( rtAction != rtPrevAction ) { nbrxxgteth ( S ) ; }
pg1kwe2jso ( ase2d1biln , mldy4xfo0l , & _rtB -> ms14ozm0qw , & _rtB ->
mgx4ixsnsf ) ; _rtDW -> gmyvhhtxia . ld1fjkwy01 = 4 ; break ; } _rtDW ->
ozyefxkqtm = 4 ; break ; } meppapiqj0 = ( _rtB -> ms14ozm0qw > alqkjudhu3 ) ;
_rtDW -> gme5mt5rhg = _rtB -> ms14ozm0qw ; _rtDW -> n4b14msae2 = _rtB ->
mgx4ixsnsf ; srUpdateBC ( _rtDW -> hfnjefvf2v ) ; s60_iter ++ ; } if ( _rtB
-> mgx4ixsnsf > _rtP -> P_821 ) { i_p = _rtP -> P_821 ; } else if ( _rtB ->
mgx4ixsnsf < _rtP -> P_822 ) { i_p = _rtP -> P_822 ; } else { i_p = _rtB ->
mgx4ixsnsf ; } jfmtdksnh0 = hsiahk1nnd [ i_p - 1 ] ; if ( jfmtdksnh0 > _rtP
-> P_622 ) { jfmtdksnh0 = _rtP -> P_622 ; } else { if ( jfmtdksnh0 < _rtP ->
P_623 ) { jfmtdksnh0 = _rtP -> P_623 ; } } i_p = ( int32_T ) jfmtdksnh0 ; i =
( int32_T ) jfmtdksnh0 ; ffd3q0dmho = ( int32_T ) jfmtdksnh0 ; s60_iter = (
int32_T ) jfmtdksnh0 ; tmp_p = ( int32_T ) jfmtdksnh0 ; tmp_e = ( int32_T )
jfmtdksnh0 ; tmp_i = ( int32_T ) jfmtdksnh0 ; tmp_m = ( int32_T ) jfmtdksnh0
; tmp_g = ( int32_T ) jfmtdksnh0 ; tmp_j = ( int32_T ) jfmtdksnh0 ; tmp_f = (
int32_T ) jfmtdksnh0 ; tmp_c = ( int32_T ) jfmtdksnh0 ; tmp_k = ( int32_T )
jfmtdksnh0 ; tmp_b = ( int32_T ) jfmtdksnh0 ; _rtB -> j5nsr3o4kc [ 0 ] = ( (
( ( ( ( ( ( ( ( ( ( dift4gyrha [ i_p - 1 ] * exrgmvycyf_idx_0 + _rtP -> P_624
[ i - 1 ] * hn15keiut1 ) + _rtP -> P_625 [ ffd3q0dmho - 1 ] * byk21oesq1 ) +
_rtP -> P_626 [ s60_iter - 1 ] * jjkfbyaomr ) + _rtP -> P_627 [ tmp_p - 1 ] *
o3cuzyoqg5 ) + _rtP -> P_628 [ tmp_e - 1 ] * km03xn13id ) + _rtP -> P_629 [
tmp_i - 1 ] * plknkmyedj ) + _rtP -> P_630 [ tmp_m - 1 ] * jmuta2homi ) +
_rtP -> P_631 [ tmp_g - 1 ] * ehyje10v1p ) + _rtP -> P_632 [ tmp_j - 1 ] *
a1jrsglzzi ) + _rtP -> P_633 [ tmp_f - 1 ] * fzccphw1bz ) + _rtP -> P_634 [
tmp_c - 1 ] * _rtB -> cqertkbhh1 ) + _rtP -> P_635 [ tmp_k - 1 ] * pyabwb0ags
) + _rtP -> P_636 [ tmp_b - 1 ] ; _rtB -> j5nsr3o4kc [ 1 ] = ( ( ( ( ( ( ( (
( ( ( ( dift4gyrha [ i_p ] * exrgmvycyf_idx_0 + _rtP -> P_624 [ i ] *
hn15keiut1 ) + _rtP -> P_625 [ ffd3q0dmho ] * byk21oesq1 ) + _rtP -> P_626 [
s60_iter ] * jjkfbyaomr ) + _rtP -> P_627 [ tmp_p ] * o3cuzyoqg5 ) + _rtP ->
P_628 [ tmp_e ] * km03xn13id ) + _rtP -> P_629 [ tmp_i ] * plknkmyedj ) +
_rtP -> P_630 [ tmp_m ] * jmuta2homi ) + _rtP -> P_631 [ tmp_g ] * ehyje10v1p
) + _rtP -> P_632 [ tmp_j ] * a1jrsglzzi ) + _rtP -> P_633 [ tmp_f ] *
fzccphw1bz ) + _rtP -> P_634 [ tmp_c ] * _rtB -> cqertkbhh1 ) + _rtP -> P_635
[ tmp_k ] * pyabwb0ags ) + _rtP -> P_636 [ tmp_b ] ; _rtB -> j5nsr3o4kc [ 2 ]
= ( ( ( ( ( ( ( ( ( ( ( ( dift4gyrha [ i_p + 1 ] * exrgmvycyf_idx_0 + _rtP ->
P_624 [ i + 1 ] * hn15keiut1 ) + _rtP -> P_625 [ ffd3q0dmho + 1 ] *
byk21oesq1 ) + _rtP -> P_626 [ s60_iter + 1 ] * jjkfbyaomr ) + _rtP -> P_627
[ tmp_p + 1 ] * o3cuzyoqg5 ) + _rtP -> P_628 [ tmp_e + 1 ] * km03xn13id ) +
_rtP -> P_629 [ tmp_i + 1 ] * plknkmyedj ) + _rtP -> P_630 [ tmp_m + 1 ] *
jmuta2homi ) + _rtP -> P_631 [ tmp_g + 1 ] * ehyje10v1p ) + _rtP -> P_632 [
tmp_j + 1 ] * a1jrsglzzi ) + _rtP -> P_633 [ tmp_f + 1 ] * fzccphw1bz ) +
_rtP -> P_634 [ tmp_c + 1 ] * _rtB -> cqertkbhh1 ) + _rtP -> P_635 [ tmp_k +
1 ] * pyabwb0ags ) + _rtP -> P_636 [ tmp_b + 1 ] ; _rtB -> jujcicagpo = _rtP
-> P_637 * _rtB -> j5nsr3o4kc [ 0 ] ; _rtDW -> kk4xei3vwx = _rtB ->
jujcicagpo ; ssWriteToDataStoreWithPath ( S , _rtDW -> dicvjmmruq ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write14"
, NULL ) ; _rtB -> ckhs4krs4m = _rtP -> P_638 * _rtB -> j5nsr3o4kc [ 1 ] ;
_rtDW -> mjfdrfawoz = _rtB -> ckhs4krs4m ; ssWriteToDataStoreWithPath ( S ,
_rtDW -> ayvym5pshc ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write15"
, NULL ) ; _rtB -> k1tmsd4fjt = _rtP -> P_639 * _rtB -> j5nsr3o4kc [ 2 ] ;
_rtDW -> oe1xcqtj2h = _rtB -> k1tmsd4fjt ; ssWriteToDataStoreWithPath ( S ,
_rtDW -> hfec1fq11b ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write16"
, NULL ) ; _rtB -> bf4jmuwmuq = ( int32_T ) ( ( int64_T ) _rtP -> P_832 *
_rtB -> mgx4ixsnsf >> 30 ) ; _rtDW -> fnhncveveb = _rtB -> bf4jmuwmuq ;
ssWriteToDataStoreWithPath ( S , _rtDW -> e44y2okmfs ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write17"
, NULL ) ; ssReadFromDataStoreWithPath ( S , _rtDW -> mn25wyuzm2 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read5"
, NULL ) ; jfmtdksnh0 = _rtDW -> axunmck3pg ; _rtB -> eycuspwp0x = _rtP ->
P_640 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_641 * fij5klqz0n ;
ssReadFromDataStoreWithPath ( S , _rtDW -> bllhrvlbkt ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read6"
, NULL ) ; _rtB -> f1m150kkit = _rtP -> P_642 * _rtDW -> gzmuaempqp ;
j5cdf5jml5 = _rtP -> P_643 * _rtB -> f1m150kkit ; if ( j5cdf5jml5 < _rtP ->
P_644 ) { am2jzeb44a = _rtP -> P_644 ; } else { am2jzeb44a = j5cdf5jml5 ; }
if ( j5cdf5jml5 > jfmtdksnh0 ) { gnrscbmka5 = jfmtdksnh0 ; } else {
gnrscbmka5 = am2jzeb44a ; } ssReadFromDataStoreWithPath ( S , _rtDW ->
iste3vyhz4 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read7"
, NULL ) ; jfmtdksnh0 = _rtDW -> gd2xytkseo ; _rtB -> au0aj2bubh = _rtP ->
P_645 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_646 ; _rtB -> lksu3sv24v =
pwkaxiafxx * _rtB -> j5nsr3o4kc [ 0 ] ; _rtB -> lmn34nxqxt = _rtB ->
j5nsr3o4kc [ 1 ] * gwzyst3ou3_p ; if ( _rtB -> au0aj2bubh > jfmtdksnh0 ) {
_rtB -> cnnxmyxf0o [ 0 ] = _rtB -> eycuspwp0x ; _rtB -> cnnxmyxf0o [ 1 ] =
gnrscbmka5 ; } else { _rtB -> cnnxmyxf0o [ 0 ] = pn0idallhu_idx_0 + _rtB ->
lksu3sv24v ; _rtB -> cnnxmyxf0o [ 1 ] = pn0idallhu_idx_1 + _rtB -> lmn34nxqxt
; } _rtB -> pvzp3twtmn = _rtP -> P_647 * _rtB -> cnnxmyxf0o [ 0 ] ; _rtDW ->
i5n35h2hi0 = _rtB -> pvzp3twtmn ; ssWriteToDataStoreWithPath ( S , _rtDW ->
ppns2wuxkl ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write18"
, NULL ) ; c2fdcpgrsp = _rtP -> P_648 * _rtB -> cnnxmyxf0o [ 1 ] ; _rtB ->
b3n1bpqi33 = _rtP -> P_649 * c2fdcpgrsp * _rtP -> P_650 ; _rtDW -> gj1id4inx4
= _rtB -> b3n1bpqi33 ; ssWriteToDataStoreWithPath ( S , _rtDW -> da43lw3s4d ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write19"
, NULL ) ; _rtB -> m0aoenudi1 = _rtP -> P_651 * _rtB -> fh1ao455t3 ; _rtDW ->
psebtvzqlm = _rtB -> m0aoenudi1 ; ssWriteToDataStoreWithPath ( S , _rtDW ->
be1j1d2kdf ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write2"
, NULL ) ; ssReadFromDataStoreWithPath ( S , _rtDW -> oapn15bbg2 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read11"
, NULL ) ; jfmtdksnh0 = _rtDW -> eppk3q2xfh ; _rtB -> pfhpxpnycz = _rtP ->
P_652 * jfmtdksnh0 ; ssReadFromDataStoreWithPath ( S , _rtDW -> e5xtrvnkj5 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read10"
, NULL ) ; jfmtdksnh0 = _rtDW -> fgc3q11l1t ; _rtB -> nytwaopivh = _rtP ->
P_653 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_654 ; meppapiqj0 = ( _rtB ->
nytwaopivh > jfmtdksnh0 ) ; jfmtdksnh0 = _rtP -> P_656 * jjkfbyaomr ; if (
ic3wqfpram_idx_0 > _rtP -> P_657 ) { ic3wqfpram_idx_0 = _rtP -> P_657 ; }
else { if ( ic3wqfpram_idx_0 < _rtP -> P_658 ) { ic3wqfpram_idx_0 = _rtP ->
P_658 ; } } finyivsrdi = jfmtdksnh0 / ic3wqfpram_idx_0 / _rtP -> P_659 *
jfmtdksnh0 ; if ( jfmtdksnh0 > _rtP -> P_662 ) { dpajlxfdyx_idx_0 = _rtP ->
P_662 ; } else if ( jfmtdksnh0 < _rtP -> P_663 ) { dpajlxfdyx_idx_0 = _rtP ->
P_663 ; } else { dpajlxfdyx_idx_0 = jfmtdksnh0 ; } cbpfnq4pxd = _rtP -> P_661
* _rtB -> ldjrvtlkq4 / dpajlxfdyx_idx_0 ; jfmtdksnh0 = _rtP -> P_664 ; if (
cbpfnq4pxd > jfmtdksnh0 ) { if ( cbpfnq4pxd > _rtP -> P_286 ) { cbpfnq4pxd =
_rtP -> P_286 ; } else { if ( cbpfnq4pxd < _rtP -> P_287 ) { cbpfnq4pxd =
_rtP -> P_287 ; } } alqkjudhu3 = _rtP -> P_288 - cbpfnq4pxd ; alqkjudhu3 *=
alqkjudhu3 * _rtP -> P_285 + cbpfnq4pxd ; if ( alqkjudhu3 > _rtP -> P_289 ) {
alqkjudhu3 = _rtP -> P_289 ; } else { if ( alqkjudhu3 < _rtP -> P_290 ) {
alqkjudhu3 = _rtP -> P_290 ; } } jfmtdksnh0 = muSingleScalarSqrt ( alqkjudhu3
) ; } else { jfmtdksnh0 = _rtP -> P_284 ; } u0 = muSingleScalarSqrt (
muSingleScalarAbs ( _rtP -> P_660 * finyivsrdi ) ) * jfmtdksnh0 ; if ( u0 >
_rtP -> P_665 ) { u0 = _rtP -> P_665 ; } else { if ( u0 < _rtP -> P_666 ) {
u0 = _rtP -> P_666 ; } } a3l10a5g2s = _rtP -> P_655 * c2fdcpgrsp / u0 ;
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
jfmtdksnh0 ) , _rtP -> P_669 , _rtB -> aeal0w25ez , _rtP -> P_667 , 15U ,
a3l10a5g2s , _rtP -> P_668 , 14U ) ; if ( jfmtdksnh0 > _rtP -> P_670 ) {
jsgk2hka41_idx_1 = _rtP -> P_670 ; } else if ( jfmtdksnh0 < _rtP -> P_671 ) {
jsgk2hka41_idx_1 = _rtP -> P_671 ; } else { jsgk2hka41_idx_1 = jfmtdksnh0 ; }
ssReadFromDataStoreWithPath ( S , _rtDW -> mgui2lqiaw ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Data Store Read1"
, NULL ) ; jfmtdksnh0 = _rtDW -> a1ts5brulz ; _rtB -> ilhhlnh5lt = _rtP ->
P_672 * jfmtdksnh0 ; alqkjudhu3 = _rtP -> P_673 * c2fdcpgrsp -
ic3wqfpram_idx_1 ; finyivsrdi = _rtP -> P_676 ; rtPrevAction = _rtDW ->
kl21dgjfyi ; if ( batdnpsvim > _rtP -> P_674 ) { jsgk2hka41_idx_0 = _rtP ->
P_674 ; } else if ( batdnpsvim < _rtP -> P_675 ) { jsgk2hka41_idx_0 = _rtP ->
P_675 ; } else { jsgk2hka41_idx_0 = batdnpsvim ; } rtAction = ( int8_T ) ! (
_rtB -> ldjrvtlkq4 / jsgk2hka41_idx_0 <= 0.4167F ) ; _rtDW -> kl21dgjfyi =
rtAction ; if ( rtPrevAction != rtAction ) { switch ( rtPrevAction ) { case 0
: ssSetSolverNeedsReset ( S ) ; break ; case 1 : ssSetSolverNeedsReset ( S )
; break ; } } switch ( rtAction ) { case 0 : if ( rtAction != rtPrevAction )
{ if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset
( S ) ; } } u0 = ( _rtP -> P_173 + finyivsrdi ) * _rtP -> P_174 ; if ( u0 >
_rtP -> P_175 ) { u0 = _rtP -> P_175 ; } else { if ( u0 < _rtP -> P_176 ) {
u0 = _rtP -> P_176 ; } } eplcvohihr = finyivsrdi / u0 ; if ( eplcvohihr >
_rtP -> P_177 ) { eplcvohihr = _rtP -> P_177 ; } else { if ( eplcvohihr <
_rtP -> P_178 ) { eplcvohihr = _rtP -> P_178 ; } } srUpdateBC ( _rtDW ->
lb2gtdwzqd ) ; break ; case 1 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } if ( batdnpsvim > _rtP -> P_181 ) { jsgk2hka41_idx_0 = _rtP -> P_181 ;
} else if ( batdnpsvim < _rtP -> P_182 ) { jsgk2hka41_idx_0 = _rtP -> P_182 ;
} else { jsgk2hka41_idx_0 = batdnpsvim ; } cbpfnq4pxd = _rtB -> ldjrvtlkq4 /
jsgk2hka41_idx_0 ; if ( finyivsrdi > _rtP -> P_184 ) { jsgk2hka41_idx_0 =
_rtP -> P_184 ; } else if ( finyivsrdi < _rtP -> P_185 ) { jsgk2hka41_idx_0 =
_rtP -> P_185 ; } else { jsgk2hka41_idx_0 = finyivsrdi ; } u0 = ( (
finyivsrdi - _rtP -> P_179 ) * ( _rtP -> P_180 - cbpfnq4pxd ) / _rtP -> P_183
/ jsgk2hka41_idx_0 + cbpfnq4pxd ) * ( _rtP -> P_186 - cbpfnq4pxd ) ; if ( u0
> _rtP -> P_187 ) { u0 = _rtP -> P_187 ; } else { if ( u0 < _rtP -> P_188 ) {
u0 = _rtP -> P_188 ; } } eplcvohihr = muSingleScalarSqrt ( u0 ) ; srUpdateBC
( _rtDW -> hpc0grqivr ) ; break ; } ssReadFromDataStoreWithPath ( S , _rtDW
-> ir12dhrecp ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Data Store Read10"
, NULL ) ; jfmtdksnh0 = _rtDW -> ok4jtsn4bb ; _rtB -> cbjrnzc5n1 = _rtP ->
P_677 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_678 ; if ( _rtB -> cbjrnzc5n1 >
jfmtdksnh0 ) { _rtB -> emejhjadst = eplcvohihr * alqkjudhu3 ; } else { _rtB
-> emejhjadst = alqkjudhu3 ; } ssReadFromDataStoreWithPath ( S , _rtDW ->
cczkkmi5hd ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Data Store Read2"
, NULL ) ; jfmtdksnh0 = _rtDW -> lqempabukg ; _rtB -> ezlhtulb34 = _rtP ->
P_679 * jfmtdksnh0 ; e0r0t533ao = _rtDW -> i5yn1movmy + _rtB -> emejhjadst ;
ssReadFromDataStoreWithPath ( S , _rtDW -> f4uwco4la1 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Data Store Read8"
, NULL ) ; jfmtdksnh0 = _rtDW -> ecauzxzkhl ; _rtB -> eah1hcsb2h = _rtP ->
P_681 * jfmtdksnh0 ; jfmtdksnh0 = ( _rtB -> emejhjadst - _rtDW -> diffnla35e
) * _rtB -> eah1hcsb2h * _rtP -> P_683 ; cbpfnq4pxd = ( real32_T ) ( _rtP ->
P_31 * jfmtdksnh0 ) ; _rtB -> o0aceads0s = _rtDW -> nqyjhyuvcj ; jfmtdksnh0 =
( real32_T ) ( _rtP -> P_32 * _rtB -> o0aceads0s ) ; cbpfnq4pxd -= jfmtdksnh0
; alqkjudhu3 = _rtDW -> fjcoqtw2bx ; jfmtdksnh0 = ( real32_T ) ( _rtP -> P_33
* _rtDW -> fjcoqtw2bx ) ; _rtB -> iq211sbcwf = cbpfnq4pxd - jfmtdksnh0 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> odph5x1drm ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read15"
, NULL ) ; jfmtdksnh0 = _rtDW -> moioiyooa5 ; _rtB -> digibh4z0w = _rtP ->
P_686 * jfmtdksnh0 ; if ( meppapiqj0 ) { _rtB -> cthsuitfz5 = _rtB ->
pfhpxpnycz ; } else if ( _rtB -> digibh4z0w > _rtP -> P_687 ) { u0 = ( ( _rtB
-> ilhhlnh5lt * _rtB -> emejhjadst + jsgk2hka41_idx_1 ) + _rtB -> ezlhtulb34
* e0r0t533ao ) + ( ( ( real32_T ) ( _rtP -> P_30 * _rtB -> o0aceads0s ) +
_rtB -> iq211sbcwf ) + alqkjudhu3 ) ; if ( u0 > _rtP -> P_164 ) { _rtB ->
cthsuitfz5 = _rtP -> P_164 ; } else if ( u0 < _rtP -> P_165 ) { _rtB ->
cthsuitfz5 = _rtP -> P_165 ; } else { _rtB -> cthsuitfz5 = u0 ; } } else {
_rtB -> cthsuitfz5 = jsgk2hka41_idx_1 ; } _rtB -> nytqtnktxr = _rtP -> P_688
* _rtB -> cthsuitfz5 ; _rtDW -> ar2qj33owm = _rtB -> nytqtnktxr ;
ssWriteToDataStoreWithPath ( S , _rtDW -> ksfm4xrloa ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write20"
, NULL ) ; _rtB -> p0f4ijhrpq = _rtP -> P_689 * _rtB -> lbwa3jpkws ; _rtDW ->
pwwmab3rlr = _rtB -> p0f4ijhrpq ; ssWriteToDataStoreWithPath ( S , _rtDW ->
izytyju2r2 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write21"
, NULL ) ; _rtB -> g3rmslxgju = _rtP -> P_690 * _rtB -> le0kdrwsw5 ; _rtDW ->
e10toipvv0 = _rtB -> g3rmslxgju ; ssWriteToDataStoreWithPath ( S , _rtDW ->
i4kzjkoyxu ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write22"
, NULL ) ; _rtB -> ek5z4y4voz = _rtP -> P_691 * orelggziy4 ; _rtDW ->
gmsrqeat5h = _rtB -> ek5z4y4voz ; ssWriteToDataStoreWithPath ( S , _rtDW ->
dhkmzrj1v2 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write23"
, NULL ) ; _rtB -> ergriw4ip1 = _rtP -> P_692 * _rtB -> cytczbxazy ; _rtDW ->
aupt3qrz3y = _rtB -> ergriw4ip1 ; ssWriteToDataStoreWithPath ( S , _rtDW ->
mk12nlvn5c ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write24"
, NULL ) ; _rtB -> cr32stjnzh = _rtP -> P_693 * kaqx4nados ; _rtDW ->
dpjpy2bpgy = _rtB -> cr32stjnzh ; ssWriteToDataStoreWithPath ( S , _rtDW ->
b4t23vdsin ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write25"
, NULL ) ; _rtB -> lrw1kivvfm = _rtP -> P_694 * _rtB -> aeal0w25ez ; _rtDW ->
pelseog20p = _rtB -> lrw1kivvfm ; ssWriteToDataStoreWithPath ( S , _rtDW ->
itfhai41fd ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write3"
, NULL ) ; _rtB -> j3fu5pyahe = _rtP -> P_695 * batdnpsvim ; _rtDW ->
nhrhyjvls4 = _rtB -> j3fu5pyahe ; ssWriteToDataStoreWithPath ( S , _rtDW ->
gxmwc1ws3i ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write4"
, NULL ) ; _rtB -> aqsjhmbxo2 = _rtP -> P_696 * _rtB -> pnx1tnohqx ; _rtDW ->
oobzxswkpo = _rtB -> aqsjhmbxo2 ; ssWriteToDataStoreWithPath ( S , _rtDW ->
od43cn3nwy ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write5"
, NULL ) ; _rtB -> iytqwgu15l = _rtP -> P_697 * _rtB -> pmiqvnd0gh ; _rtDW ->
l0b5hroyaj = _rtB -> iytqwgu15l ; ssWriteToDataStoreWithPath ( S , _rtDW ->
o4mdxa4wbe ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write6"
, NULL ) ; _rtB -> hroyaf510l = _rtP -> P_698 * _rtB -> ddovbhztt5 ; _rtDW ->
ktweu3wugd = _rtB -> hroyaf510l ; ssWriteToDataStoreWithPath ( S , _rtDW ->
aqq0xphes4 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write7"
, NULL ) ; _rtB -> bowle0ow30 = _rtP -> P_699 * g1ekzbu3oi ; _rtDW ->
nlpxiel2sg = _rtB -> bowle0ow30 ; ssWriteToDataStoreWithPath ( S , _rtDW ->
jkypds115r ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write8"
, NULL ) ; _rtB -> amm24eiw3p = _rtP -> P_700 * fwhtla1rft ; _rtDW ->
n5tosor5b5 = _rtB -> amm24eiw3p ; ssWriteToDataStoreWithPath ( S , _rtDW ->
ewajqde1w2 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write9"
, NULL ) ; _rtB -> htii4ssxez = _rtP -> P_701 * o3mfdsmmfb ; _rtDW ->
nq1n5qxeyp = _rtB -> htii4ssxez ; ssWriteToDataStoreWithPath ( S , _rtDW ->
bxddnpyqx2 ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/ntestimator/Data Store Write25"
, NULL ) ; ssReadFromDataStoreWithPath ( S , _rtDW -> hmzrrmgtbp ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read19"
, NULL ) ; jfmtdksnh0 = _rtDW -> b5t1avpqna ; _rtB -> brshx4vf1z = _rtP ->
P_702 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_703 ; meppapiqj0 = ( _rtB ->
brshx4vf1z > jfmtdksnh0 ) ; finyivsrdi = _rtDW -> iggiejtmqu ; rtPrevAction =
_rtDW -> loepcnnuit ; if ( _rtDW -> iggiejtmqu < 25.0F ) { rtAction = 0 ; }
else if ( _rtDW -> iggiejtmqu < 30.0F ) { rtAction = 1 ; } else if ( _rtDW ->
iggiejtmqu < 35.0F ) { rtAction = 2 ; } else if ( _rtDW -> iggiejtmqu < 40.0F
) { rtAction = 3 ; } else if ( _rtDW -> iggiejtmqu < 45.0F ) { rtAction = 4 ;
} else if ( _rtDW -> iggiejtmqu < 50.0F ) { rtAction = 5 ; } else if ( _rtDW
-> iggiejtmqu < 55.0F ) { rtAction = 6 ; } else if ( _rtDW -> iggiejtmqu <
60.0F ) { rtAction = 7 ; } else if ( _rtDW -> iggiejtmqu < 65.0F ) { rtAction
= 8 ; } else if ( _rtDW -> iggiejtmqu < 70.0F ) { rtAction = 9 ; } else if (
_rtDW -> iggiejtmqu < 75.0F ) { rtAction = 10 ; } else if ( _rtDW ->
iggiejtmqu < 80.0F ) { rtAction = 11 ; } else if ( _rtDW -> iggiejtmqu <
85.0F ) { rtAction = 12 ; } else if ( _rtDW -> iggiejtmqu < 90.0F ) {
rtAction = 13 ; } else if ( _rtDW -> iggiejtmqu < 95.0F ) { rtAction = 14 ; }
else if ( _rtDW -> iggiejtmqu < 100.0F ) { rtAction = 15 ; } else if ( _rtDW
-> iggiejtmqu < 105.0F ) { rtAction = 16 ; } else if ( _rtDW -> iggiejtmqu <
110.0F ) { rtAction = 17 ; } else if ( _rtDW -> iggiejtmqu < 115.0F ) {
rtAction = 18 ; } else if ( _rtDW -> iggiejtmqu < 120.0F ) { rtAction = 19 ;
} else if ( _rtDW -> iggiejtmqu < 125.0F ) { rtAction = 20 ; } else if (
_rtDW -> iggiejtmqu < 130.0F ) { rtAction = 21 ; } else if ( _rtDW ->
iggiejtmqu < 135.0F ) { rtAction = 22 ; } else if ( _rtDW -> iggiejtmqu <
140.0F ) { rtAction = 23 ; } else if ( _rtDW -> iggiejtmqu < 145.0F ) {
rtAction = 24 ; } else if ( _rtDW -> iggiejtmqu < 150.0F ) { rtAction = 25 ;
} else if ( _rtDW -> iggiejtmqu < 155.0F ) { rtAction = 26 ; } else if (
_rtDW -> iggiejtmqu < 160.0F ) { rtAction = 27 ; } else if ( _rtDW ->
iggiejtmqu < 165.0F ) { rtAction = 28 ; } else if ( _rtDW -> iggiejtmqu <
170.0F ) { rtAction = 29 ; } else if ( _rtDW -> iggiejtmqu < 175.0F ) {
rtAction = 30 ; } else if ( _rtDW -> iggiejtmqu < 180.0F ) { rtAction = 31 ;
} else if ( _rtDW -> iggiejtmqu < 185.0F ) { rtAction = 32 ; } else if (
_rtDW -> iggiejtmqu < 190.0F ) { rtAction = 33 ; } else { rtAction = 34 ; }
_rtDW -> loepcnnuit = rtAction ; if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
ssSetSolverNeedsReset ( S ) ; break ; case 2 : ssSetSolverNeedsReset ( S ) ;
break ; case 3 : ssSetSolverNeedsReset ( S ) ; break ; case 4 :
ssSetSolverNeedsReset ( S ) ; break ; case 5 : ssSetSolverNeedsReset ( S ) ;
break ; case 6 : ssSetSolverNeedsReset ( S ) ; break ; case 7 :
ssSetSolverNeedsReset ( S ) ; break ; case 8 : ssSetSolverNeedsReset ( S ) ;
break ; case 9 : ssSetSolverNeedsReset ( S ) ; break ; case 10 :
ssSetSolverNeedsReset ( S ) ; break ; case 11 : ssSetSolverNeedsReset ( S ) ;
break ; case 12 : ssSetSolverNeedsReset ( S ) ; break ; case 13 :
ssSetSolverNeedsReset ( S ) ; break ; case 14 : ssSetSolverNeedsReset ( S ) ;
break ; case 15 : ssSetSolverNeedsReset ( S ) ; break ; case 16 :
ssSetSolverNeedsReset ( S ) ; break ; case 17 : ssSetSolverNeedsReset ( S ) ;
break ; case 18 : ssSetSolverNeedsReset ( S ) ; break ; case 19 :
ssSetSolverNeedsReset ( S ) ; break ; case 20 : ssSetSolverNeedsReset ( S ) ;
break ; case 21 : ssSetSolverNeedsReset ( S ) ; break ; case 22 :
ssSetSolverNeedsReset ( S ) ; break ; case 23 : ssSetSolverNeedsReset ( S ) ;
break ; case 24 : ssSetSolverNeedsReset ( S ) ; break ; case 25 :
ssSetSolverNeedsReset ( S ) ; break ; case 26 : ssSetSolverNeedsReset ( S ) ;
break ; case 27 : ssSetSolverNeedsReset ( S ) ; break ; case 28 :
ssSetSolverNeedsReset ( S ) ; break ; case 29 : ssSetSolverNeedsReset ( S ) ;
break ; case 30 : ssSetSolverNeedsReset ( S ) ; break ; case 31 :
ssSetSolverNeedsReset ( S ) ; break ; case 32 : ssSetSolverNeedsReset ( S ) ;
break ; case 33 : ssSetSolverNeedsReset ( S ) ; break ; case 34 :
ssSetSolverNeedsReset ( S ) ; break ; } } switch ( rtAction ) { case 0 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP ->
P_304 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_304 [ 1 ] ; _rtB ->
n5bgkgnoo4 [ 2 ] = _rtP -> P_304 [ 2 ] ; srUpdateBC ( _rtDW -> o0fqt141qd ) ;
break ; case 1 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2
) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB ->
n5bgkgnoo4 [ 0 ] = _rtP -> P_306 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP ->
P_306 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_306 [ 2 ] ; srUpdateBC (
_rtDW -> h3vqcmc1hz ) ; break ; case 2 : if ( rtAction != rtPrevAction ) { if
( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S
) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_308 [ 0 ] ; _rtB -> n5bgkgnoo4 [
1 ] = _rtP -> P_308 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_308 [ 2 ] ;
srUpdateBC ( _rtDW -> pqpqjda5is ) ; break ; case 3 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_310 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_310 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_310 [ 2 ] ; srUpdateBC ( _rtDW -> bwmwpnvwlf ) ; break ; case 4
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_312 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_312 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_312 [ 2 ] ; srUpdateBC ( _rtDW ->
hf2ukkb54z ) ; break ; case 5 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_314 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_314 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_314 [ 2 ] ;
srUpdateBC ( _rtDW -> dp2wxggv2y ) ; break ; case 6 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_316 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_316 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_316 [ 2 ] ; srUpdateBC ( _rtDW -> ifikoeohu4 ) ; break ; case 7
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_318 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_318 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_318 [ 2 ] ; srUpdateBC ( _rtDW ->
fb2jmsx45b ) ; break ; case 8 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_320 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_320 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_320 [ 2 ] ;
srUpdateBC ( _rtDW -> gu2pk5utpz ) ; break ; case 9 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_322 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_322 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_322 [ 2 ] ; srUpdateBC ( _rtDW -> m1sbzn2h1n ) ; break ; case
10 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_324 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_324 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_324 [ 2 ] ; srUpdateBC ( _rtDW ->
ewylvoz5wx ) ; break ; case 11 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_326 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_326 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_326 [ 2 ] ;
srUpdateBC ( _rtDW -> bzt2b4vlgj ) ; break ; case 12 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_328 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_328 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_328 [ 2 ] ; srUpdateBC ( _rtDW -> p5cjuriyjr ) ; break ; case
13 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_330 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_330 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_330 [ 2 ] ; srUpdateBC ( _rtDW ->
klgivly02z ) ; break ; case 14 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_332 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_332 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_332 [ 2 ] ;
srUpdateBC ( _rtDW -> nlyldhhvyb ) ; break ; case 15 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_334 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_334 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_334 [ 2 ] ; srUpdateBC ( _rtDW -> k1yann3ya5 ) ; break ; case
16 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_336 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_336 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_336 [ 2 ] ; srUpdateBC ( _rtDW ->
bubafrutom ) ; break ; case 17 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_338 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_338 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_338 [ 2 ] ;
srUpdateBC ( _rtDW -> ltvu2oc3sf ) ; break ; case 18 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_340 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_340 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_340 [ 2 ] ; srUpdateBC ( _rtDW -> li2ivnnt0t ) ; break ; case
19 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_342 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_342 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_342 [ 2 ] ; srUpdateBC ( _rtDW ->
ae1e1itbfy ) ; break ; case 20 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_344 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_344 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_344 [ 2 ] ;
srUpdateBC ( _rtDW -> dhx34gepf4 ) ; break ; case 21 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_346 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_346 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_346 [ 2 ] ; srUpdateBC ( _rtDW -> p2atyilds3 ) ; break ; case
22 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_348 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_348 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_348 [ 2 ] ; srUpdateBC ( _rtDW ->
edw2mgcvx1 ) ; break ; case 23 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_350 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_350 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_350 [ 2 ] ;
srUpdateBC ( _rtDW -> n4uikvdjac ) ; break ; case 24 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_352 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_352 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_352 [ 2 ] ; srUpdateBC ( _rtDW -> chxryck3fg ) ; break ; case
25 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_354 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_354 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_354 [ 2 ] ; srUpdateBC ( _rtDW ->
dl0glhtqdr ) ; break ; case 26 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_356 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_356 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_356 [ 2 ] ;
srUpdateBC ( _rtDW -> adcpzgniuv ) ; break ; case 27 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_358 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_358 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_358 [ 2 ] ; srUpdateBC ( _rtDW -> ismm4u0kis ) ; break ; case
28 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_360 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_360 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_360 [ 2 ] ; srUpdateBC ( _rtDW ->
kct4avkdgo ) ; break ; case 29 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_362 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_362 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_362 [ 2 ] ;
srUpdateBC ( _rtDW -> ljqu2i52fc ) ; break ; case 30 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_364 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_364 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_364 [ 2 ] ; srUpdateBC ( _rtDW -> lpg4z3lelv ) ; break ; case
31 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_366 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_366 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_366 [ 2 ] ; srUpdateBC ( _rtDW ->
ombi11gse3 ) ; break ; case 32 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_368 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_368 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_368 [ 2 ] ;
srUpdateBC ( _rtDW -> igzqf1qklf ) ; break ; case 33 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_370 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_370 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_370 [ 2 ] ; srUpdateBC ( _rtDW -> moze4hcv5c ) ; break ; case
34 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_372 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_372 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_372 [ 2 ] ; srUpdateBC ( _rtDW ->
kuzwdhnrip ) ; break ; } rtPrevAction = _rtDW -> a1axcz0kbn ; if ( finyivsrdi
< 25.0F ) { rtAction = 0 ; } else if ( finyivsrdi < 30.0F ) { rtAction = 1 ;
} else if ( finyivsrdi < 35.0F ) { rtAction = 2 ; } else if ( finyivsrdi <
40.0F ) { rtAction = 3 ; } else if ( finyivsrdi < 45.0F ) { rtAction = 4 ; }
else if ( finyivsrdi < 50.0F ) { rtAction = 5 ; } else if ( finyivsrdi <
55.0F ) { rtAction = 6 ; } else if ( finyivsrdi < 60.0F ) { rtAction = 7 ; }
else if ( finyivsrdi < 65.0F ) { rtAction = 8 ; } else if ( finyivsrdi <
70.0F ) { rtAction = 9 ; } else if ( finyivsrdi < 75.0F ) { rtAction = 10 ; }
else if ( finyivsrdi < 80.0F ) { rtAction = 11 ; } else if ( finyivsrdi <
85.0F ) { rtAction = 12 ; } else if ( finyivsrdi < 90.0F ) { rtAction = 13 ;
} else if ( finyivsrdi < 95.0F ) { rtAction = 14 ; } else if ( finyivsrdi <
100.0F ) { rtAction = 15 ; } else if ( finyivsrdi < 105.0F ) { rtAction = 16
; } else if ( finyivsrdi < 110.0F ) { rtAction = 17 ; } else if ( finyivsrdi
< 115.0F ) { rtAction = 18 ; } else if ( finyivsrdi < 120.0F ) { rtAction =
19 ; } else if ( finyivsrdi < 125.0F ) { rtAction = 20 ; } else if (
finyivsrdi < 130.0F ) { rtAction = 21 ; } else if ( finyivsrdi < 135.0F ) {
rtAction = 22 ; } else if ( finyivsrdi < 140.0F ) { rtAction = 23 ; } else if
( finyivsrdi < 145.0F ) { rtAction = 24 ; } else if ( finyivsrdi < 150.0F ) {
rtAction = 25 ; } else if ( finyivsrdi < 155.0F ) { rtAction = 26 ; } else if
( finyivsrdi < 160.0F ) { rtAction = 27 ; } else if ( finyivsrdi < 165.0F ) {
rtAction = 28 ; } else if ( finyivsrdi < 170.0F ) { rtAction = 29 ; } else if
( finyivsrdi < 175.0F ) { rtAction = 30 ; } else if ( finyivsrdi < 180.0F ) {
rtAction = 31 ; } else { rtAction = 32 ; } _rtDW -> a1axcz0kbn = rtAction ;
if ( rtPrevAction != rtAction ) { switch ( rtPrevAction ) { case 0 :
ssSetSolverNeedsReset ( S ) ; break ; case 1 : ssSetSolverNeedsReset ( S ) ;
break ; case 2 : ssSetSolverNeedsReset ( S ) ; break ; case 3 :
ssSetSolverNeedsReset ( S ) ; break ; case 4 : ssSetSolverNeedsReset ( S ) ;
break ; case 5 : ssSetSolverNeedsReset ( S ) ; break ; case 6 :
ssSetSolverNeedsReset ( S ) ; break ; case 7 : ssSetSolverNeedsReset ( S ) ;
break ; case 8 : ssSetSolverNeedsReset ( S ) ; break ; case 9 :
ssSetSolverNeedsReset ( S ) ; break ; case 10 : ssSetSolverNeedsReset ( S ) ;
break ; case 11 : ssSetSolverNeedsReset ( S ) ; break ; case 12 :
ssSetSolverNeedsReset ( S ) ; break ; case 13 : ssSetSolverNeedsReset ( S ) ;
break ; case 14 : ssSetSolverNeedsReset ( S ) ; break ; case 15 :
ssSetSolverNeedsReset ( S ) ; break ; case 16 : ssSetSolverNeedsReset ( S ) ;
break ; case 17 : ssSetSolverNeedsReset ( S ) ; break ; case 18 :
ssSetSolverNeedsReset ( S ) ; break ; case 19 : ssSetSolverNeedsReset ( S ) ;
break ; case 20 : ssSetSolverNeedsReset ( S ) ; break ; case 21 :
ssSetSolverNeedsReset ( S ) ; break ; case 22 : ssSetSolverNeedsReset ( S ) ;
break ; case 23 : ssSetSolverNeedsReset ( S ) ; break ; case 24 :
ssSetSolverNeedsReset ( S ) ; break ; case 25 : ssSetSolverNeedsReset ( S ) ;
break ; case 26 : ssSetSolverNeedsReset ( S ) ; break ; case 27 :
ssSetSolverNeedsReset ( S ) ; break ; case 28 : ssSetSolverNeedsReset ( S ) ;
break ; case 29 : ssSetSolverNeedsReset ( S ) ; break ; case 30 :
ssSetSolverNeedsReset ( S ) ; break ; case 31 : ssSetSolverNeedsReset ( S ) ;
break ; case 32 : ssSetSolverNeedsReset ( S ) ; break ; } } switch ( rtAction
) { case 0 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 )
!= ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m
[ 0 ] = _rtP -> P_374 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_374 [ 1 ]
; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_374 [ 2 ] ; srUpdateBC ( _rtDW ->
j4ymuqubrw ) ; break ; case 1 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_376 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_376 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_376 [ 2 ] ;
srUpdateBC ( _rtDW -> kymzzotg2g ) ; break ; case 2 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_378 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_378 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_378 [ 2 ] ; srUpdateBC ( _rtDW -> maiimsnqs5 ) ; break ; case 3
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_380 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_380 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_380 [ 2 ] ; srUpdateBC ( _rtDW ->
dyx4tug5h3 ) ; break ; case 4 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_382 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_382 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_382 [ 2 ] ;
srUpdateBC ( _rtDW -> cr2kibgo2j ) ; break ; case 5 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_384 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_384 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_384 [ 2 ] ; srUpdateBC ( _rtDW -> pwlmqo3nxm ) ; break ; case 6
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_386 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_386 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_386 [ 2 ] ; srUpdateBC ( _rtDW ->
guuziano0t ) ; break ; case 7 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_388 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_388 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_388 [ 2 ] ;
srUpdateBC ( _rtDW -> l12omsu2tn ) ; break ; case 8 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_390 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_390 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_390 [ 2 ] ; srUpdateBC ( _rtDW -> o2zj3fqza1 ) ; break ; case 9
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_392 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_392 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_392 [ 2 ] ; srUpdateBC ( _rtDW ->
m3gfat1ui0 ) ; break ; case 10 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_394 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_394 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_394 [ 2 ] ;
srUpdateBC ( _rtDW -> dk3vj22y05 ) ; break ; case 11 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_396 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_396 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_396 [ 2 ] ; srUpdateBC ( _rtDW -> o3c1lu15ny ) ; break ; case
12 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_398 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_398 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_398 [ 2 ] ; srUpdateBC ( _rtDW ->
j45e0raewi ) ; break ; case 13 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_400 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_400 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_400 [ 2 ] ;
srUpdateBC ( _rtDW -> o3wc5wwa4p ) ; break ; case 14 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_402 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_402 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_402 [ 2 ] ; srUpdateBC ( _rtDW -> irsxloeepq ) ; break ; case
15 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_404 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_404 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_404 [ 2 ] ; srUpdateBC ( _rtDW ->
cp3q1at4o2 ) ; break ; case 16 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_406 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_406 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_406 [ 2 ] ;
srUpdateBC ( _rtDW -> pce44vep3x ) ; break ; case 17 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_408 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_408 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_408 [ 2 ] ; srUpdateBC ( _rtDW -> mee1wioe1r ) ; break ; case
18 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_410 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_410 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_410 [ 2 ] ; srUpdateBC ( _rtDW ->
a5nvnya1oe ) ; break ; case 19 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_412 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_412 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_412 [ 2 ] ;
srUpdateBC ( _rtDW -> dfax004odl ) ; break ; case 20 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_414 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_414 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_414 [ 2 ] ; srUpdateBC ( _rtDW -> mwuspmm2e1 ) ; break ; case
21 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_416 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_416 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_416 [ 2 ] ; srUpdateBC ( _rtDW ->
jgu1xgjxem ) ; break ; case 22 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_418 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_418 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_418 [ 2 ] ;
srUpdateBC ( _rtDW -> my15ghhvb1 ) ; break ; case 23 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_420 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_420 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_420 [ 2 ] ; srUpdateBC ( _rtDW -> bcd3kgenub ) ; break ; case
24 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_422 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_422 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_422 [ 2 ] ; srUpdateBC ( _rtDW ->
f5k2rzim4a ) ; break ; case 25 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_424 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_424 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_424 [ 2 ] ;
srUpdateBC ( _rtDW -> nx3flbvahx ) ; break ; case 26 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_426 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_426 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_426 [ 2 ] ; srUpdateBC ( _rtDW -> lik1wotc2i ) ; break ; case
27 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_428 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_428 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_428 [ 2 ] ; srUpdateBC ( _rtDW ->
gg02mzoxhc ) ; break ; case 28 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_430 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_430 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_430 [ 2 ] ;
srUpdateBC ( _rtDW -> gwxpzomgjh ) ; break ; case 29 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_432 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_432 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_432 [ 2 ] ; srUpdateBC ( _rtDW -> etxqofccji ) ; break ; case
30 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_434 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_434 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_434 [ 2 ] ; srUpdateBC ( _rtDW ->
ljwb0xnabb ) ; break ; case 31 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_436 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_436 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_436 [ 2 ] ;
srUpdateBC ( _rtDW -> ivkldwkotp ) ; break ; case 32 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_438 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_438 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_438 [ 2 ] ; srUpdateBC ( _rtDW -> hypqqzrtox ) ; break ; } if (
meppapiqj0 ) { dpajlxfdyx_idx_0 = _rtB -> l1dam3wq3m [ 0 ] ; jsgk2hka41_idx_0
= _rtB -> l1dam3wq3m [ 1 ] ; jsgk2hka41_idx_1 = _rtB -> l1dam3wq3m [ 2 ] ; }
else { dpajlxfdyx_idx_0 = _rtB -> n5bgkgnoo4 [ 0 ] ; jsgk2hka41_idx_0 = _rtB
-> n5bgkgnoo4 [ 1 ] ; jsgk2hka41_idx_1 = _rtB -> n5bgkgnoo4 [ 2 ] ; } _rtB ->
ehykaejtnw = _rtP -> P_707 * dpajlxfdyx_idx_0 ; _rtDW -> o3z1jsmhkx = _rtB ->
ehykaejtnw ; ssWriteToDataStoreWithPath ( S , _rtDW -> fnxjjp2lme ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write26"
, NULL ) ; _rtB -> oaon3y4tfi = _rtP -> P_708 * jsgk2hka41_idx_0 ; _rtDW ->
hptuorf3i3 = _rtB -> oaon3y4tfi ; ssWriteToDataStoreWithPath ( S , _rtDW ->
angozbvvee ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write27"
, NULL ) ; _rtB -> dhzov4va5p = _rtP -> P_709 * jsgk2hka41_idx_1 ; _rtDW ->
mi05525rde = _rtB -> dhzov4va5p ; ssWriteToDataStoreWithPath ( S , _rtDW ->
mzsuxn1hbm ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write28"
, NULL ) ; kaqx4nados *= _rtP -> P_710 ; ic3wqfpram_idx_0 = _rtP -> P_711 *
pyabwb0ags ; ic3wqfpram_idx_1 = _rtP -> P_711 * kaqx4nados ; if ( _rtB ->
ezlhtulb34 <= _rtP -> P_712 ) { _rtB -> nd3bibt0gk = _rtP -> P_713 ; } else {
_rtB -> nd3bibt0gk = e0r0t533ao ; } cbpfnq4pxd = _rtDW -> mvpjwhrzk3 ;
alqkjudhu3 = _rtDW -> mtqhixagy1 ; ssReadFromDataStoreWithPath ( S , _rtDW ->
iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter2/Data Store Read1"
, NULL ) ; kaqx4nados = _rtDW -> owcamicoch ; ssReadFromDataStoreWithPath ( S
, _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter2/Data Store Read8"
, NULL ) ; jfmtdksnh0 = _rtDW -> owcamicoch ; _rtB -> ompws1iq14 = _rtP ->
P_718 * kaqx4nados ; _rtB -> m0nyfnn554 = _rtP -> P_721 * jfmtdksnh0 ; if (
_rtB -> m0nyfnn554 > _rtP -> P_722 ) { dpajlxfdyx_idx_0 = _rtP -> P_722 ; }
else if ( _rtB -> m0nyfnn554 < _rtP -> P_723 ) { dpajlxfdyx_idx_0 = _rtP ->
P_723 ; } else { dpajlxfdyx_idx_0 = _rtB -> m0nyfnn554 ; } if ( _rtB ->
ompws1iq14 > _rtP -> P_719 ) { jsgk2hka41_idx_0 = _rtP -> P_719 ; } else if (
_rtB -> ompws1iq14 < _rtP -> P_720 ) { jsgk2hka41_idx_0 = _rtP -> P_720 ; }
else { jsgk2hka41_idx_0 = _rtB -> ompws1iq14 ; } _rtB -> egwnphshj3 = ( _rtP
-> P_717 - jsgk2hka41_idx_0 ) * cbpfnq4pxd + _rtDW -> fhgbtmls3d *
dpajlxfdyx_idx_0 ; ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter3/Data Store Read1"
, NULL ) ; kaqx4nados = _rtDW -> owcamicoch ; ssReadFromDataStoreWithPath ( S
, _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter3/Data Store Read8"
, NULL ) ; jfmtdksnh0 = _rtDW -> owcamicoch ; _rtB -> iux1flh0ub = _rtP ->
P_726 * kaqx4nados ; _rtB -> asgv30i1hr = _rtP -> P_729 * jfmtdksnh0 ; if (
_rtB -> asgv30i1hr > _rtP -> P_730 ) { dpajlxfdyx_idx_0 = _rtP -> P_730 ; }
else if ( _rtB -> asgv30i1hr < _rtP -> P_731 ) { dpajlxfdyx_idx_0 = _rtP ->
P_731 ; } else { dpajlxfdyx_idx_0 = _rtB -> asgv30i1hr ; } if ( _rtB ->
iux1flh0ub > _rtP -> P_727 ) { jsgk2hka41_idx_0 = _rtP -> P_727 ; } else if (
_rtB -> iux1flh0ub < _rtP -> P_728 ) { jsgk2hka41_idx_0 = _rtP -> P_728 ; }
else { jsgk2hka41_idx_0 = _rtB -> iux1flh0ub ; } _rtB -> mskakvqxnl = ( _rtP
-> P_725 - jsgk2hka41_idx_0 ) * alqkjudhu3 + _rtDW -> l1sigmyvxe *
dpajlxfdyx_idx_0 ;
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
br0btxcgmo ) , _rtP -> P_734 , _rtB -> fh1ao455t3 , _rtP -> P_732 , 5U , _rtB
-> aeal0w25ez , _rtP -> P_733 , 6U ) ;
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
bsmjlt2qqy ) , _rtP -> P_737 , _rtB -> fh1ao455t3 , _rtP -> P_735 , 5U , _rtB
-> aeal0w25ez , _rtP -> P_736 , 6U ) ; jfmtdksnh0 = _rtDW -> ljbykua013 ; for
( i_p = 0 ; i_p < 2 ; i_p ++ ) { btosikvjyf [ i_p ] = _rtP -> P_738 [ i_p + 4
] * exrgmvycyf_idx_2 + ( _rtP -> P_738 [ i_p + 2 ] * exrgmvycyf_idx_1 + _rtP
-> P_738 [ i_p ] * exrgmvycyf_idx_0 ) ; } dpajlxfdyx_idx_0 = _rtDW ->
noqny2ee14 - btosikvjyf [ 0 ] ; jsgk2hka41_idx_0 = jfmtdksnh0 - btosikvjyf [
1 ] ; for ( i_p = 0 ; i_p < 3 ; i_p ++ ) { tmp_n [ i_p ] = _rtP -> P_741 [
i_p + 3 ] * jsgk2hka41_idx_0 + _rtP -> P_741 [ i_p ] * dpajlxfdyx_idx_0 ; }
for ( i_p = 0 ; i_p < 3 ; i_p ++ ) { tmp_l [ i_p ] = _rtP -> P_742 [ i_p + 6
] * exrgmvycyf_idx_2 + ( _rtP -> P_742 [ i_p + 3 ] * exrgmvycyf_idx_1 + _rtP
-> P_742 [ i_p ] * exrgmvycyf_idx_0 ) ; } for ( i_p = 0 ; i_p < 3 ; i_p ++ )
{ _rtB -> ck5rlv2b0s [ i_p ] = ( _rtP -> P_743 [ i_p + 3 ] * _rtB ->
j5nsr3o4kc [ 1 ] + _rtP -> P_743 [ i_p ] * _rtB -> j5nsr3o4kc [ 0 ] ) + (
tmp_n [ i_p ] + tmp_l [ i_p ] ) ; } ssReadFromDataStoreWithPath ( S , _rtDW
-> kwfltn54ul ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read20"
, NULL ) ; _rtB -> k5ufaneaqv = _rtP -> P_744 * _rtDW -> ocojyks2sz ;
jfmtdksnh0 = _rtP -> P_746 ; if ( ! ( _rtB -> k5ufaneaqv > _rtP -> P_745 ) )
{ finyivsrdi = _rtP -> P_745 ; } _rtB -> fgtlymqtj5 = finyivsrdi + jfmtdksnh0
; _rtB -> pyvgtp5e3m = g1ekzbu3oi ; } _rtB -> aew0s1omc3 = _rtB -> bchvsczbjy
- _rtB -> pyvgtp5e3m ; ssCallAccelRunBlock ( S , 118 , 97 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB ->
ak0aa5iiev = _rtB -> hrv5myfmi5 ; ssCallAccelRunBlock ( S , 118 , 99 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> ij1u0goevc = _rtB -> bihzjyslyy [ 0 ] ;
ssCallAccelRunBlock ( S , 118 , 101 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
i32jf4ccii = _rtB -> cnnxmyxf0o [ 0 ] ; ssCallAccelRunBlock ( S , 118 , 103 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 118 , 104 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 105 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> b4uvpbx4k2 = _rtB -> bchvsczbjy - _rtB ->
pyvgtp5e3m ; ssCallAccelRunBlock ( S , 118 , 107 , SS_CALL_MDL_OUTPUTS ) ; if
( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> f32jhx0p4h = fwhtla1rft ; } _rtB ->
ffs2aavr5w = _rtB -> bzbb3dscs0 - _rtB -> f32jhx0p4h ; ssCallAccelRunBlock (
S , 118 , 110 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) {
_rtB -> kzxvn051z0 [ 0 ] = exrgmvycyf_idx_0 ; _rtB -> kzxvn051z0 [ 1 ] =
hn15keiut1 ; _rtB -> kzxvn051z0 [ 2 ] = byk21oesq1 ; _rtB -> kzxvn051z0 [ 3 ]
= jjkfbyaomr ; _rtB -> kzxvn051z0 [ 4 ] = o3cuzyoqg5 ; _rtB -> kzxvn051z0 [ 5
] = km03xn13id ; _rtB -> kzxvn051z0 [ 6 ] = plknkmyedj ; _rtB -> kzxvn051z0 [
7 ] = jmuta2homi ; _rtB -> kzxvn051z0 [ 8 ] = ehyje10v1p ; _rtB -> kzxvn051z0
[ 9 ] = a1jrsglzzi ; _rtB -> kzxvn051z0 [ 10 ] = fzccphw1bz ; _rtB ->
kzxvn051z0 [ 11 ] = _rtB -> cqertkbhh1 ; _rtB -> kzxvn051z0 [ 12 ] =
pyabwb0ags ; ssCallAccelRunBlock ( S , 118 , 112 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 118 , 113 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 118 , 114 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
moeq5yoq3z = _rtP -> P_99 * _rtB -> p0ej2ncygl ; ssCallAccelRunBlock ( S ,
118 , 116 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB
-> grbdvor2ec = not4fp11wk ; } ssCallAccelRunBlock ( S , 118 , 118 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 119 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 120 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 121 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) {
ssCallAccelRunBlock ( S , 118 , 122 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 118 , 123 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 118 , 124 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 2 , 0 ) ) { ssCallAccelRunBlock ( S , 118 , 125 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 126 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 127 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 128 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 129 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> kxudcvxngs [ 0 ] = _rtB -> dobwfafcm0 ; _rtB
-> kxudcvxngs [ 1 ] = fwhtla1rft ; _rtB -> kxudcvxngs [ 2 ] = _rtB ->
g50cgr2ero ; ssCallAccelRunBlock ( S , 118 , 131 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> dt1ycveg1s [ 0 ] = fij5klqz0n ; _rtB -> dt1ycveg1s [ 1 ] = c2fdcpgrsp
; _rtB -> dt1ycveg1s [ 2 ] = fvhzusu422 ; } ssCallAccelRunBlock ( S , 118 ,
133 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 134 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> moeq5yoq3z = _rtB -> eebr3qqx0u [ 0 ] * _rtB
-> eebr3qqx0u [ 1 ] * _rtP -> P_100 * _rtP -> P_101 ; ssCallAccelRunBlock ( S
, 118 , 138 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) {
_rtB -> mzknsrl11p [ 0 ] = pwkaxiafxx ; _rtB -> mzknsrl11p [ 1 ] =
gwzyst3ou3_p ; ssCallAccelRunBlock ( S , 118 , 140 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> kxudcvxngs [ 0 ] = _rtB -> ldjrvtlkq4 ; _rtB -> kxudcvxngs [ 1 ] =
g1ekzbu3oi ; _rtB -> kxudcvxngs [ 2 ] = _rtB -> p4ek3tnerm ;
ssCallAccelRunBlock ( S , 118 , 142 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
mzknsrl11p [ 0 ] = ic3wqfpram_idx_0 ; _rtB -> mzknsrl11p [ 1 ] =
ic3wqfpram_idx_1 ; ssCallAccelRunBlock ( S , 118 , 144 , SS_CALL_MDL_OUTPUTS
) ; _rtB -> mzknsrl11p [ 0 ] = _rtB -> cqertkbhh1 ; _rtB -> mzknsrl11p [ 1 ]
= batdnpsvim ; ssCallAccelRunBlock ( S , 118 , 146 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 118 , 147 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
ij1u0goevc = _rtB -> j5nsr3o4kc [ 2 ] ; ssCallAccelRunBlock ( S , 118 , 149 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
c1otyss11p [ 0 ] = _rtP -> P_102 [ 0 ] ; _rtB -> c1otyss11p [ 1 ] = _rtP ->
P_102 [ 1 ] ; _rtB -> c1otyss11p [ 2 ] = _rtP -> P_102 [ 2 ] ; _rtB ->
c1otyss11p [ 3 ] = _rtP -> P_102 [ 3 ] ; } _rtB -> ietg2yqpzt = _rtP -> P_103
* b11wdxnlxt ; _rtB -> iygz0aaixm = _rtP -> P_104 * _rtB -> moeq5yoq3z ; _rtB
-> ew4idsfm1c = _rtX -> cgw3asjtrv ; ssCallAccelRunBlock ( S , 0 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; aktecqyana = ( _rtB -> ew4idsfm1c * _rtB ->
indhq4wak4 + 15.6 * _rtB -> iygz0aaixm ) / ( _rtB -> iygz0aaixm + _rtB ->
indhq4wak4 ) ; if ( aktecqyana > _rtP -> P_106 ) { aktecqyana = _rtP -> P_106
; } else { if ( aktecqyana < _rtP -> P_107 ) { aktecqyana = _rtP -> P_107 ; }
} kyy20toyut = _rtB -> iygz0aaixm + _rtB -> indhq4wak4 ; if ( ssIsSampleHit (
S , 2 , 0 ) ) { loi4w1jrb4 = orelggziy4 ; f1qa0udy3j = _rtB -> cytczbxazy ;
_rtB -> crzvznbqgp = _rtB -> cthsuitfz5 ; } n4kbehhhau = _rtP -> P_108 * _rtB
-> bchvsczbjy ; o5ibp43cp4 = _rtP -> P_109 * npiyznthqi ; ssCallAccelRunBlock
( S , 118 , 163 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) )
{ _rtB -> bo2yfu1lui [ 0 ] = _rtP -> P_110 [ 0 ] ; _rtB -> bo2yfu1lui [ 1 ] =
_rtP -> P_110 [ 1 ] ; _rtB -> bo2yfu1lui [ 2 ] = _rtP -> P_110 [ 2 ] ; }
ssCallAccelRunBlock ( S , 16 , 0 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtB -> bvgnvsn3md = _rtP -> P_111 ; } if ( ssIsSampleHit (
S , 2 , 0 ) ) { _rtB -> bldsdpdbbk = _rtP -> P_112 * _rtB -> grbdvor2ec ; }
npiyznthqi = _rtP -> P_113 * b11wdxnlxt ; if ( ssIsSampleHit ( S , 1 , 0 ) )
{ _rtB -> ej0wr5psda = _rtP -> P_115 ; memcpy ( & _rtB -> gkkw35inus [ 0 ] ,
& _rtP -> P_116 [ 0 ] , 9U * sizeof ( real_T ) ) ; memcpy ( & _rtB ->
d0ggufwnyf [ 0 ] , & _rtP -> P_117 [ 0 ] , 18U * sizeof ( real_T ) ) ; _rtB
-> f2jub0exjc = _rtP -> P_118 ; } _rtB -> ja2tmyhnj3 [ 0 ] = _rtB ->
bldsdpdbbk ; _rtB -> ja2tmyhnj3 [ 1 ] = _rtP -> P_114 * npiyznthqi ;
ssCallAccelRunBlock ( S , 8 , 1 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtB -> bf0hmqlgsg = _rtP -> P_119 ; } if ( ssIsSampleHit (
S , 2 , 0 ) ) { _rtB -> fdkr00istc = _rtP -> P_120 * _rtB -> grbdvor2ec ; }
if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> hkm4lypql5 = _rtP -> P_122 ;
memcpy ( & _rtB -> osbwdyoa5q [ 0 ] , & _rtP -> P_123 [ 0 ] , 9U * sizeof (
real_T ) ) ; memcpy ( & _rtB -> fhvj2avrxh [ 0 ] , & _rtP -> P_124 [ 0 ] ,
18U * sizeof ( real_T ) ) ; _rtB -> b5b3ywpdq0 = _rtP -> P_125 ; } _rtB ->
hyh0jrfm44 [ 0 ] = _rtB -> fdkr00istc ; _rtB -> hyh0jrfm44 [ 1 ] = _rtP ->
P_121 * npiyznthqi ; ssCallAccelRunBlock ( S , 7 , 1 , SS_CALL_MDL_OUTPUTS )
; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> jflhxky1jm = _rtP -> P_126 ; }
if ( 1.0 / n4kbehhhau * o5ibp43cp4 >= _rtP -> P_127 ) { efj5q5ebcq =
n4kbehhhau / o5ibp43cp4 ; if ( efj5q5ebcq > _rtP -> P_10 ) { if ( efj5q5ebcq
> _rtP -> P_8 ) { efj5q5ebcq = _rtP -> P_8 ; } else { if ( efj5q5ebcq < _rtP
-> P_9 ) { efj5q5ebcq = _rtP -> P_9 ; } } tmp = ( ( 1.0 - efj5q5ebcq ) *
0.14285714285714282 + efj5q5ebcq ) * ( 1.0 - efj5q5ebcq ) ; if ( tmp < 0.0 )
{ npiyznthqi = - muDoubleScalarSqrt ( - tmp ) ; } else { npiyznthqi =
muDoubleScalarSqrt ( tmp ) ; } } else { npiyznthqi = _rtB -> bf0hmqlgsg ; }
efj5q5ebcq = o5ibp43cp4 / _rtB -> evjqqlvc2b / _rtB -> bvgnvsn3md *
o5ibp43cp4 * _rtP -> P_13 ; if ( efj5q5ebcq < 0.0 ) { efj5q5ebcq = -
muDoubleScalarSqrt ( muDoubleScalarAbs ( efj5q5ebcq ) ) ; } else { efj5q5ebcq
= muDoubleScalarSqrt ( efj5q5ebcq ) ; } if ( _rtB -> ine15fziix > _rtP ->
P_11 ) { tmp = _rtP -> P_11 ; } else if ( _rtB -> ine15fziix < _rtP -> P_12 )
{ tmp = _rtP -> P_12 ; } else { tmp = _rtB -> ine15fziix ; } npiyznthqi =
efj5q5ebcq * tmp * npiyznthqi * _rtP -> P_14 ; } else { efj5q5ebcq = 1.0 /
n4kbehhhau * o5ibp43cp4 ; if ( efj5q5ebcq > _rtP -> P_2 ) { if ( efj5q5ebcq >
_rtP -> P_0 ) { efj5q5ebcq = _rtP -> P_0 ; } else { if ( efj5q5ebcq < _rtP ->
P_1 ) { efj5q5ebcq = _rtP -> P_1 ; } } tmp = ( ( 1.0 - efj5q5ebcq ) *
0.14285714285714282 + efj5q5ebcq ) * ( 1.0 - efj5q5ebcq ) ; if ( tmp < 0.0 )
{ npiyznthqi = - muDoubleScalarSqrt ( - tmp ) ; } else { npiyznthqi =
muDoubleScalarSqrt ( tmp ) ; } } else { npiyznthqi = _rtB -> jflhxky1jm ; }
efj5q5ebcq = n4kbehhhau / _rtB -> evjqqlvc2b / _rtB -> bvgnvsn3md *
n4kbehhhau * _rtP -> P_5 ; if ( efj5q5ebcq < 0.0 ) { efj5q5ebcq = -
muDoubleScalarSqrt ( muDoubleScalarAbs ( efj5q5ebcq ) ) ; } else { efj5q5ebcq
= muDoubleScalarSqrt ( efj5q5ebcq ) ; } if ( _rtB -> kodkkyrzjg > _rtP -> P_3
) { tmp = _rtP -> P_3 ; } else if ( _rtB -> kodkkyrzjg < _rtP -> P_4 ) { tmp
= _rtP -> P_4 ; } else { tmp = _rtB -> kodkkyrzjg ; } npiyznthqi = efj5q5ebcq
* tmp * npiyznthqi * _rtP -> P_6 * _rtP -> P_7 ; } if ( npiyznthqi > _rtP ->
P_128 ) { npiyznthqi = _rtP -> P_128 ; } else { if ( npiyznthqi < _rtP ->
P_129 ) { npiyznthqi = _rtP -> P_129 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) )
{ for ( i = 0 ; i < 7 ; i ++ ) { _rtB -> a2dxwdm22j [ i ] = _rtP -> P_130 [ i
] ; } _rtB -> c5mlimi3qz [ 0 ] = _rtP -> P_131 [ 0 ] ; _rtB -> c5mlimi3qz [ 1
] = _rtP -> P_131 [ 1 ] ; } efj5q5ebcq = _rtP -> P_132 * _rtB -> oyqyzhhm42 ;
_rtB -> puhdjtgatd = ( ( ( ( 0.43860691 * _rtB -> n103e0ixee + - 1283.1169 )
+ 10.249443 * efj5q5ebcq ) + 4.7302501 * _rtB -> jog4051tis ) + 4.3259397e-5
* muDoubleScalarPower ( _rtB -> n103e0ixee , 2.0 ) ) + - 0.13127391 *
muDoubleScalarPower ( efj5q5ebcq , 2.0 ) ; ssCallAccelRunBlock ( S , 118 ,
193 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 194 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> pvl4kgsny3 = _rtP -> P_133 * b11wdxnlxt ;
ssCallAccelRunBlock ( S , 15 , 0 , SS_CALL_MDL_OUTPUTS ) ; efj5q5ebcq = _rtB
-> indhq4wak4 + _rtB -> iygz0aaixm ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
_rtB -> a1yzvsdunn = ( 1369.19425815691 * muDoubleScalarPower ( _rtDW ->
h1201vgmm4 , 2.0 ) + 35.4540616064791 * _rtDW -> h1201vgmm4 ) +
97.0096843671075 ; } _rtB -> fajz32efsv = _rtB -> a1yzvsdunn / _rtB ->
b2luvekoek ; _rtB -> nck4drgpoy = _rtP -> P_135 * _rtB -> owjgmyz3gk ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> inegeuxc3h = _rtP -> P_136 ; _rtB ->
gym3bbdbwx = _rtP -> P_137 ; _rtB -> hyvz5vffay = _rtP -> P_138 ; _rtB ->
lthtmcjmht = _rtP -> P_139 ; for ( i = 0 ; i < 5 ; i ++ ) { _rtB ->
kuncb1oajx [ i ] = _rtP -> P_140 [ i ] ; } for ( i = 0 ; i < 7 ; i ++ ) {
_rtB -> p45hmrznvb [ i ] = _rtP -> P_141 [ i ] ; } } _rtB -> d1wnqgnnye [ 0 ]
= _rtB -> inegeuxc3h ; _rtB -> d1wnqgnnye [ 1 ] = _rtB -> gym3bbdbwx ; _rtB
-> d1wnqgnnye [ 2 ] = _rtB -> hyvz5vffay ; _rtB -> d1wnqgnnye [ 3 ] = _rtB ->
lthtmcjmht ; ssCallAccelRunBlock ( S , 17 , 1 , SS_CALL_MDL_OUTPUTS ) ; _rtB
-> nj41c0jgez = ( ( efj5q5ebcq - _rtB -> joo1p3hpwk ) - _rtB -> oyqyzhhm42 )
* _rtP -> P_142 ; _rtB -> ipseapjv0w = 1.0 / ( _rtP -> P_144 * gen03hfvbg ) *
( ( aktecqyana - _rtX -> ge52s03ms5 ) * efj5q5ebcq ) ; efj5q5ebcq = ( (
efj5q5ebcq * _rtB -> ddm05yw3si - _rtB -> joo1p3hpwk * _rtB -> n103e0ixee ) -
_rtB -> oyqyzhhm42 * _rtB -> n103e0ixee ) - ( _rtB -> ddm05yw3si - _rtB ->
jog4051tis ) * efj5q5ebcq * _rtP -> P_145 / 1.004 ; if ( ssIsSampleHit ( S ,
1 , 0 ) ) { _rtB -> k0wms3wqic = _rtP -> P_147 ; } _rtB -> lzk2nllx4e = _rtP
-> P_146 * efj5q5ebcq / _rtB -> k0wms3wqic ; _rtB -> paauf4sj4t = ( (
npiyznthqi + _rtB -> oyqyzhhm42 ) - _rtB -> indhq4wak4 ) * _rtP -> P_148 ;
_rtB -> je1ofclouv = ( ( _rtX -> ge52s03ms5 - _rtB -> ew4idsfm1c ) * _rtB ->
oyqyzhhm42 - npiyznthqi * _rtB -> ew4idsfm1c ) * ( 1.0 / ( _rtP -> P_149 *
c4l11istf0 ) ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> dbp44n0sg3 =
_rtP -> P_151 ; } _rtB -> as1beoowbo = ( ( npiyznthqi * _rtB -> evjqqlvc2b +
_rtB -> oyqyzhhm42 * _rtB -> aomqll03f3 ) - _rtB -> ho1qnfguxm * _rtB ->
indhq4wak4 ) * _rtP -> P_150 / _rtB -> dbp44n0sg3 ; _rtB -> moeq5yoq3z = (
1.6e-9 * muDoubleScalarPower ( _rtB -> owjgmyz3gk , 2.0 ) + -
1.82444404829743e-6 * _rtB -> owjgmyz3gk ) + 0.002 ; ssCallAccelRunBlock ( S
, 118 , 232 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
_rtB -> igvptnm13v = _rtP -> P_152 ; } _rtB -> fwqrziwuvl = ( _rtB ->
owjgmyz3gk <= _rtB -> igvptnm13v ) ; if ( ssIsSampleHit ( S , 1 , 0 ) && _rtB
-> fwqrziwuvl ) { ssSetStopRequested ( S , 1 ) ; } ssCallAccelRunBlock ( S ,
118 , 236 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> msdc4mojab = ( ( _rtB ->
bryj0ppggc - _rtB -> moeq5yoq3z ) - _rtB -> em4bb22xsn ) * _rtP -> P_153 ;
ssCallAccelRunBlock ( S , 118 , 239 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 118 , 240 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
deduzorios = ( _rtB -> o4etjyeod5 - npiyznthqi ) * _rtB -> evjqqlvc2b * _rtP
-> P_154 ; ssCallAccelRunBlock ( S , 118 , 243 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 4 , 0 ) ) { _rtB -> efnnlvmivp = _rtDW -> beiefj4kfo ; }
if ( ssIsSampleHit ( S , 5 , 0 ) ) { _rtB -> o43ddgrylg = _rtDW -> d2tl5o0hel
; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { dxuu1n0atf * _rtB ;
nka5ekiiij * _rtP ; cet3mqzt35 * _rtDW ; _rtDW = ( ( cet3mqzt35 * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( nka5ekiiij * ) ssGetDefaultParam ( S ) )
; _rtB = ( ( dxuu1n0atf * ) _ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S ,
1 , 0 ) ) { _rtDW -> cc0wkfbxf2 = _rtB -> aomqll03f3 ; _rtDW -> eac1jvpkom =
_rtB -> crzvznbqgp ; } if ( ssIsSampleHit ( S , 3 , 0 ) ) { foiteff4aq ( _rtB
-> efnnlvmivp , & _rtDW -> masm1qwyo5u ) ; foiteff4aq ( _rtB -> o43ddgrylg ,
& _rtDW -> cdbewnv5xj ) ; foiteff4aq ( _rtB -> kh41jqwpx0 , & _rtDW ->
lwrmmrtmge ) ; } if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtDW -> avtbwzqnkf [ 0
] = _rtB -> cnnxmyxf0o [ 0 ] ; _rtDW -> avtbwzqnkf [ 1 ] = _rtB -> cnnxmyxf0o
[ 1 ] ; _rtDW -> poa5fptxm4 = _rtB -> cytczbxazy ; _rtDW -> bsbxmlf10r = _rtB
-> cthsuitfz5 ; _rtDW -> pybwwu5s4d = _rtB -> ldjrvtlkq4 ; _rtDW ->
j5f3ay4xaq = _rtB -> ic0xftdx3y ; _rtDW -> ackerqxqlr = _rtB -> ic0xftdx3y ;
_rtDW -> c1qvpfpyqu = _rtB -> ldjrvtlkq4 ; _rtDW -> em10zry3vm = _rtB ->
dobwfafcm0 ; _rtDW -> cz55ow2si1 [ 0 ] = _rtB -> ck5rlv2b0s [ 0 ] ; _rtDW ->
cz55ow2si1 [ 1 ] = _rtB -> ck5rlv2b0s [ 1 ] ; _rtDW -> cz55ow2si1 [ 2 ] =
_rtB -> ck5rlv2b0s [ 2 ] ; _rtDW -> h4gbii3cbq = _rtB -> khafhjxib1 ; _rtDW
-> o04t4yciip = _rtB -> lbwa3jpkws ; _rtDW -> lzwd5z4dbk = _rtB -> bb2txpcrdw
; _rtDW -> dgfekwwlr1 = _rtB -> em05kjxq5f ; _rtDW -> dw2dt5amj1 = _rtB ->
czspnnf2wz ; _rtDW -> letoggxozl = _rtB -> aeal0w25ez ; _rtDW -> frjwyakiph =
_rtB -> iqg1nj4hwf ; _rtDW -> i5yn1movmy = _rtB -> nd3bibt0gk ; _rtDW ->
diffnla35e = _rtB -> emejhjadst ; _rtDW -> nqyjhyuvcj = _rtB -> iq211sbcwf ;
_rtDW -> fjcoqtw2bx = _rtB -> o0aceads0s ; _rtDW -> iggiejtmqu = _rtB ->
fgtlymqtj5 ; _rtDW -> mvpjwhrzk3 = _rtB -> lksu3sv24v ; _rtDW -> mtqhixagy1 =
_rtB -> lmn34nxqxt ; _rtDW -> fhgbtmls3d = _rtB -> egwnphshj3 ; _rtDW ->
l1sigmyvxe = _rtB -> mskakvqxnl ; _rtDW -> noqny2ee14 = _rtB -> ldjrvtlkq4 ;
_rtDW -> ljbykua013 = _rtB -> dobwfafcm0 ; } if ( ssIsSampleHit ( S , 1 , 0 )
) { _rtDW -> h1201vgmm4 = _rtB -> joo1p3hpwk ; } if ( ssIsSampleHit ( S , 4 ,
0 ) ) { _rtDW -> beiefj4kfo = ( _rtP -> P_156 - _rtP -> P_155 ) *
rt_urand_Upu32_Yd_f_pw_snf ( & _rtDW -> msu4qgbkxt ) + _rtP -> P_155 ; } if (
ssIsSampleHit ( S , 5 , 0 ) ) { _rtDW -> d2tl5o0hel = ( _rtP -> P_159 - _rtP
-> P_158 ) * rt_urand_Upu32_Yd_f_pw_snf ( & _rtDW -> grioepryal ) + _rtP ->
P_158 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { dxuu1n0atf * _rtB ; pi4eqa0gee
* _rtXdot ; _rtXdot = ( ( pi4eqa0gee * ) ssGetdX ( S ) ) ; _rtB = ( (
dxuu1n0atf * ) _ssGetBlockIO ( S ) ) ; _rtXdot -> mupnfilrqo = _rtB ->
as1beoowbo ; _rtXdot -> huyhg2ps31 = _rtB -> lzk2nllx4e ; _rtXdot ->
lgbs44xptg = _rtB -> deduzorios ; _rtXdot -> ka43gmkysq = _rtB -> msdc4mojab
; _rtXdot -> iqp0o3u0ph = _rtB -> paauf4sj4t ; _rtXdot -> iynqfp2xbi = _rtB
-> nj41c0jgez ; _rtXdot -> cgw3asjtrv = _rtB -> je1ofclouv ; _rtXdot ->
ge52s03ms5 = _rtB -> ipseapjv0w ; } static void mdlInitializeSizes (
SimStruct * S ) { ssSetChecksumVal ( S , 0 , 2983446547U ) ; ssSetChecksumVal
( S , 1 , 3754771109U ) ; ssSetChecksumVal ( S , 2 , 4126448585U ) ;
ssSetChecksumVal ( S , 3 , 595030788U ) ; { mxArray * slVerStructMat = NULL ;
mxArray * slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ;
int status = mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" )
; if ( status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == NULL ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "8.5" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
cet3mqzt35 ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( dxuu1n0atf ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofU ( S ) != sizeof
( dq45bcq35i ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal ExternalInputs sizes do "
"not match for accelerator mex file." ) ; ssSetErrorStatus ( S , msg ) ; } if
( ssGetSizeofY ( S ) != sizeof ( b5pgekrytf ) ) { static char msg [ 256 ] ;
sprintf ( msg , "Unexpected error: Internal ExternalOutputs sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
nka5ekiiij ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & fdwl42vave ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; ( (
nka5ekiiij * ) ssGetDefaultParam ( S ) ) -> P_3 = rtInf ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_11 = rtInf ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_18 = rtInf ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_26 = rtInf ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_50 = rtInf ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_52 = rtInf ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_71 = rtInf ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_171 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_175 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_177 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_181 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_184 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_187 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_197 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_199 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_201 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_203 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_209 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_212 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_215 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_219 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_221 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_225 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_227 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_238 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_242 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_247 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_249 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_251 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_253 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_289 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_291 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_293 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_297 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_463 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_465 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_468 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_470 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_472 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_524 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_531 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_535 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_556 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_580 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_584 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_587 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_590 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_592 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_596 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_607 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_613 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_657 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_662 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_665 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_674 = rtInfF ; } static void
mdlInitializeSampleTimes ( SimStruct * S ) { { SimStruct * childS ;
SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S , 0 ) ; callSysFcns
= ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 1 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 2 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 3 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 4 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 5 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 6 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 7 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 8 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 9 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; } } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
