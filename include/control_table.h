#pragma once

#include <cstdint>

#define MODEL_NUMBER 0
#define MODEL_INFORMATION 2
#define FIRMWARE_VERSION 6
#define ID_POS 7
#define BAUD_RATE 8
#define RETURN_DELAY_TIME 9
#define DRIVE_MODE 10
#define OPERATING_MODE 11
#define SECONDARY_ID 12
#define PROTOCOL_TYPE 13
#define HOMING_OFFSET 20
#define MOVING_THRESHOLD 24
#define TEMPERATURE_LIMIT 31
#define MAX_VOLTAGE_LIMIT 32
#define MIN_VOLTAGE_LIMIT 34
#define PWM_LIMIT 36
#define VELOCITY_LIMIT 44
#define MAX_POSITION_LIMIT 48
#define MIN_POSITION_LIMIT 52
#define STARTUP_CONFIGURATION 60
#define SHUTDOWN 63
#define TORQUE_ENABLE 64
#define LED 65
#define STATUS_RETURN_LEVEL 68
#define REGISTERED_INSTRUCTION 69
#define HARDWARE_ERROR_STATUS 70
#define VELOCITY_I_GAIN 76
#define VELOCITY_P_GAIN 78
#define POSITION_D_GAIN 80
#define POSITION_I_GAIN 82
#define POSITION_P_GAIN 84
#define FEEDFORWARD_2ND_GAIN 88
#define FEEDFORWARD_1ST_GAIN 90
#define BUS_WATCHDOG 98
#define GOAL_PWM 100
#define GOAL_VELOCITY 104
#define PROFILE_ACCELERATION 108
#define PROFILE_VELOCITY 112
#define GOAL_POSITION 116
#define REALTIME_TICK 120
#define MOVING 122
#define MOVING_STATUS 123
#define PRESENT_PWM 124
#define PRESENT_LOAD 126
#define PRESENT_VELOCITY 128
#define PRESENT_POSITION 132
#define VELOCITY_TRAJECTORY 136
#define POSITION_TRAJECTORY 140
#define PRESENT_INPUT_VOLTAGE 144
#define PRESENT_TEMPERATURE 146
#define BACKUP_READY 147

#define RAM_AREA_LENGTH    (1*1024)

/* Macro for Control Table Value */
#define DXL_MAKEWORD(a, b)  ((uint16_t)(((uint8_t)(((uint64_t)(a)) & 0xff)) | ((uint16_t)((uint8_t)(((uint64_t)(b)) & 0xff))) << 8))
#define DXL_MAKEDWORD(a, b) ((uint32_t)(((uint16_t)(((uint64_t)(a)) & 0xffff)) | ((uint32_t)((uint16_t)(((uint64_t)(b)) & 0xffff))) << 8))
#define DXL_LOWORD(l)       ((uint16_t)(((uint64_t)(l)) & 0xffff))
#define DXL_HIWORD(l)       ((uint16_t)((((uint64_t)(l)) >> 16) & 0xffff))
#define DXL_LOBYTE(w)       ((uint8_t)(((uint64_t)(w)) & 0xff))
#define DXL_HIBYTE(w)       ((uint8_t)((((uint64_t)(w)) >> 8) & 0xff))
#define DXL_3BYTE(w)       ((uint8_t)((((uint64_t)(w)) >> 16) & 0xff))
#define DXL_4BYTE(w)       ((uint8_t)((((uint64_t)(w)) >> 24) & 0xff))


// Defined in linker file
extern uint8_t __CONTROL_TABLE_START;
extern volatile uint8_t ramArea[RAM_AREA_LENGTH];

// #define __USER_DATA_START 0x0800FC00

class ControlTable {

public:
    static void load_memory();
    static uint64_t get_nonvolatile(uint8_t field);
    static void set(uint8_t field, uint64_t value);
    static void flash();
    static void initialize_memory();

private:
    struct NonvolatileValues {
        uint16_t modelNumber; // Readonly
        uint32_t modelInformation; // Readonly
        uint8_t firmwareVersion; // Readonly
        uint8_t ID;
        uint8_t baudRate;
        uint8_t returnDelayTime;
        uint8_t driveMode;
        uint8_t operatingMode;
        uint8_t secondaryID;
        uint8_t protocolType;
        int32_t homingOffset;
        uint32_t movingThreshold;
        uint8_t temperatureLimit;
        uint16_t maxVoltageLimit;
        uint16_t minVoltageLimit;
        uint16_t pwmLimit;
        uint32_t velocityLimit;
        uint32_t maxPositionLimit;
        uint32_t minPositionLimit;
        uint8_t startupConfiguration;
        uint8_t shutdown;
    };

    // Copy the struct from _USER_DATA_START
    static inline uint32_t nvStartAddress = reinterpret_cast<uint32_t>(&__CONTROL_TABLE_START);
    static inline NonvolatileValues nvValues = *reinterpret_cast<NonvolatileValues*>(nvStartAddress);

};
