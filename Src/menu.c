
#include "include_Ap.h"



	menulistTypeDef anaMenu		={"ANA MENU"	,"Menu 1"       ,"Ledler"        ,"Ayarlar","Cikis"};
	menulistTypeDef beslemeMenu	={"MENU_1"		,"Servo"     	,"2. Satir"      ,"3. Satir"};
	menulistTypeDef kontrollerMenu	={"LEDLER"		,"Led 1"        ,"Led 2"         ,"Led 3"};
	menulistTypeDef menu3Menu	={"AYARLAR"		,"Saat"         ,"Takvim"        ,"Alarm"};
	menulistTypeDef acKapaMenu	={"AC/KAPAT"	,"Ac"           ,"Kapat"};


void BuildMenu(menuLevelsTypeDef *currentNode, menulistTypeDef *menuNode,OLED_COLOR color1,OLED_COLOR color2,OLED_COLOR color3,OLED_COLOR color4,
				void (*DoWork)(void) , menuLevelsTypeDef *prevNode, menuLevelsTypeDef *nextNode,menuLevelsTypeDef *upNode,menuLevelsTypeDef *downNode)
{
	currentNode->menuPtr 	= menuNode;
    currentNode->color1		= color1;
    currentNode->color2		= color2;
    currentNode->color3		= color3;
    currentNode->color4		= color4;
    currentNode->prev   	= prevNode;
    currentNode->next   	= nextNode;
    currentNode->up     	= upNode;
    currentNode->down   	= downNode;
    currentNode->DoWork 	= DoWork;
}


void Next(menuLevelsTypeDef **currentNode)
{
  if( (*currentNode) ->next != 0)
  (*currentNode) = (*currentNode)->next;
}

void Prev(menuLevelsTypeDef **currentNode)
{
  if((*currentNode)->prev != 0)
  (*currentNode) = (*currentNode)->prev;
}

void Up(menuLevelsTypeDef **currentNode)
{
  if((*currentNode)->up != 0)
  (*currentNode) = (*currentNode)->up;
}

void Down(menuLevelsTypeDef **currentNode)
{
  if((*currentNode)->DoWork != 0)
    (*currentNode)->DoWork();
  else if((*currentNode)->down != 0)
    (*currentNode) = (*currentNode)->down;
}


