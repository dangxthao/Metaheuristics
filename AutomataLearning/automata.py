"""Here are some funcions that return automata on integers that can be used as learning targets"""
import random
import DFA
from myfunctions import cmpr
from learning import Float_Range
from SA import SA_Float, SMM_Float

def targetAutomaton_for_leq4partitions():
    """
    Automaton used as example for learning a language with at most 4 partitions
    with the method of sampling
    """
    states   = range(5)
    initial  = 0
    final    = [3,4]
    alphabet = [str(i) for i in range(51)]
    def delta(state, letter):
        assert state in states
        assert letter in alphabet

        if state == 0: return 4
        if state == 1:
            if   int(letter) < 3: return 1
            elif int(letter) < 6: return 0
            elif int(letter) <33: return 3
            else: return 4
        if state == 2:
            if   int(letter) <12: return 0
            elif int(letter) <34: return 2
            else: return 1
        if state == 3: return 2
        if state == 4:
            if   int(letter) < 1: return 4
            elif int(letter) < 5: return 3
            else: return 2

    return DFA.DFA(states, alphabet, delta, initial, final)




def automatonWith2partitions():
    """
    Define a difficult to learn target language
    """
    states = range(8)
    initial = 0
    final = [4]
    alphabet = [str(i) for i in range(101)]
    def delta(state, letter):
        if state == 0:
            if int(letter) <23:
                return 1
            else:
                return 2
        if state == 1:
            if int(letter) <72:
                return 3
            else:
                return 4
        if state == 2:
            return 3
        if state == 3:
            return 5
        if state == 4:
            return 5
        if state == 5:
            if int(letter) <43:
                return 7
            else:
                return 6
        if state == 6:
            if int(letter) <95:
                return 0
            else:
                return 7
        if state == 7:
            if int(letter) <12:
                return 5
            else:
                return 1

    return DFA.DFA(states, alphabet, delta, initial, final)


def random_dfa_on_integers(num_letters = 5, num_states = 4):
        """
        A random automaton on the integers.
        The number of letters of the alphabet and the number of states can be given.
        Alphabet is given int the form ['0','1','2',...]
        States are given in the form [0,1,2,...]
        Initial state is always 0.
        Final states are radomly chosen, as well as the transitions.
        """
        # check given values
        try:
                num_letters = int(num_letters)
                if num_letters < 0:
                        raise ValueError("Negative number of letters is given")
        except:
                print( "Invalid number of letters is given! Default is used instead")
                num_letters = 5
        try:
                num_states = int(num_states)
                if num_states < 0:
                        raise ValueError("Negative number of states is given")
        except:
                print("Invalid number of states is given! Default is used instead")
                num_states = 4

        # defining the components of the automaton
        alphabet = [str(i) for i in range(num_letters)]
        states = range(num_states)
        initial = 0
        final = random.sample(states, random.choice(states)+1 )

        # transition function
        keys = [(q,a)
                for q in states
                for a in alphabet]
        values = [random.choice(states)
                  for i in range(len(keys))]
        d = dict(zip(keys, values))

        def delta(state,letter):
                return d[(state,str(letter))]

        return DFA.DFA(states = states, start = initial, accepts = final, alphabet = alphabet, delta = delta)


def random_dfa_on_integers_max_part(num_letters = 5, num_states = 4, num_partitions = 4):
        """
        A random automaton on the integers.
        The number of letters of the alphabet and the number of states can be given.
        Alphabet is given int the form ['0','1','2',...].
        States are given in the form [0,1,2,...].
        Initial state is always 0.
        Final states are radomly chosen, as well as the transitions.
        From each state we can have at most num_partitions different transitions.
        """
        # check given values
        try:
                num_letters = int(num_letters)
                if num_letters < 0:
                        raise ValueError("Negative number of letters is given")
        except:
                num_letters = 5
                print("Invalid number of letters is given! Default is used instead")
        try:
                num_states = int(num_states)
                if num_states < 0:
                        raise ValueError("Negative number of states is given")
        except:
                num_states = 4
                print("Invalid number of states is given! Default is used instead")
        try:
                num_partitions = int(num_partitions)
                if num_partitions < 0:
                        raise ValueError("Negative number of partitions is given")
        except:
                num_partitions = 4
                print("Invalid number of partitions is given! Default is used instead")
        finally:
                # partitions can not be more than the number of the letters
                if num_partitions >= num_letters -1 :
                        num_partitions = num_letters - 1

        # defining the components of the automaton
        alphabet = [str(i) for i in range(num_letters)]
        states = range(num_states)
        initial = 0
        final = random.sample(states, random.choice(states)+1 )

        # we map to every state a number of partitions
        num_part = [num_partitions-1] + [random.choice(range(num_partitions))
                                      for q in states[:-1]]
        random.shuffle(num_part)
        npps = dict(zip(states,num_part))
        partitions = dict([(state, random.sample(alphabet[1:-1],npps[state]))
                             for state in states])

        d = {}
        for state in states:
                q = random.choice(states)
                for letter in alphabet:
                        if letter in partitions[state]:
                                q = random.choice(states)
                        d[(state,letter)] = q

        def delta(state, letter):
                return d[(state,str(letter))]

        return DFA.DFA(states = states, start = initial, accepts = final, alphabet = alphabet, delta = delta)



