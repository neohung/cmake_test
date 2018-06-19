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

void Layer::clearDraw()
{
	memset(pixelbuf->pixels,0,pixelbuf->size);
}

void Layer::draw_line(unsigned short x1,unsigned short y1, unsigned short x2,unsigned short y2,unsigned int color, unsigned char size)
{
	unsigned char b = 0x0000ff & color;
    unsigned char g = (0x00ff00 & color) >> 8;
    unsigned char r = (0xff0000 & color) >> 16;
    if (x2 == x1){
    	if (y2 < y1){
        		int tmp = y2;
        		y2 = y1;
        		y1 = tmp;
        		tmp = x2;
        		x2 = x1;
        		x1 = tmp;
        }
    	int k;
    	for(k=-size;k<size;k++){
        	int j;
        	for(j=y1;j<y2;j++){
        		int i = x1+k;
        		unsigned char* offset = (unsigned char*)pixelbuf->pixels + (j *  pixelbuf->bytesperline) + (pixelbuf->colors*i);
        		*offset = b;
        		*(offset+1) = g; //G
        		*(offset+2) = r; 
        	}
    	}
    }else{
	double slop = double(y2-y1)/double(x2-x1);
	//printf("slop %f\n", slop);
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

void Layer::draw_tri(Triangle tri,unsigned int color, unsigned char size, bool is_fill)
{
	draw_line(tri.v1.x,tri.v1.y, tri.v2.x,tri.v2.y, color, size);
	draw_line(tri.v2.x,tri.v2.y, tri.v3.x,tri.v3.y, color, size);
	draw_line(tri.v3.x,tri.v3.y, tri.v1.x,tri.v1.y, color, size);
        if (is_fill){
          int y3 = tri.v3.y;
          int x3 = tri.v3.x;
          int y2 = tri.v2.y;
          int x2 = tri.v2.x;
          int y1 = tri.v1.y;
          int x1 = tri.v1.x;
          double slop1 = double(y2-y1)/double(x2-x1);
          double bb1 = double(y2*x1-y1*x2)/double(x1-x2);
          double slop2 = double(y3-y1)/double(x3-x1);
          double bb2 = double(y3*x1-y1*x3)/double(x1-x3);
          double slop3 = double(y3-y2)/double(x3-x2);
          double bb3 = double(y3*x2-y2*x3)/double(x2-x3);
          double centerx = double(x1+x2+x3)/3.0;
          double centery = double(y1+y2+y3)/3.0;
          double val_center = (slop1*centerx+bb1-centery)*(slop2*centerx+bb2-centery)*(slop3*centerx+bb3-centery);
          int i,j;
          int datax[3];
          int datay[3];
          datax[0] = tri.v1.x;
          datax[1] = tri.v2.x;
          datax[2] = tri.v3.x;
          datay[0] = tri.v1.y;
          datay[1] = tri.v2.y;
          datay[2] = tri.v3.y;
          for(i=0;i<2;i++){
            for(j=1;j<3;j++){
              //from small to big sort use >
              if (datax[i] >  datax[j]){
                int tmp = datax[i];
                datax[i] = datax[j];
                datax[j] = tmp;
              }
              if (datay[i] >  datay[j]){
                int tmp = datay[i];
                datay[i] = datay[j];
                datay[j] = tmp;
              }
            }
          }
          int li = datax[0];
          int ri = datax[2];
          int uj = datay[0];
          int dj = datay[2];
          unsigned char b = 0x0000ff & color;
          unsigned char g = (0x00ff00 & color) >> 8;
          unsigned char r = (0xff0000 & color) >> 16;
          for(i=li;i<ri;i++){
            for(j=uj;j<dj;j++){
              double val = (slop1*i+bb1-j)*(slop2*i+bb2-j)*(slop3*i+bb3-j);
              if (val*val_center > 0){
                unsigned char* offset = (unsigned char*)pixelbuf->pixels + (j *  pixelbuf->bytesperline) + (pixelbuf->colors*i);
                  *offset = b;
                  *(offset+1) = g; //G
                  *(offset+2) = r; //R
             }
          }
        }
   }
}
