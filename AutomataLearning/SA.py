import myfunctions as mf
import DFA

class SA:
    """This class represents a Symbolic Automaton."""
    def __init__(self,
                 concrete_alphabet,
                 symbolic_alphabet,
                 states,
                 initial_state,
                 final_states,
                 psi,
                 delta):
        """
        A = (S, SS, Q, ps, q0, F, dd) where double letters stand for symbolic elements.
        S  = concrete_alphabet : An iterable containing the symbols in the DFA's alphabet. Symbols must be immutable.
        SS = symbolic_alphabet : An iterable containing the symbols in the DFA's alphabet. Symbols must be immutable.
        Q  = states: An iterable containing the states of the automaton. States must be immutable.
        ps = psi : A function Q x S -> SS.
        q0 = initial_state : The state at which the automaton startss to operate. It is an element from Q.
        F  = final_states : A subset of Q that indicate the accepting statess of the automaton.
        dd = delta : A function Q x SS -> Q.

        Making delta a function rather than a transition table makes it much easier to define certain DFAs.
        If you want to use a transition table, you can just do this: delta = lambda q,c: transition_table[q][c].

        Names of states and letters in the alphabets should be hashable, i.e., strings, numbers, or tuples of hashables.
        """

        ## States
        self.states = set(states)
        assert initial_state in self.states, 'Initial state does not belong to state set'
        self.initial = initial_state
        self.current_state = initial_state
        self.final  = set([i for i in final_states if i in states])

        ## alphabets
        self.concrete_alphabet = concrete_alphabet
        self.symbolic_alphabet = symbolic_alphabet

        ## functions
        self.psi    = psi
        self.ddelta = delta

        ## semantics
        self.semantics = self.__find_semantics()

    def delta(self, state, letter):
        """
        Concrete transition function Q x S -> Q.
        """
        assert state in self.states, 'State not valid'
        assert letter in self.concrete_alphabet, 'Letter not valid'
        return self.ddelta(state, self.psi(state,letter))

    def delta_star(self, state, word):
        """
        Concrete transition function on words: Q x S* -> Q.
        """
        if type(word) == str:
            word = word.split()
        if word:
            return self.delta_star(self.delta(state, word[0]),word[1:])
        else:
            return state

    def recognizes(self, word):
        """
        Returns TRUE is the word is accepted by the automaton, FALSE otherwise.
        """
##        if type(word) == str and ' ' in word:
##            word = word.split()
        word = word.split()
        if self.delta_star(self.initial, word) in self.final:
            return True
        else:
            return False

    def make_symbolic(self, word, starting_state = None):
        """
        Returns the path followed in the automaton for a 'word' starting from the initial state
        """
        if starting_state == None: current_state = self.initial
        else: current_state = starting_state

        word = word.split()

        symb_word = []
        for i in word:
            symb_word.append(self.psi(current_state, i))
            current_state = self.delta(current_state, i)
        return ' '.join(symb_word)

    def path(self, word, starting_state = None):
        """
        Returns the path followed in the automaton for a 'word' starting from the initial state
        """
        if starting_state == None: current_state = self.initial
        else: current_state = starting_state

        if type(word) == str and ' ' in word:
            word = word.split()

        s = ''
        for i in word:
            s += '('+str(current_state)+') -'+str(i)+'-->'
            current_state = self.delta(current_state, i)
        s += '('+str(current_state)+')'

        return s

    def ppath(self, word, starting_state = None):
        """
        Returns the path followed in the automaton for a 'word' starting from the initial state
        """
        if starting_state == None: current_state = self.initial
        else: current_state = starting_state

##        if type(word) == str and ' ' in word:
        word = word.split()

        s = ''
        for i in word:
            s += '('+str(current_state)+') -'+str(self.psi(current_state, i))+'-->'
            current_state = self.delta(current_state, i)
        s += '('+str(current_state)+')'

        return s

    def __find_semantics(self):
        s = {}
        for state in self.states:
            for letter in self.concrete_alphabet:
                s[self.psi(state, letter)] = s.get(self.psi(state, letter), [])+[letter]
        return s

    def symbolic_alphabet_for_state(self,state):
        assert state in self.states
        alphabet = set()
        for letter in self.concrete_alphabet:
            alphabet.add(self.psi(state, letter))
        return alphabet

    def volume_matrix(self):
        """
        Returns a qsuare matrix V = (vij), where vij = volume(a) if ddelta(state i, symb letter a) = state j and vij = 0 otherwise.
        This matrix gives us information on the ammount of string having some propetry.

        Examples.
        The entry vij simple says how many words of length one start from state i and end in state j.
        This matrix in the power of k gives us information for example about how many strings of length k start from the initial state and and end in final state.
        """
        d1 = dict(enumerate(sorted(self.states)))    # (0,state0), (1,state1), ...
        d2 = dict([(j,i) for (i,j) in d1.items()])   # (state0,0), (state1,1), ...

        alphabet_vol = len(self.concrete_alphabet)
        V = [len(self.states)*[float(0)] for j in self.states]
        for i in self.states:
            for a in self.symbolic_alphabet_for_state(i):
                j = self.ddelta(i,a)
                V[d2[i]][d2[j]] = float(len(self.semantics[a]))/alphabet_vol
        return V, d2
