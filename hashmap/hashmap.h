#ifndef IHASHMAP
#define IHASHMAP

#define INITIAL_CAPACITY 10

typedef char *hashmap_key_t;
// values can be of arbitrary type; char * most commonly
typedef void *hashmap_val_t;

typedef struct { 
    hashmap_key_t key;
    hashmap_val_t value;
} entry; 

typedef struct node {
    entry *entry;
    struct node *next;
} node;

typedef struct {
    int size;
    int capacity;
    node **entries;
} hashmap;

hashmap *new_hashmap( void );
hashmap *create_hashmap( int, int );
void destroy_hashmap( hashmap * );
void put( hashmap *, hashmap_key_t, hashmap_val_t );
void *get( hashmap *, hashmap_key_t );
void delete( hashmap *, hashmap_key_t );
hashmap *resize( hashmap *, int );
int hash( hashmap *, hashmap_key_t );
void pretty_print( hashmap * );

#endif
