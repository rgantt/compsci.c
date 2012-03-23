#include <stdio.h>
#include "hashmap.h"

int main( int argc, char **argv ) {
	HashMap *map = new();
	put( map, "test", "this is a test" );
	put( map, "foo", "this is a foo" );
	put( map, "bar", "bar bar bar" );
	put( map, "tweak", "YOUR TAUNTAUN" );
	put( map, "fark", "frack" );
	put( map, "adama", "leeeeeee" );
	put( map, "close", "getting closer" );
	put( map, "duck", "allhands" );
	put( map, "goose", "ryuangant" );
	put( map, "chode", "aundra" );
	
	printf( "test: %s\n", get( map, "test" ) );
	printf( "foo: %s\n", get( map, "foo" ) );
	printf( "bar: %s\n", get( map, "bar" ) );
	printf( "tweak: %s\n", get( map, "tweak" ) );
	printf( "fark: %s\n", get( map, "fark" ) );
	printf( "adama: %s\n", get( map, "adama" ) );
	printf( "close: %s\n", get( map, "close" ) );
	
	delete( map, "test" );
	
	printf( "test: %s\n", get( map, "test" ) );
	
	return 0;
}