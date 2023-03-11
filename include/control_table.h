#pragma once

#include <cstdint>
#include <vector>


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

enum class CT {
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

class ControlTable {

    public:
        static std::vector<uint8_t> recover_data(uint16_t offset, uint16_t data_length);
        static bool write_data_to_memory(uint8_t offset, uint8_t length, const uint8_t* data);
        static uint64_t get(CT field);
        static uint8_t get_size(CT field);
        static void set(CT field, uint64_t value);
        // static void flash();

    private:
        #pragma pack(push, 1)
        struct Memory {
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
            uint32_t blank1;
            uint16_t blank2;
            uint32_t homingOffset;
            uint32_t movingThreshold;
            uint16_t blank3;
            uint8_t blank4;
            uint8_t temperatureLimit;
            uint16_t maxVoltageLimit;
            uint16_t minVoltageLimit;
            uint16_t pwmLimit;
            uint32_t blank5;
            uint16_t blank6;
            uint32_t velocityLimit;
            uint32_t maxPositionLimit;
            uint32_t minPositionLimit;
            uint32_t blank7;
            uint8_t startupConfiguration;
            uint16_t blank8;
            uint8_t shutdown;
            uint8_t torqueEnable;
            uint8_t LED;
            uint16_t blank9;
            uint8_t statusReturnLevel;
            uint8_t registeredInstruction;
            uint8_t hardwareErrorStatus;
            uint32_t blank10;
            uint8_t blank11;
            uint16_t velocityIGain;
            uint16_t velocityPGain;
            uint16_t positionDGain;
            uint16_t positionIGain;
            uint16_t positionPGain;
            uint16_t blank12;
            uint16_t feedforward2ndGain;
            uint16_t feedforward1stGain;
            uint32_t blank13;
            uint16_t blank14;
            uint8_t busWatchdog;
            uint8_t blank15;
            uint16_t goalPWM;
            uint16_t blank16;
            uint32_t goalVelocity;
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
            uint8_t backupReady;
        };
        #pragma pack(push, 1)

        // Copy the struct from _USER_DATA_START
        // static inline uint32_t nvStartAddress = reinterpret_cast<uint32_t>(&__CONTROL_TABLE_START);
        // static inline NonvolatileValues nvValues = *reinterpret_cast<NonvolatileValues*>(nvStartAddress);

        static inline Memory ramArea = {
            // Data Name                // Address | Size            
            .modelNumber = 1060,        // 0       | 2
            .modelInformation = 0,      // 2       | 4
            .firmwareVersion = 43,      // 6       | 1
            .ID = 1,                    // 7       | 1
            .baudRate = 2,              // 8       | 1
            .returnDelayTime = 250,     // 9       | 1
            .driveMode = 0,             // 10      | 1
            .operatingMode = 3,         // 11      | 1
            .secondaryID = 255,         // 12      | 1
            .protocolType = 2,          // 13      | 1
            .blank1 = 0,                // 14      | 4
            .blank2 = 0,                // 18      | 2
            .homingOffset = 0,          // 20      | 4
            .movingThreshold = 10,      // 24      | 4
            .blank3 = 0,                // 28      | 2
            .blank4 = 0,                // 30      | 1
            .temperatureLimit = 72,     // 31      | 1
            .maxVoltageLimit = 140,     // 32      | 2
            .minVoltageLimit = 60,      // 34      | 2
            .pwmLimit = 885,            // 36      | 2
            .blank5 = 0,                // 38      | 4
            .blank6 = 0,                // 42      | 2
            .velocityLimit = 265,       // 44      | 4
            .maxPositionLimit = 4095,   // 48      | 4
            .minPositionLimit = 0,      // 52      | 4
            .blank7 = 0,                // 56      | 4
            .startupConfiguration = 0,  // 60      | 1
            .blank8 = 0,                // 61      | 2
            .shutdown = 52,             // 63      | 1
            .torqueEnable = 0,          // 64      | 1
            .LED = 0,                   // 65      | 1
            .blank9 = 0,                // 66      | 2
            .statusReturnLevel = 2,     // 68      | 1
            .registeredInstruction = 0, // 69      | 1
            .hardwareErrorStatus = 0,   // 70      | 1
            .blank10 = 0,               // 71      | 4
            .blank11 = 0,               // 75      | 1
            .velocityIGain = 1000,      // 76      | 2
            .velocityPGain = 100,       // 78      | 2
            .positionDGain = 4000,      // 80      | 2
            .positionIGain = 0,         // 82      | 2
            .positionPGain = 640,       // 84      | 2
            .blank12 = 0,               // 86      | 2
            .feedforward2ndGain = 0,    // 88      | 2
            .feedforward1stGain = 0,    // 90      | 2
            .blank13 = 0,               // 92      | 4
            .blank14 = 0,               // 96      | 2
            .busWatchdog = 0,           // 98      | 1
            .blank15 = 0,               // 99      | 1
            .goalPWM = 0,               // 100     | 2
            .blank16 = 0,               // 102     | 2
            .goalVelocity = 0,          // 104     | 4
            .profileAcceleration = 0,   // 108     | 4
            .profileVelocity = 0,       // 112     | 4
            .goalPosition = 0,          // 116     | 4
            .realtimeTick = 0,          // 120     | 2
            .moving = 0,                // 122     | 1
            .movingStatus = 0,          // 123     | 1
            .presentPWM = 0,            // 124     | 2
            .presentLoad = 0,           // 126     | 2
            .presentVelocity = 0,       // 128     | 4
            .presentPosition = 0,       // 132     | 4
            .velocityTrajectory = 0,    // 136     | 4
            .positionTrajectory = 0,    // 140     | 4
            .presentInputVoltage = 0,   // 144     | 2
            .presentTemperature = 0,    // 146     | 1
            .backupReady = 1            // 147     | 1
        };

};
