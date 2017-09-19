#ifndef _dfa_h
#define _dfa_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dfa.h"
#include <string.h>

typedef struct {
    int transition[128];
    bool isAccepting;

}STATES;

typedef struct {
    int numOfStates;
    int currentState;
    STATES* stateArray;
}DFA;



/**
 * Allocate and return a new DFA containing the given number of states.
 */
extern DFA* DFA_new(int nstates){
    DFA *dfa = (DFA*)malloc(sizeof(DFA));
    dfa->numOfStates = nstates;
    dfa->currentState = 0;
    dfa->stateArray = (STATES *)malloc(nstates*sizeof(STATES));
    for (int i = 0; i < nstates; i++) {
        dfa->stateArray[i].isAccepting = false;
    }
    for (int i = 0; i < nstates; i++) {
        for (int j = 0; j < 128; j++) {
            dfa->stateArray[i].transition[j] = -1;
        }
    }
    return dfa;
}

/**
 * Free the given DFA.
 */
extern void DFA_free(DFA* dfa){
    free(dfa->stateArray);
    free(dfa);
};

/**
 * Return the number of states in the given DFA.
 */
extern int DFA_get_size(DFA* dfa){
    return dfa->numOfStates;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
extern int DFA_get_transition(DFA* dfa, int src, char sym){
    return dfa->stateArray[src].transition[sym];
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
extern void DFA_set_transition(DFA* dfa, int src, char sym, int dst){
    dfa->stateArray[src].transition[sym] = dst;
}

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
extern void DFA_set_transition_str(DFA* dfa, int src, char *str, int dst){
    for (int i = 0; str[i] != '\0'; i++) {
        dfa->stateArray[src].transition[str[i]] = dst;
    }
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
extern void DFA_set_transition_all(DFA* dfa, int src, int dst){
    for (int i = 0; i < 128; i++) {
        dfa->stateArray[src].transition[i] = dst;
    }
}

extern void DFA_set_transition_exception(DFA* dfa, int src, int dst, char* exc) {
    for (int i = 0; i < 128; i++) {
        dfa->stateArray[src].transition[i] = dst;
    }
    for (int i = 0; exc[i] != '\0'; i++) {
        dfa->stateArray[src].transition[exc[i]] = -1;
    }
}

/**
 * Set whether the given DFA's state is accepting or not.
 */
extern void DFA_set_accepting(DFA* dfa, int state, bool value){
    dfa->stateArray[state].isAccepting = value;
}

/**
 * Return true if the given DFA's state is an accepting state.
 */
extern bool DFA_get_accepting(DFA* dfa, int state){
    return dfa->stateArray[state].isAccepting;
}

void DFA_set_current_state(DFA *dfa, int statenum) {
    dfa->currentState = statenum;
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
extern bool DFA_execute(DFA* dfa, char *input){
    for (int i = 0; input[i] != '\0'; i++) {
        int dst = dfa->stateArray[dfa->currentState].transition[input[i]];
        DFA_set_current_state(dfa, dst);
        if (dfa->currentState == -1) {
            return false;
        }
    }
    int final = dfa->currentState;
    return DFA_get_accepting(dfa, final);
}


/**
 * Print the given DFA to System.out.
 */
extern void DFA_print(DFA* dfa){
    for(int i = 0; i < dfa->numOfStates; i++){
        printf("{%d , %d", )
    }
}
extern void problem_1_a() {
    printf("Problem 1a (Only the string ab)--------------------------------------------\n");
    printf("Only accepts 64 characters\n");
    printf("Enter quit to exit the problem\n");
    DFA* problem1a = DFA_new(3);
    DFA_set_transition(problem1a, 0, 'a', 1);
    DFA_set_transition(problem1a, 1, 'b', 2);
    DFA_set_accepting(problem1a, 2, true);

    while (1) {
        DFA_set_current_state(problem1a, 0);
        char *input = malloc(64*sizeof(char));
        printf("Test: ");
        scanf("%s", input);

        if (strncmp(input, "quit", 4) == 0) {
            printf("Quitting Problem 1a\n");
            break;
        }

        int test = DFA_execute(problem1a, input);
        if (test == 0) {
            printf("%s is not accepted\n", input);
        }
        if (test == 1) {
            printf("%s is accepted\n", input);
        }
    }
    printf("\n");
}

extern void problem_1_b() {
    printf("Problem 1b (Begins with ab)--------------------------------------------\n");
    printf("Only accepts 64 characters\n");
    printf("Enter quit to exit the problem\n");
    DFA* problem1b = DFA_new(3);
    DFA_set_transition(problem1b, 0, 'a', 1);
    DFA_set_transition(problem1b, 1, 'b', 2);
    DFA_set_transition_all(problem1b, 2, 2);
    DFA_set_accepting(problem1b, 2, true);

    while (1) {
        DFA_set_current_state(problem1b, 0);
        char *input = malloc(64*sizeof(char));
        printf("Test: ");
        scanf("%s", input);

        if (strncmp(input, "quit", 4) == 0) {
            printf("Quitting Problem 1b\n");
            break;
        }

        int test = DFA_execute(problem1b, input);
        if (test == 0) {
            printf("%s is not accepted\n", input);
        }
        if (test == 1) {
            printf("%s is accepted\n", input);
        }
    }
    printf("\n");
}

extern void problem_1_c() {
    printf("Problem 1c (Binary Input with Even Number of 1's)--------------------------------------------\n");
    printf("Only accepts 64 characters\n");
    printf("Enter quit to exit the problem\n");
    DFA* problem1c = DFA_new(2);
    DFA_set_transition(problem1c, 0, '0', 0);
    DFA_set_transition(problem1c, 0, '1', 1);
    DFA_set_transition(problem1c, 1, '1', 0);
    DFA_set_transition(problem1c, 1, '0', 1);

    DFA_set_accepting(problem1c, 0, true);

    while (1) {
        DFA_set_current_state(problem1c, 0);
        char *input = malloc(64*sizeof(char));
        printf("Test: ");
        scanf("%s", input);

        if (strncmp(input, "quit", 4) == 0) {
            printf("Quitting Problem 1b\n");
            break;
        }

        int test = DFA_execute(problem1c, input);
        if (test == 0) {
            printf("%s is not accepted\n", input);
        }
        if (test == 1) {
            printf("%s is accepted\n", input);
        }
    }
    printf("\n");
}

extern void problem_1_d(){
    printf("Problem 1d (Binary Input with Even Number of 1's and 0's)--------------------------------------------\n");
    printf("Only accepts 64 characters\n");
    printf("Enter quit to exit the problem\n");
    DFA* problem1d = DFA_new(4);
    DFA_set_transition(problem1d, 0, '0', 1);
    DFA_set_transition(problem1d, 3, '1', 0);
    DFA_set_transition(problem1d, 1, '1', 2);
    DFA_set_transition(problem1d, 2, '0', 3);
    DFA_set_transition(problem1d, 0, '1', 3);
    DFA_set_transition(problem1d, 3, '0', 2);
    DFA_set_transition(problem1d, 2, '1', 1);
    DFA_set_transition(problem1d, 1, '0', 0);

    DFA_set_accepting(problem1d, 0 , true);

    while (1) {
        DFA_set_current_state(problem1d, 0);
        char *input = malloc(64*sizeof(char));
        printf("Test: ");
        scanf("%s", input);

        if (strncmp(input, "quit", 4) == 0) {
            printf("Quitting Problem 1b\n");
            break;
        }

        int test = DFA_execute(problem1d, input);
        if (test == 0) {
            printf("%s is not accepted\n", input);
        }
        if (test == 1) {
            printf("%s is accepted\n", input);
        }
    }
    printf("\n");

}

extern void problem_1_e(){
    printf("Problem 1e (Binary Input with Odd Number of 1's and 0's)--------------------------------------------\n");
    printf("Only accepts 64 characters\n");
    printf("Enter quit to exit the problem\n");

    DFA* problem1e = DFA_new(4);
    DFA_set_transition(problem1e, 0, '0', 1);
    DFA_set_transition(problem1e, 3, '1', 0);
    DFA_set_transition(problem1e, 1, '1', 2);
    DFA_set_transition(problem1e, 2, '0', 3);
    DFA_set_transition(problem1e, 0, '1', 3);
    DFA_set_transition(problem1e, 3, '0', 2);
    DFA_set_transition(problem1e, 2, '1', 1);
    DFA_set_transition(problem1e, 1, '0', 0);

    DFA_set_accepting(problem1e, 2, true);

    while (1) {
        DFA_set_current_state(problem1e, 0);
        char *input = malloc(64*sizeof(char));
        printf("Test: ");
        scanf("%s", input);

        if (strncmp(input, "quit", 4) == 0) {
            printf("Quitting Problem 1e\n");
            break;
        }

        int test = DFA_execute(problem1e, input);
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
    problem_1_a();
    problem_1_b();
    problem_1_c();
    problem_1_d();
    problem_1_e();

}

#endif

