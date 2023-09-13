#include "Drivers/display/Inc/driver.h"


#define swap(a, b) { int16_t t = a; a = b; b = t; }

volatile uint16_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH	 = ILI9341_SCREEN_WIDTH;





/* Send command (char) to LCD */
void ILI9341_Write_Command(uint8_t Command)
{
	DISP_DC_CMD;
	HAL_SPI_Transmit(&DISP_SPI_PTR, &Command, sizeof(Command), HAL_MAX_DELAY);
}

/* Send Data (char) to LCD */
void ILI9341_Write_Data(uint8_t Data)
{
	DISP_DC_DATA;
	HAL_SPI_Transmit(&DISP_SPI_PTR, &Data, sizeof(Data), HAL_MAX_DELAY);
}
/* Send Large Data (char) to LCD */
void ILI9341_Write_Large_Data(uint8_t *Data, uint8_t size_Data)
{
	DISP_DC_DATA;
	while(size_Data > 0) 
    {
	    uint16_t chunk_size = size_Data > 32768 ? 32768 : size_Data;
	    HAL_SPI_Transmit(&DISP_SPI_PTR, Data, chunk_size, HAL_MAX_DELAY);
	    Data += chunk_size;
	    size_Data -= chunk_size;
	}
}
/*HARDWARE RESET*/
void ILI9341_Reset(void)
{
	DISP_RST_RESET;
	HAL_Delay(5);
	DISP_RST_WORK;
}


/*Ser rotation of the screen - changes x0 and y0*/
void ILI9341_Set_Rotation(uint8_t Rotation)
{
	DISP_CS_SELECT;
	ILI9341_Write_Command(0x36);
	switch(Rotation)
	{
		case SCREEN_VERTICAL_1:
			ILI9341_Write_Data(0x40|0x08);
			LCD_WIDTH = 240;
			LCD_HEIGHT = 320;
			break;
		case SCREEN_HORIZONTAL_1:
			ILI9341_Write_Data(0x20|0x08);
			LCD_WIDTH  = 320;
			LCD_HEIGHT = 240;
			break;
		case SCREEN_VERTICAL_2: //this
			ILI9341_Write_Data(0x80|0x08);
			LCD_WIDTH  = 240;
			LCD_HEIGHT = 320;
			break;
		case SCREEN_HORIZONTAL_2:
			ILI9341_Write_Data(0x40|0x80|0x20|0x08);
			LCD_WIDTH  = 320;
			LCD_HEIGHT = 240;
			break;
		default:
			break;
	}
	DISP_CS_UNSELECT;
}


