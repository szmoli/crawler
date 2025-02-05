#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>
#include "math.h"
#include "world.h"
#include "entities.h"

typedef struct {
    vector2_t screen_size;
    char *screen_data;
} screen_t;

void init_screen(screen_t *screen);
void destroy_screen(screen_t *screen);
bool update_screen_data(screen_t *screen, const vector2_t *camera_pos, const world_t *world, const entities_t *entities);
void render_screen(const screen_t *screen);

#endif