#include "fb_driver.h"

int kmain() {
    char hello[] = "hello world!";
    fb_write(hello, 12);
    return 0x333;
}
