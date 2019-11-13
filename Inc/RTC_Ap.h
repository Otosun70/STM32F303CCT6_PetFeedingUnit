/*
 * RTC_Ap.h
 *
 *  Created on: 10 Eki 2019
 *      Author: tosun_n
 */

#ifndef RTC_AP_H_
#define RTC_AP_H_

#include "string.h"
#include "stdbool.h"
#include "OLED.h"

   int8_t SaatAry[3];
   int8_t SaatAryNo;

   int8_t takvimAry[4];
   int8_t takvimAryNo;

void(*ayarlaPtr)(void);

void saat_alarm_Ayarlama(uint8_t yKonumu);

void saatAyarla();

void alarmAyarla();

void takvimAyarla();

void saatiAyarlama(uint8_t y);

void alarmAyarlama(uint8_t y);

void takvimiAyarlama(uint8_t y);

void KeySaatiAyarlama();

void KeyAlarmAyarlama();

void KeyTakvimiAyarlama();

void KeyServoKontrol();

void displaySelect();

void menuExit();

void kayitSorma(uint8_t x,uint8_t y);

bool alarmRead(void);

void alarmDurdur();

void takvimGoster();

void alarmGoster();

void alarmDeneme(uint8_t alarmDurdurmaKeyDegeri);


#endif /* RTC_AP_H_ */
