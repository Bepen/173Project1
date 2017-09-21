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
#include <string.h>
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

extern bool char_check_contains(char* exc, char c) {
    for (int i = 0; exc[i] != '\0'; i++) {
        if (exc[i] == c) {
            return true;
        }
    }
    return false;
}

extern void NFA_set_transition_exception(NFA* nfa, int src, int dst, char* exc) {
    for (int i = 0; i < 128; i++) {
        if (!char_check_contains(exc, i)) {
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

extern IntSet* give_int_set(NFA* nfa, char input, int state) {
    return nfa->stateArray[state].transition[input];
}

extern bool NFA_execute(NFA* nfa, char *input){
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
    NFA* problem2a = NFA_new(4);
    //IntSet_print(testNFA->stateArray[1].transition['a']);
    NFA_add_transition(problem2a, 0, 'm', 1);
    NFA_add_transition(problem2a, 1, 'a', 2);
    NFA_add_transition(problem2a, 2, 'n', 3);
    NFA_add_transition_all(problem2a, 0, 0);
    NFA_set_accepting(problem2a, 3, true);
    while (1) {
        NFA_set_current_state(problem2a, 0);
        char *input = malloc(64*sizeof(char));
        printf("Test: ");
        scanf("%s", input);

        if (strncmp(input, "quit", 4) == 0) {
            printf("Quitting Problem 2a\n");
            break;
        }

        int test = NFA_execute(problem2a, input);
        if (test == 0) {
            printf("%s is not accepted\n", input);
        }
        if (test == 1) {
            printf("%s is accepted\n", input);
        }
    }
    printf("\n");

}


extern void problem_2_b(){
    printf("Problem 2b (Strings with more than one a, g, h, i, o, s, t, or w, or more than two n’s)--------------------------------------------\n");
    printf("Only accepts 64 characters\n");
    printf("Enter quit to exit the problem\n");
    NFA* problem2b = NFA_new(20);

    NFA_add_transition_all(problem2b, 0, 0);

    NFA_add_transition(problem2b, 0, 'a', 1);
    NFA_set_transition_exception(problem2b, 1, 1, "a");
    NFA_add_transition(problem2b, 1, 'a', 2);
    NFA_add_transition_all(problem2b, 2, 2);

    NFA_add_transition(problem2b, 0, 'g', 3);
    NFA_set_transition_exception(problem2b, 3, 3, "g");
    NFA_add_transition(problem2b, 3, 'g', 4);
    NFA_add_transition_all(problem2b, 4, 4);

    NFA_add_transition(problem2b, 0, 'h', 5);
    NFA_set_transition_exception(problem2b, 5, 5, "h");
    NFA_add_transition(problem2b, 5, 'h', 6);
    NFA_add_transition_all(problem2b, 6, 6);

    NFA_add_transition(problem2b, 0, 'i', 7);
    NFA_set_transition_exception(problem2b, 7, 7, "i");
    NFA_add_transition(problem2b, 7, 'i', 8);
    NFA_add_transition_all(problem2b, 8, 8);

    NFA_add_transition(problem2b, 0, 'n', 9);
    NFA_set_transition_exception(problem2b, 9, 9, "n");
    NFA_add_transition(problem2b, 9, 'n', 10);
    NFA_set_transition_exception(problem2b, 10, 10, "n");
    NFA_add_transition(problem2b, 10, 'n', 11);
    NFA_add_transition_all(problem2b, 11, 11);

    NFA_add_transition(problem2b, 0, 'o', 12);
    NFA_set_transition_exception(problem2b, 12, 12, "o");
    NFA_add_transition(problem2b, 12, 'o', 13);
    NFA_add_transition_all(problem2b, 13, 13);

    NFA_add_transition(problem2b, 0, 's', 14);
    NFA_set_transition_exception(problem2b, 14, 14, "s");
    NFA_add_transition(problem2b, 14, 's', 15);
    NFA_add_transition_all(problem2b, 15, 15);

    NFA_add_transition(problem2b, 0, 't', 16);
    NFA_set_transition_exception(problem2b, 16, 16, "t");
    NFA_add_transition(problem2b, 16, 't', 17);
    NFA_add_transition_all(problem2b, 17, 17);

    NFA_add_transition(problem2b, 0, 'w', 18);
    NFA_set_transition_exception(problem2b, 18, 18, "w");
    NFA_add_transition(problem2b, 18, 'w', 19);
    NFA_add_transition_all(problem2b, 19, 19);

    NFA_set_accepting(problem2b, 2, true);
    NFA_set_accepting(problem2b, 4, true);
    NFA_set_accepting(problem2b, 6, true);
    NFA_set_accepting(problem2b, 8, true);
    NFA_set_accepting(problem2b, 11, true);
    NFA_set_accepting(problem2b, 13, true);
    NFA_set_accepting(problem2b, 15, true);
    NFA_set_accepting(problem2b, 17, true);
    NFA_set_accepting(problem2b, 19, true);


    while (1) {
        NFA_set_current_state(problem2b, 0);
        char *input = malloc(64*sizeof(char));
        printf("Test: ");
        scanf("%s", input);

        if (strncmp(input, "quit", 4) == 0) {
            printf("Quitting Problem 2b\n");
            break;
        }

        int test = NFA_execute(problem2b, input);
        if (test == 0) {
            printf("%s is not accepted\n", input);
        }
        if (test == 1) {
            printf("%s is accepted\n", input);
        }
    }
    printf("\n");

}

extern void problem_2_c(){
    printf("Problem 2c (Strings with 'code' anywhere in it)--------------------------------------------\n");
    printf("Only accepts 64 characters\n");
    printf("Enter quit to exit the problem\n");
    NFA* problem2c = NFA_new(5);

    NFA_add_transition_all(problem2c, 0, 0);
    NFA_add_transition(problem2c, 0, 'c', 1);
    NFA_add_transition(problem2c, 1, 'o', 2);
    NFA_add_transition(problem2c, 2, 'd', 3);
    NFA_add_transition(problem2c, 3, 'e', 4);
    NFA_add_transition_all(problem2c, 4, 4);
    NFA_set_accepting(problem2c, 4, true);


    while (1) {
        NFA_set_current_state(problem2c, 0);
        char *input = malloc(64*sizeof(char));
        printf("Test: ");
        scanf("%s", input);

        if (strncmp(input, "quit", 4) == 0) {
            printf("Quitting Problem 2a\n");
            break;
        }

        int test = NFA_execute(problem2c, input);
        if (test == 0) {
            printf("%s is not accepted\n", input);
        }
        if (test == 1) {
            printf("%s is accepted\n", input);
        }
    }
    printf("\n");

}

int main(int argc, char* argv[]) {
    problem_2_a();
    problem_2_b();
    problem_2_c();



}

#endif
