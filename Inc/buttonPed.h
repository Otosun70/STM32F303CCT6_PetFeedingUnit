#ifndef __BUTTONPED_H
#define __BUTTONPED_H


#include "stdio.h"
#include "stdbool.h"
#include "stm32f3xx_hal.h"

#define T1DEGER 		208
#define T2DEGER 		224
#define T3DEGER 		112
#define T4DEGER 		176
#define T3VT4DEGER 		48
#define T4VT2DEGER 		160
#define T0DEGER 		240
#define TAKVIMI_AYARLAMA 66
#define ALARM_AYARLAMA 	67
#define SERVO_KONTROL 	68
#define SAATI_AYARLAMA 	65
#define MENU_SISTEMI 	T3VT4DEGER
#define MENUEXIT 		T4VT2DEGER
#define GIRIS_EKRANI 	T4VT2DEGER

uint8_t Key;
uint8_t displaySelectKey;

bool durum,displayClean,durumFlash,kayitOnayDurum;

void ButtonPed_Init(void);

void button_Read(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin1,uint16_t GPIO_Pin2,uint16_t GPIO_Pin3,uint16_t GPIO_Pin4);



#endif /* __BUTTONPED_H */
