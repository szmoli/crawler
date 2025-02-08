#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>
#include "math.h"
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
bool update_screen_data(screen_t *screen, const vector2_t camera_pos, const world_t *world, const entities_t *entities);
void render_screen(const screen_t *screen);
vector2_t get_screen_pos(const screen_t *screen, int num);
int get_screen_data_index(const screen_t *screen, const vector2_t pos);
char get_char_at(const screen_t *screen, const vector2_t pos);
bool update_char_at(screen_t *screen, const vector2_t pos, char new_char);

#endif