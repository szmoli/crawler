#ifndef WORLD_H
#define WORLD_H

#define WORLD_WIDTH 90
#define WORLD_HEIGHT 90

#include "math.h"

typedef enum {
    PLAYER,
    ENEMY,
    WALL,
    CHEST,
    NOTHING
} tile_type_t;

typedef struct {
    tile_type_t tile_types[WORLD_WIDTH * WORLD_HEIGHT];
} world_t;

#endif