#include <stdio.h>
//#include <main.h>
//#include <testapi.h>
//#include <tcimg.h>

#include <winapi.h>
#include <SDL.h>

Layer::Layer()
{
}

Layer::~Layer()
{
}

void Layer::update(PixelBuffer* pb)
{
}

void Layer::setPos(unsigned short x, unsigned short y)
{
  PosX = x;
  PosY = y;
}

Layer::Layer(const char* name, unsigned short x, unsigned short y, unsigned short w, unsigned short h,unsigned int color):
PosX(x), PosY(y), Width(w), Height(h), IsSkip(false),order(255)
{
   Name = (char*)name;
   pixelbuf = createPixelBuffer(Width,Height, 24);
   memset(pixelbuf->pixels,color,pixelbuf->size);
}

void Layer::draw_line(unsigned short x1,unsigned short y1, unsigned short x2,unsigned short y2,unsigned int color, unsigned char size)
{
}
void Layer::draw_point(unsigned short x,unsigned short y, unsigned int color, unsigned char size)
{
  unsigned char* offset = (unsigned char*)pixelbuf->pixels;
  
  offset += y *  pixelbuf->bytesperline + (pixelbuf->colors*x);
  unsigned char b = 0x0000ff & color;
  unsigned char g = (0x00ff00 & color) >> 8;
  unsigned char r = (0xff0000 & color) >> 16;
  *offset = r;
  *(offset+1) = g;
  *(offset+2) = b;
}
