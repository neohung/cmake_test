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
	unsigned char b = 0x0000ff & color;
    unsigned char g = (0x00ff00 & color) >> 8;
    unsigned char r = (0xff0000 & color) >> 16;
	double slop = double(y2-y1)/double(x2-x1);
	double bb = double(y2*x1-y1*x2)/double(x1-x2);
        double abs_slop = abs(slop);
    int k;
    for(k=-size;k<size;k++){
        if (abs_slop < 1){
        	//X>Y
        	if (x2 < x1){
        		int tmp = x2;
        		x2 = x1;
        		x1 = tmp;
        		tmp = y2;
        		y2 = y1;
        		y1 = tmp;
        	}
        	int i;
        	for(i=x1;i<x2;i++){
        		int j = int((i*slop)+bb)+k;
        		unsigned char* offset = (unsigned char*)pixelbuf->pixels + (j *  pixelbuf->bytesperline) + (pixelbuf->colors*i);
        		*offset = b;
        		*(offset+1) = g; //G
        		*(offset+2) = r; 
        	}
        }else{
           //Y>X
        	if (y2 < y1){
        		int tmp = y2;
        		y2 = y1;
        		y1 = tmp;
        		tmp = x2;
        		x2 = x1;
        		x1 = tmp;
        	}
        	int j;
        	for(j=y1;j<y2;j++){
        		int i = int((j-bb)/slop)-k;
        		unsigned char* offset = (unsigned char*)pixelbuf->pixels + (j *  pixelbuf->bytesperline) + (pixelbuf->colors*i);
        		*offset = b;
        		*(offset+1) = g; //G
        		*(offset+2) = r; 
        	}
        }
    }
}
void Layer::draw_point(unsigned short x,unsigned short y, unsigned int color, unsigned char size)
{
  unsigned char b = 0x0000ff & color;
  unsigned char g = (0x00ff00 & color) >> 8;
  unsigned char r = (0xff0000 & color) >> 16;
  int li,ri,uj,dj;
  li = x - size;
  ri = x + size;
  uj = y - size;
  dj = y + size;
  if (li < 0) li = 0;
  if (ri > (Width-1)) ri = Width-1;
  if (uj < 0) uj = 0;
  if (dj > (Height-1)) dj = Height-1;
  int size2 = size*size;
  int i,j;
  for(j=uj;j<dj;j++){
  	for(i=li;i<ri;i++){
  		int dist2 = (j-y)*(j-y)+(i-x)*(i-x);
  		if (dist2 < size2){
  		  unsigned char* offset = (unsigned char*)pixelbuf->pixels + (j *  pixelbuf->bytesperline) + (pixelbuf->colors*i);
  		  *offset = b;
  		  *(offset+1) = g; //G
  		  *(offset+2) = r; //R
  		}
  	}
  } 
}
