    .text
    .even
    .globl _start
_start:
    mov $0177406, r0
    mov $0177400, (r0)
    mov $5, -(r0)
.test:
    tstb (r0)
    bpl .test
    clr pc