#
# Properties
#
    def isdeterministic(self):
        """
        Predicate that checks if the automaton is deterministic.
        """
        pass

#
#   minimize tha symbolic automaton using dfa's minimization
#
    def minimize(self):
        A = sa2dfa(self)
        A.minimize()
        B = dfa2sa(A)
        self.__init__(B.concrete_alphabet,
                      B.symbolic_alphabet,
                      B.states,
                      B.initial,
                      B.final,
                      B.psi,
                      B.ddelta)


#
#
#

    def copy(self):
        """
        Returns a copy of the DFA. No data is shared with the original.
        """
        return SA(self.concrete_alphabet, self.symbolic_alphabet, self.states, self.initial, self.final, self.psi, self.ddelta)

#
# print outs
#

    def _str_psi(self):
        """
        A string that contains printable information about function psi.
        """
        s  = ' \t ' + '\t '.join([str(i) for i in self.states]) + '\n'
        s2 = ''
        for j in self.concrete_alphabet:
            s1 = ''
            for i in self.states:
                s1 += str(self.psi(i,j)) + '\t'
            if s1 != s2:
                s += str(j) + '\t'
                s += s1 + '\n'
                s2 = str(s1)
        return s

    def _str_ddelta(self):
        """
        A string that contains printable information about function ddelta.
        """
        s = [['']+[str(i) for i in self.symbolic_alphabet]]
        for i in self.states:
            s1 = [str(i)]
            for j in self.symbolic_alphabet:
                try:
                    s1.append(str(self.ddelta(i,j)))
                except KeyError:
                    s1.append('-')
            s.append(s1)
        return '\n'.join(['\t'.join(i) for i in s])

    def __str__(self):
        """
        Displays all information about the automaton in a string format
        """

        s = "\nThis Symbolic Automaton has:\n "
        s += "\nStates: \n" + str(self.states) + '\n'
        s += "\nConcrete Alphabet: \n[" + str(self.concrete_alphabet[0]) + "," + str(self.concrete_alphabet[-1]) + "]\n"
        s += "\nSymbolic Alphabet: \n" + str(self.symbolic_alphabet) + '\n'
        s += "\nStarting state: "  + str(self.initial)
        s += "\nAccepting states: " + str(self.final) +'\n'
        s += "\nPsi:\n"
        s += str(self._str_psi())
        s += "\nTransition function:\n"
        s += str(self._str_ddelta())

        #s += "\nCurrent state: " + str(self.current_state)
        s +=  "\n"
        return s

    def __graph_format(self):
        """
        computes and returns the body of the dot file
        """
        def statelabel(state):
            """
            returns a nice format for naming of states
            """
            label = str(state)
            label = label.replace('(','')
            label = label.replace(')','')
            label = label.replace(', ','_')
            return ' q'+ label

        prefix = 'graph[fontsize=8] rankdir=LR; size="8"; '
        # indicating the initial state
        nodes = ['node [shape=plaintext, style=""]; start; ']
        # doublecircle all final states
        nodes.append('node [shape=doublecircle, style="", color=black]; ')
        if self.final:
            for i in self.final:
                nodes[1] += statelabel(i)
            nodes[1] += ';'
        # the rest of the states have one circle
        nodes.append('node [shape=circle, style="", color=black];')
        # find the transitions
        sides = {}
        for state in self.states:
            for letter in self.symbolic_alphabet:
                try:
                    target_state = self.ddelta(state,letter)
                    if (state,target_state) in sides.keys():
                        sides[(state,target_state)].append(letter)
                    else:
                        sides[(state,target_state)] = [letter]
                except KeyError:
                    pass

        transitions = 'start ->'+statelabel(self.initial)+' [color=blue]; '
        for i in sides:
            transitions += statelabel(i[0]) + ' ->'+statelabel(i[1])
            label = str(sorted(sides[i]))[1:-1]
            transitions += ' [label="' + label + '"]; '



        # make dot file
        s = prefix
        for i in nodes:
                s += i
        s += transitions
        return s

    def _make_dot_file(self, file_name):
        """creates a file with name "file_name.gv" that contains the automaton in DOT language."""
        #from myfunctions import make_dot_graph as mk_graph

        mf.make_dot_graph(file_name,self.__graph_format())

    def open_graph(self, file_name, typ = 'gv'):
        self._make_dot_file(file_name)
        if typ == 'gv': mf.opengv(file_name)
        else:
            mf.gv2pdf(file_name)
            mf.openpdf(file_name)

