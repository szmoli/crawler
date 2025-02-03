#include <stdio.h>
#include <stdbool.h>
#include "screen.h"

int main(void) {
    bool running = true;
    bool updated = true;
    
    init_screen();

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
            draw_screen();
        }

        updated = false;
    }

    // Free all allocated memory here.
    destroy_screen();

    return 0;
}