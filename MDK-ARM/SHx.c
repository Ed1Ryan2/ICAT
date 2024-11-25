#include "SHx.h"

extern I2C_HandleTypeDef hi2c1;


void SHT_WR_CMD(uint8_t cmd)
{
	HAL_I2C_Master_Transmit(&hi2c1, 0x44, &cmd,1, 0x100);
	//HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	//HAL_I2C_Mem_Write(&hi2c1 ,0x46,0x00,I2C_MEMADD_SIZE_8BIT,&cmd,1,0x100);
}
 

void SHT_Init(void)
{
	SHT_WR_CMD(0x2C06<<1|0x00);
	SHT_WR_CMD(0x10);
	SHT_WR_CMD(0x47);
	
}

void SHT_READ_DATA(uint8_t data[])
{
//	uint8_t temp = 0X47;
//	
//	HAL_I2C_Mem_Write(&hi2c1 ,0x47,0x00,I2C_MEMADD_SIZE_8BIT,&temp,1,0x100);
	SHT_Init();
	HAL_I2C_Master_Receive(&hi2c1, 0x46, data, 2, 0x100);
	//HAL_I2C_Mem_Read_IT(&hi2c1, 0x46, 0X00,I2C_MEMADD_SIZE_8BIT, data, 2);
	//HAL_I2C_Mem_Read(&hi2c1 ,0x46,0x47,I2C_MEMADD_SIZE_8BIT,data,2,0x100);
}
 

uint32_t SHT_Read(void)
{
    uint32_t lux = 0;
    uint8_t sensorData[2] = {0};
    SHT_READ_DATA(sensorData);
    lux = (sensorData[0] << 8 | sensorData[1]);
    return lux;
}