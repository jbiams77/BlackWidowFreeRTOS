#include "control_table.h"
#include <cstring>
#include <stm32f1xx_hal_flash.h>

volatile uint8_t ramArea[RAM_AREA_LENGTH] = {0};

/**
 * @brief Initialize Memory to factory defaults. This is only called when
 * no values have been initialized (first boot) or when the factory reset command
 * was sent over communication protocol.
 * 
 * @return ** void 
 */
void ControlTable::initialize_memory()
{
    ControlTable::set(MODEL_NUMBER, 1060);
    ControlTable::set(MODEL_INFORMATION, 0);
    ControlTable::set(FIRMWARE_VERSION, 43);
    ControlTable::set(ID_POS, 2);
    ControlTable::set(BAUD_RATE, 2);
    ControlTable::set(RETURN_DELAY_TIME, 250);
    ControlTable::set(DRIVE_MODE, 0);
    ControlTable::set(OPERATING_MODE, 3);
    ControlTable::set(SECONDARY_ID, 255);
    ControlTable::set(HOMING_OFFSET, 0);
    ControlTable::set(MOVING_THRESHOLD, 10);
    ControlTable::set(TEMPERATURE_LIMIT, 72);
    ControlTable::set(MAX_VOLTAGE_LIMIT, 140);
    ControlTable::set(MIN_VOLTAGE_LIMIT, 60);
    ControlTable::set(PWM_LIMIT, 885);
    ControlTable::set(VELOCITY_LIMIT, 265);
    ControlTable::set(MAX_POSITION_LIMIT, 4095);
    ControlTable::set(MIN_POSITION_LIMIT, 0);
    ControlTable::set(STARTUP_CONFIGURATION, 0);
    ControlTable::set(SHUTDOWN, 52);
}

