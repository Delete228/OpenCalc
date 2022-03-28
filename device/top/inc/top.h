#ifndef __TOP_H__
#define __TOP_H__

#include <cstring>

#include "display.h"
#include "stack_mem.h"

double math_string(char *string, int start, int stop);
void wordNEWvar(stack_mem *m, FILE* file);
void wordVAR(stack_mem *m, FILE* file, char *name);
void startProc(char *str, display *dis);
void text_editor(display *dis);
#endif
