##--------------------------------------------------------------------------------------##
##-----------------------------------------------------------##
## Last Update: 10 April 2020: revised to run in python3
## Date: 2-Sept-2015
## Author:  IEMens
##
##--------------------------------------------------------------------------------------##
##-----------------------------------------------------------##
##     CONTENTS
##
## Class non Adequate Teacher
##
## Learning Classes:
##     Symbolic Learner
##     Angluin like Methods:
##         Lstar
##         Lstar Maler   -- When counter-example add all suffixes to distinguishing strings
##         Lstar Reduced -- Treat counter-examples with Breakpoint method
##
##
##--------------------------------------------------------------------------------------##
##-----------------------------------------------------------##
import random
import math
from functools import cmp_to_key
from myfunctions import cmpr, sconc, valid, valid_float, random_word, random_word_float, random_words_float, opengv
from SA import SA, SA_Float, SMM_Float
import DFA


import time



##--------------------------------------------------------------------------------------##
##-----------------------------------------------------------##
#                        Teacher classes

class NonAdequateTeacher:
    """
    The Teacher knows the target language, which is given to him in the form of a DFA.
    A Teacher is able to
    answer to membership query, and
    give a random word of specific or not lenght.
    """

    def __init__(self, deterministic_finite_automaton):
        """
        Provide the Teacher with a DFA(Deterministic Finite Automaton) that represents the target language
        """
        self.automaton = deterministic_finite_automaton
        self.alphabet = sorted(self.automaton.alphabet, key = cmp_to_key(cmpr))

    # Membership Query
    def membership_query(self, word):
        """
        Returns True if the word given is recognized by the language otherwise returns False.
        """
        return self.automaton.recognizes(word)

    # Testing Query
    def test(self, Hypothesis, i, e = .05, d = .05, print_on = True, test_on_alphabet = None):
        """
        Hypothesis: is the automaton checked
        i: is the number of the hypothesis made
        e: accuracy
        d: confidence
        Tests random words to find a counterexample,i.e., missclassified word. If after r_i repetitions no counterexample is detected then returns True.
        """
        if test_on_alphabet == None: test_on_alphabet = self.alphabet
        repetitions = 2*int(math.ceil(1/e*(math.log(1/d)+(i+1)*math.log(2))))
        if print_on: print('Test Words..')

        for j in range(repetitions):
            # choose a random word
            word = random_word(test_on_alphabet)
            if print_on: print('Test word:', word)
            if self.membership_query(word) != Hypothesis.recognizes(word):
                if print_on: print("  words tested:", j)
                return word, j

        if print_on: print("Number of words tested:", j)
        return True, j


##-----------------------------------------------------------##
#   NonAdequateTeacher_Float
# A special teacher for float is needed as the way sampling for test queries
# are done is different

class NonAdequateTeacher_Float:
    """
    The Teacher knows the target language, which is given to him in the form of a DFA.
    A Teacher is able to
    answer to membership query, and
    give a random word of specific or not lenght.
    """

    def __init__(self, deterministic_finite_automaton):
        """
        Provide the Teacher with a DFA(Deterministic Finite Automaton) that represents the target language
        """

        # The automaton passed to the teacher can be a function instead of an
        # automaton
        # However, here the alphabet should be of type Float_Range
        # The automaton or function must have a function called recognizes
        # which answers a membership query

        self.automaton = deterministic_finite_automaton
#       self.alphabet = sorted(self.automaton.alphabet, key = cmp_to_key(cmpr))
        self.alphabet = self.automaton.concrete_alphabet

    # Membership Query
    def membership_query(self, word):
        """
        Returns True if the word given is recognized by the language otherwise returns False.
        """
        return self.automaton.recognizes(word)

    # Testing Query
    def test(self, Hypothesis, i, e = .05, d = .05, print_on = True, test_on_alphabet = None):
        """
        Hypothesis: is the automaton checked
        i: is the number of the hypothesis made
        e: accuracy
        d: confidence
        Tests random words to find a counterexample,i.e., missclassified word. If after r_i repetitions no counterexample is detected then returns True.
        """
        # test_on_alphabet should be of type Float_Range
        if test_on_alphabet == None: test_on_alphabet = self.alphabet
        repetitions = 2*int(math.ceil(1/e*(math.log(1/d)+(i+1)*math.log(2))))
        if print_on: print('Test Words..')

        for j in range(repetitions):
            # choose a random word
#           word = random_word(test_on_alphabet)
            word = random_word_float(test_on_alphabet, length = len(Hypothesis.states) * 4)
            if print_on: print('Test word:', word)
            if self.membership_query(word) != Hypothesis.recognizes(word):
                if print_on: print("  words tested:", j)
                return word, j

        if print_on: print("Number of words tested:", j)
        return True, j


##-----------------------------------------------------------##
#   NonAdequateTeacher_MM_Float
# A special teacher for Moore machines is needed as it is computation not
# recognition

class NonAdequateTeacher_MM_Float:
    """
    A Teacher is able to
    answer to membership query, and
    give a random word of specific or not lenght.
    """

    def __init__(self, moore_machine, cex_length=100):
        """
        Provide the Teacher with an object that can do computations
        """

        # The automaton passed to the teacher can be a function instead of an
        # automaton
        # However, here the alphabet should be of type Float_Range
        # The automaton or function must have a function called recognizes
        # which answers a membership query

        self.moore_machine = moore_machine
#       self.alphabet = sorted(self.automaton.alphabet, key = cmp_to_key(cmpr))
        self.alphabet = self.moore_machine.concrete_alphabet
        self.cex_length = cex_length

    # Membership Query
    def membership_query(self, word):
        """
        Returns the output of the moore_machine or function passed to the automaton
        """
        return self.moore_machine.compute(word)

    # Testing Query
    def test(self, Hypothesis, i, e = .05, d = .05, print_on = True, test_on_alphabet = None):
        """
        Hypothesis: is the moore machine checked
        i: is the number of the hypothesis made
        e: accuracy
        d: confidence
        Tests random words to find a counterexample,i.e., missclassified word. If after r_i repetitions no counterexample is detected then returns True.
        """
        # test_on_alphabet should be of type Float_Range
        if test_on_alphabet == None: test_on_alphabet = self.alphabet
        repetitions = 2*int(math.ceil(1/e*(math.log(1/d)+(i+1)*math.log(2))))
        if print_on: print('Test Words..')
#       testing_words = random_words_float(test_on_alphabet, self.cex_length, repetitions)
#       self.moore_machine.compute_array(testing_words)
        for j in range(repetitions):
            # choose a random word
#           word = random_word(test_on_alphabet)
            word = random_word_float(test_on_alphabet, length = self.cex_length)
            if print_on: print('Test word:', word)
            if self.membership_query(word) != Hypothesis.compute(word):
                if print_on: print("  words tested:", j)
                return word, j

        if print_on: print("Number of words tested:", j)
        return True, j
##--------------------------------------------------------------------------------------##
##-----------------------------------------------------------##
#                        Observtaion Table classes

##-----------------------------------------------------------##
#  CONCRETE OBSERVATION TABLE

class OT:
    """
    This is an Observation Table as constructed by Angluin s algorithm.
    An observation table is a tuple T = (A, S, R, E, f), where
    - A is a finite alphabet
    - S is a prefix-closed subset of A*
    - R = S.A-S
    - E is a suffix-closed subset of A*
    - f : (SUR).E --> {0,1} is the classification function
    """
    def __init__(self, alphabet):
        self.alphabet = sorted(set(alphabet), key = cmp_to_key(cmpr))
        self.alphabet = [str(i) for i in self.alphabet]
        self.initialize()

    def initialize(self):
        """
        initialize S=E=''
        """
        self.S = ['']
        self.E = ['']
        self.f = {}

    def R(self):
        """the boundary set"""
        return [sconc(prefix,a) for prefix in self.S for a in self.alphabet if sconc(prefix,a) not in self.S]

    def row(self, prefix, suffix = None):
        """
        returns the row corresponding to the prefix for all current suffixes,
        if suffix is specified it returns the classification for the word scons(prefix, suffix)
        """
        if suffix or suffix == '':
            return int(self.f[sconc(prefix, suffix)])
        return [int(self.f[sconc(prefix, suffix)]) for suffix in self.E]

    def sample(self):
        """
        all words whose classification must be known to fill in the table
        """
        return sorted(set([sconc(s,e) for s in self.S+self.R() for e in self.E]))

    def add2f(self, word, boolean):
        """
        updates the classification function by adding to f a pair (word, classification of word)
        """
        assert valid(word, self.alphabet) or word == ''
        self.f[word] = bool(boolean)

    def states(self):
        """
        returns a list of distinct elements in prefixes that stand for the states of the automaton
        """
        states = []
        rows = []
        for prefix in self.S:
            if self.row(prefix) not in rows:
                states.append(prefix)
                rows.append(self.row(prefix))
        return states

    def is_closed(self):
        """check if table is close"""

        rows_in_S = [self.row(state) for state in self.states()]  # distinct rows in Prefixes S
## TO DO
    ## change this list to a for loop
        rows_not_in_S = [r for r in self.R() if self.row(r) not in rows_in_S]
        if rows_not_in_S: return False, rows_not_in_S[0]
        else: return True, None

    def is_reduced(self):
        """
        check if table is reduced
        """
        if len(self.states())==len(self.S):
            return True
        else:
            return False

    def is_consistent(self, print_on = False):
        """check if table is consistent. Return suffix for which table is not consistent."""

        equivRows = [(q,s)      # tuples of rows that are the same in prefixes
                     for q in self.states()
                     for s in self.S
                     if s != q and self.row(q) == self.row(s)]

        for (q,s) in equivRows: # check if tuple is compatible
            for a in self.alphabet:
                r1,r2 = self.row(sconc(q,a)) , self.row(sconc(s,a))
                if r1 != r2:
                    # rows are not the same, and thus table is not compatible
                    e = self.E[[i==j for i,j in zip(r1,r2)].index(False)]
                    return False, sconc(a,e)
        return True, None

    def delta(self, q, a):
        """
        Transitions derived from the table
        """
        assert q in self.states(), "not correct state"
        assert a in self.alphabet, "not correct letter"
        s_ = sconc(q,a)
        for state in self.states():
            if self.row(s_) == self.row(state): return state

    def automaton(self):
        """
        The automaton related to the table as DFA object
        """
        assert self.is_closed()[0], "Table is not closed"
        assert self.is_consistent()[0], "Table is not inconsistent"
        st = self.states()
        d1 = dict(zip(range(len(st)),st)) # (0,''), (1,'a0')
        d2 = dict(zip(st,range(len(st))))  # ('',0), ('a0',1)

        states = sorted(d1.keys())
        initial = 0
        final = [i for i in states if self.row(d1[i],'')]

        delta = lambda x,y : d2[self.delta(d1[x],y)]

        return DFA.DFA(states, self.alphabet, delta, initial, final)

    def printable(self):
        """
        returns a string that stands for the observation table printout
        """
        try:
            first_column_length = max([len(x) for x in self.R()]) + 1   # length of largest word in boundary
            columns_length = max([len(x) for x in self.E]) + 1        # length of largest word in suffixes

            table_rows = [' '*first_column_length + '|' + ' '.join([x.center(columns_length)
                                                                    for x in self.E])]
            table_rows.append('-'*len(table_rows[0]) + '-')

            for prefix in self.S:
                table_rows.append(prefix.rjust(first_column_length) +
                                  '|' + ' '.join([str(x).center(columns_length)
                                                  for x in self.row(prefix) ]))

            table_rows.append('-'*len(table_rows[0]) + '-')

            for prefix in self.R():
                table_rows.append(prefix.rjust(first_column_length) +
                                  '|' + ' '.join([str(x).center(columns_length)
                                                  for x in self.row(prefix) ]))
            s = '\n'
            for x in table_rows:
                s += x + '\n'
            return s
        except : # AttributeError or KeyError:
            return ''

    def __str__(self):
        s = "Angluin's observation table:\n"
        s += self.printable()
        return "\n<"+str(self.__module__)+".OT instance at " + str(hex(id(self)))+">" + s


##-----------------------------------------------------------##
#  SYMBOLIC OBSERVATION TABLE

class SymbPAC_ObsTable:
    """
    Observation Table used for the Extended Symbolic Learning Algorithm.
    T = (Ac, As, SS, RR, psi, E, ff, mu, mr)
     - Ac  = concrete_alphabet,
     - As  = symbolic_alphabet,
     - SS  = prefixes,
     - RR  = boundary,
     - psi = is a family of total surjective functions from Ac to a partition of Ac,
     - E   = suffixes,
     - ff  = symbolic classification_function,
     - mu  = evidence function
     - mr  = representative function
     """

    def __init__(self, concrete_alphabet):
        self.alphabet = sorted(concrete_alphabet, key = cmp_to_key(cmpr))  # concrete alphabet taken from the teacher
        self.sample_size = 5
        self.initialize()

    def initialize(self):

        self.prefixes = ['']                       # set of prefixes (list) subset of
        self.suffixes  = ['']                      # set of distinguishing strings (list)

        self.f = {}             # the concrete classification function  (dict)

        # for the symbols
        self.local_symb_alphabet = {}       # the symbolic alphabet (dist - changes during learning)
        self.sbound = {}                    # the boundary elements of the semantics [c,c')
        # the evidences
        self.mu = {}            # mu : As --> subset of Ac (dict)
        # The representative
        mr = [('','')] + [(i,str(i)) for i in self.alphabet]
        self.mr = dict(mr)      # mr : As U Ac --> Ac where mr(a) = a for all a \in Ac (dict)

        ## add the continuations of ''
        a0 = self.add_new_symbolic_letter('')  # initialized to contain one letter
        self.initSymbol(a0)                    # initialize new symb letter to local alphabet of state ''
## TO DO
    # make a function that gives the boundary
        self.boundary = [a0]                   # boundary (list)

        # fill in csample
        self.sample = set(['']+self.mu_ext(a0))

## check the table
    def check_validity(self):
        """
        make tests to see if table is observation table
        """
        # prefixes and boundary are valid symbolic strings
        for symb_word in self.prefixes[1:]:
            assert valid(symb_word, self.symb_alphabet()), symb_word+" is not valid"
        for symb_word in self.boundary:
            assert valid(symb_word, self.symb_alphabet()), symb_word+" is not valid"
        # SS \cap RR = empty set
            assert not symb_word in self.prefixes, "SS \cap RR != empty set"
        # SS U RR is prefix closed <= from construction

        # the evidence is subset of the semantics
        for symb_letter in self.symb_alphabet():
            semantics = self.sem(symb_letter)
            for letter in self.mu[symb_letter]:
                assert letter in semantics, 'evidence '+str(letter)+ "doesn't belong to semantics of "+str(symb_letter)
        # representative is element from evidences
            assert self.mr[symb_letter] in self.mu[symb_letter], "representative is not part of the evidence in "+str(symb_letter)

        # forming partitions
        for prefix in self.prefixes:
            coverage = []
            for letter in self.local_symb_alphabet[prefix]:
                coverage += self.mu[letter]
            assert len(coverage) > len(self.alphabet) or len(set(coverage)) != len(self.alphabet), "Is not a partition at state"+str(prefix)

        print("OK!")



