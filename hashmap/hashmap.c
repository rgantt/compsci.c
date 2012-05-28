#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashmap.h"

/**
 * Implementation of a { char * => char * } hash map in C.
 * Handles collisions via chaining, as well as automatic resizing.
 *
 * Things would be simpler if I spent more time working with a List API
 *
 * @author ryangant
 * @date 2012-03-22
 */

#define RESIZE_THRESHOLD 0.80
#define SCALING_FACTOR 2

/**
 * Replace a HashMap pointer with a newly-created HashMap containing all of the original elements but with "capacity"
 * indices in the internal array
 */
void resize( HashMap *map, int capacity ) {
    HashMap *newMap = createMap( map->size, capacity );
    Node *current;
    int i;
    // we know how many elements are in the internal array; move through all of them
    for( i = 0; i < map->capacity; i++ ) {
        // move through the lists at each index and put them into the newly-allocated map
        for( current = map->entries[i]; current != NULL; current = current->next ) {
            put( newMap, current->entry.key, current->entry.value );
        }
    }
    // replace our original map pointer with a pointer to the address of the bigger map
    *map = *newMap;
}

/**
 * Creates a new HashMap with no elements and the default initial capacity
 */
HashMap *new() {
    // just create a new map with 0 elements and a well-defined size
    return createMap( 0, INITIAL_CAPACITY );
}

/**
 * Allocates 
 */
HashMap *createMap( int size, int capacity ) {
    // allocate the new memory for a hashmap
    HashMap *map = malloc( sizeof( HashMap ) );
    if( !map ) {
        printf("Could not allocate memory for new HashMap!");
        exit(1);
    }
    int i;
    map->size = size;
    map->capacity = capacity;
    map->entries = malloc( sizeof( Node ) * capacity );
    if( !map->entries ) {
        printf("Could not allocate memory for new Node entries!");
        exit(1);
    }
    // move through the newly-allocated memory and null out the values; start fresh
    for( i = 0; i < capacity; i++ ) {
        map->entries[i] = NULL;
    }
    return map;
}

/**
 * Places an entry object at a particular key. Handles situations where there are key collisions
 * caused by inefficient hashing. Also handles key overwrite situations.
 */
void put( HashMap *map, key_t key, val_t value ) {
    // determine whether our load factor is high enough to justify resizing
    if( (float)( map->size + 1 ) / map->capacity > RESIZE_THRESHOLD ) {
        resize( map, map->capacity * SCALING_FACTOR );
    }
    Entry *entry = malloc( sizeof( Entry ) );
    if( !entry ) {
        printf("Could not allocate memory for new Entry!");
        exit(1);
    }
    
    Node *new = malloc( sizeof( Node ) ), *collision;
    if( !new ) {
        printf("Could not allocate memory for new Node!");
        exit(1);
    }

    entry->key = key;
    entry->value = value;
    new->entry = *entry;
    new->next = NULL;

    int i = hash( map, key );
	// if there isn't a list at this index yet, start one
    if( map->entries[i] == NULL ) {
        map->entries[i] = new;
    } else { 
        // move through the list--if we find a list entry whose key is the same as the new entry, 
		// replace it. otherwise, add the new node to the end of the list
		collision = map->entries[i];
		do {
			// if the keys are the same, replace the entry objects
			if( strcmp( collision->entry.key, key ) == 0 ) {
				collision->entry = *entry;
				// we've made our replacement, no sense continuing along the list
				return;
			}
		} while( ( collision->next != NULL ) && ( collision = collision->next ) );
		collision->next = new;
    }
}

/**
 * Returns the value at key key_t
 */
void *get( HashMap *map, key_t key ) {
    Node *current;
    int h = hash( map, key );
    if( map->entries[h] != NULL ) {
        // finding a value at the hashed index isn't enough; we need to move through the list and match keys
		// current implementation simply returns the first entry whose key is the same as the key_t key
        for( current = map->entries[h]; current->next != NULL && strcmp( current->entry.key, key ) != 0; current = current->next );
		if( strcmp( current->entry.key, key ) == 0 ) {
			return current->entry.value;
		}
    }
    return NULL;
}

/**
 * This is awful, and doesn't take into account the fact that we are chaining
 */
void delete( HashMap *map, key_t key ) {
    int h = hash( map, key );
	Node *current, *previous;
	current = map->entries[h];
	// if the list is only one element, just clear out the array index
	if( current->next == NULL ) {
		map->entries[h] = NULL;
		free( current );
		return;
	}
	previous = current;
	current = current->next;
	// if there is a multi-element list, keep a pointer to the previous element so we can
	// easily update the pointers to remove the deleted one
	do {
		if( strcmp( current->entry.key, key ) == 0 ) {
			Node *tmp = current;
			previous->next = current->next;
			free( tmp );
		}
	} while( ( current->next != NULL ) && ( current = current->next ) );
}

/**
 * Compute an integer hash of the key provided and then return its modulus w.r.t. the size of the internal array
 */
int hash( HashMap *map, key_t key ) {
    int total = 0, i;
    for( i = 0; i < sizeof( key ); i++ ) {
        total += (int)(key + i)[0];
    }
    return total % map->capacity;
}

/**
 * Print out a nice-looking representation of a given hashmap. Shows the structure of the internal
 * array, as well as the structure of the linked list that each index holds.
 */
void pretty_print( HashMap *map ) {
	int i;
	Node *entry;
	for( i = 0; i < map->capacity; i++ ) {
		printf( "entries[%d]:\n", i );
		entry = map->entries[i];
		if( entry == NULL ) continue;
		do {
			printf( "\t%s => %s\n", entry->entry.key, (char *) entry->entry.value );
		} while( ( entry->next != NULL ) && ( entry = entry->next ) );
	}
}