#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashmap.h"

/**
 * Implementation of a { char * -> char * } hash map in vanilla C.
 * Handles collisions via chaining, as well as automatic resizing.
 *
 * @author ryangant
 * @date 2012-03-22
 */

#define RESIZE_THRESHOLD 0.80
#define SCALING_FACTOR 2
 
void resize( HashMap *map, int capacity ) {
    HashMap *newMap = createMap( map->size, capacity );
    int i;
    for( i = 0; i < map->capacity; i++ ) {
        Node *current = map->entries[i];
        while( current != NULL ) {
            put( newMap, current->entry.key, current->entry.value );
            current = current->next;
        }
    }
	*map = *newMap;
}

HashMap *new() {
	return createMap( 0, INITIAL_CAPACITY );
}

HashMap *createMap( int size, int capacity ) {
	HashMap *map = malloc( sizeof( HashMap ) );
	int i;
	if( !map ) {
		printf("Could not allocate memory for new HashMap!");
		exit(1);
	}
	map->size = size;
	map->capacity = capacity;
    map->entries = malloc( sizeof( Node ) * capacity );
	for( i = 0; i < capacity; i++ ) {
		map->entries[i] = NULL;
	}
	return map;
}

void put( HashMap *map, key_t key, val_t value ) {
	if( (float)( map->size + 1 ) / map->capacity > RESIZE_THRESHOLD ) {
		resize( map, map->capacity * SCALING_FACTOR );
	}
    Entry *entry = malloc( sizeof( Entry ) );
    entry->key = key;
    entry->value = value;
    
    Node *new = malloc( sizeof( Node ) );
    new->entry = *entry;
    new->next = NULL;
    
    int i = hash( map, key );
    if( map->entries[i] == NULL ) {
        map->entries[i] = new;
    } else { 
        Node *collision = map->entries[i];
        while( collision->next != NULL ) {
            collision = collision->next;
        }
        collision->next = new;
    }
	map->size++;
}

char *get( HashMap *map, key_t key ) {
	int h = hash( map, key );
	if( map->entries[ h ] != NULL ) {
        Node *current = map->entries[h];
        while( current->next != NULL && current->entry.key != key ) {
            current = current->next;
        }
		return current->entry.value;
	}
	return NULL;
}

void delete( HashMap *map, key_t key ) {
	int h = hash( map, key );
	map->entries[h] = NULL;
}

int hash( HashMap *map, key_t key ) {
	int total = 0, i;
	for( i = 0; i < sizeof( key ); i++ ) {
		total += (int)(key + i)[0];
	}
	return total % map->capacity;
}