## functions related to the table

    def mu_ext(self, symb_word):
        """
        extened evidence function
        """
        if symb_word == '':  # the empty word returns the empty word
            return ['']
        assert valid(symb_word, self.symb_alphabet())
        word = symb_word.split()
        ss,aa = ' '.join(word[:-1]), word[-1]
        return [sconc(self.mr_ext(ss), a) for a in self.mu[aa] ]

    def mr_ext(self, symb_word):
        """
        extened representative function
        """
        if symb_word == '':  # the empty word returns the empty word
            return ''
        assert type(symb_word) == str
        assert valid(symb_word, self.symb_alphabet().union(set(self.alphabet)))
        return ' '.join([str(self.mr[i])
                         for i in symb_word.split(' ')])


# residual functions
    def ff(self, prefix, suffix = None): # the row
        """
        ff : (SS U RR) E --> {-,+}
        the symbolic classification function related to the concrete one
        """
        if suffix in self.suffixes:
            return int(self.f[self.mr_ext(sconc(prefix,suffix))])
        return [int(self.f[self.mr_ext(sconc(prefix,e))]) for e in self.suffixes]

# samples
    def ssample(self):
        """
        all symbolic words derived from the prefixes (+boundary) and suffixes in the table
        """
        return sorted(set([sconc(s,str(e))
                           for s in self.prefixes + self.boundary
                           for e in self.suffixes]))

    def csample(self):
        """all words over the concrete alphabet in the table"""
        return sorted(self.sample)

# symbolic alphabet
    def initSymbol(self, symbol):
        """
        Initialize symbol
        """
        self.sbound[symbol] = ('lowBound', 'upperBound')   # no bounds means that all the concrete alphbaet is included
        self.mu[symbol] = sorted(random.sample(self.alphabet, self.sample_size), key = cmp_to_key(cmpr))  # sample(Ac, k)
        self.mr[symbol] = random.choice(self.mu[symbol])

    def symb_alphabet(self):
        """
        returns the (global) symbolic alphabet
        """
        return set([j
                    for i in self.local_symb_alphabet.values()
                    for j in i])

    def sem(self, symbol):
        """
        The semantics of a symbolic letter
        """
        assert symbol in self.symb_alphabet()
        left, right = self.sbound[symbol]
        # if no bounds are defined the semantics co
        if (left,right) == ('lowBound', 'upperBound'):
            return self.alphabet
        elif left == 'lowBound':
            return [i for i in self.alphabet
                    if cmpr(i,right) == -1]
        elif right == 'upperBound':
            return [i for i in self.alphabet
                    if cmpr(i,left) != -1]
        else:
            return [i for i in self.alphabet
                    if cmpr(i,left) != -1
                    and cmpr(i,right) == -1]

    def set_bounds(self, symbol, left = None, right = None):
        """
        Redefine the bounds for an existing symbol
        """
        assert symbol in self.sbounds.keys()
        if left == None:  left  = self.sbound[symbol][0]
        if right == None: right = self.sbound[symbol][1]
        self.sbound[symbol] = (left, right)

    def parent(self, symb_letter):
        """ returns the state (prefix) to whose alphabet symb_letter belongs"""
        assert symb_letter in self.symb_alphabet()
        for state in self.local_symb_alphabet:
            if symb_letter in self.local_symb_alphabet[state]: return state


## check table properties
    def is_closed(self):
        """
        Returns True if the table is closed
        False otherwise (with counterexample?)
        """
        rows = [r for r in self.boundary
                        if self.ff(r) not in [self.ff(s) for s in self.prefixes]]
        if rows: return False, rows[0]
        else: return True, None

    def is_reduced(self):
        """
        Returns True if the table is reduced
        False otherwise (with counterexample?)
        """
        rows = [tuple(self.ff(s)) for s in self.prefixes]
        if len(rows) == len(set(rows)): return True
        else: return False

    def is_evComp(self):
        """
        Returns True if the table is evidence compatible
        False otherwise (with counterexample?)
        """
        for prefix in self.prefixes + self.boundary:
            rows = [tuple(self.ff(s)) for s in self.mu_ext(prefix)]
            if len(set(rows)) >1 :
                pr = prefix.split()
                ss, aa = ' '.join(pr[:-1]), pr[-1]
                return False, ss
        return True, None


# add to table
    def add2f(self, word, boolean):
        """
        updates the concrete classification function by adding to f a pair (word, True/False)
        """
        assert valid(word, self.alphabet) or word == ''
        self.f[word] = bool(boolean)

    def add_new_symbolic_letter(self, state):
        """adds a new symbol to the symbolic alphabet and returns the new label
        """
        assert state in self.prefixes
        new_letter = 'a'+str(len(self.symb_alphabet()))
        self.local_symb_alphabet[state] = self.local_symb_alphabet.get(state,[]) + [new_letter]
        return new_letter

    def add2suffixes(self, word):
        """Adds a new suffix to suffixes and sorts the list (lengt-lexicographically).
           Returns False if the suffix was already in the set.
        """
        if word in self.suffixes: return False
        assert valid(word,self.alphabet)
        self.suffixes.append(word)
        self.suffixes.sort(key = cmp_to_key(cmpr)) #cmp = lambda a,b: cmpr(a,b))
        # update the sample
        self.add2sample([sconc(i,word) for s in self.prefixes+self.boundary for i in self.mu_ext(s) ])
        return True

    def add2sample(self, list_of_words):
        """ add to the concrete sample words """
        for word in list_of_words:
            assert valid(word,self.alphabet)
            self.sample.add(word)

    def add2mu(self, symb_letter, evidence):
        """adds a new evidence to the symbolic letter. Returns False is evidence was not added because it already existed"""
        assert symb_letter in self.symb_alphabet()
        assert evidence in self.alphabet
        assert evidence in self.sem(symb_letter)
        if evidence in self.mu.get(symb_letter,[]): return False # letter is already an evidence
        else:
            self.mu[symb_letter].append(evidence)
            self.mu[symb_letter].sort(key = cmp_to_key(cmpr))
            # update sample
            ## find which state symb_letter belongs and find representative for that
            prefix = self.mr_ext(self.parent(symb_letter))
            ## add to sample   mr(prefix) . evidence . e for e in suffixes
            self.add2sample([sconc(prefix, sconc(evidence,e)) for e in self.suffixes])
            return True

# move from boundary to prefixes
    def make_state(self, new_state):
        """An item from the boundary is moved to the prefixes and becomes a state.
        Then a new symbolic letter has to form its continuations and for this a sample is used to form its evidence.
        The table then need to be checked for evidence compatibility"""
        assert new_state in self.boundary
        # move it from the boundary to the prefixes
        self.prefixes.append(self.boundary.pop(self.boundary.index(new_state)))

        # add a new symbolic letter to stand for the new state continuations
        new_symb_letter = self.add_new_symbolic_letter(new_state)
        # add information to the boundary
        self.boundary.append(sconc(new_state, new_symb_letter))
        # initialize the new symbol
        self.initSymbol(new_symb_letter)
        # update sample
        self.add2sample([sconc(i,j) for i in self.mu_ext(sconc(new_state, new_symb_letter)) for j in self.suffixes])

# automaton
    def automaton(self):
        """
        Returns the symbolic automaton related to the table
        """
        assert self.is_closed()
        assert self.is_reduced()
        assert self.is_evComp()

        def g(r):
            """ g: RR --> SS (backedges)"""
            assert r in self.prefixes + self.boundary
            if r in self.prefixes: return r
            for state in self.prefixes:
                if self.ff(r) == self.ff(state):
                    return state
            raise ValueError("The table is not close")

        alphabet = self.alphabet
        symb_alph = sorted(self.symb_alphabet())

        d1 = dict(enumerate(list(self.prefixes)))   # (0,''), (1,'a0'), ...
        d2 = dict([(j,i) for (i,j) in d1.items()])  # ('',0), ('a0',1)

        Q  = range(len(d1))
        q0 = d2['']
        F  = [q for q in Q if self.ff(d1[q],'')]

        d = dict([((q,aa),d2[g(sconc(d1[q], aa))]) for q in Q for aa in self.local_symb_alphabet[d1[q]] ])
        def dd(state, symbol):
            assert state in Q
            assert symbol in symb_alph
            return d[(state,symbol)]

        p = dict([((q,i),aa) for q in Q for aa in self.local_symb_alphabet[d1[q]] for i in self.sem(aa)])
        def psi(state, letter):
            assert state in Q
            assert letter in alphabet
            return p[(state,letter)]

        return SA(concrete_alphabet = alphabet,
                  symbolic_alphabet = symb_alph,
                  states = Q,
                  initial_state = q0,
                  final_states = F,
                  psi = psi,
                  delta = dd)


# printing  the table
    def printMuAndSem(self):
        """prints the evidence function"""
        pass
        s = "" #"\nSemantics and Evidences:"
        for a in sorted(self.symb_alphabet()):
            s += "\n["+ a +"] = ["+ str(self.sbound[a][0]) +","+ str(self.sbound[a][1]) +"),"
            s += "\tmr("+ a + ") = "
            s += str(self.mr[a])
            s += ",\tm(" + a + ") = "
            s += str(self.mu[a])
        return s

    def printable(self):
        """prints the observation table"""
        first_column_length = max([len(x) for x in self.boundary]) + 1   # length of largest word in boundary
        columns_length = max([len(x) for x in self.suffixes]) + 1        # length of largest word in suffixes

        table_rows = [' '*first_column_length + '|' + ' '.join([x.center(columns_length)
                                                                for x in self.suffixes])]
        table_rows.append('-'*len(table_rows[0]) + '-')

        for prefix in self.prefixes:
            table_rows.append(prefix.rjust(first_column_length) +
                              '|' + ' '.join([str(x).center(columns_length)
                                              for x in self.ff(prefix) ]))

        table_rows.append('-'*len(table_rows[0]) + '-')

        for prefix in self.boundary:
            table_rows.append(prefix.rjust(first_column_length) +
                              '|' + ' '.join([str(x).center(columns_length)
                                              for x in self.ff(prefix) ]))

        table_rows.append('-'*len(table_rows[0]) + '-')

# print the evidences
        table_rows.append('-'*len(table_rows[0]) + '-')

        for prefix in self.prefixes[1:]+self.boundary:
            table_rows.append(prefix)
            for pre in self.mu_ext(prefix):
                table_rows.append(pre.rjust(first_column_length) +
                              '|' + ' '.join([str(x).center(columns_length)
                                              for x in self.ff(pre) ]))
            table_rows.append('-'*len(table_rows[0]) + '-')
#
        s = ''
        for x in table_rows:
            s += x + '\n'
        return s

    def __str__(self):
        s = 'Symbolic observation table:\n'
        s += 'SS = ' + str(sorted(self.symb_alphabet()))
        s += self.printMuAndSem() + '\n\n'
        s += self.printable()
        return "\n<"+str(self.__module__)+".ExtSL_ObsTable instance at " + str(hex(id(self)))+">\n" + s


##-----------------------------------------------------------##
#  SYMBOLIC OBSERVATION TABLE - FLOATS

class SymbPAC_ObsTable_Float:
    """
    Observation Table used for the Extended Symbolic Learning Algorithm.
    T = (Ac, As, SS, RR, psi, E, ff, mu, mr)
     - Ac  = concrete_alphabet,
     - As  = symbolic_alphabet,
     - SS  = prefixes,
     - RR  = boundary,
     - psi = is a family of total surjective functions from Ac to a partition of Ac,
     - E   = suffixes,
     - ff  = symbolic classification_function,
     - mu  = evidence function
     - mr  = representative function
     """

    # CONCRETE ALPHABET WILL HAVE TO BE OF TYPE Float_Range
    # Possible to git rid of concrete alphabet completely as a second step

    def __init__(self, alphabet):
        # self.alphabet = sorted(concrete_alphabet, key = cmp_to_key(cmpr))  # concrete alphabet taken from the teacher
        self.alphabet = alphabet
        self.sample_size = 5
        self.initialize()

    def initialize(self):

        self.prefixes = ['']                       # set of prefixes (list) subset of
        self.suffixes  = ['']                      # set of distinguishing strings (list)

        self.f = {}             # the concrete classification function  (dict)

        # for the symbols
        self.local_symb_alphabet = {}       # the symbolic alphabet (dist - changes during learning)
        self.sbound = {}                    # the boundary elements of the semantics [c,c')
        # the evidences
        self.mu = {}            # mu : As --> subset of Ac (dict)

        # The representative
        # TODONE: FIX mr(a) = a
        # In other words, mr should be: As --> Ac ONLY
#       mr = [('','')] + [(i,str(i)) for i in self.alphabet]
        mr = [('','')]
#       self.mr = dict(mr)      # mr : As U Ac --> Ac where mr(a) = a for all a \in Ac (dict)
        self.mr = dict(mr)      # mr : As --> Ac

        ## add the continuations of ''
        a0 = self.add_new_symbolic_letter('')  # initialized to contain one letter
        self.initSymbol(a0)                    # initialize new symb letter to local alphabet of state ''
## TO DO
    # make a function that gives the boundary
        self.boundary = [a0]                   # boundary (list)

        # fill in csample
        # TODONE: fix sample
        self.sample = set(['']+self.mu_ext(a0))

## check the table
    def check_validity(self):
        """
        make tests to see if table is observation table
        """
        # prefixes and boundary are valid symbolic strings
        for symb_word in self.prefixes[1:]:
            assert valid(symb_word, self.symb_alphabet()), symb_word+" is not valid"
        for symb_word in self.boundary:
            assert valid(symb_word, self.symb_alphabet()), symb_word+" is not valid"
        # SS \cap RR = empty set
            assert not symb_word in self.prefixes, "SS \cap RR != empty set"
        # SS U RR is prefix closed <= from construction

        # the evidence is subset of the semantics
        for symb_letter in self.symb_alphabet():
            semantics = self.sem(symb_letter)
            for letter in self.mu[symb_letter]:
                assert semantics.contains(float(letter)), 'evidence '+str(letter)+ "doesn't belong to semantics of "+str(symb_letter)
        # representative is element from evidences
            assert self.mr[symb_letter] in self.mu[symb_letter], "representative is not part of the evidence in "+str(symb_letter)

        # TODO: fix partitions len(self.alphabet)
        # forming partitions
        # The below assertion seems to be always false (?) commenting for now
