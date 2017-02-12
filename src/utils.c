#include <stdio.h>
#include <string.h>

#include <gb/gb.h>
#include <gb/cgb.h>
#include <gb/drawing.h>

#include "utils.h"

void set_up_sprite(int sprite_num, int tile_num, int palette_num, unsigned char * data, unsigned char * palette) {
    set_sprite_data(tile_num, 1, data);
    set_sprite_tile(sprite_num, tile_num);

    set_sprite_palette(palette_num, 1, palette);
    set_sprite_prop(sprite_num, palette_num);
}

void set_up_bg(int startx, int starty, int w, int h, unsigned char * map, unsigned char * pal_map) {
    VBK_REG = 1; // Use VBK_REG = 1 to set the palette map for the cgb
    set_bkg_tiles(startx, starty, w, h, pal_map);
    VBK_REG = 0;

    set_bkg_tiles(startx, starty, w, h, map);
}
