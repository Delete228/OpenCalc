#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "font5x7.h"

using namespace std;

#define scale 2
#define height 256
#define width 256

class display
{
public: 
    void init()
    {
    this->window.create(sf::VideoMode(scale*(height+2),scale*(width+2)), "SFML works!");
    this->up.setSize(sf::Vector2f(scale*(height+2.f),scale*(height+2.f)));
    this->pix.setSize(sf::Vector2f(scale,scale));
    
   
    this->up.setFillColor(sf::Color::Red);
    this->pix.setFillColor(sf::Color::White);
    for(int i=0;i<height;i++)
            for(int j=0;j<height;j++)
                    matr[i][j]=0;
    }
    void update()
    {

        this->window.clear();
        this->window.draw(this->up);
        for(int i=0;i<height;i++)
                for(int j=0;j<height;j++)
                {
                    if(matr[i][j]==0)
                    {
                        this->pix.setFillColor(sf::Color::White);
                    }else{
                        this->pix.setFillColor(sf::Color::Blue);
                    }
                    this->pix.setPosition(i*scale+2.f,j*scale+2.f);
                    this->window.draw(pix);
                }
        this->window.display();
    }
    void pixl(int x, int y, int pi=0){this->matr[x][y]=pi;}
    void line(int x1, int y1, int x2, int y2, int pi=1)
    {
        int deltaX=(x2-x1>0)?x2-x1:x1-x2;
        int deltaY=(y2-y1>0)?y2-y1:y1-y2;
        int signX= x1<x2?1:-1;
        int signY= y1<y2?1:-1;
        
        int error = deltaX - deltaY;
        this->pixl(x2,y2,pi);

        while(x1 != x2 || y1 != y2)
        {
            this->pixl(x1,y1,pi);
            int error2=error*2;
            if(error2 > -deltaY)
            {
                    error-=deltaY;
                    x1+=signX;
            }
            if(error2<deltaX)
            {
                    error+=deltaX;
                    y1+=signY;
            }
        }
    }
    void rect(int x1, int y1, int x2, int y2, int pi)
    {
            this->line(x1,y1,x2,y1,pi);
            this->line(x2,y1,x2,y2,pi);
            this->line(x2,y2,x1,y2,pi);
            this->line(x1,y2,x1,y1,pi);
            /*
            int mnx=x1<x2?x1:x2;
            int mxx=x1>x2?x1:x2;
            int mny=y1<y2?y1:y2;
            int mxy=y1>y2?y1:y2;
            for(int xx=mnx;xx<mxx;xx++)
                for(int yy=mny;yy<mxy;yy++)
                    this->pixl(xx,yy,pi);
                    */
    }
    void cirl(int x0, int y0, int radius, int pi)
    {
    int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while(y >= 0) {
		this->pixl(x0 + x, y0 + y, pi);
		this->pixl(x0 + x, y0 - y, pi);
		this->pixl(x0 - x, y0 + y, pi);
		this->pixl(x0 - x, y0 - y, pi);
		error = 2 * (delta + y) - 1;
		if(delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if(delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
    }

void Char(int x, int y, int pi, unsigned char c) 
{
  //if((x >= 240) || (y >= 240) || ((x + 4) < 0) || ((y + 7) < 0)) return;
  if(c<128)            c = c-32;
  if(c>=144 && c<=175) c = c-48;
  if(c>=128 && c<=143) c = c+16;
  if(c>=176 && c<=191) c = c-48;
  if(c>191)  return;
  for (int i=0; i<6; i++ ) 
	{
		int line;
    if (i == 5) line = 0x00;
    else line = font[(c*5)+i];
		for (int j = 0; j<8; j++)
		{
			if (line & 0x01) this->pixl(x + i, y + j, pi);
			line >>= 1;
		}
	}
}

void print(int x, int y, int pi, char *str) 
{
  unsigned char type = *str;
  if (type>=128) x = x - 3;
  while (*str)
	{		
		this->Char(x, y, pi, *str++); 
    unsigned char type = *str;
    if (type>=128) x=x+3;
    else x=x+6;
  }
}

    
private:

    sf::RenderWindow window;

    sf::RectangleShape up;
    sf::RectangleShape pix;

    int matr[height][width];
};


int main()
{
    display dis;
    dis.init();
    char input[100];
    cin.get(input,100);             // Получение на ввод строки, макс размер - 100

    cout << "Working in progress..";

    //dis.print(0, 0, 1, text);    // Вывод на экран
    //dis.print(7, 8, 1, sym);    // нормальное гор. расстояние = 6 пикс. верт - 8
    //dis.print(0, 0, 1, input);
    //dis.line(0, 8, 5, 8, 1);
    
    
    
    int x = 5;
    int y = 10;
    int y_null=y;
    int len_num=0;

    for (int i = 0; i <= strlen(input); i++, x+=6)
    {
        // нужно запоминать числа полностью и отрисовывать их в первую очередь
        
        
        
        
        // 2-й вариант.                             Upd. Не получилось. Выдаёт интересную ошибку. Из-за этого как минимум дроби будут сильно  кривыми.
        /*if (isdigit(input[i]) == true)
        {
            char number[7];
            int j = i;
            for (j; isdigit(input[i]) != false; j++)
            {
                number[j] = input[j];
                i += j;
            }
            dis.print(x, y, 1, number);
            x += 6 * j;
        }
        else {
            if (input[i + 1] == '*')
        {
            continue;
        }

        if (input[i + 1] == '/')
        {
            y += 4;

            dis.line(x, y, x + 4, y, 1);

            char sym = input[i];


            //dis.Char(x, y - 6, 1, 'C');

            dis.Char(x, y - 8, 1, input[i]);
            dis.Char(x, y + 2, 1, input[i + 2]);
            i += 2;

            y - +4;
            continue;
        }
        else
        {
            dis.Char(x, y + 1, 1, input[i]);
        }
        }*/


                                                 // Ниже 1-й вариант. Гуано
        if (input[i] == '*')
        {
            y=y_null;
            len_num=0;
            continue;
        }else if (input[i] == '/')
        {
            //char alarm[] = "ДРОБИ КРИВЫЕ!!!";
            //dis.print(100, 100, 1, alarm);
            //y += 4;
            for(int j=1;j<=len_num;j++)
                    dis.Char(x-6*j,y,0,input[i-j]);
            for(int j=len_num;j>0;j--)
            {
                dis.line(x-j*6, y+3, x - j*6 + 5, y+3, 1);
                dis.Char(x-j*6, y-5, 1, input[i-j]);
            }
            x-=len_num*6+6;

            //char sym = input[i];

            //dis.Char(x, y - 8, 1, input[i]);
            //dis.Char(x, y + 2, 1, input[i + 2]);
            //i += 2;

            //y - +4;
            //y=y_null;
            y+=5;
            len_num=0;
            continue;
        }else if (input[i] == '^')
        {
            //dis.Char(x, y + 4, 1, input[i+1]);
            y-=4;
            i++; 
            len_num=0;
        }else{
                //y=y_null;
                len_num++;
        }


        dis.Char(x, y, 1, input[i]);

    }

    while(true)
    {
            dis.update();
    }
    return 0;
}
