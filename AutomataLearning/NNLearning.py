import matlab.engine
import sys
from learning import Float_Range, NonAdequateTeacher_MM_Float
from learning import SymbPACLearner_MM_Float as SymbLearner_MM_Float
import numpy as np
import time
class NNTeacher:
    def __init__(self, inputLowBound, inputUpperBound, outputLowBound, outputUpperBound, outputSize):
        if 'MATLAB_4242' not in matlab.engine.find_matlab():
            print("MATLAB session not found. Terminating...")
            sys.exit(-1)

        print("Connecting to MATLAB session...")
        self.eng = matlab.engine.connect_matlab('MATLAB_4242')
        print("Connected to MATLAB session successfully!")
        self.concrete_alphabet = Float_Range(inputLowBound, inputUpperBound)
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
        t0 = time.time()
        if word == '':
            t1 = time.time() - t0
#           print("Time:", t1)
            return 'init'
        else:
            word = word.split()
            inp = [float(c) for c in word]
            if len(inp) == 1:
                new = [inp[0]]
                new.extend(inp)
                inp = new
            inp = matlab.double(inp)
            out = self.eng.NN_MembershipQuery(inp)
            t1 = time.time() - t0
#           print("Time:", t1)
            return self.concretizeOutput(out)
#           if out > 0:
#               return 1.0
#           else:
#               return -1.0
    def compute_array(self, word_array):
        t0 = time.time()
        inp = matlab.double(word_array.tolist())
        out = self.eng.NN_ListMembershipQuery(inp)
        out = np.array(out).tolist()[0]
        res = [0] * len(out)
        for i in range(len(out)):
            res[i] = self.concretizeOutput(out[i])
        print(res)
        print(time.time() - t0)


# input range, output range, spacing = 5 + 1 = 6

if len(sys.argv) < 6:
    print("Usage: python3 NNLearning.py inputLowBound inputUpperBound outputLowBound outputUpperBound outputSize")
    exit()

inputLowBound = float(sys.argv[1])
inputUpperBound = float(sys.argv[2])
assert inputLowBound < inputUpperBound, "Input lower bound must be less than upper bound"

outputLowBound = float(sys.argv[3])
outputUpperBound = float(sys.argv[4])
assert outputLowBound < outputUpperBound, "Output lower bound must be less than upper bound"

outputSize = int(sys.argv[5])
assert outputSize > 0, "Output size must be a positive integer"

T = NonAdequateTeacher_MM_Float(NNTeacher(inputLowBound, inputUpperBound, outputLowBound, outputUpperBound, outputSize), cex_length=20)

L = SymbLearner_MM_Float(T,e =.1, d = .1,  print_on = False, file_name_prefix = 'L'+str(1))

L.run()

print("Success!")

fileName = 'H_input_' + str(inputLowBound) + '_' + str(inputUpperBound) + '_output_' + str(outputLowBound) + '_' + str(outputUpperBound) + '_outputSize_' + str(outputSize)
L.hypothesis[-1].open_graph(fileName, typ = 'pdf')