void Build_Menu()
{
	//			secenek		menu					renk					fonksiyon			önceki		sonraki			üst			alt
	//-----------------------------------------------------------------------------------------------------------------------------------
	  BuildMenu(&menu1M,	&anaMenu		,Black,	White,	White,	White,		0, 				&exitM,	&ledlerM, 		0, 			&menu11M);

	  BuildMenu(&menu11M,	&beslemeMenu		,Black,	White,	White,	White,		KeyServoKontrol,&menu13M,	&menu12M, 		&menu1M, 	0);
	  BuildMenu(&menu12M,	&beslemeMenu		,White,	Black,	White,	White,		0, 				&menu11M,	&menu13M, 		&menu1M, 	0);
	  BuildMenu(&menu13M,	&beslemeMenu		,White,	White,	Black,	White,		0,				&menu12M,	&menu11M,		&menu1M, 	0);

	  BuildMenu(&ledlerM,	&anaMenu		,White,	Black,	White,	White, 		0, 				&menu1M,	&ayarlarM, 		0, 			&led1M);

	  BuildMenu(&led1M,		&kontrollerMenu		,Black,	White,	White,	White,		0,				&led3M,		&led2M, 		&ledlerM, 	&on1M);
	  BuildMenu(&on1M,		&acKapaMenu		,Black,	White,	Black,	White, 		Led3_On,		&off1M,		&off1M, 		&led1M, 	0);
	  BuildMenu(&off1M,		&acKapaMenu		,White,	Black,	Black,	White,		Led3_Off, 		&on1M, 		&on1M,			&led1M, 	0);

	  BuildMenu(&led2M,		&kontrollerMenu		,White,	Black,	White,	White, 		0,			 	&led1M, 	&led3M, 		&ledlerM , 	&on2M);
	  BuildMenu(&on2M,		&acKapaMenu		,Black,	White,	Black,	White, 		Led4_On,		&off2M,		&off2M, 		&led2M, 	0);
	  BuildMenu(&off2M,		&acKapaMenu		,White,	Black,	Black,	White, 		Led4_Off, 		&on2M, 		&on2M,			&led2M, 	0);

	  BuildMenu(&led3M,		&kontrollerMenu		,White,	White,	Black,	White, 		0,			 	&led2M, 	&led1M,			&ledlerM, 	&on3M);
	  BuildMenu(&on3M,		&acKapaMenu		,Black,	White,	Black,	White, 		Led5_On,		&off3M,		&off3M, 		&led3M, 	0);
	  BuildMenu(&off3M,		&acKapaMenu		,White,	Black,	Black,	White, 		Led5_Off, 		&on3M, 		&on3M,			&led3M, 	0);

	  BuildMenu(&ayarlarM,	&anaMenu		,White,	White,	Black,	White,		0,				&ledlerM,	&exitM,		0, 			&saatM);

	  BuildMenu(&saatM,		&menu3Menu	,Black,	White,	White,	White,		KeySaatiAyarlama, 	&alarmM,	&takvimM, 		&ayarlarM, 	0);

	  BuildMenu(&takvimM,	&menu3Menu	,White,	Black,	White,	White,		KeyTakvimiAyarlama,	&saatM, 	&alarmM, 		&ayarlarM, 	0);

	  BuildMenu(&alarmM,	&menu3Menu	,White,	White,	Black,	White,		KeyAlarmAyarlama, 				&takvimM, 	&saatM,			&ayarlarM , 0);

	  BuildMenu(&exitM,		&anaMenu		,White,	White,	White,	Black,		menuExit, 		&ayarlarM,	&menu1M, 		0, 			0);



	  //Assign the current menu item the first item in the menu
	  currentM = &menu1M;

}



void Led3_On()
{
//HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,SET);
}

void Led3_Off()
{
//HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,RESET);
}

void Led4_On()
{
//HAL_GPIO_WritePin(LD4_GPIO_Port,LD4_Pin,SET);
}

void Led4_Off()
{
//HAL_GPIO_WritePin(LD4_GPIO_Port,LD4_Pin,RESET);
}

void Led5_On()
{
//HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,SET);
}

void Led5_Off()
{
//HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,RESET);
}


void ekranMenu(uint8_t y1)
{

	char ekranYer[16];
	OLED_Fill(Black);

	strcpy(ekranYer, currentM->menuPtr->menuAdi);
	OLED_SetCursor(30, y1);
	OLED_WriteString(ekranYer, Font_7x10, White);
	strcpy(ekranYer, currentM->menuPtr->satir1);
	OLED_SetCursor(0, y1+15);
	OLED_WriteString(ekranYer, Font_7x10, currentM->color1);
	strcpy(ekranYer, currentM->menuPtr->satir2);
	OLED_SetCursor(0, y1+25);
	OLED_WriteString(ekranYer, Font_7x10, currentM->color2);
	strcpy(ekranYer, currentM->menuPtr->satir3);
	OLED_SetCursor(0, y1+35);
	OLED_WriteString(ekranYer, Font_7x10, currentM->color3);
	strcpy(ekranYer, currentM->menuPtr->satir4);
	OLED_SetCursor(0, y1+45);
	OLED_WriteString(ekranYer, Font_7x10, currentM->color4);
}

void menuSistemi(uint8_t y) {

	if (durum) {

		switch (Key) {
		case T0DEGER:
			ekranMenu(y);
			break;

		case T1DEGER:
			Next(&currentM); //Check if there is a next node and then go there
			ekranMenu(y);
			durum = false;
			break;

		case T2DEGER:
			Prev(&currentM);
			ekranMenu(y);
			durum = false;
			break;

		case T3DEGER:
			Down(&currentM);
			ekranMenu(y);
			durum = false;
			break;

		case T4DEGER:
			Up(&currentM);
			ekranMenu(y);
			durum = false;
			break;
		default:
			;
		}
		OLED_DrawLine(0, y + 11, 110, y + 11, White);
	}

}

