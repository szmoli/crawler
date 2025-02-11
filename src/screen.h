#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>
#include "custom_math.h"
#include "world.h"
#include "entities.h"
#include "lighting.h"

typedef struct {
    vector2_t screen_size;
    char *screen_data;
} screen_t;

// Function declarations
void init_screen(screen_t *screen);
void destroy_screen(screen_t *screen);
bool update_screen_data(screen_t *screen, const vector2_t camera_pos, const world_t *world, const entities_t *entities, const light_sources_t *light_sources, const tile_lights_t *tile_lights);
void render_screen(const screen_t *screen);
vector2_t get_screen_pos(int width, int num);
int get_screen_data_index(const screen_t *screen, const vector2_t pos);
char get_char_at(const screen_t *screen, const vector2_t pos);
bool update_char_at(screen_t *screen, const vector2_t pos, char new_char);

#endif