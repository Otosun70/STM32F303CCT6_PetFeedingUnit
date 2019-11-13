/*
 * RTC_Ap.c
 *
 *  Created on: 10 Eki 2019
 *      Author: tosun_n
 */
#include "include_Ap.h"

void saatAyarla()
{
	extern RTC_HandleTypeDef hrtc;
	RTC_TimeTypeDef sTime;
//	sTime.TimeFormat=RTC_HOURFORMAT12_AM;
	sTime.Hours=SaatAry[0];
	sTime.Minutes=SaatAry[1];
	sTime.Seconds=SaatAry[2];
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		Error_Handler();
	}
}

void alarmAyarla()
{
	extern RTC_HandleTypeDef hrtc;
	RTC_AlarmTypeDef sAlarm;
//	sAlarm.AlarmTime.TimeFormat=RTC_HOURFORMAT12_AM;
	sAlarm.AlarmTime.Hours=SaatAry[0];
	sAlarm.AlarmTime.Minutes=SaatAry[1];
	sAlarm.AlarmTime.Seconds=SaatAry[2];
//	sAlarm.AlarmTime.SubSeconds = 0;
//	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
//	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
//	sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
//	sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
//	sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY;
//	sAlarm.AlarmDateWeekDay = 5;
	sAlarm.Alarm = RTC_ALARM_A;

	if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

void takvimAyarla()
{
	extern RTC_HandleTypeDef hrtc;
	RTC_DateTypeDef sDate ;

	sDate.Date =takvimAry[0];
	sDate.Month =takvimAry[1];
	sDate.Year =takvimAry[2];
	sDate.WeekDay = takvimAry[3];

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
}

void saatiAyarlama(uint8_t y)
{
	ayarlaPtr=&saatAyarla;
	saat_alarm_Ayarlama(y);
}

void saat_alarm_Ayarlama(uint8_t yKonumu) {

char saatYer[16];
	if (durum) {

		switch (Key) {
		case T3DEGER:
			durum = false;
			if(kayitOnayDurum)
			{
				(ayarlaPtr)();
				displaySelectKey=MENU_SISTEMI;
				SaatAryNo=0;
				displayClean=true;
				kayitOnayDurum=false;
			}
			else	SaatAryNo ++;

			if(SaatAryNo ==3)
			{
				kayitOnayDurum=true;
			}

			break;

		case T4DEGER:
			durum = false;
			if(kayitOnayDurum)
			{
				displaySelectKey=MENU_SISTEMI;
				SaatAryNo=0;
				displayClean=true;
				kayitOnayDurum=false;
			}
			else	SaatAryNo --;

			if(SaatAryNo < 0)
			{
				SaatAryNo=2;
			}

			break;

		case T1DEGER:
			durum = false;
			SaatAry[SaatAryNo] ++;
			if(SaatAryNo==0)
			{
				if(SaatAry[SaatAryNo]>23)
				{
					SaatAry[SaatAryNo]=0;
				}
			}
			else if(SaatAryNo!=0)
			{
				if(SaatAry[SaatAryNo]>59)
				{
					SaatAry[SaatAryNo]=0;
				}
			}
			break;

		case T2DEGER:
			durum = false;
			SaatAry[SaatAryNo] --;
			if(SaatAryNo==0)
			{
				if(SaatAry[SaatAryNo]<0)
				{
					SaatAry[SaatAryNo]=23;
				}
			}
			else if(SaatAryNo!=0)
			{
				if(SaatAry[SaatAryNo]<0)
				{
					SaatAry[SaatAryNo]=59;
				}
			}
			break;

		default:
			;
		}
	}
	if(kayitOnayDurum)
	{
		kayitSorma(10,yKonumu);
	}
	sprintf(saatYer,"%02d:%02d:%02d",SaatAry[0],SaatAry[1],SaatAry[2]);
	OLED_SetCursor(10, yKonumu);
	OLED_WriteString(saatYer, Font_11x18, White);
	if(durumFlash)
	{
	OLED_SetCursor(SaatAryNo*33+10, yKonumu);
	OLED_WriteString("  ", Font_11x18, White);
	}
}

void alarmAyarlama(uint8_t y) {

	ayarlaPtr=&alarmAyarla;
	saat_alarm_Ayarlama(y);
}

void takvimiAyarlama(uint8_t y)
{
	char takvimYer[12];
 	char* weekDay[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
			"Saturday", "Sunday"};

		if (durum) {

			switch (Key) {
			case T3DEGER:
				durum = false;

				if(kayitOnayDurum)
				{
					takvimAyarla();
					displaySelectKey=MENU_SISTEMI;
					takvimAryNo=0;
					displayClean=true;
					kayitOnayDurum=false;
				}
				else	takvimAryNo ++;

				if(takvimAryNo ==4)
				{
					kayitOnayDurum=true;
				}
				break;

			case T4DEGER:
				durum = false;
				if(kayitOnayDurum)
				{
					displaySelectKey=MENU_SISTEMI;
					takvimAryNo=0;
					displayClean=true;
					kayitOnayDurum=false;
				}
				else	takvimAryNo --;

				if(takvimAryNo < 0)
				{
					takvimAryNo=3;
				}

				break;

			case T1DEGER:
				durum = false;
				takvimAry[takvimAryNo] ++;
				if(takvimAryNo==0)
				{
					if(takvimAry[takvimAryNo]>31)
					{
						takvimAry[takvimAryNo]=1;
					}
				}
				else if(takvimAryNo==1)
				{
					if(takvimAry[takvimAryNo]>12)
					{
						takvimAry[takvimAryNo]=1;
					}
				}
				else if(takvimAryNo==2)
				{
					if(takvimAry[takvimAryNo]>99)
					{
						takvimAry[takvimAryNo]=0;
					}
				}
				else if(takvimAryNo==3)
				{
					if(takvimAry[takvimAryNo]>7)
					{
						takvimAry[takvimAryNo]=1;
					}
				}
				break;

			case T2DEGER:
				durum = false;
				takvimAry[takvimAryNo] --;
				if(takvimAryNo==0)
				{
					if(takvimAry[takvimAryNo]<1)
					{
						takvimAry[takvimAryNo]=31;
					}
				}
				else if(takvimAryNo==1)
				{
					if(takvimAry[takvimAryNo]<1)
					{
						takvimAry[takvimAryNo]=12;
					}
				}
				else if(takvimAryNo==2)
				{
					if(takvimAry[takvimAryNo]<0)
					{
						takvimAry[takvimAryNo]=99;
					}
				}
				else if(takvimAryNo==3)
				{
					if(takvimAry[takvimAryNo]<1)
					{
						takvimAry[takvimAryNo]=7;
					}
				}
				break;
				break;

			default:
				;
			}
		}
		if(kayitOnayDurum)
		{
			kayitSorma(10,y+10);
		}

		sprintf(takvimYer,"%02d-%02d-20%02d",takvimAry[0],takvimAry[1],takvimAry[2]);
		OLED_SetCursor(0, y);
		OLED_WriteString(takvimYer, Font_11x18, White);
		OLED_SetCursor(30, y+20);
		OLED_WriteString(weekDay[takvimAry[3]-1], Font_7x10, White);  //
		if(durumFlash)
		{
			if(takvimAryNo<2)
			{
				OLED_SetCursor(takvimAryNo*33, y);
				OLED_WriteString("  ", Font_11x18, White);
			}
			else if(takvimAryNo==2)
			{
				OLED_SetCursor(takvimAryNo*33+22, y);
				OLED_WriteString("  ", Font_11x18, White);
			}
			else if(takvimAryNo==3)
			{
				OLED_SetCursor(30, y+20);
				OLED_WriteString("            ", Font_7x10, White);
			}

		}
}
/*Geçerli saat bilgisini okuyup saat ayar ekranına yönlendirecek Key1 değerini ayarlar */
void KeySaatiAyarlama()
{
	extern RTC_HandleTypeDef hrtc;
	RTC_TimeTypeDef sTimeGet;
	HAL_RTC_GetTime(&hrtc, &sTimeGet, RTC_FORMAT_BIN);

	SaatAry[0]=sTimeGet.Hours;
	SaatAry[1]=sTimeGet.Minutes;
	SaatAry[2]=sTimeGet.Seconds;

	displaySelectKey=SAATI_AYARLAMA;
	SaatAryNo=0;
	displayClean=true;

}
/*Geçerli alarm bilgisini okuyup alarm ayar ekranına yönlendirecek Key1 değerini ayarlar */
void KeyAlarmAyarlama()
{
	extern RTC_HandleTypeDef hrtc;
	RTC_AlarmTypeDef sAlarmGet;
	HAL_RTC_GetAlarm(&hrtc, &sAlarmGet,RTC_ALARM_A, RTC_FORMAT_BIN);

	SaatAry[0]=sAlarmGet.AlarmTime.Hours;
	SaatAry[1]=sAlarmGet.AlarmTime.Minutes;
	SaatAry[2]=sAlarmGet.AlarmTime.Seconds;

	displaySelectKey=ALARM_AYARLAMA;
	SaatAryNo=0;
	displayClean=true;

}
/*Geçerli takvim bilgisini okuyup saat ayar ekranına yönlendirecek Key1 değerini ayarlar */

void KeyTakvimiAyarlama()
{
	extern RTC_HandleTypeDef hrtc;
	RTC_DateTypeDef sDateGet;
	HAL_RTC_GetDate(&hrtc, &sDateGet, RTC_FORMAT_BIN);

	takvimAry[0]=sDateGet.Date;
	takvimAry[1]=sDateGet.Month;
	takvimAry[2]=sDateGet.Year;
	takvimAry[3]=sDateGet.WeekDay;

	displaySelectKey=TAKVIMI_AYARLAMA;
	takvimAryNo=0;
	displayClean=true;
}

void KeyServoKontrol()
{
	displaySelectKey=SERVO_KONTROL;
	displayClean=true;
}
/*Ekranda gösterilecek unsurları Key1 değerine göre seçer */
void displaySelect()
{

	button_Read(GPIOB,KEY_1_Pin,KEY_2_Pin,KEY_3_Pin,KEY_4_Pin); /*Menu ekranına geçirecek kısayol tuş kombinasyonunu algılayıp Key1 değerine aktarır*/
	if(Key==MENU_SISTEMI)
	{
		displaySelectKey=Key;
		displayClean=true;
	}
	switch(displaySelectKey)
	{
	case MENU_SISTEMI :
		if(displayClean)
		{
		displayClean=false;
		OLED_Fill(Black);
		}
//		alarmDurdur();
		menuSistemi(6);
		break;

	case SAATI_AYARLAMA:
		if(displayClean)
		{
		displayClean=false;
		OLED_Fill(Black);
		}
		saatiAyarlama(30);
		break;
	case TAKVIMI_AYARLAMA:
		if(displayClean)
		{
		displayClean=false;
		OLED_Fill(Black);
		}
		takvimiAyarlama(20);
		break;
	case ALARM_AYARLAMA:
		if(displayClean)
		{
		displayClean=false;
		OLED_Fill(Black);
		}
		alarmAyarlama(20);
		break;

	case GIRIS_EKRANI:
		if(displayClean)
		{
		displayClean=false;
		OLED_Fill(Black);
		}
		alarmGoster();
		takvimGoster();
	//	ADC_degerleriGosterme();
		break;

	case SERVO_KONTROL:
		if(displayClean)
		{
		displayClean=false;
		OLED_Fill(Black);
		}
		servoKontrol();
//		takvimGoster();

		break;

	}
}

void menuExit()
{
	displaySelectKey=MENUEXIT;
	currentM = &menu1M;
	displayClean=true;
}

void kayitSorma(uint8_t x1,uint8_t y1)
{
	if(durumFlash)
	{
		OLED_SetCursor(x1, y1+20);
		OLED_WriteString("Kaydedilsin mi?", Font_7x10, White);
	}
	else
	{
		OLED_SetCursor(x1, y1+20);
		OLED_WriteString("               ", Font_7x10, White);
	}
}

bool alarmRead(void)
{
	return ((RTC->ISR & RTC_ISR_ALRAF_Msk)>> RTC_ISR_ALRAF_Pos);
}

void alarmDurdur()
{
	RTC->ISR &=~RTC_ISR_ALRAF;
}

void alarmDeneme(uint8_t alarmDurdurmaKeyDegeri)
{
	if(Key==alarmDurdurmaKeyDegeri)
	{
		alarmDurdur();
	}

	if(alarmRead())
	{
//		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,SET);
	}
	else
	{
//		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,RESET);
	}
}

void alarmGoster()
{
	char aShowAlarm[16];
	extern RTC_HandleTypeDef hrtc;

	RTC_AlarmTypeDef sAlarmGet;

	/* Get the RTC current Time */
	HAL_RTC_GetAlarm(&hrtc, &sAlarmGet,RTC_ALARM_A, RTC_FORMAT_BIN);

	/* Display time Format : hh:mm:ss */
	sprintf(aShowAlarm, "%2d:%02d:%02d", sAlarmGet.AlarmTime.Hours, sAlarmGet.AlarmTime.Minutes, sAlarmGet.AlarmTime.Seconds);
	OLED_SetCursor(30, 0);
	OLED_WriteString(aShowAlarm, Font_7x10, White);
}

void saatGoster()
{
	char aShowTime[16];
	extern RTC_HandleTypeDef hrtc;

	RTC_TimeTypeDef sTimeGet;
	RTC_DateTypeDef sDateGet;

	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &sTimeGet, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDateGet, RTC_FORMAT_BIN);

	/* Display time Format : hh:mm:ss */
	sprintf(aShowTime, "%2d:%02d:%02d", sTimeGet.Hours, sTimeGet.Minutes, sTimeGet.Seconds);
	OLED_SetCursor(30, 0);
	OLED_WriteString(aShowTime, Font_7x10, White);
}

void takvimGoster()
{
	char aShowDate[15];
	char aShowTime[15];

	extern RTC_HandleTypeDef hrtc;

	RTC_TimeTypeDef sTimeGet;
	RTC_DateTypeDef sDateGet;

//	  const char* weekD[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", "??"};
	char* weekDay[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
			"Saturday", "Sunday"};

	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &sTimeGet, RTC_FORMAT_BIN);
	/* Display time Format : hh:mm:ss */
	sprintf(aShowTime, "%2d:%02d:%02d", sTimeGet.Hours, sTimeGet.Minutes,
			sTimeGet.Seconds);
	OLED_SetCursor(14, 16);
	OLED_WriteString(aShowTime, Font_11x18, White);

	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &sDateGet, RTC_FORMAT_BIN);
	/* Display date Format : mm-dd-yy */
	sprintf(aShowDate, "%02d-%02d-%2d", sDateGet.Date, sDateGet.Month,
			2000 + sDateGet.Year);
	OLED_SetCursor(25, 40);
	OLED_WriteString(aShowDate, Font_7x10, White);
	OLED_SetCursor(30, 53);
	OLED_WriteString(weekDay[sDateGet.WeekDay-1], Font_7x10, White);  //
}
