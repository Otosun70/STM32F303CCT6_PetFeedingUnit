#include "OLED.h"
#include "string.h"

#define ABS(x)   ((x) > 0 ? (x) : -(x))
// Screenbuffer
static SSD1306_t OLED;

static uint8_t OLED_Buffer[OLED_WIDTH * OLED_HEIGHT / 8];
//
//  Send a byte to the command register
//
static void OLED_WriteCommand(uint8_t command)
{
	HAL_I2C_Mem_Write(&hi2c1,OLED_I2C_ADDR,0x00,1,&command,1,10);
}


//
//	Initialize the oled screen
//
uint8_t OLED_Init(void)
{	
	// Wait for the screen to boot
//	HAL_Delay(100);
	
	/* Init LCD */
	OLED_WriteCommand(OLED_Display_Off); //display off
	OLED_WriteCommand(OLED_Memory_Addressing_Set); //Set Memory Addressing Mode
	OLED_WriteCommand(OLED_Page_Addressing_Column_Higher_Set); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	OLED_WriteCommand(OLED_Page_Addressing_Page_Start_Set); //Set Page Start Address for Page Addressing Mode,0-7
	OLED_WriteCommand(OLED_Com_Output_Scan_Inc); //Set COM Output Scan Direction
	OLED_WriteCommand(OLED_Page_Addressing_Column_Lower_Set); //---set low column address
	OLED_WriteCommand(OLED_Page_Addressing_Column_Higher_Set); //---set high column address
	OLED_WriteCommand(OLED_Display_Start_Line_Set); //--set start line address
	OLED_WriteCommand(OLED_Constrast_Set); //--set contrast control register
	OLED_WriteCommand(0xFF);//Contrast degeri
	OLED_WriteCommand(0xA0); //--set segment re-map 0 to 127
	OLED_WriteCommand(OLED_Display_Normal); //--set normal display
	OLED_WriteCommand(OLED_Multiplex_Radio_Set); //--set multiplex ratio(1 to 64)
	OLED_WriteCommand(0x3F); //
	OLED_WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_WriteCommand(OLED_Display_Offset_Set); //-set display offset
	OLED_WriteCommand(0x00); //-not offset
	OLED_WriteCommand(OLED_Display_Oscillator_Frequency_Set); //--set display clock divide ratio/oscillator frequency
	OLED_WriteCommand(0xF0); //--set divide ratio
	OLED_WriteCommand(OLED_Precharge_Period_Set); //--set pre-charge period
	OLED_WriteCommand(0x22); //
	OLED_WriteCommand(OLED_Com_Pins_Set); //--set com pins hardware configuration
	OLED_WriteCommand(0x12);
	OLED_WriteCommand(OLED_VCOMH_Deselect_Level_Set); //--set vcomh
	OLED_WriteCommand(0x20); //0x20,0.77xVcc
	OLED_WriteCommand(OLED_Charge_Pump_Set); //--set DC-DC enable
	OLED_WriteCommand(0x14); //
	OLED_WriteCommand(OLED_Display_On); //--turn on SSD1306 panel
	
	// Clear screen
	OLED_Fill(Black);
	
	// Flush buffer to screen
	OLED_UpdateScreen();
	
	// Set default values for screen object
	OLED.CurrentX = 0;
	OLED.CurrentY = 0;
	
	OLED.Initialized = 1;
	
	return 1;
}

//
//  Fill the whole screen with the given color
//
void OLED_Fill(OLED_COLOR color) {
	/* Set memory */
	memset(OLED_Buffer, (color == Black) ? 0x00 : 0xFF, sizeof(OLED_Buffer));
}

void OLED_ToggleInvert(void) {
	uint16_t i;

	/* Toggle invert */
	OLED.Inverted = !OLED.Inverted;

	/* Do memory toggle */
	for (i = 0; i < sizeof(OLED_Buffer); i++) {
		OLED_Buffer[i] = ~OLED_Buffer[i];
	}
}


