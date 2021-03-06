#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suite.h"
#include "hashmap.h"

void hashmap_test_add() {
	hashmap *map = new_hashmap();
	put( map, "foo", "this is foo" );
	assert_equals_str( "this is foo", get( map, "foo" ), "add" );
	destroy_hashmap(map);
}

void hashmap_test_add_hash_collision() {
	hashmap *map = new_hashmap();
	// these two generate the same index
	put( map, "foo", "this is foo" );
	put( map, "poo", "this is poo" );
	assert_equals_str( "this is poo", get( map, "poo" ), "add_hash_collisions" );
	assert_equals_str( "this is foo", get( map, "foo" ), "add_hash_collisions" );
	destroy_hashmap(map);
}

void hashmap_test_add_key_collision() {
	hashmap *map = new_hashmap();
	char *expected = "this is now foo";
	put( map, "foo", "this was foo" );
	put( map, "foo", expected );
	assert_equals_str( expected, get( map, "foo" ), "add_key_overwrite" );
	destroy_hashmap(map);
}

void hashmap_test_get_unset_key() { 
	hashmap *map = new_hashmap();
	put( map, "foo", "this is foo" );
	assert_equals( NULL, get( map, "bar" ), "get_unset_key" );
	destroy_hashmap(map);
}

void hashmap_test_get() {
	hashmap *map = new_hashmap();
	put( map, "foo", "this is foo" );
	assert_equals_str( "this is foo", get( map, "foo" ), "get" );
	destroy_hashmap(map);
}

void hashmap_test_auto_scaling() {
	hashmap *map = new_hashmap();
	int i;
	char *desc = "auto_scaling";
	char *keys[] = { "test", "poo", "bar", "tweak", "fark", "adama", "close", "duck", "goose", "chode" };
	char *values[] = { "this is a test", "this is anoo", "bar bar bar", "YOUR TAUNTAUN", "frack", "leeeeeee", "getting closer", "allhands", "ryuangant", "aundra" };
	
	for( i = 0; i < sizeof( keys )/sizeof( char * ); i++ ) {
		put( map, keys[i], values[i] );
	}
	
	for( i = 0; i < sizeof( keys )/sizeof( char * ); i++ ) {
		assert_equals_str( values[i], get( map, keys[i] ), desc );
	}
	destroy_hashmap(map);
}

void hashmap_test_holds_any_value() {
	hashmap *map = new_hashmap();
	// Make an arbitrarily typed blob
	typedef struct {
		int i;
		int j;
		char* string;
	} blob;
	blob *foo = malloc( sizeof(blob) );

	foo->i = 99;
	foo->j = 253087;
	foo->string = "trololololo";

	put( map, "foo", foo );

	// Get the thing we've stored in foo and cast it to blob* type
	blob *newfoo = (blob*) get(map, "foo");
	assert_equals_str( "trololololo", newfoo->string, "holds_any_value" );
	free(foo);
	destroy_hashmap(map);
}

void hashmap_test_delete() {
	hashmap *map = new_hashmap();
	put( map, "foo", "this is foo" );
	delete( map, "foo" );
	assert_equals( NULL, get( map, "foo" ), "delete" );
	destroy_hashmap(map);
}

void hashmap_test_delete_after_key_collision() {
	hashmap *map = new_hashmap();
	put( map, "foo", "this was foo" );
	put( map, "foo", "this is foo" );
	delete( map, "foo" );
	assert_equals( NULL, get( map, "foo" ), "delete_after_key_collision" );
	destroy_hashmap(map);
}

void hashmap_test_delete_after_hash_collision() {
	hashmap *map = new_hashmap();
	// these both hash to the same value with the current implementation of hash( int, hashmap * )
	put( map, "foo", "this is foo" );
	put( map, "poo", "this is poo" );
	delete( map, "poo" );
	assert_equals( NULL, get( map, "poo" ), "delete_after_hash_collision" );
	destroy_hashmap(map);
}

void hashmap_test_delete_nonexistent_key() {
    hashmap *map = new_hashmap();
    put( map, "foo", "this is foo" );
    delete( map, "bar" );
    // don't really need to assert, just need to avoid segfault
    destroy_hashmap(map);
}

int main( int argc, char **argv ) {
	suite_init();

	hashmap_test_add();
	hashmap_test_add_hash_collision();
	hashmap_test_add_key_collision();
	hashmap_test_get_unset_key();
	hashmap_test_get();
	hashmap_test_auto_scaling();
	hashmap_test_holds_any_value();
	hashmap_test_delete();
	hashmap_test_delete_after_key_collision();
	hashmap_test_delete_after_hash_collision();
	hashmap_test_delete_nonexistent_key();

	suite_report();
	
    return 0;
}
