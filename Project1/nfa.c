/*
 * File: nfa.h
 * Creator: George Ferguson
 * Created: Thu Sep  1 17:54:41 2016
 * Time-stamp: <Tue Aug  8 11:45:49 EDT 2017 ferguson>
 */

#ifndef _nfa_h
#define _nfa_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "IntSet.h"
#include "nfa.h"
#include "IntSet.c"

/**
 * The data structure used to represent a nondeterministic finite automaton.
 * @see FOCS Section 10.3
 * @see Comments for DFA in dfa.h
 */

typedef struct{
    IntSet transition[128];
    bool isAccepting;
} STATES;

typedef struct{
    int numOfStates;
    IntSet currentStates;
    STATES *stateArray;
} NFA;

/**
 * Allocate and return a new NFA containing the given number of states.
 */
extern NFA* NFA_new(int nstates){
    NFA *nfa = (NFA*)malloc(sizeof(NFA));
    nfa->numOfStates = nstates;
    //Create a set for the current possible states, and adding 0 to that Set.
    nfa->currentStates = IntSet_new();
    IntSet_add(nfa->currentStates, 0);

    nfa->stateArray = (STATES *)malloc(nstates*sizeof(STATES));

    for(int i = 0; i < 128; i++){
        nfa->stateArray->transition[i] = IntSet_new();
    }

    return nfa;
}

/**
 * Free the given NFA.
 */
extern void NFA_free(NFA* nfa);

/**
 * Return the number of states in the given NFA.
 */
extern int NFA_get_size(NFA* nfa);

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
extern IntSet NFA_get_transitions(NFA* nfa, int state, char sym);

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
extern void NFA_add_transition(NFA* nfa, int src, char sym, int dst){
        IntSet_add(nfa->stateArray[src].transition[sym], dst);
}

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
extern void NFA_add_transition_str(NFA* nfa, int src, char *str, int dst);

/**
 * Add a transition for the given NFA for each input symbol.
 */
extern void NFA_add_transition_all(NFA* nfa, int src, int dst){

    for(int i = 0; i < 128; i++){
        if(IntSet_is_empty(nfa->stateArray[src].transition[i])){
            nfa->stateArray[src].transition[i] = IntSet_new();
            IntSet_add(nfa->stateArray[src].transition[i], dst);
        }else{
            IntSet_add(nfa->stateArray[src].transition[i], dst);
        }
    }
}

/**
 * Set whether the given NFA's state is accepting or not.
 */
extern void NFA_set_accepting(NFA* nfa, int state, bool value);

/**
 * Return true if the given NFA's state is an accepting state.
 */
extern bool NFA_get_accepting(NFA* nfa, int state);

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
extern bool NFA_execute(NFA* nfa, char *input);

/**
 * Print the given NFA to System.out.
 */
extern void NFA_print(NFA* nfa);

extern void problem_2_a(){
    printf("Problem 2a (Strings ending in man)--------------------------------------------\n");
    printf("Only accepts 64 characters\n");
    printf("Enter quit to exit the problem\n");

}


int main(int argc, char* argv[]) {

    NFA* testNFA = NFA_new(2);

    NFA_add_transition(testNFA, 0, 'a', 1);
    NFA_add_transition(testNFA, 0, 'b', 1);
    NFA_add_transition_all(testNFA, 0, 0);

    for(int i = 0; i < 128; i++){
        printf("i: %d ", i);
        IntSet_print(testNFA->stateArray->transition[i]);
        printf("\n");
    }
}

#endif


