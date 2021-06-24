import matlab.engine
import sys
from learning import Float_Range, NonAdequateTeacher_MM_Float
from learning import SymbPACLearner_MM_Float as SymbLearner_MM_Float
import numpy as np
import time
class NNTeacher_quad:
    def __init__(self, outputLowBound, outputUpperBound, outputSize):
        if 'MATLAB_4242' not in matlab.engine.find_matlab():
            print("MATLAB session not found. Terminating...")
            sys.exit(-1)

        print("Connecting to MATLAB session...")
        self.eng = matlab.engine.connect_matlab('MATLAB_4242')
        self.eng.addpath('sim_NN_timing', nargout=0)
        print("Connected to MATLAB session successfully!")
        self.concrete_alphabet = Float_Range(0, 1)
        self.outputLowBound = outputLowBound
        self.outputUpperBound = outputUpperBound
        self.outputSize = outputSize
        self.step = (outputUpperBound - outputLowBound) * 1.0 / outputSize

    def concretizeOutput(self, output):
        """
        Converts a float output to another float output in a finite set of outputs
        The returned value x means that output belongs in [x, x + self.step)
        """
        if output < self.outputLowBound:
            return '< lowBound'
#           return self.outputLowBound - 1

        if output >= self.outputUpperBound:
            return '>= upperBound'
#           return self.outputUpperBound

        lb = outputLowBound + self.step * int((output - outputLowBound) / self.step)
        ub = lb + self.step
        return '[' + str(lb) + ', ' + str(ub) + ')'

    def compute(self, word):
        if word == '':
            return 'init'
        else:
            word = word.split()
            # we need even input to simulate both input channels
#           if len(word) % 2 != 0:
#               return 'wait'

            inp = [(float(c)*0.4-0.2) for c in word]

            # construct input2 and input3 for matlab MQ
            # input1 is constant so no need for it
            # also modify ranges from [0,1) to desired
#           inp2 = []
#           inp3 = []

#           for i in range(0, len(inp), 2):
#               inp2.append(inp[i] * 0.4 - 0.2)
#               inp3.append(inp[i+1] * 8 - 4)

#           inp2 = matlab.double(inp2)
#           inp3 = matlab.double(inp3)

#           out = self.eng.quad_MQ(inp2, inp3)

            if len(inp) == 1:
                inp = [inp[0], inp[0]]

            inp = matlab.double(inp)
            out = self.eng.quad_MQ(inp)
            return self.concretizeOutput(out)


# input range, output range, spacing = 5 + 1 = 6

if len(sys.argv) < 4:
    print("Usage: python3 NNLearning.py outputLowBound outputUpperBound outputSize")
    exit()

outputLowBound = float(sys.argv[1])
outputUpperBound = float(sys.argv[2])
assert outputLowBound < outputUpperBound, "Output lower bound must be less than upper bound"

outputSize = int(sys.argv[3])
assert outputSize > 0, "Output size must be a positive integer"

T = NonAdequateTeacher_MM_Float(NNTeacher_quad(outputLowBound, outputUpperBound, outputSize), cex_length=20)

L = SymbLearner_MM_Float(T,e =.2, d = .2,  print_on = True, make_file = False, file_name_prefix = 'L'+str(1))

L.run()

print("Success!")

fileName = 'H_quad_output_' + str(outputLowBound) + '_' + str(outputUpperBound) + '_outputSize_' + str(outputSize)
L.hypothesis[-1].open_graph(fileName, typ = 'pdf')
