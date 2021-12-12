#include "device.h"

DSelf self;

void initialize_self(void) {

    self.id = 0x01;
    self.model_number = 0xBBBB;
    self.firmware_version = 0x01;
}