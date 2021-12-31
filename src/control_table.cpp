#include "control_table.h"


// Extract user_data address from 
uint8_t __attribute__((__section__(".user_data"))) userData[64];

uint64_t ControlTable::get(CT field) {
    if(field <= CT::Shutdown && field >= CT::ModelNumber) {
        // This is an eeprom/flash field
        // TODO: Handle multi-byte fields
        uint64_t value = userData[static_cast<uint8_t>(field)];
        return value;
    }

    auto search = _ramArea.find(field);
    if(search != _ramArea.end()) {
        return search->second;
    }

    // Should never hit, it should be in either eeprom/flash or ram
    return 0xDEADBEEF;
}

void ControlTable::write(CT field, uint64_t value) {
    if(field <= CT::Shutdown) {
        // This is an eeprom/flash field
    }

    auto search = _ramArea.find(field);
    if(search != _ramArea.end()) {
        search->second = value;
    }
}