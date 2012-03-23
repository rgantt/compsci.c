#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashmap.h"

/**
 * Implementation of a { char * -> char * } hash map in vanilla C.
 * Does not handle key collisions!
 *
 * @author ryangant
 * @date 2012-03-22
 */

#define RESIZE_THRESHOLD 0.80
#define SCALING_FACTOR 2
 
HashMap resize( HashMap *map, int capacity ) {
	printf("Should have resized here!\n");
	return *map;
}

HashMap *new() {
	HashMap *map = (HashMap *) malloc( sizeof( HashMap ) );
	int i;
	if( !map ) {
		printf("Could not allocate memory for new HashMap!");
		return NULL;
	}
	map->size = 0;
	map->capacity = INITIAL_CAPACITY;
	for( i = 0; i < INITIAL_CAPACITY; i++ ) {
		map->entries[i] = NULL;
	}
	return map;
}

void put( HashMap *map, key_t key, val_t value ) {
	if( (float)( map->size + 1 ) / map->capacity > RESIZE_THRESHOLD ) {
		resize( map, map->capacity * SCALING_FACTOR );
	}
	int h = hash( map, key );
	Entry *entry = (Entry *) malloc( sizeof( Entry ) );
	// i don't like these assignments
	entry->key = key;
	entry->value = value;
	map->entries[ h ] = entry;
	map->size++;
}

char *get( HashMap *map, key_t key ) {
	int h = hash( map, key );
	if( map->entries[ h ] != NULL ) {
		return map->entries[ h ]->value;
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