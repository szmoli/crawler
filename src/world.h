#ifndef WORLD_H
#define WORLD_H

#define WORLD_WIDTH 200
#define WORLD_HEIGHT 90

#include "math.h"

// Possible tile types
typedef enum {
    WALL,
    CHEST,
    OFF_BOUNDS,
    WORLD_NOTHING
} tile_t;

// Tile map declaration
extern const char world_tilemap[WORLD_NOTHING + 1];

typedef struct {
    tile_t tiles[WORLD_WIDTH * WORLD_HEIGHT];
} world_t;

// Function declarations
void init_world(world_t *world);
int get_tile_index(const vector2_t pos);
void set_tile_at(world_t *world, const vector2_t pos, const tile_t new_tile);
vector2_t get_world_pos(int num);
char get_world_tile_char(const char world_tilemap[], const tile_t tile_type);
tile_t get_tile_at(const world_t *world, const vector2_t pos);

#endif