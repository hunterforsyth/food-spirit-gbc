//
//   FOOD SPIRIT GBC
//   (c) 2017 Hunter Forsyth
//

#ifndef SPIRIT_H
#define SPIRIT_H

#define COLLISION_FLOOR 120
#define COLLISION_CEIL 36
#define COLLISION_RIGHT 140
#define COLLISION_LEFT 20

#define MAX_FOODS 4
#define SPRITES_PER_FOOD 4

struct food {
    UBYTE food_type;
    UBYTE pos_x;
    UBYTE pos_y;
    UBYTE dir;
    UBYTE vel;
    UBYTE enabled; 
};

#endif
