#include <sys/machdef.h>
    .text
    .even
    .globl _pdp11_entry
    .extern _startup
/*
 *  -BOOT STATE-
 */
_pdp11_entry:
    jsr pc, _startup
.loop:
    jsr pc, _wait
    br .loop

    .globl _wait
_wait:
    spl $0
    wait
    rts pc

    .data
    .even
    .globl _vecbase
_vecbase:
    .skip 512