/*
 * CSC173 Project 1
 * Created By Sailesh Kaveti, Ryan Racicot, Bepen Neupane
 * Net ID: skaveti, rracico3, bneupane
 */

/*
 * File: dfa.h
 * Creator: George Ferguson
 * Created: Thu Sep  1 17:45:52 2016
 * Time-stamp: <Tue Aug  8 11:30:46 EDT 2017 ferguson>
 */

#ifndef _dfa_h
#define _dfa_h

#include <stdbool.h>

/**
 * The data structure used to represent a deterministic finite automaton.
 * @see FOCS Section 10.2
 * Note that YOU must specify this data structure, although you can hide
 * (encapsulate) its implementation behind the declared API functions and
 * only provide a partial declaration in the header file.
 */
typedef struct DFA *DFA;

/**
 * Allocate and return a new DFA containing the given number of states.
 */
extern DFA DFA_new(int nstates);

/**
 * Free the given DFA.
 */
extern void DFA_free(DFA* dfa);

/**
 * Return the number of states in the given DFA.
 */
extern int DFA_get_size(DFA* dfa);

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
extern int DFA_get_transition(DFA* dfa, int src, char sym);

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
extern void DFA_set_transition(DFA* dfa, int src, char sym, int dst);

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
extern void DFA_set_transition_str(DFA* dfa, int src, char *str, int dst);

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
extern void DFA_set_transition_all(DFA* dfa, int src, int dst);


extern void DFA_set_transition_exception(DFA* dfa, int src, int dst, char* exc);
/**
 * Set whether the given DFA's state is accepting or not.
 */
extern void DFA_set_accepting(DFA* dfa, int state, bool value);

/**
 * Return true if the given DFA's state is an accepting state.
 */
extern bool DFA_get_accepting(DFA* dfa, int state);

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */

extern void problem_1_a();

extern void problem_1_b();

extern void problem_1_c();

extern void problem_1_d();

extern void problem_1_e();

extern void problem_2_a();

//executes the automata
extern bool DFA_execute(DFA* dfa, char *input);

#endif