#       for prefix in self.prefixes:
#           coverage = []
#           for letter in self.local_symb_alphabet[prefix]:
#               coverage += self.mu[letter]
#           assert len(coverage) > len(self.alphabet) or len(set(coverage)) != len(self.alphabet), "Is not a partition at state"+str(prefix)

        print("OK!")



## functions related to the table

    # mu_ext seems to take a symb_word w1, w2, ..., wn
    # and return a string of mr(w1), mr(w2), ..., mr(wn-1), mu(wn)
    # for all mu(wn)
    def mu_ext(self, symb_word):
        """
        extened evidence function
        """
        if symb_word == '':  # the empty word returns the empty word
            return ['']
        assert valid(symb_word, self.symb_alphabet())
        word = symb_word.split()
        ss,aa = ' '.join(word[:-1]), word[-1]
        return [sconc(self.mr_ext(ss), a) for a in self.mu[aa] ]

    def mr_ext(self, symb_word):
        """
        extened representative function
        """
        if symb_word == '':  # the empty word returns the empty word
            return ''
        assert type(symb_word) == str
        # TODONE: Fix the assertion
        # assert valid(symb_word, self.symb_alphabet().union(set(self.alphabet)))
        chars = symb_word.split(' ')
        for c in chars:
            assert c in self.symb_alphabet() or self.alphabet.contains(float(c))

        # TODONE: Check if symb_word ever contains concrete alphabet
        return ' '.join([str(self.mr[i]) if i in self.symb_alphabet() else i
                         for i in symb_word.split(' ')])


# residual functions
    ## ff either returns the entry for prefix, suffix or returns the whole row
    def ff(self, prefix, suffix = None): # the row
        """
        ff : (SS U RR) E --> {-,+}
        the symbolic classification function related to the concrete one
        """
        if suffix in self.suffixes:
            return int(self.f[self.mr_ext(sconc(prefix,suffix))])
        return [int(self.f[self.mr_ext(sconc(prefix,e))]) for e in self.suffixes]

# samples
    def ssample(self):
        """
        all symbolic words derived from the prefixes (+boundary) and suffixes in the table
        """
        return sorted(set([sconc(s,str(e))
                           for s in self.prefixes + self.boundary
                           for e in self.suffixes]))

    def csample(self):
        """all words over the concrete alphabet in the table"""
        return sorted(self.sample)

# symbolic alphabet
    def initSymbol(self, symbol):
        """
        Initialize symbol
        """
#       self.sbound[symbol] = ('lowBound', 'upperBound')   # no bounds means that all the concrete alphbaet is included
        self.sbound[symbol] = (str(self.alphabet.lowBound), str(self.alphabet.upperBound)) # initially all concrete is included
        # self.mu[symbol] = sorted(random.sample(self.alphabet, self.sample_size), key = cmp_to_key(cmpr))  # sample(Ac, k)
        self.mu[symbol] = [str(i) for i in sorted(self.alphabet.sample(self.sample_size))]
        self.mr[symbol] = random.choice(self.mu[symbol])

    def symb_alphabet(self):
        """
        returns the (global) symbolic alphabet
        """
        return set([j
                    for i in self.local_symb_alphabet.values()
                    for j in i])

    def sem(self, symbol):
        """
        The semantics of a symbolic letter
        """
        assert symbol in self.symb_alphabet()
        left, right = self.sbound[symbol]

#       # if no bounds are defined the semantics co
#       if (left,right) == ('lowBound', 'upperBound'):
#           return self.alphabet
#       elif left == 'lowBound':
#           return [i for i in self.alphabet
#                   if cmpr(i,right) == -1]
#       elif right == 'upperBound':
#           return [i for i in self.alphabet
#                   if cmpr(i,left) != -1]
#       else:
#           return [i for i in self.alphabet
#                   if cmpr(i,left) != -1
#                   and cmpr(i,right) == -1]
        return Float_Range(float(left), float(right))

    def set_bounds(self, symbol, left = None, right = None):
        """
        Redefine the bounds for an existing symbol
        """
        assert symbol in self.sbounds.keys()
        if left == None:  left  = self.sbound[symbol][0]
        if right == None: right = self.sbound[symbol][1]
        self.sbound[symbol] = (left, right)

    def parent(self, symb_letter):
        """ returns the state (prefix) to whose alphabet symb_letter belongs"""
        assert symb_letter in self.symb_alphabet()
        for state in self.local_symb_alphabet:
            if symb_letter in self.local_symb_alphabet[state]: return state


## check table properties
    def is_closed(self):
        """
        Returns True if the table is closed
        False otherwise (with counterexample?)
        """
        rows = [r for r in self.boundary
                        if self.ff(r) not in [self.ff(s) for s in self.prefixes]]
        if rows: return False, rows[0]
        else: return True, None

    def is_reduced(self):
        """
        Returns True if the table is reduced
        False otherwise (with counterexample?)
        """
        rows = [tuple(self.ff(s)) for s in self.prefixes]
        if len(rows) == len(set(rows)): return True
        else: return False

    def is_evComp(self):
        """
        Returns True if the table is evidence compatible
        False otherwise (with counterexample?)
        """
        for prefix in self.prefixes + self.boundary:
            rows = [tuple(self.ff(s)) for s in self.mu_ext(prefix)]
            if len(set(rows)) >1 :
                pr = prefix.split()
                ss, aa = ' '.join(pr[:-1]), pr[-1]
                return False, ss
        return True, None


# add to table
    def add2f(self, word, boolean):
        """
        updates the concrete classification function by adding to f a pair (word, True/False)
        """
        assert word == '' or valid_float(word, self.alphabet)
        self.f[word] = bool(boolean)

    def add_new_symbolic_letter(self, state):
        """adds a new symbol to the symbolic alphabet and returns the new label
        """
        assert state in self.prefixes
        new_letter = 'a'+str(len(self.symb_alphabet()))
        self.local_symb_alphabet[state] = self.local_symb_alphabet.get(state,[]) + [new_letter]
        return new_letter

    def add2suffixes(self, word):
        """Adds a new suffix to suffixes and sorts the list (lengt-lexicographically).
           Returns False if the suffix was already in the set.
        """
        if word in self.suffixes: return False
        assert valid_float(word,self.alphabet)
        self.suffixes.append(word)
        self.suffixes.sort(key = cmp_to_key(cmpr)) #cmp = lambda a,b: cmpr(a,b))
        # update the sample
        self.add2sample([sconc(i,word) for s in self.prefixes+self.boundary for i in self.mu_ext(s) ])
        return True

    def add2sample(self, list_of_words):
        """ add to the concrete sample words """
        for word in list_of_words:
            assert valid_float(word,self.alphabet)
            self.sample.add(word)

    def add2mu(self, symb_letter, evidence):
        """adds a new evidence to the symbolic letter. Returns False is evidence was not added because it already existed"""
        assert symb_letter in self.symb_alphabet()
#       assert evidence in self.alphabet
#       assert evidence in self.sem(symb_letter)

        assert self.alphabet.contains(float(evidence))
        assert self.sem(symb_letter).contains(float(evidence))

        if evidence in self.mu.get(symb_letter,[]): return False # letter is already an evidence
        else:
            self.mu[symb_letter].append(evidence)
            self.mu[symb_letter].sort(key = cmp_to_key(cmpr))
            # update sample
            ## find which state symb_letter belongs and find representative for that
            prefix = self.mr_ext(self.parent(symb_letter))
            ## add to sample   mr(prefix) . evidence . e for e in suffixes
            self.add2sample([sconc(prefix, sconc(evidence,e)) for e in self.suffixes])
            return True

# move from boundary to prefixes
    def make_state(self, new_state):
        """An item from the boundary is moved to the prefixes and becomes a state.
        Then a new symbolic letter has to form its continuations and for this a sample is used to form its evidence.
        The table then need to be checked for evidence compatibility"""
        assert new_state in self.boundary
        # move it from the boundary to the prefixes
        self.prefixes.append(self.boundary.pop(self.boundary.index(new_state)))

        # add a new symbolic letter to stand for the new state continuations
        new_symb_letter = self.add_new_symbolic_letter(new_state)
        # add information to the boundary
        self.boundary.append(sconc(new_state, new_symb_letter))
        # initialize the new symbol
        self.initSymbol(new_symb_letter)
        # update sample
        self.add2sample([sconc(i,j) for i in self.mu_ext(sconc(new_state, new_symb_letter)) for j in self.suffixes])
        # for all mu(wn)

# automaton
    def automaton(self):
        """
        Returns the symbolic automaton related to the table
        """
        assert self.is_closed()
        assert self.is_reduced()
        assert self.is_evComp()

        def g(r):
            """ g: RR --> SS (backedges)"""
            assert r in self.prefixes + self.boundary
            if r in self.prefixes: return r
            for state in self.prefixes:
                if self.ff(r) == self.ff(state):
                    return state
            raise ValueError("The table is not close")

        alphabet = self.alphabet
        symb_alph = sorted(self.symb_alphabet())

        d1 = dict(enumerate(list(self.prefixes)))   # (0,''), (1,'a0'), ...
        d2 = dict([(j,i) for (i,j) in d1.items()])  # ('',0), ('a0',1)

        # Set of states, starting state and accepting states
        Q  = range(len(d1))
        q0 = d2['']
        F  = [q for q in Q if self.ff(d1[q],'')]

        # Transition function d, dd
        d = dict([((q,aa),d2[g(sconc(d1[q], aa))]) for q in Q for aa in self.local_symb_alphabet[d1[q]] ])
        def dd(state, symbol):
            assert state in Q
            assert symbol in symb_alph
            return d[(state,symbol)]

#       p = dict([((q,i),aa) for q in Q for aa in self.local_symb_alphabet[d1[q]] for i in self.sem(aa)])

        # given state, and letter psi is supposed to return the symbolic
        # letter that letter belongs to in the local symbols of state
        def psi(state, letter):
            assert state in Q
#           assert letter in alphabet
            assert alphabet.contains(float(letter))
#           return p[(state,letter)]
            for aa in self.local_symb_alphabet[d1[state]]:
                if self.sem(aa).contains(float(letter)):
                    return aa
            raise ValueError("Letter not found in state's local symb alphabet")

        local_symbols = dict([(q, self.local_symb_alphabet[d1[q]]) for q in Q])
        symbol_semantics = dict([(aa, self.sem(aa)) for aa in symb_alph])
        # Build an automaton SA_Float whose concrete alphabet is of type
        # Float_Range
        return SA_Float(concrete_alphabet = alphabet,
                  symbolic_alphabet = symb_alph,
                  states = Q,
                  initial_state = q0,
                  final_states = F,
                  psi = psi,
                  delta = dd,
                  local_symbols = local_symbols,
                  symbol_semantics = symbol_semantics)


# printing  the table
    def printMuAndSem(self):
        """prints the evidence function"""
        pass
        s = "" #"\nSemantics and Evidences:"
        for a in sorted(self.symb_alphabet()):
            s += "\n["+ a +"] = ["+ str(self.sbound[a][0]) +","+ str(self.sbound[a][1]) +"),"
            s += "\tmr("+ a + ") = "
            s += str(self.mr[a])
            s += ",\tm(" + a + ") = "
            s += str(self.mu[a])
        return s

    def printable(self):
        """prints the observation table"""
        first_column_length = max([len(x) for x in self.boundary]) + 1   # length of largest word in boundary
        columns_length = max([len(x) for x in self.suffixes]) + 1        # length of largest word in suffixes

        table_rows = [' '*first_column_length + '|' + ' '.join([x.center(columns_length)
                                                                for x in self.suffixes])]
        table_rows.append('-'*len(table_rows[0]) + '-')

        for prefix in self.prefixes:
            table_rows.append(prefix.rjust(first_column_length) +
                              '|' + ' '.join([str(x).center(columns_length)
                                              for x in self.ff(prefix) ]))

        table_rows.append('-'*len(table_rows[0]) + '-')

        for prefix in self.boundary:
            table_rows.append(prefix.rjust(first_column_length) +
                              '|' + ' '.join([str(x).center(columns_length)
                                              for x in self.ff(prefix) ]))

        table_rows.append('-'*len(table_rows[0]) + '-')

# print the evidences
        table_rows.append('-'*len(table_rows[0]) + '-')

        for prefix in self.prefixes[1:]+self.boundary:
            table_rows.append(prefix)
            for pre in self.mu_ext(prefix):
                table_rows.append(pre.rjust(first_column_length) +
                              '|' + ' '.join([str(x).center(columns_length)
                                              for x in self.ff(pre) ]))
            table_rows.append('-'*len(table_rows[0]) + '-')
#
        s = ''
        for x in table_rows:
            s += x + '\n'
        return s

    def __str__(self):
        s = 'Symbolic observation table:\n'
        s += 'SS = ' + str(sorted(self.symb_alphabet()))
        s += self.printMuAndSem() + '\n\n'
        s += self.printable()
        return "\n<"+str(self.__module__)+".ExtSL_ObsTable instance at " + str(hex(id(self)))+">\n" + s



##-----------------------------------------------------------##
#  SYMBOLIC OBSERVATION TABLE - MOORE MACHINE FLOATS

class SymbPAC_ObsTable_MM_Float:
    """
    Observation Table used for the Extended Symbolic Learning Algorithm.
    T = (Ac, As, SS, RR, psi, E, ff, mu, mr)
     - Ac  = concrete_alphabet,
     - As  = symbolic_alphabet,
     - SS  = prefixes,
     - RR  = boundary,
     - psi = is a family of total surjective functions from Ac to a partition of Ac,
     - E   = suffixes,
     - ff  = symbolic output function,
     - mu  = evidence function
     - mr  = representative function
     """

    # CONCRETE ALPHABET WILL HAVE TO BE OF TYPE Float_Range
    # Possible to git rid of concrete alphabet completely as a second step

    def __init__(self, alphabet):
        # self.alphabet = sorted(concrete_alphabet, key = cmp_to_key(cmpr))  # concrete alphabet taken from the teacher
        self.alphabet = alphabet
        self.sample_size = 10
        self.initialize()

    def initialize(self):

        self.prefixes = ['']                       # set of prefixes (list) subset of
        self.suffixes  = ['']                      # set of distinguishing strings (list)

        self.f = {}             # the concrete classification function  (dict)

        # for the symbols
        self.local_symb_alphabet = {}       # the symbolic alphabet (dist - changes during learning)
        self.sbound = {}                    # the boundary elements of the semantics [c,c')
        # the evidences
        self.mu = {}            # mu : As --> subset of Ac (dict)

        # The representative
        # TODONE: FIX mr(a) = a
        # In other words, mr should be: As --> Ac ONLY
