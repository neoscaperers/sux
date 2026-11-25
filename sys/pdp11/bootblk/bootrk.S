#define RKDS    0177400
#define RKCS    0177404
#define RKWC    0177406
#define RKBA    0177410
#define RKDA    0177412
#define RKDB    0177416
    .text
    .even
    .globl _start
_start:
    mov $0x8000, sp
    br .
    halt



/*
 * load disk block into memory
 * - in -
 * R0 - LBA
 * R3 - address to place block
 * - out -
 * <none>
 */
_ldblk:
    mov r0, -(r6)
    mov r1, -(r6)
    mov r2, -(r6)
    jsr pc, _lba2rkda
    mov r0, @$RKDA
    mov $-256, @$RKWC
    mov $5, @$RKCS
1:
    tstb @$RKWC
    bpl 1b
    mov (r6)+, r2
    mov (r6)+, r1
    mov (r6)+, r0
    rts pc


/*
 * converts LBA to RKDA value
 * - in -
 * R0 - LBA
 * - out -
 * R0 - RKDA value
 * !! clobbers R0, R1, and R2
 */
_lba2rkda:
    mov r0, r1
    clr r0
    div $12, r0
    mov r1, r2
    ash $4, r0
    bis r2, r0
    rts pc

    .data
_kernelname:
    .asciz "vmunix"