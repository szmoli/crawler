#ifndef SCREEN_H
#define SCREEN_H

int get_width(void);
int get_height(void);
char **init_screen_data(int width, int height);
void destroy_screen_data(char **screen_data, int height);

#endif