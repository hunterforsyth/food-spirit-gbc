#ifndef UTILS_H
#define UTILS_H

#define LEFT 1
#define RIGHT 2

void set_up_sprite(int sprite_num, int tile_num, int palette_num, unsigned char * data, unsigned char * palette);

void set_up_bg(int startx, int starty, int w, int h, unsigned char * map, unsigned char * pal_map);

#endif
