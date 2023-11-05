# MiniMusic sample

A minimal sample that shows how to use MiniMusic from 68000 assembly. Press C to play a quick "whoosh" sound. That's it (for now).

There are two points of interest:

* `main.68k` is the main program and shows how to use the MiniMusic API.
* The `sound` directory is the source code for the sound data used by MiniMusic. Z80 assembly is used for convenience as we let the assembler take care of computing all the addresses.

The `minimusic` directory is taken from MiniMusic's `api-asm` directory. Other files are support stuff like hardware routines that have nothing to do with MiniMusic.

A prebuilt `sample.bin` ROM file is provided if you just want to try it.

## How to build program

Build `buildme.68k` with a 68000 assembler into `sample.bin` (as a raw binary). It can be loaded into an emulator or a cartridge as desired.

One major issue is declaring variables, since this part is very _not_ portable across assemblers. If you have assembly errors regarding this part, open `define.z80` and change the macro definitions for `ByteVar`, `WordVar` and `LongVar` to something more appropriate for your assembler.

The sample sound data is already pre-built, but if you want to change it, see below.

## How to build sound data

Build `sound/data.z80` with a Z80 assembler into `sound/data.blob`. The same assembler used for building MiniMusic itself should work.

Sound data needs to be located starting at Z80 address `$0800`. If sound doesn't work and you notice that there's 512 bytes of padding at the beginning, open `sound/data.z80` and change the `org $800` line to something more appropriate for your assembler.

A bunch of files are included (instruments and the `define.z80` file). All paths assume that they're relative to the sample's root directory itself (i.e. you're building it as `sound/data.z80` instead of `data.z80`), if this is an issue you'll need to change the paths accordingly.

The `.eif` files are FM instruments. This is the same format as used by the Echo sound driver.