class SA_Float:
    """This class represents a Symbolic Automaton with float alphabet."""
    def __init__(self,
                 concrete_alphabet,
                 symbolic_alphabet,
                 states,
                 initial_state,
                 final_states,
                 psi,
                 delta,
                 local_symbols,
                 symbol_semantics):
        """
        A = (S, SS, Q, ps, q0, F, dd) where double letters stand for symbolic elements.
        S  = concrete_alphabet : an object of type Float_Range
        SS = symbolic_alphabet : An iterable containing the symbols in the DFA's alphabet. Symbols must be immutable.
        Q  = states: An iterable containing the states of the automaton. States must be immutable.
        ps = psi : A function Q x S -> SS.
        q0 = initial_state : The state at which the automaton startss to operate. It is an element from Q.
        F  = final_states : A subset of Q that indicate the accepting statess of the automaton.
        dd = delta : A function Q x SS -> Q.

        local_symbols: A dictionary Q -> [SS] mapping each state to a list of the local symbols forming its partitions
        symbol_semantics: A dictionary SS -> Float_Range mapping each symbol to its proper semantics

        Making delta a function rather than a transition table makes it much easier to define certain DFAs.
        If you want to use a transition table, you can just do this: delta = lambda q,c: transition_table[q][c].

        Names of states and letters in the alphabets should be hashable, i.e., strings, numbers, or tuples of hashables.
        """

        ## States
        self.states = set(states)
        assert initial_state in self.states, 'Initial state does not belong to state set'
        self.initial = initial_state
        self.current_state = initial_state
        self.final  = set([i for i in final_states if i in states])

        ## alphabets
        self.concrete_alphabet = concrete_alphabet
        self.symbolic_alphabet = symbolic_alphabet

        ## functions
        self.psi    = psi
        self.ddelta = delta

        ## dictionary mapping each state q to the set of symbols ssigma_q
        self.local_symbols = local_symbols
        ## dictionary mapping each symbolic letter ss to a Float_Range of its semantics
        self.symbol_semantics = symbol_semantics

        # TODO: currently semantics is only used in volume matrix. Need to
        # check if it is needed elsewhere
        ## semantics
        # self.semantics = self.__find_semantics()

    def delta(self, state, letter):
        """
        Concrete transition function Q x S -> Q.
        """
        assert state in self.states, 'State not valid'
#       assert letter in self.concrete_alphabet, 'Letter not valid'
        assert self.concrete_alphabet.contains(float(letter)), 'Letter not valid' + str(letter)
#       print(state, letter, self.psi(state,letter))
        return self.ddelta(state, self.psi(state,letter))

    def delta_star(self, state, word):
        """
        Concrete transition function on words: Q x S* -> Q.
        """
        if type(word) == str:
            word = word.split()
        if word:
            return self.delta_star(self.delta(state, word[0]),word[1:])
        else:
            return state

    def recognizes(self, word):
        """
        Returns TRUE is the word is accepted by the automaton, FALSE otherwise.
        """
##        if type(word) == str and ' ' in word:
##            word = word.split()
        word = word.split()
        if self.delta_star(self.initial, word) in self.final:
            return True
        else:
            return False

    def make_symbolic(self, word, starting_state = None):
        """
        Returns the path followed in the automaton for a 'word' starting from the initial state
        """
        if starting_state == None: current_state = self.initial
        else: current_state = starting_state

        word = word.split()

        symb_word = []
        for i in word:
            symb_word.append(self.psi(current_state, i))
            current_state = self.delta(current_state, i)
        return ' '.join(symb_word)

    def path(self, word, starting_state = None):
        """
        Returns the path followed in the automaton for a 'word' starting from the initial state
        """
        if starting_state == None: current_state = self.initial
        else: current_state = starting_state

        if type(word) == str and ' ' in word:
            word = word.split()

        s = ''
        for i in word:
            s += '('+str(current_state)+') -'+str(i)+'-->'
            current_state = self.delta(current_state, i)
        s += '('+str(current_state)+')'

        return s

    def ppath(self, word, starting_state = None):
        """
        Returns the path followed in the automaton for a 'word' starting from the initial state
        """
        if starting_state == None: current_state = self.initial
        else: current_state = starting_state

