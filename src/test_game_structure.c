#include "minunit.h"
#include <stdio.h>
#include "game_structure.h"
#include <stdlib.h>

int tests_run = 0;

static char* test_is_snake_in_cell_and_find_next_cell() {

	GameConstants constants = { 2,4,8 };
	uint16_t game_state_size = sizeof(GameState) + constants.board_len * sizeof(uint32_t);
	GameState* gameState = malloc(game_state_size);

	if (gameState == NULL) {
		mu_assert("Couldn't create game state", 0);
	}

	memset(gameState, 0, game_state_size);

	gameState->constants = &constants;
	gameState->frame = 3;
	gameState->points = 0;
	gameState->tail = 1;
	gameState->head = 2;
	gameState->cells[0] = 1;
	gameState->cells[1] = 2;
	gameState->cells[2] = 3;
	gameState->travel_direction = RIGHT;
	gameState->target = 6;

	/*
	* Current Board. Frame 3

	-SS-
	--*-

	*/
	
	mu_assert("is_snake_in_cell failed (1)", !is_snake_in_cell(0, gameState));
	mu_assert("is_snake_in_cell failed (2)", is_snake_in_cell(1, gameState));
	mu_assert("is_snake_in_cell failed (3)", is_snake_in_cell(2, gameState));
	mu_assert("is_snake_in_cell failed (4)", !is_snake_in_cell(3, gameState));
	mu_assert("is_snake_in_cell failed (5)", !is_snake_in_cell(6, gameState));
	
	mu_assert("find_next_cell failed (1)", find_next_cell(gameState, 0) == 1);
	mu_assert("find_next_cell failed (2)", find_next_cell(gameState, 1) == 2);
	mu_assert("find_next_cell failed (3)", find_next_cell(gameState, 2) == -1);

	gameState->frame = 4;
	gameState->cells[6] = 4;
	gameState->head = 6;
	gameState->tail = 2;
	gameState->points = 1;
	gameState->target = 4;
	gameState->travel_direction = DOWN;
	
	/*
	* Board state. Frame 4.

	-SS-
	*-S-

	*/

	mu_assert("is_snake_in_cell failed (6)", !is_snake_in_cell(0, gameState));
	mu_assert("is_snake_in_cell failed (7)", is_snake_in_cell(1, gameState));
	mu_assert("is_snake_in_cell failed (8)", is_snake_in_cell(2, gameState));
	mu_assert("is_snake_in_cell failed (9)", !is_snake_in_cell(3, gameState));
	mu_assert("is_snake_in_cell failed (10)", is_snake_in_cell(6, gameState));

	mu_assert("find_next_cell failed (4)", find_next_cell(gameState, 0) == 1);
	mu_assert("find_next_cell failed (5)", find_next_cell(gameState, 1) == 2);
	mu_assert("find_next_cell failed (6)", find_next_cell(gameState, 2) == 6);
	mu_assert("find_next_cell failed (7)", find_next_cell(gameState, 3) == -1);
	mu_assert("find_next_cell failed (8)", find_next_cell(gameState, 6) == -1);


	free(gameState);
}

static char* test_add_move_to_dir() {
	mu_assert("add_move_to_dir() not working (1)", add_move_to_dir(RIGHT, TURN_RIGHT) == DOWN);
	mu_assert("add_move_to_dir() not working (2)", add_move_to_dir(DOWN, TURN_RIGHT) == LEFT);
	mu_assert("add_move_to_dir() not working (3)", add_move_to_dir(LEFT, TURN_RIGHT) == UP);
	mu_assert("add_move_to_dir() not working (4)", add_move_to_dir(UP, TURN_RIGHT) == RIGHT);
	mu_assert("add_move_to_dir() not working (5)", add_move_to_dir(RIGHT, TURN_LEFT) == UP);
	mu_assert("add_move_to_dir() not working (6)", add_move_to_dir(UP, GO_STRAIGHT) == UP);

	return  0;
}

static char* test_get_neighbour_cell() {
	GameConstants constants = { 3, 4, 12 }; // Use a 3 by 4 grid
	/*
	0  1  2  3
	4  5  6  7
	8  9  10 11
	*/

	mu_assert("get_neighbour_cell not working (1)", get_neighbour_cell(4, LEFT, &constants) == -1);
	mu_assert("get_neighbour_cell not working (2)", get_neighbour_cell(0, LEFT, &constants) == -1);
	mu_assert("get_neighbour_cell not working (3)", get_neighbour_cell(8, DOWN, &constants) == -1);
	mu_assert("get_neighbour_cell not working (4)", get_neighbour_cell(11, RIGHT, &constants) == -1);
	mu_assert("get_neighbour_cell not working (5)", get_neighbour_cell(3, RIGHT, &constants) == -1);
	mu_assert("get_neighbour_cell not working (6)", get_neighbour_cell(3, UP, &constants) == -1);


	mu_assert("get_neighbour_cell not working (7)", get_neighbour_cell(11, UP, &constants) == 7);
	mu_assert("get_neighbour_cell not working (8)", get_neighbour_cell(6, DOWN, &constants) == 10);
	mu_assert("get_neighbour_cell not working (9)", get_neighbour_cell(4, RIGHT, &constants) == 5);
	mu_assert("get_neighbour_cell not working (10)", get_neighbour_cell(11, LEFT, &constants) == 10);
}

static char* all_tests() {
	mu_run_test(test_add_move_to_dir);
	mu_run_test(test_get_neighbour_cell);
	mu_run_test(test_is_snake_in_cell_and_find_next_cell);
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