#include "display/Inc/daemon.h"

void draw_window(uint8_t id, FontDef font);

struct window *windows;
uint8_t count_windows=0;
uint8_t current_window=0;

struct mousee mouse;

void display_demon_init(uint8_t id)
{
       windows=(struct window*)malloc(count_windows*sizeof(struct window));
       fill_screen(WHITE);
       mouse.up_down=0;
       mouse.right_left=0;
       mouse.fn=0;
       mouse.X=120;
       mouse.Y=160;
       mouse.owner_window_id=id;
       write_string(0,240-10,"OS ver 1.0", Font_7x10, BLACK, WHITE);
       write_char_0(200,240-10,'G', Font_7x10, BLACK, WHITE);
       write_char_90(220,240-10,'G', Font_7x10, BLACK, WHITE);
       write_char_180(240,240-10,'G', Font_7x10, BLACK, WHITE);
       write_char_270(260,240-10,'G', Font_7x10, BLACK, WHITE);
}
void display_demon_funk(uint8_t id)
{
        current_window++;
        if(current_window>=count_windows)
                current_window=0;

       draw_window(current_window, Font_7x10);

       mouse.up_down=0;
       mouse.right_left=0;
       mouse.fn=0;
        //right left
#if 0
        if( HAL_GPIO_ReadPin(nav_3_GPIO_Port, nav_3_Pin) == GPIO_PIN_RESET &&   //right press
            HAL_GPIO_ReadPin(nav_1_GPIO_Port, nav_1_Pin) == GPIO_PIN_SET)       //left  unpress
        {
                mouse.right_left=1;
        }
        if( HAL_GPIO_ReadPin(nav_3_GPIO_Port, nav_3_Pin) == GPIO_PIN_SET &&   //right unpress
            HAL_GPIO_ReadPin(nav_1_GPIO_Port, nav_1_Pin) == GPIO_PIN_RESET)       //left  press
        {
                mouse.right_left=-1;
        }

        //up down
        if( HAL_GPIO_ReadPin(nav_4_GPIO_Port, nav_4_Pin) == GPIO_PIN_RESET &&   //up press
            HAL_GPIO_ReadPin(nav_2_GPIO_Port, nav_2_Pin) == GPIO_PIN_SET)       //down  unpress
        {
                mouse.up_down=-1;
        }
        if( HAL_GPIO_ReadPin(nav_4_GPIO_Port, nav_4_Pin) == GPIO_PIN_SET &&   //up unpress
            HAL_GPIO_ReadPin(nav_2_GPIO_Port, nav_2_Pin) == GPIO_PIN_RESET)       //down  press
        {
                mouse.up_down=1;
        }

        //OK
        /*static uint8_t flag=1;
        if( HAL_GPIO_ReadPin(nav_5_GPIO_Port, nav_5_Pin) == GPIO_PIN_RESET) 
        {
                if(flag)
                {
                mouse.fn=(mouse.fn==1)?0:1;
                flag=0;
                }
        } else {
                flag=1;
        }*/
        static uint8_t flag=GPIO_PIN_RESET;
        if( HAL_GPIO_ReadPin(nav_5_GPIO_Port, nav_5_Pin) == GPIO_PIN_RESET) 
        {
                mouse.fn=1;
                flag=GPIO_PIN_SET;
        } else {
                mouse.fn=0;
                flag=GPIO_PIN_RESET;
        }
#endif


        draw_fill_rect(mouse.X-2,mouse.Y-2,mouse.X+2,mouse.Y+2,WHITE);
        if(!mouse.right_left || !mouse.up_down)
        {
            mouse.X+=mouse.right_left;
            mouse.Y+=mouse.up_down;
        }
        if(mouse.fn)
        {
                draw_fill_rect(mouse.X-2,mouse.Y-2,mouse.X+2,mouse.Y+2,DARKGREEN);
        }
        draw_hor_line(mouse.X-2,mouse.Y,4,DARKCYAN);
        draw_ver_line(mouse.X,mouse.Y-2,4,DARKCYAN);

        if(mouse.owner_window_id==0)
        {
            if(mouse.X>=windows[current_window].X &&
               mouse.Y>=windows[current_window].Y &&
               mouse.X<=windows[current_window].X+windows[current_window].width+1 &&
               mouse.Y<=windows[current_window].Y+windows[current_window].height+2+11)
                    mouse.owner_window_id=windows[current_window].owner_id;

        }else{
            uint8_t wn=daemons[mouse.owner_window_id].window_id;
            if(mouse.X<windows[wn].X ||
               mouse.Y<windows[wn].Y ||
               mouse.X>windows[wn].X+windows[wn].width+2 ||
               mouse.Y>windows[wn].Y+windows[wn].height+3+11)
                    mouse.owner_window_id=0;
            if(mouse.fn && mouse.owner_window_id!=0)
            {
                draw_fill_rect(windows[wn].X,windows[wn].Y,
                               windows[wn].X+windows[wn].width+2,windows[wn].Y+windows[wn].height+14,WHITE);
                windows[wn].X+=mouse.right_left;
                windows[wn].Y+=mouse.up_down;
            }
        }
        char b[5];
        sprintf(b,"%d",mouse.owner_window_id);
        write_string(80,320-10,b, Font_7x10, BLACK, WHITE);
        uint16_t *x,*y;
        if(ILI9341_TouchGetCoordinates(x,y))
        {
                char g[15];
                sprintf(g,"x:%d y$%d",*x,*y);
                write_string(250,230,g, Font_7x10, BLACK, WHITE);
        }

}


