#pragma once

#include "stm32f1xx_hal_flash.h"
#include <unordered_map>

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
    static uint64_t get(CT field);

    static void write(CT field, uint64_t value);

private:
    static inline const std::unordered_map<CT, uint8_t> _eepromToBytes = {
        {CT::ModelNumber, 2},
        {CT::ModelInformation, 4},
        {CT::FirmwareVersion, 1},
        {CT::ID, 1},
        {CT::BaudRate, 1},
        {CT::ReturnDelayTime, 1},
        {CT::DriveMode, 1},
        {CT::OperatingMode, 1},
        {CT::SecondaryID, 1},
        {CT::ProtocolType, 1},
        {CT::HomingOffset, 4},
        {CT::MovingThreshold, 4},
        {CT::TemperatureLimit, 1},
        {CT::MaxVoltageLimit, 2},
        {CT::MinVoltageLimit, 2},
        {CT::PWMLimit, 2},
        {CT::VelocityLimit, 4},
        {CT::MaxPositionLimit, 4},
        {CT::MinPositionLimit, 4},
        {CT::StartupConfiguration, 1},
        {CT::Shutdown, 1}
    };

    static inline std::unordered_map<CT, uint64_t> _ramArea = {
        { CT::TorqueEnable, 0},
        { CT::LED, 0},
        { CT::StatusReturnLevel, 0},
        { CT::RegisteredInstruction, 0},
        { CT::HardwareErrorStatus, 0},
        { CT::VelocityIGain, 0},
        { CT::VelocityPGain, 0},
        { CT::PositionDGain, 0},
        { CT::PositionIGain, 0},
        { CT::PositionPGain, 0},
        { CT::Feedforward2ndGain, 0},
        { CT::Feedforward1stGain, 0},
        { CT::BusWatchdog, 0},
        { CT::GoalPWM, 0},
        { CT::GoalVelocity, 0},
        { CT::ProfileAcceleration, 0},
        { CT::ProfileVelocity, 0},
        { CT::GoalPosition, 0},
        { CT::RealtimeTick, 0},
        { CT::Moving, 0},
        { CT::MovingStatus, 0},
        { CT::PresentPWM, 0},
        { CT::PresentLoad, 0},
        { CT::PresentVelocity, 0},
        { CT::PresentPosition, 0},
        { CT::VelocityTrajectory, 0},
        { CT::PositionTrajectory, 0},
        { CT::PresentInputVoltage, 0},
        { CT::PresentTemperature, 0},
        { CT::BackupReady, 0}
    };

    // TODO: Cache all the values so we don't have to write till Flash unless we need to
    // 43 bytes
    // struct EEPROMArea
    // {
    //     uint16_t modelNumber;  // Readonly
    //     uint32_t modelInformation; // Readonly
    //     uint8_t firmwareVersion; // Readonly
    //     uint8_t ID = 1;
    //     uint8_t baudRate = 1;
    //     uint8_t returnDelayTime = 250;
    //     uint8_t driveMode = 0;
    //     uint8_t operatingMode = 3;
    //     uint8_t secondaryID = 255;
    //     uint8_t protocolType = 2;
    //     int32_t homingOffset = 0;
    //     uint32_t movingThreshold = 10;
    //     uint8_t temperatureLimit = 72;
    //     uint16_t maxVoltageLimit = 140;
    //     uint16_t minVoltageLimit = 60;
    //     uint16_t pwmLimit = 885;
    //     uint32_t velocityLimit = 265;
    //     uint32_t maxPositionLimit = 4095;
    //     uint32_t minPositionLimit = 0;
    //     uint8_t startupConfiguration = 0;
    //     uint8_t shutdown = 52;
    // } eepromArea;

    // struct RAMArea
    // {
    //     uint8_t torqueEnable;
    //     uint8_t LED;
    //     uint8_t statusReturnLevel;
    //     uint8_t registeredInstruction;
    //     uint8_t hardwareErrorStatus;
    //     uint16_t velocityIGain;
    //     uint16_t velocityPGain;
    //     uint16_t positionDGain;
    //     uint16_t positionIGain;
    //     uint16_t positionPGain;
    //     uint16_t feedforward2ndGain;
    //     uint16_t feedforward1stGain;
    //     uint8_t busWatchdog;
    //     uint16_t goalPWM;
    //     int32_t goalVelocity;
    //     uint32_t profileAcceleration;
    //     uint32_t profileVelocity;
    //     uint32_t goalPosition;
    //     uint16_t realtimeTick;
    //     uint8_t moving;
    //     uint8_t movingStatus;
    //     uint16_t presentPWM;
    //     uint16_t presentLoad;
    //     uint32_t presentVelocity;
    //     uint32_t presentPosition;
    //     uint32_t velocityTrajectory;
    //     uint32_t positionTrajectory;
    //     uint16_t presentInputVoltage;
    //     uint8_t presentTemperature;
    // } ramArea;
};
