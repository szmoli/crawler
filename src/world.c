#include "world.h"

// Tile map
const char tile_chars[5] = {
    'p', // player
    'e', // enemy
    'w', // wall
    'c', // chest
    ' '  // nothing
};

void init_world(world_t *world) {
    for (int i = 0; i < WORLD_HEIGHT * WORLD_WIDTH; ++i) {
        vector2_t pos = get_world_pos(i);

        if (pos.y % 3 == 0) {
            set_tile_at(world, pos, WALL);
        } 
        else {
            set_tile_at(world, pos, NOTHING);
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

void set_tile_at(world_t* world, const vector2_t pos, const tile_t new_tile) {
    world->tiles[get_tile_index(pos)] = new_tile;
}

char get_tile_char(const char tile_chars[], const tile_t tile) {
    return tile_chars[tile];
}