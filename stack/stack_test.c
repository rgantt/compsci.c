#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suite.h"
#include "stack.h"

void stack_test_push() {
	stack *s = new_stack();
	push( s, "first" );
	assert_equals_str( "first", pop(s), "push" );
	destroy_stack(s);
}

void stack_test_peek_does_not_modify_stack() {
	stack *s = new_stack();
	push( s, "first" );
	peek(s);
	assert_equals_str( "first", pop(s), "peek_does_not_modify_stack" );
	destroy_stack(s);
}

void stack_test_lifo_order_preserved() {
	element elements[] = { "first", "second", "third", "fourth", "fifth" };
	stack *s = new_stack();
	int i;
	for( i = 0; i < sizeof( elements ) / sizeof( element ); i++ ) {
		push( s, elements[i] );
	}
	for( i -= 1; i >= 0; i-- ) {
		assert_equals_str( elements[i], pop(s), "lifo_order_preserved" );
	}
	destroy_stack(s);
}

void stack_test_resizing_does_not_affect_order() {
	// INITIAL_CAPACITY is set to 5; force a resize w/6 elements
	element elements[] = { "1", "2", "3", "4", "5", "6" };
	stack *s = new_stack();
	int i;
	for( i = 0; i < sizeof( elements ) / sizeof( element ); i++ ) {
		push( s, elements[i] );
	}
	for( i -= 1; i >= 0; i-- ) {
		assert_equals_str( elements[i], pop(s), "resizing_does_not_affect_order" );
	}
	destroy_stack(s);
}

int main( int argc, char **argv ) {
	suite_init();

	stack_test_push();
	stack_test_peek_does_not_modify_stack();
	stack_test_lifo_order_preserved();
	stack_test_resizing_does_not_affect_order();

	suite_report();
	
    return 0;
}
