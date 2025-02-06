#include "world.h"

// Tile map
const char world_tilemap[WORLD_NOTHING + 1] = {
    'w', // wall
    'c', // chest
    '#', // off bounds
    ' '  // nothing
};

void init_world(world_t *world) {
    for (int i = 0; i < WORLD_HEIGHT * WORLD_WIDTH; ++i) {
        vector2_t pos = get_world_pos(i);

        if (pos.y % 2 == 1 && pos.x % 2 == 1) {
            set_tile_at(world, pos, WALL);
        } 
        else {
            set_tile_at(world, pos, WORLD_NOTHING);
        }
    }
}

vector2_t get_world_pos(int num) {
    vector2_t pos = { 
        .x = num % WORLD_WIDTH,
        .y = num / WORLD_WIDTH
    };

    return pos;
}

int get_tile_index(const vector2_t pos) {
    return pos.y * WORLD_WIDTH + pos.x;
}

void set_tile_at(world_t *world, const vector2_t pos, const tile_t new_tile) {
    world->tiles[get_tile_index(pos)] = new_tile;
}

char get_world_tile_char(const char world_tilemap[], const tile_t tile) {
    return world_tilemap[tile];
}

tile_t get_tile_at(const world_t *world, const vector2_t pos) {
    return world->tiles[get_tile_index(pos)];
}