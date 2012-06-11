#ifndef IQUEUE
#define IQUEUE

#define QUEUE_STACK 1

#include "stack.h"

typedef char* element;

typedef struct {
    stack *elements;
    stack *tmp;
} queue;

queue *new_queue();
void destroy_queue( queue * );
void enqueue( queue *, element );
element dequeue( queue * );

#endif
