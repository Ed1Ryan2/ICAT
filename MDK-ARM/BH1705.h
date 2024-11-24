#ifndef __BH1705_H__
#define __BH1705_H__

#include "main.h"

void GY30_WR_CMD(uint8_t cmd);//写命令
void BH1750_Init(void);//BH1750初始化函数
void GY30_READ_DATA(uint8_t data[]);//读数据
uint32_t BH1750_ReadLightIntensity(void);//BH1750获取光强度


#endif
