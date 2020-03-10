#include <stdint.h>

#define TURN_LEFT -1;
#define STRAIGHT 0;
#define TURN_RIGHT 1;

#define UP 4;
#define RIGHT 0;
#define LEFT 3;
#define DOWN 1;

typedef struct {
	uint16_t width;
	uint16_t height;
	uint16_t board_len;
} GameConstants;

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