#include "game.h"
#include <stdlib.h>
#include <time.h> 

#define SNAKE_INITIAL_LEN 2 /* Should not be changed since the create function needs this to be 2 */

GameState* create_game(uint8_t width, uint8_t height) {
	// 0. Validate input
	uint16_t board_len = width * height;

	if (width < 2) {
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
	gameState->frame = 0;
	gameState->points = 0;

	// 3. Create snake of length 2
	gameState->tail = 0;
	gameState->head = 1; /* head and tail should be off by 1 */
	gameState->cells[gameState->tail] = 1; /* frame when the head/tail expire */
	gameState->cells[gameState->head] = 2;
	gameState->travel_direction = RIGHT;

	// 4. Place target
	char was_target_placed = place_new_target(gameState);

	if (!was_target_placed) {
		free_game(gameState);
		return NULL;
	}

	// 5. Return game state
	return gameState;
}

void free_game(GameState* gameState){
	free(gameState->constants);
	free(gameState);
}

char place_new_target(GameState* gameState)
{
	// 1. Get number of empty cells using snake length
	uint16_t num_empty_cells = gameState->constants->board_len - get_snake_length(gameState);
	
	if (num_empty_cells == 0) {
		return 0;
	}
	
	// 2. Pick target on empty cell. Should be between 0 (inclusive) and num_empty_cells (exclusive) 
	uint16_t empty_cell_num_target = get_random_int(num_empty_cells) + 1;

	// 3. Find position (index i) of target.
	uint16_t empty_cells_passed = 0;
	for (uint16_t i = 0 ;i < gameState->constants->board_len; i++) {
		if (gameState->cells[i] <= gameState->frame) {
			empty_cells_passed++;

			if (empty_cells_passed == empty_cell_num_target) {
				gameState->target = i;
				return 1;
			}
		}
	}

	return 0;
}

uint16_t get_snake_length(GameState* gameState)
{
	return gameState->points + SNAKE_INITIAL_LEN;
}

uint16_t get_random_int(uint16_t max){
	return (uint16_t)((double)rand() / (double)RAND_MAX * max);
}
