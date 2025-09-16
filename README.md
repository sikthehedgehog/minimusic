# MiniMusic

Version 1.19

A tiny Z80 sound driver for Mega Drive that runs entirely off Z80 RAM and doesn't access the cartridge slot. This may be useful if you want to play sound while writing back to cartridge Flash, or if you simply want to keep things tiny.

This driver is under the zlib license (see `LICENSE.txt`). You are *not* required to credit the author, just don't lie about it.

## How to use MiniMusic

* If using C: check `doc/api-c.md`
* If using asm: check `doc/api-asm.md`

The format for the sound data is documented in `doc/format.md`. A sample program (asm API only) is available in the `sample-asm` directory.

## VDP bug workaround

There's a bug in real hardware where if the Reset button is pressed after the 68000 sets up the DMA registers but before it issues the DMA command, an internal flag in the VDP is not cleared and will lock up on the next video memory access… unless the Z80 gets on the 68000 bus first (which clears the internal flag).

Since 1.11 MiniMusic will try to get on the 68000 bus as early as it can (by poking the PSG), to take advantage of this you need to initialize MiniMusic *before* the VDP. It takes about 480 68000 cycles, so make sure to spend some time before accessing video memory (accessing the VDP registers is fine).