#ifndef LIGHTING_H
#define LIGHTING_H

#define MAX_LIGHT_SOURCES 128
#define MAX_BRIGHTNESS 6

#include <stdbool.h>
#include "world.h"
#include "custom_math.h"

extern const char light_tilemap[MAX_BRIGHTNESS + 1];

typedef struct {
    vector2_t positions[MAX_LIGHT_SOURCES];
    int intensities[MAX_LIGHT_SOURCES];
    int radiuses[MAX_LIGHT_SOURCES];
} light_sources_t;

typedef struct {
    int brightnesses[WORLD_HEIGHT * WORLD_WIDTH];
} tile_lights_t;

// Function declarations
void init_lighting(light_sources_t *light_sources, tile_lights_t *tile_lights);
void apply_lighting(const light_sources_t *light_sources, tile_lights_t *tile_lights);
char get_light_tile_char(int brightness);
int get_brightness_at(const tile_lights_t* tile_lights, vector2_t pos);
void set_light_source(light_sources_t *light_sources, int index, vector2_t pos, int intensity, int radius);

#endif