void ControlTable::load_memory()
{
    // load nonvolatile memory into memory
    ramArea[MODEL_NUMBER] = DXL_HIBYTE(ControlTable::get_nonvolatile(MODEL_NUMBER));
    ramArea[MODEL_NUMBER + 1] = DXL_LOBYTE(ControlTable::get_nonvolatile(MODEL_NUMBER));
    ramArea[MODEL_INFORMATION] = ControlTable::get_nonvolatile(MODEL_INFORMATION);
    ramArea[FIRMWARE_VERSION] = ControlTable::get_nonvolatile(FIRMWARE_VERSION);
    ramArea[ID_POS] = ControlTable::get_nonvolatile(ID_POS);
    ramArea[BAUD_RATE] = ControlTable::get_nonvolatile(BAUD_RATE);
    ramArea[RETURN_DELAY_TIME] = ControlTable::get_nonvolatile(RETURN_DELAY_TIME);
    ramArea[DRIVE_MODE] = ControlTable::get_nonvolatile(DRIVE_MODE);
    ramArea[OPERATING_MODE] = ControlTable::get_nonvolatile(OPERATING_MODE);
    ramArea[SECONDARY_ID] = ControlTable::get_nonvolatile(SECONDARY_ID);
    ramArea[PROTOCOL_TYPE] = ControlTable::get_nonvolatile(PROTOCOL_TYPE);
    ramArea[HOMING_OFFSET] = ControlTable::get_nonvolatile(HOMING_OFFSET);
    ramArea[MOVING_THRESHOLD] = DXL_LOBYTE(ControlTable::get_nonvolatile(MOVING_THRESHOLD));
    ramArea[MOVING_THRESHOLD + 1] = DXL_HIBYTE(ControlTable::get_nonvolatile(MOVING_THRESHOLD));
    ramArea[MOVING_THRESHOLD + 2] = DXL_3BYTE(ControlTable::get_nonvolatile(MOVING_THRESHOLD));
    ramArea[MOVING_THRESHOLD + 3] = DXL_4BYTE(ControlTable::get_nonvolatile(MOVING_THRESHOLD));
    ramArea[TEMPERATURE_LIMIT] = ControlTable::get_nonvolatile(TEMPERATURE_LIMIT);
    ramArea[MAX_VOLTAGE_LIMIT] = DXL_LOBYTE(ControlTable::get_nonvolatile(MAX_VOLTAGE_LIMIT));
    ramArea[MAX_VOLTAGE_LIMIT + 1] = DXL_HIBYTE(ControlTable::get_nonvolatile(MAX_VOLTAGE_LIMIT));
    ramArea[MIN_VOLTAGE_LIMIT] = DXL_LOBYTE(ControlTable::get_nonvolatile(MIN_VOLTAGE_LIMIT));
    ramArea[MIN_VOLTAGE_LIMIT + 1] = DXL_HIBYTE(ControlTable::get_nonvolatile(MIN_VOLTAGE_LIMIT));
    ramArea[PWM_LIMIT] = DXL_LOBYTE(ControlTable::get_nonvolatile(PWM_LIMIT));
    ramArea[PWM_LIMIT + 1] = DXL_HIBYTE(ControlTable::get_nonvolatile(PWM_LIMIT));
    ramArea[VELOCITY_LIMIT] =     DXL_LOBYTE(ControlTable::get_nonvolatile(VELOCITY_LIMIT));
    ramArea[VELOCITY_LIMIT + 1] = DXL_HIBYTE(ControlTable::get_nonvolatile(VELOCITY_LIMIT));
    ramArea[VELOCITY_LIMIT + 2] = DXL_3BYTE(ControlTable::get_nonvolatile(VELOCITY_LIMIT));
    ramArea[VELOCITY_LIMIT + 3] = DXL_4BYTE(ControlTable::get_nonvolatile(VELOCITY_LIMIT));
    ramArea[MAX_POSITION_LIMIT] = ControlTable::get_nonvolatile(MAX_POSITION_LIMIT);
    ramArea[MAX_POSITION_LIMIT + 1] = DXL_HIBYTE(ControlTable::get_nonvolatile(MAX_POSITION_LIMIT));
    ramArea[MIN_POSITION_LIMIT] = DXL_LOBYTE(ControlTable::get_nonvolatile(MIN_POSITION_LIMIT));
    ramArea[MIN_POSITION_LIMIT + 1] = DXL_HIBYTE(ControlTable::get_nonvolatile(MIN_POSITION_LIMIT));
    ramArea[MIN_POSITION_LIMIT + 2] = DXL_3BYTE(ControlTable::get_nonvolatile(MIN_POSITION_LIMIT));
    ramArea[MIN_POSITION_LIMIT + 3] = DXL_4BYTE(ControlTable::get_nonvolatile(MIN_POSITION_LIMIT));
    
    ramArea[STARTUP_CONFIGURATION] = ControlTable::get_nonvolatile(STARTUP_CONFIGURATION);
    ramArea[SHUTDOWN] = ControlTable::get_nonvolatile(SHUTDOWN);
    // Initialize remaining memory
    ramArea[TORQUE_ENABLE] = 0;
    ramArea[LED] = 1;
    ramArea[STATUS_RETURN_LEVEL] = 2;
    ramArea[REGISTERED_INSTRUCTION] = 0;
    ramArea[HARDWARE_ERROR_STATUS] = 0;
    // initialize to 1000 or 0x03E8
    ramArea[VELOCITY_I_GAIN] = 0xE8;
    ramArea[VELOCITY_I_GAIN + 1] = 0x03;
    // initialize to 100 or 0x0064
    ramArea[VELOCITY_P_GAIN] = 0x64;
    // initialize to 4000 or 0x0FA0
    ramArea[POSITION_D_GAIN] = 0xA0;
    ramArea[POSITION_D_GAIN + 1] = 0x0F;
    // initialize to 640 or 0x0280
    ramArea[POSITION_P_GAIN] = 0x0280;
}

