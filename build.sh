#!/bin/sh
BASEDIR=$PWD
TOOLDIR=$BASEDIR/tools

z80() { z80asm -i$1 -o$2 && z80asm -i$1 -o/dev/null -l$3 ; }

z80 src-z80/buildme.z80 z80.blob z80.list && \
$TOOLDIR/blob2asm68k z80.blob api-asm/minimusb.68k MiniMusic_Blob MiniMusic_BlobSize && \
$TOOLDIR/blob2c z80.blob api-c/minimusb.inc minimusic_blob