def test_automaton():
	states   = range(4)
	initial  = 0
	final    = [3]
	alphabet = [str(i) for i in range(101)]

	def delta(state,letter):
		assert state in states
		assert letter in alphabet
		if state == 0:
			if int(letter) < 82: return 1
			else: return 0
		elif state == 1:
			if int(letter) < 61: return 0
			else: return 2
		elif state == 2:
			if int(letter) < 93: return 3
			else: return 0
		else: # state == 3
			return 2

	return DFA.DFA(states = states, start = initial, accepts = final, alphabet = alphabet, delta = delta)

def test3_automaton():
	states   = range(4)
	initial  = 0
	final    = [3]
	alphabet = [str(i) for i in range(5)]

	def delta(state,letter):
		assert state in states
		assert letter in alphabet
		if state == 0:
			if int(letter) < 2: return 1
			else: return 0
		elif state == 1:
			if int(letter) < 3: return 0
			else: return 2
		elif state == 2:
			if int(letter) < 2: return 3
			else: return 0
		else: # state == 3
			return 2

	return DFA.DFA(states = states, start = initial, accepts = final, alphabet = alphabet, delta = delta)





def test2_automaton():
	states   = range(5)
	initial  = 0
	final    = [3]
	alphabet = [str(i) for i in range(101)]

	def delta(state,letter):
		assert state in states
		assert letter in alphabet
		if state == 0:
			if int(letter) < 82: return 1
			else: return 2
		elif state == 1:
			if int(letter) < 61: return 3
			else: return 4
		elif state == 2:
			if int(letter) < 93: return 3
			else: return 4
		else: # state == 3,4
			return 0

	return DFA.DFA(states = states, start = initial, accepts = final, alphabet = alphabet, delta = delta)




def automaton_fixed_structure(size_of_alphabet):
    states   = range(15)
    initial  = 0
    alphabet = [str(i) for i in range(size_of_alphabet)]
    final    = [0, 3, 6, 7, 11, 12, 13, 14]

    transition = {0 : [0, 1, 5, 7, 9] , 1 : [1, 5, 7] , 2 : [1, 6, 8, 11] , 3 : [1, 9] , 4 : [2, 9, 12] , 5 : [0, 3, 5, 11] , 6 : [1] , 7 : [4, 9, 11, 12] , 8 : [8, 10, 13] , 9 : [7] , 10 : [0, 5, 13] , 11 : [4, 5] , 12 : [0, 2, 9, 14] , 13 : [2, 8] , 14 : [6, 7, 13] }

    partitioning_point = dict([(state,sorted(random.sample(alphabet[:-1], len(transition[state])-1)+[alphabet[-1]], cmp = cmpr)) for state in states])

    def delta(state, letter):
        assert state in states
        assert letter in alphabet
        return transition[state][[int(letter) > int(i) for i in partitioning_point[state]].index(False) ]

    return DFA.DFA(states = states, start = initial, accepts = final, alphabet = alphabet, delta = delta)


# Test automaton teacher for float
class TestTeacher_Float:
    def __init__(self):
        self.concrete_alphabet = Float_Range(0, 10)
    def recognizes(self, word):
        if word == '':
            return False

        character_sequence = word.split(' ')
        float_sequence = [float(i) for i in character_sequence]
        if float_sequence[0] > 5:
            return True
        else:
            return False

# Test automaton teacher for float
class TestTeacher2_Float:
    def __init__(self):
        self.concrete_alphabet = Float_Range(0, 10)
    def recognizes(self, word):
        if word == '':
            return False

        character_sequence = word.split(' ')
        float_sequence = [float(i) for i in character_sequence]
        if float_sequence[0] > 5:
            if len(float_sequence) > 1:
                if float_sequence[1] < 3:
                    return True
                else:
                    return False
            return True
        else:
            return False

# Test symbolic automaton in thesis (Figure 6.1 of thesis)
def test_symbolic_automaton_float():
    concrete_alphabet = Float_Range(0, 100)

    symbolic_alphabet = []
    for i in range(0, 9):
        symbolic_alphabet.append('a' + str(i))

    states = range(0, 4)

    initial_state = 0

    final_states = [1, 3]

    def delta(q, c):
        if q == 0:
            if c == 'a0':
                return 1
            elif c == 'a1':
                return 2
            else:
                raise KeyError
        elif q == 1:
            if c == 'a2':
                return 3
            elif c == 'a3':
                return 2
            else:
                raise KeyError
        elif q == 2:
            if c == 'a4':
                return 0
            elif c == 'a5':
                return 1
            elif c == 'a6':
                return 3
            elif c == 'a7':
                return 2
            else:
                raise KeyError
        elif q == 3:
            if c == 'a8':
                return 2
            else:
                raise KeyError
        else:
            raise KeyError

    local_symbols = {0 : ['a0', 'a1'],
            1 : ['a2', 'a3'],
            2 : ['a4', 'a5', 'a6', 'a7'],
            3 : ['a8']}

    symbol_semantics = {'a0' : Float_Range(0, 50),
            'a1' : Float_Range(50, 100),
            'a2' : Float_Range(0, 30),
            'a3' : Float_Range(30, 100),
            'a4' : Float_Range(0, 20),
            'a5' : Float_Range(50, 80),
            'a6' : Float_Range(20, 50),
            'a7' : Float_Range(80, 100),
            'a8' : Float_Range(0, 100)}

    def psi(q, s):
        for ss in local_symbols[q]:
            if symbol_semantics[ss].contains(float(s)):
                return ss

    return SA_Float(concrete_alphabet,
            symbolic_alphabet,
            states,
            initial_state,
            final_states,
            psi,
            delta,
            local_symbols,
            symbol_semantics)


