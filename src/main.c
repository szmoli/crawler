#include <stdio.h>
#include <stdbool.h>
#include "screen.h"
#include "world.h"
#include "entities.h"

#define DEBUG

int main(void) {
    screen_t screen;
    world_t world;
    entities_t entities;
    bool running = true;
    bool needs_update = true;
    
    init_screen(&screen);
    init_world(&world);
    init_entities(&entities);
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

        needs_update = update_screen_data(&screen, NULL, &world, &entities);

        // drawing the screen
        if (needs_update) {
            render_screen(&screen);
        }
    }

    // Free all allocated memory here.
    destroy_screen(&screen);

    return 0;
}