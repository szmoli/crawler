#include "lighting.h"

const char light_tilemap[MAX_BRIGHTNESS + 1] = {
    '@', // darkest
    '%',
    '#',
    '*',
    ':',
    '.',
    ' '
};

/**
 * Initializes the ligth sources and the tile lights with all zero values
 */
void init_lighting(light_sources_t *light_sources, tile_lights_t *tile_lights) {
    for (int i = 0; i < MAX_LIGHT_SOURCES; ++i) {
        light_sources->intensities[i] = 0;
        light_sources->radiuses[i] = 0;
        vector2_t pos = { .x = 0, .y = 0 };
        light_sources->positions[i] = pos; 
    }

    for (int i = 0; i < WORLD_HEIGHT * WORLD_WIDTH; ++i) {
        tile_lights->brightnesses[i] = 0;
    }
}

void apply_lighting(const light_sources_t *light_sources, tile_lights_t *tile_lights) {
    for (int i = 0; i < MAX_LIGHT_SOURCES; ++i) {
        // Skip inactive light sources
        if (light_sources->intensities[i] == 0) {
            continue;
        }

        int start_x = max_int(light_sources->positions[i].x - light_sources->radiuses[i], 0);
        int start_y = max_int(light_sources->positions[i].y - light_sources->radiuses[i], 0);
        int end_x = min_int(light_sources->positions[i].x + light_sources->radiuses[i], WORLD_WIDTH - 1);
        int end_y = min_int(light_sources->positions[i].y + light_sources->radiuses[i], WORLD_HEIGHT - 1);

        // Apply light from light source
        for (int y = start_y; y < end_y; ++y) {
            for (int x = start_x; x < end_x; ++x) {
                vector2_t pos = { x, y };

                int distance = vector_distance(light_sources->positions[i], pos);

                // if (distance > light_sources->radiuses[i]) {
                //     continue;
                // } 

                // Quadratic falloff light formula
                // int brightness = light_sources->intensities[i] / (1 + (distance * distance) / (light_sources->radiuses[i] * light_sources->radiuses[i]));

                // Linear falloff light formula                
                int brightness = light_sources->intensities[i] * (1 - (distance / light_sources->radiuses[i]));
                int tile_index = get_tile_index(pos);
                tile_lights->brightnesses[tile_index] = min_int((tile_lights->brightnesses[tile_index] + brightness), MAX_BRIGHTNESS);
            }
        }
    }
}

char get_light_tile_char(int brightness) {
    // Ensure that the brightness is between 0 and MAX_BRIGHTNESS.
    brightness = min_int(abs_int(brightness), MAX_BRIGHTNESS);
    return light_tilemap[brightness];
}

int get_brightness_at(const tile_lights_t* tile_lights, vector2_t pos) {
    int index = get_tile_index(pos);
    return tile_lights->brightnesses[index];
}

void set_light_source(light_sources_t *light_sources, int index, vector2_t pos, int intensity, int radius) {
    light_sources->intensities[index] = intensity;
    light_sources->radiuses[index] = radius;
    light_sources->positions[index] = pos;
}