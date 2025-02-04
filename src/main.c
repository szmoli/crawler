#include <stdio.h>
#include <stdbool.h>
#include "screen.h"

#define DEBUG

int main(void) {
    screen_t screen;
    bool running = true;
    bool updated = true;
    
    init_screen(&screen);
    // printf("screen size: %dx%d\n", screen.screen_size.x, screen.screen_size.y);


    /**
     *  1. check input
     *  2. do calculations based on input
     *  3. draw using the updated data
     */
    while (running) {
        // check input
        // TODO
        // char input;
        // scanf("%c", &input);
        // if (input == 'q') {
        //     running = false;
        // }


        // calculations
        // TODO


        // drawing the screen
        if (updated) {
            draw_screen(&screen);
        }

        updated = false;
    }

    // Free all allocated memory here.
    destroy_screen(&screen);

    return 0;
}