/*Initialize LCD display*/
void ILI9341_Init(void)
{
	//DISP_RST_WORK; /*Enable LCD display*/
	DISP_CS_SELECT; /* Initialize SPI */
	ILI9341_Reset();


	//SOFTWARE RESET
	ILI9341_Write_Command(0x01);
	HAL_Delay(1000);

	//POWER CONTROL A
	ILI9341_Write_Command(0xCB);
	ILI9341_Write_Data(0x39);
	ILI9341_Write_Data(0x2C);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x34);
	ILI9341_Write_Data(0x02);

	//POWER CONTROL B
	ILI9341_Write_Command(0xCF);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0xC1);
	ILI9341_Write_Data(0x30);

	//DRIVER TIMING CONTROL A
	ILI9341_Write_Command(0xE8);
	ILI9341_Write_Data(0x85);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x78);

	//DRIVER TIMING CONTROL B
	ILI9341_Write_Command(0xEA);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x00);

	//POWER ON SEQUENCE CONTROL
	ILI9341_Write_Command(0xED);
	ILI9341_Write_Data(0x64);
	ILI9341_Write_Data(0x03);
	ILI9341_Write_Data(0x12);
	ILI9341_Write_Data(0x81);

	//PUMP RATIO CONTROL
	ILI9341_Write_Command(0xF7);
	ILI9341_Write_Data(0x20);

	//POWER CONTROL,VRH[5:0]
	ILI9341_Write_Command(0xC0);
	ILI9341_Write_Data(0x10);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	ILI9341_Write_Command(0xC1);
	ILI9341_Write_Data(0x10);

	//VCM CONTROL
	ILI9341_Write_Command(0xC5);
	ILI9341_Write_Data(0x3E);
	ILI9341_Write_Data(0x28);

	//VCM CONTROL 2
	ILI9341_Write_Command(0xC7);
	ILI9341_Write_Data(0x86);

	//MEMORY ACCESS CONTROL
	ILI9341_Write_Command(0x36);
	ILI9341_Write_Data(0x48);

	//PIXEL FORMAT
	ILI9341_Write_Command(0x3A);
	ILI9341_Write_Data(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	ILI9341_Write_Command(0xB1);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x18);

	//DISPLAY FUNCTION CONTROL
	ILI9341_Write_Command(0xB6);
	ILI9341_Write_Data(0x08);
	ILI9341_Write_Data(0x82);
	ILI9341_Write_Data(0x27);

	//3GAMMA FUNCTION DISABLE
	ILI9341_Write_Command(0xF2);
	ILI9341_Write_Data(0x00);

	//GAMMA CURVE SELECTED
	ILI9341_Write_Command(0x26);
	ILI9341_Write_Data(0x01);

	//POSITIVE GAMMA CORRECTION
	ILI9341_Write_Command(0xE0);
	ILI9341_Write_Data(0x0F);
	ILI9341_Write_Data(0x31);
	ILI9341_Write_Data(0x2B);
	ILI9341_Write_Data(0x0C);
	ILI9341_Write_Data(0x0E);
	ILI9341_Write_Data(0x08);
	ILI9341_Write_Data(0x4E);
	ILI9341_Write_Data(0xF1);
	ILI9341_Write_Data(0x37);
	ILI9341_Write_Data(0x07);
	ILI9341_Write_Data(0x10);
	ILI9341_Write_Data(0x03);
	ILI9341_Write_Data(0x0E);
	ILI9341_Write_Data(0x09);
	ILI9341_Write_Data(0x00);

	//NEGATIVE GAMMA CORRECTION
	ILI9341_Write_Command(0xE1);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x0E);
	ILI9341_Write_Data(0x14);
	ILI9341_Write_Data(0x03);
	ILI9341_Write_Data(0x11);
	ILI9341_Write_Data(0x07);
	ILI9341_Write_Data(0x31);
	ILI9341_Write_Data(0xC1);
	ILI9341_Write_Data(0x48);
	ILI9341_Write_Data(0x08);
	ILI9341_Write_Data(0x0F);
	ILI9341_Write_Data(0x0C);
	ILI9341_Write_Data(0x31);
	ILI9341_Write_Data(0x36);
	ILI9341_Write_Data(0x0F);

	//EXIT SLEEP
	ILI9341_Write_Command(0x11);
	HAL_Delay(120);
	ILI9341_Write_Command(0x29);

	//STARTING ROTATION
	ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
	DISP_CS_UNSELECT;
}

/* Set Address - Location block - to draw into */
void ILI9341_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
    ILI9341_Write_Command(0x2A); // CASET
    {
        uint8_t data[] = { (X1 >> 8) & 0xFF, X1 & 0xFF, (X2 >> 8) & 0xFF, X2 & 0xFF };
        ILI9341_Write_Large_Data(data, sizeof(data));
    }

// row address set
    ILI9341_Write_Command(0x2B); // RASET
    {
        uint8_t data[] = { (Y1 >> 8) & 0xFF, Y1 & 0xFF, (Y2 >> 8) & 0xFF, Y2 & 0xFF };
        ILI9341_Write_Large_Data(data, sizeof(data));
    }
    // write to RAM
    ILI9341_Write_Command(0x2C);
}


/*Sends single pixel colour information to LCD*/
void ILI9341_Draw_Colour(uint16_t Colour)
{
	DISP_DC_DATA;
    uint8_t data[] = { Colour >> 8, Colour & 0xFF };
    HAL_SPI_Transmit(&DISP_SPI_PTR, data, 2, HAL_MAX_DELAY);
}

/*Sends block colour information to LCD*/
void ILI9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size)
{
	DISP_DC_DATA;
    uint8_t data[] = { Colour >> 8, Colour & 0xFF };

	while(Size > 0)
	{
        HAL_SPI_Transmit(&DISP_SPI_PTR, data, 2, HAL_MAX_DELAY);
		Size--;
	}
}


/* Draw filling rectangle */
void draw_fill_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    if((x1 >= LCD_WIDTH) || 
       (y1 >= LCD_HEIGHT) || 
       (x2 >= LCD_WIDTH) || 
       (y2 >= LCD_HEIGHT)) 
            return;
	if(x1>x2) swap(x1,x2);
	if(y1>y2) swap(y1,y2);

    DISP_CS_SELECT;
    ILI9341_Set_Address(x1, y1, x2, y2);
    ILI9341_Draw_Colour_Burst(color,(x2-x1+1)*(y2-y1+1));
    //uint8_t data[] = { color >> 8, color & 0xFF };
    //DISP_DC_DATA;
    //for(uint32_t i = 0; i < (x2-x1+1)*(y2-y1+1); i++)
    //{
    //      HAL_SPI_Transmit(&DISP_SPI_PTR, data, 2, HAL_MAX_DELAY);
    //}
	DISP_CS_UNSELECT;
}

