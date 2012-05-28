#ifndef TESTSUITE
#define TESTSUITE

struct {
	int tests_run;
	int tests_failed;
} suite;

void suite_init();
void suite_report();
void assert_equals_str( char *, char *, char * );

#endif