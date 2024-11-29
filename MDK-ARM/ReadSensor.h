#ifndef __READSENSOR_H__
#define __READSENSOR_H__

#include "main.h"
#include "SHx.h"
#include "Led.h"
#include "BH1705.h"
#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "usart.h"


void Lora_Init();
void Sensor_Init();
void Sensor_Read();

#endif