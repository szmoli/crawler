#include <sys/ioctl.h>
#include <malloc.h>
#include "screen.h"
#include "math.h"

/**
 * Stuff needed:
 * - camera box where you see the world
 * - a sidebar where you see descriptions, interact with menus
 * - a bottom bar where you see I/O related stuff
 */
typedef struct {
    vector2_t screen_size;
    char **screen_data;
    // vector2_t sidebar_size;
} screen_t;

static screen_t screen;

int get_width(void) {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}

int get_height(void) {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_row;
}

/**
 * Allocates memory for the screen data and fills it with space characters by default. The caller needs to free the allocated memory.
 * 
 * Sets the static variable named screen.
 */
void init_screen() {
    vector2_t screen_size = { .x = get_width(), .y = get_height() };
    screen.screen_size = screen_size;

    char **screen_data = (char **) malloc(screen_size.y * sizeof(char *)); // Allocate array of char arrays.
    for (int y = 0; y < screen_size.y; ++y) {
        screen_data[y] = (char *) malloc (screen_size.x * sizeof(char)); // Allocate char array.
        for (int x = 0; x < screen_size.x; ++x) {
            screen_data[y][x] = '.'; // Fill line with blank chars.
        }
    }

    screen.screen_data = screen_data;
}

/**
 * Frees the allocated memory for the screen data.
 */
void destroy_screen() {
    // Free all chars individually.
    for (int y = 0; y < screen.screen_size.y; ++y) {
        free(screen.screen_data[y]);
    }

    // Free the array.
    free(screen.screen_data);
}

/**
 * Draws the characters in screen data.
 */
void draw_screen() {
    printf("\033[2J"); // Clear the terminal

    for (int y = 0; y < screen.screen_size.y; ++y) {
        fwrite(screen.screen_data[y], sizeof(char), screen.screen_size.x, stdout);

        // Skip the last new line character.
        if (y == screen.screen_size.y - 1) {
            continue;
        }

        putchar('\n');
    }

    fflush(stdout);
}