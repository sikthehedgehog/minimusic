#ifndef MINIMUS_H_
#define MINIMUS_H_

#include <stddef.h>
#include <stdint.h>

#define MINIMUSIC_MEMORY_BARRIER() volatile asm ("" : : : "memory")

static inline MINIMUSIC_Z80_GUARD_BEGIN() {
   volatile uint16_t *port = (uint16_t*)(0xA11100);
   MINIMUSIC_MEMORY_BARRIER();
   *port = 0x100;
   MINIMUSIC_MEMORY_BARRIER();
}

static inline MINIMUSIC_Z80_GUARD_END() {
   volatile uint16_t *port = (uint16_t*)(0xA11100);
   MINIMUSIC_MEMORY_BARRIER();
   *port = 0x000;
   MINIMUSIC_MEMORY_BARRIER();
}

void minimusic_init(const void *, uint16_t);
void minimusic_sendcmd(uint8_t);

#endif
