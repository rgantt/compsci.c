#ifndef IQUEUE
#define IQUEUE

#define INITIAL_CAPACITY 5
#define SCALING_FACTOR 2

typedef char* element;

typedef struct {
    int capacity;
    int count;
    int head;
    int tail;
    element* elements;
} queue;

queue *new_queue();
queue *create_queue( const int );
void destroy_queue( queue * );
queue *resize( queue *, const int );
void enqueue( queue *, element );
element dequeue( queue * );

#endif
