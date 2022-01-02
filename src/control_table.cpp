#include "control_table.h"
#include <cstring>
#include <stm32f1xx_hal_flash.h>

uint64_t ControlTable::get(CT field)
{
    switch (field) {
    // Flash values
    case CT::ModelNumber:
        return static_cast<uint64_t>(nvValues.modelNumber);
    case CT::ModelInformation:
        return static_cast<uint64_t>(nvValues.modelInformation);
    case CT::FirmwareVersion:
        return static_cast<uint64_t>(nvValues.firmwareVersion);
    case CT::ID:
        return static_cast<uint64_t>(nvValues.ID);
    case CT::BaudRate:
        return static_cast<uint64_t>(nvValues.baudRate);
    case CT::ReturnDelayTime:
        return static_cast<uint64_t>(nvValues.returnDelayTime);
    case CT::DriveMode:
        return static_cast<uint64_t>(nvValues.driveMode);
    case CT::OperatingMode:
        return static_cast<uint64_t>(nvValues.operatingMode);
    case CT::SecondaryID:
        return static_cast<uint64_t>(nvValues.secondaryID);
    case CT::ProtocolType:
        return static_cast<uint64_t>(nvValues.protocolType);
    case CT::HomingOffset:
        return static_cast<uint64_t>(nvValues.homingOffset);
    case CT::MovingThreshold:
        return static_cast<uint64_t>(nvValues.movingThreshold);
    case CT::TemperatureLimit:
        return static_cast<uint64_t>(nvValues.temperatureLimit);
    case CT::MaxVoltageLimit:
        return static_cast<uint64_t>(nvValues.maxVoltageLimit);
    case CT::MinVoltageLimit:
        return static_cast<uint64_t>(nvValues.minVoltageLimit);
    case CT::PWMLimit:
        return static_cast<uint64_t>(nvValues.pwmLimit);
    case CT::VelocityLimit:
        return static_cast<uint64_t>(nvValues.velocityLimit);
    case CT::MaxPositionLimit:
        return static_cast<uint64_t>(nvValues.maxPositionLimit);
    case CT::MinPositionLimit:
        return static_cast<uint64_t>(nvValues.minPositionLimit);
    case CT::StartupConfiguration:
        return static_cast<uint64_t>(nvValues.startupConfiguration);
    case CT::Shutdown:
        return static_cast<uint64_t>(nvValues.shutdown);

    // RAM Values
    case CT::TorqueEnable:
        return static_cast<uint64_t>(values.torqueEnable);
    case CT::LED:
        return static_cast<uint64_t>(values.LED);
    case CT::StatusReturnLevel:
        return static_cast<uint64_t>(values.statusReturnLevel);
    case CT::RegisteredInstruction:
        return static_cast<uint64_t>(values.registeredInstruction);
    case CT::HardwareErrorStatus:
        return static_cast<uint64_t>(values.hardwareErrorStatus);
    case CT::VelocityIGain:
        return static_cast<uint64_t>(values.velocityIGain);
    case CT::VelocityPGain:
        return static_cast<uint64_t>(values.velocityPGain);
    case CT::PositionDGain:
        return static_cast<uint64_t>(values.positionDGain);
    case CT::PositionIGain:
        return static_cast<uint64_t>(values.positionIGain);
    case CT::PositionPGain:
        return static_cast<uint64_t>(values.positionPGain);
    case CT::Feedforward2ndGain:
        return static_cast<uint64_t>(values.feedforward2ndGain);
    case CT::Feedforward1stGain:
        return static_cast<uint64_t>(values.feedforward1stGain);
    case CT::BusWatchdog:
        return static_cast<uint64_t>(values.busWatchdog);
    case CT::GoalPWM:
        return static_cast<uint64_t>(values.goalPWM);
    case CT::GoalVelocity:
        return static_cast<uint64_t>(values.goalVelocity);
    case CT::ProfileAcceleration:
        return static_cast<uint64_t>(values.profileAcceleration);
    case CT::ProfileVelocity:
        return static_cast<uint64_t>(values.profileVelocity);
    case CT::GoalPosition:
        return static_cast<uint64_t>(values.goalPosition);
    case CT::RealtimeTick:
        return static_cast<uint64_t>(values.realtimeTick);
    case CT::Moving:
        return static_cast<uint64_t>(values.moving);
    case CT::MovingStatus:
        return static_cast<uint64_t>(values.movingStatus);
    case CT::PresentPWM:
        return static_cast<uint64_t>(values.presentPWM);
    case CT::PresentLoad:
        return static_cast<uint64_t>(values.presentLoad);
    case CT::PresentVelocity:
        return static_cast<uint64_t>(values.presentVelocity);
    case CT::PresentPosition:
        return static_cast<uint64_t>(values.presentPosition);
    case CT::VelocityTrajectory:
        return static_cast<uint64_t>(values.velocityTrajectory);
    case CT::PositionTrajectory:
        return static_cast<uint64_t>(values.positionTrajectory);
    case CT::PresentInputVoltage:
        return static_cast<uint64_t>(values.presentInputVoltage);
    case CT::PresentTemperature:
        return static_cast<uint64_t>(values.presentTemperature);
    case CT::BackupReady:
        return static_cast<uint64_t>(values.backupReady);
    default:
        return 0xDEADBEEF;
    }
}

