#include "control_table.h"
#include <cstring>
#include <stm32f1xx_hal_flash.h>

std::vector<uint8_t> ControlTable::recover_data(uint16_t offset, uint16_t data_length) {
    std::vector<uint8_t> packed_data(data_length);
    uint8_t* packed_data_ptr = packed_data.data();

    // Compute the starting address of the requested data.
    uint8_t* start_address = reinterpret_cast<uint8_t*>(&ramArea) + offset;

    // Copy the data byte by byte, in little-endian order.
    for (uint8_t i = 0; i < data_length; ++i) {
        *packed_data_ptr++ = *(start_address + i);
    }

    return packed_data;
}


bool ControlTable::write_data_to_memory(uint8_t offset, uint8_t length, const uint8_t* data) {
    // Compute the starting and ending addresses of the memory area to write to.
    uint8_t* start_address = reinterpret_cast<uint8_t*>(&ramArea) + offset;
    uint8_t* end_address = start_address + length;

    // Check if the write operation would exceed the bounds of the memory area.
    if (end_address > reinterpret_cast<uint8_t*>(&ramArea) + sizeof(Memory)) {
        return false;
    }

    // Copy the data byte by byte, in little-endian order.
    for (uint8_t i = 0; i < length; ++i) {
        *(start_address + i) = *(data + i);
    }
    return true;
}



uint64_t ControlTable::get(CT field)
{
    switch (field) {
    // Flash values
    case CT::ModelNumber:
        return static_cast<uint64_t>(ramArea.modelNumber);
    case CT::ModelInformation:
        return static_cast<uint64_t>(ramArea.modelInformation);
    case CT::FirmwareVersion:
        return static_cast<uint64_t>(ramArea.firmwareVersion);
    case CT::ID:
        return static_cast<uint64_t>(ramArea.ID);
    case CT::BaudRate:
        return static_cast<uint64_t>(ramArea.baudRate);
    case CT::ReturnDelayTime:
        return static_cast<uint64_t>(ramArea.returnDelayTime);
    case CT::DriveMode:
        return static_cast<uint64_t>(ramArea.driveMode);
    case CT::OperatingMode:
        return static_cast<uint64_t>(ramArea.operatingMode);
    case CT::SecondaryID:
        return static_cast<uint64_t>(ramArea.secondaryID);
    case CT::ProtocolType:
        return static_cast<uint64_t>(ramArea.protocolType);
    case CT::HomingOffset:
        return static_cast<uint64_t>(ramArea.homingOffset);
    case CT::MovingThreshold:
        return static_cast<uint64_t>(ramArea.movingThreshold);
    case CT::TemperatureLimit:
        return static_cast<uint64_t>(ramArea.temperatureLimit);
    case CT::MaxVoltageLimit:
        return static_cast<uint64_t>(ramArea.maxVoltageLimit);
    case CT::MinVoltageLimit:
        return static_cast<uint64_t>(ramArea.minVoltageLimit);
    case CT::PWMLimit:
        return static_cast<uint64_t>(ramArea.pwmLimit);
    case CT::VelocityLimit:
        return static_cast<uint64_t>(ramArea.velocityLimit);
    case CT::MaxPositionLimit:
        return static_cast<uint64_t>(ramArea.maxPositionLimit);
    case CT::MinPositionLimit:
        return static_cast<uint64_t>(ramArea.minPositionLimit);
    case CT::StartupConfiguration:
        return static_cast<uint64_t>(ramArea.startupConfiguration);
    case CT::Shutdown:
        return static_cast<uint64_t>(ramArea.shutdown);

    // RAM Values
    case CT::TorqueEnable:
        return static_cast<uint64_t>(ramArea.torqueEnable);
    case CT::LED:
        return static_cast<uint64_t>(ramArea.LED);
    case CT::StatusReturnLevel:
        return static_cast<uint64_t>(ramArea.statusReturnLevel);
    case CT::RegisteredInstruction:
        return static_cast<uint64_t>(ramArea.registeredInstruction);
    case CT::HardwareErrorStatus:
        return static_cast<uint64_t>(ramArea.hardwareErrorStatus);
    case CT::VelocityIGain:
        return static_cast<uint64_t>(ramArea.velocityIGain);
    case CT::VelocityPGain:
        return static_cast<uint64_t>(ramArea.velocityPGain);
    case CT::PositionDGain:
        return static_cast<uint64_t>(ramArea.positionDGain);
    case CT::PositionIGain:
        return static_cast<uint64_t>(ramArea.positionIGain);
    case CT::PositionPGain:
        return static_cast<uint64_t>(ramArea.positionPGain);
    case CT::Feedforward2ndGain:
        return static_cast<uint64_t>(ramArea.feedforward2ndGain);
    case CT::Feedforward1stGain:
        return static_cast<uint64_t>(ramArea.feedforward1stGain);
    case CT::BusWatchdog:
        return static_cast<uint64_t>(ramArea.busWatchdog);
    case CT::GoalPWM:
        return static_cast<uint64_t>(ramArea.goalPWM);
    case CT::GoalVelocity:
        return static_cast<uint64_t>(ramArea.goalVelocity);
    case CT::ProfileAcceleration:
        return static_cast<uint64_t>(ramArea.profileAcceleration);
    case CT::ProfileVelocity:
        return static_cast<uint64_t>(ramArea.profileVelocity);
    case CT::GoalPosition:
        return static_cast<uint64_t>(ramArea.goalPosition);
    case CT::RealtimeTick:
        return static_cast<uint64_t>(ramArea.realtimeTick);
    case CT::Moving:
        return static_cast<uint64_t>(ramArea.moving);
    case CT::MovingStatus:
        return static_cast<uint64_t>(ramArea.movingStatus);
    case CT::PresentPWM:
        return static_cast<uint64_t>(ramArea.presentPWM);
    case CT::PresentLoad:
        return static_cast<uint64_t>(ramArea.presentLoad);
    case CT::PresentVelocity:
        return static_cast<uint64_t>(ramArea.presentVelocity);
    case CT::PresentPosition:
        return static_cast<uint64_t>(ramArea.presentPosition);
    case CT::VelocityTrajectory:
        return static_cast<uint64_t>(ramArea.velocityTrajectory);
    case CT::PositionTrajectory:
        return static_cast<uint64_t>(ramArea.positionTrajectory);
    case CT::PresentInputVoltage:
        return static_cast<uint64_t>(ramArea.presentInputVoltage);
    case CT::PresentTemperature:
        return static_cast<uint64_t>(ramArea.presentTemperature);
    case CT::BackupReady:
        return static_cast<uint64_t>(ramArea.backupReady);
    default:
        return 0xDEADBEEF;
    }
}

