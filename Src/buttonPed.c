
#include "buttonPed.h"
#include "main.h"
#include "stdbool.h"


void ButtonPed_Init(void)
{
//  GPIO_InitTypeDef ButtonPed_InitStruct = {0};

  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : T1_Pin T2_Pin T3_Pin T4_Pin */
//  ButtonPed_InitStruct.Pin = T1_Pin|T2_Pin|T3_Pin|T4_Pin;
//  ButtonPed_InitStruct.Mode = GPIO_MODE_INPUT;
//  ButtonPed_InitStruct.Pull = GPIO_PULLUP;
//  HAL_GPIO_Init(GPIOD, &ButtonPed_InitStruct);

}

void button_Read(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin1, uint16_t GPIO_Pin2, uint16_t GPIO_Pin3, uint16_t GPIO_Pin4)
{
  Key=(GPIOx->IDR & (GPIO_Pin1|GPIO_Pin2|GPIO_Pin3|GPIO_Pin4));

  if(Key==T0DEGER)
  {
	  durum=true;
  }
}
