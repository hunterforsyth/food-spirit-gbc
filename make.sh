#!/bin/bash
mkdir build

FILE_NAME="platformer"
ARGS="-Wa-l -Wl-m -Wl-j -Wl-yp0x143=0x80"

/opt/gbdk/bin/lcc $ARGS -c -o build/$FILE_NAME.o src/$FILE_NAME.c
/opt/gbdk/bin/lcc $ARGS -o build/$FILE_NAME.gbc build/$FILE_NAME.o
