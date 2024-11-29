#include "SHx.h"

extern I2C_HandleTypeDef hi2c1;
extern uint8_t SHT3X_Modecommand_Buffer[2]; //periodic mode commands 
extern uint8_t SHT3X_Fetchcommand_Bbuffer[2];//��ȡ�������
extern uint8_t SHT3X_Data_Buffer[6]; //byte0,1Ϊ�¶� byte4,5Ϊʪ��

void SHT_Init()
{
	HAL_I2C_Master_Transmit(&hi2c1,0x44<<1,SHT3X_Modecommand_Buffer,2,0x10); //��һ��������periodic mode commands�������������ԵĽ�����ʪ��ת��
}

void SHT_Read()
{
	HAL_I2C_Master_Transmit(&hi2c1,0x44<<1,SHT3X_Fetchcommand_Bbuffer,2,0x10); //�ڶ�������ʱ��ȡ������������ 
	HAL_I2C_Master_Receive(&hi2c1,(0x44<<1)+1,SHT3X_Data_Buffer,6,0x10); 
}