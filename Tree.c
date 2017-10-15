#define FAILED NULL
#include "stdio.h"
#include "stdlib.h"
#include "Tree.h"

typedef struct NODE *TREE;
struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};

TREE parseTree;
char *nextTerminal;

TREE makeNode0(char x){
    TREE root;
    root = (TREE)malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}
TREE makeNode1(char x, TREE t){
    TREE root;
    root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4){
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = t4;
    return root;
}

TREE B(){
    TREE firstB, secondB;
    if(*nextTerminal == '('){
        nextTerminal++;
        firstB = B();
        if(firstB != FAILED && *nextTerminal == ')'){
            nextTerminal++;
            secondB = B();
            if(secondB == FAILED){
                return FAILED;
            } else{
            return makeNode4('B', makeNode0('('), firstB, makeNode0(')'), secondB);
            }
        } else{
            return FAILED;
        }
    }else{
        return makeNode1('B', makeNode0('e'));
    }

}

int main(){
    nextTerminal = "()()";
    parseTree = B();
    return 0;
}