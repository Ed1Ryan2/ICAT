#include "ReadSensor.h"

uint8_t SHT3X_Modecommand_Buffer[2]={0x22,0x36}; //SHT������ָ��
uint8_t SHT3X_Fetchcommand_Bbuffer[2]={0xE0,0x00};//��ȡ�������
uint8_t SHT3X_Data_Buffer[6]; //byte0,1Ϊ�¶� byte4,5Ϊʪ��
float Humidity; //ʪ�� ����
float Temperature; //�¶� ����Ϊ����
uint32_t Lux;//����ǿ�ȴ�����BH1705
uint16_t Soil_Humidity;//����ʪ�ȴ�������ģ������

void Lora_Init()
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_RESET);
}

void Sensor_Init()
{
	HAL_ADCEx_Calibration_Start(&hadc1,0x10);//ADC1У׼
	
	HAL_I2C_Master_Transmit(&hi2c1,0x44<<1,SHT3X_Modecommand_Buffer,2,0x10); //��һ��������SHT������ָ������������ԵĽ�����ʪ��ת��
	
	HAL_I2C_Master_Transmit(&hi2c1,0x44<<1,SHT3X_Fetchcommand_Bbuffer,2,0x10); //�ڶ�������ʱ��ȡ������������ 
}

void Sensor_Read()
{
	Soil_Humidity=Get_adc(4);
	Lux = BH1750_ReadLightIntensity();
	HAL_Delay(500);
	HAL_I2C_Master_Receive(&hi2c1,(0x44<<1)+1,SHT3X_Data_Buffer,6,0x10); 
	Temperature=(float)((((SHT3X_Data_Buffer[0]<<8)+SHT3X_Data_Buffer[1])*175)/65535.0f)-45; //�õ����϶��¶� 
  Humidity=(((SHT3X_Data_Buffer[3]<<8)+SHT3X_Data_Buffer[4])*100)/65535.0f; //���Եõ����ʪ��
//	printf("Lux:%d LUX Tem:%.2f Hum:%.2f,SHum:%d\r\n",Lux,Temperature,Humidity,Soil_Humidity);
}