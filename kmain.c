#include "timer.h"
#include "fb_driver.h"
#include "serial_driver.h"
#include "descriptor_tables.h"

int32_t kmain() {
    init_descriptor_tables();
    init_timer(50);
    return 0;
}
