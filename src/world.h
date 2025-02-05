#ifndef WORLD_H
#define WORLD_H

#define WORLD_WIDTH 200
#define WORLD_HEIGHT 90

#include "math.h"

// Possible tile types
typedef enum {
    PLAYER,
    ENEMY,
    WALL,
    CHEST,
    NOTHING
} tile_t;

// Tile map declaration
extern const char tile_chars[5];

typedef struct {
    tile_t tiles[WORLD_WIDTH * WORLD_HEIGHT];
} world_t;

// Function declarations
void init_world(world_t *world);
int get_tile_index(const vector2_t pos);
void set_tile_at(world_t* world, const vector2_t pos, const tile_t new_tile);
vector2_t get_world_pos(int num);
char get_tile_char(const char tile_chars[], const tile_t tile_type);

#endif