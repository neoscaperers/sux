#include "machdef.h"
#include "io.h"

long jiffies; 

extern void vector_clk(void);

void clk_interrupt(void) {
    jiffies++;
}

void timer_init(void) {
    jiffies = 0;
    INSTALL_INTVEC(CLKVEC, vector_clk, PRIO(6));
    UNIBUS_WRITE_WORD(LKS, 0x40);
}