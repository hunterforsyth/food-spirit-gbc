//
//   FOOD SPIRIT GBC
//   (c) 2017 Hunter Forsyth
//

#ifndef UTILS_H
#define UTILS_H

#define SPR_W 8
#define SPR_H 8

#define MID 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

#define ON 0 
#define OFF 1

void set_up_sprite(int sprite_num, int tile_num, int palette_num, unsigned char * data, unsigned char * palette);

void set_up_sprite_simple(int sprite_num, int palette_num, unsigned char * data, unsigned char * palette);

void set_up_bg(int startx, int starty, int w, int h, unsigned char * map, unsigned char * pal_map);

#endif
