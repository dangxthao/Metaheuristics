#include "__cf_KD_cl_harness_forthao_breach.h"
#ifndef RTW_HEADER_KD_cl_harness_forthao_breach_h_
#define RTW_HEADER_KD_cl_harness_forthao_breach_h_
#include <stddef.h>
#include <string.h>
#include "rtw_modelmap.h"
#ifndef KD_cl_harness_forthao_breach_COMMON_INCLUDES_
#define KD_cl_harness_forthao_breach_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "KD_cl_harness_forthao_breach_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_look1d32.h"
#include "rt_look2d32_normal.h"
#include "rt_look32.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#define MODEL_NAME KD_cl_harness_forthao_breach
#define NSAMPLE_TIMES (6) 
#define NINPUTS (2)       
#define NOUTPUTS (1)     
#define NBLOCKIO (185) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (8)   
#elif NCSTATES != 8
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T e2b5x1uxlg ; } mbkhwxmspr ; typedef struct { int8_T
ld1fjkwy01 ; } dosiyf2ryn ; typedef struct { real_T odrmud5052 ; } g4kb1dhx4k
; typedef struct { real_T afjuedjd2w ; real_T akpttb2uyr ; } jcvtjjdhjy ;
typedef struct { real_T ezgferlgph ; real_T ndwlmk3bzn ; real_T nfipgrtuvr ;
real_T ehhntoamo3 ; real_T glxqot4hmc ; real_T nucdgci0rr ; real_T gwkex5211t
; real_T psdqponccq [ 2 ] ; real_T p2d41sdffb [ 2 ] ; real_T i45enf1q3e ;
real_T ixoqjsjjol ; real_T gurfdczwyr ; real_T pe0kzgwhkx ; real_T mnmkwbcoth
; real_T eh3nc1dwbh ; real_T gpulvfhg1s ; real_T ixod0recqg ; real_T
ptmfmdqmdu ; real_T jg43ge1e1q ; real_T eyyzffon51 ; real_T jaeao5tvyt ;
real_T db3aloisol ; real_T jjsej1qngo ; real_T duoa5br5cp ; real_T awinecmsma
[ 3 ] ; real_T bxv0vvreuu [ 3 ] ; real_T crgbyrrs3v ; real_T m2zzbwcwm4 [ 2 ]
; real_T emjllewz5k [ 3 ] ; real_T aisp4eno0x [ 2 ] ; real_T ji51d50do5 [ 2 ]
; real_T leav20jvu1 ; real_T ohwrf1raz0 ; real_T ejc4fyifu5 ; real_T
pfzxy051h0 ; real_T ikbnonbcrn ; real_T pl42gnrwz2 ; real_T bfvor2h2qz ;
real_T e1xcvnjj5g ; real_T loievit34u ; real_T eplj1scayr ; real_T b54muslow1
; real_T oe0tyrtgj3 ; real_T jkv43wgavw ; real_T cuwv2nwel5 ; real_T
py5osja1pm ; real_T fto5rqjonq ; real_T ndy320v1c1 ; real_T kdbgmjpooy ;
real_T ivmstlzdxm ; real_T bxgw3kq3ij ; real32_T cwsbtrwpfc ; real32_T
ffjdcznvkg ; real32_T itsvvwrq0a ; real32_T ljk4xix01m ; real32_T eiwdrfcxnn
; real32_T m3qm5dlk4i ; real32_T apexfxt05y ; real32_T evxrp31n1t ; real32_T
ksaqwiryhv ; real32_T faswnrxfir [ 13 ] ; real32_T j0uztscc4c ; real32_T
fllsdcflzq ; real32_T ir10qbb2h0 ; real32_T lgha5fyofj ; real32_T lj0vvkbxsr
; real32_T m5uqx1qg4p ; real32_T jofwokwi4b ; real32_T jendnkkere ; real32_T
jnglkal4bm ; real32_T btjw2bwujo ; real32_T asokdz5ql3 ; real32_T dtnj1tjnn0
; real32_T lsc4svyhjg ; real32_T epaoao0ex4 ; real32_T kzspe3uhcs [ 3 ] ;
real32_T cjbmrximrw ; real32_T dlanmxddxv ; real32_T pidy302dbb ; real32_T
cqzg3fjzex ; real32_T ompjonegnn ; real32_T kmhklseyi0 ; real32_T lz1xovijdz
; real32_T o2frmjlatg ; real32_T dkpngqys4z ; real32_T h2ldtsrohl ; real32_T
ittbcftddk ; real32_T ighfnj0qfi ; real32_T cdx14uwqgo ; real32_T e3xygmo5lb
; real32_T ghtnph5m13 ; real32_T nkcobpyvlo ; real32_T gyr32rwmec ; real32_T
oknjoatyhh ; real32_T fnbokrjfka ; real32_T hwqwznwhbl ; real32_T lvfxs442og
; real32_T eem54jmxca ; real32_T c0a55ctkeh ; real32_T gj05xuhqyp ; real32_T
fnoycnzxjt ; real32_T jtmcug05p1 ; real32_T lmosmreh2j ; real32_T eq5k4gzitz
; real32_T f1zcecdgrp ; real32_T pik2cpjozq ; real32_T nslfibkrov ; real32_T
l4ddhp1s2y ; real32_T m3gtxwsewc ; real32_T gyejnsfev5 ; real32_T eacys0hvzp
; real32_T fokzlm1wwg ; real32_T eu3n5piaim [ 3 ] ; real32_T moobo5rhbx ;
real32_T mmuzqgowqh ; real32_T ludldegbkb ; real32_T pvsewex5ju ; real32_T
gcx1li42yu ; real32_T bggc12g3ce ; real32_T lqzoneosua ; real32_T gy1swsl5lp
; real32_T dwx51vir01 [ 2 ] ; real32_T luidd34yzh ; real32_T g1n35fyh1r ;
real32_T novvn2g13i ; real32_T gl0e32zavt ; real32_T f25tnd03zw ; real32_T
lhab5ae5gp ; real32_T fmwv0d4znx ; real32_T ntcwr4dn2u ; real32_T kwlj023pby
; real32_T n2jcapcy4z ; real32_T jzzd4u2sum ; real32_T pqqblejffn ; real32_T
ass1bqlzd1 ; real32_T mr2jn5bxm5 ; real32_T pobddrevcj ; real32_T nkv11cjkkg
; real32_T nskmznxef3 ; real32_T g3lqrwkn4j ; real32_T lmhrkqqsla ; real32_T
mc4y1a4y4j ; real32_T hf2zl0mcd2 ; real32_T kxt1uasxmv ; real32_T iw1ygflm02
; real32_T kbfvhn1zpd ; real32_T jdtbjg2wuq ; real32_T iu2eoz2dfq ; real32_T
nuic2wdm4g ; real32_T mnaji2ovrg ; real32_T ixrjwgdohx ; real32_T fnzk1kwery
[ 3 ] ; real32_T dzd1zqtqmx [ 3 ] ; real32_T modanr3tbz ; real32_T hpemxq4evt
; real32_T ppjeb0koux ; real32_T gkalf2lwvh ; real32_T iqpuylkhd5 ; real32_T
kaoklhu34x ; real32_T lxrst0kqri ; real32_T i1qmymrrth ; real32_T cgkybpq2my
; real32_T dtn0co1rlo ; real32_T mebfpuov3e [ 3 ] ; real32_T hc4pbn1ftr ;
real32_T lluxiqhlvi ; real32_T o3l2mqkjgp ; real32_T dmnianvpym ; real32_T
ilgb03fx1o ; real32_T arhywgn0ud [ 2 ] ; real32_T g0gsnsbc3h ; real32_T
gzcrpdyase ; real32_T eznht2b1xz ; real32_T a5xydgx2md ; real32_T arcts1reys
; int32_T g1hxajyvoh ; int32_T dgqpk3ff5k ; boolean_T aebqkvtnky ; g4kb1dhx4k
lwrmmrtmge ; g4kb1dhx4k cdbewnv5xj ; g4kb1dhx4k masm1qwyo5u ; mbkhwxmspr
haonxcq3pb ; mbkhwxmspr b5mifpqvp3 ; mbkhwxmspr eso2sg3fe3 ; mbkhwxmspr
k511l1m2xq ; } B ; typedef struct { real_T cc0wkfbxf2 ; real_T eac1jvpkom ;
real_T h1201vgmm4 ; real_T beiefj4kfo ; real_T d2tl5o0hel ; struct { void *
TimePtr ; void * DataPtr ; void * RSimInfoPtr ; } hvzkbecm4i ; struct { void
* TimePtr ; void * DataPtr ; void * RSimInfoPtr ; } b2ezf5nkn2 ; struct {
void * TimePtr ; void * DataPtr ; void * RSimInfoPtr ; } dlyfy0ipc5 ; struct
{ void * TimePtr ; void * DataPtr ; void * RSimInfoPtr ; } oi2egj2zap ;
struct { void * SignalProbe ; } jllpsh2lx2 ; struct { void * SignalProbe ; }
kjuost3l4t ; struct { void * SignalProbe ; } gegk3zt5rh ; struct { void *
SignalProbe ; } br3dyaxwzn ; struct { void * SignalProbe ; } msk43x33qs ;
struct { void * SignalProbe ; } aiqcj0xpj3 ; struct { void * SignalProbe ; }
imyl4toc4j ; struct { void * SignalProbe ; } juk00hf1bn ; struct { void *
SignalProbe ; } prcjjqdyp5 ; struct { void * SignalProbe ; } llq51al0ac ;
struct { void * SignalProbe ; } iz4q3uhlvz ; struct { void * LoggedData ; }
o02f1axwt1 ; struct { void * LoggedData ; } etcffifed1 ; struct { void *
LoggedData ; } cgvchy4rjz ; struct { void * LoggedData ; } ecx5etklyp ;
struct { void * LoggedData ; } n4gmz4j4hp ; struct { void * LoggedData ; }
cjtu2gvfu3 ; struct { void * LoggedData ; } kd250x2sgg ; struct { void *
LoggedData ; } cmlxapjojl ; struct { void * LoggedData ; } fdbzhbhm5w ;
struct { void * LoggedData ; } j2kd5bha4b ; struct { void * LoggedData ; }
jcasi5loyb ; struct { void * LoggedData ; } lscu5irxwr ; struct { void *
LoggedData ; } hnhslp1bvt ; struct { void * LoggedData ; } moxm2bblwy ;
struct { void * LoggedData ; } auoyy55qok ; struct { void * LoggedData ; }
pd2fs1ditr ; struct { void * LoggedData ; } lyifwmtiaf ; struct { void *
LoggedData ; } n2no12labo ; struct { void * LoggedData ; } jhwi52suok ;
struct { void * LoggedData ; } iesioivz5z ; struct { void * LoggedData ; }
jhe31dgiau ; struct { void * LoggedData ; } ojkakflagz ; struct { void *
TimePtr ; void * DataPtr ; void * RSimInfoPtr ; } alrdv1eret ; struct { void
* TimePtr ; void * DataPtr ; void * RSimInfoPtr ; } p1e0b0rkdr ; struct {
void * TimePtr ; void * DataPtr ; void * RSimInfoPtr ; } clwukip414 ; struct
{ void * SignalProbe ; } dcyih1kpjy ; struct { void * LoggedData ; }
bdj3wmcbnu ; struct { void * TimePtr ; void * DataPtr ; void * RSimInfoPtr ;
} d5tz0vp4gc ; struct { void * TimePtr ; void * DataPtr ; void * RSimInfoPtr
; } ozs1urzqbb ; struct { void * TimePtr ; void * DataPtr ; void *
RSimInfoPtr ; } jfbqvyxdrm ; real32_T avtbwzqnkf [ 2 ] ; real32_T poa5fptxm4
; real32_T bsbxmlf10r ; real32_T pybwwu5s4d ; real32_T j5f3ay4xaq ; real32_T
ackerqxqlr ; real32_T c1qvpfpyqu ; real32_T em10zry3vm ; real32_T cz55ow2si1
[ 3 ] ; real32_T h4gbii3cbq ; real32_T o04t4yciip ; real32_T lzwd5z4dbk ;
real32_T dgfekwwlr1 ; real32_T dw2dt5amj1 ; real32_T letoggxozl ; real32_T
frjwyakiph ; real32_T i5yn1movmy ; real32_T diffnla35e ; real32_T nqyjhyuvcj
; real32_T fjcoqtw2bx ; real32_T iggiejtmqu ; real32_T mvpjwhrzk3 ; real32_T
mtqhixagy1 ; real32_T fhgbtmls3d ; real32_T l1sigmyvxe ; real32_T noqny2ee14
; real32_T ljbykua013 ; real32_T owlkbndpg5 ; real32_T gme5mt5rhg ; real32_T
ehd3s5jupn ; int32_T n4b14msae2 ; real32_T dpjpy2bpgy ; real32_T nqvcv4lcej ;
real32_T mi05525rde ; real32_T gsy0d3xgez ; real32_T owcamicoch ; real32_T
o0hytehsup ; real32_T pelseog20p ; real32_T nhrhyjvls4 ; real32_T oobzxswkpo
; real32_T l0b5hroyaj ; real32_T fuwbxjmtyy ; real32_T nq1n5qxeyp ; real32_T
b5t1avpqna ; real32_T ocojyks2sz ; real32_T ntmupcyyck ; real32_T devn1wdclr
; real32_T ktweu3wugd ; real32_T o3z1jsmhkx ; real32_T hptuorf3i3 ; real32_T
nlpxiel2sg ; real32_T n5tosor5b5 ; real32_T n5pkawvqdo ; real32_T c1deueau4e
; real32_T mi5h1pks4n ; real32_T bvlm5joqvj ; real32_T kk4xei3vwx ; real32_T
nwf1nud1fv ; real32_T mjfdrfawoz ; real32_T oe1xcqtj2h ; real32_T i5n35h2hi0
; real32_T gj1id4inx4 ; real32_T ar2qj33owm ; real32_T bakpq4fzl0 ; real32_T
enudnf03vn ; real32_T gd2xytkseo ; real32_T axunmck3pg ; real32_T estlkslffw
; real32_T gzmuaempqp ; real32_T pwwmab3rlr ; real32_T e10toipvv0 ; real32_T
hyhv0echnn ; real32_T gmsrqeat5h ; real32_T aupt3qrz3y ; real32_T jnju4d4o03
; real32_T bpo1eig15d ; real32_T fgc3q11l1t ; real32_T eppk3q2xfh ; real32_T
dpzir5hccd ; real32_T ayjpjfupkc ; real32_T d210tl5n23 ; real32_T moioiyooa5
; real32_T a1ts5brulz ; real32_T lqempabukg ; real32_T ecauzxzkhl ; real32_T
fllyhv1jnh ; real32_T ok4jtsn4bb ; real32_T pmewcnpxdb ; real32_T dhb1ak5ywv
; real32_T psebtvzqlm ; int32_T fnhncveveb ; uint32_T msu4qgbkxt ; uint32_T
grioepryal ; struct { int_T PrevIndex ; } bfsa3u0wlu ; struct { int_T
PrevIndex ; } h4uocsxftg ; struct { int_T PrevIndex ; } fwkxoupfre ; struct {
int_T PrevIndex ; } fb1c24lf0o ; struct { int_T PrevIndex ; } khael42orb ;
struct { int_T PrevIndex ; } bi4mdaymdj ; struct { int_T PrevIndex ; }
d1tbd3ecab ; struct { int_T PrevIndex ; } aloadsnzst ; struct { int_T
PrevIndex ; } fzvbkpkm44 ; struct { int_T PrevIndex ; } gyhzvvm031 ; int8_T
ljedkvx4od ; int8_T hfnjefvf2v ; int8_T kl21dgjfyi ; int8_T lb2gtdwzqd ;
int8_T hpc0grqivr ; int8_T loepcnnuit ; int8_T o0fqt141qd ; int8_T h3vqcmc1hz
; int8_T pqpqjda5is ; int8_T bwmwpnvwlf ; int8_T hf2ukkb54z ; int8_T
dp2wxggv2y ; int8_T ifikoeohu4 ; int8_T fb2jmsx45b ; int8_T gu2pk5utpz ;
int8_T m1sbzn2h1n ; int8_T ewylvoz5wx ; int8_T bzt2b4vlgj ; int8_T p5cjuriyjr
; int8_T klgivly02z ; int8_T nlyldhhvyb ; int8_T k1yann3ya5 ; int8_T
bubafrutom ; int8_T ltvu2oc3sf ; int8_T li2ivnnt0t ; int8_T ae1e1itbfy ;
int8_T dhx34gepf4 ; int8_T p2atyilds3 ; int8_T edw2mgcvx1 ; int8_T n4uikvdjac
; int8_T chxryck3fg ; int8_T dl0glhtqdr ; int8_T adcpzgniuv ; int8_T
ismm4u0kis ; int8_T kct4avkdgo ; int8_T ljqu2i52fc ; int8_T lpg4z3lelv ;
int8_T ombi11gse3 ; int8_T igzqf1qklf ; int8_T moze4hcv5c ; int8_T kuzwdhnrip
; int8_T a1axcz0kbn ; int8_T j4ymuqubrw ; int8_T kymzzotg2g ; int8_T
maiimsnqs5 ; int8_T dyx4tug5h3 ; int8_T cr2kibgo2j ; int8_T pwlmqo3nxm ;
int8_T guuziano0t ; int8_T l12omsu2tn ; int8_T o2zj3fqza1 ; int8_T m3gfat1ui0
; int8_T dk3vj22y05 ; int8_T o3c1lu15ny ; int8_T j45e0raewi ; int8_T
o3wc5wwa4p ; int8_T irsxloeepq ; int8_T cp3q1at4o2 ; int8_T pce44vep3x ;
int8_T mee1wioe1r ; int8_T a5nvnya1oe ; int8_T dfax004odl ; int8_T mwuspmm2e1
; int8_T jgu1xgjxem ; int8_T my15ghhvb1 ; int8_T bcd3kgenub ; int8_T
f5k2rzim4a ; int8_T nx3flbvahx ; int8_T lik1wotc2i ; int8_T gg02mzoxhc ;
int8_T gwxpzomgjh ; int8_T etxqofccji ; int8_T ljwb0xnabb ; int8_T ivkldwkotp
; int8_T hypqqzrtox ; int8_T kqdf0adzeb ; int8_T gdpkwnqxlj ; int8_T
ozyefxkqtm ; int8_T dqd4zebieo ; int8_T awpbtqxcnq ; int8_T l4mofmlly2 ;
int8_T kltb44md1r ; int8_T g0pejldppu ; int8_T oqqlpwtggt ; int8_T hgwa21u3tp
; uint8_T dvtr5mddec ; jcvtjjdhjy lwrmmrtmge ; jcvtjjdhjy cdbewnv5xj ;
jcvtjjdhjy masm1qwyo5u ; dosiyf2ryn gmyvhhtxia ; dosiyf2ryn pg1kwe2jsoh ; }
DW ; typedef struct { real_T mupnfilrqo ; real_T huyhg2ps31 ; real_T
lgbs44xptg ; real_T ka43gmkysq ; real_T iqp0o3u0ph ; real_T iynqfp2xbi ;
real_T cgw3asjtrv ; real_T ge52s03ms5 ; } X ; typedef struct { real_T
mupnfilrqo ; real_T huyhg2ps31 ; real_T lgbs44xptg ; real_T ka43gmkysq ;
real_T iqp0o3u0ph ; real_T iynqfp2xbi ; real_T cgw3asjtrv ; real_T ge52s03ms5
; } XDot ; typedef struct { boolean_T mupnfilrqo ; boolean_T huyhg2ps31 ;
boolean_T lgbs44xptg ; boolean_T ka43gmkysq ; boolean_T iqp0o3u0ph ;
boolean_T iynqfp2xbi ; boolean_T cgw3asjtrv ; boolean_T ge52s03ms5 ; } XDis ;
typedef struct { real_T mupnfilrqo ; real_T huyhg2ps31 ; real_T lgbs44xptg ;
real_T ka43gmkysq ; real_T iqp0o3u0ph ; real_T iynqfp2xbi ; real_T cgw3asjtrv
; real_T ge52s03ms5 ; } CStateAbsTol ; typedef struct { real_T ch4dzb1x4i ;
real_T gm151yhz1l ; } ExtU ; typedef struct { real_T f2pqowb0h2 ; } ExtY ;
typedef struct { rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct
ev5xuv0chq_ { real_T UnitDelay_InitialCondition ; real_T
RateLimiter_RisingLim ; real_T RateLimiter_FallingLim ; real_T RateLimiter_IC
; } ; struct P_ { real_T Constant2_Value ; real_T Constant1_Value ; real_T
SliderGain_Gain ; real_T Constant_Value ; real_T SliderGain_Gain_fxl4cn0nhs ;
real_T Saturation1_UpperSat ; real_T Saturation1_LowerSat ; real_T
Switch1_Threshold ; real_T Saturation_UpperSat ; real_T Saturation_LowerSat ;
real_T Gain2_Gain ; real_T tokgps1_Gain ; real_T Gain_Gain ; real_T
Saturation1_UpperSat_f1otdzijdo ; real_T Saturation1_LowerSat_cp0nvaxf44 ;
real_T Switch1_Threshold_l55imt4c03 ; real_T Saturation_UpperSat_c3vbgn0h23 ;
real_T Saturation_LowerSat_oqjcpbpiw2 ; real_T Gain2_Gain_euknr0ejrc ; real_T
tokgps1_Gain_ieeppbarz5 ; real_T Saturation1_UpperSat_b4sddjbmu4 ; real_T
Saturation1_LowerSat_jzbybanmuo ; real_T Switch1_Threshold_poxw0fzcvi ;
real_T Saturation_UpperSat_nesqhf0mrq ; real_T Saturation_LowerSat_fuvtfoywaf
; real_T Gain2_Gain_dnatce3asn ; real_T Gain2_Gain_giae1yyt3d ; real_T
Gain_Gain_lblkibiobo ; real_T Saturation1_UpperSat_l5pty0i0ge ; real_T
Saturation1_LowerSat_ov30a1gada ; real_T Switch1_Threshold_azwyz32q30 ;
real_T Saturation_UpperSat_dzsaidwyzg ; real_T Saturation_LowerSat_l1bt303gva
; real_T Gain2_Gain_ovbataovg4 ; real_T Gain2_Gain_i3ytcncqtp ; real_T
b_2_1_Gain ; real_T s_1_Gain ; real_T a_2_1_Gain ; real_T a_3_1_Gain ; real_T
Integrator1_IC ; real_T Integrator2_IC ; real_T Gain2_Gain_ldmywfqo5l ;
real_T Memory_X0 ; real_T Ra_Value ; real_T Memory_X0_h1tbtxp2t3 ; real_T
Gain_Gain_nhdxkrws3j ; real_T FromWorkspace1_Time0 [ 24166 ] ; real_T
FromWorkspace1_Data0 [ 24166 ] ; real_T Saturation1_UpperSat_fkuqqwyy3e ;
real_T Saturation1_LowerSat_pr4ywobu3p ; real_T FromWorkspace3_Time0 [ 24166
] ; real_T FromWorkspace3_Data0 [ 24166 ] ; real_T
Saturation_UpperSat_drcjljjkd1 ; real_T Saturation_LowerSat_bfxwgbinrc ;
real_T Gain7_Gain ; real_T conversiontoRPM_Gain ; real_T Gain1_Gain ; real_T
Constant4_Value ; real_T Constant3_Value [ 9 ] ; real_T Constant5_Value [ 18
] ; real_T Constant9_Value ; real_T Gain1_Gain_k3z2xphv3w ; real_T
Constant1_Value_dtwovyy2kg ; real_T Gain_Gain_bgx0ie0qw3 ; real_T
Gain1_Gain_gsz2kuibzm ; real_T Constant6_Value ; real_T
Constant2_Value_jilhapm4hi [ 9 ] ; real_T Constant7_Value [ 18 ] ; real_T
Constant8_Value ; real_T Constant1_Value_p5hzjcc2mh ; real_T Switch_Threshold
; real_T Saturation1_UpperSat_ed2d1dsvvu ; real_T
Saturation1_LowerSat_n0bdrwhesa ; real_T FromWorkspace11_Time0 ; real_T
FromWorkspace11_Data0 ; real_T p_prethrottlekPa1_IC ; real_T
FromWorkspace12_Time0 ; real_T FromWorkspace12_Data0 ; real_T
Integrator1_IC_mhqedcm0z1 ; real_T conversiontoRPM_Gain_aifzn4wkiq ; real_T
Constant_Value_gwpofekbsw ; real_T Constant3_Value_jcaewg4fcb ; real_T
Constant4_Value_kguicwhsfv ; real_T Constant1_Value_ar1vpqpi0c ; real_T
Constant2_Value_jsvh2omtfu ; real_T Constant5_Value_blirrlxqgk [ 12 ] ;
real_T Constant6_Value_bzlxiqld1i [ 9 ] ; real_T Gain2_Gain_atufxtbbsi ;
real_T Integrator_IC ; real_T R_air1_Gain ; real_T Gain3_Gain ; real_T
Gain4_Gain ; real_T conversiontoRPM_Gain_hamejm3o4p ; real_T
Integrator_IC_heumtkcm2e ; real_T R_air_Gain ; real_T
Constant_Value_g3u4sx54dp ; real_T Constant1_Value_lma0kogrsm ; real_T
Constant2_Value_ph0axwg3ul [ 6 ] ; real_T Gain_Gain_dlhxvjf4sb ; real_T
n1_Gain ; real_T n2_Gain ; real_T Saturation_UpperSat_awfrwwo30m ; real_T
Saturation_LowerSat_ggypqh2rl4 ; real_T n3_Gain ; real_T
Gain1_Gain_kphh4wmlkt ; real_T Gain5_Gain ; real_T Constant3_Value_jljz3p1fkf
[ 4 ] ; real_T conversiontoRPM_Gain_jcb4d3q1ao ; real_T Gain6_Gain ; real_T
Integrator_IC_nxixalf5pn ; real_T Saturation_UpperSat_mderhtvsta ; real_T
Saturation_LowerSat_na0sdh24gx ; real_T Gain_Gain_mac0nz3shk ; real_T
Gain1_Gain_nxm3m0oimc ; real_T FromWorkspace6_Time0 ; real_T
FromWorkspace6_Data0 ; real_T Constant_Value_nytnoeucmv [ 3 ] ; real_T
Ra_Value_kj3pmm4raq ; real_T Gain_Gain_hyiakb1knr ; real_T
conversiontoRPM_Gain_mcxghe0z0j ; real_T Gain1_Gain_jsikeibefk ; real_T
Constant6_Value_mf5czz2ry0 ; real_T Constant2_Value_famev12dvd [ 9 ] ; real_T
Constant7_Value_ev42suj2mv [ 18 ] ; real_T Constant8_Value_jnqtvlutwj ;
real_T Constant1_Value_imn1hkkgc1 ; real_T Gain_Gain_c04eta5jei ; real_T
Gain1_Gain_i3scwfulpa ; real_T Constant6_Value_k0ew1yhaa2 ; real_T
Constant2_Value_ldq5tfox0g [ 9 ] ; real_T Constant7_Value_c5zkgrzq1z [ 18 ] ;
real_T Constant8_Value_jpnyl202ps ; real_T Constant1_Value_fu0eog2bs5 ;
real_T Switch_Threshold_l51av4ct4h ; real_T Saturation_UpperSat_ar1iwsjf3t ;
real_T Saturation_LowerSat_idpgnii55n ; real_T Constant_Value_hjtsi0eo30 [ 7
] ; real_T Constant1_Value_dfgbihyjmh [ 2 ] ; real_T gain_Gain ; real_T
FromWorkspace7_Time0 ; real_T FromWorkspace7_Data0 ; real_T
FromWorkspace4_Time0 ; real_T FromWorkspace4_Data0 ; real_T
conversiontoRPM1_Gain ; real_T Memory_X0_kgirpjp1em ; real_T
conversiontoRPM_Gain_c31itt1fpi ; real_T Constant7_Value_lsrcvwaode ; real_T
Constant13_Value ; real_T Constant11_Value ; real_T Constant12_Value ; real_T
Constant8_Value_oi5cuui1pe [ 5 ] ; real_T Constant9_Value_jt0hblxo1l [ 7 ] ;
real_T exhaustmanifoldvolume_Gain ; real_T Integrator1_IC_ficjnaw5sq ; real_T
exhaustmanifoldvolume_Gain_bcvpqqb1p5 ; real_T k_heat_W_Gain ; real_T
gammaR_air_Gain ; real_T exhaust_manifold_vol_Value ; real_T
intakemanifoldvolume_Gain ; real_T intakemanifoldvolume1_Gain ; real_T
gammaR_air_Gain_gxlwxkgn4a ; real_T Intake_manifold_vol_Value ; real_T
Constant_Value_hh24nrqhdu ; real_T J_turbo_Gain ; real_T FromWorkspace5_Time0
; real_T FromWorkspace5_Data0 ; real_T FromWorkspace8_Time0 ; real_T
FromWorkspace8_Data0 ; real_T gammaRV_preThrottle_Gain ; real_T
FromWorkspace_Time0 [ 3 ] ; real_T FromWorkspace_Data0 [ 3 ] ; real_T
UniformRandomNumber_Minimum ; real_T UniformRandomNumber_Maximum ; real_T
UniformRandomNumber_Seed ; real_T UniformRandomNumber1_Minimum ; real_T
UniformRandomNumber1_Maximum ; real_T UniformRandomNumber1_Seed ; real32_T
thr_ff_map_RowIdx [ 20 ] ; real32_T thr_ff_map_ColIdx [ 20 ] ; real32_T
thr_ff_map_Table [ 400 ] ; real32_T Saturation6_UpperSat ; real32_T
Saturation6_LowerSat ; real32_T Constant4_Value_fcj2xxbxnn ; real32_T
Constant2_Value_iglpak03on ; real32_T Saturation1_UpperSat_ojvkrkpnti ;
real32_T Saturation1_LowerSat_kz22ykzlmo ; real32_T
Constant3_Value_opcmg5klwq ; real32_T Saturation2_UpperSat ; real32_T
Saturation2_LowerSat ; real32_T one_Value ; real32_T Gain6_Gain_eqvrzpdjgj ;
real32_T Saturation3_UpperSat ; real32_T Saturation3_LowerSat ; real32_T
Saturation1_UpperSat_l0fn5euabx ; real32_T Saturation1_LowerSat_oko05faisu ;
real32_T one4_Value ; real32_T one3_Value ; real32_T Saturation4_UpperSat ;
real32_T Saturation4_LowerSat ; real32_T two_Value ; real32_T
Saturation2_UpperSat_neszcqhzip ; real32_T Saturation2_LowerSat_ownvik0s0l ;
real32_T one5_Value ; real32_T Saturation_UpperSat_phsdj5dg3g ; real32_T
Saturation_LowerSat_mqpqdfn3am ; real32_T Gain_Gain_loxnzerzgs ; real32_T
expLookupTable_XData [ 103 ] ; real32_T expLookupTable_YData [ 103 ] ;
real32_T UnitDelay_InitialCondition ; real32_T one1_Value ; real32_T
Gain1_Gain_gb423uv2ae ; real32_T one_Value_gh4ygofu0g ; real32_T
Gain6_Gain_oo3qmk1vhv ; real32_T Saturation3_UpperSat_fpowc2uvdu ; real32_T
Saturation3_LowerSat_b1lgcpn3h4 ; real32_T Saturation1_UpperSat_jhk0udkkso ;
real32_T Saturation1_LowerSat_aobxdvcimk ; real32_T
Saturation4_UpperSat_fgk5yexhjk ; real32_T Saturation4_LowerSat_o5mois15qj ;
real32_T Saturation2_UpperSat_kqxekeh4ne ; real32_T
Saturation2_LowerSat_cum5140yxb ; real32_T Gain_Gain_pmlstkcmse ; real32_T
one_Value_a45lx41rlt ; real32_T one4_Value_lfqywyfkb1 ; real32_T
one3_Value_pho5uxuvjc ; real32_T Saturation4_UpperSat_mvi32mle5a ; real32_T
Saturation4_LowerSat_h1tphx4t4v ; real32_T two_Value_fwe0t422am ; real32_T
Saturation2_UpperSat_m0obbkx21y ; real32_T Saturation2_LowerSat_aj21rgvimm ;
real32_T one5_Value_e10f33ajto ; real32_T Saturation_UpperSat_bb44f3rn3e ;
real32_T Saturation_LowerSat_l0ofoykzq5 ; real32_T one2_Value ; real32_T
one1_Value_cfbkskxgcs ; real32_T Saturation1_UpperSat_dbmtmwbw0d ; real32_T
Saturation1_LowerSat_cuwighb455 ; real32_T Saturation3_UpperSat_eu4nn5aeqt ;
real32_T Saturation3_LowerSat_kswln5xcqk ; real32_T fifteen_Value ; real32_T
one_Value_januwcu5ef ; real32_T Saturation1_UpperSat_h1az5n4to4 ; real32_T
Saturation1_LowerSat_cgvkg1cu0s ; real32_T Saturation3_UpperSat_fyjrms34ap ;
real32_T Saturation3_LowerSat_enydkrbip1 ; real32_T Constant10_Value [ 9 ] ;
real32_T Constant11_Value_dfwxcchqhl [ 9 ] ; real32_T
Constant12_Value_p4sdtff4av [ 9 ] ; real32_T Constant13_Value_drcxtjpegy ;
real32_T Constant14_Value ; real32_T Constant7_Value_jx1utvbjk0 ; real32_T
Constant8_Value_bk5pmdij31 ; real32_T Gain10_Gain ; real32_T Gain11_Gain ;
real32_T Saturation4_UpperSat_ne3ia3nb0j ; real32_T
Saturation4_LowerSat_hbatond2b0 ; real32_T pexmax1_Value ; real32_T
Gain3_Gain_gi5nnsebzm ; real32_T Saturation1_UpperSat_mmdkyxpjcy ; real32_T
Saturation1_LowerSat_m5mjtmtt23 ; real32_T Gain6_Gain_mzhcfliz3a ; real32_T
man_pex_eps_Gain ; real32_T Gain1_Gain_ok5bp1tyb1 ; real32_T
Saturation5_UpperSat ; real32_T Saturation5_LowerSat ; real32_T
Saturation2_UpperSat_fjp1hny0ya ; real32_T Saturation2_LowerSat_gqdcpi2olt ;
real32_T Saturation4_UpperSat_f5y5vur4ve ; real32_T
Saturation4_LowerSat_kbnhpimcru ; real32_T Saturation_UpperSat_d0ebinhgkh ;
real32_T Saturation_LowerSat_czzo0et5n0 ; real32_T man_use_LM_Gain ; real32_T
zero8_Value ; real32_T man_pex_eps1_Gain ; real32_T Gain2_Gain_inrigkvibz ;
real32_T unity2_Value ; real32_T interp_XData [ 2 ] ; real32_T interp_YData [
2 ] ; real32_T mintos_Value ; real32_T rv_Y0 ; real32_T
Constant_Value_akx2zsubmt ; real32_T bigH1_Value [ 1030 ] ; real32_T
ibigHstart_Value [ 103 ] ; real32_T Saturation1_UpperSat_jyclkdtald ;
real32_T Saturation1_LowerSat_nhdjll5e0q ; real32_T bigH2_Value [ 1030 ] ;
real32_T bigH3_Value [ 1030 ] ; real32_T bigH4_Value [ 1030 ] ; real32_T
bigH5_Value [ 1030 ] ; real32_T bigH6_Value [ 1030 ] ; real32_T bigH7_Value [
1030 ] ; real32_T bigH8_Value [ 1030 ] ; real32_T bigH9_Value [ 1030 ] ;
real32_T bigH10_Value [ 1030 ] ; real32_T bigH11_Value [ 1030 ] ; real32_T
bigH12_Value [ 1030 ] ; real32_T bigH13_Value [ 1030 ] ; real32_T bigK_Value
[ 1030 ] ; real32_T rv_register_InitialCondition ; real32_T
rv_update_merge_InitialOutput ; real32_T Constant5_Value_pvrh0hx004 ;
real32_T Constant3_Value_py3cg1rapn ; real32_T
Saturation1_UpperSat_kb5wgoij0s ; real32_T Saturation1_LowerSat_hcztblyabo ;
real32_T Constant4_Value_j11gk30hoj ; real32_T
Saturation3_UpperSat_jgnvlh1trc ; real32_T Saturation3_LowerSat_eezjeovjb4 ;
real32_T Saturation4_UpperSat_fg5ix0ri20 ; real32_T
Saturation4_LowerSat_g5gg4j1znz ; real32_T Saturation7_UpperSat ; real32_T
Saturation7_LowerSat ; real32_T c_km1d2k1_Gain ; real32_T c_p4d1p4_Gain ;
real32_T Saturation_UpperSat_dfiskt0evr ; real32_T
Saturation_LowerSat_kkda3f5nhs ; real32_T Gain_Gain_nty4sel1wt ; real32_T
expLookupTable_XData_jvstrz5tjz [ 103 ] ; real32_T
expLookupTable_YData_o1u0ravagw [ 103 ] ; real32_T
UnitDelay_InitialCondition_j4qityl4pb ; real32_T Out1_Y0 [ 3 ] ; real32_T
tp_Value [ 3 ] ; real32_T Out1_Y0_g3ilp1142h [ 3 ] ; real32_T
tp_Value_mmdc5jjvbq [ 3 ] ; real32_T Out1_Y0_o1unubeg55 [ 3 ] ; real32_T
tp_Value_oipiuqzz5m [ 3 ] ; real32_T Out1_Y0_cfbmbz0s4v [ 3 ] ; real32_T
tp_Value_d0bqr0adai [ 3 ] ; real32_T Out1_Y0_fzdsbyixjn [ 3 ] ; real32_T
tp_Value_e3hgnntmco [ 3 ] ; real32_T Out1_Y0_i20jpg1ssx [ 3 ] ; real32_T
tp_Value_npphduwijc [ 3 ] ; real32_T Out1_Y0_et2raie4nn [ 3 ] ; real32_T
tp_Value_ou5xhjjrog [ 3 ] ; real32_T Out1_Y0_ky0jsoirgo [ 3 ] ; real32_T
tp_Value_o1owsucjxa [ 3 ] ; real32_T Out1_Y0_h4dmjfn41x [ 3 ] ; real32_T
tp_Value_mrn2z15h1h [ 3 ] ; real32_T Out1_Y0_an2sth1szw [ 3 ] ; real32_T
tp_Value_llx05eyp5k [ 3 ] ; real32_T Out1_Y0_ldubnjtjvb [ 3 ] ; real32_T
tp_Value_fue1paeukq [ 3 ] ; real32_T Out1_Y0_oszp3rq3fo [ 3 ] ; real32_T
tp_Value_jfinzetqib [ 3 ] ; real32_T Out1_Y0_ays1y1015e [ 3 ] ; real32_T
tp_Value_ootste3xt4 [ 3 ] ; real32_T Out1_Y0_cwm0ratokt [ 3 ] ; real32_T
tp_Value_glry24veam [ 3 ] ; real32_T Out1_Y0_ib4cx3cul2 [ 3 ] ; real32_T
tp_Value_a2liswbfky [ 3 ] ; real32_T Out1_Y0_jbohyy2t2k [ 3 ] ; real32_T
tp_Value_f4oghoc422 [ 3 ] ; real32_T Out1_Y0_fdoepsc2fh [ 3 ] ; real32_T
tp_Value_mg4ej1dk4c [ 3 ] ; real32_T Out1_Y0_jjo55kw3ex [ 3 ] ; real32_T
tp_Value_io4ywoj4cq [ 3 ] ; real32_T Out1_Y0_gv2tsfk40f [ 3 ] ; real32_T
tp_Value_pupcrx2sx4 [ 3 ] ; real32_T Out1_Y0_lzd5sorf1b [ 3 ] ; real32_T
tp_Value_lppwvyte25 [ 3 ] ; real32_T Out1_Y0_exe1vlznp5 [ 3 ] ; real32_T
tp_Value_aqtk5tk1ud [ 3 ] ; real32_T Out1_Y0_kda1u3d0rz [ 3 ] ; real32_T
tp_Value_e5rebtcdsl [ 3 ] ; real32_T Out1_Y0_pzvjwx2vmz [ 3 ] ; real32_T
tp_Value_ag1b2ln31i [ 3 ] ; real32_T Out1_Y0_fv0ynyqema [ 3 ] ; real32_T
tp_Value_d4yv4borja [ 3 ] ; real32_T Out1_Y0_craatzwyjv [ 3 ] ; real32_T
tp_Value_fqq5esx3ho [ 3 ] ; real32_T Out1_Y0_mvnq5nqcib [ 3 ] ; real32_T
tp_Value_adjdr5el0e [ 3 ] ; real32_T Out1_Y0_fufsc5q3mt [ 3 ] ; real32_T
tp_Value_hwfgj3cglx [ 3 ] ; real32_T Out1_Y0_hjs1yrsfu4 [ 3 ] ; real32_T
tp_Value_hw24qnkg5a [ 3 ] ; real32_T Out1_Y0_pppo1wbrr3 [ 3 ] ; real32_T
tp_Value_emdemdcjqw [ 3 ] ; real32_T Out1_Y0_fzit3grq2n [ 3 ] ; real32_T
tp_Value_m2pfqecp3r [ 3 ] ; real32_T Out1_Y0_htniehg5e5 [ 3 ] ; real32_T
tp_Value_m3vqy1b0ro [ 3 ] ; real32_T Out1_Y0_jw1c5kunqy [ 3 ] ; real32_T
tp_Value_mcbwndmcgn [ 3 ] ; real32_T Out1_Y0_pwzdagqydm [ 3 ] ; real32_T
tp_Value_lw1gyfl3x2 [ 3 ] ; real32_T Out1_Y0_pehuglceod [ 3 ] ; real32_T
tp_Value_iqqu53t0m4 [ 3 ] ; real32_T Out1_Y0_ki3neydkxc [ 3 ] ; real32_T
tp_Value_lvdpu0ygf2 [ 3 ] ; real32_T Out1_Y0_hmks2vgxo4 [ 3 ] ; real32_T
tp_Value_kncwrbpx0j [ 3 ] ; real32_T Out1_Y0_oneyowtt3q [ 3 ] ; real32_T
tp_Value_anpzo5c2vg [ 3 ] ; real32_T Out1_Y0_eds0rmp0ij [ 3 ] ; real32_T
tp_Value_pl0rshtt5z [ 3 ] ; real32_T Out1_Y0_bu2mgwj0zv [ 3 ] ; real32_T
tp_Value_djrhs1sek1 [ 3 ] ; real32_T Out1_Y0_ahmxi3osbt [ 3 ] ; real32_T
tp_Value_izulaw4r0j [ 3 ] ; real32_T Out1_Y0_mqabdzzuww [ 3 ] ; real32_T
tp_Value_bljmnhbssi [ 3 ] ; real32_T Out1_Y0_k3deuwitgk [ 3 ] ; real32_T
tp_Value_atkwrgxtrm [ 3 ] ; real32_T Out1_Y0_hlbejplcej [ 3 ] ; real32_T
tp_Value_mzh3evdrk5 [ 3 ] ; real32_T Out1_Y0_bb0bagvudq [ 3 ] ; real32_T
tp_Value_ljry3t5zvi [ 3 ] ; real32_T Out1_Y0_huz5txvytd [ 3 ] ; real32_T
tp_Value_jwr5rhqyrj [ 3 ] ; real32_T Out1_Y0_g4khwpdvgp [ 3 ] ; real32_T
tp_Value_id4dgkpbz2 [ 3 ] ; real32_T Out1_Y0_gfwj4x0vnc [ 3 ] ; real32_T
tp_Value_b1geh04tje [ 3 ] ; real32_T Out1_Y0_hsoa4pracq [ 3 ] ; real32_T
tp_Value_gp424rrzsc [ 3 ] ; real32_T Out1_Y0_inc00gtcro [ 3 ] ; real32_T
tp_Value_m4cdr3ebrt [ 3 ] ; real32_T Out1_Y0_cdtmzio14w [ 3 ] ; real32_T
tp_Value_muv5msoizt [ 3 ] ; real32_T Out1_Y0_ndyqry4oan [ 3 ] ; real32_T
tp_Value_feweqckn0h [ 3 ] ; real32_T Out1_Y0_doti2utdex [ 3 ] ; real32_T
tp_Value_l02eb0qhwx [ 3 ] ; real32_T Out1_Y0_lg1jjee3ki [ 3 ] ; real32_T
tp_Value_fntfr5tndb [ 3 ] ; real32_T Out1_Y0_jke2qn1f2u [ 3 ] ; real32_T
tp_Value_pmklg2ovge [ 3 ] ; real32_T Out1_Y0_eoiajy4dla [ 3 ] ; real32_T
tp_Value_j0jknsqgnc [ 3 ] ; real32_T Out1_Y0_ezvh0eoaf3 [ 3 ] ; real32_T
tp_Value_cigkhzn0ua [ 3 ] ; real32_T Out1_Y0_lf5joc1kq1 [ 3 ] ; real32_T
tp_Value_eqr0fc2ekw [ 3 ] ; real32_T Out1_Y0_inezqsygfa [ 3 ] ; real32_T
tp_Value_ltt52ykbaf [ 3 ] ; real32_T Out1_Y0_e50mwcz2qh [ 3 ] ; real32_T
tp_Value_ieij3u5c0j [ 3 ] ; real32_T Out1_Y0_h5mvojrry4 [ 3 ] ; real32_T
tp_Value_brvneamxcn [ 3 ] ; real32_T Out1_Y0_dy01kx4xye [ 3 ] ; real32_T
tp_Value_nbyf2qneco [ 3 ] ; real32_T Out1_Y0_bhmju4ggll [ 3 ] ; real32_T
tp_Value_hj03giyyop [ 3 ] ; real32_T Out1_Y0_ltqatlbxqk [ 3 ] ; real32_T
tp_Value_gezfx3zot5 [ 3 ] ; real32_T Out1_Y0_jycc30fiih [ 3 ] ; real32_T
tp_Value_nssh0jxsrt [ 3 ] ; real32_T Out1_Y0_lhqgexa4xs [ 3 ] ; real32_T
tp_Value_fddutnl2oo [ 3 ] ; real32_T Out1_Y0_d5hs12amdx [ 3 ] ; real32_T
tp_Value_oaafylj13a [ 3 ] ; real32_T Out1_Y0_hdbrigas4j [ 3 ] ; real32_T
tp_Value_ovs553bhfy [ 3 ] ; real32_T Out1_Y0_av1mg5yp24 [ 3 ] ; real32_T
tp_Value_hc1bpxti1u [ 3 ] ; real32_T mon_map_Gain ; real32_T mon_wegr_Gain ;
real32_T ye_Value [ 2 ] ; real32_T ue_Value [ 2 ] ; real32_T
UnitDelay1_InitialCondition [ 2 ] ; real32_T Gain4_Gain_ff4g3pyzm4 [ 4 ] ;
real32_T Delay1_InitialCondition ; real32_T man_tuneFiltalpha1_Gain ;
real32_T Saturation1_UpperSat_evi3lcggpc ; real32_T
Saturation1_LowerSat_hvawqdgu0g ; real32_T zero1_Value ; real32_T
man_tuneFiltalpha_Gain ; real32_T Saturation4_UpperSat_ox5ea3vzv2 ; real32_T
Saturation4_LowerSat_fnwk5eluqv ; real32_T man_wcyl_gperrev_Gain ; real32_T
zero3_Value ; real32_T UnitDelay4_InitialCondition ; real32_T
one_Value_aeususitml ; real32_T man_use_Wcylinterp_Gain ; real32_T
zero2_Value ; real32_T man_wegrhat_gain_Gain ; real32_T
UnitDelay3_InitialCondition ; real32_T V_Value ; real32_T CtoK_Value ;
real32_T Saturation5_UpperSat_dlhoczu115 ; real32_T
Saturation5_LowerSat_duc145inwk ; real32_T Saturation4_UpperSat_nmdcwefbw5 ;
real32_T Saturation4_LowerSat_pc32rj1qgb ; real32_T R_Value ; real32_T
Saturation2_UpperSat_hskdnsucj5 ; real32_T Saturation2_LowerSat_pvcw4rcoue ;
real32_T Saturation1_UpperSat_kk32mwbior ; real32_T
Saturation1_LowerSat_bt1eom2vut ; real32_T Saturation3_UpperSat_aodcenepxv ;
real32_T Saturation3_LowerSat_dbo42efvqo ; real32_T Gain7_Gain_je5is4zb3m ;
real32_T man_use_wegrhat_Gain ; real32_T zero3_Value_c4pusxmemm ; real32_T
UnitDelay5_InitialCondition ; real32_T Gain_Gain_ji33gjxgix [ 2 ] ; real32_T
Gain1_Gain_ktwf12ggqn [ 2 ] ; real32_T Gain2_Gain_b5usxkmjtz ; real32_T
Gain3_Gain_khxel0hppy [ 2 ] ; real32_T UnitDelay5_InitialCondition_kpkvgiix5s
; real32_T UnitDelay1_InitialCondition_jptrwhyymm ; real32_T
UnitDelay2_InitialCondition ; real32_T man_use_ROO_Gain ; real32_T
zero8_Value_enfwb3sxd4 ; real32_T UnitDelay_InitialCondition_ezolpyxjya [ 3 ]
; real32_T mon_map_hat_Gain ; real32_T mon_egrr_hat_Gain ; real32_T
mon_x1_hat_Gain ; real32_T man_use_wegrhat2_Gain ; real32_T
zero2_Value_mzu0rbqhwf ; real32_T Gain8_Gain ; real32_T ctok_Value ; real32_T
man_pexh_adder_Gain ; real32_T y_cons1_Value ; real32_T
UnitDelay3_InitialCondition_ffvh0pkag0 ; real32_T
UnitDelay2_InitialCondition_pgqysx40c3 ; real32_T Gain7_Gain_hdbaustsmr [ 4 ]
; real32_T Delay1_InitialCondition_cabzb21box ; real32_T
man_tuneFiltalpha1_Gain_na2addg3ve ; real32_T Saturation1_UpperSat_aiumrxurnx
; real32_T Saturation1_LowerSat_hmzuy5u0pb ; real32_T zero1_Value_mjmu52lvvx
; real32_T man_tuneFiltalpha_Gain_muc2cpzprk ; real32_T
Saturation4_UpperSat_mli4xalwq5 ; real32_T Saturation4_LowerSat_o1m3sqjmh3 ;
real32_T n9_Gain ; real32_T UnitDelay8_InitialCondition ; real32_T
Delay1_InitialCondition_plljnknkib ; real32_T
man_tuneFiltalpha1_Gain_cqsveg5rxa ; real32_T Saturation1_UpperSat_aeygqv5amr
; real32_T Saturation1_LowerSat_imqjfndrcy ; real32_T zero1_Value_cfkzinnzed
; real32_T man_tuneFiltalpha_Gain_m1s1jazml1 ; real32_T
Saturation4_UpperSat_heyzyhtkkx ; real32_T Saturation4_LowerSat_fudpzb5job ;
real32_T UnitDelay9_InitialCondition ; real32_T Gain10_Gain_bwanyq3goq [ 8 ]
; real32_T Gain11_Gain_o3ain5lccm [ 2 ] ; real32_T man_use_PexHat_Gain ;
real32_T zero6_Value ; real32_T Gain4_Gain_dbouzguspb ; real32_T
Saturation4_UpperSat_epdhn4s0cl ; real32_T Saturation4_LowerSat_av41cx1fh3 ;
real32_T Ra_Value_cq5xpakoe0 ; real32_T Gain2_Gain_f5pp4pdbvl ; real32_T
LookupTable_XData [ 16 ] ; real32_T LookupTable_YData [ 16 ] ; real32_T
Gain2_Gain_jqgsltqvvo ; real32_T Saturation3_UpperSat_hvmdvvrxvg ; real32_T
Saturation3_LowerSat_cbroun1d3t ; real32_T Constant5_Value_oine35ovff ;
real32_T tokgps1_Gain_niett2ztcu ; real32_T Saturation_UpperSat_heyubqqqyr ;
real32_T Saturation_LowerSat_libsvlbteb ; real32_T man_egrr_cons_Gain ;
real32_T c_100inv_Gain ; real32_T Saturation1_UpperSat_b2bgfkqzvd ; real32_T
Saturation1_LowerSat_pdrhlonent ; real32_T rate_max1_Value ; real32_T n4_Gain
; real32_T n6_Gain ; real32_T mon_flowmax_Gain ; real32_T bigF1_Value [ 309 ]
; real32_T ibigFstart_Value [ 103 ] ; real32_T epimbs_map_RowIdx [ 20 ] ;
real32_T epimbs_map_ColIdx [ 20 ] ; real32_T epimbs_map_Table [ 400 ] ;
real32_T man_pinrefadd_Gain ; real32_T epimbs_map_RowIdx_hricelzw4c [ 20 ] ;
real32_T epimbs_map_ColIdx_aw5dr10asn [ 20 ] ; real32_T
epimbs_map_Table_ievkkvfepo [ 400 ] ; real32_T Gain2_Gain_bqzhmg4lx1 ;
real32_T man_egrrefadd_Gain ; real32_T Saturation1_UpperSat_omybqinkw3 ;
real32_T Saturation1_LowerSat_mdkjykh3qf ; real32_T thousand_Value ; real32_T
pincomp_Value ; real32_T Gain_Gain_nqiwfihzfk ; real32_T four_Value ;
real32_T Delay1_InitialCondition_btda0c1p1a ; real32_T filt_Value ; real32_T
Saturation1_UpperSat_myjsita4wq ; real32_T Saturation1_LowerSat_e3kdxawffw ;
real32_T one_Value_h01zho5suw ; real32_T filt1_Value ; real32_T
Saturation4_UpperSat_iuohbhcftj ; real32_T Saturation4_LowerSat_fp4jygx5yy ;
real32_T tokgps2_Gain ; real32_T man_use_throttleffmap_Gain ; real32_T
zero5_Value ; real32_T man_throttle_ff_Gain ; real32_T Gain_Gain_jgqj4bq1it ;
real32_T Gain1_Gain_huollvbetb ; real32_T svrthrottle1_Value [ 9 ] ; real32_T
svrthrottle2_Value [ 9 ] ; real32_T svrthrottlearg_Value ; real32_T
svrthrottleargbeta_Value [ 9 ] ; real32_T Saturation2_UpperSat_ar3amrrdo0 ;
real32_T Saturation2_LowerSat_gcjzh4zwtf ; real32_T one_Value_j5dpbec4pp ;
real32_T tic_Value ; real32_T Saturation5_UpperSat_lsmaqufwep ; real32_T
Saturation5_LowerSat_inbxi0ty31 ; real32_T Ra_Value_lzmtkyahjs ; real32_T
Saturation1_UpperSat_otpxulmvuy ; real32_T Saturation1_LowerSat_ppefjc3clp ;
real32_T Gain2_Gain_oeyqknfg3u ; real32_T Saturation_UpperSat_aeqkn4yat2 ;
real32_T Saturation_LowerSat_eqca1cxjhu ; real32_T
Saturation3_UpperSat_e5wb1y1qfm ; real32_T Saturation3_LowerSat_o44sgnqx2m ;
real32_T c_km1d2k_Value ; real32_T two_Value_ggoksfpb1h ; real32_T
Saturation1_UpperSat_pqesfzc0le ; real32_T Saturation1_LowerSat_javhnqsmey ;
real32_T c_1d2p4_Value ; real32_T Gain2_Gain_hgyagoi5x4 ; real32_T
Lookup_Table_2D_RowIdx [ 20 ] ; real32_T Lookup_Table_2D_ColIdx [ 16 ] ;
real32_T Lookup_Table_2D_Table [ 320 ] ; real32_T conversiontoradpers_Gain ;
real32_T Gain1_Gain_p0b0owyvrq ; real32_T vnliftmax_Value ; real32_T
man_gsvgt_Gain ; real32_T Saturation3_UpperSat_gfw1stpglz ; real32_T
Saturation3_LowerSat_j1w5p5qkgi ; real32_T vnliftmin_Value ; real32_T
n1_Gain_pvuonpooax ; real32_T n3_Gain_ddgktxpofx ; real32_T man_gswegr_Gain ;
real32_T Saturation2_UpperSat_pd4jn2febf ; real32_T
Saturation2_LowerSat_na315pjcdo ; real32_T flowmin_Value ; real32_T
n2_Gain_higq23ggss ; real32_T man_map_cons_Gain ; real32_T y_cons5_Value ;
real32_T man_pex_cons_Gain ; real32_T man_ntcons_Gain ; real32_T
Gain3_Gain_m5i2an5c5h ; real32_T Saturation1_UpperSat_haurxgbsmv ; real32_T
Saturation1_LowerSat_ky0lpt3bhz ; real32_T bigF2_Value [ 309 ] ; real32_T
bigF3_Value [ 309 ] ; real32_T bigF4_Value [ 309 ] ; real32_T bigF5_Value [
309 ] ; real32_T bigF6_Value [ 309 ] ; real32_T bigF7_Value [ 309 ] ;
real32_T bigF8_Value [ 309 ] ; real32_T bigF9_Value [ 309 ] ; real32_T
bigF10_Value [ 309 ] ; real32_T bigF11_Value [ 309 ] ; real32_T bigF12_Value
[ 309 ] ; real32_T bigF13_Value [ 309 ] ; real32_T bigG_Value [ 309 ] ;
real32_T mon_delvgt_Gain ; real32_T mon_delflow_Gain ; real32_T
mon_slack_Gain ; real32_T man_vgtff_Gain ; real32_T n5_Gain ; real32_T
man_wegrff_Gain ; real32_T Gain9_Gain ; real32_T zero_Value ; real32_T
man_ctrl_Gain ; real32_T zero1_Value_jogrhh3e5m ; real32_T mon_vgt_Gain ;
real32_T Gain_Gain_izbq1vn3ay ; real32_T n7_Gain ; real32_T mon_uwegr_Gain ;
real32_T mon_wf_Gain ; real32_T man_valveff_Gain ; real32_T
man_use_valveff_Gain ; real32_T zero4_Value ; real32_T togps_Gain ; real32_T
Gain_Gain_exnmofkiqk ; real32_T Saturation4_UpperSat_jpf21d0c4s ; real32_T
Saturation4_LowerSat_nemejy2x0v ; real32_T Ra_Value_ml4zxyzp5y ; real32_T
Gain1_Gain_mlwsoiu4wp ; real32_T Gain1_Gain_nwjp5v2nv4 ; real32_T
Saturation2_UpperSat_eil30qspgi ; real32_T Saturation2_LowerSat_pgybggvmgo ;
real32_T Constant1_Value_m1lei4f355 ; real32_T
Saturation4_UpperSat_kyzipinvaz ; real32_T Saturation4_LowerSat_b3ugkcddqm ;
real32_T invert_svr_lut_RowIdx [ 16 ] ; real32_T invert_svr_lut_ColIdx [ 15 ]
; real32_T invert_svr_lut_Table [ 240 ] ; real32_T
Saturation1_UpperSat_jvb251jt2n ; real32_T Saturation1_LowerSat_iqly2zdexs ;
real32_T man_wegr_P_Gain ; real32_T Gain12_Gain ; real32_T
Saturation5_UpperSat_h4urtqtiyp ; real32_T Saturation5_LowerSat_aeeskfq3pr ;
real32_T Constant13_Value_nbirv4rghg ; real32_T man_use_SG_Gain ; real32_T
zero4_Value_av1gbwxi0k ; real32_T man_wegr_I_Gain ; real32_T
UnitDelay1_InitialCondition_lugtrxmixa ; real32_T man_wegr_D_Gain ; real32_T
UnitDelay3_InitialCondition_dnd305am25 ; real32_T c_100inv_Gain_fusdgx1rvb ;
real32_T Delay11_InitialCondition ; real32_T Delay21_InitialCondition ;
real32_T man_use_PID_Gain ; real32_T zero7_Value ; real32_T mon_valve_Gain ;
real32_T mon_pex_hat_Gain ; real32_T mon_wcyl_ecu_Gain ; real32_T
mon_egrr_est_Gain ; real32_T mon_wegr_est_Gain ; real32_T mon_ntest_Gain ;
real32_T mon_ene_Gain ; real32_T mon_pex_ecu_Gain ; real32_T
mon_wegr_ecu_Gain ; real32_T mon_tin_Gain ; real32_T mon_maf_ecu_Gain ;
real32_T mon_map_ref_Gain ; real32_T mon_egrr_ref_Gain ; real32_T
mon_pthr_Gain ; real32_T man_run2500tp_Gain ; real32_T zero9_Value ; real32_T
UnitDelay10_InitialCondition ; real32_T Merge_InitialOutput [ 3 ] ; real32_T
Merge_InitialOutput_iz5qfjawh0 [ 3 ] ; real32_T man_map_cons1_Gain ; real32_T
man_egrr_cons1_Gain ; real32_T man_pex_cons1_Gain ; real32_T
Gain5_Gain_jqsodes1v1 ; real32_T Gain6_Gain_hjsd4cpev4 ; real32_T
zero3_Value_oxiwsglhov ; real32_T zero1_Value_lj4wvitffo ; real32_T
UnitDelay6_InitialCondition ; real32_T UnitDelay7_InitialCondition ; real32_T
Delay1_InitialCondition_ortecfcub3 ; real32_T zero1_Value_jcxubjmcqw ;
real32_T man_tuneFiltalpha_Gain_bfzlu554zk ; real32_T
Saturation4_UpperSat_fgykekgs25 ; real32_T Saturation4_LowerSat_lknp0jneji ;
real32_T man_tuneFiltalpha1_Gain_jgtgdms0x5 ; real32_T
Saturation1_UpperSat_omkudzerxc ; real32_T Saturation1_LowerSat_hq5jvogu4t ;
real32_T Delay1_InitialCondition_enn30ozomz ; real32_T zero1_Value_cfe22a4fnb
; real32_T man_tuneFiltalpha_Gain_hlqsioyaw5 ; real32_T
Saturation4_UpperSat_hzncksesqh ; real32_T Saturation4_LowerSat_hp04ybe0ds ;
real32_T man_tuneFiltalpha1_Gain_oqdux2lbda ; real32_T
Saturation1_UpperSat_hyh2idym0z ; real32_T Saturation1_LowerSat_hh0hohkue0 ;
real32_T gain_schedule_egr_RowIdx [ 6 ] ; real32_T gain_schedule_egr_ColIdx [
7 ] ; real32_T gain_schedule_egr_Table [ 42 ] ; real32_T
gain_schedule_uvnlift_RowIdx [ 6 ] ; real32_T gain_schedule_uvnlift_ColIdx [
7 ] ; real32_T gain_schedule_uvnlift_Table [ 42 ] ; real32_T
Gain_Gain_j24i2xq1z0 [ 6 ] ; real32_T UnitDelay_InitialCondition_jua2isvxie ;
real32_T UnitDelay1_InitialCondition_onlqmfj3vv ; real32_T
Gain1_Gain_nbjizbigxo [ 6 ] ; real32_T Gain2_Gain_oz0f03bs1q [ 9 ] ; real32_T
Gain3_Gain_ibhgrspb4v [ 6 ] ; real32_T man_start_pattern_Gain ; real32_T
zero10_Value ; real32_T zero11_Value ; real32_T ctok_Value_czyz5znrbb ;
real32_T DataStoreMemory1_InitialValue ; real32_T
DataStoreMemory100_InitialValue ; real32_T DataStoreMemory101_InitialValue ;
real32_T DataStoreMemory102_InitialValue ; real32_T
DataStoreMemory103_InitialValue ; real32_T DataStoreMemory104_InitialValue ;
real32_T DataStoreMemory105_InitialValue ; real32_T
DataStoreMemory106_InitialValue ; real32_T DataStoreMemory107_InitialValue ;
real32_T DataStoreMemory108_InitialValue ; real32_T
DataStoreMemory2_InitialValue ; real32_T DataStoreMemory3_InitialValue ;
real32_T DataStoreMemory4_InitialValue ; real32_T
DataStoreMemory5_InitialValue ; real32_T DataStoreMemory52_InitialValue ;
real32_T DataStoreMemory55_InitialValue ; real32_T
DataStoreMemory56_InitialValue ; real32_T DataStoreMemory57_InitialValue ;
real32_T DataStoreMemory58_InitialValue ; real32_T
DataStoreMemory59_InitialValue ; real32_T DataStoreMemory60_InitialValue ;
real32_T DataStoreMemory61_InitialValue ; real32_T
DataStoreMemory62_InitialValue ; real32_T DataStoreMemory63_InitialValue ;
real32_T DataStoreMemory64_InitialValue ; real32_T
DataStoreMemory65_InitialValue ; real32_T DataStoreMemory66_InitialValue ;
real32_T DataStoreMemory67_InitialValue ; real32_T
DataStoreMemory68_InitialValue ; real32_T DataStoreMemory70_InitialValue ;
real32_T DataStoreMemory71_InitialValue ; real32_T
DataStoreMemory72_InitialValue ; real32_T DataStoreMemory73_InitialValue ;
real32_T DataStoreMemory74_InitialValue ; real32_T
DataStoreMemory75_InitialValue ; real32_T DataStoreMemory76_InitialValue ;
real32_T DataStoreMemory77_InitialValue ; real32_T
DataStoreMemory78_InitialValue ; real32_T DataStoreMemory79_InitialValue ;
real32_T DataStoreMemory80_InitialValue ; real32_T
DataStoreMemory81_InitialValue ; real32_T DataStoreMemory82_InitialValue ;
real32_T DataStoreMemory83_InitialValue ; real32_T
DataStoreMemory84_InitialValue ; real32_T DataStoreMemory85_InitialValue ;
real32_T DataStoreMemory86_InitialValue ; real32_T
DataStoreMemory87_InitialValue ; real32_T DataStoreMemory88_InitialValue ;
real32_T DataStoreMemory89_InitialValue ; real32_T
DataStoreMemory90_InitialValue ; real32_T DataStoreMemory91_InitialValue ;
real32_T DataStoreMemory92_InitialValue ; real32_T
DataStoreMemory93_InitialValue ; real32_T DataStoreMemory94_InitialValue ;
real32_T DataStoreMemory95_InitialValue ; real32_T
DataStoreMemory96_InitialValue ; real32_T DataStoreMemory97_InitialValue ;
real32_T DataStoreMemory98_InitialValue ; real32_T
DataStoreMemory99_InitialValue ; int32_T ForIterator_IterationLimit ; int32_T
Saturation1_UpperSat_lrtspvu1in ; int32_T Saturation1_LowerSat_cp3gsgarn4 ;
int32_T region_Y0 ; int32_T region_1_Value ; int32_T region_Y0_klozt0y54h ;
int32_T Saturation5_UpperSat_ekawuruosz ; int32_T
Saturation5_LowerSat_ihri13muhp ; int32_T reg_register_InitialCondition ;
int32_T reg_update_merge_InitialOutput ; int32_T
ForIterator_IterationLimit_dfiupsd0in ; int32_T
Saturation1_UpperSat_oxxrzmuthi ; int32_T Saturation1_LowerSat_g2klx1snpo ;
int32_T region_ic_Value ; int32_T Saturation5_UpperSat_l4y5uubttw ; int32_T
Saturation5_LowerSat_muc4d0y3pl ; int32_T DataStoreMemory69_InitialValue ;
uint32_T Delay1_DelayLength ; uint32_T Delay1_DelayLength_lm2qy5cz4x ;
uint32_T Delay1_DelayLength_amitx4x22y ; uint32_T
Delay1_DelayLength_kkjcwezpt4 ; uint32_T Delay11_DelayLength ; uint32_T
Delay21_DelayLength ; uint32_T Delay1_DelayLength_iesj1nyvk1 ; uint32_T
Delay1_DelayLength_htvqvf2sqs ; int32_T mon_region_Gain ; uint8_T
ManualSwitch_CurrentSetting ; uint8_T ManualSwitch1_CurrentSetting ; uint8_T
ManualSwitch_CurrentSetting_myjoxppklo ; uint8_T
ManualSwitch1_CurrentSetting_h0jpqknavp ; boolean_T y_cons4_Value ;
ev5xuv0chq lwrmmrtmge ; ev5xuv0chq cdbewnv5xj ; ev5xuv0chq masm1qwyo5u ; } ;
extern P rtP ; extern const char * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB
; extern X rtX ; extern DW rtDW ; extern ExtU rtU ; extern ExtY rtY ; extern
const rtwCAPI_ModelMappingStaticInfo *
KD_cl_harness_forthao_breach_GetCAPIStaticMap ( void ) ; extern SimStruct *
const rtS ; extern const int_T gblNumToFiles ; extern const int_T
gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern rtInportTUtable
* gblInportTUtables ; extern const char * gblInportFileName ; extern const
int_T gblNumRootInportBlks ; extern const int_T gblNumModelInputs ; extern
const int_T gblInportDataTypeIdx [ ] ; extern const int_T gblInportDims [ ] ;
extern const int_T gblInportComplex [ ] ; extern const int_T
gblInportInterpoFlag [ ] ; extern const int_T gblInportContinuous [ ] ;
extern DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( void
) ;
#endif