uint8_t ControlTable::get_size(CT field)
{
    switch (field) {
    // Flash values
    case CT::ModelNumber:
        return 2;
    case CT::ModelInformation:
        return 4;
    case CT::FirmwareVersion:
        return 2;
    case CT::ID:
        return 1;
    case CT::BaudRate:
        return 1;
    case CT::ReturnDelayTime:
        return 1;
    case CT::DriveMode:
        return 1;
    case CT::OperatingMode:
        return 1;
    case CT::SecondaryID:
        return 1;
    case CT::ProtocolType:
        return 1;
    case CT::HomingOffset:
        return 4;
    case CT::MovingThreshold:
        return 4;
    case CT::TemperatureLimit:
        return 1;
    case CT::MaxVoltageLimit:
        return 2;
    case CT::MinVoltageLimit:
        return 2;
    case CT::PWMLimit:
        return 2;
    case CT::VelocityLimit:
        return 4;
    case CT::MaxPositionLimit:
        return 4;
    case CT::MinPositionLimit:
        return 4;
    case CT::StartupConfiguration:
        return 1;
    case CT::Shutdown:
        return 1;

    // RAM Values
    case CT::TorqueEnable:
        return 1;
    case CT::LED:
        return 1;
    case CT::StatusReturnLevel:
        return 1;
    case CT::RegisteredInstruction:
        return 1;
    case CT::HardwareErrorStatus:
        return 1;
    case CT::VelocityIGain:
        return 2;
    case CT::VelocityPGain:
        return 2;
    case CT::PositionDGain:
        return 2;
    case CT::PositionIGain:
        return 2;
    case CT::PositionPGain:
        return 2;
    case CT::Feedforward2ndGain:
        return 2;
    case CT::Feedforward1stGain:
        return 2;
    case CT::BusWatchdog:
        return 1;
    case CT::GoalPWM:
        return 2;
    case CT::GoalVelocity:
        return 4;
    case CT::ProfileAcceleration:
        return 4;
    case CT::ProfileVelocity:
        return 4;
    case CT::GoalPosition:
        return 4;
    case CT::RealtimeTick:
        return 2;
    case CT::Moving:
        return 1;
    case CT::MovingStatus:
        return 1;
    case CT::PresentPWM:
        return 2;
    case CT::PresentLoad:
        return 2;
    case CT::PresentVelocity:
        return 4;
    case CT::PresentPosition:
        return 4;
    case CT::VelocityTrajectory:
        return 4;
    case CT::PositionTrajectory:
        return 4;
    case CT::PresentInputVoltage:
        return 2;
    case CT::PresentTemperature:
        return 1;
    case CT::BackupReady:
        return 1;
    default:
        return 0xDEADBEEF;
    }
}


