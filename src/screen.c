#include <sys/ioctl.h>
#include <malloc.h>
#include "screen.h"

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

    for (int i = 0; i < screen_size.x * screen_size.y; ++i) {
        screen_data[i] = '.'; // Fill with blank spaces.
    }

    screen->screen_size = screen_size;
    screen->screen_data = screen_data;
}

/**
 * Frees the allocated memory for the screen data.
 */
void destroy_screen(screen_t *screen) {
    free(screen->screen_data); // Free the array.
}

bool update_screen_data(screen_t *screen, const vector2_t *camera_pos, const world_t *world, const entities_t *entities) {
    bool changed = false;

    // Default to (0, 0) if no camera position was given.
    vector2_t actual_camera_pos = {
        .x = camera_pos == NULL ? 0 : camera_pos->x,
        .y = camera_pos == NULL ? 0 : camera_pos->y
    };
    
    // Render world tiles
    for (int i = 0; i < screen->screen_size.x * screen->screen_size.y; ++i) {
        vector2_t screen_pos = get_screen_pos(screen, i);
        vector2_t world_pos = vector_add(screen_pos, actual_camera_pos);
        char new_char = get_world_tile_char(world_tilemap, get_tile_at(world, world_pos));
        
        changed = update_char_at(screen, screen_pos, new_char);
    }

    // Render entity tiles
    // for (int i = 0; i < MAX_ENTITIES; ++i) {
    //     if (entities->types[i] == ENTITY_NOTHING) {
    //         continue;
    //     }

    //     char new_char = get_entity_tile_char(entities, entity_tilemap, i);
    //     vector2_t screen_pos = vector_substract(get_entity_pos(entities, i), actual_camera_pos);

    //     changed = update_char_at(screen, screen_pos, new_char);
    // }

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

vector2_t get_screen_pos(const screen_t *screen, int num) {
    vector2_t pos = {
        .x = num % screen->screen_size.x,
        .y = num / screen->screen_size.x
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