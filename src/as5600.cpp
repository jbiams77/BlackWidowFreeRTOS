#include "stm32f1xx_hal.h"
#include "as5600.h"

extern I2C_HandleTypeDef hi2c2;

void MagneticEncoder::WriteRegister(uint8_t reg, uint8_t data)
{
	HAL_I2C_Master_Transmit(&hi2c2, AS5600_ADDRESS, &data, 1, 10);	
	HAL_I2C_Mem_Write(&hi2c2, (AS5600_ADDRESS << 1), reg, 1, &data, 1, 100);
}

uint8_t MagneticEncoder::ReadRegister(uint8_t reg)
{
	uint8_t data_read = 0;	
	HAL_I2C_Mem_Read(&hi2c2, (AS5600_ADDRESS << 1), reg, 1, &data_read, 1, 100);
	
	
	return data_read;
}

uint32_t MagneticEncoder::GetAngle()
{
	return (int)((float)(ReadRegister(ANGLE_L) + (ReadRegister(ANGLE_H) << 8))/4096*360);	
}


uint16_t MagneticEncoder::GetRawAngle()
{
	uint16_t angle_val = ReadRegister(RAWANG_L) + (ReadRegister(RAWANG_H) << 8);
	return angle_val;	
}

uint8_t MagneticEncoder::GetStatus()
{
	return ReadRegister(STATUS) & 0x38;	
}

void MagneticEncoder::SetHystheresis(uint8_t hystheresis)
{
	uint8_t tmp_conf_high = ReadRegister(CONF_H);
	tmp_conf_high |= (HYST_MASK & hystheresis);	
	WriteRegister(CONF_H, tmp_conf_high);
}

void MagneticEncoder::SetOutputStage(uint8_t out_stage)
{
	uint8_t tmp_conf_high = ReadRegister(CONF_H);
	tmp_conf_high |= (OUT_STG_MASK & out_stage);
	WriteRegister(CONF_H, tmp_conf_high);
}

void MagneticEncoder::SetPWMFrequency(uint8_t frequency)
{
	uint8_t tmp_conf_high=ReadRegister(CONF_H);
	tmp_conf_high |= (PWMF_MASK & frequency);
	WriteRegister(CONF_H, tmp_conf_high);
}