void ControlTable::set(CT field, uint64_t value)
{
    switch (field) {
    case CT::ModelNumber:
        ramArea.modelNumber = value;
        break;
    case CT::ModelInformation:
        ramArea.modelInformation = value;
        break;
    case CT::FirmwareVersion:
        ramArea.firmwareVersion = value;
        break;
    case CT::ID:
        ramArea.ID = value;
        break;
    case CT::BaudRate:
        ramArea.baudRate = value;
        break;
    case CT::ReturnDelayTime:
        ramArea.returnDelayTime = value;
        break;
    case CT::DriveMode:
        ramArea.driveMode = value;
        break;
    case CT::OperatingMode:
        ramArea.operatingMode = value;
        break;
    case CT::SecondaryID:
        ramArea.secondaryID = value;
        break;
    case CT::ProtocolType:
        ramArea.protocolType = value;
        break;
    case CT::HomingOffset:
        ramArea.homingOffset = value;
        break;
    case CT::MovingThreshold:
        ramArea.movingThreshold = value;
        break;
    case CT::TemperatureLimit:
        ramArea.temperatureLimit = value;
        break;
    case CT::MaxVoltageLimit:
        ramArea.maxVoltageLimit = value;
        break;
    case CT::MinVoltageLimit:
        ramArea.minVoltageLimit = value;
        break;
    case CT::PWMLimit:
        ramArea.pwmLimit = value;
        break;
    case CT::VelocityLimit:
        ramArea.velocityLimit = value;
        break;
    case CT::MaxPositionLimit:
        ramArea.maxPositionLimit = value;
        break;
    case CT::MinPositionLimit:
        ramArea.minPositionLimit = value;
        break;
    case CT::StartupConfiguration:
        ramArea.startupConfiguration = value;
        break;
    case CT::Shutdown:
        ramArea.shutdown = value;
        break;
    case CT::TorqueEnable:
        ramArea.torqueEnable = value;
        break;
    case CT::LED:
        ramArea.LED = value;
        break;
    case CT::StatusReturnLevel:
        ramArea.statusReturnLevel = value;
        break;
    case CT::RegisteredInstruction:
        ramArea.registeredInstruction = value;
        break;
    case CT::HardwareErrorStatus:
        ramArea.hardwareErrorStatus = value;
        break;
    case CT::VelocityIGain:
        ramArea.velocityIGain = value;
        break;
    case CT::VelocityPGain:
        ramArea.velocityPGain = value;
        break;
    case CT::PositionDGain:
        ramArea.positionDGain = value;
        break;
    case CT::PositionIGain:
        ramArea.positionIGain = value;
        break;
    case CT::PositionPGain:
        ramArea.positionPGain = value;
        break;
    case CT::Feedforward2ndGain:
        ramArea.feedforward2ndGain = value;
        break;
    case CT::Feedforward1stGain:
        ramArea.feedforward1stGain = value;
        break;
    case CT::BusWatchdog:
        ramArea.busWatchdog = value;
        break;
    case CT::GoalPWM:
        ramArea.goalPWM = value;
        break;
    case CT::GoalVelocity:
        ramArea.goalVelocity = value;
        break;
    case CT::ProfileAcceleration:
        ramArea.profileAcceleration = value;
        break;
    case CT::ProfileVelocity:
        ramArea.profileVelocity = value;
        break;
    case CT::GoalPosition:
        ramArea.goalPosition = value;
        break;
    case CT::RealtimeTick:
        ramArea.realtimeTick = value;
        break;
    case CT::Moving:
        ramArea.moving = value;
        break;
    case CT::MovingStatus:
        ramArea.movingStatus = value;
        break;
    case CT::PresentPWM:
        ramArea.presentPWM = value;
        break;
    case CT::PresentLoad:
        ramArea.presentLoad = value;
        break;
    case CT::PresentVelocity:
        ramArea.presentVelocity = value;
        break;
    case CT::PresentPosition:
        ramArea.presentPosition = value;
        break;
    case CT::VelocityTrajectory:
        ramArea.velocityTrajectory = value;
        break;
    case CT::PositionTrajectory:
        ramArea.positionTrajectory = value;
        break;
    case CT::PresentInputVoltage:
        ramArea.presentInputVoltage = value;
        break;
    case CT::PresentTemperature:
        ramArea.presentTemperature = value;
        break;
    case CT::BackupReady:
        ramArea.backupReady = value;
        break;
    default:
        return;
    }
}

// void ControlTable::flash()
// {
//     static FLASH_EraseInitTypeDef eraseInitStruct;

//     // Unlock the flash to enable the flash control register access
//     HAL_FLASH_Unlock();

//     eraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
//     eraseInitStruct.PageAddress = nvStartAddress;
//     eraseInitStruct.NbPages = 1;

//     uint32_t pageError;
//     if (HAL_FLASHEx_Erase(&eraseInitStruct, &pageError) != HAL_OK) {
//         uint32_t err = HAL_FLASH_GetError();
//         (void)err;
//         return;
//     }

//     // i -> size of nvValues in **doublewords(64-bit)**
//     for (uint32_t i = 0; i < sizeof(NonvolatileValues) / 8; i++) {
//         // Access the i-th doubleword
//         uint64_t val = reinterpret_cast<uint64_t*>(&nvValues)[i];

//         // Flash the doubleworld
//         if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, nvStartAddress + i * 8, val) != HAL_OK) {
//             uint32_t err = HAL_FLASH_GetError();
//             (void)err;
//             return;
//         }
//     }

//     // Lock the Flash to disable the flash control register access
//     HAL_FLASH_Lock();
// }
