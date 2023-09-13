#ifndef __OS_H
#define __OS_H

#include "stm32h7xx_hal.h"
#include "main.h"
#include <stdlib.h>
#include "display/Inc/daemon.h"

void daemon_init(void);
void daemon_update(void);
void daemon_update_delay(void);
void daemon_delay(uint8_t, uint32_t);
uint8_t create_demon(void (*init)(uint8_t),void (*update)(uint8_t), char *nm);


void first_demon_init(uint8_t);
void first_demon_funk(uint8_t);
void second_demon_init(uint8_t);
void second_demon_funk(uint8_t);


struct daemon
{
        void (*init_funktion)(uint8_t);
        void (*update_funktion)(uint8_t);
        uint32_t pause_time;
        uint8_t priority;
        uint8_t id;
        char *name;
        int8_t window_id;
};


extern struct daemon *daemons;
extern uint8_t count_daemons;


#endif