#       mr = [('','')] + [(i,str(i)) for i in self.alphabet]
        mr = [('','')]
#       self.mr = dict(mr)      # mr : As U Ac --> Ac where mr(a) = a for all a \in Ac (dict)
        self.mr = dict(mr)      # mr : As --> Ac

        ## add the continuations of ''
        a0 = self.add_new_symbolic_letter('')  # initialized to contain one letter
        self.initSymbol(a0)                    # initialize new symb letter to local alphabet of state ''
## TO DO
    # make a function that gives the boundary
        self.boundary = [a0]                   # boundary (list)

        # fill in csample
        # TODONE: fix sample
        self.sample = set(['']+self.mu_ext(a0))

## check the table
    def check_validity(self):
        """
        make tests to see if table is observation table
        """
        # prefixes and boundary are valid symbolic strings
        for symb_word in self.prefixes[1:]:
            assert valid(symb_word, self.symb_alphabet()), symb_word+" is not valid"
        for symb_word in self.boundary:
            assert valid(symb_word, self.symb_alphabet()), symb_word+" is not valid"
        # SS \cap RR = empty set
            assert not symb_word in self.prefixes, "SS \cap RR != empty set"
        # SS U RR is prefix closed <= from construction

        # the evidence is subset of the semantics
        for symb_letter in self.symb_alphabet():
            semantics = self.sem(symb_letter)
            for letter in self.mu[symb_letter]:
                assert semantics.contains(float(letter)), 'evidence '+str(letter)+ "doesn't belong to semantics of "+str(symb_letter)
        # representative is element from evidences
            assert self.mr[symb_letter] in self.mu[symb_letter], "representative is not part of the evidence in "+str(symb_letter)

        # TODO: fix partitions len(self.alphabet)
        # forming partitions
        # The below assertion seems to be always false (?) commenting for now
#       for prefix in self.prefixes:
#           coverage = []
#           for letter in self.local_symb_alphabet[prefix]:
#               coverage += self.mu[letter]
#           assert len(coverage) > len(self.alphabet) or len(set(coverage)) != len(self.alphabet), "Is not a partition at state"+str(prefix)

        print("OK!")



## functions related to the table

    # mu_ext seems to take a symb_word w1, w2, ..., wn
    # and return a string of mr(w1), mr(w2), ..., mr(wn-1), mu(wn)
    # for all mu(wn)
    def mu_ext(self, symb_word):
        """
        extened evidence function
        """
        if symb_word == '':  # the empty word returns the empty word
            return ['']
        assert valid(symb_word, self.symb_alphabet())
        word = symb_word.split()
        ss,aa = ' '.join(word[:-1]), word[-1]
        return [sconc(self.mr_ext(ss), a) for a in self.mu[aa] ]

    def mr_ext(self, symb_word):
        """
        extened representative function
        """
        if symb_word == '':  # the empty word returns the empty word
            return ''
        assert type(symb_word) == str
        # TODONE: Fix the assertion
        # assert valid(symb_word, self.symb_alphabet().union(set(self.alphabet)))
        chars = symb_word.split(' ')
        for c in chars:
            assert c in self.symb_alphabet() or self.alphabet.contains(float(c))

        # TODONE: Check if symb_word ever contains concrete alphabet
        return ' '.join([str(self.mr[i]) if i in self.symb_alphabet() else i
                         for i in symb_word.split(' ')])


# residual functions
    ## ff either returns the entry for prefix, suffix or returns the whole row
    def ff(self, prefix, suffix = None): # the row
        """
        ff : (SS U RR) E --> output_alphabet
        the symbolic classification function related to the concrete one
        """
        if suffix in self.suffixes:
            return self.f[self.mr_ext(sconc(prefix,suffix))]
        return [self.f[self.mr_ext(sconc(prefix,e))] for e in self.suffixes]

# samples
    def ssample(self):
        """
        all symbolic words derived from the prefixes (+boundary) and suffixes in the table
        """
        return sorted(set([sconc(s,str(e))
                           for s in self.prefixes + self.boundary
                           for e in self.suffixes]))

    def csample(self):
        """all words over the concrete alphabet in the table"""
        return sorted(self.sample)

# symbolic alphabet
    def initSymbol(self, symbol):
        """
        Initialize symbol
        """
#       self.sbound[symbol] = ('lowBound', 'upperBound')   # no bounds means that all the concrete alphbaet is included
        self.sbound[symbol] = (str(self.alphabet.lowBound), str(self.alphabet.upperBound)) # initially all concrete is included
        # self.mu[symbol] = sorted(random.sample(self.alphabet, self.sample_size), key = cmp_to_key(cmpr))  # sample(Ac, k)
        self.mu[symbol] = [str(i) for i in sorted(self.alphabet.sample(self.sample_size))]
        self.mr[symbol] = random.choice(self.mu[symbol])

    def symb_alphabet(self):
        """
        returns the (global) symbolic alphabet
        """
        return set([j
                    for i in self.local_symb_alphabet.values()
                    for j in i])

    def sem(self, symbol):
        """
        The semantics of a symbolic letter
        """
        assert symbol in self.symb_alphabet()
        left, right = self.sbound[symbol]

#       # if no bounds are defined the semantics co
#       if (left,right) == ('lowBound', 'upperBound'):
#           return self.alphabet
#       elif left == 'lowBound':
#           return [i for i in self.alphabet
#                   if cmpr(i,right) == -1]
#       elif right == 'upperBound':
#           return [i for i in self.alphabet
#                   if cmpr(i,left) != -1]
#       else:
#           return [i for i in self.alphabet
#                   if cmpr(i,left) != -1
#                   and cmpr(i,right) == -1]
        return Float_Range(float(left), float(right))

    def set_bounds(self, symbol, left = None, right = None):
        """
        Redefine the bounds for an existing symbol
        """
        assert symbol in self.sbounds.keys()
        if left == None:  left  = self.sbound[symbol][0]
        if right == None: right = self.sbound[symbol][1]
        self.sbound[symbol] = (left, right)

    def parent(self, symb_letter):
        """ returns the state (prefix) to whose alphabet symb_letter belongs"""
        assert symb_letter in self.symb_alphabet()
        for state in self.local_symb_alphabet:
            if symb_letter in self.local_symb_alphabet[state]: return state


## check table properties
    def is_closed(self):
        """
        Returns True if the table is closed
        False otherwise (with counterexample?)
        """
        rows = [r for r in self.boundary
                        if self.ff(r) not in [self.ff(s) for s in self.prefixes]]
        if rows: return False, rows[0]
        else: return True, None

    def is_reduced(self):
        """
        Returns True if the table is reduced
        False otherwise (with counterexample?)
        """
        rows = [tuple(self.ff(s)) for s in self.prefixes]
        if len(rows) == len(set(rows)): return True
        else: return False

    def is_evComp(self):
        """
        Returns True if the table is evidence compatible
        False otherwise (with counterexample?)
        """
        for prefix in self.prefixes + self.boundary:
            rows = [tuple(self.ff(s)) for s in self.mu_ext(prefix)]
            if len(set(rows)) >1 :
                pr = prefix.split()
                ss, aa = ' '.join(pr[:-1]), pr[-1]
                return False, ss
        return True, None


# add to table
    def add2f(self, word, output):
        """
        updates the concrete classification function by adding to f a pair (word, True/False)
        """
        assert word == '' or valid_float(word, self.alphabet)
        self.f[word] = output

    def add_new_symbolic_letter(self, state):
        """adds a new symbol to the symbolic alphabet and returns the new label
        """
        assert state in self.prefixes
        new_letter = 'a'+str(len(self.symb_alphabet()))
        self.local_symb_alphabet[state] = self.local_symb_alphabet.get(state,[]) + [new_letter]
        return new_letter

    def add2suffixes(self, word):
        """Adds a new suffix to suffixes and sorts the list (lengt-lexicographically).
           Returns False if the suffix was already in the set.
        """
        if word in self.suffixes: return False
        assert valid_float(word,self.alphabet)
        self.suffixes.append(word)
        self.suffixes.sort(key = cmp_to_key(cmpr)) #cmp = lambda a,b: cmpr(a,b))
        # update the sample
        self.add2sample([sconc(i,word) for s in self.prefixes+self.boundary for i in self.mu_ext(s) ])
        return True

    def add2sample(self, list_of_words):
        """ add to the concrete sample words """
        for word in list_of_words:
            assert valid_float(word,self.alphabet)
            self.sample.add(word)

    def add2mu(self, symb_letter, evidence):
        """adds a new evidence to the symbolic letter. Returns False is evidence was not added because it already existed"""
        assert symb_letter in self.symb_alphabet()
#       assert evidence in self.alphabet
#       assert evidence in self.sem(symb_letter)

        assert self.alphabet.contains(float(evidence))
        assert self.sem(symb_letter).contains(float(evidence))

        if evidence in self.mu.get(symb_letter,[]): return False # letter is already an evidence
        else:
            self.mu[symb_letter].append(evidence)
            self.mu[symb_letter].sort(key = cmp_to_key(cmpr))
            # update sample
            ## find which state symb_letter belongs and find representative for that
            prefix = self.mr_ext(self.parent(symb_letter))
            ## add to sample   mr(prefix) . evidence . e for e in suffixes
            self.add2sample([sconc(prefix, sconc(evidence,e)) for e in self.suffixes])
            return True

# move from boundary to prefixes
    def make_state(self, new_state):
        """An item from the boundary is moved to the prefixes and becomes a state.
        Then a new symbolic letter has to form its continuations and for this a sample is used to form its evidence.
        The table then need to be checked for evidence compatibility"""
        assert new_state in self.boundary
        # move it from the boundary to the prefixes
        self.prefixes.append(self.boundary.pop(self.boundary.index(new_state)))

        # add a new symbolic letter to stand for the new state continuations
        new_symb_letter = self.add_new_symbolic_letter(new_state)
        # add information to the boundary
        self.boundary.append(sconc(new_state, new_symb_letter))
        # initialize the new symbol
        self.initSymbol(new_symb_letter)
        # update sample
        self.add2sample([sconc(i,j) for i in self.mu_ext(sconc(new_state, new_symb_letter)) for j in self.suffixes])
        # for all mu(wn)

# automaton
    def moore_machine(self):
        """
        Returns the symbolic moore_machine related to the table
        """
        assert self.is_closed()
        assert self.is_reduced()
        assert self.is_evComp()

        def g(r):
            """ g: RR --> SS (backedges)"""
            assert r in self.prefixes + self.boundary
            if r in self.prefixes: return r
            for state in self.prefixes:
                if self.ff(r) == self.ff(state):
                    return state
            raise ValueError("The table is not close")

        alphabet = self.alphabet
        symb_alph = sorted(self.symb_alphabet())

        d1 = dict(enumerate(list(self.prefixes)))   # (0,''), (1,'a0'), ...
        d2 = dict([(j,i) for (i,j) in d1.items()])  # ('',0), ('a0',1)

        # Set of states, starting state and accepting states
        Q  = range(len(d1))
        q0 = d2['']
#       F  = [q for q in Q if self.ff(d1[q],'')]
        def output_function(q):
            return self.ff(d1[q], '')

        # Transition function d, dd
        d = dict([((q,aa),d2[g(sconc(d1[q], aa))]) for q in Q for aa in self.local_symb_alphabet[d1[q]] ])
        def dd(state, symbol):
            assert state in Q
            assert symbol in symb_alph
            return d[(state,symbol)]

#       p = dict([((q,i),aa) for q in Q for aa in self.local_symb_alphabet[d1[q]] for i in self.sem(aa)])

        # given state, and letter psi is supposed to return the symbolic
        # letter that letter belongs to in the local symbols of state
        def psi(state, letter):
            assert state in Q
#           assert letter in alphabet
            assert alphabet.contains(float(letter))
#           return p[(state,letter)]
            for aa in self.local_symb_alphabet[d1[state]]:
                if self.sem(aa).contains(float(letter)):
                    return aa
            raise ValueError("Letter not found in state's local symb alphabet")

        local_symbols = dict([(q, self.local_symb_alphabet[d1[q]]) for q in Q])
        symbol_semantics = dict([(aa, self.sem(aa)) for aa in symb_alph])

        output_alphabet = []
        for i in self.f:
            output_alphabet.append(self.f[i])
        output_alphabet = set(output_alphabet)

        # Build an automaton SA_Float whose concrete alphabet is of type
        # Float_Range
        return SMM_Float(concrete_alphabet = alphabet,
                  symbolic_alphabet = symb_alph,
                  output_alphabet = output_alphabet,
                  states = Q,
                  initial_state = q0,
                  output_function = output_function,
#                 final_states = F,
                  psi = psi,
                  delta = dd,
                  local_symbols = local_symbols,
                  symbol_semantics = symbol_semantics)


# printing  the table
    def printMuAndSem(self):
        """prints the evidence function"""
        pass
        s = "" #"\nSemantics and Evidences:"
        for a in sorted(self.symb_alphabet()):
            s += "\n["+ a +"] = ["+ str(self.sbound[a][0]) +","+ str(self.sbound[a][1]) +"),"
            s += "\tmr("+ a + ") = "
            s += str(self.mr[a])
            s += ",\tm(" + a + ") = "
            s += str(self.mu[a])
        return s

    def printable(self):
        """prints the observation table"""
        first_column_length = max([len(x) for x in self.boundary]) + 1   # length of largest word in boundary
        columns_length = max([len(x) for x in self.suffixes]) + 1        # length of largest word in suffixes

        table_rows = [' '*first_column_length + '|' + ' '.join([x.center(columns_length)
                                                                for x in self.suffixes])]
        table_rows.append('-'*len(table_rows[0]) + '-')

        for prefix in self.prefixes:
            table_rows.append(prefix.rjust(first_column_length) +
                              '|' + ' '.join([str(x).center(columns_length)
                                              for x in self.ff(prefix) ]))

        table_rows.append('-'*len(table_rows[0]) + '-')

        for prefix in self.boundary:
            table_rows.append(prefix.rjust(first_column_length) +
                              '|' + ' '.join([str(x).center(columns_length)
                                              for x in self.ff(prefix) ]))

        table_rows.append('-'*len(table_rows[0]) + '-')

# print the evidences
        table_rows.append('-'*len(table_rows[0]) + '-')

        for prefix in self.prefixes[1:]+self.boundary:
            table_rows.append(prefix)
            for pre in self.mu_ext(prefix):
                table_rows.append(pre.rjust(first_column_length) +
                              '|' + ' '.join([str(x).center(columns_length)
                                              for x in self.ff(pre) ]))
            table_rows.append('-'*len(table_rows[0]) + '-')
