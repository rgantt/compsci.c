#ifndef IQUEUE
#define IQUEUE

#define QUEUE_STACK 1

#include "stack.h"

typedef char* element;

/**
 * this is implementation-specific
 */
typedef struct {
    stack *elements;
    stack *tmp;
} queue;

/**
 * "public" api
 */
queue *new_queue();
void destroy_queue( queue * );
void enqueue( queue *, element );
element dequeue( queue * );

// implementation-specific stuff is mostly handled by stack

#endif
