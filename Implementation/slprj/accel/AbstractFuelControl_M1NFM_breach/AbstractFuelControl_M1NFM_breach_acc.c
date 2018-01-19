#include "__cf_AbstractFuelControl_M1NFM_breach.h"
#if 0
This file is not available for use in any application other than as a MATLAB
( R ) MEX file for use with the Simulink ( R ) product . If you do not have
the Simulink Coder licensed , this file contains encrypted block names , etc
. If you purchase the Simulink Coder , this file will contain full block
descriptions and improved variable names .
#endif
#include <math.h>
#include "AbstractFuelControl_M1NFM_breach_acc.h"
#include "AbstractFuelControl_M1NFM_breach_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T AbstractFuelControl_M1NFM_breach_acc_rt_TDelayUpdateTailOrGrowBuf (
int_T * bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr ,
real_T tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * *
xBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay , int_T *
maxNewBufSzPtr ) { int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = *
bufSzPtr ; real_T * tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T
numBuffer = 2 ; if ( istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ;
} testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay
<= tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T *
tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T
newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr ) { *
maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer *
newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false )
; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
tBufPtr = tempT ; * uBufPtr = tempU ; if ( istransportdelay ) * xBufPtr =
tempX ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
AbstractFuelControl_M1NFM_breach_acc_rt_VTDelayfindtDInterpolate ( real_T x ,
real_T * tBuf , real_T * uBuf , real_T * xBuf , int_T bufSz , int_T head ,
int_T tail , int_T * pLast , real_T t , real_T tStart , boolean_T discrete ,
boolean_T minorStepAndTAtLastMajorOutput , real_T initOutput , real_T *
appliedDelay ) { int_T n , k ; real_T f ; int_T kp1 ; real_T tminustD , tL ,
tR , uD , uL , uR , fU ; if ( minorStepAndTAtLastMajorOutput ) { if ( * pLast
== head ) { * pLast = ( * pLast == 0 ) ? bufSz - 1 : * pLast - 1 ; } head = (
head == 0 ) ? bufSz - 1 : head - 1 ; } if ( x <= 1 ) { return initOutput ; }
k = * pLast ; n = 0 ; for ( ; ; ) { n ++ ; if ( n > bufSz ) break ; if ( x -
xBuf [ k ] > 1.0 ) { if ( k == head ) { int_T km1 ; f = ( x - 1.0 - xBuf [ k
] ) / ( x - xBuf [ k ] ) ; tminustD = ( 1.0 - f ) * tBuf [ k ] + f * t ; km1
= k - 1 ; if ( km1 < 0 ) km1 = bufSz - 1 ; tL = tBuf [ km1 ] ; tR = tBuf [ k
] ; uL = uBuf [ km1 ] ; uR = uBuf [ k ] ; break ; } kp1 = k + 1 ; if ( kp1 ==
bufSz ) kp1 = 0 ; if ( x - xBuf [ kp1 ] <= 1.0 ) { f = ( x - 1.0 - xBuf [ k ]
) / ( xBuf [ kp1 ] - xBuf [ k ] ) ; tL = tBuf [ k ] ; tR = tBuf [ kp1 ] ; uL
= uBuf [ k ] ; uR = uBuf [ kp1 ] ; tminustD = ( 1.0 - f ) * tL + f * tR ;
break ; } k = kp1 ; } else { if ( k == tail ) { f = ( x - 1.0 ) / xBuf [ k ]
; if ( discrete ) { return ( uBuf [ tail ] ) ; } kp1 = k + 1 ; if ( kp1 ==
bufSz ) kp1 = 0 ; tminustD = ( 1 - f ) * tStart + f * tBuf [ k ] ; tL = tBuf
[ k ] ; tR = tBuf [ kp1 ] ; uL = uBuf [ k ] ; uR = uBuf [ kp1 ] ; break ; } k
= k - 1 ; if ( k < 0 ) k = bufSz - 1 ; } } * pLast = k ; if ( tR == tL ) { fU
= 1.0 ; } else { fU = ( tminustD - tL ) / ( tR - tL ) ; } if ( discrete ) {
uD = ( fU > ( 1.0 - fU ) ) ? uR : uL ; } else { uD = ( 1.0 - fU ) * uL + fU *
uR ; } * appliedDelay = t - tminustD ; return uD ; } real_T look2_binlxpw (
real_T u0 , real_T u1 , const real_T bp0 [ ] , const real_T bp1 [ ] , const
real_T table [ ] , const uint32_T maxIndex [ ] , uint32_T stride ) { real_T
frac ; uint32_T bpIndices [ 2 ] ; real_T fractions [ 2 ] ; real_T yL_1d ;
uint32_T iRght ; uint32_T bpIdx ; uint32_T iLeft ; if ( u0 <= bp0 [ 0U ] ) {
iLeft = 0U ; frac = ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ] - bp0 [ 0U ] ) ; }
else if ( u0 < bp0 [ maxIndex [ 0U ] ] ) { bpIdx = maxIndex [ 0U ] >> 1U ;
iLeft = 0U ; iRght = maxIndex [ 0U ] ; while ( iRght - iLeft > 1U ) { if ( u0
< bp0 [ bpIdx ] ) { iRght = bpIdx ; } else { iLeft = bpIdx ; } bpIdx = (
iRght + iLeft ) >> 1U ; } frac = ( u0 - bp0 [ iLeft ] ) / ( bp0 [ iLeft + 1U
] - bp0 [ iLeft ] ) ; } else { iLeft = maxIndex [ 0U ] - 1U ; frac = ( u0 -
bp0 [ maxIndex [ 0U ] - 1U ] ) / ( bp0 [ maxIndex [ 0U ] ] - bp0 [ maxIndex [
0U ] - 1U ] ) ; } fractions [ 0U ] = frac ; bpIndices [ 0U ] = iLeft ; if (
u1 <= bp1 [ 0U ] ) { iLeft = 0U ; frac = ( u1 - bp1 [ 0U ] ) / ( bp1 [ 1U ] -
bp1 [ 0U ] ) ; } else if ( u1 < bp1 [ maxIndex [ 1U ] ] ) { bpIdx = maxIndex
[ 1U ] >> 1U ; iLeft = 0U ; iRght = maxIndex [ 1U ] ; while ( iRght - iLeft >
1U ) { if ( u1 < bp1 [ bpIdx ] ) { iRght = bpIdx ; } else { iLeft = bpIdx ; }
bpIdx = ( iRght + iLeft ) >> 1U ; } frac = ( u1 - bp1 [ iLeft ] ) / ( bp1 [
iLeft + 1U ] - bp1 [ iLeft ] ) ; } else { iLeft = maxIndex [ 1U ] - 1U ; frac
= ( u1 - bp1 [ maxIndex [ 1U ] - 1U ] ) / ( bp1 [ maxIndex [ 1U ] ] - bp1 [
maxIndex [ 1U ] - 1U ] ) ; } bpIdx = iLeft * stride + bpIndices [ 0U ] ;
yL_1d = ( table [ bpIdx + 1U ] - table [ bpIdx ] ) * fractions [ 0U ] + table
[ bpIdx ] ; bpIdx += stride ; return ( ( ( table [ bpIdx + 1U ] - table [
bpIdx ] ) * fractions [ 0U ] + table [ bpIdx ] ) - yL_1d ) * frac + yL_1d ; }
static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T o43lpjacju ;
real_T tNextAdjusted ; uint32_T numCycles ; int8_T rtPrevAction ; int8_T
rtAction ; real_T abswwtaokt ; ZCEventType zcEvent ; boolean_T bmqjuwerbv ;
real32_T murv4kynwz ; real32_T hbbmvu1ti2 ; ph1nm0us43 * _rtB ; dcl0awcq00 *
_rtP ; kytkvw2bdr * _rtX ; eoyji14rg3 * _rtZCE ; m2i0d1iib5 * _rtDW ; _rtDW =
( ( m2i0d1iib5 * ) ssGetRootDWork ( S ) ) ; _rtZCE = ( ( eoyji14rg3 * )
_ssGetPrevZCSigState ( S ) ) ; _rtX = ( ( kytkvw2bdr * ) ssGetContStates ( S
) ) ; _rtP = ( ( dcl0awcq00 * ) ssGetDefaultParam ( S ) ) ; _rtB = ( (
ph1nm0us43 * ) _ssGetBlockIO ( S ) ) ; _rtB -> ek0daqiir2 = ( ( kytkvw2bdr *
) ssGetContStates ( S ) ) -> f0uysuxxc1 ; _rtB -> puwxndtiqx = _rtP -> P_8 *
_rtB -> ek0daqiir2 ; _rtB -> gkkpdxravm = 0.0 ; _rtB -> gkkpdxravm += _rtP ->
P_10 * _rtX -> gxzm0c403c ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
cjj3tfxc43 = _rtP -> P_11 ; } _rtB -> iqivgceeqj = _rtB -> gkkpdxravm + _rtB
-> cjj3tfxc43 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> cjl405i3az = _rtB
-> iqivgceeqj >= _rtP -> P_12 ? 1 : _rtB -> iqivgceeqj > _rtP -> P_13 ? 0 : -
1 ; } _rtB -> jvmkacwvl5 = _rtDW -> cjl405i3az == 1 ? _rtP -> P_12 : _rtDW ->
cjl405i3az == - 1 ? _rtP -> P_13 : _rtB -> iqivgceeqj ; ssCallAccelRunBlock (
S , 17 , 6 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW
-> ahcljuesel = ( ( f11gk4xn5j * ) ssGetU ( S ) ) -> ienofsir3m >= _rtP ->
P_14 ? 1 : ( ( f11gk4xn5j * ) ssGetU ( S ) ) -> ienofsir3m > _rtP -> P_15 ? 0
: - 1 ; } _rtB -> hel0zpgi2w = _rtDW -> ahcljuesel == 1 ? _rtP -> P_14 :
_rtDW -> ahcljuesel == - 1 ? _rtP -> P_15 : ( ( f11gk4xn5j * ) ssGetU ( S ) )
-> ienofsir3m ; _rtB -> ocwsydb01a = _rtP -> P_16 * _rtB -> hel0zpgi2w ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW -> m4j1jhhp3e = ( ssGetTaskTime ( S , 1
) >= _rtP -> P_17 ) ; if ( _rtDW -> m4j1jhhp3e == 1 ) { _rtB -> g2ickh0fvt =
_rtP -> P_19 ; } else { _rtB -> g2ickh0fvt = _rtP -> P_18 ; } } _rtB ->
jcrlgpninh = ( real32_T ) _rtB -> ocwsydb01a ; _rtB -> b1zhf3ueyq = (
real32_T ) _rtB -> jvmkacwvl5 ; o43lpjacju = ( ( 2.821 - 0.05231 * _rtB ->
jvmkacwvl5 ) + 0.10299 * _rtB -> jvmkacwvl5 * _rtB -> jvmkacwvl5 ) - 0.00063
* _rtB -> jvmkacwvl5 * _rtB -> jvmkacwvl5 * _rtB -> jvmkacwvl5 ; _rtB ->
n5at0j5xf2 = ( ( kytkvw2bdr * ) ssGetContStates ( S ) ) -> mphig5gmgs ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> c4ntxy5usk = _rtP -> P_21 ; } _rtB ->
pnoduxvqg5 = _rtB -> n5at0j5xf2 / _rtB -> c4ntxy5usk ; _rtB -> nl4lofzxqk =
1.0 / _rtB -> n5at0j5xf2 * _rtB -> c4ntxy5usk ; if ( ssIsMajorTimeStep ( S )
) { tNextAdjusted = _rtB -> pnoduxvqg5 ; _rtDW -> jrenr0quvo = 0 ; if ( _rtB
-> nl4lofzxqk < _rtB -> pnoduxvqg5 ) { tNextAdjusted = _rtB -> nl4lofzxqk ;
_rtDW -> jrenr0quvo = 1 ; } _rtB -> dyxtbj4z2s = tNextAdjusted ; } else {
tNextAdjusted = _rtB -> pnoduxvqg5 ; if ( _rtDW -> jrenr0quvo == 1 ) {
tNextAdjusted = _rtB -> nl4lofzxqk ; } _rtB -> dyxtbj4z2s = tNextAdjusted ; }
if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> ayvpg1qfs1 = _rtP -> P_22 ; } if
( ssIsMajorTimeStep ( S ) ) { _rtDW -> iyjoihkybi = ( _rtB -> dyxtbj4z2s >=
_rtP -> P_23 ) ; } if ( _rtDW -> iyjoihkybi ) { tNextAdjusted = _rtB ->
dyxtbj4z2s - _rtB -> dyxtbj4z2s * _rtB -> dyxtbj4z2s ; if ( tNextAdjusted <
0.0 ) { tNextAdjusted = - muDoubleScalarSqrt ( - tNextAdjusted ) ; } else {
tNextAdjusted = muDoubleScalarSqrt ( tNextAdjusted ) ; } _rtB -> brj2vus43q =
2.0 * tNextAdjusted ; _rtB -> jvyom45mqw = _rtB -> brj2vus43q ; } else { _rtB
-> jvyom45mqw = _rtB -> ayvpg1qfs1 ; } _rtB -> bq2ygt10h0 = _rtB ->
c4ntxy5usk - _rtB -> n5at0j5xf2 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if (
_rtB -> bq2ygt10h0 > 0.0 ) { _rtDW -> nguprscwos = 1 ; } else if ( _rtB ->
bq2ygt10h0 < 0.0 ) { _rtDW -> nguprscwos = - 1 ; } else { _rtDW -> nguprscwos
= 0 ; } _rtB -> g1s5nynbd4 = _rtDW -> nguprscwos ; } _rtB -> odgjzh4qy0 =
o43lpjacju * _rtB -> jvyom45mqw * _rtB -> g1s5nynbd4 ; _rtB -> i4yf011jd0 =
_rtP -> P_24 * _rtB -> odgjzh4qy0 ; _rtB -> e1h02sbxw0 = ( real32_T ) _rtB ->
i4yf011jd0 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> ktlsapn4ns = _rtP
-> P_25 ; } if ( _rtB -> g2ickh0fvt >= _rtP -> P_26 ) { _rtB -> bxiecodzf4 =
_rtB -> ktlsapn4ns ; } else { _rtB -> bxiecodzf4 = _rtB -> puwxndtiqx ; }
_rtB -> a4n1ddhq55 = _rtB -> bxiecodzf4 * ( ( f11gk4xn5j * ) ssGetU ( S ) )
-> lq41yutgrc ; _rtB -> pwtkvvgwte = ( real32_T ) _rtB -> a4n1ddhq55 ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW -> o450djtvjy = ( ssGetTaskTime ( S , 1
) >= _rtP -> P_0 ) ; if ( _rtDW -> o450djtvjy == 1 ) { abswwtaokt = _rtP ->
P_2 ; } else { abswwtaokt = _rtP -> P_1 ; } } if ( ssIsSampleHit ( S , 2 , 0
) ) { o43lpjacju = ssGetTaskTime ( S , 2 ) ; tNextAdjusted = ( real_T )
ssGetTNextWasAdjusted ( S , 2 ) ; if ( tNextAdjusted != 0.0 ) { _rtDW ->
iuxpe0eosa = _ssGetVarNextHitTime ( S , 0 ) ; } if ( _rtDW -> cywvnac1yr != 0
) { _rtDW -> cywvnac1yr = 0 ; if ( o43lpjacju >= _rtP -> P_6 ) {
tNextAdjusted = ( o43lpjacju - _rtP -> P_6 ) / _rtP -> P_4 ; numCycles = (
uint32_T ) muDoubleScalarFloor ( tNextAdjusted ) ; if ( muDoubleScalarAbs ( (
real_T ) ( numCycles + 1U ) - tNextAdjusted ) < DBL_EPSILON * tNextAdjusted )
{ numCycles ++ ; } _rtDW -> ld1nr1phhh = numCycles ; tNextAdjusted = ( (
real_T ) numCycles * _rtP -> P_4 + _rtP -> P_6 ) + _rtP -> P_5 * _rtP -> P_4
/ 100.0 ; if ( o43lpjacju < tNextAdjusted ) { _rtDW -> bgsfpvxr30 = 1 ; _rtDW
-> iuxpe0eosa = tNextAdjusted ; } else { _rtDW -> bgsfpvxr30 = 0 ; _rtDW ->
iuxpe0eosa = ( real_T ) ( numCycles + 1U ) * _rtP -> P_4 + _rtP -> P_6 ; } }
else { _rtDW -> ld1nr1phhh = _rtP -> P_6 != 0.0 ? - 1 : 0 ; _rtDW ->
bgsfpvxr30 = 0 ; _rtDW -> iuxpe0eosa = _rtP -> P_6 ; } } else { if ( _rtDW ->
iuxpe0eosa <= o43lpjacju ) { if ( _rtDW -> bgsfpvxr30 == 1 ) { _rtDW ->
bgsfpvxr30 = 0 ; _rtDW -> iuxpe0eosa = ( real_T ) ( _rtDW -> ld1nr1phhh + 1L
) * _rtP -> P_4 + _rtP -> P_6 ; } else { _rtDW -> ld1nr1phhh ++ ; _rtDW ->
bgsfpvxr30 = 1 ; _rtDW -> iuxpe0eosa = ( _rtP -> P_5 * _rtP -> P_4 * 0.01 + (
real_T ) _rtDW -> ld1nr1phhh * _rtP -> P_4 ) + _rtP -> P_6 ; } } }
_ssSetVarNextHitTime ( S , 0 , _rtDW -> iuxpe0eosa ) ; if ( _rtDW ->
bgsfpvxr30 == 1 ) { _rtB -> lfocptxalw = _rtP -> P_3 ; } else { _rtB ->
lfocptxalw = 0.0 ; } } _rtDW -> km1uayiklu = _rtB -> jcrlgpninh ;
ssWriteToDataStoreWithPath ( S , _rtDW -> emzgemsqq5 ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/DataStoreWrite"
, NULL ) ; _rtDW -> jptcqedh1l = _rtB -> b1zhf3ueyq ;
ssWriteToDataStoreWithPath ( S , _rtDW -> etejukreso ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/DataStoreWrite3"
, NULL ) ; _rtDW -> inhxdlsjhw = _rtB -> e1h02sbxw0 ;
ssWriteToDataStoreWithPath ( S , _rtDW -> kt2vs52kgo ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/DataStoreWrite1"
, NULL ) ; _rtDW -> ckq5qgg34u = _rtB -> pwtkvvgwte ;
ssWriteToDataStoreWithPath ( S , _rtDW -> legr1ngkkz ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/DataStoreWrite2"
, NULL ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( S )
) { zcEvent = rt_ZCFcn ( RISING_ZERO_CROSSING , & _rtZCE -> hpxdtrvctq , (
abswwtaokt ) ) ; if ( zcEvent != NO_ZCEVENT ) { _rtDW -> ga452ypwyn = ( _rtP
-> P_86 != 0.0F ) ; ssWriteToDataStoreWithPath ( S , _rtDW -> n5qkcfgqfz ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_pwon/DataStoreWrite1"
, NULL ) ; _rtDW -> pqgtev5dhl = _rtP -> P_87 ; ssWriteToDataStoreWithPath (
S , _rtDW -> dj152ewjo5 ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_pwon/DataStoreWrite"
, NULL ) ; _rtDW -> pnmn3fxw0t = _rtP -> P_88 ; ssWriteToDataStoreWithPath (
S , _rtDW -> ilcwodo5bh ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_pwon/DataStoreWrite2"
, NULL ) ; _rtDW -> g0ypnvmg3k = 4 ; } } tNextAdjusted = _rtB -> lfocptxalw ;
if ( ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn ( RISING_ZERO_CROSSING ,
& _rtZCE -> d0g1h1vrvn , ( tNextAdjusted ) ) ; if ( zcEvent != NO_ZCEVENT ) {
ssReadFromDataStoreWithPath ( S , _rtDW -> legr1ngkkz ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_mode_10ms/DataStoreRead2"
, NULL ) ; _rtB -> jxgqlgjchv = ( ( _rtDW -> ckq5qgg34u <= _rtP -> P_85 ) ||
_rtDW -> dm20gj5232 ) ; _rtB -> kq0a1bi4jm = _rtDW -> kl5fz2aceg + _rtP ->
P_81 ; _rtB -> ds4tpg1udl = ( ( _rtB -> kq0a1bi4jm >= _rtP -> P_82 ) || _rtDW
-> bpun4nkfds ) ; bmqjuwerbv = ! _rtB -> ds4tpg1udl ;
ssReadFromDataStoreWithPath ( S , _rtDW -> etejukreso ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_mode_10ms/DataStoreRead4"
, NULL ) ; if ( _rtDW -> dppxlo1pjb ) { murv4kynwz = _rtP -> P_84 ; } else {
murv4kynwz = _rtP -> P_84 + _rtP -> P_83 ; } _rtB -> ey3xfuixax = ( _rtDW ->
jptcqedh1l >= murv4kynwz ) ; _rtDW -> ga452ypwyn = ( _rtB -> jxgqlgjchv ||
bmqjuwerbv || _rtB -> ey3xfuixax ) ; ssWriteToDataStoreWithPath ( S , _rtDW
-> n5qkcfgqfz ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_mode_10ms/DataStoreWrite"
, NULL ) ; if ( _rtB -> ds4tpg1udl && _rtB -> ey3xfuixax ) { _rtDW ->
pnmn3fxw0t = _rtP -> P_79 ; } else { _rtDW -> pnmn3fxw0t = _rtP -> P_78 ; }
ssWriteToDataStoreWithPath ( S , _rtDW -> ilcwodo5bh ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_mode_10ms/DataStoreWrite1"
, NULL ) ; _rtDW -> dm20gj5232 = _rtB -> jxgqlgjchv ; _rtDW -> kl5fz2aceg =
_rtB -> kq0a1bi4jm ; _rtDW -> bpun4nkfds = _rtB -> ds4tpg1udl ; _rtDW ->
dppxlo1pjb = _rtB -> ey3xfuixax ; _rtDW -> fhpxyg42ch = 4 ; } } tNextAdjusted
= _rtB -> lfocptxalw ; if ( ssIsMajorTimeStep ( S ) ) { zcEvent = rt_ZCFcn (
RISING_ZERO_CROSSING , & _rtZCE -> jqqdqxlxb5 , ( tNextAdjusted ) ) ; if (
zcEvent != NO_ZCEVENT ) { ssReadFromDataStoreWithPath ( S , _rtDW ->
kt2vs52kgo ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreRead"
, NULL ) ; murv4kynwz = _rtDW -> inhxdlsjhw ; ssReadFromDataStoreWithPath ( S
, _rtDW -> emzgemsqq5 ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreRead1"
, NULL ) ; hbbmvu1ti2 = ( ( _rtDW -> atoemjnxhr * _rtDW -> km1uayiklu * _rtP
-> P_67 + _rtP -> P_66 ) + _rtDW -> atoemjnxhr * _rtDW -> atoemjnxhr * _rtDW
-> km1uayiklu * _rtP -> P_68 ) + _rtDW -> km1uayiklu * _rtDW -> km1uayiklu *
_rtDW -> atoemjnxhr * _rtP -> P_69 ; _rtB -> jbjl4bbqjp = ( murv4kynwz -
hbbmvu1ti2 ) * _rtP -> P_71 * _rtP -> P_65 + _rtDW -> atoemjnxhr ;
ssReadFromDataStoreWithPath ( S , _rtDW -> ilcwodo5bh ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreRead4"
, NULL ) ; murv4kynwz = _rtDW -> pnmn3fxw0t ; hbbmvu1ti2 /= _rtDW ->
pnmn3fxw0t ; ssReadFromDataStoreWithPath ( S , _rtDW -> n5qkcfgqfz ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreRead3"
, NULL ) ; bmqjuwerbv = _rtDW -> ga452ypwyn ; ssReadFromDataStoreWithPath ( S
, _rtDW -> legr1ngkkz ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreRead2"
, NULL ) ; _rtB -> jvkhnam4e2 = ! bmqjuwerbv ; if ( _rtB -> jvkhnam4e2 ) {
murv4kynwz = _rtDW -> ckq5qgg34u - murv4kynwz ; _rtB -> o2nx15hiem = _rtP ->
P_74 * murv4kynwz * _rtP -> P_72 + _rtDW -> kgik04xjrr ; _rtB -> fegly24dwg =
_rtP -> P_73 * murv4kynwz + _rtB -> o2nx15hiem ; _rtDW -> lxfyar3rl3 = 4 ; }
if ( bmqjuwerbv ) { murv4kynwz = _rtP -> P_64 ; } else { murv4kynwz = _rtP ->
P_61 + _rtB -> fegly24dwg ; if ( murv4kynwz > _rtP -> P_62 ) { murv4kynwz =
_rtP -> P_62 ; } else { if ( murv4kynwz < _rtP -> P_63 ) { murv4kynwz = _rtP
-> P_63 ; } } } murv4kynwz *= hbbmvu1ti2 ; if ( murv4kynwz > _rtP -> P_76 ) {
_rtDW -> pqgtev5dhl = _rtP -> P_76 ; } else if ( murv4kynwz < _rtP -> P_77 )
{ _rtDW -> pqgtev5dhl = _rtP -> P_77 ; } else { _rtDW -> pqgtev5dhl =
murv4kynwz ; } ssWriteToDataStoreWithPath ( S , _rtDW -> dj152ewjo5 ,
 "AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreWrite"
, NULL ) ; _rtDW -> atoemjnxhr = _rtB -> jbjl4bbqjp ; if ( _rtB -> jvkhnam4e2
) { _rtDW -> kgik04xjrr = _rtB -> o2nx15hiem ; } _rtDW -> br22nzqllb = 4 ; }
} } ssReadFromDataStoreWithPath ( S , _rtDW -> dj152ewjo5 ,
"AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/DataStoreRead" , NULL
) ; _rtB -> erppc1fauu = _rtDW -> pqgtev5dhl ; ssReadFromDataStoreWithPath (
S , _rtDW -> n5qkcfgqfz ,
"AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/DataStoreRead1" ,
NULL ) ; _rtB -> ghhc0nbpfp = _rtDW -> ga452ypwyn ;
ssReadFromDataStoreWithPath ( S , _rtDW -> ilcwodo5bh ,
"AbstractFuelControl_M1NFM_breach/Model 1/AF_Controller/DataStoreRead2" ,
NULL ) ; _rtB -> kj4bltkadr = _rtDW -> pnmn3fxw0t ; _rtB -> eo3k0uel35 = ( (
kytkvw2bdr * ) ssGetContStates ( S ) ) -> faoxhmxf1x ; _rtB -> fu3eouxgwn =
_rtB -> eo3k0uel35 - _rtB -> ek0daqiir2 ; _rtB -> m50p0kdswv = _rtP -> P_28 *
_rtB -> fu3eouxgwn ; _rtB -> kdqyg4ujyo = ( ( ( 0.08979 * _rtB -> n5at0j5xf2
* _rtB -> ocwsydb01a + - 0.366 ) - 0.0337 * _rtB -> ocwsydb01a * _rtB ->
n5at0j5xf2 * _rtB -> n5at0j5xf2 ) + 0.0001 * _rtB -> n5at0j5xf2 * _rtB ->
ocwsydb01a * _rtB -> ocwsydb01a ) * _rtP -> P_95 ; _rtB -> pe5bydramr = _rtP
-> P_29 * _rtB -> ocwsydb01a ; _rtB -> dk1oekplhr = _rtB -> kdqyg4ujyo / _rtB
-> ocwsydb01a ; _rtB -> l5tsewjzol = _rtP -> P_30 * _rtB -> dk1oekplhr ;
tNextAdjusted = look2_binlxpw ( _rtB -> pe5bydramr , _rtB -> l5tsewjzol ,
_rtP -> P_32 , _rtP -> P_33 , _rtP -> P_31 , _rtP -> P_96 , 5U ) ; _rtB ->
fry1kairhn = _rtP -> P_34 * tNextAdjusted ; _rtB -> fq5jqzup3u = _rtB ->
erppc1fauu ; _rtB -> i23l1cxhyu = _rtP -> P_35 * _rtB -> fq5jqzup3u ; _rtB ->
offrnf2ajl = _rtB -> fry1kairhn * _rtB -> i23l1cxhyu ; _rtB -> p3n53nfrpc = (
( kytkvw2bdr * ) ssGetContStates ( S ) ) -> dsqwnu05gu ; tNextAdjusted =
look2_binlxpw ( _rtB -> pe5bydramr , _rtB -> l5tsewjzol , _rtP -> P_38 , _rtP
-> P_39 , _rtP -> P_37 , _rtP -> P_97 , 5U ) ; _rtB -> inogd4ihax = _rtP ->
P_40 * tNextAdjusted ; _rtB -> bfhxhydtre = _rtB -> p3n53nfrpc / _rtB ->
inogd4ihax ; _rtB -> nbag1ft25y = _rtB -> offrnf2ajl + _rtB -> bfhxhydtre ;
_rtB -> lfn3antqjj = _rtB -> kdqyg4ujyo / _rtB -> nbag1ft25y ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> ncumjqptve . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> ncumjqptve . TUbufferPtrs [ 1 ] ;
real_T * * xBuffer = ( real_T * * ) & _rtDW -> ncumjqptve . TUbufferPtrs [ 2
] ; real_T simTime = ssGetT ( S ) ; real_T appliedDelay ; _rtB -> chlojd4npa
= AbstractFuelControl_M1NFM_breach_acc_rt_VTDelayfindtDInterpolate ( ( (
kytkvw2bdr * ) ssGetContStates ( S ) ) -> b5zeqedrqj , * tBuffer , * uBuffer
, * xBuffer , _rtDW -> pvijbqyclt . CircularBufSize , _rtDW -> pvijbqyclt .
Head , _rtDW -> pvijbqyclt . Tail , & _rtDW -> pvijbqyclt . Last , simTime ,
0.0 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput
( S ) == ssGetT ( S ) ) ) , _rtP -> P_42 , & appliedDelay ) ; } _rtB ->
edtstjecxw = _rtB -> chlojd4npa - _rtB -> eo3k0uel35 ; _rtB -> laqczpgktp =
_rtP -> P_43 * _rtB -> edtstjecxw ; _rtB -> cyylr31ofn = _rtP -> P_44 * _rtB
-> ocwsydb01a ; _rtB -> ew1kdyfxtu = look2_binlxpw ( _rtB -> cyylr31ofn ,
_rtB -> l5tsewjzol , _rtP -> P_46 , _rtP -> P_47 , _rtP -> P_45 , _rtP ->
P_98 , 5U ) ; _rtB -> fhe5qppnfd = _rtB -> odgjzh4qy0 - _rtB -> kdqyg4ujyo ;
_rtB -> iu5yj25t14 = _rtP -> P_48 * _rtB -> fhe5qppnfd ; _rtB -> pi1tvblhjg =
_rtP -> P_49 * _rtB -> fry1kairhn ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB
-> h0iwxu2xdg = _rtP -> P_50 ; } _rtB -> ewx0g5abdh = _rtB -> pi1tvblhjg +
_rtB -> h0iwxu2xdg ; _rtB -> orb42yv0ft = _rtB -> i23l1cxhyu * _rtB ->
ewx0g5abdh ; _rtB -> b5ih2f44fq = _rtB -> orb42yv0ft - _rtB -> bfhxhydtre ;
if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> ppf4qsuxe4 = _rtP -> P_99 ; }
_rtB -> mkenna1lxt = _rtB -> kj4bltkadr ; if ( ssIsSampleHit ( S , 1 , 0 ) )
{ _rtDW -> h0vfpqoucu = ( ssGetTaskTime ( S , 1 ) >= _rtP -> P_57 ) ; if (
_rtDW -> h0vfpqoucu == 1 ) { o43lpjacju = _rtP -> P_59 ; } else { o43lpjacju
= _rtP -> P_58 ; } _rtB -> nyf3gny3dk = ( o43lpjacju > _rtP -> P_60 ) ; if (
ssIsMajorTimeStep ( S ) ) { if ( _rtB -> nyf3gny3dk ) { if ( ! _rtDW ->
etm5fnevgk ) { ( ( gqjxvmtw0u * ) ssGetContStateDisabled ( S ) ) ->
jguowumzpr = 0 ; if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } _rtDW -> etm5fnevgk = true ; } } else { if (
_rtDW -> etm5fnevgk ) { ssSetSolverNeedsReset ( S ) ; ( ( gqjxvmtw0u * )
ssGetContStateDisabled ( S ) ) -> jguowumzpr = 1 ; switch ( _rtDW ->
enffyazcso ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
ssSetSolverNeedsReset ( S ) ; ( ( gqjxvmtw0u * ) ssGetContStateDisabled ( S )
) -> jguowumzpr = 1 ; break ; case 2 : break ; } _rtDW -> enffyazcso = - 1 ;
_rtDW -> etm5fnevgk = false ; } } } } if ( _rtDW -> etm5fnevgk ) {
rtPrevAction = _rtDW -> enffyazcso ; if ( ssIsMajorTimeStep ( S ) ) { switch
( _rtB -> ppf4qsuxe4 ) { case 1 : rtAction = 0 ; break ; case 2 : rtAction =
1 ; break ; default : rtAction = 2 ; break ; } _rtDW -> enffyazcso = rtAction
; } else { rtAction = _rtDW -> enffyazcso ; } switch ( rtAction ) { case 0 :
if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 0 ) != ssGetTStart
( S ) ) { ssSetSolverNeedsReset ( S ) ; } } if ( ssIsSampleHit ( S , 1 , 0 )
) { _rtB -> jizfbof0wf = _rtP -> P_51 ; } _rtB -> kzhcriujsz = _rtB ->
puwxndtiqx / _rtB -> mkenna1lxt ; _rtB -> nza32deirt = _rtB -> kzhcriujsz -
_rtB -> jizfbof0wf ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW ->
jhbpz1ucig ) ; } break ; case 1 : if ( rtAction != rtPrevAction ) { ( (
gqjxvmtw0u * ) ssGetContStateDisabled ( S ) ) -> jguowumzpr = 0 ; if (
ssGetTaskTime ( S , 0 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> avikbhwnbr = _rtP -> P_52
; } _rtB -> pbqiweufty = ( ( kytkvw2bdr * ) ssGetContStates ( S ) ) ->
jguowumzpr ; _rtB -> kiodwghiiy = _rtB -> pbqiweufty / _rtB -> avikbhwnbr ;
_rtB -> dpkhfwlifs = _rtB -> puwxndtiqx - _rtB -> mkenna1lxt ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW -> mgnnayzozq = ( ssGetTaskTime ( S , 1
) >= _rtP -> P_54 ) ; if ( _rtDW -> mgnnayzozq == 1 ) { _rtB -> an2rbmuvtp =
_rtP -> P_56 ; } else { _rtB -> an2rbmuvtp = _rtP -> P_55 ; } } _rtB ->
no4o1knyjd = _rtB -> dpkhfwlifs * _rtB -> dpkhfwlifs * _rtB -> an2rbmuvtp ;
tNextAdjusted = _rtB -> kiodwghiiy ; if ( ssIsMajorTimeStep ( S ) ) { if (
_rtDW -> mgy1zaa4ya != 0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW ->
mgy1zaa4ya = 0 ; } _rtB -> ecshjnsfs3 = muDoubleScalarSqrt ( _rtB ->
kiodwghiiy ) ; } else { if ( _rtB -> kiodwghiiy < 0.0 ) { _rtB -> ecshjnsfs3
= - muDoubleScalarSqrt ( muDoubleScalarAbs ( _rtB -> kiodwghiiy ) ) ; } else
{ _rtB -> ecshjnsfs3 = muDoubleScalarSqrt ( _rtB -> kiodwghiiy ) ; } if (
tNextAdjusted < 0.0 ) { _rtDW -> mgy1zaa4ya = 1 ; } } if ( ssIsMajorTimeStep
( S ) ) { srUpdateBC ( _rtDW -> oo1oerf1jj ) ; } break ; case 2 : break ; }
if ( _rtB -> ppf4qsuxe4 == 1 ) { _rtB -> n2ye5zhcak = _rtB -> nza32deirt ; }
else { _rtB -> n2ye5zhcak = _rtB -> ecshjnsfs3 ; } if ( ssIsMajorTimeStep ( S
) ) { srUpdateBC ( _rtDW -> lmgc31bxj5 ) ; } } ssCallAccelRunBlock ( S , 22 ,
2 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> l5hy1mlg42 = _rtB -> ghhc0nbpfp ;
ssCallAccelRunBlock ( S , 22 , 4 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 22 , 5 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 22 , 6 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 22 , 7 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 22 , 8 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 22 , 9 , SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER (
tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { ph1nm0us43 * _rtB ;
dcl0awcq00 * _rtP ; m2i0d1iib5 * _rtDW ; _rtDW = ( ( m2i0d1iib5 * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( dcl0awcq00 * ) ssGetDefaultParam ( S ) )
; _rtB = ( ( ph1nm0us43 * ) _ssGetBlockIO ( S ) ) ; { real_T * * uBuffer = (
real_T * * ) & _rtDW -> ncumjqptve . TUbufferPtrs [ 0 ] ; real_T * * tBuffer
= ( real_T * * ) & _rtDW -> ncumjqptve . TUbufferPtrs [ 1 ] ; real_T * *
xBuffer = ( real_T * * ) & _rtDW -> ncumjqptve . TUbufferPtrs [ 2 ] ; real_T
simTime = ssGetT ( S ) ; real_T appliedDelay ; appliedDelay = _rtB ->
ew1kdyfxtu ; if ( appliedDelay > _rtP -> P_41 ) { appliedDelay = _rtP -> P_41
; } _rtDW -> pvijbqyclt . Head = ( ( _rtDW -> pvijbqyclt . Head < ( _rtDW ->
pvijbqyclt . CircularBufSize - 1 ) ) ? ( _rtDW -> pvijbqyclt . Head + 1 ) : 0
) ; if ( _rtDW -> pvijbqyclt . Head == _rtDW -> pvijbqyclt . Tail ) { if ( !
AbstractFuelControl_M1NFM_breach_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> pvijbqyclt . CircularBufSize , & _rtDW -> pvijbqyclt . Tail , & _rtDW ->
pvijbqyclt . Head , & _rtDW -> pvijbqyclt . Last , simTime - _rtP -> P_41 ,
tBuffer , uBuffer , xBuffer , ( boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW ->
pvijbqyclt . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"vtdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
pvijbqyclt . Head ] = simTime ; ( * uBuffer ) [ _rtDW -> pvijbqyclt . Head ]
= _rtB -> lfn3antqjj ; ( * xBuffer ) [ _rtDW -> pvijbqyclt . Head ] = ( (
kytkvw2bdr * ) ssGetContStates ( S ) ) -> b5zeqedrqj ; } if ( _rtDW ->
etm5fnevgk && ( _rtDW -> enffyazcso == 1 ) ) { } UNUSED_PARAMETER ( tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { ph1nm0us43 * _rtB ; dcl0awcq00
* _rtP ; kytkvw2bdr * _rtX ; mvgtdhrln1 * _rtXdot ; m2i0d1iib5 * _rtDW ;
_rtDW = ( ( m2i0d1iib5 * ) ssGetRootDWork ( S ) ) ; _rtXdot = ( ( mvgtdhrln1
* ) ssGetdX ( S ) ) ; _rtX = ( ( kytkvw2bdr * ) ssGetContStates ( S ) ) ;
_rtP = ( ( dcl0awcq00 * ) ssGetDefaultParam ( S ) ) ; _rtB = ( ( ph1nm0us43 *
) _ssGetBlockIO ( S ) ) ; { ( ( mvgtdhrln1 * ) ssGetdX ( S ) ) -> f0uysuxxc1
= _rtB -> m50p0kdswv ; } _rtXdot -> gxzm0c403c = 0.0 ; _rtXdot -> gxzm0c403c
+= _rtP -> P_9 * _rtX -> gxzm0c403c ; _rtXdot -> gxzm0c403c += ( ( f11gk4xn5j
* ) ssGetU ( S ) ) -> m1ugc53fgm ; { ( ( mvgtdhrln1 * ) ssGetdX ( S ) ) ->
mphig5gmgs = _rtB -> iu5yj25t14 ; } { ( ( mvgtdhrln1 * ) ssGetdX ( S ) ) ->
faoxhmxf1x = _rtB -> laqczpgktp ; } { ( ( mvgtdhrln1 * ) ssGetdX ( S ) ) ->
dsqwnu05gu = _rtB -> b5ih2f44fq ; } { real_T instantDelay ; instantDelay =
_rtB -> ew1kdyfxtu ; if ( instantDelay > _rtP -> P_41 ) { instantDelay = _rtP
-> P_41 ; } if ( instantDelay < 0.0 ) { ( ( mvgtdhrln1 * ) ssGetdX ( S ) ) ->
b5zeqedrqj = 0 ; } else { ( ( mvgtdhrln1 * ) ssGetdX ( S ) ) -> b5zeqedrqj =
1.0 / instantDelay ; } } if ( _rtDW -> etm5fnevgk ) { ( ( mvgtdhrln1 * )
ssGetdX ( S ) ) -> jguowumzpr = 0.0 ; if ( _rtDW -> enffyazcso == 1 ) { { ( (
mvgtdhrln1 * ) ssGetdX ( S ) ) -> jguowumzpr = _rtB -> no4o1knyjd ; } } }
else { ( ( mvgtdhrln1 * ) ssGetdX ( S ) ) -> jguowumzpr = 0.0 ; } }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { ph1nm0us43 * _rtB ;
dcl0awcq00 * _rtP ; l3aslnucdt * _rtZCSV ; m2i0d1iib5 * _rtDW ; _rtDW = ( (
m2i0d1iib5 * ) ssGetRootDWork ( S ) ) ; _rtZCSV = ( ( l3aslnucdt * )
ssGetSolverZcSignalVector ( S ) ) ; _rtP = ( ( dcl0awcq00 * )
ssGetDefaultParam ( S ) ) ; _rtB = ( ( ph1nm0us43 * ) _ssGetBlockIO ( S ) ) ;
_rtZCSV -> hojmmrdgoa = _rtB -> iqivgceeqj - _rtP -> P_12 ; _rtZCSV ->
a55gmch0gw = _rtB -> iqivgceeqj - _rtP -> P_13 ; _rtZCSV -> e230grztni = ( (
f11gk4xn5j * ) ssGetU ( S ) ) -> ienofsir3m - _rtP -> P_14 ; _rtZCSV ->
bc4dpqnezi = ( ( f11gk4xn5j * ) ssGetU ( S ) ) -> ienofsir3m - _rtP -> P_15 ;
_rtZCSV -> lwerqr2omh = ssGetT ( S ) - _rtP -> P_17 ; if ( _rtB -> pnoduxvqg5
< _rtB -> nl4lofzxqk ) { if ( _rtDW -> jrenr0quvo == 0 ) { _rtZCSV ->
k3kqa2lgs5 = _rtB -> pnoduxvqg5 - _rtB -> pnoduxvqg5 ; } else { _rtZCSV ->
k3kqa2lgs5 = _rtB -> pnoduxvqg5 - _rtB -> nl4lofzxqk ; } } else if ( _rtDW ->
jrenr0quvo == 0 ) { _rtZCSV -> k3kqa2lgs5 = _rtB -> nl4lofzxqk - _rtB ->
pnoduxvqg5 ; } else { _rtZCSV -> k3kqa2lgs5 = _rtB -> nl4lofzxqk - _rtB ->
nl4lofzxqk ; } _rtZCSV -> k2yzyzkleb = _rtB -> dyxtbj4z2s - _rtP -> P_23 ;
_rtZCSV -> esjkmmddit = _rtB -> bq2ygt10h0 ; _rtZCSV -> lwwvz1g53l = ssGetT (
S ) - _rtP -> P_0 ; _rtZCSV -> c5zwuxhpn5 = ssGetT ( S ) - _rtP -> P_57 ; if
( _rtDW -> etm5fnevgk ) { { ( ( l3aslnucdt * ) ssGetSolverZcSignalVector ( S
) ) -> jrkr34d33h = 0.0 ; } if ( _rtDW -> enffyazcso == 1 ) { _rtZCSV ->
jrkr34d33h = ssGetT ( S ) - _rtP -> P_54 ; } } else { { ( ( l3aslnucdt * )
ssGetSolverZcSignalVector ( S ) ) -> jrkr34d33h = 0.0 ; } } } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 299906412U
) ; ssSetChecksumVal ( S , 1 , 3326391545U ) ; ssSetChecksumVal ( S , 2 ,
2693444511U ) ; ssSetChecksumVal ( S , 3 , 3435519057U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "8.5" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( m2i0d1iib5 ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( ph1nm0us43 ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofU ( S ) != sizeof
( f11gk4xn5j ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal ExternalInputs sizes do "
"not match for accelerator mex file." ) ; ssSetErrorStatus ( S , msg ) ; } if
( ssGetSizeofY ( S ) != sizeof ( p1nzsf5soq ) ) { static char msg [ 256 ] ;
sprintf ( msg , "Unexpected error: Internal ExternalOutputs sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
dcl0awcq00 ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & l4w3hnds0m ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; ( (
dcl0awcq00 * ) ssGetDefaultParam ( S ) ) -> P_62 = rtInfF ; } static void
mdlInitializeSampleTimes ( SimStruct * S ) { } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
