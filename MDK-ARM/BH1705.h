#ifndef __BH1705_H__
#define __BH1705_H__

#include "main.h"

void GY30_WR_CMD(uint8_t cmd);//д����
void BH1750_Init(void);//BH1750��ʼ������
void GY30_READ_DATA(uint8_t data[]);//������
uint32_t BH1750_ReadLightIntensity(void);//BH1750��ȡ��ǿ��


#endif
