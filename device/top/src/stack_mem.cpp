#include "stack_mem.h"



stack_mem::stack_mem()
{
    count_vars=0;
    for(int i=0;i<SIZEOFSTACK;i++)
    {
        stack[i]=0.0;
        for(int j=0;j<10;j++)
            name_vars[i][j]=0;
    }
}


void stack_mem::new_var(char *str)
{
    if(this->find_var(str)==-1)
    {
        strncpy(this->name_vars[count_vars],str,10);
        count_vars++;
        this->print();
    }
}


void stack_mem::new_var(char *str, double value)
{
    if(this->find_var(str)==-1)
    {
        strncpy(this->name_vars[count_vars],str,10);
        stack[count_vars]=value;
        count_vars++;
        this->print();
    }
}


double stack_mem::get_var(char *str)
{
    if(this->find_var(str)==-1) return 0;
    return stack[this->find_var(str)];
}


void stack_mem::set_var(char *str, double vaule)
{
    if(this->find_var(str)==-1) return;
    stack[this->find_var(str)]=vaule;
 }


int stack_mem::check_var(char *str)
{
    if(this->find_var(str)==-1) return 0;
    else return 1;
}


void stack_mem::print()
{
    for(int i=0;i<count_vars;i++)
        printf("Var: %s=%f \n",name_vars[i] ,stack[i]);
}


int stack_mem::find_var(char *str)
{
    for(int i=0;i<count_vars;i++)
        if(!strcmp(str,name_vars[i])) return i;
    return -1;
}
