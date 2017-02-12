#include <stdio.h>
#include <string.h>

#include <gb/cgb.h>
#include <gb/drawing.h>
#include <gb/gb.h>

#include "utils.h"
#include "sprites.c"
#include "bg_tiles.c"
#include "bg_maps.c"
#include "palettes.c"

UBYTE player_x;
UBYTE player_y;
UBYTE player_dir;

void read_controls() {
    UBYTE button = joypad();

    if (button & J_UP)
        player_y--;

    if (button & J_DOWN)
        player_y++;

    if (button & J_RIGHT) {
        player_x++;
        player_dir = RIGHT;
    } else if (button & J_LEFT) {
        player_x--;
        player_dir = LEFT;
    } else {
        player_dir = 0;
    }
}

void draw_player() {
    move_sprite(PLAYER_SPR_BOT, player_x, player_y);
    move_sprite(PLAYER_SPR_TOP, player_x, player_y - 8);

    if (player_dir == LEFT) {
        set_up_sprite(PLAYER_SPR_BOT, PLAYER_SPR_BOT, PLAYER_SPR_BOT, PLAYER_SPR_BOT_LEFT_DATA, PLAYER_SPR_BOT_PAL);
    } else if (player_dir == RIGHT) {
        set_up_sprite(PLAYER_SPR_BOT, PLAYER_SPR_BOT, PLAYER_SPR_BOT, PLAYER_SPR_BOT_RIGHT_DATA, PLAYER_SPR_BOT_PAL);
    } else {
        set_up_sprite(PLAYER_SPR_BOT, PLAYER_SPR_BOT, PLAYER_SPR_BOT, PLAYER_SPR_BOT_MID_DATA, PLAYER_SPR_BOT_PAL);
    }
}

void game_loop() {
    read_controls();
    draw_player();
}

void init_player() {
    player_x = 40;
    player_y = 40;

    set_up_sprite(PLAYER_SPR_TOP, PLAYER_SPR_TOP, PLAYER_SPR_TOP, PLAYER_SPR_TOP_DATA, PLAYER_SPR_TOP_PAL);
    set_up_sprite(PLAYER_SPR_BOT, PLAYER_SPR_BOT, PLAYER_SPR_BOT, PLAYER_SPR_BOT_MID_DATA, PLAYER_SPR_BOT_PAL);
}

void init_bg() {
    set_bkg_palette(1, 1, BG_PAL_1);
    set_bkg_data(1, 1, BG_TILE_1_DATA);

    set_up_bg(0, 1, 20, 17, BG_1_MAP, BG_1_MAP_PAL);
}

void initialize() {
    cgb_compatibility();

    init_bg();
    init_player();

    SHOW_BKG;
    SHOW_SPRITES;
}

void main() {
    wait_vbl_done();
    initialize();

    while (1) {
        wait_vbl_done();
        game_loop();
    }
}
