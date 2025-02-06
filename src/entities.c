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

/**
 * Returns an entity index or MAX_ENTITIES there is no entity at the position.
 */
int get_entity_at(const entities_t *entities, vector2_t pos) {
    int i;
    for (int i = 0; i < MAX_ENTITIES; ++i) {
        if (are_vectors_equal(entities->positions[i], pos)) {
            return i;
        }
    }

    return MAX_ENTITIES; // Return MAX_ENTITIES if not found since this is an invalid index and I prefer it over returning -1.
}