#
        s = ''
        for x in table_rows:
            s += x + '\n'
        return s

    def __str__(self):
        s = 'Symbolic observation table:\n'
        s += 'SS = ' + str(sorted(self.symb_alphabet()))
        s += self.printMuAndSem() + '\n\n'
        s += self.printable()
        return "\n<"+str(self.__module__)+".ExtSL_ObsTable instance at " + str(hex(id(self)))+">\n" + s



##-----------------------------------------------------------##
##-----------------------------------------------------------##
#                        Learning classes

##-----------------------------------------------------------##
#  SYMBOLIC LEARNER

class SymbPACLearner:

    def __init__(self, teacher, e = 0.05, d = 0.05, print_on = True, make_file = False, file_name_prefix = ''):
        # alphabet in Teacher should be a list and should be ordered
        assert e > 0 and e < 1
        assert d > 0 and d < 1
        assert print_on in [True, False]
        assert make_file in [True, False]
        assert type(file_name_prefix) == str

        self.teacher = teacher
        self.table = SymbPAC_ObsTable(self.teacher.alphabet)         # Initialize table

        self.learned = False
        self.hypothesis = []
        self.cex = ['']

        self.print_on = print_on
        self.make_file_on = make_file
        self.file_name_prefix = file_name_prefix
        self.parameter = (e,d) # parameters e = accuracy, d=confidence

        self.reset_counters()

    def reset_counters(self):
        self.num_mq = 0
        self.num_mq_for_cex = 0

        self.num_tests = 0
        self.num_words_tested = 0

        self.num_treatments = 0

        self.total_run_time = 0   # add-up the time run was envoked
        self.testing_time = 0     # time needed for testing
        self.treat_time = 0


    def run(self):
        t0_run = time.clock()
        if self.print_on: print('Print is set ON\n')
        else: print('Print is set OFF')

        self.learned = False

        while not self.learned:
            # fill in table asking MQs and close if needed
            self.askMQs()
            if self.print_on: print(self.table)

            isClosed, new_state = self.table.is_closed() ## return False and the row fro which not closed
            if not isClosed:
                if self.print_on: print( 'Table is not closed. Make', new_state,'a new state.')
                self.makeClose(new_state)
                continue # go to next loop

            evCompatible, incompatibility = self.table.is_evComp()
            if not evCompatible:
                if self.print_on: print('Table is not evidence compatible. Incompatibility in state', incompatibility)
                self.makeEvComp(incompatibility)
                continue # go to next loop

            if self.print_on: print('Table is both Closed and Evidence Compatible')

            # make new hypothesis
            self.hypothesis.append(self.table.automaton())
            i = len(self.hypothesis)-1
            if self.print_on:
                print("Make new hypothesis H"+str(i))
                print(self.hypothesis[-1])
            if self.make_file_on: self.hypothesis[-1].open_graph(self.file_name_prefix + 'H'+str(i), typ = 'gv')

            # if the last counterexample is still a counterexample
            if self.hypothesis[-1].recognizes(self.cex[-1]) != self.teacher.membership_query(self.cex[-1]):
               if self.print_on: print( "treat same counterexample again")
               if not self.treat_counterexample():
                   print("counterexample", self.cex[-1], 'could not treated succefully')
                   self.cex.pop()
                   continue
            else:
            # Test the new hypothesis
               if self.print_on: print("\nTest new hypothesis")
               self.num_tests += 1
               t0_test = time.clock()
               w, words_tested = self.teacher.test(self.hypothesis[-1], i, print_on = self.print_on)
               self.testing_time += time.clock() - t0_test
               self.num_words_tested += words_tested
               if w == True:
                   if self.print_on:
                       print("Target Automaton Learned successfully!")
                       print("P(error < {e:.2f} ) > {d:.2f} ".format(e = self.parameter[0], d = 1- self.parameter[1]))
                   self.learned = True
               else:
                   if self.print_on: print("New counterexample w = ", w)
                   self.cex.append(w)
                   if not self.treat_counterexample():
                       print("counterexample",w, 'could not treated succefully')
                       self.cex.pop()
                       continue

        self.total_run_time += time.clock() - t0_run

# fill in the table by asking membership queries
    def askMQs(self):
        """ ask MQs to fill in the table"""
        for word in self.table.csample():
            if word not in self.table.f.keys():
                self.table.add2f(word, self.teacher.membership_query(word))
                self.num_mq += 1
                if self.print_on: print("Ask MQ for ", word, ":", self.table.f[word])

# treat counterexample
    def treat_counterexample(self):
        self.num_treatments += 1
        if self.print_on: print( "Counterexample Treatment")
        # last hypothesis
        H = self.hypothesis[-1]
        # counterexample    w = b(0).b(1).b(2)....b(m-1)
        w = self.cex[-1]

        # check that w is a counterexample
        assert self.teacher.membership_query(w) != H.recognizes(w), str(w)+" is not a counterexample. Search a new one."
        if self.print_on: print
        if self.print_on: print( 'w=',w, )

        ww = H.make_symbolic(w)
        ws = w.split()
        wws = ww.split()

        t0_treat = time.clock()

        flag = H.recognizes(w)  # set up the flag for i = m+1
        if self.print_on: print( '\tflag is set to ',flag)
        # iterate on m, m-1, ....,2,1
        for i in reversed(range(len(ws))):
            u_i = ' '.join(ws[:i])
            a_i = ws[i]
            v_i = ' '.join(ws[i+1:])
            if self.print_on: print( "\nIteration",i,',',"\tw =",u_i,',',a_i,',',v_i)
            # find access string equivalent to u_i
            access_string = self.table.prefixes[H.delta_star(H.initial, u_i)]

            # word = m(access(u_i)).m(a_i).v_i
            word = sconc(self.table.mr_ext(access_string),sconc(self.table.mr_ext(wws[i]),v_i))
            # test word for vertical expansion
            self.num_mq_for_cex += 1
            if self.teacher.membership_query(word) != flag:
                if self.print_on: print('add suffix: ', v_i)
                if self.table.add2suffixes(v_i):
                    if self.print_on:  print('distinguish string added')
                    self.treat_time += time.clock()-t0_treat
                    return True # Treatment ended succefully

            # word = m(access(u_i)).a_i.v_i
            word = sconc(self.table.mr_ext(access_string),sconc(a_i,v_i))
            # test word for horizontal expansion
            self.num_mq_for_cex += 1
            if self.teacher.membership_query(word) != flag:
                if self.print_on: print('add evidence', a_i,'to ', wws[i])
                if self.table.add2mu(wws[i],a_i):
                    if self.print_on: print('evidence added')
                    self.treat_time += time.clock()-t0_treat
                    return True # treatment ended succesfully
                else:
                    # need to add suffix as well
                    self.table.add2suffixes(v_i)
                    if self.print_on:  print('also suffix', v_i, 'is added')
                    self.treat_time += time.clock()-t0_treat
                    return False

        print("treatment ended without results")
        self.treat_time += time.clock()-t0_treat
        return False


# close and fill in table
    def makeClose(self, new_state):
        """when table is not close he moves the appropiate elements from boundary to prefixes"""
        self.table.make_state(new_state)
        self.askMQs()

    def split(self, a1, a2):
        assert a1 in self.teacher.alphabet
        assert a2 in self.teacher.alphabet
        i = self.teacher.alphabet.index(a1)
        j = self.teacher.alphabet.index(a2)
        assert i < j
        return self.teacher.alphabet[int((i+j)/2) +1]

    def makeEvComp(self, incompatible_state):
        """Solve incompatibility by refining the partitions"""
        ss = str(incompatible_state)
        s = self.table.mr_ext(ss)

        # (a_i,aa_i) pairs for which a_i \in mu(aa_i)
        partpsi = dict([(i,a)
                      for a in self.table.local_symb_alphabet[ss]
                      for i in self.table.mu[a]])
        # all evidences for state alphabet ss
        evidence = sorted(partpsi.keys(), key = cmp_to_key(cmpr))
        # pairs (i,f_i) of evidences and their residual
        residuals = dict([(i,self.table.ff(sconc(s,i))) for i in evidence])

        # Find the index i for which f_{i-1} != f_i and a_{i-1} a_i \in the same semantics
        ind = [(residuals[i] != residuals[j] and partpsi[i] == partpsi[j]) for i,j in zip(evidence[:-1],evidence[1:])].index(True) + 1
        if self.print_on: print( 'ind = ', ind)
        aa = partpsi[evidence[ind]]
        c,c_ = tuple(self.table.sbound[aa])

        p = self.split(evidence[ind-1], evidence[ind])

        # ind is not last index && evidence[ind] = max mu (aa)  && f_{ind} == f_{ind+1}
        if ind < len(evidence)-1 and aa != partpsi[evidence[ind+1]] and residuals[evidence[ind]] == residuals[evidence[ind+1]]:
            # then we are in the first case
            # old:  [aa] = [c,c') and [aa_{j+1}] = [c',d)
            # new:  [aa] = [c,p)  and [aa_{j+1}] = [p,d)
            # update aa_{j+1}
            a_next = str(partpsi[evidence[ind+1]])
            self.table.sbound[a_next] = (str(p),self.table.sbound[a_next][1])
            # update  aa_j
            self.table.sbound[aa] = (str(c), str(p))
            # update the evidence function for a_{j+1}
            self.table.mu[a_next] = [i for i in self.table.mu[aa] if cmpr(i, p) != -1] + self.table.mu[a_next]
            # update the evidence function for a_j
            self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i, p) == -1]

        # ind-1 is not first index && evidence[ind-1] = min mu (aa) && f_{ind-1} == f_{ind-2}
        elif ind > 1 and aa != partpsi[evidence[ind-2]] and residuals[evidence[ind-1]] == residuals[evidence[ind-2]]:
            # then we are in the second case
            # old:  [aa_{j-1}] = [d,c) and [aa] = [c,c')
            # old:  [aa_{j-1}] = [d,p) and [aa] = [p,c')
            # update aa_{j-1}
            a_previous = str(partpsi[evidence[ind-2]])
            self.table.sbound[a_previous] = (self.table.sbound[a_previous][0],str(p))  # change upper bound to p
            # update aa_j
            self.table.sbound[aa] = (str(p), str(c_))  # change lower bound to p
            # update the evidence function for a_{j-1}
            self.table.mu[a_previous] = self.table.mu[a_previous] + [i for i in self.table.mu[aa] if cmpr(i, p) == -1]
            # update the evidence function for a_j
            self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i,p) != -1]

        else:
            # introduce new symbol
            bb = self.table.add_new_symbolic_letter(ss)
            self.table.boundary.append(sconc(ss,bb))
            if cmpr(self.table.mr[aa] , p) == -1:    # mr(aa) < p
                # old:  [aa] = [c,c')
                # new:  [aa] = [c,p) and [bb] = [p,c')
                self.table.sbound[bb] = (str(p), str(c_))
                self.table.sbound[aa] = (str(c), str(p))
                self.table.mu[bb] = [i for i in self.table.mu[aa] if cmpr(i,p) != -1]
                self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i,p) == -1]
            else:  # mr(aa) >= p
                # old:  [aa] = [c,c')
                # new:  [bb] = [c,p) and [aa] = [p,c')
                self.table.sbound[bb] = (str(c), str(p))
                self.table.sbound[aa] = (str(p), str(c_))
                self.table.mu[bb] = [i for i in self.table.mu[aa] if cmpr(i,p) == -1]
                self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i,p) != -1]
##            self.table.mu[bb] = [i for i in self.table.mu[aa] if i in self.table.sem(bb)]
##            self.table.mu[aa] = [i for i in self.table.mu[aa] if i in self.table.sem(aa)]
            self.table.mr[bb] = random.choice(self.table.mu[bb])


    def results(self):
        s = {'prefixes'              : len(self.table.prefixes),
             'states'                : len(self.table.prefixes),
             'boundary'              : len(self.table.boundary),
             'suffixes'              : len(self.table.suffixes),
             'symbols'               : len(self.table.symb_alphabet()),
             'symb_sample'           : len(self.table.prefixes+ self.table.boundary)*len(self.table.suffixes),
             'concr_sample'          : len(self.table.f),
             'hypotheses'            : len(self.hypothesis),
             'cex'                   : len(self.cex),
             'calls_treat'           : self.num_treatments,
             'TQs'                   : self.num_tests,
             'MQs_to_fill_table'     : self.num_mq,
             'MQs_for_cex_treatment' : self.num_mq_for_cex,
             'words_tested'          : self.num_words_tested,
             'MQs_total'             : self.num_mq + self.num_mq_for_cex,
             'total_run_time'        : self.total_run_time,
             'time_for_testing'      : self.testing_time,
             'time_for_cexs'         : self.treat_time}
        return s

##-----------------------------------------------------------##
#  SYMBOLIC LEARNER - FLOATS
class SymbPACLearner_Float:

    def __init__(self, teacher, e = 0.05, d = 0.05, print_on = True, make_file = False, file_name_prefix = ''):
        # alphabet in Teacher should be a list and should be ordered
        assert e > 0 and e < 1
        assert d > 0 and d < 1
        assert print_on in [True, False]
        assert make_file in [True, False]
        assert type(file_name_prefix) == str

        self.teacher = teacher
