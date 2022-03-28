#include "top.h"

int main()
{
    display dis;
    dis.init();
    //                       01234567890
    //             01234567891111111112
    char tester[]="8 + ( 67 - 90 () )";
    printf("\n%lf\n",math_string(tester,0,strlen(tester)-1));
    //startProc("test.ecl", &dis);
    //text_editor(&dis);
    //while(true)
    //    dis.update();
    return 0;
}


void wordNEWvar(stack_mem *m, FILE* file)
{
    //m->new_var("test",16.0);
    char buf[10]="";
    for(char c=getc(file);c!='\n' && c!=' ';c=getc(file))
    {
       if(c==' ')
       {
            return;
       }else{
            buf[strlen(buf)]=c;
       }
    }
    m->new_var(buf);
}


void wordVAR(stack_mem *m, FILE* file, char *name)
{
    char buf[100]="";
    for(char c=getc(file);c!='\n' && c!=EOF;c=getc(file))
    {
        buf[strlen(buf)]=c;
    }
    printf("var string: \"%s\"\n", buf);
    int do_whith_var=0;
    //0
    //1 =
    //2 +
    //3 -
    //4 /
    //5 *
    if(buf[0]=='=')
    {
        do_whith_var=1;
    }else{
        printf("Error, symbol \"%c\" is not defined", buf[0]);
        return;
    }
    //printf("\nttttttttttt%s",buf);
}


double math_string(char *st, int start, int stop)
{
    double otv=0;
    for(int i=start;i<=stop;i++)
    {
        if(st[i]=='(')
        {
            int count_scob=0;
            int new_stop;
            for(int j=i+1;j<=stop;j++)
            {
                    if(st[j]=='(')
                            count_scob++;
                    if(st[j]==')' && count_scob==0)
                            new_stop=j;
                    else if(st[j]==')' && count_scob!=0)
                            count_scob--;
            }
            double zamena=math_string(st, i+1, new_stop-1);
            printf("start %d stop %d\n",i,new_stop);
        }
    }
    return otv;
}

void startProc(char *str, display *dis)
{
    stack_mem memory;
    //printf("%f\n",memory.get_var("test"));
    FILE* file=fopen(str, "r");
    char buff[100]="";
    //char setted_var[10]="";
    for(char c=getc(file);c!=EOF;c=getc(file))
    {
        if(c==' ' || c=='\n' || c==EOF)
        {
printf("\tCommand \"%s\"\n",buff);
            if(strcmp(buff,"var")==0)
            {
                wordNEWvar(&memory, file);
            //}else if(!strcmp(buff,"")){
            }else{
                printf("Command \"%s\" is not defined\n  Check vars...\n", buff);
                if(memory.check_var(buff))
                {
                        printf("  Var \"%s\" found\n",buff);
                        wordVAR(&memory, file, buff);
                        //for(int i=0;i<10;i++)
                        //    setted_var[i]=0;
                        //strncpy(setted_var,buff,10);
                }else printf("  Var \"%s\" not found\n",buff);
            }
            for(int i=0;i<100;i++)
                    buff[i]=0;
        }else{
            buff[strlen(buff)]=c;
        }
    }
    dis->print(10,10,1,buff);
    fclose(file);
}


void text_editor(display *dis)
{
    char buf[1000]="";
    char c;
    while(true)
    {
        //scanf("%s",buf);
        c=getchar();
        buf[strlen(buf)]=c;
        dis->print(10,20,1, buf );
        dis->update();
    }
}
