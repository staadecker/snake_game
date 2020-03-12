#ifndef GAME_H
#define GAME_H



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
GameState* create_game(uint8_t height, uint8_t width);

/*kk
 * Function: free_game
 * ----------------------
 * Free's the gameState pointer.
 */
void free_game(GameState* gameState);

/*
* Function: place_new_target
* ---------------------------
* Adds a target to the board where the snake isn't. Overwrites the previous target.
* Returns 1 if there's no empty cells and returns 0 on success.
* 1. Find number of empty cells using snakes length
* 2. Randomely pick an empty cell.
* 3. Iterate through the cells until the nth empty cell.
* 4. Place target at such cell.
*/
char place_new_target(GameState* gameState);

/*
* Function: get_random_int
* --------------------------
* Returns a random integer greater or equal to zero and smaller than max.
*/
uint16_t get_random_int(uint16_t max);

/*
* Function: move_snake
* --------------------
* Takes in a move (TURN_LEFT, TURN_RIGHT or GO_STRAIGHT) and then moves the snake.
* 
* Internal logic
* 1. Calculate new direction of snake using add_move_to_dir().
* 2. Determine next cell using get_neighbour_cell() and return if there's a collision with the wall.
* 3. Increment frame
* 4. Check if there's a collision with the snake and return if true
* 5. Update head and tail pointers
* 6. Set next cell to contain frame
* 7. Check if food is eaten.
* 8. If food was eaten increment points and call place_new_target()
*/
MoveResult move_snake(GameState* gameState, char move);

#endif // !GAME_H