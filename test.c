#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

int main( int argc, char **argv ) {
    HashMap *map = new();
    
    // Make an arbitrarily typed blob
    typedef struct blob {
        int i;
        int j;
        char* string;
        char* anotherString;
    } blob;
    blob *foo = malloc( sizeof(blob) );

    // Give it some data so we can make sure we've still got it
    foo->i = 99;
    foo->j = 253087;
    foo->string = "trololololo";
    foo->anotherString = "yeyeyeyeye";

    // Check it's working
    printf(foo->string);

    put( map, "foo", foo );
    
    // Get the thing we've stored in foo and cast it to blob* type
    blob *newfoo = (blob*) get(map, "foo");
    printf( "foo: %s\n", newfoo->anotherString );
    
    put( map, "test", "this is a test" );
    printf( "test: %s\n", (char *) get( map, "test" ) );
    put( map, "foo", "this is a foo" );
    put( map, "bar", "bar bar bar" );
    put( map, "tweak", "YOUR TAUNTAUN" );
    put( map, "fark", "frack" );
    put( map, "adama", "leeeeeee" );
    put( map, "close", "getting closer" );
    put( map, "duck", "allhands" );
    put( map, "goose", "ryuangant" );
    put( map, "chode", "aundra" );
    put( map, "moar", "moooaaarr" );

    printf("\nafter potential resizing:\n\n");

    printf( "test: %s\n", get( map, "test" ) );
    printf( "foo: %s\n", get( map, "foo" ) );
    printf( "bar: %s\n", get( map, "bar" ) );
    printf( "tweak: %s\n", get( map, "tweak" ) );
    printf( "fark: %s\n", get( map, "fark" ) );
    printf( "adama: %s\n", get( map, "adama" ) );
    printf( "close: %s\n", get( map, "close" ) );
    printf( "duck: %s\n", get( map, "duck" ) );
    printf( "goose: %s\n", get( map, "goose" ) );
    printf( "chode: %s\n", get( map, "chode" ) );

    delete( map, "test" );

    printf( "test: %s\n", get( map, "test" ) );

    return 0;
}