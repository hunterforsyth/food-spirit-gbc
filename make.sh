#!/bin/bash
mkdir build

ARGS="-Wa-l -Wl-m -Wl-j -Wl-yp0x143=0x80"

/opt/gbdk/bin/lcc $ARGS -c -o build/food_spirit.o src/food_spirit.c
/opt/gbdk/bin/lcc $ARGS -c -o build/utils.o src/utils.c

/opt/gbdk/bin/lcc $ARGS -o build/food_spirit.gb build/food_spirit.o build/utils.o
