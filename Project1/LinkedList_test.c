/*
 * File: LinkedList_test.c
 * Creator: George Ferguson
 * Created: Wed Sep  7 17:59:30 2016
 * Time-stamp: <Fri Aug  4 10:04:36 EDT 2017 ferguson>
 *
 * Test program for LinkedList library.
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int
main(int argc, char **argv) {
    LinkedList *list = LinkedList_new();
    printf("new list =");
    LinkedList_print_string_list(list);

    printf("adding three elements: ");
    LinkedList_add_at_end(list, "foo");
    LinkedList_add_at_end(list, "bar");
    LinkedList_add_at_end(list, "baz");
    LinkedList_print_string_list(list);
    printf("adding Ted at front: ");
    LinkedList_add_at_front(list, "Ted");
    LinkedList_print_string_list(list);

    printf("iterating over list:\n");
    LinkedListIterator *iterator = LinkedList_iterator(list);
    while (LinkedListIterator_has_next(iterator)) {
	void *data = LinkedListIterator_next(iterator);
	char *str = (char*)data;
	printf("%s\n", str);
    }
    free(iterator);

    // Test remove in middle
    printf("removing bar from middle: ");
    LinkedList_remove(list, "bar");
    LinkedList_print_string_list(list);
    // Test remove at head
    printf("removing Ted from start: ");
    LinkedList_remove(list, "Ted");
    LinkedList_print_string_list(list);
    // Test remove in end
    printf("removing baz from end: ");
    LinkedList_remove(list, "baz");
    LinkedList_print_string_list(list);

    // Test remove only element
    void *elt = LinkedList_element_at(list, 0);
    printf("element 0 is \"%s\"\n", (char*)elt);
    printf("removing only remaining element: ");
    LinkedList_remove(list, elt);
    LinkedList_print_string_list(list);

    printf("list is_empty: %d\n", LinkedList_is_empty(list));
}
