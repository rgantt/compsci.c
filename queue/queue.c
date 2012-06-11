#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue *new_queue() {
	return create_queue( INITIAL_CAPACITY );
}

queue *create_queue( const int capacity ) {
	int i;
	queue *q = malloc( sizeof( queue ) );
	if( !q ) {
		printf("Could not allocate memory for new queue!");
		exit(1);
	}
	q->elements = malloc( sizeof( element ) * capacity );
	if( !q->elements ) {
		printf("Could not allocate memory for queue elements!");
		exit(1);
	}
	q->capacity = capacity;
	q->count = 0;
	q->head = 0;
	q->tail = 0;
	for( i = 0; i < capacity; i++ ) {
		q->elements[i] = NULL;
	}
	return q;
}

void destroy_queue( queue *q ) {
    free(q->elements);
    free(q);
}

queue *resize( queue *q, const int capacity ) {
	queue *new_queue = create_queue( capacity );
	new_queue->head = q->head;
	new_queue->tail = q->tail;
	element e;
	while( ( e = dequeue(q) ) != NULL ) {
		enqueue( new_queue, e );
	}
	destroy_queue(q);
	return new_queue;
}

void enqueue( queue *q, element e ) {
    if( q->count >= q->capacity ) {
        q = resize( q, q->capacity * SCALING_FACTOR );
    }
    q->elements[q->tail] = e;
    if( q->tail == q->capacity ) {
        printf("huckin' a jimmy\n");
        q->tail = 0;
    } else {
        q->tail++;
    }
    q->count++;
}

element dequeue( queue *q ) {
    element e = q->elements[q->head];
    if( q->head == q->capacity ) {
        q->head = 0;
    } else {
        q->head++;
    }
    q->count--;
    return e;
}
