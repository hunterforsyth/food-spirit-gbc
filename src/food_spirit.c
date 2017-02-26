//
//   FOOD SPIRIT GBC
//   (c) 2017 Hunter Forsyth
//

#include <stdio.h>
#include <string.h>

#include <gb/cgb.h>
#include <gb/drawing.h>
#include <gb/gb.h>

#include "sprites.c"
#include "bg_tiles.c"
#include "bg_maps.c"
#include "palettes.c"

#include "food_spirit.h"
#include "utils.h"

UBYTE player_x;
UBYTE player_y;
UBYTE player_y_draw_offset;
UBYTE player_dir;
UBYTE player_jump_frames;

UWORD player_idle_anim_frames;

struct food foods[MAX_FOODS];

void read_controls() {
    UBYTE button = joypad();

    if (button & J_A) {
        init_rand();

        if (player_jump_frames == 0) {
            player_jump_frames = 20;
        }
    }

    if (button & J_RIGHT) {
        init_rand();

        if (player_x < COLLISION_RIGHT)
            player_x += 2;

        player_dir = RIGHT;
    } else if (button & J_LEFT) {
        init_rand();

        if (player_x > COLLISION_LEFT)
            player_x -= 2;

        player_dir = LEFT;
    } else {
        player_dir = MID;
    }
}

void bounce_food(struct food * f, int dir1, int dir2, int dir3) {
    UBYTE rand_dir;
    rand_dir = get_rand(0, 2);

    if (rand_dir == 0) {
        f->dir = dir1;
    } else if (rand_dir == 1) {
        f->dir = dir2;
    } else if (rand_dir == 2) {
        f->dir = dir3;
    }
}

void food_collision(struct food * f) {
    if (player_x < f->pos_x + SPR_W + SPR_W && player_x + SPR_W + SPR_W > f->pos_x
        && player_y < f->pos_y + SPR_W + SPR_W && player_y + SPR_W + SPR_W + SPR_W > f->pos_y) {
        set_sprite_prop(f->spr_num_0_0, PAL_NUM_FOOD_TOUCH);
        set_sprite_prop(f->spr_num_1_0, PAL_NUM_FOOD_TOUCH);
        set_sprite_prop(f->spr_num_0_1, PAL_NUM_FOOD_TOUCH);
        set_sprite_prop(f->spr_num_1_1, PAL_NUM_FOOD_TOUCH);
    } else {
        set_sprite_prop(f->spr_num_0_0, f->original_pal_num);
        set_sprite_prop(f->spr_num_1_0, f->original_pal_num);
        set_sprite_prop(f->spr_num_0_1, f->original_pal_num);
        set_sprite_prop(f->spr_num_1_1, f->original_pal_num);
    }
}

