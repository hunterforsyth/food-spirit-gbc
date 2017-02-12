#include <stdio.h>
#include <string.h>

#include <gb/gb.h>
#include <gb/cgb.h>
#include <gb/drawing.h>

const UBYTE PLAYER_SPRITE_NUM = 0;

const unsigned char PLAYER_SPRITE[] = 
    { 0x3C,0x3C,0x42,0x42,0x3C,0x3C,0x00,0x7E, 0x00,0x18,0x00,0x18,0x24,0x00,0x42,0x00 };

UBYTE player_x;
UBYTE player_y;

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
    move_sprite(PLAYER_SPRITE_NUM, player_x, player_y);
}

void game_loop() {
    read_controls();
    draw_player();
}

void init_player() {
    player_x = 40;
    player_y = 40;

    set_sprite_data(PLAYER_SPRITE_NUM, 1, PLAYER_SPRITE);
    set_sprite_tile(PLAYER_SPRITE_NUM, 0); // 0 is the tile #
    set_sprite_prop(PLAYER_SPRITE_NUM, 0x10);
}

void initialize() {
    cgb_compatibility();

    init_player();

    SHOW_SPRITES;
}

void main() {
    initialize();

    while (1) {
        wait_vbl_done();
        game_loop();
    }
}
