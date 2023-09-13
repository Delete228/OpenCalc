#ifndef __DAEMON_DISPLAY_H
#define __DAEMON_DISPLAY_H

#include "Drivers/display/Inc/driver.h"
#include "Drivers/display/Inc/fonts.h"
#include "xpt2046_touch.h"
#include "stm32h7xx_hal.h"
#include "main.h"
#include "OS.h"


void display_demon_init(uint8_t);
void display_demon_funk(uint8_t);
void create_window(uint8_t ow_id, uint8_t h, uint8_t w, uint8_t t, uint8_t r);

void write_string_ON_WINDOW(uint8_t id, uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void draw_pixel_ON_WINDOW(uint8_t id, uint16_t x, uint16_t y, uint16_t Colour);
void fill_screen_ON_WINDOW(uint8_t id,uint16_t Colour);
enum type_window
{
        canvas=0,
};

enum resize_window
{
        no=0,
        yes_height,
        yes_width,
        yes_all,
};

enum window_state
{
        no_changes=0,
        move,
        rename,
        resize,

};

struct window
{
        uint8_t owner_id;
        uint16_t height;
        uint16_t width;
        uint16_t X;
        uint16_t Y;
        enum window_state state;
        enum type_window type;
        enum resize_window resize;
};


struct mousee
{
        int8_t up_down;
        int8_t right_left;
        uint8_t fn;
        uint16_t X;
        uint16_t Y;
        uint8_t owner_window_id;
};

extern struct window *windows;
extern uint8_t count_windows;

#endif
