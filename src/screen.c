#include <sys/ioctl.h>
#include <malloc.h>
#include "screen.h"

/**
 * Stuff needed:
 * - camera box where you see the world
 * - a sidebar where you see descriptions, interact with menus
 * - a bottom bar where you see I/O related stuff
 */

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

void update_screen_data(const screen_t *screen, const world_t *world, const entities_t *entities) {
    // TODO
}

/**
 * Draws the characters in screen data.
 */
void draw_screen(const screen_t *screen) {
    printf("\033[2J"); // Clear the terminal

    for (int y = 0; y < screen->screen_size.y; ++y) {
        fwrite(screen->screen_data, sizeof(char), screen->screen_size.x, stdout);

        // Skip the last new line character.
        if (y == screen->screen_size.y - 1) {
            continue;
        }

        putchar('\n');
    }

    fflush(stdout);
}