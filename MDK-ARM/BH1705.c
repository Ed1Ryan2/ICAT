#include "BH1705.h"

extern I2C_HandleTypeDef hi2c1;

void BH1707_WR_CMD(uint8_t cmd)
{
	HAL_I2C_Master_Transmit(&hi2c1, 0x46, &cmd,1, 0x100);
}
 

void BH1750_Init(void)
{
	BH1707_WR_CMD(0x01);
	BH1707_WR_CMD(0x10);
	BH1707_WR_CMD(0x47);
	
}

void GY30_READ_DATA(uint8_t data[])
{
	BH1750_Init();
	HAL_I2C_Master_Receive(&hi2c1, 0x46, data, 2, 0x100);
}
 

uint32_t BH1750_ReadLightIntensity(void)
{
    uint32_t lux = 0;
    uint8_t sensorData[2] = {0};
    GY30_READ_DATA(sensorData);
    lux = (sensorData[0] << 8 | sensorData[1]);
    return lux;
}