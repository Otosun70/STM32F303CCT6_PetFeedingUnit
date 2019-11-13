
#ifndef __MENU_H
#define __MENU_H

#include "string.h"
#include "stdbool.h"
#include "OLED.h"

void Build_Menu();

void menuSistemi(uint8_t y);

void ekranMenu(uint8_t y);

void Led3_On();

void Led3_Off();

void Led4_On();

void Led4_Off();

void Led5_On();

void Led5_Off();



	typedef struct {
				char menuAdi[10];
				char satir1[10];
				char satir2[10];
				char satir3[10];
				char satir4[10];
}menulistTypeDef;

	menulistTypeDef anaMenu, menu1Menu,ledlerMenu,ayarlarMenu,acKapaMenu, *menuPtr;


   typedef struct level{
			   menulistTypeDef *menuPtr;
			   OLED_COLOR color1;
			   OLED_COLOR color2;
			   OLED_COLOR color3;
			   OLED_COLOR color4;
			   struct level *next;
			   struct level *prev;
			   struct level *down;
			   struct level *up;
			   void (*DoWork)(void);
}menuLevelsTypeDef;

   menuLevelsTypeDef menu1M,menu11M,menu12M,menu13M,ledlerM,led1M,led2M,led3M,ayarlarM,saatM,takvimM, alarmM, on1M, off1M, on2M ,off2M, on3M, off3M,exitM, *currentM;


#endif /* __MENU_H */
