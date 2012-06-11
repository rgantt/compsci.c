#include <stdlib.h>
#include <stdio.h>
#include "queue-stack.h"

queue *new_queue() {
    queue *new = malloc( sizeof( queue ) );
    stack *elements = new_stack();
    stack *tmp = new_stack();
    new->elements = elements;
    new->tmp = tmp;
    return new;
}

void destroy_queue( queue *q ) {
    destroy_stack( q->elements );
    destroy_stack( q->tmp );
    free(q);
}

// just put the element on the queue as if it were a stack
void enqueue( queue *q, element e ) {
    push( q->elements, e );
}

// blow elements onto tmp, pop, then blow back onto the elements
element dequeue( queue *q ) {
    element e, value;
    while( ( e = pop(q->elements) ) != NULL ) {
        push( q->tmp, e );
    }
    value = pop(q->tmp);
    while( ( e = pop(q->tmp) ) != NULL ) {
        push( q->elements, e );   
    }
    return value;
}
