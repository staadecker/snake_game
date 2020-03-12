#include "game.h"
#include "game_structure.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <stddef.h>
#include <stdint.h>

#define START_FRAME 2

GameState* create_game(uint8_t height, uint8_t width) {
	// 0. Validate input
	uint16_t board_len = width * height;

	if (width < 2) { /* Since snake won't fit*/
		return 0;
	}

	// 1. Initialize seed for random function
	srand(time(0));

	// 2. Setup game state
	uint16_t game_state_size = sizeof(GameState) + board_len * sizeof(uint32_t);

	GameConstants* constants = malloc(sizeof(GameConstants));
	GameState* gameState = malloc(game_state_size);

	if (gameState == NULL || constants == NULL) {
		return NULL;
	}

	memset(gameState, 0, game_state_size);

	constants->width = width;
	constants->height = height;
	constants->board_len = board_len;

	gameState->constants = constants;
	gameState->frame = START_FRAME;
	gameState->points = 0;

	// 3. Create snake of length 2
	gameState->tail = 0;
	gameState->head = 1; /* head and tail should be off by 1 */
	gameState->cells[gameState->tail] = START_FRAME - 1; /* frame when the head/tail expire */
	gameState->cells[gameState->head] = START_FRAME;
	gameState->travel_direction = RIGHT;

	// 4. Place target
	char failed = place_new_target(gameState);

	if (failed) {
		free_game(gameState);
		return NULL;
	}

	// 5. Return game state
	return gameState;
}

void free_game(GameState* gameState) {
	free(gameState->constants);
	free(gameState);
}

char place_new_target(GameState* gameState)
{
	// 1. Get number of empty cells using snake length
	uint16_t num_empty_cells = gameState->constants->board_len - get_snake_length(gameState);

	if (num_empty_cells == 0) {
		return 1;
	}

	// 2. Pick target on empty cell. Should be between 0 (inclusive) and num_empty_cells (exclusive) 
	uint16_t empty_cell_num_target = get_random_int(num_empty_cells) + 1;

	// 3. Find position (index i) of target.
	uint16_t empty_cells_passed = 0;
	for (uint16_t i = 0; i < gameState->constants->board_len; i++) {
		if (!is_snake_in_cell(i, gameState)) {
			empty_cells_passed++;

			if (empty_cells_passed == empty_cell_num_target) {
				gameState->target = i;
				return 0;
			}
		}
	}

	return 1;
}



uint16_t get_random_int(uint16_t max) {
	return (uint16_t)((double)rand() / (double)RAND_MAX * max);
}

MoveResult move_snake(GameState* gameState, char move)
{
	gameState->travel_direction = add_move_to_dir(gameState->travel_direction, move);

	uint16_t next_cell = get_neighbour_cell(gameState->head, gameState->travel_direction, gameState->constants);

	if (next_cell == -1) {
		return (MoveResult) { COLLISION };
	}

	gameState->frame++;

	if (is_snake_in_cell(next_cell, gameState)) {
		return (MoveResult) { COLLISION };
	}

	if (gameState->target != next_cell) {
		gameState->tail = find_next_cell(gameState, gameState->tail);
	}
	gameState->head = next_cell;
	gameState->cells[next_cell] = gameState->frame;

	if (gameState->target == gameState->head) {
		gameState->points++;
		if (place_new_target(gameState)) {
			return (MoveResult) { END_GAME };
		}

		return (MoveResult) { TARGET_EATEN };
	}

	return (MoveResult) { NORMAL_MOVE };
}
