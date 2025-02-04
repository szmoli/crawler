#ifndef SCREEN_H
#define SCREEN_H

#include "math.h"
#include "world.h"
#include "entities.h"

typedef struct {
    vector2_t screen_size;
    char *screen_data;
} screen_t;

void init_screen(screen_t *screen);
void destroy_screen(screen_t *screen);
void update_screen_data(const screen_t *screen, const world_t *world, const entities_t *entities);
void draw_screen(const screen_t *screen);

#endif