void OLED_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, OLED_COLOR c) {
	int16_t dx, dy, sx, sy, err, e2, i, tmp;

	/* Check for overflow */
	if (x0 >= OLED_WIDTH) {
		x0 = OLED_WIDTH - 1;
	}
	if (x1 >= OLED_WIDTH) {
		x1 = OLED_WIDTH - 1;
	}
	if (y0 >= OLED_HEIGHT) {
		y0 = OLED_HEIGHT - 1;
	}
	if (y1 >= OLED_HEIGHT) {
		y1 = OLED_HEIGHT - 1;
	}

	dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
	dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = ((dx > dy) ? dx : -dy) / 2;

	if (dx == 0) {
		if (y1 < y0) {
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}

		if (x1 < x0) {
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}

		/* Vertical line */
		for (i = y0; i <= y1; i++) {
			OLED_DrawPixel(x0, i, c);
		}

		/* Return from function */
		return;
	}

	if (dy == 0) {
		if (y1 < y0) {
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}

		if (x1 < x0) {
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}

		/* Horizontal line */
		for (i = x0; i <= x1; i++) {
			OLED_DrawPixel(i, y0, c);
		}

		/* Return from function */
		return;
	}

	while (1) {
		OLED_DrawPixel(x0, y0, c);
		if (x0 == x1 && y0 == y1) {
			break;
		}
		e2 = err;
		if (e2 > -dx) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		}
	}
}

void OLED_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, OLED_COLOR c) {
	/* Check input parameters */
	if (
		x >= OLED_WIDTH ||
		y >= OLED_HEIGHT
	) {
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((x + w) >= OLED_WIDTH) {
		w = OLED_WIDTH - x;
	}
	if ((y + h) >= OLED_HEIGHT) {
		h = OLED_HEIGHT - y;
	}

	/* Draw 4 lines */
	OLED_DrawLine(x, y, x + w, y, c);         /* Top line */
	OLED_DrawLine(x, y + h, x + w, y + h, c); /* Bottom line */
	OLED_DrawLine(x, y, x, y + h, c);         /* Left line */
	OLED_DrawLine(x + w, y, x + w, y + h, c); /* Right line */
}

void OLED_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, OLED_COLOR c) {
	uint8_t i;

	/* Check input parameters */
	if (
		x >= OLED_WIDTH ||
		y >= OLED_HEIGHT
	) {
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((x + w) >= OLED_WIDTH) {
		w = OLED_WIDTH - x;
	}
	if ((y + h) >= OLED_HEIGHT) {
		h = OLED_HEIGHT - y;
	}

	/* Draw lines */
	for (i = 0; i <= h; i++) {
		/* Draw lines */
		OLED_DrawLine(x, y + i, x + w, y + i, c);
	}
}

void OLED_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, OLED_COLOR color) {
	/* Draw lines */
	OLED_DrawLine(x1, y1, x2, y2, color);
	OLED_DrawLine(x2, y2, x3, y3, color);
	OLED_DrawLine(x3, y3, x1, y1, color);
}


void OLED_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, OLED_COLOR color) {
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
	curpixel = 0;

	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;

	if (x2 >= x1) {
		xinc1 = 1;
		xinc2 = 1;
	} else {
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {
		yinc1 = 1;
		yinc2 = 1;
	} else {
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay){
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	} else {
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++) {
		OLED_DrawLine(x, y, x3, y3, color);

		num += numadd;
		if (num >= den) {
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

void OLED_DrawCircle(int16_t x0, int16_t y0, int16_t r, OLED_COLOR c) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    OLED1_DrawPixel(x0, y0 + r, c);
    OLED1_DrawPixel(x0, y0 - r, c);
    OLED1_DrawPixel(x0 + r, y0, c);
    OLED1_DrawPixel(x0 - r, y0, c);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        OLED_DrawPixel(x0 + x, y0 + y, c);
        OLED_DrawPixel(x0 - x, y0 + y, c);
        OLED_DrawPixel(x0 + x, y0 - y, c);
        OLED_DrawPixel(x0 - x, y0 - y, c);

        OLED_DrawPixel(x0 + y, y0 + x, c);
        OLED_DrawPixel(x0 - y, y0 + x, c);
        OLED_DrawPixel(x0 + y, y0 - x, c);
        OLED_DrawPixel(x0 - y, y0 - x, c);
    }
}

void OLED_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, OLED_COLOR c) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    OLED_DrawPixel(x0, y0 + r, c);
    OLED_DrawPixel(x0, y0 - r, c);
    OLED_DrawPixel(x0 + r, y0, c);
    OLED_DrawPixel(x0 - r, y0, c);
    OLED_DrawLine(x0 - r, y0, x0 + r, y0, c);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        OLED_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, c);
        OLED_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, c);

        OLED_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, c);
        OLED_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, c);
    }
}




