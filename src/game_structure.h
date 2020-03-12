#ifndef GAME_STRUCTURE_H
#define GAME_STRUCTURE_H

#include <stdint.h>
#include <stdbool.h>

#define TURN_LEFT -1
#define GO_STRAIGHT 0
#define TURN_RIGHT 1

#define UP 3
#define RIGHT 0
#define LEFT 2
#define DOWN 1

#define COLLISION 0
#define NORMAL_MOVE 1
#define TARGET_EATEN 2
#define END_GAME 3

/*
* Struct: GameConstants
* ---------------------
* Defines the size of the board. Should not be modified throughout the game.
*/
typedef struct {
	uint16_t height;
	uint16_t width;
	uint16_t board_len;
} GameConstants;

/*
* Struct: GameState
* -----------------
* Defines the current state of the game.
*/
typedef struct {
	GameConstants *constants;
	char travel_direction;
	uint16_t tail;
	uint16_t head;
	uint16_t points;
	uint16_t target;
	uint32_t frame;
	uint32_t cells[];
} GameState;

typedef struct {
	char move_result;
} MoveResult;

/*
* Function: add_move_to_dir
* ------------------------
* Returns the new direction after a move. Takes in a direction and move.
*/
char add_move_to_dir(char initial_dir, char move);

/*
* Function: get_neighbour_cell
* ----------------------------
* Returns the index of a neighbouring cell. Returns -1 if the neighbour is off the edge of the board.
*/
int16_t get_neighbour_cell(uint16_t cell, char direction, GameConstants* constants);

/*
* Function: is_snake_in_cell
* ---------------------------
* Returns 0 or 1 (false or true) depending on if the snake is in the cell
* 
* Internal logic:
* Each cell has an int which is the frame where the head of the snake arrived at that frame.
*/
char is_snake_in_cell(uint16_t cell, GameState* state);

/*
* Function: get_snake_length
* --------------------------
* Returns the length of the snake using the number of points accumulated and knowing that the starting length is 2.
*/
uint16_t get_snake_length(GameState* gameState);

/*
* Function: find_next_cell
* -------------------
* Returns the index of the next square of the snake by looking at which neighbouring cell is one greater than the current cell.
* Returns -1 if fails (snake isn't currently one the path).
* Internal logic.
* Gets everyneighbour. If neighbour exists check if neighbour is one greater. If true return true.
*/
int16_t find_next_cell(GameState* gameState, uint16_t cell);

#endif 