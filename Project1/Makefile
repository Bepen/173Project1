CC=gcc
CFLAGS= -Wall -Werror
SOURCES=auto.c nfa.c dfa.c IntSet.c
OBJECTS=$(SOURCES: .c=.o)
EXECUTABLE=auto

all: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

auto.o: auto.c
	$(CC) $(CFLAGS) auto.c

nfa.o: nfa.c
	$(CC) $(CFLAGS) nfa.c

dfa.o: dfa.c
	$(CC) $(CFLAGS) dfa.c

IntSet.o: IntSet.c
	$(CC) $(CFLAGS) IntSet.c

clean:
	rm  $(EXECUTABLE)
