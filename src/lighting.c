#include "lighting.h"

static bool light_update = false; // Tracks if light sources changed.
const char light_tilemap[MAX_BRIGHTNESS + 1] = {
    '@', // darkest
    '*',
    ':',
    '.',
    ' '
};

/**
 * Initializes the ligth sources and the tile lights with all zero values
 * 
 * Sets light_update to true.
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

    light_update = true;
}

/**
 * Applies the light of the light sources to the tiles.
 * 
 * Sets update_light to false.
 */
void apply_lighting(const light_sources_t *light_sources, tile_lights_t *tile_lights) {
    if (!light_update) {
        return;
    }

    for (int i = 0; i < MAX_LIGHT_SOURCES; ++i) {
        // Skip inactive light sources
        if (light_sources->intensities[i] == 0) {
            continue;
        }

        int falloff_distance = abs_int(light_sources->intensities[i] - MAX_BRIGHTNESS);
        int true_radius = light_sources->radiuses[i];
        int start_x = max_int(light_sources->positions[i].x - true_radius, 0);
        int start_y = max_int(light_sources->positions[i].y - true_radius, 0);
        int end_x = min_int(light_sources->positions[i].x + true_radius, WORLD_WIDTH - 1);
        int end_y = min_int(light_sources->positions[i].y + true_radius, WORLD_HEIGHT - 1);

        // Apply light from light source
        for (int y = start_y; y < end_y; ++y) {
            for (int x = start_x; x < end_x; ++x) {
                vector2_t pos = { x, y };
                int distance = vector_distance(light_sources->positions[i], pos);
                if (distance > true_radius) {
                    continue;
                } 

                // Linear falloff light formula                
                int brightness = max_int(0, light_sources->intensities[i] * (1 - (float)distance / true_radius));
                int tile_index = get_tile_index(pos);
                tile_lights->brightnesses[tile_index] = min_int(MAX_BRIGHTNESS, brightness);
            }
        }
    }

    light_update = false;
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

/**
 * Sets light_update to true if light source is changed.
 */
void set_light_source(light_sources_t *light_sources, int index, vector2_t pos, int intensity, int radius) {
    bool different_intensity = light_sources->intensities[index] != intensity;
    bool different_radius = light_sources->radiuses[index] != radius;
    bool different_pos = are_vectors_equal(light_sources->positions[index], pos);
    light_update = (different_intensity || different_radius || different_pos); 

    light_sources->intensities[index] = intensity;
    light_sources->radiuses[index] = radius;
    light_sources->positions[index] = pos;
}

bool lightingNeedsUpdate() {
    return light_update;
}