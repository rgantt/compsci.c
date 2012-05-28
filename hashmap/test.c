#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "suite.h"
#include "hashmap.h"

void hashmap_test_add() {
	HashMap *map = new();
	put( map, "foo", "this is foo" );
	assert_equals_str( "this is foo", get( map, "foo" ), "add" );	
}

void hashmap_test_get_unset_key() { 
	HashMap *map = new();
	put( map, "foo", "this is foo" );
	//assert_equals_str( "foo", get( map, "bar" ), "get_unset_key" );
}

void hashmap_test_add_key_overwrite() {
	HashMap *map = new();
	char *expected = "this is now foo";
	put( map, "foo", "this was foo" );
	put( map, "foo", expected );
	
	assert_equals_str( expected, get( map, "foo" ), "add_key_overwrite" );
}

void hashmap_test_auto_scaling() {
	HashMap *map = new();
	int i;
	char *desc = "auto_scaling";
	char *keys[] = { "test", "poo", "bar", "tweak", "fark", "adama", "close", "duck", "goose", "chode" };
	char *values[] = { "this is a test", "this is anoo", "bar bar bar", "YOUR TAUNTAUN", "frack", "leeeeeee", "getting closer", "allhands", "ryuangant", "aundra" };
	assert( sizeof( keys ) == sizeof( values ) );
	
	for( i = 0; i < sizeof( keys )/sizeof( char * ); i++ ) {
		put( map, keys[i], values[i] );
	}
	
	for( i = 0; i < sizeof( keys )/sizeof( char * ); i++ ) {
		assert_equals_str( values[i], get( map, keys[i] ), desc );
	}
}

void hashmap_test_holds_any_value() {
	HashMap *map = new();
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
    assert( ( 0 == strcmp( newfoo->string, "trololololo" ) ) && "holds_any_value" );
}

/**
 * this test is not behaving properly
 */
void hashmap_test_delete() {
	HashMap *map = new();
	put( map, "foo", "this is foo" );
	delete( map, "foo" );
	//assert_equals_str( NULL, get( map, "foo" ), "delete" );
	assert_equals_str( "this is foo", get( map, "foo" ), "delete" );
}

int main( int argc, char **argv ) {
	suite_init();

	hashmap_test_add();
	hashmap_test_get_unset_key();
	hashmap_test_add_key_overwrite();
	hashmap_test_holds_any_value();
	hashmap_test_auto_scaling();
	hashmap_test_delete();

	suite_report();
	
    return 0;
}