#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suite.h"

extern struct suite;

void suite_init() {
	suite.tests_run = 0;
	suite.tests_failed = 0;
}

void suite_report() {
	printf("\n------- RESULTS -------\n");
	printf( "Assertions made: %d\n", suite.tests_run );
	printf( "Passed:\t%d\n", suite.tests_run - suite.tests_failed );
	printf( "Failed:\t%d\n", suite.tests_failed );
	printf("-----------------------\n");
}

void assert_equals_str( char *expected, char *actual, char *description ) {
	assert_equality( strcmp, expected, actual, description );
}

void assert_equals( void *expected, void *actual, char *description ) {
	// create a locally-scoped function that we can use to compare for nulls etc
	int cmp( void *expected, void *actual ) {
		return ( expected == actual ) ? 0 : -1;
	}
	assert_equality( cmp, expected, actual, description );
}

void assert_equality( int (*cmp)( void *, void * ), void *expected, void *actual, char *description ) {
	char *preface = ( NULL != description ) ? description : "Assertion";
	if( cmp( expected, actual ) != 0 ) {
		printf("[FAIL] %s\nExpected: <%s>, but was <%s>\n", preface, (char *) expected, (char *) actual );
		suite.tests_failed++;
	}
	suite.tests_run++;
}