##        if type(word) == str and ' ' in word:
        word = word.split()

        s = ''
        for i in word:
            s += '('+str(current_state)+') -'+str(self.psi(current_state, i))+'-->'
            current_state = self.delta(current_state, i)
        s += '('+str(current_state)+')'

        return s

    # TODO: fix semantics for SA
#   def __find_semantics(self):
#       s = {}
#       for state in self.states:
#           for letter in self.concrete_alphabet:
#               s[self.psi(state, letter)] = s.get(self.psi(state, letter), [])+[letter]
#       return s

    # This has to be something similar to local alphabet for obstable
    def symbolic_alphabet_for_state(self,state):
        assert state in self.states
#       alphabet = set()
#       for letter in self.concrete_alphabet:
#           alphabet.add(self.psi(state, letter))
#       return alphabet
        return local_symbols[state]

    # REMOVED VOLUME MATRIX FUNCTION 
#   def volume_matrix(self):
#       """
#       Returns a qsuare matrix V = (vij), where vij = volume(a) if ddelta(state i, symb letter a) = state j and vij = 0 otherwise.
#       This matrix gives us information on the ammount of string having some propetry.

#       Examples.
#       The entry vij simple says how many words of length one start from state i and end in state j.
#       This matrix in the power of k gives us information for example about how many strings of length k start from the initial state and and end in final state.
#       """
#       d1 = dict(enumerate(sorted(self.states)))    # (0,state0), (1,state1), ...
#       d2 = dict([(j,i) for (i,j) in d1.items()])   # (state0,0), (state1,1), ...

#       alphabet_vol = len(self.concrete_alphabet)
#       V = [len(self.states)*[float(0)] for j in self.states]
#       for i in self.states:
#           for a in self.symbolic_alphabet_for_state(i):
#               j = self.ddelta(i,a)
#               V[d2[i]][d2[j]] = float(len(self.semantics[a]))/alphabet_vol
#       return V, d2


#
# Properties
#
    def isdeterministic(self):
        """
        Predicate that checks if the automaton is deterministic.
        """
        pass

#
#   minimize tha symbolic automaton using dfa's minimization
#

    # TODO: Minimization is different
#   def minimize(self):
#       A = sa2dfa(self)
#       A.minimize()
#       B = dfa2sa(A)
#       self.__init__(B.concrete_alphabet,
#                     B.symbolic_alphabet,
#                     B.states,
#                     B.initial,
#                     B.final,
#                     B.psi,
#                     B.ddelta)


#
#
#

    def copy(self):
        """
        Returns a copy of the DFA. No data is shared with the original.
        """
        return SA_Float(self.concrete_alphabet, self.symbolic_alphabet, self.states, self.initial, self.final, self.psi, self.ddelta, self.local_symbols, self.symbol_semantics)

#
# print outs
#

    # TODONE: fix str psi // printing semantics instead
    def _str_sem(self):
        """
        A string that contains printable information about function psi.
        """
