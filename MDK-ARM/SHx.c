#include "SHx.h"

extern I2C_HandleTypeDef hi2c1;
extern uint8_t SHT3X_Modecommand_Buffer[2]; //periodic mode commands 
extern uint8_t SHT3X_Fetchcommand_Bbuffer[2];//读取测量结果
extern uint8_t SHT3X_Data_Buffer[6]; //byte0,1为温度 byte4,5为湿度

void SHT_Init()
{
	HAL_I2C_Master_Transmit(&hi2c1,0x44<<1,SHT3X_Modecommand_Buffer,2,0x10); //第一步，发送periodic mode commands，传感器周期性的进行温湿度转换
}

void SHT_Read()
{
	HAL_I2C_Master_Transmit(&hi2c1,0x44<<1,SHT3X_Fetchcommand_Bbuffer,2,0x10); //第二步，随时读取传感器的数据 
	HAL_I2C_Master_Receive(&hi2c1,(0x44<<1)+1,SHT3X_Data_Buffer,6,0x10); 
}