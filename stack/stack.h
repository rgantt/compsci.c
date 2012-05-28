#ifndef ISTACK
#define ISTACK

#define INITIAL_CAPACITY 5
#define SCALING_FACTOR 2

typedef char* element;

typedef struct {
	int capacity;
	int top;
	element *elements;
} stack;

stack *new_stack();
stack *create_stack( const int );
void resize( stack *, const int );
int empty( const stack * );
void push( stack *, element );
element pop( stack * );
element peek( stack * );
void pretty_print( const stack * );

#endif