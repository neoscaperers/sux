/* required definitions */
#ifndef _ASM
struct intstate {
    int r0;
    int r1;
    int r2;
    int r3;
    int r4;
    int r5;
    int sp;
    int pc;
    int psw;
};

extern long jiffies;

extern void wait(void);
#endif /*_ASM*/

#define HZ  60
#define PTRBASE 8
/* machine-specific definitions */

#define PRIO(n) (n << 5)

/* device CSRs */

/* PSW + hardware memory management CSRs */
#define SSR0    0177572
#define SSR1    0177574
#define SSR2    0177576
#define SSR3    0177516

/* 
 * Supervisor PARs/PDRs
 */
#define SISDB   0172200 /* I space PDR */
#define SDSDB   0172220 /* D space PDR */
#define SISAB   0172240 /* I space PAR */
#define SDSAB   0172260 /* D space PAR */

/*
 * Kernel PARs/PDRs
 */
#define KISDB   0172300 /* I space PDR */
#define KDSDB   0172320 /* D space PDR */
#define KISAB   0172340 /* I space PAR */
#define KDSAB   0172360 /* D space PAR */

/*
 * User PARs/PDRs
 */
#define UISDB   0177600 /* I space PDR */
#define UDSDB   0177620 /* D space PDR */
#define UISAB   0177640 /* I space PAR */
#define UDSAB   0177660 /* D space PAR */

/*
 * DL11 CSRs
 */
#define RCSR    0177560
#define RBUF    0177562
#define XCSR    0177564
#define XBUF    0177566
#define LKS     0177546
#define CONVEC  0060
#define XMITVEC 0064
#define CLKVEC  0100

/*
 * RK11 CSRs
 */
#define RKDS    0177400
#define RKER    0177402
#define RKCS    0177404
#define RKWC    0177406
#define RKBA    0177410
#define RKDA    0177412
#define RKDB    0177416

/*
 * Trap vectors
 */
#define TRPBUS  000004
#define TRPILL  000010
#define TRPBPT  000014
#define TRPIOT  000020
#define TRPPWR  000024
#define TRPEMT  000030
#define TRPSYS  000034

#ifndef _ASM

void timer_init(void);

#endif /*_ASM*/