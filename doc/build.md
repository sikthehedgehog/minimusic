# How to build MiniMusic

The Z80 program is already built for you so you shouldn't need this if you only want to use MiniMusic as-is. These instructions are in case you want to modify it instead.

First you'll need three programs:

* `z80asm`
* `blob2asm68k` (provided in the `tools` directory)
* `blob2c` (provided in the `tools` directory)

You can get `z80asm` from <https://www.nongnu.org/z80asm/> (though I downloaded it from the Ubuntu repo instead). The other two tools are single file C programs, build them as-is with your favorite C compiler.

Now you can rebuild MiniMusic using `build.sh`. That's a Linux shell file, but it shouldn't be too hard to rewrite into a BAT file for Windows if you need it.

## `blob2asm68k` and `blob2c` licenses

The license for `blob2asm68k` and `blob2c` is the following line from their source code:

> Feel free to use in whatever way you want.

These two tools are so basic that it wasn't worth applying even the zlib license to them. You may find them useful if you ever need to convert a binary blob into an array for use in source code.