#       s  = ' \t ' + '\t '.join([str(i) for i in self.states]) + '\n'
#       s2 = ''
#       for j in self.concrete_alphabet:
#           s1 = ''
#           for i in self.states:
#               s1 += str(self.psi(i,j)) + '\t'
#           if s1 != s2:
#               s += str(j) + '\t'
#               s += s1 + '\n'
#               s2 = str(s1)
#       return s

        # IMPOSSIBLE TO PRINT PSI FOR ALL
        # GOING TO PRINT INFORMATION ABOUT THE LOCAL SYMBOLS FOR EACH STATE
        # INSTEAD
        s = ''
        for state in self.states:
            s += 'state ' + str(state) + ': '
            for symbol in self.local_symbols[state]:
                sem = self.symbol_semantics[symbol]
                s += '{' + symbol + ': [' + str(sem.lowBound) + ', ' + str(sem.upperBound) + ')}  '
            s += '\n'
        return s





    def _str_ddelta(self):
        """
        A string that contains printable information about function ddelta.
        """
        s = [['']+[str(i) for i in self.symbolic_alphabet]]
        for i in self.states:
            s1 = [str(i)]
            for j in self.symbolic_alphabet:
                try:
                    s1.append(str(self.ddelta(i,j)))
                except KeyError:
                    s1.append('-')
            s.append(s1)
        return '\n'.join(['\t'.join(i) for i in s])

    def __str__(self):
        """
        Displays all information about the automaton in a string format
        """

        s = "\nThis Symbolic Automaton has:\n "
        s += "\nStates: \n" + str(self.states) + '\n'
        s += "\nConcrete Alphabet: \n[" + str(self.concrete_alphabet.lowBound) + "," + str(self.concrete_alphabet.upperBound) + "]\n"
        s += "\nSymbolic Alphabet: \n" + str(self.symbolic_alphabet) + '\n'
        s += "\nStarting state: "  + str(self.initial)
        s += "\nAccepting states: " + str(self.final) +'\n'
        # TODONE: make sure psi is fixed // printing semantics instead
        # s += "\nPsi:\n"
        s += "\nSemantics:\n"
        s += str(self._str_sem())
        s += "\nTransition function:\n"
        s += str(self._str_ddelta())

        #s += "\nCurrent state: " + str(self.current_state)
        s +=  "\n"
        return s

    def __graph_format(self):
        """
        computes and returns the body of the dot file
        """
        def statelabel(state):
            """
            returns a nice format for naming of states
            """
            label = str(state)
            label = label.replace('(','')
            label = label.replace(')','')
            label = label.replace(', ','_')
            return ' q'+ label

        prefix = 'graph[fontsize=8] rankdir=LR; size="8"; '
        # indicating the initial state
        nodes = ['node [shape=plaintext, style=""]; start; ']
        # doublecircle all final states
        nodes.append('node [shape=doublecircle, style="", color=black]; ')
        if self.final:
            for i in self.final:
                nodes[1] += statelabel(i)
            nodes[1] += ';'
        # the rest of the states have one circle
        nodes.append('node [shape=circle, style="", color=black];')
        # find the transitions
        sides = {}
        for state in self.states:
            for letter in self.symbolic_alphabet:
                try:
                    target_state = self.ddelta(state,letter)
                    sem = self.symbol_semantics[letter]
                    label = letter + ': [' + str(sem.lowBound) + ', ' + str(sem.upperBound) + ')'
                    if (state,target_state) in sides.keys():
                        sides[(state,target_state)].append(label)
                    else:
                        sides[(state,target_state)] = [label]
                except KeyError:
                    pass

        transitions = 'start ->'+statelabel(self.initial)+' [color=blue]; '
        for i in sides:
            transitions += statelabel(i[0]) + ' ->'+statelabel(i[1])
            label = str(sorted(sides[i]))[1:-1]
            transitions += ' [label="' + label + '"]; '

        # make dot file
        s = prefix
        for i in nodes:
                s += i
        s += transitions
        return s

    def _make_dot_file(self, file_name):
        """creates a file with name "file_name.gv" that contains the automaton in DOT language."""
        #from myfunctions import make_dot_graph as mk_graph

        mf.make_dot_graph(file_name,self.__graph_format())

    def open_graph(self, file_name, typ = 'gv'):
        self._make_dot_file(file_name)
        if typ == 'gv': mf.opengv(file_name)
        else:
            mf.gv2pdf(file_name)
            mf.openpdf(file_name)



class SMM_Float:
    """This class represents a Symbolic Moore Machine with float input alphabet."""
    def __init__(self,
                 concrete_alphabet,
                 symbolic_alphabet,
                 output_alphabet,
                 states,
                 initial_state,
#                final_states,
                 output_function,
                 psi,
                 delta,
                 local_symbols,
                 symbol_semantics):
        """
        A = (S, SS, O, Q, ps, q0, lambda, dd) where double letters stand for symbolic elements.
        S  = concrete_alphabet : An object of type Float_Range
        SS = symbolic_alphabet : An iterable containing the symbols in the DFA's alphabet. Symbols must be immutable.
        O  = output alphabet : An iterable containing the output alphabet of the Moore machine. Must be non-empty.
        Q  = states: An iterable containing the states of the automaton. States must be immutable.
        ps = psi : A function Q x S -> SS.
        q0 = initial_state : The state at which the automaton startss to operate. It is an element from Q.
        # F  = final_states : A subset of Q that indicate the accepting statess of the automaton.
        lambda = output_function = A function Q -> O mapping each state to its corresponding output
        dd = delta : A function Q x SS -> Q.

        local_symbols: A dictionary Q -> [SS] mapping each state to a list of the local symbols forming its partitions
        symbol_semantics: A dictionary SS -> Float_Range mapping each symbol to its proper semantics

        Making delta a function rather than a transition table makes it much easier to define certain DFAs.
        If you want to use a transition table, you can just do this: delta = lambda q,c: transition_table[q][c].

        Names of states and letters in the alphabets should be hashable, i.e., strings, numbers, or tuples of hashables.
        """

        ## States
        self.states = set(states)
        assert initial_state in self.states, 'Initial state does not belong to state set'
        self.initial = initial_state
        self.current_state = initial_state
