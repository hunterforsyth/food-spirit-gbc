#include <stdio.h>
#include <string.h>

#include <gb/gb.h>
#include <gb/cgb.h>
#include <gb/drawing.h>

const UBYTE PLAYER_SPRITE_TOP_NUM = 0;
const UBYTE PLAYER_SPRITE_BOT_NUM = 1;

const unsigned char PLAYER_SPRITE_TOP_DATA[] = 
     { 0x00,0x18,0x18,0x66,0x7E,0xA5,0x7E,0xA5, 0x3C,0x42,0x00,0x3C,0x00,0x3C,0x00,0x5A };

const unsigned char PLAYER_SPRITE_BOT_DATA[] = 
     { 0x00,0x5A,0x00,0x5A,0x18,0x42,0x18,0x00, 0x24,0x00,0x24,0x00,0x42,0x00,0x00,0x42 };

const UWORD PLAYER_SPRITE_TOP_PALETTE[] = 
    { RGB(0, 0, 0), RGB(20, 17, 17), RGB(0, 0, 0), RGB(5, 5, 8) };

const UWORD PLAYER_SPRITE_BOT_PALETTE[] = 
    { RGB(0, 0, 0), RGB(0, 0, 31), RGB(0, 0, 0), RGB(0, 0, 0) };

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
    move_sprite(PLAYER_SPRITE_BOT_NUM, player_x, player_y);
    move_sprite(PLAYER_SPRITE_TOP_NUM, player_x, player_y - 8);
}

void game_loop() {
    read_controls();
    draw_player();
}

void init_player() {
    player_x = 40;
    player_y = 40;

    set_sprite_data(PLAYER_SPRITE_TOP_NUM, 1, PLAYER_SPRITE_TOP_DATA);
    set_sprite_tile(PLAYER_SPRITE_TOP_NUM, PLAYER_SPRITE_TOP_NUM);
    set_sprite_palette(PLAYER_SPRITE_TOP_NUM, 1, PLAYER_SPRITE_TOP_PALETTE);
    set_sprite_prop(PLAYER_SPRITE_TOP_NUM, PLAYER_SPRITE_TOP_NUM);

    set_sprite_data(PLAYER_SPRITE_BOT_NUM, 1, PLAYER_SPRITE_BOT_DATA);
    set_sprite_tile(PLAYER_SPRITE_BOT_NUM, PLAYER_SPRITE_BOT_NUM);
    set_sprite_palette(PLAYER_SPRITE_BOT_NUM, 1, PLAYER_SPRITE_BOT_PALETTE);
    set_sprite_prop(PLAYER_SPRITE_BOT_NUM, PLAYER_SPRITE_BOT_NUM);
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
