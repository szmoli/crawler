#include <sys/ioctl.h>
#include <malloc.h>
#include "screen.h"
#include "lighting.h"

/**
 * Allocates memory for the screen data and fills it with space characters by default. The caller needs to free the allocated memory.
 * 
 * Sets the static variable named screen.
 */
void init_screen(screen_t *screen) {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w); // Get the size of the terminal
    vector2_t screen_size = { .x = w.ws_col, .y = w.ws_row };
    // printf("init_screen: screen size: %dx%d\n", screen_size.x, screen_size.y);

    char *screen_data = (char *) malloc(screen_size.x * screen_size.y * sizeof(char)); // Allocate 1D array for memory efficiency.

    screen->screen_size = screen_size;
    screen->screen_data = screen_data;
}

/**
 * Frees the allocated memory for the screen data.
 */
void destroy_screen(screen_t *screen) {
    free(screen->screen_data); // Free the array.
}

bool update_screen_data(screen_t *screen, const vector2_t camera_pos, const world_t *world, const entities_t *entities, const light_sources_t *light_sources, const tile_lights_t *tile_lights) {
    bool changed = false;
    char *screen_data_buffer = (char *) malloc(screen->screen_size.x * screen->screen_size.y * sizeof(char)); // TODO: free buffer

    // Update screen data buffer based on the world data and overlay lighting
    for (int cell_i = 0; cell_i < screen->screen_size.x * screen->screen_size.y; ++cell_i) {
        vector2_t screen_pos = get_screen_pos(screen->screen_size.x, cell_i);
        vector2_t world_pos = vector_add(screen_pos, camera_pos);

        char new_char;
        int brightness = get_brightness_at(tile_lights, world_pos); 
        // Check if the world position is within the world bounds.
        if (world_pos.x < 0 || world_pos.x > WORLD_WIDTH || world_pos.y < 0 || world_pos.y > WORLD_HEIGHT) {
            new_char = world_tilemap[WORLD_NOTHING];
        }
        // The world tile is visible.
        else if (brightness == MAX_BRIGHTNESS) {
            new_char = get_world_tile_char(world_tilemap, get_tile_at(world, world_pos));
        }
        // The world tile is not visible. The light tile is rendered instead.
        else {
            new_char = get_light_tile_char(brightness);
        }

        screen_data_buffer[cell_i] = new_char;
    }

    // Overlay entites
    // for (int entity_i = 0; entity_i < MAX_ENTITIES; ++entity_i) {
    //     if (entities->types[entity_i] == ENTITY_NOTHING) {
    //         continue;
    //     }

    //     vector2_t screen_pos = vector_substract(entities->positions[entity_i], camera_pos);
    //     char new_char = get_entity_tile_char(entities, entity_tilemap, entity_i);
    //     screen_data_buffer.screen_data[get_screen_data_index(&screen_data_buffer, screen_pos)] = new_char;
    // }

    // Copy buffer into the screen data and compare
    for (int cell_i = 0; cell_i < screen->screen_size.x * screen->screen_size.y; ++cell_i) {
        changed |= screen->screen_data[cell_i] != screen_data_buffer[cell_i];
        if (!changed) {
            continue;
        }
    }

    if (changed) {
        free(screen->screen_data);
        screen->screen_data = screen_data_buffer;
    } 

    return changed;
}

/**
 * Draws the characters in screen data.
 */
void render_screen(const screen_t *screen) {
    printf("\033[2J"); // Clear the terminal

    for (int y = 0; y < screen->screen_size.y; ++y) {
        int row_index = y * screen->screen_size.x;
        fwrite((char *) ((screen->screen_data) + row_index), sizeof(char), screen->screen_size.x, stdout);

        // Skip the last new line character.
        if (y == screen->screen_size.y - 1) {
            continue;
        }

        putchar('\n');
    }

    fflush(stdout);
}

vector2_t get_screen_pos(int width, int num) {
    vector2_t pos = {
        .x = num % width,
        .y = num / width
    };

    return pos;
}

int get_screen_data_index(const screen_t *screen, const vector2_t pos) {
    return pos.y * screen->screen_size.x + pos.x;
}

char get_char_at(const screen_t *screen, const vector2_t pos) {
    return screen->screen_data[get_screen_data_index(screen, pos)];
}

bool update_char_at(screen_t *screen, const vector2_t pos, char new_char) {
    if (get_char_at(screen, pos) == new_char) {
        return false;
    }
    
    screen->screen_data[get_screen_data_index(screen, pos)] = new_char;
    return true;
}