void ControlTable::set(CT field, uint64_t value)
{
    switch (field) {
    case CT::ModelNumber:
        nvValues.modelNumber = value;
        break;
    case CT::ModelInformation:
        nvValues.modelInformation = value;
        break;
    case CT::FirmwareVersion:
        nvValues.firmwareVersion = value;
        break;
    case CT::ID:
        nvValues.ID = value;
        break;
    case CT::BaudRate:
        nvValues.baudRate = value;
        break;
    case CT::ReturnDelayTime:
        nvValues.returnDelayTime = value;
        break;
    case CT::DriveMode:
        nvValues.driveMode = value;
        break;
    case CT::OperatingMode:
        nvValues.operatingMode = value;
        break;
    case CT::SecondaryID:
        nvValues.secondaryID = value;
        break;
    case CT::ProtocolType:
        nvValues.protocolType = value;
        break;
    case CT::HomingOffset:
        nvValues.homingOffset = value;
        break;
    case CT::MovingThreshold:
        nvValues.movingThreshold = value;
        break;
    case CT::TemperatureLimit:
        nvValues.temperatureLimit = value;
        break;
    case CT::MaxVoltageLimit:
        nvValues.maxVoltageLimit = value;
        break;
    case CT::MinVoltageLimit:
        nvValues.minVoltageLimit = value;
        break;
    case CT::PWMLimit:
        nvValues.pwmLimit = value;
        break;
    case CT::VelocityLimit:
        nvValues.velocityLimit = value;
        break;
    case CT::MaxPositionLimit:
        nvValues.maxPositionLimit = value;
        break;
    case CT::MinPositionLimit:
        nvValues.minPositionLimit = value;
        break;
    case CT::StartupConfiguration:
        nvValues.startupConfiguration = value;
        break;
    case CT::Shutdown:
        nvValues.shutdown = value;
        break;
    case CT::TorqueEnable:
        values.torqueEnable = value;
        break;
    case CT::LED:
        values.LED = value;
        break;
    case CT::StatusReturnLevel:
        values.statusReturnLevel = value;
        break;
    case CT::RegisteredInstruction:
        values.registeredInstruction = value;
        break;
    case CT::HardwareErrorStatus:
        values.hardwareErrorStatus = value;
        break;
    case CT::VelocityIGain:
        values.velocityIGain = value;
        break;
    case CT::VelocityPGain:
        values.velocityPGain = value;
        break;
    case CT::PositionDGain:
        values.positionDGain = value;
        break;
    case CT::PositionIGain:
        values.positionIGain = value;
        break;
    case CT::PositionPGain:
        values.positionPGain = value;
        break;
    case CT::Feedforward2ndGain:
        values.feedforward2ndGain = value;
        break;
    case CT::Feedforward1stGain:
        values.feedforward1stGain = value;
        break;
    case CT::BusWatchdog:
        values.busWatchdog = value;
        break;
    case CT::GoalPWM:
        values.goalPWM = value;
        break;
    case CT::GoalVelocity:
        values.goalVelocity = value;
        break;
    case CT::ProfileAcceleration:
        values.profileAcceleration = value;
        break;
    case CT::ProfileVelocity:
        values.profileVelocity = value;
        break;
    case CT::GoalPosition:
        values.goalPosition = value;
        break;
    case CT::RealtimeTick:
        values.realtimeTick = value;
        break;
    case CT::Moving:
        values.moving = value;
        break;
    case CT::MovingStatus:
        values.movingStatus = value;
        break;
    case CT::PresentPWM:
        values.presentPWM = value;
        break;
    case CT::PresentLoad:
        values.presentLoad = value;
        break;
    case CT::PresentVelocity:
        values.presentVelocity = value;
        break;
    case CT::PresentPosition:
        values.presentPosition = value;
        break;
    case CT::VelocityTrajectory:
        values.velocityTrajectory = value;
        break;
    case CT::PositionTrajectory:
        values.positionTrajectory = value;
        break;
    case CT::PresentInputVoltage:
        values.presentInputVoltage = value;
        break;
    case CT::PresentTemperature:
        values.presentTemperature = value;
        break;
    case CT::BackupReady:
        values.backupReady = value;
        break;
    default:
        return;
    }
}

void ControlTable::flash()
{
    static FLASH_EraseInitTypeDef eraseInitStruct;

    // Unlock the flash to enable the flash control register access
    HAL_FLASH_Unlock();

    eraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInitStruct.PageAddress = nvStartAddress;
    eraseInitStruct.NbPages = 1;

    uint32_t pageError;
    if (HAL_FLASHEx_Erase(&eraseInitStruct, &pageError) != HAL_OK) {
        uint32_t err = HAL_FLASH_GetError();
        (void)err;
        return;
    }

    // i -> size of nvValues in **doublewords(64-bit)**
    for (uint32_t i = 0; i < sizeof(NonvolatileValues) / 8; i++) {
        // Access the i-th doubleword
        uint64_t val = reinterpret_cast<uint64_t*>(&nvValues)[i];

        // Flash the doubleworld
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, nvStartAddress + i * 8, val) != HAL_OK) {
            uint32_t err = HAL_FLASH_GetError();
            (void)err;
            return;
        }
    }

    // Lock the Flash to disable the flash control register access
    HAL_FLASH_Lock();
}
