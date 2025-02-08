#include <stdio.h>
#include <stdbool.h>
#include "screen.h"
#include "world.h"
#include "entities.h"
#include "lighting.h"

#define DEBUG

int main(void) {
    screen_t screen;
    world_t world;
    entities_t entities;
    light_sources_t light_sources;
    tile_lights_t tile_lights;
    vector2_t camera_pos = {
        .x = 0,
        .y = 0
    };
    bool running = true;
    bool needs_update = true;
    
    init_screen(&screen);
    init_world(&world);
    init_entities(&entities);
    init_lighting(&light_sources, &tile_lights);
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

        vector2_t light_source_pos = { 10, 6 };
        set_light_source(&light_sources, 0, light_source_pos, 10, 7);
        
        needs_update = update_screen_data(&screen, camera_pos, &world, &entities, &light_sources, &tile_lights);

        // drawing the screen
        if (needs_update) {
            render_screen(&screen);
        }
    }

    // Free all allocated memory here.
    destroy_screen(&screen);

    return 0;
}