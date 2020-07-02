"""
iPython functions
"""
import numpy as np
import matplotlib.pyplot as plt

import SA
##import myfunctions as mf

"""
There is integer overflow in numpy matrix power.
Particularly for this example the first overflow is noticed
np.linalg.matrix_power(v,9) where v = np.array(v).

Even when defining v elements as long then with the array changes them automatically to numpy.int64
long or long may would solve the problem
"""


def volume_up2length(self,max_length):
    """ ONLY FOR IPYTHON
    returns the size of language accepted by symbolic_automaton for string up to length k
    """
    ks = range(max_length)

    # the volume matrix as array
    v,d = self.volume_matrix() # d is a dictionary tha relates the states of the automaton to the row/column numbers
    V  = np.array(v)
    # elements we need to sum (paths starting from initial and end in some final state
    elements = [(d[self.initial],d[f]) for f in self.final]

    vk = np.linalg.linalg.identity(len(self.states))
    size = 0

    # length = 0
    size += sum([vk[i][j] for (i,j) in elements])

    for k in ks:
    #for length k = 1,2,3,.....
        vk = np.dot(vk,V)
        size += sum([vk[i][j] for (i,j) in elements])

    return size

def volume(self, length):
    """ ONLY FOR IPYTHON
    returns the size of language accepted by symbolic_automaton for strings of length k
    """
    # ks = range(length)
    # the volume matrix as array
    v,d = self.volume_matrix() # d is a dictionary tha relates the states of the automaton to the row/column numbers
    V  = np.array(v)
    # elements we need to sum (paths starting from initial and end in some final state
    elements = [(d[self.initial],d[f]) for f in self.final]

    vk = np.linalg.matrix_power(V,length)
    size = sum([vk[i][j] for (i,j) in elements])
    return size

def volumeValue(symb_automaton):
    """ returns a value that is the number where the error converges to"""
    j = 5
    v = [volume(symb_automaton,i)  for i in range(j)]

    while abs(sum(v[-5:])/5 - v[-1]) > 0.00001 and j < 100:
        j += 1
        v.append(volume(symb_automaton,j))

    return v[-1]


def convErrorSA(teacher, hypothesis):
    """ returns a value that is the number where the error converges to"""
    A = SA.dfa2sa(teacher.automaton)
    C = SA.symmetric_difference(A,hypothesis)
##    C.minimize()
    j = 2*len(teacher.automaton.states)

    v = [volume(C,i)  for i in range(j)]

    while abs(sum(v[-5:])/5 - v[-1]) > 0.001 and j < 100 and v[-1] > 0:
        j += 1
        v.append(volume(C,j))

    return v[-1]

def convErrorDFA(teacher, hypothesis):
    """ returns a value that is the number where the error converges to"""
    A = SA.dfa2sa(teacher.automaton)
    B = SA.dfa2sa(hypothesis)
    C = SA.symmetric_difference(A,B)
##    C.minimize()
    j = 2*len(teacher.automaton.states)

    v = [volume(C,i)  for i in range(j)]

    while abs(sum(v[-5:])/5 - v[-1]) > 0.001 and j < 100 and v[-1] > 0:
        j += 1
        v.append(volume(C,j))

    return v[-1]



def convErrorSeq(teacher, hypothesis):
    """ returns a value that is the number where the error converges to"""
    A = SA.dfa2sa(teacher.automaton)
    C = SA.symmetric_difference(A,hypothesis)
##    C.minimize()
    j = 2*len(teacher.automaton.states)

    v = [volume(C,m)  for m in range(j)]

    while abs(sum(v[-5:])/5 - v[-1]) > 0.001 and j < 100 and v[-1] > 0:
        j += 1
        v.append(volume(C,j))

    return v


