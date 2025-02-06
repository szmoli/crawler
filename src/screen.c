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
    
    // Render world and entity tiles
    for (int i = 0; i < screen->screen_size.x * screen->screen_size.y; ++i) {
        vector2_t screen_pos = get_screen_pos(screen, i);
        vector2_t world_pos = vector_add(screen_pos, actual_camera_pos);
        char new_char;

        // Check if the world position is within the world bounds.
        if (world_pos.x < 0 || world_pos.x > WORLD_WIDTH || world_pos.y < 0 || world_pos.y > WORLD_HEIGHT) {
            new_char = world_tilemap[OFF_BOUNDS];
        }
        else {
            new_char = get_world_tile_char(world_tilemap, get_tile_at(world, world_pos));
        }

        // TODO: I don't really like this approach because I need to loop over all the entities for every pixel which feels really wasteful but I don't have a better idea yet so I'm sticking with it for now.
        // I will need to implement a buffer for the screen and compare the buffer to the actual screen data so I can avoid flickering and the looping issue at the same time.
        int entity_index = get_entity_at(entities, world_pos);
        if (entity_index != MAX_ENTITIES) {
            new_char = get_entity_tile_char(entities, entity_tilemap, entity_index);
        }
        
        changed |= update_char_at(screen, screen_pos, new_char); // If changed was set to true already keep it that way.
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