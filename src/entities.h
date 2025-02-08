#ifndef ENTITIES_H
#define ENTITIES_H

#define MAX_ENTITIES 20

#include "custom_math.h"

typedef enum {
    PLAYER,
    ENEMY,
    ENTITY_NOTHING
} entity_t;

extern const char entity_tilemap[ENTITY_NOTHING + 1];

typedef struct {
    vector2_t positions[MAX_ENTITIES];
    int healths[MAX_ENTITIES];
    entity_t types[MAX_ENTITIES];
} entities_t;

// Function declarations
void init_entities(entities_t *entities);
void move_entity(entities_t *entities, int entity_index, const vector2_t new_pos);
void add_health(entities_t *entities, int entity_index, int hp);
char get_entity_tile_char(const entities_t *entities, const char *entity_tilemap, int index);
vector2_t get_entity_pos(const entities_t *entities, int index);
int get_entity_at(const entities_t *entities, vector2_t pos);

#endif