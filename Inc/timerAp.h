/*
 * timerAp.h
 *
 *  Created on: 7 Eki 2019
 *      Author: tosun_n
 */

#ifndef TIMERAP_H_
#define TIMERAP_H_
#include "stm32f3xx_hal.h"
#include "stdbool.h"

//Timer7 Prescaler :550; Preload = 65455-1;
// Actual Interrupt Time = 1000 ms
#define UIE 0x00000001 // Update interrupt enable
#define CEN 0x00000001 // Counter enable
#define UIF 0x00000001 // Update interrupt flag
//#define RCC_APB1ENR_TIM7EN 0x00000020
extern bool durumFlash;

void InitTimer14(void);
void TIM14_IRQHandler (void);



#endif /* TIMERAP_H_ */
