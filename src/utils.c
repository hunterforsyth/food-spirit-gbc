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