#       self.final  = set([i for i in final_states if i in states])

        ## alphabets
        self.concrete_alphabet = concrete_alphabet
        self.symbolic_alphabet = symbolic_alphabet
        self.output_alphabet = output_alphabet

        ## functions
        self.psi    = psi
        self.ddelta = delta
        self.output_function = output_function

        ## dictionary mapping each state q to the set of symbols ssigma_q
        self.local_symbols = local_symbols
        ## dictionary mapping each symbolic letter ss to a Float_Range of its semantics
        self.symbol_semantics = symbol_semantics

        # TODO: currently semantics is only used in volume matrix. Need to
        # check if it is needed elsewhere
        ## semantics
        # self.semantics = self.__find_semantics()

    def delta(self, state, letter):
        """
        Concrete transition function Q x S -> Q.
        """
        assert state in self.states, 'State not valid'
#       assert letter in self.concrete_alphabet, 'Letter not valid'
        assert self.concrete_alphabet.contains(float(letter)), 'Letter not valid'
#       print(state, letter, self.psi(state,letter))
        return self.ddelta(state, self.psi(state,letter))

    def delta_star(self, state, word):
        """
        Concrete transition function on words: Q x S* -> Q.
        """
        if type(word) == str:
            word = word.split()
        if word:
            return self.delta_star(self.delta(state, word[0]),word[1:])
        else:
            return state

    def compute(self, word):
        """
        Returns the output of the word as computed by the Moore machine.
        Original function name for Automata: recognizes()
        """
##        if type(word) == str and ' ' in word:
##            word = word.split()
        word = word.split()
        # compute the state at which the computation terminates
        out_state = self.delta_star(self.initial, word)
        # output the corresponding output corresponding to the output state
        return self.output_function(out_state)

    def make_symbolic(self, word, starting_state = None):
        """
        Returns the path followed in the automaton for a 'word' starting from the initial state
        """
        if starting_state == None: current_state = self.initial
        else: current_state = starting_state

        word = word.split()

        symb_word = []
        for i in word:
            symb_word.append(self.psi(current_state, i))
            current_state = self.delta(current_state, i)
        return ' '.join(symb_word)

    def path(self, word, starting_state = None):
        """
        Returns the path followed in the automaton for a 'word' starting from the initial state
        """
        if starting_state == None: current_state = self.initial
        else: current_state = starting_state

        if type(word) == str and ' ' in word:
            word = word.split()

        s = ''
        for i in word:
            s += '('+str(current_state)+') -'+str(i)+'-->'
            current_state = self.delta(current_state, i)
        s += '('+str(current_state)+')'

        return s

    def ppath(self, word, starting_state = None):
        """
        Returns the path followed in the automaton for a 'word' starting from the initial state
        """
        if starting_state == None: current_state = self.initial
        else: current_state = starting_state

##        if type(word) == str and ' ' in word:
        word = word.split()

        s = ''
        for i in word:
            s += '('+str(current_state)+') -'+str(self.psi(current_state, i))+'-->'
            current_state = self.delta(current_state, i)
        s += '('+str(current_state)+')'

        return s

    # TODO: fix semantics for SA
#   def __find_semantics(self):
#       s = {}
#       for state in self.states:
#           for letter in self.concrete_alphabet:
#               s[self.psi(state, letter)] = s.get(self.psi(state, letter), [])+[letter]
#       return s

    # This has to be something similar to local alphabet for obstable
    def symbolic_alphabet_for_state(self,state):
        assert state in self.states
#       alphabet = set()
#       for letter in self.concrete_alphabet:
#           alphabet.add(self.psi(state, letter))
#       return alphabet
        return local_symbols[state]

    # REMOVED VOLUME MATRIX FUNCTION 
#   def volume_matrix(self):
#       """
#       Returns a qsuare matrix V = (vij), where vij = volume(a) if ddelta(state i, symb letter a) = state j and vij = 0 otherwise.
#       This matrix gives us information on the ammount of string having some propetry.

#       Examples.
#       The entry vij simple says how many words of length one start from state i and end in state j.
#       This matrix in the power of k gives us information for example about how many strings of length k start from the initial state and and end in final state.
#       """
#       d1 = dict(enumerate(sorted(self.states)))    # (0,state0), (1,state1), ...
#       d2 = dict([(j,i) for (i,j) in d1.items()])   # (state0,0), (state1,1), ...

#       alphabet_vol = len(self.concrete_alphabet)
#       V = [len(self.states)*[float(0)] for j in self.states]
#       for i in self.states:
#           for a in self.symbolic_alphabet_for_state(i):
#               j = self.ddelta(i,a)
#               V[d2[i]][d2[j]] = float(len(self.semantics[a]))/alphabet_vol
#       return V, d2


