#include <stdio.h>
#include <stdbool.h>
#include "screen.h"

int main(void) {
    bool running = true;
    int width = get_width();
    int height = get_height();
    char screen_data[width][height];

    /**
     *  1. check input
     *  2. do calculations based on input
     *  3. draw using the updated data
     */
    while (running) {
        // check input



        // calculations



        // drawing the screen
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {

            }
        }
    }    

    return 0;
}