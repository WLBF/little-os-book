#include "fb_driver.h"
#include "serial_driver.h"
#include "descriptor_tables.h"

int32_t kmain() {
    init_descriptor_tables();
    asm volatile ("int $0x4");
    return 0;
}
