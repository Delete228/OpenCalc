#include "display.h"

void display::init()
{
    
    this->window.create(sf::VideoMode(scale*(height+2),scale*(width+2)), "DispCalcEMU");
    this->up.setSize(sf::Vector2f(scale*(height+2.f),scale*(height+2.f)));
    this->pix.setSize(sf::Vector2f(scale,scale));
    
   
    this->up.setFillColor(sf::Color::Red);
    this->pix.setFillColor(sf::Color::White);
    for(int i=0;i<height;i++)
            for(int j=0;j<height;j++)
                    matr[i][j]=0;
    this->window.clear();
    this->window.display();
}


void display::update()
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


void display::pixl(int x, int y, int pi)
{
    if(x<0||x>=height||y<0||y>=height) return;
    this->matr[x][y]=pi;
}


void display::clear(int pi)
{
    for(int i=0;i<height;i++)
        for(int j=0;j<height;j++)
            this->pixl(i,j,pi);
}


void display::line(int x1, int y1, int x2, int y2, int pi)
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


void display::rect(int x1, int y1, int x2, int y2, int pi)
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


void display::cirl(int x0, int y0, int radius, int pi)
{
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;
	while(y >= 0) 
    {
        this->pixl(x0 + x, y0 + y, pi);
        this->pixl(x0 + x, y0 - y, pi);
        this->pixl(x0 - x, y0 + y, pi);
        this->pixl(x0 - x, y0 - y, pi);
        error = 2 * (delta + y) - 1;
        if(delta < 0 && error <= 0) 
        {
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        error = 2 * (delta - x) - 1;
        if(delta > 0 && error > 0) 
        {
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        ++x;
        delta += 2 * (x - y);
        --y;
    }
}


void display::Char(int x, int y, int pi, unsigned char c) 
{
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


void display::print(int x, int y, int pi, char *str) 
{
    unsigned char type = *str;
    int xnull=x;
    if (type>=128) x = x - 3;
    while (*str)
    {		
        this->Char(x, y, pi, *str++); 
        unsigned char type = *str;
        if (type>=128) x=x+3;
        else x=x+6;
        if (type=='\n')
        {
            y+=8;
            x=xnull;
            *str++;
        }
    }
}
