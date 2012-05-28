#ifndef TESTSUITE
#define TESTSUITE

struct {
	int tests_run;
	int tests_failed;
} suite;

void suite_init();
void suite_report();
void assert_equality( int (*)( void *, void * ), void *, void *, char * );
void assert_equals_str( char *, char *, char * );
void assert_equals( void *, void *, char * );

#endif