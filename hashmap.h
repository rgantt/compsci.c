#ifndef IHASHMAP
#define IHASHMAP

#define INITIAL_CAPACITY 10

typedef char *key_t;
typedef char *val_t;

typedef struct { 
	key_t key;
	val_t value;
} Entry; 
 
typedef struct {
	int size;
	int capacity;
	Entry *entries[ INITIAL_CAPACITY ];
} HashMap;

HashMap *new();
void put( HashMap *map, key_t key, val_t value );
char *get( HashMap *map, key_t key );
void delete( HashMap *map, key_t key );
HashMap resize( HashMap *map, int capacity );
int hash( HashMap *map, key_t key );

#endif