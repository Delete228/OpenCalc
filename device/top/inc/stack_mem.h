#ifndef __STACK_MEM_H__
#define __STACK_MEM_H__

#include <cstring>
#include <cstdio>

#define SIZEOFSTACK 1024


class stack_mem
{
public:
    stack_mem();
    void new_var(char *str);
    void new_var(char *str, double value);
    double get_var(char *str);
    void set_var(char *str, double vaule);
    int check_var(char *str);
    void print();
private:
    double stack[SIZEOFSTACK];
    char name_vars[SIZEOFSTACK][10];
    int count_vars;
    int find_var(char *str);
};
#endif