#       self.table = SymbPAC_ObsTable(self.teacher.alphabet)         # Initialize table
        self.table = SymbPAC_ObsTable_Float(self.teacher.alphabet)         # Initialize table

        self.learned = False
        self.hypothesis = []
        self.cex = ['']

        self.print_on = print_on
        self.make_file_on = make_file
        self.file_name_prefix = file_name_prefix
        self.parameter = (e,d) # parameters e = accuracy, d=confidence

        self.reset_counters()

    def reset_counters(self):
        self.num_mq = 0
        self.num_mq_for_cex = 0

        self.num_tests = 0
        self.num_words_tested = 0

        self.num_treatments = 0

        self.total_run_time = 0   # add-up the time run was envoked
        self.testing_time = 0     # time needed for testing
        self.treat_time = 0


    def run(self):
        t0_run = time.clock()
        if self.print_on: print('Print is set ON\n')
        else: print('Print is set OFF')

        self.learned = False

        while not self.learned:
            # fill in table asking MQs and close if needed
            self.askMQs()
            if self.print_on: print(self.table)

            isClosed, new_state = self.table.is_closed() ## return False and the row fro which not closed
            if not isClosed:
                if self.print_on: print( 'Table is not closed. Make', new_state,'a new state.')
                self.makeClose(new_state)
                continue # go to next loop

            evCompatible, incompatibility = self.table.is_evComp()
            if not evCompatible:
                if self.print_on: print('Table is not evidence compatible. Incompatibility in state', incompatibility)
                self.makeEvComp(incompatibility)
                continue # go to next loop

            if self.print_on: print('Table is both Closed and Evidence Compatible')

            # make new hypothesis
            self.hypothesis.append(self.table.automaton())
            i = len(self.hypothesis)-1
            if self.print_on:
                print("Make new hypothesis H"+str(i))
                print(self.hypothesis[-1])
            if self.make_file_on: self.hypothesis[-1].open_graph(self.file_name_prefix + 'H'+str(i), typ = 'gv')

            # if the last counterexample is still a counterexample
            if self.hypothesis[-1].recognizes(self.cex[-1]) != self.teacher.membership_query(self.cex[-1]):
               if self.print_on: print( "treat same counterexample again")
               if not self.treat_counterexample():
                   print("counterexample", self.cex[-1], 'could not treated succefully')
                   self.cex.pop()
                   continue
            else:
            # Test the new hypothesis
               if self.print_on: print("\nTest new hypothesis")
               self.num_tests += 1
               t0_test = time.clock()
               w, words_tested = self.teacher.test(self.hypothesis[-1], i, print_on = False)
               self.testing_time += time.clock() - t0_test
               self.num_words_tested += words_tested
               if w == True:
                   if self.print_on:
                       print("Target Automaton Learned successfully!")
                       print("P(error < {e:.2f} ) > {d:.2f} ".format(e = self.parameter[0], d = 1- self.parameter[1]))
                       print("Number of hypotheses made: ", len(self.hypothesis))
                   self.learned = True
               else:
                   if self.print_on: print("New counterexample w = ", w)
                   self.cex.append(w)
                   if not self.treat_counterexample():
                       print("counterexample",w, 'could not treated succefully')
                       self.cex.pop()
                       continue

        self.total_run_time += time.clock() - t0_run

# fill in the table by asking membership queries
    def askMQs(self):
        """ ask MQs to fill in the table"""
        for word in self.table.csample():
            if word not in self.table.f.keys():
                self.table.add2f(word, self.teacher.membership_query(word))
                self.num_mq += 1
                if self.print_on: print("Ask MQ for ", word, ":", self.table.f[word])

# treat counterexample
    def treat_counterexample(self):
        self.num_treatments += 1
        if self.print_on: print( "Counterexample Treatment")
        # last hypothesis
        H = self.hypothesis[-1]
        # counterexample    w = b(0).b(1).b(2)....b(m-1)
        w = self.cex[-1]

        # check that w is a counterexample
        assert self.teacher.membership_query(w) != H.recognizes(w), str(w)+" is not a counterexample. Search a new one."
        if self.print_on: print
        if self.print_on: print( 'w=',w, )

        ww = H.make_symbolic(w)
        ws = w.split()
        wws = ww.split()

        t0_treat = time.clock()

        flag = H.recognizes(w)  # set up the flag for i = m+1
        if self.print_on: print( '\tflag is set to ',flag)
        # iterate on m, m-1, ....,2,1
        for i in reversed(range(len(ws))):
            u_i = ' '.join(ws[:i])
            a_i = ws[i]
            v_i = ' '.join(ws[i+1:])
            if self.print_on: print( "\nIteration",i,',',"\tw =",u_i,',',a_i,',',v_i)
            # find access string equivalent to u_i
            access_string = self.table.prefixes[H.delta_star(H.initial, u_i)]

            # word = m(access(u_i)).m(a_i).v_i
            word = sconc(self.table.mr_ext(access_string),sconc(self.table.mr_ext(wws[i]),v_i))
            # test word for vertical expansion
            self.num_mq_for_cex += 1
            if self.teacher.membership_query(word) != flag:
                if self.print_on: print('add suffix: ', v_i)
                if self.table.add2suffixes(v_i):
                    if self.print_on:  print('distinguish string added')
                    self.treat_time += time.clock()-t0_treat
                    return True # Treatment ended succefully

            # word = m(access(u_i)).a_i.v_i
            word = sconc(self.table.mr_ext(access_string),sconc(a_i,v_i))
            # test word for horizontal expansion
            self.num_mq_for_cex += 1
            if self.teacher.membership_query(word) != flag:
                if self.print_on: print('add evidence', a_i,'to ', wws[i])
                if self.table.add2mu(wws[i],a_i):
                    if self.print_on: print('evidence added')
                    self.treat_time += time.clock()-t0_treat
                    return True # treatment ended succesfully
                else:
                    # need to add suffix as well
                    self.table.add2suffixes(v_i)
                    if self.print_on:  print('also suffix', v_i, 'is added')
                    self.treat_time += time.clock()-t0_treat
                    return False

        print("treatment ended without results")
        self.treat_time += time.clock()-t0_treat
        return False


# close and fill in table
    def makeClose(self, new_state):
        """when table is not close he moves the appropiate elements from boundary to prefixes"""
        self.table.make_state(new_state)
        self.askMQs()

    def split(self, a1, a2):
#       assert a1 in self.teacher.alphabet
#       assert a2 in self.teacher.alphabet
#       i = self.teacher.alphabet.index(a1)
#       j = self.teacher.alphabet.index(a2)
#       assert i < j
#       return self.teacher.alphabet[int((i+j)/2) +1]
        assert self.teacher.alphabet.contains(float(a1))
        assert self.teacher.alphabet.contains(float(a2))
        return str((float(a1) + float(a2)) / 2)

    def makeEvComp(self, incompatible_state):
        # Dissection of the code:
        # incompatible_state is the state at which the evidences are not
        # compatible, i.e. in mu

        """Solve incompatibility by refining the partitions"""
        ss = str(incompatible_state)
        s = self.table.mr_ext(ss)

        # (a_i,aa_i) pairs for which a_i \in mu(aa_i)
        partpsi = dict([(i,a)
                      for a in self.table.local_symb_alphabet[ss]
                      for i in self.table.mu[a]])
        # all evidences for state alphabet ss
        evidence = sorted(partpsi.keys(), key = cmp_to_key(cmpr))
        # pairs (i,f_i) of evidences and their residual
        residuals = dict([(i,self.table.ff(sconc(s,i))) for i in evidence])

        # Find the index i for which f_{i-1} != f_i and a_{i-1} a_i \in the same semantics
        ind = [(residuals[i] != residuals[j] and partpsi[i] == partpsi[j]) for i,j in zip(evidence[:-1],evidence[1:])].index(True) + 1
        if self.print_on: print( 'ind = ', ind)
        aa = partpsi[evidence[ind]]
        c,c_ = tuple(self.table.sbound[aa])

        p = self.split(evidence[ind-1], evidence[ind])

        tol = self.e

        # Dicotomic search
        A = float(evidence[ind-1])
        B = float(evidence[ind])

        f_A = residuals[evidence[ind-1]]
        f_B = residuals[evidence[ind]]
        # transform entries to True/False because the comparison happens with
        # membership query entries which are True/False
        f_A = [True if i==1 else False for i in f_A]
        f_B = [True if i==1 else False for i in f_B]

        difference = float(B) - float(A)
        while difference > tol:
            assert f_A != f_B
            P = (A + B) / 2
            f_P = []
            for e in self.table.suffixes:
                f_P.append(self.teacher.membership_query(sconc(s, str(P), e)))
            if f_P != f_A:
                B = P
                f_B = f_P
            elif f_P != f_B:
                A = P
                f_A = f_P
            else:
                assert True, 'ERROR'

            difference = B - A

        p = self.split(str(A), str(B))
        # ind is not last index && evidence[ind] = max mu (aa)  && f_{ind} == f_{ind+1}
        if ind < len(evidence)-1 and aa != partpsi[evidence[ind+1]] and residuals[evidence[ind]] == residuals[evidence[ind+1]]:
            # then we are in the first case
            # old:  [aa] = [c,c') and [aa_{j+1}] = [c',d)
            # new:  [aa] = [c,p)  and [aa_{j+1}] = [p,d)
            # update aa_{j+1}
            a_next = str(partpsi[evidence[ind+1]])



            self.table.sbound[a_next] = (str(p),self.table.sbound[a_next][1])
            # update  aa_j
            self.table.sbound[aa] = (str(c), str(p))
            # update the evidence function for a_{j+1}
            self.table.mu[a_next] = [i for i in self.table.mu[aa] if cmpr(i, p) != -1] + self.table.mu[a_next]
            # update the evidence function for a_j
            self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i, p) == -1]

        # ind-1 is not first index && evidence[ind-1] = min mu (aa) && f_{ind-1} == f_{ind-2}
        elif ind > 1 and aa != partpsi[evidence[ind-2]] and residuals[evidence[ind-1]] == residuals[evidence[ind-2]]:
            # then we are in the second case
            # old:  [aa_{j-1}] = [d,c) and [aa] = [c,c')
            # old:  [aa_{j-1}] = [d,p) and [aa] = [p,c')
            # update aa_{j-1}
            a_previous = str(partpsi[evidence[ind-2]])



            self.table.sbound[a_previous] = (self.table.sbound[a_previous][0],str(p))  # change upper bound to p
            # update aa_j
            self.table.sbound[aa] = (str(p), str(c_))  # change lower bound to p
            # update the evidence function for a_{j-1}
            self.table.mu[a_previous] = self.table.mu[a_previous] + [i for i in self.table.mu[aa] if cmpr(i, p) == -1]
            # update the evidence function for a_j
            self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i,p) != -1]

        else:
            # introduce new symbol
            bb = self.table.add_new_symbolic_letter(ss)
            self.table.boundary.append(sconc(ss,bb))
            if cmpr(self.table.mr[aa] , p) == -1:    # mr(aa) < p
                # old:  [aa] = [c,c')
                # new:  [aa] = [c,p) and [bb] = [p,c')
                self.table.sbound[bb] = (str(p), str(c_))
                self.table.sbound[aa] = (str(c), str(p))
                self.table.mu[bb] = [i for i in self.table.mu[aa] if cmpr(i,p) != -1]
                self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i,p) == -1]
            else:  # mr(aa) >= p
                # old:  [aa] = [c,c')
                # new:  [bb] = [c,p) and [aa] = [p,c')
                self.table.sbound[bb] = (str(c), str(p))
                self.table.sbound[aa] = (str(p), str(c_))
                self.table.mu[bb] = [i for i in self.table.mu[aa] if cmpr(i,p) == -1]
                self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i,p) != -1]
##            self.table.mu[bb] = [i for i in self.table.mu[aa] if i in self.table.sem(bb)]
##            self.table.mu[aa] = [i for i in self.table.mu[aa] if i in self.table.sem(aa)]
            self.table.mr[bb] = random.choice(self.table.mu[bb])


    def results(self):
        s = {'prefixes'              : len(self.table.prefixes),
             'states'                : len(self.table.prefixes),
             'boundary'              : len(self.table.boundary),
             'suffixes'              : len(self.table.suffixes),
             'symbols'               : len(self.table.symb_alphabet()),
             'symb_sample'           : len(self.table.prefixes+ self.table.boundary)*len(self.table.suffixes),
             'concr_sample'          : len(self.table.f),
             'hypotheses'            : len(self.hypothesis),
             'cex'                   : len(self.cex),
             'calls_treat'           : self.num_treatments,
             'TQs'                   : self.num_tests,
             'MQs_to_fill_table'     : self.num_mq,
             'MQs_for_cex_treatment' : self.num_mq_for_cex,
             'words_tested'          : self.num_words_tested,
             'MQs_total'             : self.num_mq + self.num_mq_for_cex,
             'total_run_time'        : self.total_run_time,
             'time_for_testing'      : self.testing_time,
             'time_for_cexs'         : self.treat_time}
        return s



##-----------------------------------------------------------##
#  SYMBOLIC LEARNER - MOORE MACHINE FLOATS
class SymbPACLearner_MM_Float:

    def __init__(self, teacher, e = 0.05, d = 0.05, print_on = True, make_file = False, file_name_prefix = ''):
        # alphabet in Teacher should be a list and should be ordered
        assert e > 0 and e < 1
        assert d > 0 and d < 1
        assert print_on in [True, False]
        assert make_file in [True, False]
        assert type(file_name_prefix) == str

        self.teacher = teacher
#       self.table = SymbPAC_ObsTable(self.teacher.alphabet)         # Initialize table
        self.table = SymbPAC_ObsTable_MM_Float(self.teacher.alphabet)         # Initialize table

        self.learned = False
        self.hypothesis = []
        self.cex = ['']

        self.print_on = print_on
        self.make_file_on = make_file
        self.file_name_prefix = file_name_prefix
        self.parameter = (e,d) # parameters e = accuracy, d=confidence

        self.reset_counters()

    def reset_counters(self):
        self.num_mq = 0
        self.num_mq_for_cex = 0

        self.num_tests = 0
        self.num_words_tested = 0

        self.num_treatments = 0

        self.total_run_time = 0   # add-up the time run was envoked
        self.testing_time = 0     # time needed for testing
        self.treat_time = 0


    def run(self):
        t0_run = time.clock()
        if self.print_on: print('Print is set ON\n')
        else: print('Print is set OFF')

        self.learned = False

        while not self.learned:
            # fill in table asking MQs and close if needed
            self.askMQs()
            if self.print_on: print(self.table)

            isClosed, new_state = self.table.is_closed() ## return False and the row fro which not closed
            if not isClosed:
                if self.print_on: print( 'Table is not closed. Make', new_state,'a new state.')
                self.makeClose(new_state)
                continue # go to next loop

            evCompatible, incompatibility = self.table.is_evComp()
            if not evCompatible:
                if self.print_on: print('Table is not evidence compatible. Incompatibility in state', incompatibility)
                self.makeEvComp(incompatibility)
                continue # go to next loop

            if self.print_on: print('Table is both Closed and Evidence Compatible')

            # make new hypothesis
            self.hypothesis.append(self.table.moore_machine())
            i = len(self.hypothesis)-1
            print("Make new hypothesis H"+str(i))
            self.hypothesis[-1].open_graph(self.file_name_prefix + 'H'+str(i), typ = 'pdf')
            if self.print_on:
                print("Make new hypothesis H"+str(i))
                print(self.hypothesis[-1])
            if self.make_file_on: self.hypothesis[-1].open_graph(self.file_name_prefix + 'H'+str(i), typ = 'gv')

            # if the last counterexample is still a counterexample
            if len(self.cex) > 0 and self.hypothesis[-1].compute(self.cex[-1]) != self.teacher.membership_query(self.cex[-1]):
               if self.print_on: print( "treat same counterexample again")
               if not self.treat_counterexample():
                   print("counterexample", self.cex[-1], 'could not treated succefully')
                   self.cex.pop()
                   continue
            else:
            # Test the new hypothesis
               if self.print_on: print("\nTest new hypothesis")
               self.num_tests += 1
               t0_test = time.clock()
               w, words_tested = self.teacher.test(self.hypothesis[-1], i, print_on = False)
               self.testing_time += time.clock() - t0_test
               self.num_words_tested += words_tested
               if w == True:
                   if self.print_on:
                       print("Target Automaton Learned successfully!")
                       print("P(error < {e:.2f} ) > {d:.2f} ".format(e = self.parameter[0], d = 1- self.parameter[1]))
                   self.learned = True
               else:
                   if self.print_on: print("New counterexample w = ", w)
                   self.cex.append(w)
                   if not self.treat_counterexample():
                       print("counterexample",w, 'could not treated succefully')
                       self.cex.pop()
                       continue

        self.total_run_time += time.clock() - t0_run

