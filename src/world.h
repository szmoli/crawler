#ifndef WORLD_H
#define WORLD_H

#define WORLD_WIDTH 90
#define WORLD_HEIGHT 90

#include "math.h"

// Possible tile types
typedef enum {
    PLAYER,
    ENEMY,
    WALL,
    CHEST,
    NOTHING
} tile_type_t;

// Tile map declaration
extern const char tile_chars[5];

typedef struct {
    tile_type_t tile_types[WORLD_WIDTH * WORLD_HEIGHT];
} world_t;

// Function declarations
void init_world(world_t *world);
char get_tile_char(const char tile_chars[], const tile_type_t tile_type);

#endif