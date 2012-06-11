#ifndef IQUEUE
#define IQUEUE

#define QUEUE_STACK 0
#define INITIAL_CAPACITY 5
#define SCALING_FACTOR 2

typedef char* element;

/**
 * this is implementation-specific
 */
typedef struct {
    int capacity;
    int count;
    int head;
    int tail;
    element* elements;
} queue;

/**
 * "public" api
 */
queue *new_queue();
void destroy_queue( queue * );
void enqueue( queue *, element );
element dequeue( queue * );

/**
 * "private"/implementation-specific api
 */
queue *resize( queue *, const int );
queue *create_queue( const int );

#endif
