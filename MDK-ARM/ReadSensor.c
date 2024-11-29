#include "ReadSensor.h"

uint8_t SHT3X_Modecommand_Buffer[2]={0x22,0x36}; //SHT传感器指令
uint8_t SHT3X_Fetchcommand_Bbuffer[2]={0xE0,0x00};//读取测量结果
uint8_t SHT3X_Data_Buffer[6]; //byte0,1为温度 byte4,5为湿度
float Humidity; //湿度 正数
float Temperature; //温度 可能为负数
uint32_t Lux;//光照强度传感器BH1705
uint16_t Soil_Humidity;//土壤湿度传感器（模拟量）

void Lora_Init()
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_RESET);
}

void Sensor_Init()
{
	HAL_ADCEx_Calibration_Start(&hadc1,0x10);//ADC1校准
	
	HAL_I2C_Master_Transmit(&hi2c1,0x44<<1,SHT3X_Modecommand_Buffer,2,0x10); //第一步，发送SHT传感器指令，传感器周期性的进行温湿度转换
	
	HAL_I2C_Master_Transmit(&hi2c1,0x44<<1,SHT3X_Fetchcommand_Bbuffer,2,0x10); //第二步，随时读取传感器的数据 
}

void Sensor_Read()
{
	Soil_Humidity=Get_adc(4);
	Lux = BH1750_ReadLightIntensity();
	HAL_Delay(500);
	HAL_I2C_Master_Receive(&hi2c1,(0x44<<1)+1,SHT3X_Data_Buffer,6,0x10); 
	Temperature=(float)((((SHT3X_Data_Buffer[0]<<8)+SHT3X_Data_Buffer[1])*175)/65535.0f)-45; //得到摄氏度温度 
  Humidity=(((SHT3X_Data_Buffer[3]<<8)+SHT3X_Data_Buffer[4])*100)/65535.0f; //可以得到相对湿度
//	printf("Lux:%d LUX Tem:%.2f Hum:%.2f,SHum:%d\r\n",Lux,Temperature,Humidity,Soil_Humidity);
}