#ifndef IHASHMAP
#define IHASHMAP

#define INITIAL_CAPACITY 10

typedef char *key_t;
// values can be of arbitrary type; char * most commonly
typedef void *val_t;

typedef struct { 
    key_t key;
    val_t value;
} Entry; 

typedef struct Node {
    Entry entry;
    struct Node *next;
} Node;

typedef struct {
    int size;
    int capacity;
    Node **entries;
} HashMap;

HashMap *new( void );
HashMap *createMap( int, int );
void put( HashMap *, key_t, val_t );
void *get( HashMap *, key_t );
void delete( HashMap *, key_t );
void resize( HashMap *, int );
int hash( HashMap *, key_t );

#endif