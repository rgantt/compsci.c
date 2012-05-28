#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

stack *new_stack() {
	return create_stack( INITIAL_CAPACITY );
}

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

void resize( stack *s, int capacity ) {
	stack *new_stack = create_stack( capacity );
	new_stack->top = s->top;
	stack *tmp_stack = create_stack( s->capacity );
	while( peek( s ) != NULL ) {
		push( tmp_stack, pop(s) );
	}
	while( peek( tmp_stack ) != NULL ) {
		push( new_stack, pop( tmp_stack ) );
	}
	*s = *new_stack;
}

int empty( stack *s ) {
	return ( s->top == -1 ) ? 1 : 0;
}

void push( stack *s, element e ) {
	if( ++s->top > s->capacity ) {
		resize( s, s->capacity * SCALING_FACTOR );
	}
	s->elements[s->top] = e;
}

element pop( stack *s ) {
	if( empty( s ) == 0 ) {
		return s->elements[s->top--];
	}
	return NULL;
}

element peek( stack *s ) {
	element e = pop(s);
	push( s, e );
	return e;
}

void pretty_print( stack *s ) {
	int i;
	for( i = 0; i < s->capacity; i++ ) {
		printf("s[%d]: %s\n", i, s->elements[i] );
	}
}