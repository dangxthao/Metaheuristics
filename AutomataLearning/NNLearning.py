import matlab.engine
import sys

if 'MATLAB_4242' not in matlab.engine.find_matlab():
    print("MATLAB session not found. Terminating...")
    sys.exit(-1)

print("Connecting to MATLAB session...")
eng = matlab.engine.connect_matlab('MATLAB_4242')
print("Connected to MATLAB session successfully!")


