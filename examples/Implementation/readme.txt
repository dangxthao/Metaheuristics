The folder contains the following items.

1) code.m: Code to implement falsification search of STL formulas.
2) PTC_demo.m: A demo of the implementation of code on PTC_benchmark example.
3) auto…._demo.m A demo of the implementation of the code with slight modifications on 
                 the auto_transmission example.

Explanation of code.
————————————————————

 This code takes as input a coverage breach set object and an STL formula
 and searches for a falsifier of the STL formula.

 The coverage breach object should have an epsilon grid size specified
 with no points initially, i.e. NumPoints = 0 at start.

 Upon running the code, the user will be prompted to enter the following
 parameters.
  1) The coverage breach set object.
  2) The STL formula specified in breach.
  3) The falsification method: a list of choices are displayed.
  4) A seed for pseudo-random sampling.
  5) Other parameters specific to the falsification method.

