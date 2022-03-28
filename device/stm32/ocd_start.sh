#!/bin/bash
cd /home/delete/openocd/scripts/
../bin/openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
