% Example for coverage-based Breach extension evaluation
%
% The examples in this directory relate to a prototype, test, diesel engine
% controller design model. 
% 
% PropertyCheck_STaLiRo.m is setup to use the model
% KD_cl_harness_tommasso.slx to do a falsification.
%
% The version that this script corresponds to is
% "KD_cl_harness_forthao.slx". The script sets up the necessary parameters
% and then opens the model. The model can then be "run" to show one
% instance of behaviors for a fixed input trajectory. The input signals  
% are blocks:
%
% KD_cl_harness_forthao/In1
% KD_cl_harness_forthao/In2
% 
% The output signal is:
%
% KD_cl_harness_forthao/Out1
%
%
% Note that for the "Thao" version of the model, the swtich blocks are set
% so that the external inputs are bypassed for some fixed input signals. To
% setup this version for a Breach analysis, you need to switch the inputs
% back to the In1 and In2 blocks.
%
% J. Kapinski
% 7-2018
%

close all
warning('off', 'ALL')
% Initialize the model 
load('expcon.mat')
load('KD_const_coeffs_0624.mat')
load('pexhat_stuff.mat')
load('thr_ff_map.mat')

open KD_cl_harness_forthao.slx

