//
//   FOOD SPIRIT GBC
//   (c) 2017 Hunter Forsyth
//

#define PAL_NUM_PLAYER 0

#define PAL_NUM_FOOD_TOUCH 1

#define PAL_NUM_FOOD_0 2
#define PAL_NUM_FOOD_1 3

// Player
const UWORD PAL_PLAYER[] = 
    { 0, RGB(0, 31, 27), RGB(0, 20, 17), RGB(0, 0, 0) };

// Food Touch
const UWORD PAL_FOOD_TOUCH[] = 
    { 0, RGB(27, 31, 5), RGB(27, 31, 5), RGB(0, 0, 0) };

// Food
const UWORD PAL_FOOD_0[] =
    {0, RGB(31, 31, 31), RGB(26, 12, 0), RGB(0, 0, 0)};
const UWORD PAL_FOOD_1[] =
    {0, RGB(28, 2, 2), RGB(3, 20, 1), RGB(0, 0, 0)};

// BG
const UWORD PAL_BG_SPOTS[] = 
    { RGB(31, 31, 21), RGB(29, 29, 18), 0, 0 };

const UWORD PAL_BG_POT[] = 
    { RGB(31, 31, 21), RGB(25, 25, 25), RGB(31, 21, 7), RGB(9, 9, 9) };
const UWORD PAL_BG_POT_DARK[] = 
    { 0, RGB(24, 24, 24), 0, 0};
const UWORD PAL_BG_POT_DARK_2[] = 
    { 0, RGB(23, 23, 23), 0, 0};
const UWORD PAL_BG_POT_DARK_3[] = 
    { 0, RGB(22, 22, 22), 0, 0};

const UWORD PAL_BG_FIRE[] = 
    { RGB(31, 31, 21), RGB(31, 31, 10), RGB(31, 0, 0), 0 };
