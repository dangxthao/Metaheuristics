import random

###########################################################
# Functions we need for words over the reals
#----------------------------------------------------------
def cmp(a,b):
    """cmp funtion from python 2 used here to tranfer code to python 3"""
    return (a>b)-(a<b)

def cmpr(a,b):  # length-lexicographical order for symbolic words over the reals
    a_ = a.split()
    b_ = b.split()
    if a == b:
        return 0
    elif len(a_) != len(b_):
        return cmp(len(a_), len(b_))
    else:
        t = [cmp(float(i),float(j)) for (i,j) in zip(a_,b_)
             if cmp(float(i),float(j))]
#       t = [cmp(int(i),int(j)) for (i,j) in zip(a_,b_)
#            if cmp(int(i),int(j))]
        return t[0]

def sconc(*words):
    """symbolic concatenation of all words in *words"""
    w = ''
    for word in words:
        if word:
            w = w + ' ' + word.strip()
    return w.strip()
##sc = sconc

def valid(word, alphabet):
    word = word.split(' ')
    for letter in word:
        if letter not in alphabet:
            return False
    return True

# valid function for when alphabet is of type Float_Range
def valid_float(word, alphabet):
    word = word.split(' ')
    for letter in word:
        if not alphabet.contains(float(letter)):
            return False
    return True

#################################################################
# Find random word
#----------------------------------------------------------------

def random_word(alphabet, length = None, n = 1):
    """
    This function generates a random word on the alphabet given.
    Length is a non negative number and
    if given the function returns a random word of this length.
    If length is not given a word of arbitrary length is given as output.
    In this case we force the function to stop earlier as we increase number n
    """
    if length == None:
        assert type(n) == int, 'n must be integer'
        word = ''
        alphabet = alphabet + ['']
        letter = random.choice(alphabet)
        while letter:
            word = sconc(word,letter)
            alphabet = alphabet + n*['']
            letter = random.choice(alphabet)
        return word
    try:
        length = int(length)
    except:
        raise TypeError('length must be a number')
    if length == 0:
        return ''
    elif int(length) > 0:
        letter = random.choice(list(alphabet))
        word = sconc(random_word(alphabet, length -1), letter)
        return word
    else:
        raise ValueError('length must be non negative')

# Find a random word when the alphabet of type Float_Range
# TODO: Problem with the stopping criterion and length in case of Float_Range
# For the moment, set n manually and let it the algorithm return '' with
# probability 1/n while decreasing n by 1 at each iteration.
# Problem with this approach is that length of returned word is at most n
def random_word_float(alphabet, length = None, n = 100):
    """
    This function generates a random word on the alphabet given.
    Length is a non negative number and
    if given the function returns a random word of this length.
    If length is not given a word of arbitrary length is given as output.
    In this case we force the function to stop earlier as we increase number n
    """
    if length == None:
        assert type(n) == int, 'n must be integer'
        word = ''
#       alphabet = alphabet + ['']
        # set letter to '' with probability 1/n
        rand_n = random.randint(1, n)
        if rand_n % n == 0:
            letter = ''
        else:
            letter = str(random.uniform(alphabet.lowBound, alphabet.upperBound))
#       letter = random.choice(alphabet)
        while letter:
            word = sconc(word,letter)
#           alphabet = alphabet + n*['']
            # decrease n so that next time '' will be picked with higher
            # probability
            n = n - 1
            rand_n = random.randint(1, n)
            if rand_n % n == 0:
                letter = ''
            else:
                letter = str(random.uniform(alphabet.lowBound, alphabet.upperBound))
#           letter = random.choice(alphabet)
        return word
    try:
        length = int(length)
    except:
        raise TypeError('length must be a number')
    if length == 0:
        return ''
    elif int(length) > 0:
#       letter = random.choice(list(alphabet))
        letter = str(random.uniform(alphabet.lowBound, alphabet.upperBound))
#       word = sconc(random_word(alphabet, length -1), letter)
        word = sconc(random_word_float(alphabet, length -1), letter)
        return word
    else:
        raise ValueError('length must be non negative')

###########################################################
# Make for .gv or .dot files (graphs in DOT language)
#----------------------------------------------------------
def make_dot_graph(file_name, main):
    prefix = "digraph " + file_name + " {"
    suffix = "};"
    main = str(main)

    with open(file_name + ".gv",'w') as f:
        s = prefix + main + suffix
        f.write(s)


###########################################################
# Transform files
#----------------------------------------------------------

def gv2pdf(name1, name2 = None):
    if name2 == None:
        name2 = name1
    from os import system
    command = 'dot -Tpdf -o "' + name2 + '.pdf" -v ' + name1 + '.gv'
    system(command)


###########################################################
# Open files
#----------------------------------------------------------

def opengv(name):
    from os import system
    command = "dotty " + name + ".gv & "
    system(command)

def openpdf(name):
    from os import system
    command = "okular " + name + ".pdf & "
    system(command)

###########################################################
# Make the .gv file for an automaton
#----------------------------------------------------------
def label_reduction(dot_graph_string):
    """
    creates a file with name "file_name.gv" that contains the automaton in DOT language.
    """
    s = dot_graph_string
    result = ''
    while 'label' in s:
        pos0 = s.find('label="') + 7
        pos1 = s.find('"',pos0)
        s_ = s[pos0:pos1]
        if ',' in s_:
            s_ = transformation(s_)
        result += s[:pos0]+s_
        s = s[pos1:]

    return result + s

def transformation(string):
    # auxilary function for 'transform_DOT_file'
    # metatrepei mia akolouthia tis morfis px
    # [1,2,3,4,5,6] se [1,6] or
    # [1,2,3,4,7,8,9] se [1,4],[7,9]
        s = string.split(',')
        lst = [int(i) for i in s]
        lst.sort()

        ls = ''
        for i in range(len(lst)):
                if len(lst) == 1:
                        ls += str(lst[0])
                        break
                if i == 0:
                        ls += '[' + str(lst[i]) + ', '
                else:
                        if lst[i] == lst[i-1] +1:
                                if i == len(lst)-1:
                                        ls += str(lst[i]) + ']'
                                        break
                        else:
                                ls += str(lst[i-1])
                                ls += '], [' + str(lst[i]) + ', '
                                if i == len(lst)-1:
                                        ls += ']'

        return ls

def figure(name,automaton):
    """
    makes and opens the dot graph of the automaton given and
    stores it under the name 'name.gv'
    """
    print("Creating dot graph: ", name)
    make_dot_graph(name, label_reduction(automaton.graph_format()))
    opengv(name)



###################################################################
#  Open all the hypotheses (SA) made by a learner in .gv and .pdf
#------------------------------------------------------------------

def hypothesesGVfiles(learner, prefix = 'H', save_as_pdf = False):
    for i in range(len(learner.hypothesis)):
        A = learner.hypothesis[i]
        A.open_graph(prefix+str(i))
        if save_as_pdf:
            gv2pdf(prefix+str(i))