# fill in the table by asking membership queries
    def askMQs(self):
        """ ask MQs to fill in the table"""
        for word in self.table.csample():
            if word not in self.table.f.keys():
                self.table.add2f(word, self.teacher.membership_query(word))
                self.num_mq += 1
                if self.print_on: print("Ask MQ for ", word, ":", self.table.f[word])

# treat counterexample
    def treat_counterexample(self):
        self.num_treatments += 1
        if self.print_on: print( "Counterexample Treatment")
        # last hypothesis
        H = self.hypothesis[-1]
        # counterexample    w = b(0).b(1).b(2)....b(m-1)
        w = self.cex[-1]

        # check that w is a counterexample
        assert self.teacher.membership_query(w) != H.compute(w), str(w)+" is not a counterexample. Search a new one."
        if self.print_on: print
        if self.print_on: print( 'w=',w, )

        ww = H.make_symbolic(w)
        ws = w.split()
        wws = ww.split()

        t0_treat = time.clock()

        flag = H.compute(w)  # set up the flag for i = m+1
        if self.print_on: print( '\tflag is set to ',flag)
        # iterate on m, m-1, ....,2,1
        for i in reversed(range(len(ws))):
            u_i = ' '.join(ws[:i])
            a_i = ws[i]
            v_i = ' '.join(ws[i+1:])
            if self.print_on: print( "\nIteration",i,',',"\tw =",u_i,',',a_i,',',v_i)
            # find access string equivalent to u_i
            access_string = self.table.prefixes[H.delta_star(H.initial, u_i)]

            # word = m(access(u_i)).m(a_i).v_i
            word = sconc(self.table.mr_ext(access_string),sconc(self.table.mr_ext(wws[i]),v_i))
            # test word for vertical expansion
            self.num_mq_for_cex += 1
            if self.teacher.membership_query(word) != flag:
                if self.print_on: print('add suffix: ', v_i)
                if self.table.add2suffixes(v_i):
                    if self.print_on:  print('distinguish string added')
                    self.treat_time += time.clock()-t0_treat
                    return True # Treatment ended succefully

            # word = m(access(u_i)).a_i.v_i
            word = sconc(self.table.mr_ext(access_string),sconc(a_i,v_i))
            # test word for horizontal expansion
            self.num_mq_for_cex += 1
            if self.teacher.membership_query(word) != flag:
                if self.print_on: print('add evidence', a_i,'to ', wws[i])
                if self.table.add2mu(wws[i],a_i):
                    if self.print_on: print('evidence added')
                    self.treat_time += time.clock()-t0_treat
                    return True # treatment ended succesfully
                else:
                    # need to add suffix as well
                    self.table.add2suffixes(v_i)
                    if self.print_on:  print('also suffix', v_i, 'is added')
                    self.treat_time += time.clock()-t0_treat
                    return False

        print("treatment ended without results")
        self.treat_time += time.clock()-t0_treat
        return False


# close and fill in table
    def makeClose(self, new_state):
        """when table is not close he moves the appropiate elements from boundary to prefixes"""
        self.table.make_state(new_state)
        self.askMQs()

    def split(self, a1, a2):
#       assert a1 in self.teacher.alphabet
#       assert a2 in self.teacher.alphabet
#       i = self.teacher.alphabet.index(a1)
#       j = self.teacher.alphabet.index(a2)
#       assert i < j
#       return self.teacher.alphabet[int((i+j)/2) +1]
        assert self.teacher.alphabet.contains(float(a1))
        assert self.teacher.alphabet.contains(float(a2))
        return str((float(a1) + float(a2)) / 2)

    def makeEvComp(self, incompatible_state):
        """Solve incompatibility by refining the partitions"""
        ss = str(incompatible_state)
        s = self.table.mr_ext(ss)

        # (a_i,aa_i) pairs for which a_i \in mu(aa_i)
        partpsi = dict([(i,a)
                      for a in self.table.local_symb_alphabet[ss]
                      for i in self.table.mu[a]])
        # all evidences for state alphabet ss
        evidence = sorted(partpsi.keys(), key = cmp_to_key(cmpr))
        # pairs (i,f_i) of evidences and their residual
        residuals = dict([(i,self.table.ff(sconc(s,i))) for i in evidence])

        # Find the index i for which f_{i-1} != f_i and a_{i-1} a_i \in the same semantics
        ind = [(residuals[i] != residuals[j] and partpsi[i] == partpsi[j]) for i,j in zip(evidence[:-1],evidence[1:])].index(True) + 1
        if self.print_on: print( 'ind = ', ind)
        aa = partpsi[evidence[ind]]
        c,c_ = tuple(self.table.sbound[aa])

        p = self.split(evidence[ind-1], evidence[ind])

        tol = self.parameter[0]

        # Dicotomic search
        A = float(evidence[ind-1])
        B = float(evidence[ind])

        f_A_original = residuals[evidence[ind-1]]
        f_B_original = residuals[evidence[ind]]

        f_A = f_A_original
        f_B = f_B_original

        # dictionary mapping NEW evidences to NEW residuals in case they are
        # discovered
        new_mu = dict([])

        difference = float(B) - float(A)
        while difference > tol:
            assert f_A != f_B
            P = (A + B) / 2
            f_P = []
            for e in self.table.suffixes:
                f_P.append(self.teacher.membership_query(sconc(s, str(P), e)))

            if f_P != f_A_original and f_P != f_B_original:
                if f_P not in new_mu.values():
                    new_mu[str(P)] = f_P
                    print(str(P))

            if f_P != f_A:
                B = P
                f_B = f_P
            elif f_P != f_B:
                A = P
                f_A = f_P
            else:
                assert True, 'ERROR'

            difference = B - A

        # in case there are newly discovered evidences, add them
        if len(new_mu) > 0:
            for m in new_mu.keys():
                self.table.add2mu(aa, m)

        p = self.split(str(A), str(B))
        # ind is not last index && evidence[ind] = max mu (aa)  && f_{ind} == f_{ind+1}
        if ind < len(evidence)-1 and aa != partpsi[evidence[ind+1]] and residuals[evidence[ind]] == residuals[evidence[ind+1]]:
            # then we are in the first case
            # old:  [aa] = [c,c') and [aa_{j+1}] = [c',d)
            # new:  [aa] = [c,p)  and [aa_{j+1}] = [p,d)
            # update aa_{j+1}
            a_next = str(partpsi[evidence[ind+1]])
            self.table.sbound[a_next] = (str(p),self.table.sbound[a_next][1])
            # update  aa_j
            self.table.sbound[aa] = (str(c), str(p))
            # update the evidence function for a_{j+1}
            self.table.mu[a_next] = [i for i in self.table.mu[aa] if cmpr(i, p) != -1] + self.table.mu[a_next]
            # update the evidence function for a_j
            self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i, p) == -1]

        # ind-1 is not first index && evidence[ind-1] = min mu (aa) && f_{ind-1} == f_{ind-2}
        elif ind > 1 and aa != partpsi[evidence[ind-2]] and residuals[evidence[ind-1]] == residuals[evidence[ind-2]]:
            # then we are in the second case
            # old:  [aa_{j-1}] = [d,c) and [aa] = [c,c')
            # old:  [aa_{j-1}] = [d,p) and [aa] = [p,c')
            # update aa_{j-1}
            a_previous = str(partpsi[evidence[ind-2]])
            self.table.sbound[a_previous] = (self.table.sbound[a_previous][0],str(p))  # change upper bound to p
            # update aa_j
            self.table.sbound[aa] = (str(p), str(c_))  # change lower bound to p
            # update the evidence function for a_{j-1}
            self.table.mu[a_previous] = self.table.mu[a_previous] + [i for i in self.table.mu[aa] if cmpr(i, p) == -1]
            # update the evidence function for a_j
            self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i,p) != -1]

        else:
            # introduce new symbol
            bb = self.table.add_new_symbolic_letter(ss)
            self.table.boundary.append(sconc(ss,bb))
            if cmpr(self.table.mr[aa] , p) == -1:    # mr(aa) < p
                # old:  [aa] = [c,c')
                # new:  [aa] = [c,p) and [bb] = [p,c')
                self.table.sbound[bb] = (str(p), str(c_))
                self.table.sbound[aa] = (str(c), str(p))
                self.table.mu[bb] = [i for i in self.table.mu[aa] if cmpr(i,p) != -1]
                self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i,p) == -1]
            else:  # mr(aa) >= p
                # old:  [aa] = [c,c')
                # new:  [bb] = [c,p) and [aa] = [p,c')
                self.table.sbound[bb] = (str(c), str(p))
                self.table.sbound[aa] = (str(p), str(c_))
                self.table.mu[bb] = [i for i in self.table.mu[aa] if cmpr(i,p) == -1]
                self.table.mu[aa] = [i for i in self.table.mu[aa] if cmpr(i,p) != -1]
##            self.table.mu[bb] = [i for i in self.table.mu[aa] if i in self.table.sem(bb)]
##            self.table.mu[aa] = [i for i in self.table.mu[aa] if i in self.table.sem(aa)]
            self.table.mr[bb] = random.choice(self.table.mu[bb])


    def results(self):
        s = {'prefixes'              : len(self.table.prefixes),
             'states'                : len(self.table.prefixes),
             'boundary'              : len(self.table.boundary),
             'suffixes'              : len(self.table.suffixes),
             'symbols'               : len(self.table.symb_alphabet()),
             'symb_sample'           : len(self.table.prefixes+ self.table.boundary)*len(self.table.suffixes),
             'concr_sample'          : len(self.table.f),
             'hypotheses'            : len(self.hypothesis),
             'cex'                   : len(self.cex),
             'calls_treat'           : self.num_treatments,
             'TQs'                   : self.num_tests,
             'MQs_to_fill_table'     : self.num_mq,
             'MQs_for_cex_treatment' : self.num_mq_for_cex,
             'words_tested'          : self.num_words_tested,
             'MQs_total'             : self.num_mq + self.num_mq_for_cex,
             'total_run_time'        : self.total_run_time,
             'time_for_testing'      : self.testing_time,
             'time_for_cexs'         : self.treat_time}
        return s



##-----------------------------------------------------------##
#  ANGLUIN'S LEARNER -- LStar

class AngluinsPACLearnerClassic:
    """
    Angluin's learner can interact with a teacher which is aware of the target language and can answer to membership queries annd equivalence queries. If the answer to an equivalence query is negative the teacher can provide the learner a counterexample.
    The learner keeps all information in an observation table (OT). He can make a hypothesis and terminates when this hypothesis recognizes correctly the target language.
    """
    def __init__(self, teacher, e = 0.05, d = 0.05, print_on = True, make_file = False, file_name_prefix = ''):
        assert e > 0 and e < 1
        assert d > 0 and d < 1
        assert print_on in [True, False]
        assert make_file in [True, False]
        assert type(file_name_prefix) == str

        self.teacher = teacher
        self.table = OT(self.teacher.alphabet)

        self.learned = False
        self.hypothesis = []
        self.cex = []

        self.parameter = (e,d) # parameters e = accuracy, d=confidence

        self.print_on = print_on

        self.make_file_on = make_file
        self.file_name_prefix = file_name_prefix

        self.reset_counters()

    def reset_counters(self):
        self.num_mq = 0
        self.num_mq_for_cex = 0

        self.num_tests = 0
        self.num_words_tested = 0

        self.num_treatments = 0

        self.total_run_time = 0   # add-up the time run was envoked
        self.testing_time = 0     # time needed for testing
        self.treat_time = 0



    def run(self):
        t0_run = time.clock()
        if self.print_on: print('Print is set ON')
        else: print('Print is set OFF')
        # start algorithm
        self.learned = False

        while not self.learned:
            # fill in table asking MQs and close if needed
            self.askMQs()
            if self.print_on: print( self.table)

            isClosed, new_state = self.table.is_closed() ## return False and the row fro which not closed
            if not isClosed:
                if self.print_on: print( 'Table is not closed. Make', new_state,'a new state.')
                self.makeClose(new_state)
                continue # go to next loop

            isConsistent, new_dist_string = self.table.is_consistent()
            if not isConsistent:
                if self.print_on: print( 'Table is not Consistent. New distinguishing string', new_dist_string, 'is added to set of suffixes.')
                self.makeConsistent(new_dist_string)
                continue # go to next loop

            # Now that table is both Closed and consistent
            # make new hypothesis
            self.hypothesis.append(self.table.automaton())
            i = len(self.hypothesis)-1
            if self.print_on: print("Table is closed and consistent.\nMake hypothesis H"+str(i))
            if self.make_file_on:
                self.hypothesis[-1].make_reduced_dot_graph('HA'+str(i))
                opengv('HA'+str(i))

            if self.print_on: print("\nTest new hypothesis")
            self.num_tests += 1
            t0_test = time.clock()
            w, words_tested = self.teacher.test(self.hypothesis[-1], i, print_on = self.print_on)
            self.testing_time += time.clock() - t0_test
            self.num_words_tested += words_tested

            if w == True:
                if self.print_on:
                    print( "Target Automaton Learned successfully!")
                    print( "P(error < {e:.2f} ) > {d:.2f} ".format(e = self.parameter[0], d = 1- self.parameter[1]))
                self.learned = True

            else:
                if self.print_on: print( "New counterexample w = ", w)
                self.cex.append(w)

                self.treat_counterexample(w)
        self.total_run_time += time.clock() - t0_run

    def treat_counterexample(self, word):
        self.num_treatments += 1
        t0_treat = time.clock()
        assert valid(word, self.table.alphabet), "counterexample is not a valid word"
        word = word.split(' ')
        for i in range(len(word)+1):
            prefix = ' '.join(word[:i])
            if prefix not in self.table.S:
                self.table.S.append(prefix)
        self.table.S.sort(key = cmp_to_key(cmpr))
        self.treat_time += time.clock()-t0_treat

    def makeClose(self, new_row):
        """Close table"""
        self.table.S.append(new_row)
        self.table.S.sort(key = cmp_to_key(cmpr))

    def makeConsistent(self, new_suffix):
        """make the table consistent"""
        assert not new_suffix in self.table.E
        self.table.E.append(new_suffix)
        self.table.E.sort(key = cmp_to_key(cmpr))

    def askMQs(self):
        """when classification is missing for some elements in the table, the teacher is asked"""
        for word in self.table.sample():
            if word not in self.table.f.keys():
                self.table.add2f(word, self.teacher.membership_query(word))
                self.num_mq += 1
                if self.print_on: print("Ask MQ for ", word, ":", self.table.f[word])

    def results(self):
        s = {'prefixes'              : len(self.table.S),
             'states'                : len(self.table.states()),
             'boundary'              : len(self.table.R()),
             'suffixes'              : len(self.table.E),
             'concr_sample'          : len(self.table.f),
             'hypotheses'            : len(self.hypothesis),
             'cex'                   : len(self.cex),
             'calls_treat'           : self.num_treatments,
             'TQs'                   : self.num_tests,
             'MQs_to_fill_table'     : self.num_mq,
             'MQs_for_cex_treatment' : self.num_mq_for_cex,
             'words_tested'          : self.num_words_tested,
             'MQs_total'             : self.num_mq + self.num_mq_for_cex,
             'total_run_time'        : self.total_run_time,
             'time_for_testing'      : self.testing_time,
             'time_for_cexs'         : self.treat_time,
             'symbols'               : 0,
             'symb_sample'           : 0}
        return s



