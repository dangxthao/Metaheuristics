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
* S , int_T tid ) { real_T jolwkb0ztx ; real32_T iou1bb3prl ; real32_T
omfw35sfyk ; real32_T j5z4rdmkwv ; real32_T ase2d1biln ; real32_T awl0z0b3sb
; real32_T a3jnflwpkj ; real32_T ckkx05hfhz ; int32_T esndn1d5qn ; int32_T
mldy4xfo0l ; real_T isss3jba5z ; real_T pjtzipg04i ; real32_T e4orw3vqsn ;
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
* _rtB -> ircgfqnvid ; _rtB -> p3z5lkj1n3 = _rtP -> P_42 * _rtP -> P_41 ;
_rtB -> mgmokgblyl = _rtP -> P_44 * _rtP -> P_43 ; } if ( ssIsSampleHit ( S ,
3 , 0 ) ) { masm1qwyo5 ( & _rtB -> masm1qwyo5u , & _rtDW -> masm1qwyo5u , (
ev5xuv0chq * ) & _rtP -> masm1qwyo5u ) ; masm1qwyo5 ( & _rtB -> cdbewnv5xj ,
& _rtDW -> cdbewnv5xj , ( ev5xuv0chq * ) & _rtP -> cdbewnv5xj ) ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 118 , 14 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 3 , 0 ) ) { masm1qwyo5 ( &
_rtB -> lwrmmrtmge , & _rtDW -> lwrmmrtmge , ( ev5xuv0chq * ) & _rtP ->
lwrmmrtmge ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> mgmokgblyl =
_rtP -> P_45 ; ssCallAccelRunBlock ( S , 118 , 17 , SS_CALL_MDL_OUTPUTS ) ; }
if ( ssIsSampleHit ( S , 2 , 0 ) ) { ssCallAccelRunBlock ( S , 118 , 18 ,
SS_CALL_MDL_OUTPUTS ) ; if ( _rtB -> bdookktsiu > _rtP -> P_46 ) { _rtB ->
g2wdwqcgm0 = _rtP -> P_46 ; } else if ( _rtB -> bdookktsiu < _rtP -> P_47 ) {
_rtB -> g2wdwqcgm0 = _rtP -> P_47 ; } else { _rtB -> g2wdwqcgm0 = _rtB ->
bdookktsiu ; } ssCallAccelRunBlock ( S , 118 , 20 , SS_CALL_MDL_OUTPUTS ) ;
if ( _rtB -> bdookktsiu > _rtP -> P_48 ) { _rtB -> dkuzk20to1 = _rtP -> P_48
; } else if ( _rtB -> bdookktsiu < _rtP -> P_49 ) { _rtB -> dkuzk20to1 = _rtP
-> P_49 ; } else { _rtB -> dkuzk20to1 = _rtB -> bdookktsiu ; } } if (
ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 118 , 22 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 118 , 23 ,
SS_CALL_MDL_OUTPUTS ) ; b11wdxnlxt = _rtP -> P_50 * _rtB -> abq1p53goy [ 1 ]
; npiyznthqi = _rtP -> P_51 * b11wdxnlxt ; if ( ssIsSampleHit ( S , 1 , 0 ) )
{ _rtB -> ojhesksyob = _rtP -> P_53 ; memcpy ( & _rtB -> n14h3ghe24 [ 0 ] , &
_rtP -> P_54 [ 0 ] , 9U * sizeof ( real_T ) ) ; memcpy ( & _rtB -> dx03szxnnl
[ 0 ] , & _rtP -> P_55 [ 0 ] , 18U * sizeof ( real_T ) ) ; _rtB -> ntvqkxd0ew
= _rtP -> P_56 ; } _rtB -> burpslxsjz [ 0 ] = _rtB -> fh2qfrkpzp ; _rtB ->
burpslxsjz [ 1 ] = _rtP -> P_52 * npiyznthqi ; ssCallAccelRunBlock ( S , 14 ,
1 , SS_CALL_MDL_OUTPUTS ) ; o5ibp43cp4 = _rtP -> P_57 * _rtB -> bchvsczbjy ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> jo0d2qrlo3 = _rtP -> P_58 ; _rtB
-> fshec5wz2o = _rtP -> P_59 * _rtB -> ircgfqnvid ; _rtB -> gbo4tvzupy = _rtP
-> P_61 ; memcpy ( & _rtB -> mm3jwjhmvi [ 0 ] , & _rtP -> P_62 [ 0 ] , 9U *
sizeof ( real_T ) ) ; memcpy ( & _rtB -> kb1vuy0qfs [ 0 ] , & _rtP -> P_63 [
0 ] , 18U * sizeof ( real_T ) ) ; _rtB -> cyvox4ezyw = _rtP -> P_64 ; } _rtB
-> mqekmji2jy [ 0 ] = _rtB -> fshec5wz2o ; _rtB -> mqekmji2jy [ 1 ] = _rtP ->
P_60 * npiyznthqi ; ssCallAccelRunBlock ( S , 13 , 1 , SS_CALL_MDL_OUTPUTS )
; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> fx5vhkxbrl = _rtP -> P_65 ; }
if ( 1.0 / o5ibp43cp4 * n4kbehhhau >= _rtP -> P_66 ) { efj5q5ebcq =
o5ibp43cp4 / n4kbehhhau ; if ( efj5q5ebcq > _rtP -> P_25 ) { if ( efj5q5ebcq
> _rtP -> P_23 ) { efj5q5ebcq = _rtP -> P_23 ; } else { if ( efj5q5ebcq <
_rtP -> P_24 ) { efj5q5ebcq = _rtP -> P_24 ; } } tmp = ( ( 1.0 - efj5q5ebcq )
* 0.14285714285714282 + efj5q5ebcq ) * ( 1.0 - efj5q5ebcq ) ; if ( tmp < 0.0
) { npiyznthqi = - muDoubleScalarSqrt ( - tmp ) ; } else { npiyznthqi =
muDoubleScalarSqrt ( tmp ) ; } } else { npiyznthqi = _rtB -> jo0d2qrlo3 ; }
efj5q5ebcq = n4kbehhhau / _rtB -> lcox2cqw1x / _rtB -> cfjfxf2th0 *
n4kbehhhau * _rtP -> P_28 ; if ( efj5q5ebcq < 0.0 ) { efj5q5ebcq = -
muDoubleScalarSqrt ( muDoubleScalarAbs ( efj5q5ebcq ) ) ; } else { efj5q5ebcq
= muDoubleScalarSqrt ( efj5q5ebcq ) ; } if ( _rtB -> clgr4b120z > _rtP ->
P_26 ) { tmp = _rtP -> P_26 ; } else if ( _rtB -> clgr4b120z < _rtP -> P_27 )
{ tmp = _rtP -> P_27 ; } else { tmp = _rtB -> clgr4b120z ; } _rtB ->
g4zs5uffpf = efj5q5ebcq * tmp * npiyznthqi * _rtP -> P_29 ; } else {
efj5q5ebcq = 1.0 / o5ibp43cp4 * n4kbehhhau ; if ( efj5q5ebcq > _rtP -> P_17 )
{ if ( efj5q5ebcq > _rtP -> P_15 ) { efj5q5ebcq = _rtP -> P_15 ; } else { if
( efj5q5ebcq < _rtP -> P_16 ) { efj5q5ebcq = _rtP -> P_16 ; } } tmp = ( ( 1.0
- efj5q5ebcq ) * 0.14285714285714282 + efj5q5ebcq ) * ( 1.0 - efj5q5ebcq ) ;
if ( tmp < 0.0 ) { npiyznthqi = - muDoubleScalarSqrt ( - tmp ) ; } else {
npiyznthqi = muDoubleScalarSqrt ( tmp ) ; } } else { npiyznthqi = _rtB ->
fx5vhkxbrl ; } efj5q5ebcq = o5ibp43cp4 / _rtB -> lcox2cqw1x / _rtB ->
cfjfxf2th0 * o5ibp43cp4 * _rtP -> P_20 ; if ( efj5q5ebcq < 0.0 ) { efj5q5ebcq
= - muDoubleScalarSqrt ( muDoubleScalarAbs ( efj5q5ebcq ) ) ; } else {
efj5q5ebcq = muDoubleScalarSqrt ( efj5q5ebcq ) ; } if ( _rtB -> pm03vr5zrk >
_rtP -> P_18 ) { tmp = _rtP -> P_18 ; } else if ( _rtB -> pm03vr5zrk < _rtP
-> P_19 ) { tmp = _rtP -> P_19 ; } else { tmp = _rtB -> pm03vr5zrk ; } _rtB
-> g4zs5uffpf = efj5q5ebcq * tmp * npiyznthqi * _rtP -> P_21 * _rtP -> P_22 ;
} if ( _rtB -> g4zs5uffpf > _rtP -> P_67 ) { _rtB -> emytkc4hpm = _rtP ->
P_67 ; } else if ( _rtB -> g4zs5uffpf < _rtP -> P_68 ) { _rtB -> emytkc4hpm =
_rtP -> P_68 ; } else { _rtB -> emytkc4hpm = _rtB -> g4zs5uffpf ; }
ssCallAccelRunBlock ( S , 118 , 47 , SS_CALL_MDL_OUTPUTS ) ; npiyznthqi =
_rtX -> lgbs44xptg ; _rtB -> cnzqd1iis2 = 1.0 / _rtB -> mdayruhtru * _rtX ->
lgbs44xptg ; ssCallAccelRunBlock ( S , 118 , 50 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> mdayruhtru = _rtX -> ka43gmkysq ; _rtB -> lerlbeqhnx = _rtP -> P_71 *
_rtB -> mdayruhtru ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> bg34kireo5
= _rtP -> P_72 ; _rtB -> fd1sxxwdcy = _rtP -> P_73 ; _rtB -> ctgfi2lvmt =
_rtP -> P_74 ; _rtB -> o1uzvyl4oe = _rtP -> P_75 ; _rtB -> bsmnltswab = _rtP
-> P_76 ; memcpy ( & _rtB -> cjfw3wzab4 [ 0 ] , & _rtP -> P_77 [ 0 ] , 12U *
sizeof ( real_T ) ) ; memcpy ( & _rtB -> bgkxgls2fy [ 0 ] , & _rtP -> P_78 [
0 ] , 9U * sizeof ( real_T ) ) ; } _rtB -> mwi40jynvr [ 0 ] = _rtB ->
bg34kireo5 ; _rtB -> mwi40jynvr [ 1 ] = _rtB -> fd1sxxwdcy ; _rtB ->
mwi40jynvr [ 2 ] = _rtB -> ctgfi2lvmt ; _rtB -> mwi40jynvr [ 3 ] = _rtB ->
o1uzvyl4oe ; _rtB -> mwi40jynvr [ 4 ] = _rtB -> bsmnltswab ;
ssCallAccelRunBlock ( S , 2 , 1 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> gzbcdplagg
= _rtB -> emytkc4hpm / ( _rtB -> emytkc4hpm + _rtB -> o4etjyeod5 ) * _rtP ->
P_79 ; _rtB -> jnrdxk3azf = ( real32_T ) _rtB -> gzbcdplagg ; _rtB ->
auohfil2jj = ( real32_T ) _rtB -> abq1p53goy [ 0 ] ; _rtB -> agikm532fv = (
real32_T ) _rtB -> abq1p53goy [ 1 ] ; _rtB -> fgauyincbo = ( real32_T ) _rtB
-> b2luvekoek ; c4l11istf0 = _rtX -> iqp0o3u0ph ; _rtB -> hupcczf3ah = 1.0 /
( _rtP -> P_81 * _rtX -> iqp0o3u0ph ) * _rtB -> bchvsczbjy ; if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> m3skk1zhjh = _rtP -> P_743 ; } _rtB
-> i2cdqqxwp0 = ( real32_T ) _rtB -> hupcczf3ah - _rtB -> m3skk1zhjh ; _rtB
-> bblimdbln2 = ( real32_T ) ( _rtP -> P_82 * _rtB -> emytkc4hpm ) ; _rtB ->
mt0t1wog2n = ( real32_T ) ( _rtP -> P_83 * _rtB -> o4etjyeod5 ) ; _rtB ->
i12tydiwwi = _rtP -> P_84 * b11wdxnlxt ; gen03hfvbg = _rtX -> iynqfp2xbi ;
_rtB -> i5ltskj44y = 1.0 / ( _rtP -> P_86 * _rtX -> iynqfp2xbi ) * _rtB ->
b2luvekoek ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> db1ygdxcf2 = _rtP
-> P_87 ; _rtB -> bgtyc0diwi = _rtP -> P_88 ; for ( i = 0 ; i < 6 ; i ++ ) {
_rtB -> pqwsytper5 [ i ] = _rtP -> P_89 [ i ] ; } } _rtB -> jzkasgtoic [ 0 ]
= _rtB -> db1ygdxcf2 ; _rtB -> jzkasgtoic [ 1 ] = _rtB -> bgtyc0diwi ;
ssCallAccelRunBlock ( S , 1 , 1 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> n2un1jwvgy
= _rtP -> P_90 * _rtB -> lsyc0sxhxh ; if ( _rtB -> abq1p53goy [ 1 ] > _rtP ->
P_93 ) { tmp = _rtP -> P_93 ; } else if ( _rtB -> abq1p53goy [ 1 ] < _rtP ->
P_94 ) { tmp = _rtP -> P_94 ; } else { tmp = _rtB -> abq1p53goy [ 1 ] ; }
_rtB -> ou0itdgh1d = ( real32_T ) ( _rtP -> P_91 * _rtB -> n2un1jwvgy * _rtP
-> P_92 / tmp ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> ldjrvtlkq4 =
_rtB -> ipni0rpjg1 ; _rtB -> hscm1hdjfm = _rtP -> P_435 * _rtB -> ldjrvtlkq4
; _rtDW -> estlkslffw = _rtB -> hscm1hdjfm ; ssWriteToDataStoreWithPath ( S ,
_rtDW -> ofu0g31ksp ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write"
, NULL ) ; _rtB -> lfhmjay0c0 = _rtP -> P_436 * _rtB -> jnrdxk3azf ; _rtDW ->
dpzir5hccd = _rtB -> lfhmjay0c0 ; ssWriteToDataStoreWithPath ( S , _rtDW ->
mogcuu34yn ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write1"
, NULL ) ; ic3wqfpram_idx_0 = _rtP -> P_437 [ 0 ] ; ic3wqfpram_idx_1 = _rtP
-> P_437 [ 1 ] ; pn0idallhu_idx_0 = _rtDW -> avtbwzqnkf [ 0 ] ;
pn0idallhu_idx_1 = _rtDW -> avtbwzqnkf [ 1 ] ; jsgk2hka41_idx_0 = _rtDW ->
avtbwzqnkf [ 0 ] - _rtP -> P_438 [ 0 ] ; jsgk2hka41_idx_1 = _rtDW ->
avtbwzqnkf [ 1 ] - _rtP -> P_438 [ 1 ] ; btosikvjyf [ 0 ] = _rtP -> P_440 [ 0
] * jsgk2hka41_idx_0 + _rtP -> P_440 [ 2 ] * jsgk2hka41_idx_1 ; btosikvjyf [
1 ] = _rtP -> P_440 [ 1 ] * jsgk2hka41_idx_0 + _rtP -> P_440 [ 3 ] *
jsgk2hka41_idx_1 ; finyivsrdi = _rtDW -> poa5fptxm4 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/custom_filter/Data Store Read8"
, NULL ) ; _rtB -> la1bi141vb = _rtP -> P_442 * _rtDW -> owcamicoch ; if (
_rtB -> la1bi141vb > _rtP -> P_443 ) { e0r0t533ao = _rtP -> P_443 ; } else if
( _rtB -> la1bi141vb < _rtP -> P_444 ) { e0r0t533ao = _rtP -> P_444 ; } else
{ e0r0t533ao = _rtB -> la1bi141vb ; } cbpfnq4pxd = _rtP -> P_445 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/custom_filter/Data Store Read1"
, NULL ) ; _rtB -> blsiovdtlr = _rtP -> P_446 * _rtDW -> owcamicoch ; if (
_rtB -> blsiovdtlr > _rtP -> P_447 ) { dpajlxfdyx_idx_0 = _rtP -> P_447 ; }
else if ( _rtB -> blsiovdtlr < _rtP -> P_448 ) { dpajlxfdyx_idx_0 = _rtP ->
P_448 ; } else { dpajlxfdyx_idx_0 = _rtB -> blsiovdtlr ; } alqkjudhu3 =
cbpfnq4pxd - dpajlxfdyx_idx_0 ; ssReadFromDataStoreWithPath ( S , _rtDW ->
ess4wlwley ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/Data Store Read1"
, NULL ) ; _rtB -> o5smpqnaet = _rtP -> P_449 * _rtDW -> bpo1eig15d ; if (
_rtB -> o5smpqnaet > _rtP -> P_450 ) { o3mfdsmmfb = _rtB -> ou0itdgh1d * _rtB
-> agikm532fv / _rtP -> P_258 ; } else { o3mfdsmmfb = _rtB -> ou0itdgh1d ; }
e4orw3vqsn = _rtDW -> bsbxmlf10r ; cbpfnq4pxd = _rtP -> P_452 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> ourjtqa0v4 ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/Data Store Read3"
, NULL ) ; _rtB -> dnzxvrt3hi = _rtP -> P_453 * _rtDW -> o0hytehsup ; if (
_rtB -> dnzxvrt3hi > _rtP -> P_454 ) {
KD_cl_harness_forthao_breach_acc_LookUp_real32_T_real32_T ( & ( emptrcbnkv )
, _rtP -> P_257 , e4orw3vqsn , _rtP -> P_256 , 1U ) ; o3mfdsmmfb = (
cbpfnq4pxd - emptrcbnkv ) * _rtB -> mt0t1wog2n + o3mfdsmmfb * emptrcbnkv ; }
ssReadFromDataStoreWithPath ( S , _rtDW -> gl5aakmwtq ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/egr_est/Data Store Read8"
, NULL ) ; _rtB -> k2jykilip4 = _rtP -> P_455 * _rtDW -> jnju4d4o03 ;
jfmtdksnh0 = _rtP -> P_458 ; if ( _rtB -> i2cdqqxwp0 > _rtP -> P_459 ) {
kaqx4nados = _rtP -> P_459 ; } else if ( _rtB -> i2cdqqxwp0 < _rtP -> P_460 )
{ kaqx4nados = _rtP -> P_460 ; } else { kaqx4nados = _rtB -> i2cdqqxwp0 ; }
jfmtdksnh0 += kaqx4nados ; u0 = jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_463 ; if
( u0 > _rtP -> P_461 ) { u0 = _rtP -> P_461 ; } else { if ( u0 < _rtP ->
P_462 ) { u0 = _rtP -> P_462 ; } } if ( jfmtdksnh0 > _rtP -> P_464 ) {
dpajlxfdyx_idx_0 = _rtP -> P_464 ; } else if ( jfmtdksnh0 < _rtP -> P_465 ) {
dpajlxfdyx_idx_0 = _rtP -> P_465 ; } else { dpajlxfdyx_idx_0 = jfmtdksnh0 ; }
o3mfdsmmfb += ( _rtB -> ldjrvtlkq4 - _rtDW -> pybwwu5s4d ) * _rtB ->
k2jykilip4 * _rtP -> P_457 / u0 / dpajlxfdyx_idx_0 - _rtB -> mt0t1wog2n ; if
( o3mfdsmmfb > _rtP -> P_466 ) { o3mfdsmmfb = _rtP -> P_466 ; } else { if (
o3mfdsmmfb < _rtP -> P_467 ) { o3mfdsmmfb = _rtP -> P_467 ; } } _rtB ->
cytczbxazy = finyivsrdi * e0r0t533ao + alqkjudhu3 * o3mfdsmmfb ; jfmtdksnh0 =
_rtB -> cytczbxazy + _rtB -> mt0t1wog2n ; if ( jfmtdksnh0 > _rtP -> P_468 ) {
dpajlxfdyx_idx_0 = _rtP -> P_468 ; } else if ( jfmtdksnh0 < _rtP -> P_469 ) {
dpajlxfdyx_idx_0 = _rtP -> P_469 ; } else { dpajlxfdyx_idx_0 = jfmtdksnh0 ; }
orelggziy4 = _rtB -> cytczbxazy / dpajlxfdyx_idx_0 * _rtP -> P_470 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> h5rpc5xiyn ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read8"
, NULL ) ; jfmtdksnh0 = _rtDW -> hyhv0echnn ; _rtB -> hqg1hpmaaw = _rtP ->
P_471 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_472 ; if ( _rtB -> hqg1hpmaaw >
jfmtdksnh0 ) { _rtB -> dobwfafcm0 = orelggziy4 ; } else { _rtB -> dobwfafcm0
= _rtB -> jnrdxk3azf ; } btosikvjyf [ 0 ] = _rtB -> ldjrvtlkq4 - btosikvjyf [
0 ] ; jfmtdksnh0 = _rtDW -> j5f3ay4xaq ; ic3wqfpram_idx_0 = ( btosikvjyf [ 0
] - ic3wqfpram_idx_0 ) - _rtP -> P_474 [ 0 ] * jfmtdksnh0 ; dpajlxfdyx_idx_0
= ( ( _rtB -> dobwfafcm0 - btosikvjyf [ 1 ] ) - ic3wqfpram_idx_1 ) - _rtP ->
P_474 [ 1 ] * jfmtdksnh0 ; cbpfnq4pxd = _rtP -> P_476 * jfmtdksnh0 ;
jfmtdksnh0 = _rtP -> P_477 [ 0 ] * jsgk2hka41_idx_0 + _rtP -> P_477 [ 1 ] *
jsgk2hka41_idx_1 ; _rtB -> ic0xftdx3y = ( ( _rtP -> P_475 [ 0 ] *
ic3wqfpram_idx_0 + _rtP -> P_475 [ 1 ] * dpajlxfdyx_idx_0 ) + cbpfnq4pxd ) +
jfmtdksnh0 ; _rtB -> khafhjxib1 = _rtB -> ic0xftdx3y - _rtDW -> ackerqxqlr ;
jfmtdksnh0 = _rtDW -> c1qvpfpyqu ; o3mfdsmmfb = _rtDW -> em10zry3vm ;
ssReadFromDataStoreWithPath ( S , _rtDW -> nqxydshzsv ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read16"
, NULL ) ; _rtB -> dxbeigwbxl = _rtP -> P_481 * _rtDW -> dhb1ak5ywv ; if (
_rtB -> dxbeigwbxl > _rtP -> P_482 ) { exrgmvycyf_idx_0 = _rtB -> khafhjxib1
; exrgmvycyf_idx_1 = jfmtdksnh0 ; exrgmvycyf_idx_2 = o3mfdsmmfb ; } else {
exrgmvycyf_idx_0 = _rtDW -> cz55ow2si1 [ 0 ] ; exrgmvycyf_idx_1 = _rtDW ->
cz55ow2si1 [ 1 ] ; exrgmvycyf_idx_2 = _rtDW -> cz55ow2si1 [ 2 ] ; } _rtB ->
pbopc5e2xk = _rtP -> P_484 * exrgmvycyf_idx_1 ; _rtDW -> n5pkawvqdo = _rtB ->
pbopc5e2xk ; ssWriteToDataStoreWithPath ( S , _rtDW -> i5qc0rf4ul ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write10"
, NULL ) ; _rtB -> fhegodw1bv = _rtP -> P_485 * exrgmvycyf_idx_2 ; _rtDW ->
c1deueau4e = _rtB -> fhegodw1bv ; ssWriteToDataStoreWithPath ( S , _rtDW ->
jl3aimob5t ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write11"
, NULL ) ; _rtB -> k2xoaosf3f = _rtP -> P_486 * exrgmvycyf_idx_0 ; _rtDW ->
mi5h1pks4n = _rtB -> k2xoaosf3f ; ssWriteToDataStoreWithPath ( S , _rtDW ->
jzhsquaa0d ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write12"
, NULL ) ; ssReadFromDataStoreWithPath ( S , _rtDW -> h5rpc5xiyn ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read9"
, NULL ) ; jfmtdksnh0 = _rtDW -> hyhv0echnn ; _rtB -> m3engjean1 = _rtP ->
P_487 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_488 ; if ( _rtB -> m3engjean1 >
jfmtdksnh0 ) { ic3wqfpram_idx_1 = _rtB -> cytczbxazy ; } else {
ic3wqfpram_idx_1 = _rtB -> bblimdbln2 ; } ic3wqfpram_idx_0 = _rtP -> P_489 *
kaqx4nados + _rtP -> P_490 ; ssReadFromDataStoreWithPath ( S , _rtDW ->
drhj21kmpw ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read14"
, NULL ) ; _rtB -> gkhrttsbg1 = _rtP -> P_491 * _rtDW -> fllyhv1jnh ;
batdnpsvim = _rtB -> gkhrttsbg1 + _rtB -> fgauyincbo ; finyivsrdi = _rtP ->
P_492 ; jfmtdksnh0 = _rtDW -> o04t4yciip ; btosikvjyf [ 0 ] = _rtP -> P_495 [
0 ] * _rtDW -> h4gbii3cbq + _rtP -> P_495 [ 2 ] * jfmtdksnh0 ; btosikvjyf [ 1
] = _rtP -> P_495 [ 1 ] * _rtDW -> h4gbii3cbq ; btosikvjyf [ 1 ] += _rtP ->
P_495 [ 3 ] * jfmtdksnh0 ; cbpfnq4pxd = _rtDW -> lzwd5z4dbk ;
ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter/Data Store Read8"
, NULL ) ; _rtB -> cefzy5i3uw = _rtP -> P_497 * _rtDW -> owcamicoch ; if (
_rtB -> cefzy5i3uw > _rtP -> P_498 ) { alqkjudhu3 = _rtP -> P_498 ; } else if
( _rtB -> cefzy5i3uw < _rtP -> P_499 ) { alqkjudhu3 = _rtP -> P_499 ; } else
{ alqkjudhu3 = _rtB -> cefzy5i3uw ; } kaqx4nados = _rtP -> P_500 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter/Data Store Read1"
, NULL ) ; jfmtdksnh0 = _rtDW -> owcamicoch ; _rtB -> pyz3jksooh = _rtP ->
P_501 * jfmtdksnh0 ; _rtB -> em05kjxq5f = _rtB -> auohfil2jj * _rtB ->
agikm532fv * _rtP -> P_504 ; if ( _rtB -> pyz3jksooh > _rtP -> P_502 ) {
dpajlxfdyx_idx_0 = _rtP -> P_502 ; } else if ( _rtB -> pyz3jksooh < _rtP ->
P_503 ) { dpajlxfdyx_idx_0 = _rtP -> P_503 ; } else { dpajlxfdyx_idx_0 = _rtB
-> pyz3jksooh ; } _rtB -> bb2txpcrdw = ( kaqx4nados - dpajlxfdyx_idx_0 ) * (
_rtB -> em05kjxq5f - _rtDW -> dgfekwwlr1 ) + cbpfnq4pxd * alqkjudhu3 ;
cbpfnq4pxd = _rtDW -> dw2dt5amj1 ; ssReadFromDataStoreWithPath ( S , _rtDW ->
iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter1/Data Store Read8"
, NULL ) ; _rtB -> fbsgkm3jsf = _rtP -> P_507 * _rtDW -> owcamicoch ; if (
_rtB -> fbsgkm3jsf > _rtP -> P_508 ) { alqkjudhu3 = _rtP -> P_508 ; } else if
( _rtB -> fbsgkm3jsf < _rtP -> P_509 ) { alqkjudhu3 = _rtP -> P_509 ; } else
{ alqkjudhu3 = _rtB -> fbsgkm3jsf ; } kaqx4nados = _rtP -> P_510 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter1/Data Store Read1"
, NULL ) ; jfmtdksnh0 = _rtDW -> owcamicoch ; _rtB -> mtwomkip2g = _rtP ->
P_511 * jfmtdksnh0 ; if ( _rtB -> mtwomkip2g > _rtP -> P_512 ) {
dpajlxfdyx_idx_0 = _rtP -> P_512 ; } else if ( _rtB -> mtwomkip2g < _rtP ->
P_513 ) { dpajlxfdyx_idx_0 = _rtP -> P_513 ; } else { dpajlxfdyx_idx_0 = _rtB
-> mtwomkip2g ; } _rtB -> czspnnf2wz = ( kaqx4nados - dpajlxfdyx_idx_0 ) * (
_rtB -> agikm532fv - _rtDW -> letoggxozl ) + cbpfnq4pxd * alqkjudhu3 ; for (
i_p = 0 ; i_p < 2 ; i_p ++ ) { btosikvjyf [ i_p ] += ( ( _rtP -> P_515 [ i_p
+ 2 ] * 0.0F + _rtP -> P_515 [ i_p ] * 0.0F ) + _rtP -> P_515 [ i_p + 4 ] *
_rtB -> bb2txpcrdw ) + _rtP -> P_515 [ i_p + 6 ] * _rtB -> czspnnf2wz ; }
gwzyst3ou3_p = _rtP -> P_516 [ 0 ] * btosikvjyf [ 0 ] + _rtP -> P_516 [ 1 ] *
btosikvjyf [ 1 ] ; s60_iter = 1 ; meppapiqj0 = ( finyivsrdi != 0.0F ) ; while
( meppapiqj0 && ( s60_iter <= 5 ) ) { for ( i = 0 ; i < 9 ; i ++ ) {
frrr5abd2i [ i ] = _rtP -> P_225 [ i ] ; fbk03eccj1 [ i ] = _rtP -> P_226 [ i
] ; phcrozezwb [ i ] = _rtP -> P_227 [ i ] ; } jmuta2homi = _rtP -> P_228 ;
cbpfnq4pxd = _rtP -> P_229 ; alqkjudhu3 = _rtP -> P_230 ; finyivsrdi = _rtP
-> P_231 ; e0r0t533ao = _rtP -> P_232 * e4orw3vqsn ; jsgk2hka41_idx_1 = _rtP
-> P_233 * _rtB -> agikm532fv ; if ( _rtB -> ldjrvtlkq4 > _rtP -> P_234 ) {
km03xn13id = _rtP -> P_234 ; } else if ( _rtB -> ldjrvtlkq4 < _rtP -> P_235 )
{ km03xn13id = _rtP -> P_235 ; } else { km03xn13id = _rtB -> ldjrvtlkq4 ; }
plknkmyedj = _rtP -> P_236 ; pyabwb0ags = _rtP -> P_237 * e0r0t533ao ; if (
pyabwb0ags > _rtP -> P_238 ) { pyabwb0ags = _rtP -> P_238 ; } else { if (
pyabwb0ags < _rtP -> P_239 ) { pyabwb0ags = _rtP -> P_239 ; } } a1jrsglzzi =
_rtP -> P_240 * gwzyst3ou3_p ; ssReadFromDataStoreWithPath ( S , _rtDW ->
drfkeqzjbb ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/While_Iterator_Subsystem/newton/update/Data Store Read11"
, NULL ) ; _rtB -> crbbi2ic45 = _rtP -> P_241 * _rtDW -> ayjpjfupkc ;
fvhzusu422 = _rtP -> P_242 * _rtB -> ldjrvtlkq4 ; if ( a1jrsglzzi > _rtP ->
P_243 ) { fzccphw1bz = _rtP -> P_243 ; } else if ( a1jrsglzzi < _rtP -> P_244
) { fzccphw1bz = _rtP -> P_244 ; } else { fzccphw1bz = a1jrsglzzi ; } if (
_rtDW -> dvtr5mddec != 0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW ->
ehd3s5jupn = _rtP -> P_188 ; } _rtDW -> dvtr5mddec = 1U ; for ( ffd3q0dmho =
1 ; ffd3q0dmho <= _rtP -> P_803 ; ffd3q0dmho ++ ) { if ( ffd3q0dmho > _rtP ->
P_804 ) { i = _rtP -> P_804 ; } else if ( ffd3q0dmho < _rtP -> P_805 ) { i =
_rtP -> P_805 ; } else { i = ffd3q0dmho ; } i -- ; c2fdcpgrsp = e0r0t533ao -
phcrozezwb [ i ] ; ehyje10v1p = c2fdcpgrsp * c2fdcpgrsp ; c2fdcpgrsp =
jsgk2hka41_idx_1 - fbk03eccj1 [ i ] ; a3jnflwpkj = ( ( 0.0F - ehyje10v1p ) -
c2fdcpgrsp * c2fdcpgrsp ) / ( cbpfnq4pxd * cbpfnq4pxd * _rtP -> P_185 ) ;
KD_cl_harness_forthao_breach_acc_LookUp_real32_T_real32_T ( & ( ckkx05hfhz )
, _rtP -> P_187 , a3jnflwpkj , _rtP -> P_186 , 102U ) ; _rtB -> eprfrytaac =
ckkx05hfhz * frrr5abd2i [ i ] + _rtDW -> ehd3s5jupn ; _rtDW -> ehd3s5jupn =
_rtB -> eprfrytaac ; } if ( alqkjudhu3 > _rtP -> P_247 ) { alqkjudhu3 = _rtP
-> P_247 ; } else { if ( alqkjudhu3 < _rtP -> P_248 ) { alqkjudhu3 = _rtP ->
P_248 ; } } if ( ic3wqfpram_idx_0 > _rtP -> P_245 ) { dpajlxfdyx_idx_0 = _rtP
-> P_245 ; } else if ( ic3wqfpram_idx_0 < _rtP -> P_246 ) { dpajlxfdyx_idx_0
= _rtP -> P_246 ; } else { dpajlxfdyx_idx_0 = ic3wqfpram_idx_0 ; } finyivsrdi
= finyivsrdi / dpajlxfdyx_idx_0 / alqkjudhu3 / alqkjudhu3 ; if ( finyivsrdi >
_rtP -> P_249 ) { finyivsrdi = _rtP -> P_249 ; } else { if ( finyivsrdi <
_rtP -> P_250 ) { finyivsrdi = _rtP -> P_250 ; } } alqkjudhu3 =
muSingleScalarSqrt ( finyivsrdi ) ; rtPrevAction = _rtDW -> awpbtqxcnq ;
rtAction = ( int8_T ) ! ( fvhzusu422 / fzccphw1bz <= 0.4167F ) ; _rtDW ->
awpbtqxcnq = rtAction ; if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
ssSetSolverNeedsReset ( S ) ; break ; } } switch ( rtAction ) { case 0 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } u0 = ( _rtP -> P_191 + jmuta2homi ) *
_rtP -> P_192 ; if ( u0 > _rtP -> P_193 ) { u0 = _rtP -> P_193 ; } else { if
( u0 < _rtP -> P_194 ) { u0 = _rtP -> P_194 ; } } u0 = jmuta2homi / u0 ; if (
u0 > _rtP -> P_195 ) { u0 = _rtP -> P_195 ; } else { if ( u0 < _rtP -> P_196
) { u0 = _rtP -> P_196 ; } } _rtB -> bihzjyslyy [ 0 ] = _rtB -> eprfrytaac *
alqkjudhu3 * muSingleScalarSqrt ( u0 ) ; u0 = ( _rtP -> P_189 + jmuta2homi )
* _rtP -> P_190 ; if ( u0 > _rtP -> P_197 ) { u0 = _rtP -> P_197 ; } else {
if ( u0 < _rtP -> P_198 ) { u0 = _rtP -> P_198 ; } } u0 = jmuta2homi / u0 ;
if ( u0 > _rtP -> P_199 ) { u0 = _rtP -> P_199 ; } else { if ( u0 < _rtP ->
P_200 ) { u0 = _rtP -> P_200 ; } } _rtB -> bihzjyslyy [ 1 ] = _rtB ->
eprfrytaac * alqkjudhu3 * muSingleScalarSqrt ( u0 ) * a1jrsglzzi ; _rtDW ->
l4mofmlly2 = 4 ; break ; case 1 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } if ( a1jrsglzzi > _rtP -> P_205 ) { dpajlxfdyx_idx_0 = _rtP -> P_205 ;
} else if ( a1jrsglzzi < _rtP -> P_206 ) { dpajlxfdyx_idx_0 = _rtP -> P_206 ;
} else { dpajlxfdyx_idx_0 = a1jrsglzzi ; } cbpfnq4pxd = fvhzusu422 /
dpajlxfdyx_idx_0 ; if ( jmuta2homi > _rtP -> P_208 ) { dpajlxfdyx_idx_0 =
_rtP -> P_208 ; } else if ( jmuta2homi < _rtP -> P_209 ) { dpajlxfdyx_idx_0 =
_rtP -> P_209 ; } else { dpajlxfdyx_idx_0 = jmuta2homi ; } u0 = ( (
jmuta2homi - _rtP -> P_203 ) * ( _rtP -> P_204 - cbpfnq4pxd ) / _rtP -> P_207
/ dpajlxfdyx_idx_0 + cbpfnq4pxd ) * ( _rtP -> P_210 - cbpfnq4pxd ) ; if ( u0
> _rtP -> P_211 ) { u0 = _rtP -> P_211 ; } else { if ( u0 < _rtP -> P_212 ) {
u0 = _rtP -> P_212 ; } } _rtB -> bihzjyslyy [ 1 ] = a1jrsglzzi * _rtB ->
eprfrytaac * alqkjudhu3 * muSingleScalarSqrt ( u0 ) ; u0 = ( ( jmuta2homi +
_rtP -> P_213 ) * fvhzusu422 + ( jmuta2homi - _rtP -> P_214 ) * a1jrsglzzi )
* ( _rtP -> P_201 * jmuta2homi * ( a1jrsglzzi - fvhzusu422 ) ) ; if ( u0 >
_rtP -> P_215 ) { u0 = _rtP -> P_215 ; } else { if ( u0 < _rtP -> P_216 ) {
u0 = _rtP -> P_216 ; } } u0 = muSingleScalarSqrt ( u0 ) ; if ( u0 > _rtP ->
P_217 ) { u0 = _rtP -> P_217 ; } else { if ( u0 < _rtP -> P_218 ) { u0 = _rtP
-> P_218 ; } } _rtB -> bihzjyslyy [ 0 ] = ( ( jmuta2homi - _rtP -> P_202 ) *
a1jrsglzzi + fvhzusu422 ) / u0 * ( _rtB -> eprfrytaac * alqkjudhu3 ) ; _rtDW
-> kltb44md1r = 4 ; break ; } cbpfnq4pxd = ic3wqfpram_idx_1 - _rtB ->
bihzjyslyy [ 1 ] ; ssReadFromDataStoreWithPath ( S , _rtDW -> ko2ysb3l22 ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/While_Iterator_Subsystem/newton/update/Data Store Read16"
, NULL ) ; _rtB -> mzt0y0nfo5 = _rtP -> P_251 * _rtDW -> nqvcv4lcej ;
meppapiqj0 = ( _rtB -> mzt0y0nfo5 > _rtP -> P_252 ) ;
ssReadFromDataStoreWithPath ( S , _rtDW -> drfkeqzjbb ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/While_Iterator_Subsystem/newton/update/Data Store Read1"
, NULL ) ; _rtB -> iwz44y4cr5 = _rtP -> P_253 * _rtDW -> ayjpjfupkc ; if (
meppapiqj0 ) { u0 = _rtB -> bihzjyslyy [ 0 ] * _rtB -> bihzjyslyy [ 0 ] +
_rtB -> crbbi2ic45 ; if ( u0 > _rtP -> P_223 ) { u0 = _rtP -> P_223 ; } else
{ if ( u0 < _rtP -> P_224 ) { u0 = _rtP -> P_224 ; } } cbpfnq4pxd *= 1.0F /
u0 * _rtB -> bihzjyslyy [ 0 ] ; } else { u0 = _rtB -> iwz44y4cr5 + _rtB ->
bihzjyslyy [ 0 ] ; if ( u0 > _rtP -> P_221 ) { u0 = _rtP -> P_221 ; } else {
if ( u0 < _rtP -> P_222 ) { u0 = _rtP -> P_222 ; } } cbpfnq4pxd *= 1.0F / u0
; } alqkjudhu3 = ( a1jrsglzzi + cbpfnq4pxd ) * _rtP -> P_254 ; rtPrevAction =
_rtDW -> g0pejldppu ; rtAction = ( int8_T ) ! ( pyabwb0ags < 15.0F ) ; _rtDW
-> g0pejldppu = rtAction ; if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
ssSetSolverNeedsReset ( S ) ; break ; } } switch ( rtAction ) { case 0 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } cbpfnq4pxd = pyabwb0ags / _rtP ->
P_219 ; _rtB -> hrv5myfmi5 = ( _rtP -> P_220 - cbpfnq4pxd ) * batdnpsvim +
alqkjudhu3 * cbpfnq4pxd ; _rtDW -> oqqlpwtggt = 4 ; break ; case 1 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> hrv5myfmi5 = alqkjudhu3 ;
_rtDW -> hgwa21u3tp = 4 ; break ; } cbpfnq4pxd = _rtP -> P_255 + km03xn13id ;
if ( _rtB -> hrv5myfmi5 < cbpfnq4pxd ) { awl0z0b3sb = cbpfnq4pxd ; } else {
awl0z0b3sb = _rtB -> hrv5myfmi5 ; } if ( _rtB -> hrv5myfmi5 > plknkmyedj ) {
_rtB -> lbwa3jpkws = plknkmyedj ; } else { _rtB -> lbwa3jpkws = awl0z0b3sb ;
} meppapiqj0 = _rtP -> P_833 ; srUpdateBC ( _rtDW -> ljedkvx4od ) ; s60_iter
++ ; } ssReadFromDataStoreWithPath ( S , _rtDW -> i0oacsu105 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read13"
, NULL ) ; _rtB -> hiqxaf3x1i = _rtP -> P_517 * _rtDW -> pmewcnpxdb ; if (
_rtB -> hiqxaf3x1i > _rtP -> P_518 ) { jjkfbyaomr = _rtB -> lbwa3jpkws ; }
else { jjkfbyaomr = batdnpsvim ; } kaqx4nados = _rtP -> P_519 * jjkfbyaomr ;
jfmtdksnh0 = _rtP -> P_522 ; if ( ic3wqfpram_idx_0 > _rtP -> P_520 ) {
dpajlxfdyx_idx_0 = _rtP -> P_520 ; } else if ( ic3wqfpram_idx_0 < _rtP ->
P_521 ) { dpajlxfdyx_idx_0 = _rtP -> P_521 ; } else { dpajlxfdyx_idx_0 =
ic3wqfpram_idx_0 ; } jfmtdksnh0 = kaqx4nados / dpajlxfdyx_idx_0 / jfmtdksnh0
* kaqx4nados * _rtP -> P_523 ; jfmtdksnh0 = muSingleScalarAbs ( jfmtdksnh0 )
; jfmtdksnh0 = muSingleScalarSqrt ( jfmtdksnh0 ) ; if ( kaqx4nados > _rtP ->
P_527 ) { kaqx4nados = _rtP -> P_527 ; } else { if ( kaqx4nados < _rtP ->
P_528 ) { kaqx4nados = _rtP -> P_528 ; } } cbpfnq4pxd = _rtP -> P_526 * _rtB
-> ldjrvtlkq4 / kaqx4nados ; if ( cbpfnq4pxd > _rtP -> P_529 ) { if (
cbpfnq4pxd > _rtP -> P_164 ) { cbpfnq4pxd = _rtP -> P_164 ; } else { if (
cbpfnq4pxd < _rtP -> P_165 ) { cbpfnq4pxd = _rtP -> P_165 ; } } alqkjudhu3 =
_rtP -> P_166 - cbpfnq4pxd ; alqkjudhu3 *= alqkjudhu3 * _rtP -> P_163 +
cbpfnq4pxd ; if ( alqkjudhu3 > _rtP -> P_167 ) { alqkjudhu3 = _rtP -> P_167 ;
} else { if ( alqkjudhu3 < _rtP -> P_168 ) { alqkjudhu3 = _rtP -> P_168 ; } }
kaqx4nados = muSingleScalarSqrt ( alqkjudhu3 ) ; } else { kaqx4nados = _rtP
-> P_162 ; } kaqx4nados = jfmtdksnh0 * rt_Lookup32 ( _rtP -> P_524 , 16 ,
_rtB -> agikm532fv , _rtP -> P_525 ) * kaqx4nados * _rtP -> P_530 ; if (
kaqx4nados > _rtP -> P_531 ) { kaqx4nados = _rtP -> P_531 ; } else { if (
kaqx4nados < _rtP -> P_532 ) { kaqx4nados = _rtP -> P_532 ; } }
ssReadFromDataStoreWithPath ( S , _rtDW -> angozbvvee ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read4"
, NULL ) ; jfmtdksnh0 = _rtDW -> hptuorf3i3 ; _rtB -> g50cgr2ero = _rtP ->
P_533 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_534 * _rtB -> g50cgr2ero ; if (
jfmtdksnh0 > _rtP -> P_535 ) { jfmtdksnh0 = _rtP -> P_535 ; } else { if (
jfmtdksnh0 < _rtP -> P_536 ) { jfmtdksnh0 = _rtP -> P_536 ; } } jfmtdksnh0 =
_rtB -> mt0t1wog2n * jfmtdksnh0 / ( _rtP -> P_537 - jfmtdksnh0 ) * _rtP ->
P_538 ; fij5klqz0n = muSingleScalarMin ( kaqx4nados , jfmtdksnh0 ) ; _rtB ->
hvx1cvumuq = _rtP -> P_539 * fij5klqz0n * _rtP -> P_540 ; _rtDW -> bvlm5joqvj
= _rtB -> hvx1cvumuq ; ssWriteToDataStoreWithPath ( S , _rtDW -> o3fzpatiqj ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write13"
, NULL ) ; memcpy ( & dift4gyrha [ 0 ] , & _rtP -> P_541 [ 0 ] , 309U *
sizeof ( real32_T ) ) ; memcpy ( & hsiahk1nnd [ 0 ] , & _rtP -> P_542 [ 0 ] ,
103U * sizeof ( real32_T ) ) ;
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
cl24d41ibh ) , _rtP -> P_545 , _rtB -> agikm532fv , _rtP -> P_543 , 19U ,
_rtB -> auohfil2jj , _rtP -> P_544 , 19U ) ; ssReadFromDataStoreWithPath ( S
, _rtDW -> lbc21h24p2 ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/set_point_maps/Data Store Read3"
, NULL ) ; _rtB -> hcepujpuwf = _rtP -> P_546 * _rtDW -> enudnf03vn ;
g1ekzbu3oi = cl24d41ibh + _rtB -> hcepujpuwf ; hn15keiut1 = exrgmvycyf_idx_1
- g1ekzbu3oi ;
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
e51a0t11ia ) , _rtP -> P_549 , _rtB -> agikm532fv , _rtP -> P_547 , 19U ,
_rtB -> auohfil2jj , _rtP -> P_548 , 19U ) ; cbpfnq4pxd = _rtP -> P_550 *
e51a0t11ia ; ssReadFromDataStoreWithPath ( S , _rtDW -> iibzcraycn ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/set_point_maps/Data Store Read1"
, NULL ) ; _rtB -> ardfej0rww = _rtP -> P_551 * _rtDW -> bakpq4fzl0 ;
fwhtla1rft = cbpfnq4pxd + _rtB -> ardfej0rww ; if ( fwhtla1rft > _rtP ->
P_552 ) { fwhtla1rft = _rtP -> P_552 ; } else { if ( fwhtla1rft < _rtP ->
P_553 ) { fwhtla1rft = _rtP -> P_553 ; } } byk21oesq1 = exrgmvycyf_idx_2 -
fwhtla1rft ; kaqx4nados = _rtB -> mt0t1wog2n / _rtP -> P_554 ; jfmtdksnh0 =
_rtP -> P_555 ; fzccphw1bz = _rtP -> P_556 * _rtB -> ldjrvtlkq4 ; ehyje10v1p
= _rtP -> P_557 ; if ( _rtP -> P_559 > _rtP -> P_560 ) { dpajlxfdyx_idx_0 =
_rtP -> P_560 ; } else if ( _rtP -> P_559 < _rtP -> P_561 ) {
dpajlxfdyx_idx_0 = _rtP -> P_561 ; } else { dpajlxfdyx_idx_0 = _rtP -> P_559
; } if ( _rtP -> P_563 > _rtP -> P_564 ) { jsgk2hka41_idx_0 = _rtP -> P_564 ;
} else if ( _rtP -> P_563 < _rtP -> P_565 ) { jsgk2hka41_idx_0 = _rtP ->
P_565 ; } else { jsgk2hka41_idx_0 = _rtP -> P_563 ; } _rtB -> iqg1nj4hwf = (
_rtP -> P_562 - jsgk2hka41_idx_0 ) * kaqx4nados + _rtDW -> frjwyakiph *
dpajlxfdyx_idx_0 ; cbpfnq4pxd = _rtP -> P_566 * _rtB -> iqg1nj4hwf ;
ssReadFromDataStoreWithPath ( S , _rtDW -> dxbshoizcp ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read12"
, NULL ) ; _rtB -> fkwa0nrbz3 = _rtP -> P_567 * _rtDW -> d210tl5n23 ;
meppapiqj0 = ( _rtB -> fkwa0nrbz3 > _rtP -> P_568 ) ;
ssReadFromDataStoreWithPath ( S , _rtDW -> cutqc2g2te ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read2"
, NULL ) ; _rtB -> gkcuuaqdia = _rtP -> P_569 * _rtDW -> nwf1nud1fv ; if (
meppapiqj0 ) {
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
dbt3uojgmq ) , _rtP -> P_159 , _rtB -> agikm532fv , _rtP -> P_157 , 19U ,
_rtB -> auohfil2jj , _rtP -> P_158 , 19U ) ; not4fp11wk = dbt3uojgmq ; } else
{ not4fp11wk = _rtB -> gkcuuaqdia ; } alqkjudhu3 = _rtP -> P_570 * not4fp11wk
; finyivsrdi = _rtP -> P_571 * _rtB -> agikm532fv ; e0r0t533ao = _rtP ->
P_574 ; for ( i = 0 ; i < 9 ; i ++ ) { frrr5abd2i [ i ] = _rtP -> P_572 [ i ]
; fbk03eccj1 [ i ] = _rtP -> P_573 [ i ] ; phcrozezwb [ i ] = _rtP -> P_575 [
i ] ; } ssSetSolverNeedsReset ( S ) ; _rtDW -> owlkbndpg5 = _rtP -> P_298 ;
for ( s60_iter = 1 ; s60_iter <= _rtP -> P_813 ; s60_iter ++ ) { if (
s60_iter > _rtP -> P_814 ) { i = _rtP -> P_814 ; } else if ( s60_iter < _rtP
-> P_815 ) { i = _rtP -> P_815 ; } else { i = s60_iter ; } ffd3q0dmho = i - 1
; jsgk2hka41_idx_1 = alqkjudhu3 - frrr5abd2i [ ffd3q0dmho ] ; c2fdcpgrsp =
jsgk2hka41_idx_1 * jsgk2hka41_idx_1 ; jsgk2hka41_idx_1 = finyivsrdi -
fbk03eccj1 [ ffd3q0dmho ] ; iou1bb3prl = ( ( 0.0F - c2fdcpgrsp ) -
jsgk2hka41_idx_1 * jsgk2hka41_idx_1 ) / ( e0r0t533ao * e0r0t533ao * _rtP ->
P_295 ) ; KD_cl_harness_forthao_breach_acc_LookUp_real32_T_real32_T ( & (
omfw35sfyk ) , _rtP -> P_297 , iou1bb3prl , _rtP -> P_296 , 102U ) ; _rtB ->
o5df4vinc5 = omfw35sfyk * phcrozezwb [ ffd3q0dmho ] + _rtDW -> owlkbndpg5 ;
_rtDW -> owlkbndpg5 = _rtB -> o5df4vinc5 ; } if ( _rtP -> P_579 > _rtP ->
P_580 ) { dpajlxfdyx_idx_0 = _rtP -> P_580 ; } else if ( _rtP -> P_579 < _rtP
-> P_581 ) { dpajlxfdyx_idx_0 = _rtP -> P_581 ; } else { dpajlxfdyx_idx_0 =
_rtP -> P_579 ; } if ( _rtP -> P_582 > _rtP -> P_583 ) { jsgk2hka41_idx_0 =
_rtP -> P_583 ; } else if ( _rtP -> P_582 < _rtP -> P_584 ) {
jsgk2hka41_idx_0 = _rtP -> P_584 ; } else { jsgk2hka41_idx_0 = _rtP -> P_582
; } u0 = _rtP -> P_578 / dpajlxfdyx_idx_0 / jsgk2hka41_idx_0 * _rtP -> P_585
; if ( u0 > _rtP -> P_586 ) { u0 = _rtP -> P_586 ; } else { if ( u0 < _rtP ->
P_587 ) { u0 = _rtP -> P_587 ; } } u0 = muSingleScalarSqrt ( u0 ) ; if ( _rtB
-> o5df4vinc5 > _rtP -> P_576 ) { dpajlxfdyx_idx_0 = _rtP -> P_576 ; } else
if ( _rtB -> o5df4vinc5 < _rtP -> P_577 ) { dpajlxfdyx_idx_0 = _rtP -> P_577
; } else { dpajlxfdyx_idx_0 = _rtB -> o5df4vinc5 ; } if ( u0 > _rtP -> P_588
) { u0 = _rtP -> P_588 ; } else { if ( u0 < _rtP -> P_589 ) { u0 = _rtP ->
P_589 ; } } o3mfdsmmfb = cbpfnq4pxd / dpajlxfdyx_idx_0 / u0 ; cbpfnq4pxd =
o3mfdsmmfb * o3mfdsmmfb ; if ( o3mfdsmmfb > _rtP -> P_592 ) { o3mfdsmmfb =
_rtP -> P_592 ; } else { if ( o3mfdsmmfb < _rtP -> P_593 ) { o3mfdsmmfb =
_rtP -> P_593 ; } } if ( fzccphw1bz / o3mfdsmmfb > _rtP -> P_594 ) {
alqkjudhu3 = fzccphw1bz * fzccphw1bz ; cbpfnq4pxd = ( ( _rtP -> P_291 *
alqkjudhu3 - alqkjudhu3 ) - cbpfnq4pxd ) * ehyje10v1p * _rtP -> P_590 ;
alqkjudhu3 = fzccphw1bz - _rtP -> P_292 * fzccphw1bz ; u0 = alqkjudhu3 *
alqkjudhu3 - cbpfnq4pxd ; if ( u0 > _rtP -> P_293 ) { u0 = _rtP -> P_293 ; }
else { if ( u0 < _rtP -> P_294 ) { u0 = _rtP -> P_294 ; } } if ( _rtP ->
P_590 > _rtP -> P_289 ) { dpajlxfdyx_idx_0 = _rtP -> P_289 ; } else if ( _rtP
-> P_590 < _rtP -> P_290 ) { dpajlxfdyx_idx_0 = _rtP -> P_290 ; } else {
dpajlxfdyx_idx_0 = _rtP -> P_590 ; } if ( _rtP -> P_591 > _rtP -> P_287 ) {
jsgk2hka41_idx_0 = _rtP -> P_287 ; } else if ( _rtP -> P_591 < _rtP -> P_288
) { jsgk2hka41_idx_0 = _rtP -> P_288 ; } else { jsgk2hka41_idx_0 = _rtP ->
P_591 ; } o3mfdsmmfb = ( muSingleScalarSqrt ( u0 ) - alqkjudhu3 ) /
dpajlxfdyx_idx_0 / jsgk2hka41_idx_0 ; } else { o3mfdsmmfb = cbpfnq4pxd ; }
o3mfdsmmfb *= _rtP -> P_595 ; kaqx4nados = rt_Lookup2D32_Normal ( _rtP ->
P_596 , 20 , _rtP -> P_597 , 16 , _rtP -> P_598 , kaqx4nados , 1.0F /
jfmtdksnh0 * o3mfdsmmfb ) * _rtP -> P_599 ; o3cuzyoqg5 = _rtP -> P_600 *
kaqx4nados ; jfmtdksnh0 = _rtP -> P_601 ; cbpfnq4pxd = jfmtdksnh0 -
pn0idallhu_idx_0 ; ssReadFromDataStoreWithPath ( S , _rtDW -> elilh0acjp ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read" ,
NULL ) ; jfmtdksnh0 = _rtDW -> ntmupcyyck ; _rtB -> hasrpixfyh = _rtP ->
P_602 * jfmtdksnh0 ; if ( _rtB -> hasrpixfyh > _rtP -> P_603 ) { pwkaxiafxx =
_rtP -> P_603 ; } else if ( _rtB -> hasrpixfyh < _rtP -> P_604 ) { pwkaxiafxx
= _rtP -> P_604 ; } else { pwkaxiafxx = _rtB -> hasrpixfyh ; } km03xn13id =
cbpfnq4pxd / pwkaxiafxx ; jfmtdksnh0 = _rtP -> P_605 ; plknkmyedj = (
jfmtdksnh0 - pn0idallhu_idx_0 ) * _rtP -> P_606 * ( 1.0F / pwkaxiafxx ) ;
cbpfnq4pxd = _rtP -> P_607 * fij5klqz0n ; ssReadFromDataStoreWithPath ( S ,
_rtDW -> f00eda2bjz ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read1"
, NULL ) ; jfmtdksnh0 = _rtDW -> devn1wdclr ; _rtB -> kzf3qrbzkj = _rtP ->
P_608 * jfmtdksnh0 ; if ( _rtB -> kzf3qrbzkj > _rtP -> P_609 ) { gwzyst3ou3_p
= _rtP -> P_609 ; } else if ( _rtB -> kzf3qrbzkj < _rtP -> P_610 ) {
gwzyst3ou3_p = _rtP -> P_610 ; } else { gwzyst3ou3_p = _rtB -> kzf3qrbzkj ; }
jmuta2homi = ( cbpfnq4pxd - pn0idallhu_idx_1 ) / gwzyst3ou3_p ; fvhzusu422 =
_rtP -> P_611 ; ehyje10v1p = ( _rtP -> P_611 - pn0idallhu_idx_1 ) * _rtP ->
P_612 * ( 1.0F / gwzyst3ou3_p ) ; ssReadFromDataStoreWithPath ( S , _rtDW ->
fnxjjp2lme ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read3"
, NULL ) ; jfmtdksnh0 = _rtDW -> o3z1jsmhkx ; _rtB -> p4ek3tnerm = _rtP ->
P_613 * jfmtdksnh0 ; a1jrsglzzi = _rtB -> p4ek3tnerm - g1ekzbu3oi ;
jfmtdksnh0 = _rtP -> P_614 ; fzccphw1bz = jfmtdksnh0 - fwhtla1rft ;
ssReadFromDataStoreWithPath ( S , _rtDW -> mzsuxn1hbm ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read17"
, NULL ) ; jfmtdksnh0 = _rtDW -> mi05525rde ; _rtB -> cqertkbhh1 = _rtP ->
P_615 * jfmtdksnh0 ; ssReadFromDataStoreWithPath ( S , _rtDW -> a02t5mvtkd ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read18"
, NULL ) ; jfmtdksnh0 = _rtDW -> fuwbxjmtyy ; _rtB -> lqin2qgn0v = _rtP ->
P_616 * jfmtdksnh0 ; pyabwb0ags = _rtP -> P_617 * _rtB -> lqin2qgn0v ;
s60_iter = 1 ; meppapiqj0 = ( _rtP -> P_816 != 0 ) ; while ( meppapiqj0 && (
s60_iter <= 103 ) ) { esndn1d5qn = s60_iter ; alqkjudhu3 = _rtP -> P_260 ;
memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_261 [ 0 ] , 1030U * sizeof
( real32_T ) ) ; if ( esndn1d5qn > _rtP -> P_809 ) { i = _rtP -> P_809 ; }
else if ( esndn1d5qn < _rtP -> P_810 ) { i = _rtP -> P_810 ; } else { i =
esndn1d5qn ; } if ( _rtP -> P_262 [ i - 1 ] > _rtP -> P_263 ) { cbpfnq4pxd =
_rtP -> P_263 ; } else if ( _rtP -> P_262 [ i - 1 ] < _rtP -> P_264 ) {
cbpfnq4pxd = _rtP -> P_264 ; } else { cbpfnq4pxd = _rtP -> P_262 [ i - 1 ] ;
} i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) {
cfpabnsfkw [ i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] *
exrgmvycyf_idx_0 ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_265 [
0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p
= 0 ; i_p < 10 ; i_p ++ ) { dqg1fl5gyp [ i_p ] = _rtB -> l2buyyse4x [ ( i_p +
i ) - 1 ] * hn15keiut1 ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP ->
P_266 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ;
for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { n4vetwv3qv [ i_p ] = _rtB -> l2buyyse4x
[ ( i_p + i ) - 1 ] * byk21oesq1 ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , &
_rtP -> P_267 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T )
cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { np1ecrs5jr [ i_p ] = _rtB
-> l2buyyse4x [ ( i_p + i ) - 1 ] * jjkfbyaomr ; } memcpy ( & _rtB ->
l2buyyse4x [ 0 ] , & _rtP -> P_268 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i
= ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { klzvh1ekin [
i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] * o3cuzyoqg5 ; } memcpy ( &
_rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_269 [ 0 ] , 1030U * sizeof ( real32_T
) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) {
ebqfsagx32 [ i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] * km03xn13id ; }
memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_270 [ 0 ] , 1030U * sizeof
( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p
++ ) { cxofaf120r [ i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] *
plknkmyedj ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_271 [ 0 ] ,
1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ;
i_p < 10 ; i_p ++ ) { bfa5h0zq23 [ i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) -
1 ] * jmuta2homi ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_272 [
0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p
= 0 ; i_p < 10 ; i_p ++ ) { fa4aelt32d [ i_p ] = _rtB -> l2buyyse4x [ ( i_p +
i ) - 1 ] * ehyje10v1p ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP ->
P_273 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ;
for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { p22ala5lq4 [ i_p ] = _rtB -> l2buyyse4x
[ ( i_p + i ) - 1 ] * a1jrsglzzi ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , &
_rtP -> P_274 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i = ( int32_T )
cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { galtyeac1e [ i_p ] = _rtB
-> l2buyyse4x [ ( i_p + i ) - 1 ] * fzccphw1bz ; } memcpy ( & _rtB ->
l2buyyse4x [ 0 ] , & _rtP -> P_275 [ 0 ] , 1030U * sizeof ( real32_T ) ) ; i
= ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p ++ ) { hgfxoibhl0 [
i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] * _rtB -> cqertkbhh1 ; }
memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_276 [ 0 ] , 1030U * sizeof
( real32_T ) ) ; i = ( int32_T ) cbpfnq4pxd ; for ( i_p = 0 ; i_p < 10 ; i_p
++ ) { iqq1rbnkkz [ i_p ] = _rtB -> l2buyyse4x [ ( i_p + i ) - 1 ] *
pyabwb0ags ; } memcpy ( & _rtB -> l2buyyse4x [ 0 ] , & _rtP -> P_277 [ 0 ] ,
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
= j5z4rdmkwv ; _rtB -> mgx4ixsnsf = _rtP -> P_807 ; _rtDW -> gdpkwnqxlj = 4 ;
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
-> mgx4ixsnsf > _rtP -> P_817 ) { i_p = _rtP -> P_817 ; } else if ( _rtB ->
mgx4ixsnsf < _rtP -> P_818 ) { i_p = _rtP -> P_818 ; } else { i_p = _rtB ->
mgx4ixsnsf ; } jfmtdksnh0 = hsiahk1nnd [ i_p - 1 ] ; if ( jfmtdksnh0 > _rtP
-> P_618 ) { jfmtdksnh0 = _rtP -> P_618 ; } else { if ( jfmtdksnh0 < _rtP ->
P_619 ) { jfmtdksnh0 = _rtP -> P_619 ; } } i_p = ( int32_T ) jfmtdksnh0 ; i =
( int32_T ) jfmtdksnh0 ; ffd3q0dmho = ( int32_T ) jfmtdksnh0 ; s60_iter = (
int32_T ) jfmtdksnh0 ; tmp_p = ( int32_T ) jfmtdksnh0 ; tmp_e = ( int32_T )
jfmtdksnh0 ; tmp_i = ( int32_T ) jfmtdksnh0 ; tmp_m = ( int32_T ) jfmtdksnh0
; tmp_g = ( int32_T ) jfmtdksnh0 ; tmp_j = ( int32_T ) jfmtdksnh0 ; tmp_f = (
int32_T ) jfmtdksnh0 ; tmp_c = ( int32_T ) jfmtdksnh0 ; tmp_k = ( int32_T )
jfmtdksnh0 ; tmp_b = ( int32_T ) jfmtdksnh0 ; _rtB -> j5nsr3o4kc [ 0 ] = ( (
( ( ( ( ( ( ( ( ( ( dift4gyrha [ i_p - 1 ] * exrgmvycyf_idx_0 + _rtP -> P_620
[ i - 1 ] * hn15keiut1 ) + _rtP -> P_621 [ ffd3q0dmho - 1 ] * byk21oesq1 ) +
_rtP -> P_622 [ s60_iter - 1 ] * jjkfbyaomr ) + _rtP -> P_623 [ tmp_p - 1 ] *
o3cuzyoqg5 ) + _rtP -> P_624 [ tmp_e - 1 ] * km03xn13id ) + _rtP -> P_625 [
tmp_i - 1 ] * plknkmyedj ) + _rtP -> P_626 [ tmp_m - 1 ] * jmuta2homi ) +
_rtP -> P_627 [ tmp_g - 1 ] * ehyje10v1p ) + _rtP -> P_628 [ tmp_j - 1 ] *
a1jrsglzzi ) + _rtP -> P_629 [ tmp_f - 1 ] * fzccphw1bz ) + _rtP -> P_630 [
tmp_c - 1 ] * _rtB -> cqertkbhh1 ) + _rtP -> P_631 [ tmp_k - 1 ] * pyabwb0ags
) + _rtP -> P_632 [ tmp_b - 1 ] ; _rtB -> j5nsr3o4kc [ 1 ] = ( ( ( ( ( ( ( (
( ( ( ( dift4gyrha [ i_p ] * exrgmvycyf_idx_0 + _rtP -> P_620 [ i ] *
hn15keiut1 ) + _rtP -> P_621 [ ffd3q0dmho ] * byk21oesq1 ) + _rtP -> P_622 [
s60_iter ] * jjkfbyaomr ) + _rtP -> P_623 [ tmp_p ] * o3cuzyoqg5 ) + _rtP ->
P_624 [ tmp_e ] * km03xn13id ) + _rtP -> P_625 [ tmp_i ] * plknkmyedj ) +
_rtP -> P_626 [ tmp_m ] * jmuta2homi ) + _rtP -> P_627 [ tmp_g ] * ehyje10v1p
) + _rtP -> P_628 [ tmp_j ] * a1jrsglzzi ) + _rtP -> P_629 [ tmp_f ] *
fzccphw1bz ) + _rtP -> P_630 [ tmp_c ] * _rtB -> cqertkbhh1 ) + _rtP -> P_631
[ tmp_k ] * pyabwb0ags ) + _rtP -> P_632 [ tmp_b ] ; _rtB -> j5nsr3o4kc [ 2 ]
= ( ( ( ( ( ( ( ( ( ( ( ( dift4gyrha [ i_p + 1 ] * exrgmvycyf_idx_0 + _rtP ->
P_620 [ i + 1 ] * hn15keiut1 ) + _rtP -> P_621 [ ffd3q0dmho + 1 ] *
byk21oesq1 ) + _rtP -> P_622 [ s60_iter + 1 ] * jjkfbyaomr ) + _rtP -> P_623
[ tmp_p + 1 ] * o3cuzyoqg5 ) + _rtP -> P_624 [ tmp_e + 1 ] * km03xn13id ) +
_rtP -> P_625 [ tmp_i + 1 ] * plknkmyedj ) + _rtP -> P_626 [ tmp_m + 1 ] *
jmuta2homi ) + _rtP -> P_627 [ tmp_g + 1 ] * ehyje10v1p ) + _rtP -> P_628 [
tmp_j + 1 ] * a1jrsglzzi ) + _rtP -> P_629 [ tmp_f + 1 ] * fzccphw1bz ) +
_rtP -> P_630 [ tmp_c + 1 ] * _rtB -> cqertkbhh1 ) + _rtP -> P_631 [ tmp_k +
1 ] * pyabwb0ags ) + _rtP -> P_632 [ tmp_b + 1 ] ; _rtB -> jujcicagpo = _rtP
-> P_633 * _rtB -> j5nsr3o4kc [ 0 ] ; _rtDW -> kk4xei3vwx = _rtB ->
jujcicagpo ; ssWriteToDataStoreWithPath ( S , _rtDW -> dicvjmmruq ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write14"
, NULL ) ; _rtB -> ckhs4krs4m = _rtP -> P_634 * _rtB -> j5nsr3o4kc [ 1 ] ;
_rtDW -> mjfdrfawoz = _rtB -> ckhs4krs4m ; ssWriteToDataStoreWithPath ( S ,
_rtDW -> ayvym5pshc ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write15"
, NULL ) ; _rtB -> k1tmsd4fjt = _rtP -> P_635 * _rtB -> j5nsr3o4kc [ 2 ] ;
_rtDW -> oe1xcqtj2h = _rtB -> k1tmsd4fjt ; ssWriteToDataStoreWithPath ( S ,
_rtDW -> hfec1fq11b ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write16"
, NULL ) ; _rtB -> bf4jmuwmuq = ( int32_T ) ( ( int64_T ) _rtP -> P_828 *
_rtB -> mgx4ixsnsf >> 30 ) ; _rtDW -> fnhncveveb = _rtB -> bf4jmuwmuq ;
ssWriteToDataStoreWithPath ( S , _rtDW -> e44y2okmfs ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write17"
, NULL ) ; ssReadFromDataStoreWithPath ( S , _rtDW -> mn25wyuzm2 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read5"
, NULL ) ; jfmtdksnh0 = _rtDW -> axunmck3pg ; _rtB -> eycuspwp0x = _rtP ->
P_636 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_637 * fij5klqz0n ;
ssReadFromDataStoreWithPath ( S , _rtDW -> bllhrvlbkt ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read6"
, NULL ) ; _rtB -> f1m150kkit = _rtP -> P_638 * _rtDW -> gzmuaempqp ;
j5cdf5jml5 = _rtP -> P_639 * _rtB -> f1m150kkit ; if ( j5cdf5jml5 < _rtP ->
P_640 ) { am2jzeb44a = _rtP -> P_640 ; } else { am2jzeb44a = j5cdf5jml5 ; }
if ( j5cdf5jml5 > jfmtdksnh0 ) { gnrscbmka5 = jfmtdksnh0 ; } else {
gnrscbmka5 = am2jzeb44a ; } ssReadFromDataStoreWithPath ( S , _rtDW ->
iste3vyhz4 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read7"
, NULL ) ; jfmtdksnh0 = _rtDW -> gd2xytkseo ; _rtB -> au0aj2bubh = _rtP ->
P_641 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_642 ; _rtB -> lksu3sv24v =
pwkaxiafxx * _rtB -> j5nsr3o4kc [ 0 ] ; _rtB -> lmn34nxqxt = _rtB ->
j5nsr3o4kc [ 1 ] * gwzyst3ou3_p ; if ( _rtB -> au0aj2bubh > jfmtdksnh0 ) {
_rtB -> cnnxmyxf0o [ 0 ] = _rtB -> eycuspwp0x ; _rtB -> cnnxmyxf0o [ 1 ] =
gnrscbmka5 ; } else { _rtB -> cnnxmyxf0o [ 0 ] = pn0idallhu_idx_0 + _rtB ->
lksu3sv24v ; _rtB -> cnnxmyxf0o [ 1 ] = pn0idallhu_idx_1 + _rtB -> lmn34nxqxt
; } _rtB -> pvzp3twtmn = _rtP -> P_643 * _rtB -> cnnxmyxf0o [ 0 ] ; _rtDW ->
i5n35h2hi0 = _rtB -> pvzp3twtmn ; ssWriteToDataStoreWithPath ( S , _rtDW ->
ppns2wuxkl ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write18"
, NULL ) ; c2fdcpgrsp = _rtP -> P_644 * _rtB -> cnnxmyxf0o [ 1 ] ; _rtB ->
b3n1bpqi33 = _rtP -> P_645 * c2fdcpgrsp * _rtP -> P_646 ; _rtDW -> gj1id4inx4
= _rtB -> b3n1bpqi33 ; ssWriteToDataStoreWithPath ( S , _rtDW -> da43lw3s4d ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write19"
, NULL ) ; _rtB -> m0aoenudi1 = _rtP -> P_647 * _rtB -> auohfil2jj ; _rtDW ->
psebtvzqlm = _rtB -> m0aoenudi1 ; ssWriteToDataStoreWithPath ( S , _rtDW ->
be1j1d2kdf ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write2"
, NULL ) ; ssReadFromDataStoreWithPath ( S , _rtDW -> oapn15bbg2 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read11"
, NULL ) ; jfmtdksnh0 = _rtDW -> eppk3q2xfh ; _rtB -> pfhpxpnycz = _rtP ->
P_648 * jfmtdksnh0 ; ssReadFromDataStoreWithPath ( S , _rtDW -> e5xtrvnkj5 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read10"
, NULL ) ; jfmtdksnh0 = _rtDW -> fgc3q11l1t ; _rtB -> nytwaopivh = _rtP ->
P_649 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_650 ; meppapiqj0 = ( _rtB ->
nytwaopivh > jfmtdksnh0 ) ; jfmtdksnh0 = _rtP -> P_652 * jjkfbyaomr ; if (
ic3wqfpram_idx_0 > _rtP -> P_653 ) { ic3wqfpram_idx_0 = _rtP -> P_653 ; }
else { if ( ic3wqfpram_idx_0 < _rtP -> P_654 ) { ic3wqfpram_idx_0 = _rtP ->
P_654 ; } } finyivsrdi = jfmtdksnh0 / ic3wqfpram_idx_0 / _rtP -> P_655 *
jfmtdksnh0 ; if ( jfmtdksnh0 > _rtP -> P_658 ) { dpajlxfdyx_idx_0 = _rtP ->
P_658 ; } else if ( jfmtdksnh0 < _rtP -> P_659 ) { dpajlxfdyx_idx_0 = _rtP ->
P_659 ; } else { dpajlxfdyx_idx_0 = jfmtdksnh0 ; } cbpfnq4pxd = _rtP -> P_657
* _rtB -> ldjrvtlkq4 / dpajlxfdyx_idx_0 ; jfmtdksnh0 = _rtP -> P_660 ; if (
cbpfnq4pxd > jfmtdksnh0 ) { if ( cbpfnq4pxd > _rtP -> P_282 ) { cbpfnq4pxd =
_rtP -> P_282 ; } else { if ( cbpfnq4pxd < _rtP -> P_283 ) { cbpfnq4pxd =
_rtP -> P_283 ; } } alqkjudhu3 = _rtP -> P_284 - cbpfnq4pxd ; alqkjudhu3 *=
alqkjudhu3 * _rtP -> P_281 + cbpfnq4pxd ; if ( alqkjudhu3 > _rtP -> P_285 ) {
alqkjudhu3 = _rtP -> P_285 ; } else { if ( alqkjudhu3 < _rtP -> P_286 ) {
alqkjudhu3 = _rtP -> P_286 ; } } jfmtdksnh0 = muSingleScalarSqrt ( alqkjudhu3
) ; } else { jfmtdksnh0 = _rtP -> P_280 ; } u0 = muSingleScalarSqrt (
muSingleScalarAbs ( _rtP -> P_656 * finyivsrdi ) ) * jfmtdksnh0 ; if ( u0 >
_rtP -> P_661 ) { u0 = _rtP -> P_661 ; } else { if ( u0 < _rtP -> P_662 ) {
u0 = _rtP -> P_662 ; } } a3l10a5g2s = _rtP -> P_651 * c2fdcpgrsp / u0 ;
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
jfmtdksnh0 ) , _rtP -> P_665 , _rtB -> agikm532fv , _rtP -> P_663 , 15U ,
a3l10a5g2s , _rtP -> P_664 , 14U ) ; if ( jfmtdksnh0 > _rtP -> P_666 ) {
jsgk2hka41_idx_1 = _rtP -> P_666 ; } else if ( jfmtdksnh0 < _rtP -> P_667 ) {
jsgk2hka41_idx_1 = _rtP -> P_667 ; } else { jsgk2hka41_idx_1 = jfmtdksnh0 ; }
ssReadFromDataStoreWithPath ( S , _rtDW -> mgui2lqiaw ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Data Store Read1"
, NULL ) ; jfmtdksnh0 = _rtDW -> a1ts5brulz ; _rtB -> ilhhlnh5lt = _rtP ->
P_668 * jfmtdksnh0 ; alqkjudhu3 = _rtP -> P_669 * c2fdcpgrsp -
ic3wqfpram_idx_1 ; finyivsrdi = _rtP -> P_672 ; rtPrevAction = _rtDW ->
kl21dgjfyi ; if ( batdnpsvim > _rtP -> P_670 ) { jsgk2hka41_idx_0 = _rtP ->
P_670 ; } else if ( batdnpsvim < _rtP -> P_671 ) { jsgk2hka41_idx_0 = _rtP ->
P_671 ; } else { jsgk2hka41_idx_0 = batdnpsvim ; } rtAction = ( int8_T ) ! (
_rtB -> ldjrvtlkq4 / jsgk2hka41_idx_0 <= 0.4167F ) ; _rtDW -> kl21dgjfyi =
rtAction ; if ( rtPrevAction != rtAction ) { switch ( rtPrevAction ) { case 0
: ssSetSolverNeedsReset ( S ) ; break ; case 1 : ssSetSolverNeedsReset ( S )
; break ; } } switch ( rtAction ) { case 0 : if ( rtAction != rtPrevAction )
{ if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset
( S ) ; } } u0 = ( _rtP -> P_169 + finyivsrdi ) * _rtP -> P_170 ; if ( u0 >
_rtP -> P_171 ) { u0 = _rtP -> P_171 ; } else { if ( u0 < _rtP -> P_172 ) {
u0 = _rtP -> P_172 ; } } eplcvohihr = finyivsrdi / u0 ; if ( eplcvohihr >
_rtP -> P_173 ) { eplcvohihr = _rtP -> P_173 ; } else { if ( eplcvohihr <
_rtP -> P_174 ) { eplcvohihr = _rtP -> P_174 ; } } srUpdateBC ( _rtDW ->
lb2gtdwzqd ) ; break ; case 1 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } if ( batdnpsvim > _rtP -> P_177 ) { jsgk2hka41_idx_0 = _rtP -> P_177 ;
} else if ( batdnpsvim < _rtP -> P_178 ) { jsgk2hka41_idx_0 = _rtP -> P_178 ;
} else { jsgk2hka41_idx_0 = batdnpsvim ; } cbpfnq4pxd = _rtB -> ldjrvtlkq4 /
jsgk2hka41_idx_0 ; if ( finyivsrdi > _rtP -> P_180 ) { jsgk2hka41_idx_0 =
_rtP -> P_180 ; } else if ( finyivsrdi < _rtP -> P_181 ) { jsgk2hka41_idx_0 =
_rtP -> P_181 ; } else { jsgk2hka41_idx_0 = finyivsrdi ; } u0 = ( (
finyivsrdi - _rtP -> P_175 ) * ( _rtP -> P_176 - cbpfnq4pxd ) / _rtP -> P_179
/ jsgk2hka41_idx_0 + cbpfnq4pxd ) * ( _rtP -> P_182 - cbpfnq4pxd ) ; if ( u0
> _rtP -> P_183 ) { u0 = _rtP -> P_183 ; } else { if ( u0 < _rtP -> P_184 ) {
u0 = _rtP -> P_184 ; } } eplcvohihr = muSingleScalarSqrt ( u0 ) ; srUpdateBC
( _rtDW -> hpc0grqivr ) ; break ; } ssReadFromDataStoreWithPath ( S , _rtDW
-> ir12dhrecp ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Data Store Read10"
, NULL ) ; jfmtdksnh0 = _rtDW -> ok4jtsn4bb ; _rtB -> cbjrnzc5n1 = _rtP ->
P_673 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_674 ; if ( _rtB -> cbjrnzc5n1 >
jfmtdksnh0 ) { _rtB -> emejhjadst = eplcvohihr * alqkjudhu3 ; } else { _rtB
-> emejhjadst = alqkjudhu3 ; } ssReadFromDataStoreWithPath ( S , _rtDW ->
cczkkmi5hd ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Data Store Read2"
, NULL ) ; jfmtdksnh0 = _rtDW -> lqempabukg ; _rtB -> ezlhtulb34 = _rtP ->
P_675 * jfmtdksnh0 ; e0r0t533ao = _rtDW -> i5yn1movmy + _rtB -> emejhjadst ;
ssReadFromDataStoreWithPath ( S , _rtDW -> f4uwco4la1 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/PID/Data Store Read8"
, NULL ) ; jfmtdksnh0 = _rtDW -> ecauzxzkhl ; _rtB -> eah1hcsb2h = _rtP ->
P_677 * jfmtdksnh0 ; jfmtdksnh0 = ( _rtB -> emejhjadst - _rtDW -> diffnla35e
) * _rtB -> eah1hcsb2h * _rtP -> P_679 ; cbpfnq4pxd = ( real32_T ) ( _rtP ->
P_31 * jfmtdksnh0 ) ; _rtB -> o0aceads0s = _rtDW -> nqyjhyuvcj ; jfmtdksnh0 =
( real32_T ) ( _rtP -> P_32 * _rtB -> o0aceads0s ) ; cbpfnq4pxd -= jfmtdksnh0
; alqkjudhu3 = _rtDW -> fjcoqtw2bx ; jfmtdksnh0 = ( real32_T ) ( _rtP -> P_33
* _rtDW -> fjcoqtw2bx ) ; _rtB -> iq211sbcwf = cbpfnq4pxd - jfmtdksnh0 ;
ssReadFromDataStoreWithPath ( S , _rtDW -> odph5x1drm ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read15"
, NULL ) ; jfmtdksnh0 = _rtDW -> moioiyooa5 ; _rtB -> digibh4z0w = _rtP ->
P_682 * jfmtdksnh0 ; if ( meppapiqj0 ) { _rtB -> cthsuitfz5 = _rtB ->
pfhpxpnycz ; } else if ( _rtB -> digibh4z0w > _rtP -> P_683 ) { u0 = ( ( _rtB
-> ilhhlnh5lt * _rtB -> emejhjadst + jsgk2hka41_idx_1 ) + _rtB -> ezlhtulb34
* e0r0t533ao ) + ( ( ( real32_T ) ( _rtP -> P_30 * _rtB -> o0aceads0s ) +
_rtB -> iq211sbcwf ) + alqkjudhu3 ) ; if ( u0 > _rtP -> P_160 ) { _rtB ->
cthsuitfz5 = _rtP -> P_160 ; } else if ( u0 < _rtP -> P_161 ) { _rtB ->
cthsuitfz5 = _rtP -> P_161 ; } else { _rtB -> cthsuitfz5 = u0 ; } } else {
_rtB -> cthsuitfz5 = jsgk2hka41_idx_1 ; } _rtB -> nytqtnktxr = _rtP -> P_684
* _rtB -> cthsuitfz5 ; _rtDW -> ar2qj33owm = _rtB -> nytqtnktxr ;
ssWriteToDataStoreWithPath ( S , _rtDW -> ksfm4xrloa ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write20"
, NULL ) ; _rtB -> p0f4ijhrpq = _rtP -> P_685 * _rtB -> lbwa3jpkws ; _rtDW ->
pwwmab3rlr = _rtB -> p0f4ijhrpq ; ssWriteToDataStoreWithPath ( S , _rtDW ->
izytyju2r2 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write21"
, NULL ) ; _rtB -> g3rmslxgju = _rtP -> P_686 * _rtB -> ou0itdgh1d ; _rtDW ->
e10toipvv0 = _rtB -> g3rmslxgju ; ssWriteToDataStoreWithPath ( S , _rtDW ->
i4kzjkoyxu ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write22"
, NULL ) ; _rtB -> ek5z4y4voz = _rtP -> P_687 * orelggziy4 ; _rtDW ->
gmsrqeat5h = _rtB -> ek5z4y4voz ; ssWriteToDataStoreWithPath ( S , _rtDW ->
dhkmzrj1v2 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write23"
, NULL ) ; _rtB -> ergriw4ip1 = _rtP -> P_688 * _rtB -> cytczbxazy ; _rtDW ->
aupt3qrz3y = _rtB -> ergriw4ip1 ; ssWriteToDataStoreWithPath ( S , _rtDW ->
mk12nlvn5c ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write24"
, NULL ) ; _rtB -> cr32stjnzh = _rtP -> P_689 * kaqx4nados ; _rtDW ->
dpjpy2bpgy = _rtB -> cr32stjnzh ; ssWriteToDataStoreWithPath ( S , _rtDW ->
b4t23vdsin ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write25"
, NULL ) ; _rtB -> lrw1kivvfm = _rtP -> P_690 * _rtB -> agikm532fv ; _rtDW ->
pelseog20p = _rtB -> lrw1kivvfm ; ssWriteToDataStoreWithPath ( S , _rtDW ->
itfhai41fd ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write3"
, NULL ) ; _rtB -> j3fu5pyahe = _rtP -> P_691 * batdnpsvim ; _rtDW ->
nhrhyjvls4 = _rtB -> j3fu5pyahe ; ssWriteToDataStoreWithPath ( S , _rtDW ->
gxmwc1ws3i ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write4"
, NULL ) ; _rtB -> aqsjhmbxo2 = _rtP -> P_692 * _rtB -> bblimdbln2 ; _rtDW ->
oobzxswkpo = _rtB -> aqsjhmbxo2 ; ssWriteToDataStoreWithPath ( S , _rtDW ->
od43cn3nwy ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write5"
, NULL ) ; _rtB -> iytqwgu15l = _rtP -> P_693 * _rtB -> i2cdqqxwp0 ; _rtDW ->
l0b5hroyaj = _rtB -> iytqwgu15l ; ssWriteToDataStoreWithPath ( S , _rtDW ->
o4mdxa4wbe ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write6"
, NULL ) ; _rtB -> hroyaf510l = _rtP -> P_694 * _rtB -> mt0t1wog2n ; _rtDW ->
ktweu3wugd = _rtB -> hroyaf510l ; ssWriteToDataStoreWithPath ( S , _rtDW ->
aqq0xphes4 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write7"
, NULL ) ; _rtB -> bowle0ow30 = _rtP -> P_695 * g1ekzbu3oi ; _rtDW ->
nlpxiel2sg = _rtB -> bowle0ow30 ; ssWriteToDataStoreWithPath ( S , _rtDW ->
jkypds115r ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write8"
, NULL ) ; _rtB -> amm24eiw3p = _rtP -> P_696 * fwhtla1rft ; _rtDW ->
n5tosor5b5 = _rtB -> amm24eiw3p ; ssWriteToDataStoreWithPath ( S , _rtDW ->
ewajqde1w2 ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write9"
, NULL ) ; _rtB -> htii4ssxez = _rtP -> P_697 * o3mfdsmmfb ; _rtDW ->
nq1n5qxeyp = _rtB -> htii4ssxez ; ssWriteToDataStoreWithPath ( S , _rtDW ->
bxddnpyqx2 ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/ntestimator/Data Store Write25"
, NULL ) ; ssReadFromDataStoreWithPath ( S , _rtDW -> hmzrrmgtbp ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read19"
, NULL ) ; jfmtdksnh0 = _rtDW -> b5t1avpqna ; _rtB -> brshx4vf1z = _rtP ->
P_698 * jfmtdksnh0 ; jfmtdksnh0 = _rtP -> P_699 ; meppapiqj0 = ( _rtB ->
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
P_300 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_300 [ 1 ] ; _rtB ->
n5bgkgnoo4 [ 2 ] = _rtP -> P_300 [ 2 ] ; srUpdateBC ( _rtDW -> o0fqt141qd ) ;
break ; case 1 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2
) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB ->
n5bgkgnoo4 [ 0 ] = _rtP -> P_302 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP ->
P_302 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_302 [ 2 ] ; srUpdateBC (
_rtDW -> h3vqcmc1hz ) ; break ; case 2 : if ( rtAction != rtPrevAction ) { if
( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S
) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_304 [ 0 ] ; _rtB -> n5bgkgnoo4 [
1 ] = _rtP -> P_304 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_304 [ 2 ] ;
srUpdateBC ( _rtDW -> pqpqjda5is ) ; break ; case 3 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_306 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_306 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_306 [ 2 ] ; srUpdateBC ( _rtDW -> bwmwpnvwlf ) ; break ; case 4
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_308 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_308 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_308 [ 2 ] ; srUpdateBC ( _rtDW ->
hf2ukkb54z ) ; break ; case 5 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_310 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_310 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_310 [ 2 ] ;
srUpdateBC ( _rtDW -> dp2wxggv2y ) ; break ; case 6 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_312 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_312 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_312 [ 2 ] ; srUpdateBC ( _rtDW -> ifikoeohu4 ) ; break ; case 7
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_314 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_314 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_314 [ 2 ] ; srUpdateBC ( _rtDW ->
fb2jmsx45b ) ; break ; case 8 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_316 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_316 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_316 [ 2 ] ;
srUpdateBC ( _rtDW -> gu2pk5utpz ) ; break ; case 9 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_318 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_318 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_318 [ 2 ] ; srUpdateBC ( _rtDW -> m1sbzn2h1n ) ; break ; case
10 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_320 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_320 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_320 [ 2 ] ; srUpdateBC ( _rtDW ->
ewylvoz5wx ) ; break ; case 11 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_322 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_322 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_322 [ 2 ] ;
srUpdateBC ( _rtDW -> bzt2b4vlgj ) ; break ; case 12 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_324 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_324 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_324 [ 2 ] ; srUpdateBC ( _rtDW -> p5cjuriyjr ) ; break ; case
13 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_326 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_326 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_326 [ 2 ] ; srUpdateBC ( _rtDW ->
klgivly02z ) ; break ; case 14 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_328 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_328 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_328 [ 2 ] ;
srUpdateBC ( _rtDW -> nlyldhhvyb ) ; break ; case 15 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_330 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_330 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_330 [ 2 ] ; srUpdateBC ( _rtDW -> k1yann3ya5 ) ; break ; case
16 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_332 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_332 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_332 [ 2 ] ; srUpdateBC ( _rtDW ->
bubafrutom ) ; break ; case 17 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_334 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_334 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_334 [ 2 ] ;
srUpdateBC ( _rtDW -> ltvu2oc3sf ) ; break ; case 18 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_336 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_336 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_336 [ 2 ] ; srUpdateBC ( _rtDW -> li2ivnnt0t ) ; break ; case
19 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_338 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_338 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_338 [ 2 ] ; srUpdateBC ( _rtDW ->
ae1e1itbfy ) ; break ; case 20 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_340 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_340 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_340 [ 2 ] ;
srUpdateBC ( _rtDW -> dhx34gepf4 ) ; break ; case 21 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_342 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_342 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_342 [ 2 ] ; srUpdateBC ( _rtDW -> p2atyilds3 ) ; break ; case
22 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_344 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_344 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_344 [ 2 ] ; srUpdateBC ( _rtDW ->
edw2mgcvx1 ) ; break ; case 23 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_346 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_346 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_346 [ 2 ] ;
srUpdateBC ( _rtDW -> n4uikvdjac ) ; break ; case 24 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_348 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_348 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_348 [ 2 ] ; srUpdateBC ( _rtDW -> chxryck3fg ) ; break ; case
25 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_350 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_350 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_350 [ 2 ] ; srUpdateBC ( _rtDW ->
dl0glhtqdr ) ; break ; case 26 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_352 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_352 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_352 [ 2 ] ;
srUpdateBC ( _rtDW -> adcpzgniuv ) ; break ; case 27 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_354 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_354 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_354 [ 2 ] ; srUpdateBC ( _rtDW -> ismm4u0kis ) ; break ; case
28 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_356 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_356 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_356 [ 2 ] ; srUpdateBC ( _rtDW ->
kct4avkdgo ) ; break ; case 29 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_358 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_358 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_358 [ 2 ] ;
srUpdateBC ( _rtDW -> ljqu2i52fc ) ; break ; case 30 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_360 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_360 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_360 [ 2 ] ; srUpdateBC ( _rtDW -> lpg4z3lelv ) ; break ; case
31 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_362 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_362 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_362 [ 2 ] ; srUpdateBC ( _rtDW ->
ombi11gse3 ) ; break ; case 32 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_364 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1
] = _rtP -> P_364 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_364 [ 2 ] ;
srUpdateBC ( _rtDW -> igzqf1qklf ) ; break ; case 33 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [ 0 ] = _rtP -> P_366 [
0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_366 [ 1 ] ; _rtB -> n5bgkgnoo4 [ 2
] = _rtP -> P_366 [ 2 ] ; srUpdateBC ( _rtDW -> moze4hcv5c ) ; break ; case
34 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> n5bgkgnoo4 [
0 ] = _rtP -> P_368 [ 0 ] ; _rtB -> n5bgkgnoo4 [ 1 ] = _rtP -> P_368 [ 1 ] ;
_rtB -> n5bgkgnoo4 [ 2 ] = _rtP -> P_368 [ 2 ] ; srUpdateBC ( _rtDW ->
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
[ 0 ] = _rtP -> P_370 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_370 [ 1 ]
; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_370 [ 2 ] ; srUpdateBC ( _rtDW ->
j4ymuqubrw ) ; break ; case 1 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_372 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_372 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_372 [ 2 ] ;
srUpdateBC ( _rtDW -> kymzzotg2g ) ; break ; case 2 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_374 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_374 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_374 [ 2 ] ; srUpdateBC ( _rtDW -> maiimsnqs5 ) ; break ; case 3
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_376 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_376 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_376 [ 2 ] ; srUpdateBC ( _rtDW ->
dyx4tug5h3 ) ; break ; case 4 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_378 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_378 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_378 [ 2 ] ;
srUpdateBC ( _rtDW -> cr2kibgo2j ) ; break ; case 5 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_380 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_380 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_380 [ 2 ] ; srUpdateBC ( _rtDW -> pwlmqo3nxm ) ; break ; case 6
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_382 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_382 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_382 [ 2 ] ; srUpdateBC ( _rtDW ->
guuziano0t ) ; break ; case 7 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_384 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_384 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_384 [ 2 ] ;
srUpdateBC ( _rtDW -> l12omsu2tn ) ; break ; case 8 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_386 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_386 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_386 [ 2 ] ; srUpdateBC ( _rtDW -> o2zj3fqza1 ) ; break ; case 9
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_388 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_388 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_388 [ 2 ] ; srUpdateBC ( _rtDW ->
m3gfat1ui0 ) ; break ; case 10 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_390 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_390 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_390 [ 2 ] ;
srUpdateBC ( _rtDW -> dk3vj22y05 ) ; break ; case 11 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_392 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_392 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_392 [ 2 ] ; srUpdateBC ( _rtDW -> o3c1lu15ny ) ; break ; case
12 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_394 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_394 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_394 [ 2 ] ; srUpdateBC ( _rtDW ->
j45e0raewi ) ; break ; case 13 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_396 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_396 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_396 [ 2 ] ;
srUpdateBC ( _rtDW -> o3wc5wwa4p ) ; break ; case 14 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_398 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_398 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_398 [ 2 ] ; srUpdateBC ( _rtDW -> irsxloeepq ) ; break ; case
15 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_400 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_400 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_400 [ 2 ] ; srUpdateBC ( _rtDW ->
cp3q1at4o2 ) ; break ; case 16 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_402 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_402 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_402 [ 2 ] ;
srUpdateBC ( _rtDW -> pce44vep3x ) ; break ; case 17 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_404 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_404 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_404 [ 2 ] ; srUpdateBC ( _rtDW -> mee1wioe1r ) ; break ; case
18 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_406 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_406 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_406 [ 2 ] ; srUpdateBC ( _rtDW ->
a5nvnya1oe ) ; break ; case 19 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_408 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_408 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_408 [ 2 ] ;
srUpdateBC ( _rtDW -> dfax004odl ) ; break ; case 20 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_410 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_410 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_410 [ 2 ] ; srUpdateBC ( _rtDW -> mwuspmm2e1 ) ; break ; case
21 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_412 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_412 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_412 [ 2 ] ; srUpdateBC ( _rtDW ->
jgu1xgjxem ) ; break ; case 22 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_414 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_414 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_414 [ 2 ] ;
srUpdateBC ( _rtDW -> my15ghhvb1 ) ; break ; case 23 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_416 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_416 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_416 [ 2 ] ; srUpdateBC ( _rtDW -> bcd3kgenub ) ; break ; case
24 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_418 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_418 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_418 [ 2 ] ; srUpdateBC ( _rtDW ->
f5k2rzim4a ) ; break ; case 25 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_420 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_420 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_420 [ 2 ] ;
srUpdateBC ( _rtDW -> nx3flbvahx ) ; break ; case 26 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_422 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_422 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_422 [ 2 ] ; srUpdateBC ( _rtDW -> lik1wotc2i ) ; break ; case
27 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_424 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_424 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_424 [ 2 ] ; srUpdateBC ( _rtDW ->
gg02mzoxhc ) ; break ; case 28 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_426 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_426 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_426 [ 2 ] ;
srUpdateBC ( _rtDW -> gwxpzomgjh ) ; break ; case 29 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_428 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_428 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_428 [ 2 ] ; srUpdateBC ( _rtDW -> etxqofccji ) ; break ; case
30 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [
0 ] = _rtP -> P_430 [ 0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_430 [ 1 ] ;
_rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_430 [ 2 ] ; srUpdateBC ( _rtDW ->
ljwb0xnabb ) ; break ; case 31 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_432 [ 0 ] ; _rtB -> l1dam3wq3m [ 1
] = _rtP -> P_432 [ 1 ] ; _rtB -> l1dam3wq3m [ 2 ] = _rtP -> P_432 [ 2 ] ;
srUpdateBC ( _rtDW -> ivkldwkotp ) ; break ; case 32 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } _rtB -> l1dam3wq3m [ 0 ] = _rtP -> P_434 [
0 ] ; _rtB -> l1dam3wq3m [ 1 ] = _rtP -> P_434 [ 1 ] ; _rtB -> l1dam3wq3m [ 2
] = _rtP -> P_434 [ 2 ] ; srUpdateBC ( _rtDW -> hypqqzrtox ) ; break ; } if (
meppapiqj0 ) { dpajlxfdyx_idx_0 = _rtB -> l1dam3wq3m [ 0 ] ; jsgk2hka41_idx_0
= _rtB -> l1dam3wq3m [ 1 ] ; jsgk2hka41_idx_1 = _rtB -> l1dam3wq3m [ 2 ] ; }
else { dpajlxfdyx_idx_0 = _rtB -> n5bgkgnoo4 [ 0 ] ; jsgk2hka41_idx_0 = _rtB
-> n5bgkgnoo4 [ 1 ] ; jsgk2hka41_idx_1 = _rtB -> n5bgkgnoo4 [ 2 ] ; } _rtB ->
ehykaejtnw = _rtP -> P_703 * dpajlxfdyx_idx_0 ; _rtDW -> o3z1jsmhkx = _rtB ->
ehykaejtnw ; ssWriteToDataStoreWithPath ( S , _rtDW -> fnxjjp2lme ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write26"
, NULL ) ; _rtB -> oaon3y4tfi = _rtP -> P_704 * jsgk2hka41_idx_0 ; _rtDW ->
hptuorf3i3 = _rtB -> oaon3y4tfi ; ssWriteToDataStoreWithPath ( S , _rtDW ->
angozbvvee ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write27"
, NULL ) ; _rtB -> dhzov4va5p = _rtP -> P_705 * jsgk2hka41_idx_1 ; _rtDW ->
mi05525rde = _rtB -> dhzov4va5p ; ssWriteToDataStoreWithPath ( S , _rtDW ->
mzsuxn1hbm ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Write28"
, NULL ) ; kaqx4nados *= _rtP -> P_706 ; ic3wqfpram_idx_0 = _rtP -> P_707 *
pyabwb0ags ; ic3wqfpram_idx_1 = _rtP -> P_707 * kaqx4nados ; if ( _rtB ->
ezlhtulb34 <= _rtP -> P_708 ) { _rtB -> nd3bibt0gk = _rtP -> P_709 ; } else {
_rtB -> nd3bibt0gk = e0r0t533ao ; } cbpfnq4pxd = _rtDW -> mvpjwhrzk3 ;
alqkjudhu3 = _rtDW -> mtqhixagy1 ; ssReadFromDataStoreWithPath ( S , _rtDW ->
iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter2/Data Store Read1"
, NULL ) ; kaqx4nados = _rtDW -> owcamicoch ; ssReadFromDataStoreWithPath ( S
, _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter2/Data Store Read8"
, NULL ) ; jfmtdksnh0 = _rtDW -> owcamicoch ; _rtB -> ompws1iq14 = _rtP ->
P_714 * kaqx4nados ; _rtB -> m0nyfnn554 = _rtP -> P_717 * jfmtdksnh0 ; if (
_rtB -> m0nyfnn554 > _rtP -> P_718 ) { dpajlxfdyx_idx_0 = _rtP -> P_718 ; }
else if ( _rtB -> m0nyfnn554 < _rtP -> P_719 ) { dpajlxfdyx_idx_0 = _rtP ->
P_719 ; } else { dpajlxfdyx_idx_0 = _rtB -> m0nyfnn554 ; } if ( _rtB ->
ompws1iq14 > _rtP -> P_715 ) { jsgk2hka41_idx_0 = _rtP -> P_715 ; } else if (
_rtB -> ompws1iq14 < _rtP -> P_716 ) { jsgk2hka41_idx_0 = _rtP -> P_716 ; }
else { jsgk2hka41_idx_0 = _rtB -> ompws1iq14 ; } _rtB -> egwnphshj3 = ( _rtP
-> P_713 - jsgk2hka41_idx_0 ) * cbpfnq4pxd + _rtDW -> fhgbtmls3d *
dpajlxfdyx_idx_0 ; ssReadFromDataStoreWithPath ( S , _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter3/Data Store Read1"
, NULL ) ; kaqx4nados = _rtDW -> owcamicoch ; ssReadFromDataStoreWithPath ( S
, _rtDW -> iopgawxuof ,
 "KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/custom_filter3/Data Store Read8"
, NULL ) ; jfmtdksnh0 = _rtDW -> owcamicoch ; _rtB -> iux1flh0ub = _rtP ->
P_722 * kaqx4nados ; _rtB -> asgv30i1hr = _rtP -> P_725 * jfmtdksnh0 ; if (
_rtB -> asgv30i1hr > _rtP -> P_726 ) { dpajlxfdyx_idx_0 = _rtP -> P_726 ; }
else if ( _rtB -> asgv30i1hr < _rtP -> P_727 ) { dpajlxfdyx_idx_0 = _rtP ->
P_727 ; } else { dpajlxfdyx_idx_0 = _rtB -> asgv30i1hr ; } if ( _rtB ->
iux1flh0ub > _rtP -> P_723 ) { jsgk2hka41_idx_0 = _rtP -> P_723 ; } else if (
_rtB -> iux1flh0ub < _rtP -> P_724 ) { jsgk2hka41_idx_0 = _rtP -> P_724 ; }
else { jsgk2hka41_idx_0 = _rtB -> iux1flh0ub ; } _rtB -> mskakvqxnl = ( _rtP
-> P_721 - jsgk2hka41_idx_0 ) * alqkjudhu3 + _rtDW -> l1sigmyvxe *
dpajlxfdyx_idx_0 ;
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
br0btxcgmo ) , _rtP -> P_730 , _rtB -> auohfil2jj , _rtP -> P_728 , 5U , _rtB
-> agikm532fv , _rtP -> P_729 , 6U ) ;
KD_cl_harness_forthao_breach_acc_Look2D_real32_T_real32_T_real32_T ( & (
bsmjlt2qqy ) , _rtP -> P_733 , _rtB -> auohfil2jj , _rtP -> P_731 , 5U , _rtB
-> agikm532fv , _rtP -> P_732 , 6U ) ; jfmtdksnh0 = _rtDW -> ljbykua013 ; for
( i_p = 0 ; i_p < 2 ; i_p ++ ) { btosikvjyf [ i_p ] = _rtP -> P_734 [ i_p + 4
] * exrgmvycyf_idx_2 + ( _rtP -> P_734 [ i_p + 2 ] * exrgmvycyf_idx_1 + _rtP
-> P_734 [ i_p ] * exrgmvycyf_idx_0 ) ; } dpajlxfdyx_idx_0 = _rtDW ->
noqny2ee14 - btosikvjyf [ 0 ] ; jsgk2hka41_idx_0 = jfmtdksnh0 - btosikvjyf [
1 ] ; for ( i_p = 0 ; i_p < 3 ; i_p ++ ) { tmp_n [ i_p ] = _rtP -> P_737 [
i_p + 3 ] * jsgk2hka41_idx_0 + _rtP -> P_737 [ i_p ] * dpajlxfdyx_idx_0 ; }
for ( i_p = 0 ; i_p < 3 ; i_p ++ ) { tmp_l [ i_p ] = _rtP -> P_738 [ i_p + 6
] * exrgmvycyf_idx_2 + ( _rtP -> P_738 [ i_p + 3 ] * exrgmvycyf_idx_1 + _rtP
-> P_738 [ i_p ] * exrgmvycyf_idx_0 ) ; } for ( i_p = 0 ; i_p < 3 ; i_p ++ )
{ _rtB -> ck5rlv2b0s [ i_p ] = ( _rtP -> P_739 [ i_p + 3 ] * _rtB ->
j5nsr3o4kc [ 1 ] + _rtP -> P_739 [ i_p ] * _rtB -> j5nsr3o4kc [ 0 ] ) + (
tmp_n [ i_p ] + tmp_l [ i_p ] ) ; } ssReadFromDataStoreWithPath ( S , _rtDW
-> kwfltn54ul ,
"KD_cl_harness_forthao_breach/ctrl_rb_explicit_20131031_v2/Data Store Read20"
, NULL ) ; _rtB -> k5ufaneaqv = _rtP -> P_740 * _rtDW -> ocojyks2sz ;
jfmtdksnh0 = _rtP -> P_742 ; if ( ! ( _rtB -> k5ufaneaqv > _rtP -> P_741 ) )
{ finyivsrdi = _rtP -> P_741 ; } _rtB -> fgtlymqtj5 = finyivsrdi + jfmtdksnh0
; _rtB -> ikyuhe115u = g1ekzbu3oi ; } _rtB -> o405dyavj2 = _rtB -> bchvsczbjy
- _rtB -> ikyuhe115u ; ssCallAccelRunBlock ( S , 118 , 95 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB ->
je2pvfozpx = _rtB -> hrv5myfmi5 ; ssCallAccelRunBlock ( S , 118 , 97 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> bdookktsiu = _rtB -> bihzjyslyy [ 0 ] ;
ssCallAccelRunBlock ( S , 118 , 99 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
fgv3xdpig1 = _rtB -> cnnxmyxf0o [ 0 ] ; ssCallAccelRunBlock ( S , 118 , 101 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 118 , 102 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 103 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> d3wpj2ehqd = _rtB -> bchvsczbjy - _rtB ->
ikyuhe115u ; ssCallAccelRunBlock ( S , 118 , 105 , SS_CALL_MDL_OUTPUTS ) ; if
( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> ateeecg4um = fwhtla1rft ; } _rtB ->
nhgz3iacwm = _rtB -> gzbcdplagg - _rtB -> ateeecg4um ; ssCallAccelRunBlock (
S , 118 , 108 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) {
_rtB -> bsw5ed2ei2 [ 0 ] = exrgmvycyf_idx_0 ; _rtB -> bsw5ed2ei2 [ 1 ] =
hn15keiut1 ; _rtB -> bsw5ed2ei2 [ 2 ] = byk21oesq1 ; _rtB -> bsw5ed2ei2 [ 3 ]
= jjkfbyaomr ; _rtB -> bsw5ed2ei2 [ 4 ] = o3cuzyoqg5 ; _rtB -> bsw5ed2ei2 [ 5
] = km03xn13id ; _rtB -> bsw5ed2ei2 [ 6 ] = plknkmyedj ; _rtB -> bsw5ed2ei2 [
7 ] = jmuta2homi ; _rtB -> bsw5ed2ei2 [ 8 ] = ehyje10v1p ; _rtB -> bsw5ed2ei2
[ 9 ] = a1jrsglzzi ; _rtB -> bsw5ed2ei2 [ 10 ] = fzccphw1bz ; _rtB ->
bsw5ed2ei2 [ 11 ] = _rtB -> cqertkbhh1 ; _rtB -> bsw5ed2ei2 [ 12 ] =
pyabwb0ags ; ssCallAccelRunBlock ( S , 118 , 110 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 118 , 111 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 118 , 112 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
pv4sn4jq3a = _rtP -> P_95 * _rtB -> emytkc4hpm ; ssCallAccelRunBlock ( S ,
118 , 114 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB
-> nsxqtvqbxa = not4fp11wk ; } ssCallAccelRunBlock ( S , 118 , 116 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 117 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 118 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 119 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) {
ssCallAccelRunBlock ( S , 118 , 120 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 118 , 121 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 118 , 122 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 2 , 0 ) ) { ssCallAccelRunBlock ( S , 118 , 123 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 124 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 125 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 126 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 127 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> pqoz5xc5du [ 0 ] = _rtB -> dobwfafcm0 ; _rtB
-> pqoz5xc5du [ 1 ] = fwhtla1rft ; _rtB -> pqoz5xc5du [ 2 ] = _rtB ->
g50cgr2ero ; ssCallAccelRunBlock ( S , 118 , 129 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> jxcpyfgatb [ 0 ] = fij5klqz0n ; _rtB -> jxcpyfgatb [ 1 ] = c2fdcpgrsp
; _rtB -> jxcpyfgatb [ 2 ] = fvhzusu422 ; } ssCallAccelRunBlock ( S , 118 ,
131 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 132 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> pv4sn4jq3a = _rtB -> abq1p53goy [ 0 ] * _rtB
-> abq1p53goy [ 1 ] * _rtP -> P_96 * _rtP -> P_97 ; ssCallAccelRunBlock ( S ,
118 , 136 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB
-> naxhafm4sy [ 0 ] = pwkaxiafxx ; _rtB -> naxhafm4sy [ 1 ] = gwzyst3ou3_p ;
ssCallAccelRunBlock ( S , 118 , 138 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
pqoz5xc5du [ 0 ] = _rtB -> ldjrvtlkq4 ; _rtB -> pqoz5xc5du [ 1 ] = g1ekzbu3oi
; _rtB -> pqoz5xc5du [ 2 ] = _rtB -> p4ek3tnerm ; ssCallAccelRunBlock ( S ,
118 , 140 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> naxhafm4sy [ 0 ] =
ic3wqfpram_idx_0 ; _rtB -> naxhafm4sy [ 1 ] = ic3wqfpram_idx_1 ;
ssCallAccelRunBlock ( S , 118 , 142 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
naxhafm4sy [ 0 ] = _rtB -> cqertkbhh1 ; _rtB -> naxhafm4sy [ 1 ] = batdnpsvim
; ssCallAccelRunBlock ( S , 118 , 144 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 118 , 145 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
bdookktsiu = _rtB -> j5nsr3o4kc [ 2 ] ; ssCallAccelRunBlock ( S , 118 , 147 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
jcchc5ro3r [ 0 ] = _rtP -> P_98 [ 0 ] ; _rtB -> jcchc5ro3r [ 1 ] = _rtP ->
P_98 [ 1 ] ; _rtB -> jcchc5ro3r [ 2 ] = _rtP -> P_98 [ 2 ] ; _rtB ->
jcchc5ro3r [ 3 ] = _rtP -> P_98 [ 3 ] ; } _rtB -> d2mnr0gjk3 = _rtP -> P_99 *
b11wdxnlxt ; _rtB -> dp5rxe4iul = _rtP -> P_100 * _rtB -> pv4sn4jq3a ; _rtB
-> oogiqer2su = _rtX -> cgw3asjtrv ; ssCallAccelRunBlock ( S , 0 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; aktecqyana = ( _rtB -> oogiqer2su * _rtB ->
n2un1jwvgy + 15.6 * _rtB -> dp5rxe4iul ) / ( _rtB -> dp5rxe4iul + _rtB ->
n2un1jwvgy ) ; if ( aktecqyana > _rtP -> P_102 ) { aktecqyana = _rtP -> P_102
; } else { if ( aktecqyana < _rtP -> P_103 ) { aktecqyana = _rtP -> P_103 ; }
} jolwkb0ztx = _rtB -> dp5rxe4iul + _rtB -> n2un1jwvgy ; if ( ssIsSampleHit (
S , 2 , 0 ) ) { isss3jba5z = orelggziy4 ; pjtzipg04i = _rtB -> cytczbxazy ;
_rtB -> ed1spi442q = _rtB -> cthsuitfz5 ; } n4kbehhhau = _rtP -> P_104 * _rtB
-> bchvsczbjy ; o5ibp43cp4 = _rtP -> P_105 * npiyznthqi ; ssCallAccelRunBlock
( S , 118 , 161 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) )
{ _rtB -> pmdfxiryra [ 0 ] = _rtP -> P_106 [ 0 ] ; _rtB -> pmdfxiryra [ 1 ] =
_rtP -> P_106 [ 1 ] ; _rtB -> pmdfxiryra [ 2 ] = _rtP -> P_106 [ 2 ] ; }
ssCallAccelRunBlock ( S , 16 , 0 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtB -> mc3jee13cu = _rtP -> P_107 ; } if ( ssIsSampleHit (
S , 2 , 0 ) ) { _rtB -> hvovkvfecz = _rtP -> P_108 * _rtB -> nsxqtvqbxa ; }
npiyznthqi = _rtP -> P_109 * b11wdxnlxt ; if ( ssIsSampleHit ( S , 1 , 0 ) )
{ _rtB -> bs12xkh5d2 = _rtP -> P_111 ; memcpy ( & _rtB -> hq3xyej01v [ 0 ] ,
& _rtP -> P_112 [ 0 ] , 9U * sizeof ( real_T ) ) ; memcpy ( & _rtB ->
jokok0sble [ 0 ] , & _rtP -> P_113 [ 0 ] , 18U * sizeof ( real_T ) ) ; _rtB
-> hqy1jjmh3m = _rtP -> P_114 ; } _rtB -> ja2tmyhnj3 [ 0 ] = _rtB ->
hvovkvfecz ; _rtB -> ja2tmyhnj3 [ 1 ] = _rtP -> P_110 * npiyznthqi ;
ssCallAccelRunBlock ( S , 8 , 1 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit
( S , 1 , 0 ) ) { _rtB -> inucny24ld = _rtP -> P_115 ; } if ( ssIsSampleHit (
S , 2 , 0 ) ) { _rtB -> b3aoglncfn = _rtP -> P_116 * _rtB -> nsxqtvqbxa ; }
if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> eyvlabfz35 = _rtP -> P_118 ;
memcpy ( & _rtB -> by3idv4rjp [ 0 ] , & _rtP -> P_119 [ 0 ] , 9U * sizeof (
real_T ) ) ; memcpy ( & _rtB -> g5cy1hupuw [ 0 ] , & _rtP -> P_120 [ 0 ] ,
18U * sizeof ( real_T ) ) ; _rtB -> hd4dyryhyo = _rtP -> P_121 ; } _rtB ->
hyh0jrfm44 [ 0 ] = _rtB -> b3aoglncfn ; _rtB -> hyh0jrfm44 [ 1 ] = _rtP ->
P_117 * npiyznthqi ; ssCallAccelRunBlock ( S , 7 , 1 , SS_CALL_MDL_OUTPUTS )
; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> k4nb2fciye = _rtP -> P_122 ; }
if ( 1.0 / n4kbehhhau * o5ibp43cp4 >= _rtP -> P_123 ) { efj5q5ebcq =
n4kbehhhau / o5ibp43cp4 ; if ( efj5q5ebcq > _rtP -> P_10 ) { if ( efj5q5ebcq
> _rtP -> P_8 ) { efj5q5ebcq = _rtP -> P_8 ; } else { if ( efj5q5ebcq < _rtP
-> P_9 ) { efj5q5ebcq = _rtP -> P_9 ; } } tmp = ( ( 1.0 - efj5q5ebcq ) *
0.14285714285714282 + efj5q5ebcq ) * ( 1.0 - efj5q5ebcq ) ; if ( tmp < 0.0 )
{ npiyznthqi = - muDoubleScalarSqrt ( - tmp ) ; } else { npiyznthqi =
muDoubleScalarSqrt ( tmp ) ; } } else { npiyznthqi = _rtB -> inucny24ld ; }
efj5q5ebcq = o5ibp43cp4 / _rtB -> evjqqlvc2b / _rtB -> mc3jee13cu *
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
muDoubleScalarSqrt ( tmp ) ; } } else { npiyznthqi = _rtB -> k4nb2fciye ; }
efj5q5ebcq = n4kbehhhau / _rtB -> evjqqlvc2b / _rtB -> mc3jee13cu *
n4kbehhhau * _rtP -> P_5 ; if ( efj5q5ebcq < 0.0 ) { efj5q5ebcq = -
muDoubleScalarSqrt ( muDoubleScalarAbs ( efj5q5ebcq ) ) ; } else { efj5q5ebcq
= muDoubleScalarSqrt ( efj5q5ebcq ) ; } if ( _rtB -> kodkkyrzjg > _rtP -> P_3
) { tmp = _rtP -> P_3 ; } else if ( _rtB -> kodkkyrzjg < _rtP -> P_4 ) { tmp
= _rtP -> P_4 ; } else { tmp = _rtB -> kodkkyrzjg ; } npiyznthqi = efj5q5ebcq
* tmp * npiyznthqi * _rtP -> P_6 * _rtP -> P_7 ; } if ( npiyznthqi > _rtP ->
P_124 ) { npiyznthqi = _rtP -> P_124 ; } else { if ( npiyznthqi < _rtP ->
P_125 ) { npiyznthqi = _rtP -> P_125 ; } } if ( ssIsSampleHit ( S , 1 , 0 ) )
{ for ( i = 0 ; i < 7 ; i ++ ) { _rtB -> o2q5t1f1qu [ i ] = _rtP -> P_126 [ i
] ; } _rtB -> k1ps2ghsnt [ 0 ] = _rtP -> P_127 [ 0 ] ; _rtB -> k1ps2ghsnt [ 1
] = _rtP -> P_127 [ 1 ] ; } efj5q5ebcq = _rtP -> P_128 * _rtB -> g4zs5uffpf ;
_rtB -> itrula04mb = ( ( ( ( 0.43860691 * _rtB -> i5ltskj44y + - 1283.1169 )
+ 10.249443 * efj5q5ebcq ) + 4.7302501 * _rtB -> l3w4wnvf30 ) + 4.3259397e-5
* muDoubleScalarPower ( _rtB -> i5ltskj44y , 2.0 ) ) + - 0.13127391 *
muDoubleScalarPower ( efj5q5ebcq , 2.0 ) ; ssCallAccelRunBlock ( S , 118 ,
191 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 118 , 192 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> pfjlw5lr0k = _rtP -> P_129 * b11wdxnlxt ;
ssCallAccelRunBlock ( S , 15 , 0 , SS_CALL_MDL_OUTPUTS ) ; efj5q5ebcq = _rtB
-> n2un1jwvgy + _rtB -> dp5rxe4iul ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
_rtB -> puqwmlegg3 = ( 1369.19425815691 * muDoubleScalarPower ( _rtDW ->
h1201vgmm4 , 2.0 ) + 35.4540616064791 * _rtDW -> h1201vgmm4 ) +
97.0096843671075 ; } _rtB -> fuzlkkiiol = _rtB -> puqwmlegg3 / _rtB ->
b2luvekoek ; _rtB -> hu5bxh125n = _rtP -> P_131 * _rtB -> mdayruhtru ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> auey3t313w = _rtP -> P_132 ; _rtB ->
dyicqrr5zm = _rtP -> P_133 ; _rtB -> mfc1qbtpbh = _rtP -> P_134 ; _rtB ->
njmogd2rld = _rtP -> P_135 ; for ( i = 0 ; i < 5 ; i ++ ) { _rtB ->
awvtuqtvtj [ i ] = _rtP -> P_136 [ i ] ; } for ( i = 0 ; i < 7 ; i ++ ) {
_rtB -> i533l50tdy [ i ] = _rtP -> P_137 [ i ] ; } } _rtB -> d1wnqgnnye [ 0 ]
= _rtB -> auey3t313w ; _rtB -> d1wnqgnnye [ 1 ] = _rtB -> dyicqrr5zm ; _rtB
-> d1wnqgnnye [ 2 ] = _rtB -> mfc1qbtpbh ; _rtB -> d1wnqgnnye [ 3 ] = _rtB ->
njmogd2rld ; ssCallAccelRunBlock ( S , 17 , 1 , SS_CALL_MDL_OUTPUTS ) ; _rtB
-> e1c3pmsqne = ( ( efj5q5ebcq - _rtB -> joo1p3hpwk ) - _rtB -> g4zs5uffpf )
* _rtP -> P_138 ; _rtB -> jbmgl2xjkd = 1.0 / ( _rtP -> P_140 * gen03hfvbg ) *
( ( aktecqyana - _rtX -> ge52s03ms5 ) * efj5q5ebcq ) ; efj5q5ebcq = ( (
efj5q5ebcq * _rtB -> ddm05yw3si - _rtB -> joo1p3hpwk * _rtB -> i5ltskj44y ) -
_rtB -> g4zs5uffpf * _rtB -> i5ltskj44y ) - ( _rtB -> ddm05yw3si - _rtB ->
l3w4wnvf30 ) * efj5q5ebcq * _rtP -> P_141 / 1.004 ; if ( ssIsSampleHit ( S ,
1 , 0 ) ) { _rtB -> hd1zca4gmc = _rtP -> P_143 ; } _rtB -> bgfuarduqf = _rtP
-> P_142 * efj5q5ebcq / _rtB -> hd1zca4gmc ; _rtB -> nrka54dvrg = ( (
npiyznthqi + _rtB -> g4zs5uffpf ) - _rtB -> n2un1jwvgy ) * _rtP -> P_144 ;
_rtB -> g3pmlzz4ss = ( ( _rtX -> ge52s03ms5 - _rtB -> oogiqer2su ) * _rtB ->
g4zs5uffpf - npiyznthqi * _rtB -> oogiqer2su ) * ( 1.0 / ( _rtP -> P_145 *
c4l11istf0 ) ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> l4bungqz0o =
_rtP -> P_147 ; } _rtB -> g5lp13b0ul = ( ( npiyznthqi * _rtB -> evjqqlvc2b +
_rtB -> g4zs5uffpf * _rtB -> aomqll03f3 ) - _rtB -> hupcczf3ah * _rtB ->
n2un1jwvgy ) * _rtP -> P_146 / _rtB -> l4bungqz0o ; _rtB -> pv4sn4jq3a = (
1.6e-9 * muDoubleScalarPower ( _rtB -> mdayruhtru , 2.0 ) + -
1.82444404829743e-6 * _rtB -> mdayruhtru ) + 0.002 ; ssCallAccelRunBlock ( S
, 118 , 230 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
_rtB -> b1amhr52hl = _rtP -> P_148 ; } _rtB -> lespb22kzi = ( _rtB ->
mdayruhtru <= _rtB -> b1amhr52hl ) ; if ( ssIsSampleHit ( S , 1 , 0 ) && _rtB
-> lespb22kzi ) { ssSetStopRequested ( S , 1 ) ; } ssCallAccelRunBlock ( S ,
118 , 234 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> lzrox5v1eq = ( ( _rtB ->
bryj0ppggc - _rtB -> pv4sn4jq3a ) - _rtB -> em4bb22xsn ) * _rtP -> P_149 ;
ssCallAccelRunBlock ( S , 118 , 237 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 118 , 238 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
ag3hjwa1z3 = ( _rtB -> o4etjyeod5 - npiyznthqi ) * _rtB -> evjqqlvc2b * _rtP
-> P_150 ; ssCallAccelRunBlock ( S , 118 , 241 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 4 , 0 ) ) { _rtB -> itn3byrwvm = _rtDW -> beiefj4kfo ; }
if ( ssIsSampleHit ( S , 5 , 0 ) ) { _rtB -> lpu04mltzu = _rtDW -> d2tl5o0hel
; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { dxuu1n0atf * _rtB ;
nka5ekiiij * _rtP ; cet3mqzt35 * _rtDW ; _rtDW = ( ( cet3mqzt35 * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( nka5ekiiij * ) ssGetDefaultParam ( S ) )
; _rtB = ( ( dxuu1n0atf * ) _ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S ,
1 , 0 ) ) { _rtDW -> cc0wkfbxf2 = _rtB -> aomqll03f3 ; _rtDW -> eac1jvpkom =
_rtB -> ed1spi442q ; } if ( ssIsSampleHit ( S , 3 , 0 ) ) { foiteff4aq ( _rtB
-> itn3byrwvm , & _rtDW -> masm1qwyo5u ) ; foiteff4aq ( _rtB -> lpu04mltzu ,
& _rtDW -> cdbewnv5xj ) ; foiteff4aq ( _rtB -> pma3ohqkrh , & _rtDW ->
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
czspnnf2wz ; _rtDW -> letoggxozl = _rtB -> agikm532fv ; _rtDW -> frjwyakiph =
_rtB -> iqg1nj4hwf ; _rtDW -> i5yn1movmy = _rtB -> nd3bibt0gk ; _rtDW ->
diffnla35e = _rtB -> emejhjadst ; _rtDW -> nqyjhyuvcj = _rtB -> iq211sbcwf ;
_rtDW -> fjcoqtw2bx = _rtB -> o0aceads0s ; _rtDW -> iggiejtmqu = _rtB ->
fgtlymqtj5 ; _rtDW -> mvpjwhrzk3 = _rtB -> lksu3sv24v ; _rtDW -> mtqhixagy1 =
_rtB -> lmn34nxqxt ; _rtDW -> fhgbtmls3d = _rtB -> egwnphshj3 ; _rtDW ->
l1sigmyvxe = _rtB -> mskakvqxnl ; _rtDW -> noqny2ee14 = _rtB -> ldjrvtlkq4 ;
_rtDW -> ljbykua013 = _rtB -> dobwfafcm0 ; } if ( ssIsSampleHit ( S , 1 , 0 )
) { _rtDW -> h1201vgmm4 = _rtB -> joo1p3hpwk ; } if ( ssIsSampleHit ( S , 4 ,
0 ) ) { _rtDW -> beiefj4kfo = ( _rtP -> P_152 - _rtP -> P_151 ) *
rt_urand_Upu32_Yd_f_pw_snf ( & _rtDW -> msu4qgbkxt ) + _rtP -> P_151 ; } if (
ssIsSampleHit ( S , 5 , 0 ) ) { _rtDW -> d2tl5o0hel = ( _rtP -> P_155 - _rtP
-> P_154 ) * rt_urand_Upu32_Yd_f_pw_snf ( & _rtDW -> grioepryal ) + _rtP ->
P_154 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { dxuu1n0atf * _rtB ; pi4eqa0gee
* _rtXdot ; _rtXdot = ( ( pi4eqa0gee * ) ssGetdX ( S ) ) ; _rtB = ( (
dxuu1n0atf * ) _ssGetBlockIO ( S ) ) ; _rtXdot -> mupnfilrqo = _rtB ->
g5lp13b0ul ; _rtXdot -> huyhg2ps31 = _rtB -> bgfuarduqf ; _rtXdot ->
lgbs44xptg = _rtB -> ag3hjwa1z3 ; _rtXdot -> ka43gmkysq = _rtB -> lzrox5v1eq
; _rtXdot -> iqp0o3u0ph = _rtB -> nrka54dvrg ; _rtXdot -> iynqfp2xbi = _rtB
-> e1c3pmsqne ; _rtXdot -> cgw3asjtrv = _rtB -> g3pmlzz4ss ; _rtXdot ->
ge52s03ms5 = _rtB -> jbmgl2xjkd ; } static void mdlInitializeSizes (
SimStruct * S ) { ssSetChecksumVal ( S , 0 , 3446512300U ) ; ssSetChecksumVal
( S , 1 , 2594695650U ) ; ssSetChecksumVal ( S , 2 , 2419757157U ) ;
ssSetChecksumVal ( S , 3 , 957878992U ) ; { mxArray * slVerStructMat = NULL ;
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
ssGetDefaultParam ( S ) ) -> P_46 = rtInf ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_48 = rtInf ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_67 = rtInf ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_167 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_171 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_173 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_177 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_180 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_183 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_193 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_195 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_197 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_199 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_205 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_208 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_211 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_215 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_217 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_221 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_223 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_234 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_238 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_243 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_245 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_247 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_249 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_285 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_287 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_289 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_293 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_459 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_461 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_464 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_466 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_468 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_520 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_527 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_531 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_552 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_576 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_580 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_583 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_586 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_588 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_592 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_603 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_609 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_653 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_658 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_661 = rtInfF ; ( ( nka5ekiiij * )
ssGetDefaultParam ( S ) ) -> P_670 = rtInfF ; } static void
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
