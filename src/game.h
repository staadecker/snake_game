#include <stdint.h>
#include "game_structure.h"

/*
* Function: create_game
* ---------------------
* Creates a game object ready to play.
* Returns NULL if no memory could be allocated.
* 
* 1. Calls srand() using time(0) to ensure proper random number generation.
* 2. Initializes the GameState
* 3. Creates a snake of length two at spaces 0 and 1.
* 4. Places a target
*/
GameState* create_game(uint8_t width, uint8_t height);

/*
 * Function: free_game
 * ----------------------
 * Free's the gameState pointer.
 */
void free_game(GameState* gameState);

/*
* Function: place_new_target
* ---------------------------
* Adds a target to the board where the snake isn't. Overwrites the previous target.
* Returns 0 (false) if there's no empty cells.
* 1. Find number of empty cells using snakes length
* 2. Randomely pick an empty cell.
* 3. Iterate through the cells until the nth empty cell.
* 4. Place target at such cell.
*/
char place_new_target(GameState* gameState);

/*
* Function: get_snake_length
* --------------------------
* Returns the length of the snake using the number of points accumulated and knowing that the starting length is 2.
*/
uint16_t get_snake_length(GameState* gameState);

/*
* Function: get_random_int
* --------------------------
* Returns a random integer greater or equal to zero and smaller than max.
*/
uint16_t get_random_int(uint16_t max);