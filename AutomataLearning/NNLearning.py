import matlab.engine
import sys
from learning import Float_Range, NonAdequateTeacher_MM_Float
from learning import SymbPACLearner_MM_Float as SymbLearner_MM_Float

class NNTeacher:
    def __init__(self):
        if 'MATLAB_4242' not in matlab.engine.find_matlab():
            print("MATLAB session not found. Terminating...")
            sys.exit(-1)

        print("Connecting to MATLAB session...")
        self.eng = matlab.engine.connect_matlab('MATLAB_4242')
        print("Connected to MATLAB session successfully!")
        self.concrete_alphabet = Float_Range(-10, 10)
    def compute(self, word):
        if word == '':
            return 0.0
        else:
            word = word.split()
            inp = [float(c) for c in word]
            if len(inp) == 1:
                new = [inp[0]]
                new.extend(inp)
                inp = new
            inp = matlab.double(inp)
            out = self.eng.NN_MembershipQuery(inp)
            if out > 0:
                return 1.0
            else:
                return -1.0


T = NonAdequateTeacher_MM_Float(NNTeacher())

L = SymbLearner_MM_Float(T,e =.1, d = .1,  print_on = True, file_name_prefix = 'L'+str(1))

L.run()

print("Success!")

L.hypothesis[-1].open_graph('H')
