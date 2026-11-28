    .macro vector name, handler
    .globl \name
\name:
    mov r5, -(sp)
    mov r4, -(sp)
    mov r3, -(sp)
    mov r2, -(sp)
    mov r1, -(sp)
    mov r0, -(sp)

    mov sp, -(sp)
    jsr pc, \handler
    add $2, sp
    
    mov (sp)+, r0
    mov (sp)+, r1
    mov (sp)+, r2
    mov (sp)+, r3
    mov (sp)+, r4
    mov (sp)+, r5
    rti
    .endm

    .even
    .text
    .extern _tx_interrupt
    .extern _rx_interrupt
    .extern _clk_interrupt

    vector _vector_tx, _tx_interrupt
    vector _vector_rx, _rx_interrupt
    vector _vector_clk, _clk_interrupt