#
# Properties
#
    def isdeterministic(self):
        """
        Predicate that checks if the automaton is deterministic.
        """
        pass

#
#   minimize tha symbolic automaton using dfa's minimization
#

    # TODO: Minimization is different
#   def minimize(self):
#       A = sa2dfa(self)
#       A.minimize()
#       B = dfa2sa(A)
#       self.__init__(B.concrete_alphabet,
#                     B.symbolic_alphabet,
#                     B.states,
#                     B.initial,
#                     B.final,
#                     B.psi,
#                     B.ddelta)


#
#
#

    def copy(self):
        """
        Returns a copy of the DFA. No data is shared with the original.
        """
        return SMM_Float(self.concrete_alphabet,
                         self.symbolic_alphabet,
                         self.output_alphabet,
                         self.states,
                         self.initial_state,
                         self.output_function,
                         self.psi,
                         self.delta,
                         self.local_symbols,
                         self.symbol_semantics)

#
# print outs
#

    # TODONE: fix str psi // printing semantics instead
    def _str_sem(self):
        """
        A string that contains printable information about function psi.
        """
#       s  = ' \t ' + '\t '.join([str(i) for i in self.states]) + '\n'
#       s2 = ''
#       for j in self.concrete_alphabet:
#           s1 = ''
#           for i in self.states:
#               s1 += str(self.psi(i,j)) + '\t'
#           if s1 != s2:
#               s += str(j) + '\t'
#               s += s1 + '\n'
#               s2 = str(s1)
#       return s

        # IMPOSSIBLE TO PRINT PSI FOR ALL
        # GOING TO PRINT INFORMATION ABOUT THE LOCAL SYMBOLS FOR EACH STATE
        # INSTEAD
        s = ''
        for state in self.states:
            s += 'state ' + str(state) + ': '
            for symbol in self.local_symbols[state]:
                sem = self.symbol_semantics[symbol]
                s += '{' + symbol + ': [' + str(sem.lowBound) + ', ' + str(sem.upperBound) + ')}  '
            s += '\n'
        return s





    def _str_ddelta(self):
        """
        A string that contains printable information about function ddelta.
        """
        s = [['']+[str(i) for i in self.symbolic_alphabet]]
        for i in self.states:
            s1 = [str(i)]
            for j in self.symbolic_alphabet:
                try:
                    s1.append(str(self.ddelta(i,j)))
                except KeyError:
                    s1.append('-')
            s.append(s1)
        return '\n'.join(['\t'.join(i) for i in s])

    def _str_output_function(self):
        """
        A string represing the output function mapping each state to an output
        """
        s = ''
        for q in self.states:
            s += str(q)
            s += ' : '
            s += str(self.output_function(q))
            s += '\n'
        return s

    def __str__(self):
        """
        Displays all information about the automaton in a string format
        """

        s = "\nThis Symbolic Automaton has:\n "
        s += "\nStates: \n" + str(self.states) + '\n'
        s += "\nConcrete Alphabet: \n[" + str(self.concrete_alphabet.lowBound) + "," + str(self.concrete_alphabet.upperBound) + "]\n"
        s += "\nSymbolic Alphabet: \n" + str(self.symbolic_alphabet) + '\n'
        s += "\nOutput Alphabet: \n" + str(self.output_alphabet) + '\n'
        s += "\nStarting state: "  + str(self.initial) + '\n'
#       s += "\nAccepting states: " + str(self.final) +'\n'
        s += "\nState outputs:\n" + str(self._str_output_function())
        # TODONE: make sure psi is fixed // printing semantics instead
#       s += "\nPsi:\n"
        s += "\nSemantics:\n"
        s += str(self._str_sem())
        s += "\nTransition function:\n"
        s += str(self._str_ddelta())

        #s += "\nCurrent state: " + str(self.current_state)
        s +=  "\n"
        return s

    def __graph_format(self):
        """
        computes and returns the body of the dot file
        """
        def statelabel(state):
            """
            returns a nice format for naming of states
            """
            output = str(self.output_function(state))
            label = str(state)
            label = label.replace('(','')
            label = label.replace(')','')
            label = label.replace(', ','_')
            return '" q'+ label + ' / ' + output + '"'

        prefix = 'graph[fontsize=8] rankdir=LR; size="8"; '
        # indicating the initial state
        nodes = ['node [shape=plaintext, style=""]; start; ']