# Test symbolic moore machine representing the automaton above
def test_symbolic_mm_float():
    concrete_alphabet = Float_Range(0, 100)

    symbolic_alphabet = []
    for i in range(0, 9):
        symbolic_alphabet.append('a' + str(i))

    output_alphabet = [0, 1]

    states = range(0, 4)

    initial_state = 0

    final_states = [1, 3]

    def delta(q, c):
        if q == 0:
            if c == 'a0':
                return 1
            elif c == 'a1':
                return 2
            else:
                raise KeyError
        elif q == 1:
            if c == 'a2':
                return 3
            elif c == 'a3':
                return 2
            else:
                raise KeyError
        elif q == 2:
            if c == 'a4':
                return 0
            elif c == 'a5':
                return 1
            elif c == 'a6':
                return 3
            elif c == 'a7':
                return 2
            else:
                raise KeyError
        elif q == 3:
            if c == 'a8':
                return 2
            else:
                raise KeyError
        else:
            raise KeyError

    local_symbols = {0 : ['a0', 'a1'],
            1 : ['a2', 'a3'],
            2 : ['a4', 'a5', 'a6', 'a7'],
            3 : ['a8']}

    symbol_semantics = {'a0' : Float_Range(0, 50),
            'a1' : Float_Range(50, 100),
            'a2' : Float_Range(0, 30),
            'a3' : Float_Range(30, 100),
            'a4' : Float_Range(0, 20),
            'a5' : Float_Range(50, 80),
            'a6' : Float_Range(20, 50),
            'a7' : Float_Range(80, 100),
            'a8' : Float_Range(0, 100)}

    def psi(q, s):
        for ss in local_symbols[q]:
            if symbol_semantics[ss].contains(float(s)):
                return ss

    def output_function(q):
        if q in final_states:
            return 1
        else:
            return 0

    return SMM_Float(concrete_alphabet,
            symbolic_alphabet,
            output_alphabet,
            states,
            initial_state,
            output_function,
            psi,
            delta,
            local_symbols,
            symbol_semantics)



# Test symbolic moore machine representing the automaton above
def test_symbolic_mm_float2():
    concrete_alphabet = Float_Range(0, 100)

    symbolic_alphabet = []
    for i in range(0, 9):
        symbolic_alphabet.append('a' + str(i))

    output_alphabet = [1.1, 2.2, 3.3]

    states = range(0, 4)

    initial_state = 0

    def delta(q, c):
        if q == 0:
            if c == 'a0':
                return 1
            elif c == 'a1':
                return 2
            else:
                raise KeyError
        elif q == 1:
            if c == 'a2':
                return 3
            elif c == 'a3':
                return 2
            else:
                raise KeyError
        elif q == 2:
            if c == 'a4':
                return 0
            elif c == 'a5':
                return 1
            elif c == 'a6':
                return 3
            elif c == 'a7':
                return 2
            else:
                raise KeyError
        elif q == 3:
            if c == 'a8':
                return 2
            else:
                raise KeyError
        else:
            raise KeyError

    local_symbols = {0 : ['a0', 'a1'],
            1 : ['a2', 'a3'],
            2 : ['a4', 'a5', 'a6', 'a7'],
            3 : ['a8']}

    symbol_semantics = {'a0' : Float_Range(0, 50),
            'a1' : Float_Range(50, 100),
            'a2' : Float_Range(0, 30),
            'a3' : Float_Range(30, 100),
            'a4' : Float_Range(0, 20),
            'a5' : Float_Range(50, 80),
            'a6' : Float_Range(20, 50),
            'a7' : Float_Range(80, 100),
            'a8' : Float_Range(0, 100)}

    def psi(q, s):
        for ss in local_symbols[q]:
            if symbol_semantics[ss].contains(float(s)):
                return ss

    outputs = {0 : 1.1, 1 : 2.2, 2: 1.1, 3 : 3.3}

    return SMM_Float(concrete_alphabet,
            symbolic_alphabet,
            output_alphabet,
            states,
            initial_state,
            lambda q : outputs[q],
            psi,
            delta,
            local_symbols,
            symbol_semantics)

