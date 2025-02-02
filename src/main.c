#include <stdio.h>
#include <stdbool.h>
#include "screen.h"

int main(void) {
    bool running = true;
    int width = get_width();
    int height = get_height() - 1; // -1 for the cursor line
    char **screen_data = init_screen_data(width, height);

    /**
     *  1. check input
     *  2. do calculations based on input
     *  3. draw using the updated data
     */
    bool updated = true;
    while (running) {
        // check input
        // TODO


        // calculations
        // TODO


        // drawing the screen
        if (updated) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    printf("%c", screen_data[y][x]);
                }
                printf("\n");
            }
        }

        updated = false;
    }

    // Free all allocated memory here.
    destroy_screen_data(screen_data, width, height);

    return 0;
}