##############################################################################
def makePlot1(teacher, hypotheses, rep = 100, prefix = 'L'):
    """
    Plot of error for list of automata compared to the teachers automaton
    """
    x = np.array(range(rep))
    e1,e2 = .01, .05
    A = SA.dfa2sa(teacher.automaton)

    fig = plt.figure()
    plt.plot([0,rep], [e1,e1], 'b-')
    plt.plot([0,rep], [e2,e2], 'g-')
    plt.xlabel('length')
    plt.ylabel('size/error')

    c = 0
    for h in hypotheses:
        C = SA.symmetric_difference(A,h)
        C.minimize()
        y = np.array([volume(C,j) for j in x])
        plt.plot(x,y, label=prefix+str(c))
        c += 1

    plt.ylim(ymax = plt.axis()[-1]+.01)
    plt.legend()
    return fig


def makePlot2(teacher, hypotheses, rep = 100, prefix = 'L'):
    """
    Plot of error for list of automata compared to the teachers automaton
    """
    x = np.array(range(rep))
    e1,e2 = .01, .05
    A = SA.dfa2sa(teacher.automaton)

    fig = plt.figure()
    plt.plot([0,rep], [e1,e1], 'b-')
##    plt.plot([0,rep], [e2,e2], 'g-')
    plt.xlabel('length')
    plt.ylabel('size/error')

    c = 0
    for h in hypotheses:
        C = SA.symmetric_difference(A,h)
##        C.minimize()
        y = np.array([volume(C,j) for j in x])
        plt.plot(x,y, label=prefix+str(c))
        c += 1

    plt.ylim(ymax = plt.axis()[-1]+.01)
    plt.legend()
    return fig


def makePlot3(teacher, learner):
    """ returns a figure where the error is calculated along the learning procedure"""
    x = np.array(range(len(learner.hypothesis)))
    e1,e2 = .01, .05
    A = SA.dfa2sa(teacher.automaton)

    y = []
    for h in learner.hypothesis:
        C = SA.symmetric_difference(A,h)
        C.minimize()
        y.append(volumeValue(C))

    y = np.array(y)

    fig = plt.figure()
    plt.plot([0,len(x)], [e1,e1], 'b-')
##    plt.plot([0,rep], [e2,e2], 'g-')
    plt.xlabel('hypotheses')
    plt.ylabel('size/error')
    plt.plot(x,y)
    plt.ylim(ymax = plt.axis()[-1]+.01)
    return fig



def makePlot4(teacher, learner):
    """ returns a figure where the error is calculated along the learning procedure"""
    x = np.array(range(len(learner.hypothesis)))
    e1,e2 = .01, .05
    A = SA.dfa2sa(teacher.automaton)

    y = []
    for h in learner.hypothesis:
        C = SA.symmetric_difference(A,h)
##        C.minimize()
        y.append(volumeValue(C))

    y = np.array(y)

    fig = plt.figure()
    plt.plot([0,len(x)], [e1,e1], 'b-')
##    plt.plot([0,rep], [e2,e2], 'g-')
    plt.xlabel('hypotheses')
    plt.ylabel('error')
    plt.plot(x,y)
    plt.ylim(ymax = plt.axis()[-1]+.01)
    return fig

def makePlot5(teacher, learners):
    """ returns a figure where the error is calculated along the learning procedure for several learners"""

    e1,e2 = .01, .05
    A = SA.dfa2sa(teacher.automaton)

    row = []
    for L in learners:
        y = []
        for h in L.hypothesis:
            C = SA.symmetric_difference(A,h)
            C.minimize()
            y.append(volumeValue(C))
        y = np.array(y)
        row.append(y)

    x = max([len(i) for i in row])
    fig = plt.figure()
    plt.plot([0,x], [e1,e1], 'b-')
    plt.plot([0,x], [e2,e2], 'g-')
    plt.xlabel('hypotheses')
    plt.ylabel('error')

    for i in range(len(row)):
        x = np.array(range(len(row[i])))
        plt.plot(x,row[i], label="L"+str(i))

    plt.ylim(ymax = plt.axis()[-1]+.01)
    plt.legend()
    return fig
