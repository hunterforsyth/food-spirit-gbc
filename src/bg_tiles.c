//
//   FOOD SPIRIT GBC
//   (c) 2017 Hunter Forsyth
//

const unsigned char TILE_BLANK[] = 
{ 0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00 };

const unsigned char TILE_SPOTS[] = 
{ 0x42,0x00,0x81,0x00,0x18,0x00,0x24,0x00,0x24,0x00,0x18,0x00,0x81,0x00,0x42,0x00 };

const unsigned char TILE_POT_FLOOR[] =
{ 0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0x00,0x00 };
const unsigned char TILE_POT_LEFT_CORNER[] =
{ 0xFF,0xF0,0xFF,0xF0,0xFF,0xF8,0xFF,0xFF,0x7F,0x7F,0x3F,0x3F,0x10,0x1F,0x00,0x00 };
const unsigned char TILE_POT_RIGHT_CORNER[] =
{ 0xFF,0x0F,0xFF,0x0F,0xFF,0x1F,0xFF,0xFF,0xFE,0xFE,0xFC,0xFC,0x08,0xF8,0x00,0x00 };
const unsigned char TILE_POT_LEFT_WALL[] =
{ 0xFF,0xF0,0xFF,0xF0,0xFF,0xF0,0xFF,0xF0,0xFF,0xF0,0xFF,0xF0,0xFF,0xF0,0xFF,0xF0 };
const unsigned char TILE_POT_RIGHT_WALL[] =
{ 0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F,0xFF,0x0F };

const unsigned char TILE_FIRE[] =
{ 0x10,0x10,0x30,0x30,0x28,0x38,0x24,0x3C,0x54,0x6C,0x5A,0x66,0x6E,0x52,0x34,0x2C };
