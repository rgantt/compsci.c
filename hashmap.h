#ifndef IHASHMAP
#define IHASHMAP

#define INITIAL_CAPACITY 10

typedef char *key_t;
typedef char *val_t;

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

HashMap *createMap( int size, int capacity );
HashMap *new();
void put( HashMap *map, key_t key, val_t value );
char *get( HashMap *map, key_t key );
void delete( HashMap *map, key_t key );
void resize( HashMap *map, int capacity );
int hash( HashMap *map, key_t key );

#endif