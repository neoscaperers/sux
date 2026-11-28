#ifndef _IO_H
#define _IO_H

#define UNIBUS_WRITE_WORD(addr, word) \
    *((volatile int*)addr) = word

#define UNIBUS_WRITE_BYTE(addr, byte) \
    *((volatile char*)addr) = byte

#define UNIBUS_READ_WORD(addr) \
    (*(volatile int*)addr)

#define UNIBUS_READ_BYTE(addr) \
    (*(volatile char*)addr)

#define INSTALL_INTVEC(vector, handler, psw) \
    *((volatile int*)vector) = (int)handler; \
    *((volatile int*)(vector + 2)) = psw

#endif /*_IO_H*/