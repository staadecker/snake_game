#include "minunit.h"
#include <stdio.h>

int tests_run = 0;

static char* test_foo() {
	//mu_assert("message. test failed because...", expected_test);

	return  0;
}

static char* all_tests() {
	mu_run_test(test_foo);
	return 0;
}

int main() {
	char* result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);

	return result != 0;
}