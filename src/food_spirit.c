//
//   FOOD SPIRIT GBC
//   (c) 2017 Hunter Forsyth
//

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

#define COLLISION_FLOOR 120
#define COLLISION_CEIL 36
#define COLLISION_RIGHT 140
#define COLLISION_LEFT 20

UBYTE player_x;
UBYTE player_y;
UBYTE player_y_draw_offset;
UBYTE player_dir;
UBYTE player_jump_frames;

UWORD player_idle_anim_frames;

void read_controls() {
    UBYTE button = joypad();

    if (button & J_A) {
        if (player_jump_frames == 0) {
            player_jump_frames = 20;
        }
    }

    if (button & J_RIGHT) {
        if (player_x < COLLISION_RIGHT)
            player_x += 2;

        player_dir = RIGHT;
    } else if (button & J_LEFT) {
        if (player_x > COLLISION_LEFT)
            player_x -= 2;

        player_dir = LEFT;
    } else {
        player_dir = MID;
    }
}

void player_jump_and_gravity() {
    if (player_jump_frames > 0) {
        player_jump_frames--;
    }

    if (player_jump_frames > 6) {
        if (player_y > COLLISION_CEIL) {
            player_y -= 3;
        }
    } else if (player_y < COLLISION_FLOOR) {
        player_y += 3;
    }
}

void player_idle_anim() {
    if (player_idle_anim_frames < 120) {
        player_idle_anim_frames++;
    } else {
        player_idle_anim_frames = 0;
    }

    if (player_idle_anim_frames < 20) {
        player_y_draw_offset = -1;
    } else if (player_idle_anim_frames < 40) {
        player_y_draw_offset = -2;
    } else if (player_idle_anim_frames < 60) {
        player_y_draw_offset = -3;
    } else if (player_idle_anim_frames < 80) {
        player_y_draw_offset = -2;
    } else if (player_idle_anim_frames < 100) {
        player_y_draw_offset = -1;
    } else {
        player_y_draw_offset = 0;
    }
}

void draw_player() {
    UBYTE draw_y_pos;

    if (player_dir == MID)
        player_idle_anim();
    
    draw_y_pos = player_y + player_y_draw_offset;

    move_sprite(SPR_PLAYER_0_0_MID, player_x, draw_y_pos);
    move_sprite(SPR_PLAYER_1_0_MID, player_x + SPR_W, draw_y_pos);
    move_sprite(SPR_PLAYER_0_1_MID, player_x, draw_y_pos + SPR_H);
    move_sprite(SPR_PLAYER_1_1_MID, player_x + SPR_W, draw_y_pos + SPR_H);
    move_sprite(SPR_PLAYER_0_2_MID, player_x, draw_y_pos + SPR_H + SPR_H);
    move_sprite(SPR_PLAYER_1_2_MID, player_x + SPR_W, draw_y_pos + SPR_H + SPR_H);
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
    player_idle_anim_frames = 0;
    player_y_draw_offset = 0;

    set_up_sprite_simple(SPR_PLAYER_0_0_MID, SPR_DAT_PLAYER_0_0_MID, PAL_PLAYER);
    set_up_sprite_simple(SPR_PLAYER_1_0_MID, SPR_DAT_PLAYER_1_0_MID, PAL_PLAYER);
    set_up_sprite_simple(SPR_PLAYER_0_1_MID, SPR_DAT_PLAYER_0_1_MID, PAL_PLAYER);
    set_up_sprite_simple(SPR_PLAYER_1_1_MID, SPR_DAT_PLAYER_1_1_MID, PAL_PLAYER);
    set_up_sprite_simple(SPR_PLAYER_0_2_MID, SPR_DAT_PLAYER_0_2_MID, PAL_PLAYER);
    set_up_sprite_simple(SPR_PLAYER_1_2_MID, SPR_DAT_PLAYER_1_2_MID, PAL_PLAYER);
}

void init_bg() {
    set_bkg_palette(1, 1, PAL_BG_SPOTS);
    set_bkg_palette(2, 1, PAL_BG_POT);
    set_bkg_palette(3, 1, PAL_BG_FIRE);
    set_bkg_palette(4, 1, PAL_BG_POT_DARK);
    set_bkg_palette(5, 1, PAL_BG_POT_DARK_2);
    set_bkg_palette(6, 1, PAL_BG_POT_DARK_3);

    set_bkg_data(1, 1, TILE_SPOTS);
    set_bkg_data(2, 1, TILE_POT_FLOOR);
    set_bkg_data(3, 1, TILE_POT_LEFT_CORNER);
    set_bkg_data(4, 1, TILE_POT_RIGHT_CORNER);
    set_bkg_data(5, 1, TILE_POT_LEFT_WALL);
    set_bkg_data(6, 1, TILE_POT_RIGHT_WALL);
    set_bkg_data(7, 1, TILE_FIRE);
    set_bkg_data(8, 1, TILE_BLANK);

    set_up_bg(0, 1, 20, 17, MAP_BG_1, MAP_PAL_BG_1);
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
