#include <sys/ioctl.h>
#include <malloc.h>
#include "screen.h"

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
 */
char **init_screen_data(int width, int height) {
    char **screen_data = (char **) malloc(height * sizeof(char *)); // Allocate array of char arrays.
    for (int y = 0; y < height; ++y) {
        screen_data[y] = (char *) malloc (width * sizeof(char)); // Allocate char array.
        for (int x = 0; x < width; ++x) {
            screen_data[y][x] = ' '; // Fill line with blank chars.
        }
    }

    return screen_data;
}

void destroy_screen_data(char **screen_data, int width, int height) {
    // Free all chars individually.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            free(&screen_data[y][x]);
        }
    }

    // Free the array.
    free(screen_data);
}