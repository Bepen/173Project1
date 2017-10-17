/*
 * CSC173 Project 1
 * Created By Sailesh Kaveti, Ryan Racicot, Bepen Neupane
 * Net ID: skaveti, rracico3, bneupane
 */

 In order to compile and run the project, navigate to the project directory and type:
  make
To remove exe file, type:
  make clean

Format of output: The program loops through each of the problems until the user types in "quit".
There is a description of each of the problems displayed as well as the input accepted. The DFA and NFA
will print out whether or not the input matches the automata.

The NFA to DFA program cannot compile without returning an error, so we chose not to include it in the make file
because of the restrictions placed by -Wall and -Werror.
The previous year's implementation of the IntSet worked better for out needs. It was found on the link below. That is the only thing we used the github link for.
Our linked list was made using the provided file.

https://github.com/chperkins/Suffer/blob/master/IntSet.c
