#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suite.h"

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
	char *preface = ( NULL != description ) ? description : "Assertion";
	if( 0 != strcmp( expected, actual ) ) {
		printf("[FAIL] %s\nExpected: <%s>, but was <%s>\n", preface, expected, actual );
		suite.tests_failed++;
	}
	suite.tests_run++;
}