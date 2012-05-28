#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

/**
 * Creates a new stack whose size is equal to the value of INITIAL_CAPACITY
 */
stack *new_stack() {
	return create_stack( INITIAL_CAPACITY );
}

/**
 * Handles all of the memory allocation and address initialization required for a new stack
 * of a given capacity
 */
stack *create_stack( const int capacity ) {
	int i;
	stack *s = malloc( sizeof( stack ) );
	if( !s ) {
		printf("Could not allocate memory for new stack!");
		exit(1);
	}
	s->capacity = capacity;
	s->top = -1;
	s->elements = malloc( sizeof( element ) * capacity );
	if( !s->elements ) {
		printf("Could not allocate memory for stack elements!");
		exit(1);
	}
	for( i = 0; i < capacity; i++ ) {
		s->elements[i] = NULL;
	}
	return s;
}

/**
 * Resizes the stack by creating a new stack whose size is double the original stack size using
 * only stack operations and a temporary stack
 */
void resize( stack *s, const int capacity ) {
	stack *new_stack = create_stack( capacity );
	new_stack->top = s->top;
	stack *tmp_stack = create_stack( s->capacity );
	element e;
	// pop from original stack, push onto tmp. pop from tmp, push onto new, larger stack
	while( ( e = pop(s) ) != NULL ) {
		push( tmp_stack, e );
	}
	while( ( e = pop(tmp_stack) ) != NULL ) {
		push( new_stack, e );
	}
	*s = *new_stack;
}

/**
 * Returns 1 if the index pointer is less than 0 (not pointing to anything)
 */
int empty( const stack *s ) {
	return ( s->top < 0 );
}

/**
 * Pushes an element onto the top of the stack and updates the index pointer
 */
void push( stack *s, element e ) {
	if( ++s->top > s->capacity ) {
		resize( s, s->capacity * SCALING_FACTOR );
	}
	s->elements[s->top] = e;
}

/**
 * Removes the top element from the stack, returns it, and updates the index pointer
 */
element pop( stack *s ) {
	return empty(s) ? NULL : s->elements[s->top--];
}

/**
 * Gives a preview of the topmost element by popping it, saving it, and pushing it back on
 */
element peek( stack *s ) {
	element e = pop(s);
	push( s, e );
	return e;
}

/**
 * Prints out the underlying array housing the stack, as well as the index of the top pointer
 */
void pretty_print( const stack *s ) {
	int i;
	printf("top index: %d\n", s->top);
	for( i = 0; i < s->capacity; i++ ) {
		printf("s[%d]: %s\n", i, s->elements[i] );
	}
}