void write_string_ON_WINDOW(uint8_t id, uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor)
{
       if(daemons[id].window_id==-1) return;

       if(x>windows[daemons[id].window_id].width || y>windows[daemons[id].window_id].height) return;

       write_string(x+windows[daemons[id].window_id].X+1,y+windows[daemons[id].window_id].Y+13,str, font, color, bgcolor);
}

void draw_pixel_ON_WINDOW(uint8_t id, uint16_t x, uint16_t y, uint16_t Colour)
{
       if(daemons[id].window_id==-1) return;

       if(x>windows[daemons[id].window_id].width || y>windows[daemons[id].window_id].height) return;
       draw_pixel(x+windows[daemons[id].window_id].X+1,y+windows[daemons[id].window_id].Y+13,Colour);

}

void fill_screen_ON_WINDOW(uint8_t id,uint16_t Colour)
{
       if(daemons[id].window_id==-1) return;
       draw_fill_rect(windows[daemons[id].window_id].X+1,windows[daemons[id].window_id].Y+13,
                      windows[daemons[id].window_id].width+windows[daemons[id].window_id].X+1,windows[daemons[id].window_id].height+windows[daemons[id].window_id].Y+13,Colour);
}



void create_window(uint8_t ow_id, uint8_t h, uint8_t w, enum type_window t, enum resize_window r)
{
        count_windows++;
        windows=(struct window*)realloc(windows,count_windows*sizeof(struct window));
        windows[count_windows-1].owner_id=ow_id;
        windows[count_windows-1].height=h;
        windows[count_windows-1].width=w;
        windows[count_windows-1].type=t;
        windows[count_windows-1].resize=r;
        windows[count_windows-1].state=no_changes;
        windows[count_windows-1].X=20;
        windows[count_windows-1].Y=20;
        daemons[ow_id].window_id=count_windows-1;
}


void draw_window(uint8_t id, FontDef font)
{
        draw_hor_line(windows[current_window].X,
                      windows[current_window].Y,
                      windows[current_window].width+2, BLACK);

        draw_hor_line(windows[current_window].X,
                      windows[current_window].Y+font.height+2,
                      windows[current_window].width+2, BLACK);

        draw_hor_line(windows[current_window].X,
                      windows[current_window].Y+font.height+windows[current_window].height+4,
                      windows[current_window].width+2, BLACK);



        draw_ver_line(windows[current_window].X,
                      windows[current_window].Y,
                      windows[current_window].height+4+font.height, BLACK);

        draw_ver_line(windows[current_window].X+windows[current_window].width+2,
                      windows[current_window].Y,
                      windows[current_window].height+4+font.height, BLACK);


        write_string(windows[current_window].X+1,
                     windows[current_window].Y+2,
                     daemons[windows[current_window].owner_id].name,
                     font, BLACK, WHITE);
}
