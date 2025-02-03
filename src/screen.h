#ifndef SCREEN_H
#define SCREEN_H

int get_width(void);
int get_height(void);
// char **init_screen(int width, int height);
void init_screen();
// void destroy_screen(char **screen_data, int height);
void destroy_screen();
void draw_screen();

#endif