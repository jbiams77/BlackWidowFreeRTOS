#ifndef DEVICE_H
#define DEVICE_H

#include <stdio.h>

struct EEPROM
{
    uint16_t modelNumber;
    uint32_t modelInformation;
    uint8_t firmwareVersion;
    uint8_t ID;
    uint8_t baudRate;
    uint8_t returnDelayTime;
    uint8_t driveMode;
    uint8_t operatingMode;
    uint8_t secondaryID;
    uint8_t protocolType;
    int homingOffset;
    uint32_t movingThreshold;
    uint8_t temperatureLimit;
    uint16_t maxVoltageLimit;
    uint16_t minVoltageLimit;
    uint16_t pWMLimit;
    uint32_t velocityLimit;
    uint32_t maxPositionLimit;
    uint32_t minPositionLimit;
    uint8_t startupConfiguration;
    uint8_t shutdown;
};

struct ControlTable
{
    uint8_t torqueEnable;
    uint8_t LED;
    uint8_t statusReturnLevel;
    uint8_t registeredInstruction;
    uint8_t hardwareErrorStatus;
    uint16_t velocityIGain;
    uint16_t velocityPGain;
    uint16_t positionDGain;
    uint16_t positionIGain;
    uint16_t positionPGain;
    uint16_t feedforward2ndGain;
    uint16_t feedforward1stGain;
    uint8_t busWatchdog;
    uint16_t goalPWM;
    int goalVelocity;
    uint32_t profileAcceleration;
    uint32_t profileVelocity;
    uint32_t goalPosition;
    uint16_t realtimeTick;
    uint8_t moving;
    uint8_t movingStatus;
    uint16_t presentPWM;
    uint16_t presentLoad;
    uint32_t presentVelocity;
    uint32_t presentPosition;
    uint32_t velocityTrajectory;
    uint32_t positionTrajectory;
    uint16_t presentInputVoltage;
    uint8_t presentTemperature;
};

class Device
{

    public:
        EEPROM eeprom;
        ControlTable controlTable;
        
        Device();
};

#endif