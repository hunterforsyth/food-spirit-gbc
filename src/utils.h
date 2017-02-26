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

#define ON 0 
#define OFF 1

#define DIR_N 0
#define DIR_NE 1
#define DIR_E 2
#define DIR_SE 3
#define DIR_S 4
#define DIR_SW 5
#define DIR_W 6
#define DIR_NW 7

void set_up_sprite(int sprite_num, int tile_num, int palette_num, unsigned char * data, unsigned char * palette);

void set_up_sprite_simple(int sprite_num, int palette_num, unsigned char * data, unsigned char * palette);

void set_up_bg(int startx, int starty, int w, int h, unsigned char * map, unsigned char * pal_map);

void pre_init_rand();

void init_rand();

UBYTE get_rand(int min, int max);

UBYTE get_rand_ready();

#endif
