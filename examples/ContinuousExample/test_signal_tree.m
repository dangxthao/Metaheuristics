% Test script for signal_tree class
%
L = .5;
epsilon=.4;
tset = 0:.01:1; 
ulim = [-1, 1];

% Create tree 
sig_tree = signal_tree(ulim, L, epsilon,tset);
sig_tree.show();

% Grow complete tree
sig_tree = sig_tree.grow_epsi_tree();
sig_tree.show();
sig_tree.plot_all();


