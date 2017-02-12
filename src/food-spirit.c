#include <stdio.h>
#include <string.h>

#include <gb/cgb.h>
#include <gb/drawing.h>
#include <gb/gb.h>

#include "utils.h"
#include "sprites.c"
#include "palettes.c"

UBYTE player_x;
UBYTE player_y;
UBYTE cooked_percent;

void read_controls() {
    UBYTE button = joypad();

    if (button & J_UP)
        player_y--;

    if (button & J_DOWN)
        player_y++;

    if (button & J_RIGHT)
        player_x++;

    if (button & J_LEFT)
        player_x--;
}

void draw_player() {
    move_sprite(PLAYER_SPR_BOT, player_x, player_y);
    move_sprite(PLAYER_SPR_TOP, player_x, player_y - 8);
}

void update_score_display() {
    gotogxy(0, 0);
    gprintf("%d%% Tasty  ", cooked_percent);
}

void set_score(int new) {
    cooked_percent = new;
    update_score_display();
}

void update_score(int diff) {
    cooked_percent += diff;
    update_score_display();
}

void game_loop() {
    read_controls();
    draw_player();
}

void init_player() {
    player_x = 40;
    player_y = 40;

    set_up_sprite(PLAYER_SPR_TOP, PLAYER_SPR_TOP, PLAYER_SPR_TOP, PLAYER_SPR_TOP_DATA, PLAYER_SPR_TOP_PAL);
    set_up_sprite(PLAYER_SPR_BOT, PLAYER_SPR_BOT, PLAYER_SPR_BOT, PLAYER_SPR_BOT_DATA, PLAYER_SPR_BOT_PAL);
}

void init_text() {
    // TODO set text palettes
}

void initialize() {
    cgb_compatibility();

    init_text();
    init_player();
    set_score(100);
    set_score(10);

    SHOW_SPRITES;
}

void main() {
    initialize();

    while (1) {
        wait_vbl_done();
        game_loop();
    }
}
