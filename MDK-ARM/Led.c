#include "Led.h"


void Led_Init()
{
	static uint8_t temp=0;
	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==0)
	  {
		  HAL_Delay(10);
		  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==0)
		  {
			  temp++;
			  if(temp==3)temp=0;
			  HAL_GPIO_WritePin(GPIOC, RED_Pin|GREEN_Pin|BLUE_Pin, GPIO_PIN_SET);
		  }
		  while(!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13));
	  }
	if(temp==0)HAL_GPIO_WritePin(GPIOC,RED_Pin,GPIO_PIN_RESET);
	if(temp==1)HAL_GPIO_WritePin(GPIOC,GREEN_Pin,GPIO_PIN_RESET);
	if(temp==2)HAL_GPIO_WritePin(GPIOC,BLUE_Pin,GPIO_PIN_RESET);
}