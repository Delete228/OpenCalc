#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "OS.h"
#include "stm32h7xx_hal.h"
#include "main.h"
#include "Drivers/display/Inc/fonts.h"




extern SPI_HandleTypeDef hspi1;
#define DISP_SPI_PTR     hspi1
#define DISP_SPI         SPI1

////////////////////////////////////// настройка пинов /////////////////////////////////////
#define DISP_CS_SELECT      HAL_GPIO_WritePin(DIS_CS_GPIO_Port, DIS_CS_Pin, GPIO_PIN_RESET)
#define DISP_CS_UNSELECT    HAL_GPIO_WritePin(DIS_CS_GPIO_Port, DIS_CS_Pin, GPIO_PIN_SET)

#define DISP_DC_DATA        HAL_GPIO_WritePin(DIS_DC_GPIO_Port, DIS_DC_Pin, GPIO_PIN_SET)
#define DISP_DC_CMD         HAL_GPIO_WritePin(DIS_DC_GPIO_Port, DIS_DC_Pin, GPIO_PIN_RESET)

#define DISP_RST_RESET      HAL_GPIO_WritePin(DIS_RES_GPIO_Port, DIS_RES_Pin, GPIO_PIN_RESET)
#define DISP_RST_WORK       HAL_GPIO_WritePin(DIS_RES_GPIO_Port, DIS_RES_Pin, GPIO_PIN_SET)

///////////////// ширина высота ///////////////////
#define ILI9341_SCREEN_WIDTH 	320
#define ILI9341_SCREEN_HEIGHT   240

// различные цвета, создать нужный можно здесь https://trolsoft.ru/ru/articles/rgb565-color-picker
#define MYFON       0x2965 // #2F2F2F
#define BLACK       0x0000
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xF81F

/////////////////////////////////////////////////////////
#define SCREEN_VERTICAL_1		0
#define SCREEN_HORIZONTAL_1		1
#define SCREEN_VERTICAL_2		2
#define SCREEN_HORIZONTAL_2		3

/////////////////////////////////////////////////////////


void ILI9341_Write_Command(uint8_t Command);
void ILI9341_Write_Data(uint8_t Data);
void ILI9341_Write_Large_Data(uint8_t *Data, uint8_t size_Data);
void ILI9341_Reset(void);
void ILI9341_Set_Rotation(uint8_t Rotation);
void ILI9341_Init(void);
void ILI9341_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
void ILI9341_Draw_Colour(uint16_t Colour);
void ILI9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size);

void draw_fill_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void fill_screen(uint16_t Colour);
void draw_pixel(uint16_t X, uint16_t Y, uint16_t Colour);
void draw_hor_line(uint16_t X, uint16_t Y, uint16_t leght, uint16_t Colour);
void draw_ver_line(uint16_t X, uint16_t Y, uint16_t leght, uint16_t Colour);
void write_char_270(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void write_char_180(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void write_char_90(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void write_char_0(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void write_string(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
#endif