uint64_t ControlTable::get_nonvolatile(uint8_t field)
{
    switch (field) {
    // Flash values
    case MODEL_NUMBER:
        return static_cast<uint64_t>(nvValues.modelNumber);
    case MODEL_INFORMATION:
        return static_cast<uint64_t>(nvValues.modelInformation);
    case FIRMWARE_VERSION:
        return static_cast<uint64_t>(nvValues.firmwareVersion);
    case ID_POS:
        return static_cast<uint64_t>(nvValues.ID);
    case BAUD_RATE:
        return static_cast<uint64_t>(nvValues.baudRate);
    case RETURN_DELAY_TIME:
        return static_cast<uint64_t>(nvValues.returnDelayTime);
    case DRIVE_MODE:
        return static_cast<uint64_t>(nvValues.driveMode);
    case OPERATING_MODE:
        return static_cast<uint64_t>(nvValues.operatingMode);
    case SECONDARY_ID:
        return static_cast<uint64_t>(nvValues.secondaryID);
    case PROTOCOL_TYPE:
        return static_cast<uint64_t>(nvValues.protocolType);
    case HOMING_OFFSET:
        return static_cast<uint64_t>(nvValues.homingOffset);
    case MOVING_THRESHOLD:
        return static_cast<uint64_t>(nvValues.movingThreshold);
    case TEMPERATURE_LIMIT:
        return static_cast<uint64_t>(nvValues.temperatureLimit);
    case MAX_VOLTAGE_LIMIT:
        return static_cast<uint64_t>(nvValues.maxVoltageLimit);
    case MIN_VOLTAGE_LIMIT:
        return static_cast<uint64_t>(nvValues.minVoltageLimit);
    case PWM_LIMIT:
        return static_cast<uint64_t>(nvValues.pwmLimit);
    case VELOCITY_LIMIT:
        return static_cast<uint64_t>(nvValues.velocityLimit);
    case MAX_POSITION_LIMIT:
        return static_cast<uint64_t>(nvValues.maxPositionLimit);
    case MIN_POSITION_LIMIT:
        return static_cast<uint64_t>(nvValues.minPositionLimit);
    case STARTUP_CONFIGURATION:
        return static_cast<uint64_t>(nvValues.startupConfiguration);
    case SHUTDOWN:
        return static_cast<uint64_t>(nvValues.shutdown);
    default:
        return 0xDEADBEEF;
    }
}



void ControlTable::set(uint8_t field, uint64_t value)
{
    switch (field) {
    case MODEL_NUMBER:
        nvValues.modelNumber = value;
        break;
    case MODEL_INFORMATION:
        nvValues.modelInformation = value;
        break;
    case FIRMWARE_VERSION:
        nvValues.firmwareVersion = value;
        break;
    case ID_POS:
        nvValues.ID = value;
        break;
    case BAUD_RATE:
        nvValues.baudRate = value;
        break;
    case RETURN_DELAY_TIME:
        nvValues.returnDelayTime = value;
        break;
    case DRIVE_MODE:
        nvValues.driveMode = value;
        break;
    case OPERATING_MODE:
        nvValues.operatingMode = value;
        break;
    case SECONDARY_ID:
        nvValues.secondaryID = value;
        break;
    case PROTOCOL_TYPE:
        nvValues.protocolType = value;
        break;
    case HOMING_OFFSET:
        nvValues.homingOffset = value;
        break;
    case MOVING_THRESHOLD:
        nvValues.movingThreshold = value;
        break;
    case TEMPERATURE_LIMIT:
        nvValues.temperatureLimit = value;
        break;
    case MAX_VOLTAGE_LIMIT:
        nvValues.maxVoltageLimit = value;
        break;
    case MIN_VOLTAGE_LIMIT:
        nvValues.minVoltageLimit = value;
        break;
    case PWM_LIMIT:
        nvValues.pwmLimit = value;
        break;
    case VELOCITY_LIMIT:
        nvValues.velocityLimit = value;
        break;
    case MAX_POSITION_LIMIT:
        nvValues.maxPositionLimit = value;
        break;
    case MIN_POSITION_LIMIT:
        nvValues.minPositionLimit = value;
        break;
    case STARTUP_CONFIGURATION:
        nvValues.startupConfiguration = value;
        break;
    case SHUTDOWN:
        nvValues.shutdown = value;
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
