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
UBYTE player_jump_frames;

void read_controls() {
    UBYTE button = joypad();

    if (button & J_A) {
        if (player_jump_frames == 0) {
            player_jump_frames = 20;
        }
    }

    if (button & J_RIGHT) {
        if (player_x < 148)
            player_x += 2;

        player_dir = RIGHT;
    } else if (button & J_LEFT) {
        if (player_x > 20)
            player_x -= 2;

        player_dir = LEFT;
    } else {
        player_dir = 0;
    }
}

void player_jump_and_gravity() {
    if (player_jump_frames > 0) {
        player_jump_frames--;
    }

    if (player_jump_frames > 6) {
        if (player_y > 34)
            player_y -= 3;
    } else if (player_y < 136) {
        player_y += 3;
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

    player_jump_and_gravity();
    draw_player();
}

void init_player() {
    player_x = 40;
    player_y = 40;
    player_jump_frames = 0;

    set_up_sprite(PLAYER_SPR_TOP, PLAYER_SPR_TOP, PLAYER_SPR_TOP, PLAYER_SPR_TOP_DATA, PLAYER_SPR_TOP_PAL);
}

void init_bg() {
    set_bkg_palette(1, 1, BG_PAL_SPOTS);
    set_bkg_palette(2, 1, BG_PAL_POT);
    set_bkg_palette(3, 1, BG_PAL_FIRE);
    set_bkg_palette(4, 1, BG_PAL_POT_DARK);
    set_bkg_palette(5, 1, BG_PAL_POT_DARK_2);
    set_bkg_palette(6, 1, BG_PAL_POT_DARK_3);

    set_bkg_data(1, 1, BG_TILE_SPOTS_DATA);
    set_bkg_data(2, 1, BG_TILE_POT_FLOOR_DATA);
    set_bkg_data(3, 1, BG_TILE_POT_LEFT_CORNER_DATA);
    set_bkg_data(4, 1, BG_TILE_POT_RIGHT_CORNER_DATA);
    set_bkg_data(5, 1, BG_TILE_POT_LEFT_WALL_DATA);
    set_bkg_data(6, 1, BG_TILE_POT_RIGHT_WALL_DATA);
    set_bkg_data(7, 1, BG_TILE_FIRE_DATA);
    set_bkg_data(8, 1, BG_TILE_BLANK_DATA);

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
