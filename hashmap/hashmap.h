#ifndef Ihashmap
#define Ihashmap

#define INITIAL_CAPACITY 10

typedef char *key_t;
// values can be of arbitrary type; char * most commonly
typedef void *val_t;

typedef struct { 
    key_t key;
    val_t value;
} entry; 

typedef struct node {
    entry entry;
    struct node *next;
} node;

typedef struct {
    int size;
    int capacity;
    node **entries;
} hashmap;

hashmap *new_hashmap( void );
hashmap *create_hashmap( int, int );
void put( hashmap *, key_t, val_t );
void *get( hashmap *, key_t );
void delete( hashmap *, key_t );
void resize( hashmap *, int );
int hash( hashmap *, key_t );
void pretty_print( hashmap * );

#endif