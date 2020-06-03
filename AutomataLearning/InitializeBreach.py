import matlab.engine
import sys

if 'MATLAB_4242' in matlab.engine.find_matlab():
    print("MATLAB session already running. Terminating...")
    sys.exit(-1)

print("Starting MATLAB Engine...")
eng = matlab.engine.start_matlab()
eng.matlab.engine.shareEngine('MATLAB_4242', nargout=0)
print("MATLAB Engine started.")

eng.InitializeBreach(nargout=0)

input('Press enter to exit and end MATLAB session...')

