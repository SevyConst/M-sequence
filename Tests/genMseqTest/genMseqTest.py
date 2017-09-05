from scipy.signal import max_len_seq
from random import randint
import json

# This dictionary copied from Scipy _max_len_seq.py. It contains default
# "taps" for generating m-sequence (also known as Maximum length sequence
# or MLS) with different lengths of registers. key  - length of register.
# Value - taps which allow to generate M-sequence.
_dictionary_taps = {5: [3], 6: [5], 7: [6], 8: [7, 6, 1],
             9: [5], 10: [7], 11: [9], 12: [11, 10, 4], 13: [12, 11, 8]}


def gen_init_state(state_length):
    ''' Generate initial state randomly

    state_length -- length of returned array

    Returns: list. Contains only 1 and 0.
    Must contains at least one 1

    '''
    state = []  # returning value

    all_zeros = True
    while (all_zeros):
        for i in range(state_length):
            state.append(randint(0, 1))
            if state[i] == 1:
                all_zeros = False

    return state


def prepare_for_json(state, taps, m_seq):
    '''Prepare data about SINGLE M-sequence for writing to file

    arguments:
    state - initial state (np.ndarray)
    taps - taps of LSFR (list)
    m_seq - samples of M-sequence (np.array)

    returns: dictionary with all above data about one M-sequence

    '''

    dictionary_state = {}
    for j in range(len(state)):
        dictionary_state[j] = state[j]

    # convert np.array m-seq for writing to JSON file
    m_seq = m_seq.tolist()
    dictionary_m_seq = {}
    for j in range(len(m_seq)):
        dictionary_m_seq[j] = m_seq[j]

    # All information about one M-sequence
    return {"initial state": dictionary_state,
            "taps": taps,
            "samples of M-sequence": dictionary_m_seq}


def write_json(data):

    filename = "M-sequences.json"
    myfile = open(filename, mode='w')
    json.dump(data, myfile, indent=2)
    myfile.close()


if __name__ == '__main__':

    # all data which will be written to JSON file
    all_data = {}

    num_test = 0

    # generate M-sequences
    for register_length in _dictionary_taps:

        # randomly generate initial state for register
        state = gen_init_state(register_length)

        # pick up taps from the dictionary _dictionary_taps
        taps = _dictionary_taps[register_length]

        # period of generated M-sequence
        period = 2**register_length - 1

        # Number of samples of M-sequence
        # for testing slightly more then one period
        num_samples = period + register_length

        # generate array M-sequence
        m_seq = max_len_seq(register_length, state, num_samples, taps)[0]

        # generate array M-sequence
        m_seq = max_len_seq(register_length, state, num_samples, taps)[0]

        data_single_m_seq = prepare_for_json(state, taps, m_seq)
        all_data["No. " + str(num_test)] = data_single_m_seq

        num_test += 1

    write_json(all_data)
