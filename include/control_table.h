#pragma once

#include "stm32f1xx_hal_flash.h"

enum class CT
{
    ModelNumber = 0,
    ModelInformation = 2,
    FirmwareVersion = 6,
    ID = 7,
    BaudRate = 8,
    ReturnDelayTime = 9,
    DriveMode = 10,
    OperatingMode = 11,
    SecondaryID = 12,
    ProtocolType = 13,
    HomingOffset = 20,
    MovingThreshold = 24,
    TemperatureLimit = 31,
    MaxVoltageLimit = 32,
    MinVoltageLimit = 34,
    PWMLimit = 36,
    VelocityLimit = 44,
    MaxPositionLimit = 48,
    MinPositionLimit = 52,
    StartupConfiguration = 60,
    Shutdown = 63,
    TorqueEnable = 64,
    LED = 65,
    StatusReturnLevel = 68,
    RegisteredInstruction = 69,
    HardwareErrorStatus = 70,
    VelocityIGain = 76,
    VelocityPGain = 78,
    PositionDGain = 80,
    PositionIGain = 82,
    PositionPGain = 84,
    Feedforward2ndGain = 88,
    Feedforward1stGain = 90,
    BusWatchdog = 98,
    GoalPWM = 100,
    GoalVelocity = 104,
    ProfileAcceleration = 108,
    ProfileVelocity = 112,
    GoalPosition = 116,
    RealtimeTick = 120,
    Moving = 122,
    MovingStatus = 123,
    PresentPWM = 124,
    PresentLoad = 126,
    PresentVelocity = 128,
    PresentPosition = 132,
    VelocityTrajectory = 136,
    PositionTrajectory = 140,
    PresentInputVoltage = 144,
    PresentTemperature = 146,
    BackupReady = 147,
    IndirectAddress1 = 168,
    IndirectAddress2 = 170,
    IndirectAddress3 = 172,
    // ...
    IndirectAddress26 = 218,
    IndirectAddress27 = 220,
    IndirectAddress28 = 222,
    IndirectData1 = 224,
    IndirectData2 = 225,
    IndirectData3 = 226,
    // ...
    IndirectData26 = 249,
    IndirectData27 = 250,
    IndirectData28 = 251,
    IndirectAddress29 = 578,
    IndirectAddress30 = 580,
    IndirectAddress31 = 582,
    // ...
    IndirectAddress54 = 628,
    IndirectAddress55 = 630,
    IndirectAddress56 = 632,
    IndirectData29 = 634,
    IndirectData30 = 635,
    IndirectData31 = 636,
    // ...
    IndirectData54 = 659,
    IndirectData55 = 660,
    IndirectData56 = 661
};

class ControlTable
{

public:
    uint64_t get(CT field) {
        return 0;
    };

    void write(CT, uint64_t) {
        
    };

private:
    // 43 bytes
    struct EEPROMArea
    {
        uint16_t modelNumber;  // Readonly
        uint32_t modelInformation; // Readonly
        uint8_t firmwareVersion; // Readonly
        uint8_t ID = 1;
        uint8_t baudRate = 1;
        uint8_t returnDelayTime = 250;
        uint8_t driveMode = 0;
        uint8_t operatingMode = 3;
        uint8_t secondaryID = 255;
        uint8_t protocolType = 2;
        int32_t homingOffset = 0;
        uint32_t movingThreshold = 10;
        uint8_t temperatureLimit = 72;
        uint16_t maxVoltageLimit = 140;
        uint16_t minVoltageLimit = 60;
        uint16_t pwmLimit = 885;
        uint32_t velocityLimit = 265;
        uint32_t maxPositionLimit = 4095;
        uint32_t minPositionLimit = 0;
        uint8_t startupConfiguration = 0;
        uint8_t shutdown = 52;
    } eepromArea;

    struct RAMArea
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
        int32_t goalVelocity;
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
    } ramArea;
};
