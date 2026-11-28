#include <sys/cons.h>
#include "machdef.h"

void startup(void) {
    long a = 53353;
    timer_init();
    if (consoledev.cn_probe(&consoledev) == 0) {
        consoledev.cn_init(&consoledev);
    }
    if ((a / 4121) == 0) {

    }
}