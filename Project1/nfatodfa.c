/*
 * CSC173 Project 1
 * Created By Sailesh Kaveti, Ryan Racicot, Bepen Neupane
 * Net ID: skaveti, rracico3, bneupane
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "nfatodfa.h"
#include "IntSet.h"
#include "LinkedList.h"
#include "nfa.h"
#include "dfa.h"
#include <string.h>

extern DFA_STATES* new_DFA_STATE() {
  DFA_STATES* dfa_state = (DFA_STATES*)malloc(sizeof(DFA_STATES));
  dfa_state->isAccepting = false;
  for (int i = 0; i < 128; i++) {
    dfa_state->transition[i] = -1;
  }
  return dfa_state;
}

extern DFA* nfa_to_dfa(NFA* nfa) {
  IntSet statesSet = IntSet_new();


  //Creates a set of all the states in the new DFA
  for(int i = 0; i < nfa->numOfStates; i++){
    for(int j = 0 j < 128; j++){
      if(IntSet_contains(statesSet, nfa->NFA_STATES[i]->transition[j] != true)){
        IntSet_add(statesSet, nfa->NFA_STATES[i]->transition[j]);
      }
    }
  }

  DFA *dfa = (DFA*)malloc(sizeof(DFA));


}
