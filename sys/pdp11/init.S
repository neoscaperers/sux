#include "mach.h"
    .text
    .even
    .globl _pdp11_entry

/*
 *  -BOOT STATE-
 *  user and kernel must use the default register set
 *  we enter in user mode at priority 7, with all of our mappings correct, including the I/O page
 *  we will then copy all user mappings into the kernel, issue a trap instruction, and return in kernel mode.
 *  if kernel does not have split i/d enabled, we enable it here
 */
_pdp11_entry:
    bis $4, @SSR3
    mov $UISDB, r0
    mov $KISDB, r1
    clr r2
1:
    mov (r0)+, (r1)+
    inc r2
    cmp $16, r2
    blt 1b

    mov $_escalate_trap, @000034
    mov $000340, @000036
    mov sp, @KSP
    trap $0

    halt

/*
 *  escalate to kernel mode
 *  used only during the boot process
 */
_escalate_trap:
    add $2, @sp
    mov $0170340, 2(sp)
    rti