#       # doublecircle all final states
#       nodes.append('node [shape=doublecircle, style="", color=black]; ')
#       if self.final:
#           for i in self.final:
#               nodes[1] += statelabel(i)
#           nodes[1] += ';'
        # the rest of the states have one circle
        nodes.append('node [shape=circle, style="", color=black];')
        # find the transitions
        sides = {}
        for state in self.states:
            for letter in self.symbolic_alphabet:
                try:
                    target_state = self.ddelta(state,letter)
                    sem = self.symbol_semantics[letter]
                    label = letter + ': [' + str(sem.lowBound) + ', ' + str(sem.upperBound) + ')'
                    if (state,target_state) in sides.keys():
                        sides[(state,target_state)].append(label)
                    else:
                        sides[(state,target_state)] = [label]
                except KeyError:
                    pass

        transitions = 'start ->'+statelabel(self.initial)+' [color=blue]; '
        for i in sides:
            transitions += statelabel(i[0]) + ' ->'+statelabel(i[1])
            label = str(sorted(sides[i]))[1:-1]
            transitions += ' [label="' + label + '"]; '

        # make dot file
        s = prefix
        for i in nodes:
                s += i
        s += transitions
        return s

    def _make_dot_file(self, file_name):
        """creates a file with name "file_name.gv" that contains the automaton in DOT language."""
        #from myfunctions import make_dot_graph as mk_graph

        mf.make_dot_graph(file_name,self.__graph_format())

    def open_graph(self, file_name, typ = 'gv'):
        self._make_dot_file(file_name)
        if typ == 'gv': mf.opengv(file_name)
        else:
            mf.gv2pdf(file_name)
            mf.openpdf(file_name)


# TODO: why is symmetric difference needed?
def symmetric_difference(sa1, sa2):
    for f in [sa1,sa2]:
        assert f.__module__+"."+f.__class__.__name__ == 'SA.SA'

    # alphabets
    assert set(sa1.concrete_alphabet) == set(sa1.concrete_alphabet)
    concrete_alphabet = sa1.concrete_alphabet
    symbolic_alphabet = [(i,j) for i in sa1.symbolic_alphabet for j in sa2.symbolic_alphabet]

    # states
    states  = set([(i,j) for i in sa1.states for j in sa2.states])
    initial = (sa1.initial, sa2.initial)
    assert initial in states
    final = [q for q in states
             if ((q[0] in sa1.final and q[1] not in sa2.final)
                 or
                 (q[0] not in sa1.final and q[1] in sa2.final))]

    # ddelta: states x symb_alph --> states
    ddelta = lambda state, symb_letter: (sa1.ddelta(state[0],symb_letter[0]), sa2.ddelta(state[1],symb_letter[1]))

    # psi: states x concr_alph --> symb_alph
    psi = lambda state, letter: (sa1.psi(state[0],letter), sa2.psi(state[1],letter))


##    return concrete_alphabet, symbolic_alphabet, states, initial, final, psi, ddelta

    return SA(concrete_alphabet,
              symbolic_alphabet,
              states,
              initial,
              final,
              psi,
              ddelta)
##

###########################################################
# Automata transformations
#----------------------------------------------------------


def dfa2sa(aDfa):
    """gives an equivalent automaton in SA format. Semantics are not convex sets."""
    states     = sorted(aDfa.states)
    concr_alph = sorted(aDfa.alphabet, cmp = mf.cmpr)
    psi   = {}
    ddelta = {}
    for state in states:
        symb_letter = ''
        for letter in concr_alph:
            current_letter = 'a('+str(state)+','+str(aDfa.delta(state, letter))+')'
            psi[state, letter] = current_letter
            if current_letter != symb_letter:
                ddelta[state, current_letter] = aDfa.delta(state, letter)
            symb_letter = current_letter


    symb_alph    = sorted(set(psi.values()))
    final_psi    = lambda state,letter : psi[state,letter]
    final_ddelta = lambda state,letter : ddelta[state,letter]

    return SA(concrete_alphabet = concr_alph,
              symbolic_alphabet = sorted(symb_alph),
              states = states,
              initial_state = aDfa.start,
              final_states  = sorted(aDfa.accepts),
              psi = final_psi,
              delta = final_ddelta)



def sa2dfa(aSymbolicAutomaton):
    """gives an equivalent automaton in DFA format"""
    delta = lambda state,letter : aSymbolicAutomaton.ddelta(state, aSymbolicAutomaton.psi(state, letter))
    return DFA.DFA(states   = aSymbolicAutomaton.states,
                   alphabet = aSymbolicAutomaton.concrete_alphabet,
                   delta    = delta,
                   start    = aSymbolicAutomaton.initial,
                   accepts  = aSymbolicAutomaton.final)
