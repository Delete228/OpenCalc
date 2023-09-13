#ifndef __DISPLAY_H__
#define __DISPLAY_H__


#include <SFML/Graphics.hpp>
#include "font5x7.h"


#define scale 2
#define height 240
#define width 320

class display
{
public: 
    void init();
    void update();
    void pixl(int x, int y, int pi=0);
    void clear(int pi=0);
    void line(int x1, int y1, int x2, int y2, int pi=1);
    void rect(int x1, int y1, int x2, int y2, int pi);
    void cirl(int x0, int y0, int radius, int pi);
    void Char(int x, int y, int pi, unsigned char c) ;
    void print(int x, int y, int pi, char *str);
private:
    sf::RenderWindow window;
    sf::RectangleShape up;
    sf::RectangleShape pix;
    int matr[height][width];
};




#endif
