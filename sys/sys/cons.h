#ifndef _CONS_H
#define _CONS_H

struct consdev {
    int (*cn_probe)(struct consdev*);
    void (*cn_init)(struct consdev*);
    void (*cn_lock)(struct consdev*);
    void (*cn_unlock)(struct consdev*);
    int (*cn_getc)(struct consdev*);
    void (*cn_putc)(struct consdev*, int);
    /*short cn_prio;
    int cn_flags;*/
    char cn_name[32];
};

extern struct consdev consoledev;

void puts(const char* s);
void printf(const char* fmt, ...);

#endif /*_CONS_H*/