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

/**
 * The data structure used to represent a nondeterministic finite automaton.
 * @see FOCS Section 10.3
 * @see Comments for DFA in dfa.h
 */

typedef struct{
    IntSet* transition[128];
    bool isAccepting;
} STATES;

typedef struct{
    int numOfStates;
    int numOfAcceptingStates;
    IntSet *currentStates;
    int *acceptingStates;
    STATES *stateArray;
} NFA;

/**
 * Allocate and return a new NFA containing the given number of states.
 */
extern NFA* NFA_new(int nstates){
    NFA *nfa = (NFA*)malloc(sizeof(NFA));
    nfa->numOfStates = nstates;
    nfa->currentStates = IntSet_new();
    IntSet_add(nfa->currentStates, 0);
    nfa->numOfAcceptingStates = 0;
    nfa->stateArray = (STATES *)malloc(nstates*sizeof(STATES));
    nfa->acceptingStates = (int *)malloc(nstates*sizeof(int));
    //Initialize the accepting state array to "NULL"
    for(int i = 0; i < nstates; i++){
        nfa->acceptingStates[i] = -1;
    }
    for (int i = 0; i < nstates; i++) {
        nfa->stateArray[i].isAccepting = false;
    }
    for (int i = 0; i < nstates; i++) {
        for (int j = 0; j < 128; j++) {
            nfa->stateArray[i].transition[j] = IntSet_new();
        }
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
extern int NFA_get_size(NFA* nfa){
    return nfa->numOfStates;
}

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
extern IntSet* NFA_get_transitions(NFA* nfa, int state, char sym){
    return nfa->stateArray[state].transition[sym];
}

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
extern void NFA_add_transition_str(NFA* nfa, int src, char *str, int dst){
    for (int i = 0; str[i] != '\0'; i++) {
        IntSet_add(nfa->stateArray[src].transition[str[i]], dst);

    }
}

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
extern void NFA_set_accepting(NFA* nfa, int state, bool value) {
    nfa->stateArray[state].isAccepting = value;
    nfa->numOfAcceptingStates++;
    for(int i = 0; i < nfa->numOfAcceptingStates; i++){
        if(nfa->acceptingStates[i] == -1){
            nfa->acceptingStates[i] = state;
            break;
        }
    }
}

/**
 * Return true if the given NFA's state is an accepting state.
 */
extern bool NFA_get_accepting(NFA* nfa, int state) {
    return nfa->stateArray[state].isAccepting;
}

void NFA_set_current_state(NFA* nfa, int statenum){
    IntSet *stateSet = IntSet_new();
    IntSet_add(stateSet, statenum);
    if (IntSet_is_empty(nfa->currentStates)) {

    };
}


/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
extern bool NFA_execute(NFA* nfa, char *input){
    for (int j = 0; j < nfa->numOfStates; j++) {
        for (int i = 0; input[i] != '\0'; i++) {
            //if (IntSet_is_empty(nfa->stateArray[j].transition[i]) != true) {
            if (IntSet_is_empty(nfa->stateArray[j].transition[input[i]]) != true) {

                //Every state is being inserting into currentStates, which is incorrect

                IntSetIterator* iterator = IntSet_iterator(nfa->stateArray[j].transition[input[i]]);
                IntSet *tempSet = IntSet_new();
                while(IntSetIterator_has_next(iterator)) {
                    int iteratorNext = IntSetIterator_next(iterator);
                    if (IntSet_contains(nfa->currentStates, iteratorNext) != true) {
                        //IntSet_union(nfa->currentStates, nfa->stateArray[j].transition[input[i]]);
                        IntSet_union(tempSet, nfa->stateArray[j].transition[input[i]]);
                        printf("tempSet: ");
                        IntSet_print(tempSet);
                        printf("\n");
                        nfa->currentStates = tempSet;
                        printf("tempSet after currentStates=tempSet : ");
                        IntSet_print(tempSet);
                        printf("\n");
                   }

                }
            }
        }
    }
    for(int i = 0; i < nfa->numOfAcceptingStates; i++){
            if (IntSet_contains(nfa->currentStates, nfa->acceptingStates[i])){
                printf("Accepting states: %d\n", nfa->acceptingStates[i]);
                printf("current states set: ");
                IntSet_print(nfa->currentStates);

                printf("\ntrue\n");
                return true;
            }
    }
    printf("false");
    return false;
}

extern IntSet* give_int_set(NFA* nfa, char input, int state) {
    return nfa->stateArray[state].transition[input];
}

extern bool NFA_execute2(NFA* nfa, char *input){
    IntSet* tempSet = IntSet_new();
    IntSet* beginSet = IntSet_new();
    IntSet_add(tempSet, 0);
    IntSet* middleSet;
    for (int i = 0; input[i] != '\0'; i++) {
        beginSet = tempSet;
        IntSetIterator* iterator = IntSet_iterator(beginSet);
        middleSet = IntSet_new();
        while(IntSetIterator_has_next(iterator)) {
            int iteratorFirst = IntSetIterator_next(iterator);
            tempSet = give_int_set(nfa, input[i], iteratorFirst);
            IntSet_union(middleSet, tempSet);
            if (!IntSetIterator_has_next(iterator)) {
                tempSet = middleSet;
                break;
            }
        }
    }
    nfa->currentStates = tempSet;
    for(int i = 0; i < nfa->numOfAcceptingStates; i++){
        if (IntSet_contains(nfa->currentStates, nfa->acceptingStates[i])){
            //printf("Accepting states: %d\n", nfa->acceptingStates[i]);
            //printf("current states set: ");
            //IntSet_print(nfa->currentStates);

            //printf("\ntrue\n");
            return true;
        }
    }
    //printf("false");
    return false;
}

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

    problem_2_a();
    NFA* testNFA = NFA_new(4);
    //IntSet_print(testNFA->stateArray[1].transition['a']);
    NFA_add_transition(testNFA, 0, 'm', 1);
    NFA_add_transition(testNFA, 1, 'a', 2);
    NFA_add_transition(testNFA, 2, 'n', 3);
    NFA_add_transition_all(testNFA, 0, 0);
    NFA_set_accepting(testNFA, 3, true);
    printf("Evaluation: %d\n", NFA_execute2(testNFA, "maan"));
    /*
    for (int j = 0; j < testNFA->numOfStates; j++) {
        for (int i = 0; i < 128; i++) {
            if (IntSet_is_empty(testNFA->stateArray[j].transition[i]) != true) {
                printf("State: %d\n", j);
                printf("c: %c ", i);
                IntSet_print(testNFA->stateArray[j].transition[i]);
                printf("\n");
            }
        }
    }
     */

}

#endif