# 68000 asm API for MiniMusic

## Adding MiniMusic to your game

You need to add the following files from the `api-asm` directory into your program:

* `minimus.68k` is the 68000 API
* `minimusb.68k` is the Z80 program

## Initialization

To initialize the sound driver, you need to call `MiniMusic_Init`. You can pass your sound data (up to 6KB) by putting the address in `a0` and the size in `d0`.

```
    lea     (SoundData), a0
    move.w  #SoundDataEnd-SoundData, d0
    jsr     MiniMusic_Init
```

Check `doc/format.md` for the format of the sound data (and remember it has to fit within 6144 bytes). This includes all the tracks as well as the instruments.

## Play music

You can play music or sound effects using the `MiniMusic_SendCmd` subroutine. Put the sound number in `d0`:

```
    move.b  #1, d0
    jsr     MiniMusic_SendCmd
```

Registers `d0-d1/a0-a1` are modified on return. Passing 0 does nothing.

The "sound number" starts at 1 and depends on how many music and sound effects you have. If you have e.g. five music and ten sound effects, then music numbers range from 1 to 5 and sound effect numbers range from 6 to 15.

## Special commands

A few special values can be passed to `MiniMusic_SendCmd` instead of a music or sound effect number:

* 255: stop music
* 254: pause playback
* 253: resume playback

When pausing, all current sound effects will be stopped, but you will be able to play new sound effects *after* it's paused (if you want to play a pause jingle, make sure you do it after sending the pause command!).

## DMA and I/O port accesses

While MiniMusic does not access the cartridge slot, it *does* access the 68000 bus (to use the PSG), so you still need to guard against hardware bugs when using DMA or the I/O ports.

To prevent this, request the Z80 bus before starting DMA or accessing the I/O port, and release the bus afterwards. You don't need to wait for the Z80 to release the bus, this is just to make sure the Z80 doesn't interfere. MiniMusic provides two macros to do this:

```
    ; any other setup needed here
    MINIMUSIC_Z80_GUARD_BEGIN
    ; start DMA or read pads here
    MINIMUSIC_Z80_GUARD_END
```

Note: only the command that triggers DMA needs to be guarded like this (you don't need to guard around other DMA registers).

## Check if music is still playing

You can check if music is still playing by calling the `MiniMusic_GetStatus` subroutine. It returns status flags in `d0`, use `btst` with `MINIMUSIC_STATUS_BGM` to check if it's playing:

```
    jsr     MiniMusic_GetStatus
    btst    #MINIMUSIC_STATUS_BGM, d0
    bne     MusicIsPlaying
```

(replace `bne` with `beq` to jump if it is *not* playing instead)

Note that it will report music as *still* playing if it's paused. It only returns false when:

* Music has stopped on its own (all tracks reached the end without looping).
* Music has been interrupted by sending a stop (255) command.
* No music has ever played to begin with.  
