#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>


typedef struct {
    uint16_t model_number;
    uint8_t firmware_version;
    uint8_t id;
} DSelf;

void initialize_self(void);

#endif