//
//  Write the screenbuffer with changed to the screen
//
void OLED_UpdateScreen(void) 
{
	uint8_t i;
	
	for (i = 0; i < 8; i++) {
		OLED_WriteCommand(0xB0 + i);
		OLED_WriteCommand(0x00);
		OLED_WriteCommand(0x10);

		HAL_I2C_Mem_Write(&hi2c1,OLED_I2C_ADDR,0x40,1,&OLED_Buffer[OLED_WIDTH * i],OLED_WIDTH,100);
	}
}

//
//	Draw one pixel in the screenbuffer
//	X => X Coordinate
//	Y => Y Coordinate
//	color => Pixel color
//

void OLED_DrawPixel(uint8_t x, uint8_t y, OLED_COLOR color) {
	if (
		x >= OLED_WIDTH ||
		y >= OLED_HEIGHT
	) {
		/* Error */
		return;
	}

	/* Check if pixels are inverted */
	if (OLED.Inverted) {
		color = (OLED_COLOR)!color;
	}

	/* Set color */
	if (color == White) {
		OLED_Buffer[x + (y / 8) * OLED_WIDTH] |= 1 << (y % 8);
	} else {
		OLED_Buffer[x + (y / 8) * OLED_WIDTH] &= ~(1 << (y % 8));
	}
}


//
//  Draw 1 char to the screen buffer
//	ch 		=> char om weg te schrijven
//	Font 	=> Font waarmee we gaan schrijven
//	color 	=> Black or White
//
char OLED_WriteChar(char ch, FontDef Font, OLED_COLOR color)
{
	uint32_t i, b, j;
	
	// Check remaining space on current line
	if (OLED_WIDTH <= (OLED.CurrentX + Font.FontWidth) ||
		OLED_HEIGHT <= (OLED.CurrentY + Font.FontHeight))
	{
		// Not enough space on current line
		return 0;
	}
	
	// Use the font to write
	for (i = 0; i < Font.FontHeight; i++)
	{
		b = Font.data[(ch - 32) * Font.FontHeight + i];
		for (j = 0; j < Font.FontWidth; j++)
		{
			if ((b << j) & 0x8000) 
			{
				OLED_DrawPixel(OLED.CurrentX + j, (OLED.CurrentY + i), (OLED_COLOR) color);
			} 
			else 
			{
				OLED_DrawPixel(OLED.CurrentX + j, (OLED.CurrentY + i), (OLED_COLOR)!color);
			}
		}
	}
	
	// The current space is now taken
	OLED.CurrentX += Font.FontWidth;
	
	// Return written char for validation
	return ch;
}

//
//  Write full string to screenbuffer
//
char OLED_WriteString(char* str, FontDef Font, OLED_COLOR color)
{
	// Write until null-byte
	while (*str) 
	{
		if (OLED_WriteChar(*str, Font, color) != *str)
		{
			// Char could not be written
			return *str;
		}
		
		// Next char
		str++;
	}
	
	// Everything ok
	return *str;
}

//
//	Position the cursor
//

void OLED_SetCursor(uint8_t x, uint8_t y) 
{
	OLED.CurrentX = x;
	OLED.CurrentY = y;
}