/* Filling screen */
void fill_screen(uint16_t Colour)
{
        draw_fill_rect(0,0,LCD_WIDTH-1,LCD_HEIGHT-1,Colour);
}



//DRAW PIXEL AT XY POSITION WITH SELECTED COLOUR
void draw_pixel(uint16_t X, uint16_t Y, uint16_t Colour)
{
        draw_fill_rect(X,Y,X,Y,Colour);
}


void draw_hor_line(uint16_t X, uint16_t Y, uint16_t leght, uint16_t Colour)
{
        draw_fill_rect(X,Y,X+leght,Y,Colour);
}
void draw_ver_line(uint16_t X, uint16_t Y, uint16_t leght, uint16_t Colour)
{
        draw_fill_rect(X,Y,X,Y+leght,Colour);
}



void write_char_270(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
    uint32_t i, b, j;

    DISP_CS_SELECT;
    ILI9341_Set_Address(x, y, x + font.height - 1, y + font.width - 1);

    for(i = font.width - 1; i >= 0 && i < font.width; i--)
    {

        for(j = 0; j < font.height; j++)
        {
            b = font.data[(ch - 32) * font.height + j];

            if((b << i) & 0x8000)
            {
                ILI9341_Write_Data(color >> 8);
                ILI9341_Write_Data(color & 0xFF);
            }
            else
            {
                ILI9341_Write_Data(bgcolor >> 8);
                ILI9341_Write_Data(bgcolor & 0xFF);
            }
        }
    }
	DISP_CS_UNSELECT;
}

void write_char_180(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
    uint32_t i, b, j;

    DISP_CS_SELECT;
    ILI9341_Set_Address(x, y, x + font.width - 1, y + font.height - 1);

    for(i = font.height - 1; i >= 0 && i < font.height; i--)
    {
        b = font.data[(ch - 32) * font.height + i];

        for(j = font.width - 1; j >= 0 && j < font.width; j--)
        {
            if((b << j) & 0x8000)
            {
                ILI9341_Write_Data(color >> 8);
                ILI9341_Write_Data(color & 0xFF);
            }
            else
            {
                ILI9341_Write_Data(bgcolor >> 8);
                ILI9341_Write_Data(bgcolor & 0xFF);
            }
        }
    }
	DISP_CS_UNSELECT;
}
void write_char_90(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
    uint32_t i, b, j;

    DISP_CS_SELECT;
    ILI9341_Set_Address(x, y, x + font.height - 1, y + font.width - 1);

    for(i = 0; i < font.width; i++)
    {

        for(j = font.height - 1; j >= 0 && j < font.height; j--)
        {
            b = font.data[(ch - 32) * font.height + j];

            if((b << i) & 0x8000)
            {
                ILI9341_Write_Data(color >> 8);
                ILI9341_Write_Data(color & 0xFF);
            }
            else
            {
                ILI9341_Write_Data(bgcolor >> 8);
                ILI9341_Write_Data(bgcolor & 0xFF);
            }
        }
    }
	DISP_CS_UNSELECT;
}
// Вывод символа
void write_char_0(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
    uint32_t i, b, j;

    DISP_CS_SELECT;
    ILI9341_Set_Address(x, y, x + font.width - 1, y + font.height - 1);

    for(i = 0; i < font.height; i++)
    {
        b = font.data[(ch - 32) * font.height + i];

        for(j = 0; j < font.width; j++)
        {
            if((b << j) & 0x8000)
            {
                ILI9341_Write_Data(color >> 8);
                ILI9341_Write_Data(color & 0xFF);
            }
            else
            {
                ILI9341_Write_Data(bgcolor >> 8);
                ILI9341_Write_Data(bgcolor & 0xFF);
            }
        }
    }
	DISP_CS_UNSELECT;
}

// Вывод строки
void write_string(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor)
{
    while(*str)
    {
        if(x + font.width >= ILI9341_SCREEN_WIDTH)
        {
            x = 0;
            y += font.height;

            if(y + font.height >= ILI9341_SCREEN_HEIGHT)
            {
                break;
            }

            if(*str == ' ')
            {
                str++;
                continue;
            }
        }

        write_char_0(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }
}
