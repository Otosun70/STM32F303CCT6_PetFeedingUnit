/*
 * timerAp.c
 *
 *  Created on: 7 Eki 2019
 *      Author: tosun_n
 */
#include "timerAp.h"
#include "main.h"
/*
void InitTimer14(void){
RCC->APB1ENR |= RCC_APB1ENR_TIM14EN; // Enable clock for TIM7
TIM14->CR1 &= ~CEN; // Disable TIM7 interrupt
TIM14->PSC = 256;
TIM14->ARR = 45000;
NVIC_EnableIRQ(TIM14_IRQn);
TIM14->DIER |= UIE; // Enable TIM7 interrupt
TIM14->CR1 |= CEN; // TIM7 enable
}


void TIM14_IRQHandler (void) {
TIM14->SR &= ~UIF; // Clear UIF
//HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

if(durumFlash)
{
	durumFlash=false;
}
else
{
	durumFlash=true;
}
}
*/
