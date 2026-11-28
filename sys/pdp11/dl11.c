#include <sys/cons.h>
#include "machdef.h"
#include "io.h"

static int console_lock = 0;
static int tx_ready = 0;
static int rx_ready = 0;

extern void vector_tx(void);
extern void vector_rx(void);

void tx_interrupt(void) {
    tx_ready = 1;
}

void rx_interrupt(void) {
    rx_ready = 1;
}

static int dl11_init(void) {
    INSTALL_INTVEC(XMITVEC, vector_tx, PRIO(4));
    INSTALL_INTVEC(CONVEC, vector_rx, PRIO(4));
    tx_ready = 1;
    rx_ready = 1;
    UNIBUS_WRITE_WORD(XCSR, 0x40);
    UNIBUS_WRITE_WORD(RCSR, 0x40);
    return 0;
}

static void dl11_waittx(void) {
    while (!tx_ready) {
        wait();
    }
}

static void dl11_waitrx(void) {
    while (!rx_ready) {
        wait();
    }
}

static int dl11_getc(void) {
    char c;
    
    dl11_waitrx();
    c = UNIBUS_READ_BYTE(RBUF);
    return c;
}

static void dl11_putc(int c) {
    dl11_waittx();
    UNIBUS_WRITE_BYTE(XBUF, (char)c);
    tx_ready = 0;
}

static int cons_probe(struct consdev* dev) {   
    return dl11_init();
}

static void cons_init(struct consdev* dev) {
    return;
}

static void cons_lock(struct consdev* dev) {
    console_lock = 1;
}

static void cons_unlock(struct consdev* dev) {
    console_lock = 0;
}

static int cons_getc(struct consdev* dev) {
    return dl11_getc();
}

static void cons_putc(struct consdev* dev, int c) {
    dl11_putc(c);
}

struct consdev consoledev = {
    cons_probe,
    cons_init,
    cons_lock,
    cons_unlock,
    cons_getc,
    cons_putc,
    "dl11dev"
};