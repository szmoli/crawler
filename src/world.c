#include "world.h"

const char tile_chars[] = {
    'p', // player
    'e', // enemy
    'w', // wall
    'c', // chest
    ' '  // nothing
};

void init_world(world_t world) {
    for (int i = 0; i < WORLD_HEIGHT * WORLD_WIDTH; ++i) {
        vector2_t current_position = { 
            .x = i % WORLD_WIDTH,
            .y = i / WORLD_HEIGHT
        };

        if (current_position.y % 3 == 0) {
            world.tile_types[i] = WALL;
        } 
        else {
            world.tile_types[i] = NOTHING;
        }
    }
}