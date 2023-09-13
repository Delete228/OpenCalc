#include "OS.h"


struct daemon *daemons;
uint8_t count_daemons=0;
uint8_t current_demon=0;



uint8_t create_demon(void (*init)(uint8_t),void (*update)(uint8_t), char *nm)
{
        count_daemons++;
        daemons=(struct daemon*)realloc(daemons,count_daemons*sizeof(struct daemon));
        daemons[count_daemons-1].init_funktion=init;
        daemons[count_daemons-1].update_funktion=update;
        daemons[count_daemons-1].pause_time=0;
        daemons[count_daemons-1].priority=1;
        daemons[count_daemons-1].id=count_daemons-1;
        daemons[count_daemons-1].name=nm;
        daemons[count_daemons-1].window_id=-1;

}


void first_demon_init(uint8_t id) 
{
        create_window(id, 50, 50, 0, 0);
}
void first_demon_funk(uint8_t id)
{
          static uint8_t tr=0;
          fill_screen_ON_WINDOW(id,YELLOW);
          write_string_ON_WINDOW(id,1,1,"test1",Font_7x10,BLACK,GREEN);
          draw_pixel_ON_WINDOW(id, 0,0,RED);
          draw_pixel_ON_WINDOW(id, 50,50,RED);
          tr = (tr==0)?1:0;
          if(tr==1)
            write_string_ON_WINDOW(id,1,20,"ON ",Font_7x10,BLACK,GREEN);
          else
            write_string_ON_WINDOW(id,1,20,"OFF",Font_7x10,BLACK,GREEN);
          //HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);
          daemon_delay(id, 90);
}

void second_demon_init(uint8_t id) 
{
        create_window(id, 75, 70, 0, 0);
}
void second_demon_funk(uint8_t id)
{
          write_string_ON_WINDOW(id,1,1,"2 yellow",Font_7x10,BLACK,GREEN);
          //HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port,LED_YELLOW_Pin);
          daemon_delay(id, 30);
}



void daemon_update_delay(void)
{
        for(int i=0;i<count_daemons;i++)
        {
                if(daemons[i].pause_time>0)
                    daemons[i].pause_time--;
        }
}

void daemon_delay(uint8_t id, uint32_t del)
{
        daemons[id].pause_time=del;
}

void daemon_init(void)
{
        daemons=(struct daemon*)malloc(count_daemons*sizeof(struct daemon));
        create_demon(display_demon_init, display_demon_funk, "display");
        create_demon(first_demon_init, first_demon_funk, "Led 1");
        create_demon(second_demon_init, second_demon_funk, "led Yellow");


        for(int i=0;i<count_daemons;i++)
                daemons[i].init_funktion(i);
}

void daemon_update(void)
{
        if(daemons[current_demon].pause_time==0)
                daemons[current_demon].update_funktion(current_demon);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
          HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
          //__HAL_TIM_SET_AUTORELOAD(htim, tim_period);
          //tim_period+=1;
          //current_demon++;
          //if(current_demon>=count_daemons)
          //{
          //        current_demon=0;
          //}
          daemon_update_delay();
          for(int i=0;i<count_daemons;i++)
          {
                  current_demon++;
                  if(current_demon>=count_daemons)
                          current_demon=0;
                  if(daemons[current_demon].pause_time==0)
                          break;
          }
          HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
}


