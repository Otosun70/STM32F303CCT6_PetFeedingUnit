/*
 * ADC_Ap.c
 *
 *  Created on: 12 Eki 2019
 *      Author: tosun_n
 */
#include "include_Ap.h"

extern DMA_HandleTypeDef hdm1_adc1;
extern ADC_HandleTypeDef hadc1;

extern uint16_t deger[4];
extern int potDeger2, tempDeger, batDeger;

char keyYer[14];

void ADC_DMA_degerOkuma() {
	HAL_ADC_Start_DMA(&hadc1, deger, 4);
	HAL_ADC_ConvHalfCpltCallback(&hadc1);
	HAL_ADC_Stop_DMA(&hadc1);
}

void pilGoster() {
	int pilDeger = (deger[0] / 4 - 3);

	OLED_SetCursor(111, 0);
	OLED_WriteChar((pilDeger), Font_16x6, White);
}

void ADC_degerleriGosterme() {
	OLED_SetCursor(0, 0);
	sprintf(keyYer, "%3d", (deger[1]));
	OLED_WriteString(keyYer, Font_7x10, White);
	OLED_SetCursor(0, 40);
	sprintf(keyYer, "%3d", (deger[2]));
	OLED_WriteString(keyYer, Font_7x10, White);
	OLED_SetCursor(0, 50);
	sprintf(keyYer, "%3d", (deger[3]));
	OLED_WriteString(keyYer, Font_7x10, White);
}

