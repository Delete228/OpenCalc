#!/bin/bash
arm-none-eabi-gdb -ex "target extended-remote localhost:3333" -ex "file build/Cacl.elf" -ex "load" -ex "run" -ex "quit"
