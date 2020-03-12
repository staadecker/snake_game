#include "game_structure.h"

#define SNAKE_INITIAL_LEN 2 /* Should not be changed since the create function needs this to be 2 */

char add_move_to_dir(char initial_dir, char move) {
	char new_dir = initial_dir + move;
	if (new_dir >= 4) {
		new_dir -= 4;
	}
	if (new_dir < 0) {
		new_dir += 4;
	}

	return new_dir;
}

int16_t get_neighbour_cell(uint16_t cell, char direction, GameConstants* constants) {
	switch (direction) {

	case UP:
		cell -= constants->width;
		
		if (cell < 0) {
			return -1;
		}
		
		break;

	case RIGHT:
		if ((cell + 1) % constants->width == 0) {
			return -1;
		}
		
		cell++;
		break;

	case DOWN:
		cell += constants->width;
		if (cell >= constants->board_len) {
			return -1;
		}

		break;

	case LEFT:
		if (cell % constants->width == 0) {
			return -1;
		}

		cell--;
		break;
	}

	return cell;
}

char is_snake_in_cell(uint16_t cell, GameState* state)
{
	return state->cells[cell] + get_snake_length(state) > state->frame;
}

uint16_t get_snake_length(GameState* gameState)
{
	return gameState->points + SNAKE_INITIAL_LEN;
}

int16_t find_next_cell(GameState* gameState, uint16_t cell)
{
	char current_dir = RIGHT;
	char target_value = gameState->cells[cell] + 1;

	do {
		int16_t neighbour = get_neighbour_cell(cell, current_dir, gameState->constants);
		
		if (neighbour != -1 && gameState->cells[neighbour] == target_value) {
			return neighbour;
		}

		current_dir = add_move_to_dir(current_dir, TURN_RIGHT);
	} while (current_dir != RIGHT);

	return -1;
}
