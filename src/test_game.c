#include "game.h"
#include "minunit.h"
#include <stdio.h>

int tests_run = 0;

static char* test_get_random_int() {
	int times_at_zero = 0;
	for (int i = 0; i < 1000; i++) {
		mu_assert("Random int incorrect (1)", get_random_int(1) == 0);
		uint16_t random_int = get_random_int(2);
		mu_assert("Random int incorrect (2)", random_int == 0 || random_int == 1);
		if (random_int == 0) {
			times_at_zero++;
		}
	}

	printf("INFO: Random integer function split between 0 and 1 at %d%% and %d%%. \n", times_at_zero/10, 100 - times_at_zero/10);

	return 0;
}

static char* test_create() {
	GameState* gameState = create_game(2,2);

	mu_assert("Could not create object properly (1)", gameState->cells[0] == 1);
	mu_assert("Could not create object properly (2)", gameState->cells[1] == 2);
	mu_assert("Could not create object properly (3)", gameState->constants != NULL);
	mu_assert("Could not create object properly (4)", gameState->frame == 0);
	mu_assert("Could not create object properly (5)", gameState->points == 0);
	mu_assert("Could not create object properly (6)", gameState->target == 2 || gameState->target == 3);
	mu_assert("Could not create object properly (7)", gameState->head == 1);
	mu_assert("Could not create object properly (8)", gameState->tail == 0);

	free_game(gameState);

	gameState = create_game(2, 1);
	mu_assert("Did not return null during create_game", gameState == NULL);

	gameState = create_game(1, 10);
	mu_assert("Did not return null during create_game", gameState == NULL);

	return 0;
}

static char* all_tests() {
	mu_run_test(test_create);
	mu_run_test(test_get_random_int);
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