void food_logic() {
    UBYTE i;

    if (get_rand_ready() != 0) {
        return;
    }

    for (i = 0; i < MAX_FOODS; i++) {
        struct food * f;
        f = &foods[i];

        if (f->enabled == ON) {
            if (f->pos_y - SPR_W < COLLISION_FLOOR && f->dir != DIR_N) {
                f->pos_y += 1;
            }

            switch (f->dir) {
                case DIR_N :
                    if (f->pos_y - SPR_W > COLLISION_CEIL) {
                        f->pos_y -= f->vel;
                    } else {
                        bounce_food(f, DIR_S, DIR_SE, DIR_SW);
                    }

                    break;

                case DIR_NE :
                    if (f->pos_y - SPR_W > COLLISION_CEIL && f->pos_x < COLLISION_RIGHT) {
                        f->pos_x += f->vel;
                        f->pos_y -= f->vel;
                    } else {
                        bounce_food(f, DIR_SW, DIR_S, DIR_W);
                    }

                    break;

                case DIR_E :
                    if (f->pos_x < COLLISION_RIGHT) {
                        f->pos_x += f->vel;
                    } else {
                        bounce_food(f, DIR_W, DIR_SW, DIR_NW);
                    }

                    break;

                case DIR_SE :
                    if (f->pos_y - SPR_W < COLLISION_FLOOR && f->pos_x < COLLISION_RIGHT) {
                        f->pos_x += f->vel;
                        f->pos_y += f->vel;
                    } else {
                        bounce_food(f, DIR_NW, DIR_N, DIR_W);
                    }

                    break;

                case DIR_S :
                    if (f->pos_y - SPR_W < COLLISION_FLOOR) {
                        f->pos_y += f->vel;
                    } else {
                        bounce_food(f, DIR_N, DIR_NW, DIR_NE);
                    }

                    break;

                case DIR_SW :
                    if (f->pos_y - SPR_W < COLLISION_FLOOR && f->pos_x > COLLISION_LEFT) {
                        f->pos_x -= f->vel;
                        f->pos_y += f->vel;
                    } else {
                        bounce_food(f, DIR_NE, DIR_N, DIR_E);
                    }

                    break;

                case DIR_W :
                    if (f->pos_x > COLLISION_LEFT) {
                        f->pos_x -= f->vel;
                    } else {
                        bounce_food(f, DIR_E, DIR_SE, DIR_NE);
                    }

                    break;

                case DIR_NW :
                    if (f->pos_y - SPR_W > COLLISION_CEIL && f->pos_x > COLLISION_LEFT) {
                        f->pos_x -= f->vel;
                        f->pos_y -= f->vel;
                    } else {
                        bounce_food(f, DIR_SE, DIR_S, DIR_E);
                    }

                    break;
            }

            food_collision(f);
        }
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

    if (player_dir == MID) {
        player_idle_anim();
    }
    
    draw_y_pos = player_y + player_y_draw_offset;

    move_sprite(SPR_PLAYER_0_0_MID, player_x, draw_y_pos);
    move_sprite(SPR_PLAYER_1_0_MID, player_x + SPR_W, draw_y_pos);
    move_sprite(SPR_PLAYER_0_1_MID, player_x, draw_y_pos + SPR_H);
    move_sprite(SPR_PLAYER_1_1_MID, player_x + SPR_W, draw_y_pos + SPR_H);
    move_sprite(SPR_PLAYER_0_2_MID, player_x, draw_y_pos + SPR_H + SPR_H);
    move_sprite(SPR_PLAYER_1_2_MID, player_x + SPR_W, draw_y_pos + SPR_H + SPR_H);
}

void draw_foods() {
    UBYTE spr; // Sprite index
    UBYTE i;   // Logical index

    if (get_rand_ready() != 0) {
        return;
    }

    i = 0;
    for (spr = 0; spr < MAX_FOODS * SPRITES_PER_FOOD; spr += SPRITES_PER_FOOD) {
        struct food * f;
        f = &foods[i];

        move_sprite(SPR_FOOD(spr), f->pos_x, f->pos_y);
        move_sprite(SPR_FOOD(spr + 1), f->pos_x + SPR_W, f->pos_y);
        move_sprite(SPR_FOOD(spr + 2), f->pos_x, f->pos_y + SPR_W);
        move_sprite(SPR_FOOD(spr + 3), f->pos_x + SPR_W, f->pos_y + SPR_W);

        i++;
    }
}

void init_player() {
    player_x = 40;
    player_y = 40;
    player_jump_frames = 0;
    player_idle_anim_frames = 0;
    player_y_draw_offset = 0;

    set_up_sprite_simple(SPR_PLAYER_0_0_MID, PAL_NUM_PLAYER, SPR_DAT_PLAYER_0_0_MID, PAL_PLAYER);
    set_up_sprite_simple(SPR_PLAYER_1_0_MID, PAL_NUM_PLAYER, SPR_DAT_PLAYER_1_0_MID, PAL_PLAYER);
    set_up_sprite_simple(SPR_PLAYER_0_1_MID, PAL_NUM_PLAYER, SPR_DAT_PLAYER_0_1_MID, PAL_PLAYER);
    set_up_sprite_simple(SPR_PLAYER_1_1_MID, PAL_NUM_PLAYER, SPR_DAT_PLAYER_1_1_MID, PAL_PLAYER);
    set_up_sprite_simple(SPR_PLAYER_0_2_MID, PAL_NUM_PLAYER, SPR_DAT_PLAYER_0_2_MID, PAL_PLAYER);
    set_up_sprite_simple(SPR_PLAYER_1_2_MID, PAL_NUM_PLAYER, SPR_DAT_PLAYER_1_2_MID, PAL_PLAYER);
}

void set_up_food_sprite(struct food * f, int spr_num, int pal_num, unsigned char * spr_dat, unsigned char * pal_dat) {
    f->original_pal_num = pal_num;

    set_up_sprite_simple(spr_num, pal_num, spr_dat, pal_dat);
}

void set_food_type(int food_index, int type) {
    UBYTE spr;
    struct food * f;

    spr = food_index * SPRITES_PER_FOOD;
    f = &foods[food_index];

    f->food_type = type;

    f->spr_num_0_0 = SPR_FOOD(spr);
    f->spr_num_1_0 = SPR_FOOD(spr + 1);
    f->spr_num_0_1 = SPR_FOOD(spr + 2);
    f->spr_num_1_1 = SPR_FOOD(spr + 3);

    if (type == 0) {
        set_up_food_sprite(f, f->spr_num_0_0, PAL_NUM_FOOD_0, SPR_DAT_FOOD_0_0_0, PAL_FOOD_0);    
        set_up_food_sprite(f, f->spr_num_1_0, PAL_NUM_FOOD_0, SPR_DAT_FOOD_1_0_0, PAL_FOOD_0);
        set_up_food_sprite(f, f->spr_num_0_1, PAL_NUM_FOOD_0, SPR_DAT_FOOD_0_1_0, PAL_FOOD_0);
        set_up_food_sprite(f, f->spr_num_1_1, PAL_NUM_FOOD_0, SPR_DAT_FOOD_1_1_0, PAL_FOOD_0);
    } else if (type == 1) {
        set_up_food_sprite(f, f->spr_num_0_0, PAL_NUM_FOOD_0, SPR_DAT_FOOD_0_0_1, PAL_FOOD_0);    
        set_up_food_sprite(f, f->spr_num_1_0, PAL_NUM_FOOD_0, SPR_DAT_FOOD_1_0_1, PAL_FOOD_0);
        set_up_food_sprite(f, f->spr_num_0_1, PAL_NUM_FOOD_0, SPR_DAT_FOOD_0_1_1, PAL_FOOD_0);
        set_up_food_sprite(f, f->spr_num_1_1, PAL_NUM_FOOD_0, SPR_DAT_FOOD_1_1_1, PAL_FOOD_0);
    }
}

void init_food(int food_index, int type, int startx, int starty, int enabled) {
    struct food * f;
    f = &foods[food_index];

    f->pos_x = startx;
    f->pos_y = starty;

    f->dir = DIR_S;
    f->vel = 3;

    f->enabled = enabled;

    set_food_type(food_index, type);
}

void init_foods() {
    UBYTE i;

    set_sprite_palette(PAL_NUM_FOOD_TOUCH, 1, PAL_FOOD_TOUCH);

    for (i = 0; i < MAX_FOODS; i++) {
        init_food(i, 0, 0, 0, OFF);
    }
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
    set_bkg_data(8, 1, TILE_BLANK_LIGHT);

    set_up_bg(0, 1, 20, 17, MAP_BG_1, MAP_PAL_BG_1);
}

void game_loop() {
    read_controls();

    player_jump_and_gravity();
    draw_player();

    food_logic();
    draw_foods();
}

void initialize() {
    cgb_compatibility();
    pre_init_rand();

    init_bg();
    init_player();
    init_foods();

    // TODO these should be spawned intermittently.
    init_food(0, 0, 80, 31, ON);
    init_food(1, 0, 60, 22, ON);
    init_food(2, 0, 30, 25, ON);
    init_food(3, 0, 40, 27, ON);
    init_food(4, 0, 80, 31, ON);
    init_food(5, 0, 60, 22, ON);
    init_food(6, 0, 30, 25, ON);
    init_food(7, 0, 40, 27, ON);

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
