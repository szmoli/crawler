#include "entities.h"

const char entity_tilemap[ENTITY_NOTHING + 1] = {
    'p', // player
    'e', // enemy
    ' '  // nothing
};

void init_entities(entities_t *entities) {
    entities->types[0] = PLAYER;
    entities->healths[0] = 10;
    vector2_t pos = { .x = 0, .y = 0 };
    entities->positions[0] = pos;

    for (int i = 1; i < MAX_ENTITIES; ++i) {
        entities->types[i] = ENTITY_NOTHING;
    }
}

void move_entity(entities_t *entities, int entity_index, const vector2_t new_pos) {
    entities->positions[entity_index] = new_pos;
}

void add_health(entities_t *entities, int entity_index, int hp) {
    entities->healths[entity_index] += hp;
}

char get_entity_tile_char(const entities_t *entities, const char *entity_tilemap, int index) {
    return entity_tilemap[entities->types[index]];
}

vector2_t get_entity_pos(const entities_t *entities, int index) {
    return entities->positions[index];
}