##-----------------------------------------------------------##
#  ANGLUIN'S LEARNER -- Maler

class AngluinsPACLearnerMaler:
    """
    Angluin's learner can interact with a teacher which is aware of the target language and can answer to membership queries annd equivalence queries. If the answer to an equivalence query is negative the teacher can provide the learner a counterexample.
    The learner keeps all information in an observation table (OT). He can make a hypothesis and terminates when this hypothesis recognizes correctly the target language.
    """
    def __init__(self, teacher, e = 0.05, d = 0.05, print_on = True, make_file = False, file_name_prefix = ''):
        assert e > 0 and e < 1
        assert d > 0 and d < 1
        assert print_on in [True, False]
        assert make_file in [True, False]
        assert type(file_name_prefix) == str

        self.teacher = teacher
        self.table = OT(self.teacher.alphabet)

        self.learned = False
        self.hypothesis = []
        self.cex = []

        self.parameter = (e,d) # parameters e = accuracy, d=confidence

        self.print_on = print_on

        self.make_file_on = make_file
        self.file_name_prefix = file_name_prefix

        self.reset_counters()

    def reset_counters(self):
        self.num_mq = 0
        self.num_mq_for_cex = 0

        self.num_tests = 0
        self.num_words_tested = 0

        self.num_treatments = 0

        self.total_run_time = 0   # add-up the time run was envoked
        self.testing_time = 0     # time needed for testing
        self.treat_time = 0


    def run(self):
        t0_run = time.clock()
        if self.print_on: print( 'Print is set ON')
        else: print( 'Print is set OFF')
        # start algorithm
        self.learned = False

        while not self.learned:
            # fill in table asking MQs and close if needed
            self.askMQs()
            if self.print_on: print(self.table)

            isClosed, new_state = self.table.is_closed() ## return False and the row fro which not closed
            if not isClosed:
                if self.print_on: print('Table is not closed. Make', new_state,'a new state.')
                self.makeClose(new_state)
                continue # go to next loop

##            isConsistent, new_dist_string = self.table.is_consistent()
##            if not isConsistent:
##                if self.print_on: print 'Table is not Consistent. New distinguishing string', new_dist_string, 'is added to set of suffixes.'
##                self.makeConsistent(new_dist_string)
##                continue # go to next loop

            # Now that table is both Closed and consistent
            # make new hypothesis
            self.hypothesis.append(self.table.automaton())
            i = len(self.hypothesis)-1
            if self.print_on: print( "Table is closed.\nMake hypothesis H"+str(i))
            if self.make_file_on:
                self.hypothesis[-1].make_reduced_dot_graph('HA'+str(i))
                opengv('HA'+str(i))

            if self.print_on: print( "\nTest new hypothesis")
            self.num_tests += 1
            t0_test = time.clock()
            w, words_tested = self.teacher.test(self.hypothesis[-1], i, print_on = self.print_on)
            self.testing_time += time.clock() - t0_test
            self.num_words_tested += words_tested

            if w == True:
                if self.print_on:
                    print( "Target Automaton Learned successfully!")
                    print( "P(error < {e:.2f} ) > {d:.2f} ".format(e = self.parameter[0], d = 1- self.parameter[1]))
                self.learned = True

            else:
                if self.print_on: print( "New counterexample w = ", w)
                self.cex.append(w)

                self.treat_counterexample(w)

        self.total_run_time += time.clock() - t0_run

    def treat_counterexample(self, word):
        self.num_treatments += 1
        t0_treat = time.clock()
        assert valid(word, self.table.alphabet), "counterexample is not a valid word"
        word = word.split(' ')
        for i in reversed(range(len(word))):
            suffix = ' '.join(word[i:])
            if suffix not in self.table.E:
                self.table.E.append(suffix)
        self.table.E.sort(key = cmp_to_key(cmpr))
        self.treat_time += time.clock() - t0_treat


    def makeClose(self, new_row):
        """Close table"""
        self.table.S.append(new_row)
        self.table.S.sort(key = cmp_to_key(cmpr))

    def makeConsistent(self, new_suffix):
        """make the table consistent"""
        assert not new_suffix in self.table.E
        self.table.E.append(new_suffix)
        self.table.E.sort(key = cmp_to_key(cmpr))

    def askMQs(self):
        """when classification is missing for some elements in the table, the teacher is asked"""
        for word in self.table.sample():
            if word not in self.table.f.keys():
                self.table.add2f(word, self.teacher.membership_query(word))
                self.num_mq += 1
                if self.print_on: print( "Ask MQ for ", word, ":", self.table.f[word])

    def results(self):
        s = {'prefixes'              : len(self.table.S),
             'states'                : len(self.table.states()),
             'boundary'              : len(self.table.R()),
             'suffixes'              : len(self.table.E),
             'concr_sample'          : len(self.table.f),
             'hypotheses'            : len(self.hypothesis),
             'cex'                   : len(self.cex),
             'calls_treat'           : self.num_treatments,
             'TQs'                   : self.num_tests,
             'MQs_to_fill_table'     : self.num_mq,
             'MQs_for_cex_treatment' : self.num_mq_for_cex,
             'words_tested'          : self.num_words_tested,
             'MQs_total'             : self.num_mq + self.num_mq_for_cex,
             'total_run_time'        : self.total_run_time,
             'time_for_testing'      : self.testing_time,
             'time_for_cexs'         : self.treat_time,
             'symbols'               : 0,
             'symb_sample'           : 0}
        return s


##-----------------------------------------------------------##
#  ANGLUIN'S LEARNER -- Reduced

class AngluinsPACLearnerReduced:
    """
    Angluin's learner can interact with a teacher which is aware of the target language and can answer to membership queries annd equivalence queries. If the answer to an equivalence query is negative the teacher can provide the learner a counterexample.
    The learner keeps all information in an observation table (OT). He can make a hypothesis and terminates when this hypothesis recognizes correctly the target language.
    """
    def __init__(self, teacher, e = 0.05, d = 0.05, print_on = True, make_file = False, file_name_prefix = ''):
        assert e > 0 and e < 1
        assert d > 0 and d < 1
        assert print_on in [True, False]
        assert make_file in [True, False]
        assert type(file_name_prefix) == str

        self.teacher = teacher
        self.table = OT(self.teacher.alphabet)

        self.learned = False
        self.hypothesis = []
        self.cex = ['']

        self.parameter = (e,d) # parameters e = accuracy, d=confidence

        self.print_on = print_on

        self.make_file_on = make_file
        self.file_name_prefix = file_name_prefix

        self.reset_counters()

    def reset_counters(self):
        self.num_mq = 0
        self.num_mq_for_cex = 0

        self.num_tests = 0
        self.num_words_tested = 0

        self.num_treatments = 0

        self.total_run_time = 0   # add-up the time run was envoked
        self.testing_time = 0     # time needed for testing
        self.treat_time = 0



    def run(self):
        t0_run = time.clock()
        if self.print_on: print( 'Print is set ON')
        else: print( 'Print is set OFF')
        # start algorithm
        self.learned = False

        while not self.learned:
            # fill in table asking MQs and close if needed
            self.askMQs()
            if self.print_on: print( self.table)

            isClosed, new_state = self.table.is_closed() ## return False and the row fro which not closed
            if not isClosed:
                if self.print_on: print( 'Table is not closed. Make', new_state,'a new state.')
                self.makeClose(new_state)
                continue # go to next loop

##            isConsistent, new_dist_string = self.table.is_consistent()
##            if not isConsistent:
##                if self.print_on: print 'Table is not Consistent. New distinguishing string', new_dist_string, 'is added to set of suffixes.'
##                self.makeConsistent(new_dist_string)
##                continue # go to next loop

            # Now that table is Closed
            # make new hypothesis
            self.hypothesis.append(self.table.automaton())
            i = len(self.hypothesis)-1
            if self.print_on:
                print( "Table is closed.\nMake hypothesis H"+str(i))
                print(i)
            if self.make_file_on:
                self.hypothesis[-1].make_reduced_dot_graph('HA'+str(i))
                opengv('HA'+str(i))


            # if the counterexample is still a counterexample
            if self.hypothesis[-1].recognizes(self.cex[-1]) != self.teacher.membership_query(self.cex[-1]):
                if self.print_on: print("treat same counterexample again")
                self.treat_counterexample()
##                self.learned = True
                continue

            # Test current hypothesis
            if self.print_on: print( "\nTest new hypothesis")
            self.num_tests += 1
            t0_test = time.clock()
            w, words_tested = self.teacher.test(self.hypothesis[-1], i, print_on = self.print_on)
            self.testing_time += time.clock() - t0_test
            self.num_words_tested += words_tested

            if w == True:  # if no counterexample has been found then terminate
                if self.print_on:
                    print( "Target Automaton Learned successfully!")
                    print( "P(error < {e:.2f} ) > {d:.2f} ".format(e = self.parameter[0], d = 1- self.parameter[1]))
                self.learned = True

            else:         # else treat the new counterexample
                if self.print_on: print( "New counterexample w = ", w)
                self.cex.append(w)
##                self.learned = True
##                print "treat cex now"
                self.treat_counterexample()

        self.total_run_time += time.clock() - t0_run

# treat counterexample
    def treat_counterexample(self):
        self.num_treatments += 1
        t0_treat = time.clock()
        if self.print_on: print( "Counterexample Treatment")

        # last hypothesis
        H = self.hypothesis[-1]

        # counterexample    w = b(0).b(1).b(2)....b(m-1)
        w = self.cex[-1]

        # check that w is a counterexample
        assert self.teacher.membership_query(w) != H.recognizes(w), str(w)+" is not a counterexample. Search a new one."
        if self.print_on: print
        if self.print_on: print( 'w=',w, )

        ws = w.split()

        flag = H.recognizes(w)
        if self.print_on: print( '\tflag is set to ',flag)

        for i in reversed(range(len(ws))):  # iterate on m, m-1, ... where m is the length of w
            # factorization of cex
            u_i = ' '.join(ws[:i])
            a_i = ws[i]
            v_i = ' '.join(ws[i+1:])
            if self.print_on: print( 'Iteration',i,'on w =',u_i,'.',sconc(a_i,v_i))

            # find the access string for the prefix u_i
            access_string = self.table.S[H.delta_star(H.start, u_i)]
            if self.print_on: print( 'access string =',access_string)

            # replace prefix u_i by its access string
            word = sconc(access_string, sconc(a_i,v_i))
            if self.print_on: print( "word to be tested", word,)

            # test word
            self.num_mq_for_cex += 1
            if self.print_on: print( '\t-->', self.teacher.membership_query(word))
            if self.teacher.membership_query(word) != flag:

                # then the suffix is a distinguishing string and is added to E
                if v_i in self.table.E:
                    # if the suffix exist already in E then proceed to next iteration
                    if self.print_on: print( "the suffix exist already in E then proceed to next iteration")
                    continue
                else:
                    if self.print_on: print( 'add suffix: ', v_i)
                    self.table.E.append(v_i)
                    self.table.E.sort(key = cmp_to_key(cmpr))
                    self.treat_time += time.clock()-t0_treat
                    return
            if self.print_on: print

        print( 'Treatment ended without results')
        self.learned = True
        self.treat_time += time.clock()-t0_treat
##        return False

    def makeClose(self, new_row):
        """Close table"""
        self.table.S.append(new_row)
        self.table.S.sort(key = cmp_to_key(cmpr))

    def makeConsistent(self, new_suffix):
        """make the table consistent"""
        assert not new_suffix in self.table.E
        self.table.E.append(new_suffix)
        self.table.E.sort(key = cmp_to_key(cmpr))

    def askMQs(self):
        """when classification is missing for some elements in the table, the teacher is asked"""
        for word in self.table.sample():
            if word not in self.table.f.keys():
                self.table.add2f(word, self.teacher.membership_query(word))
                self.num_mq += 1
                if self.print_on: print( "Ask MQ for ", word, ":", self.table.f[word])

    def results(self):
        s = {'prefixes'              : len(self.table.S),
             'states'                : len(self.table.states()),
             'boundary'              : len(self.table.R()),
             'suffixes'              : len(self.table.E),
             'concr_sample'          : len(self.table.f),
             'hypotheses'            : len(self.hypothesis),
             'cex'                   : len(self.cex),
             'calls_treat'           : self.num_treatments,
             'TQs'                   : self.num_tests,
             'MQs_to_fill_table'     : self.num_mq,
             'MQs_for_cex_treatment' : self.num_mq_for_cex,
             'words_tested'          : self.num_words_tested,
             'MQs_total'             : self.num_mq + self.num_mq_for_cex,
             'total_run_time'        : self.total_run_time,
             'time_for_testing'      : self.testing_time,
             'time_for_cexs'         : self.treat_time,
             'symbols'               : 0,
             'symb_sample'           : 0}
        return s


##-----------------------------------------------------------##
#  FLOAT RANGE [lowBound, upperBound) representing float
#  alphabet

class Float_Range:
    def __init__(self, lowBound, upperBound):
        self.lowBound = lowBound
        self.upperBound = upperBound

    def contains(self, character):
        return character >= self.lowBound and character < self.upperBound

    def sample(self, sample_size):
        s = []
        for i in range(0, sample_size):
            s.append(random.uniform(self.lowBound, self.upperBound))
        return s



