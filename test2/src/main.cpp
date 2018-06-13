#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <main.h>
#include <testapi.h>
#include <tcimg.h>
#include <winapi.h>

void eventcb(WINEVENT e)
{
	switch (e.type)
	{
		case MOUSEBUTTONDOWN:
		{ 
			printf("M: state:%d,button %d (%d,%d)\n",e.button.state,e.button.button,e.button.x,e.button.y);
                        break;
		}
		case KEYUP:
		{
			printf("K: state:%d,key (%d)\n",e.key.state,e.key.keysym);
			if (e.key.keysym == KEY_ESCAPE){
			//	printf("Press ESC\n");
				exit(0);
			}
		        break;
               }
	}
}

void updatecb(PixelBuffer screenbuffer)
{
	extern TrueColorImage abc;
        PixelBuffer*  p = createPixelBuffer(abc.ImgWidth , abc.ImgHeight, 24);
	memcpy(p->pixels,abc.ImgData,abc.ImgTotalBytes);
        int i,j;
        for (j=-20;j<20;j++)
          for (i=-20;i<20;i++){
                int jj = SDLWindow::instance()->MouseY+j;
                int ii = SDLWindow::instance()->MouseX+i;
                if ((jj > 5) && (ii > 5) && (jj < SDLWindow::instance()->Height-5) && (ii < SDLWindow::instance()->Width-5)){
                  //printf(" p->bytesperline=%d\n", p->bytesperline);
                  unsigned char* offset = (unsigned char*)(p->pixels) + (((SDLWindow::instance()->MouseY+j) * p->bytesperline)+ 3*(SDLWindow::instance()->MouseX+i));
                  offset[0] = 0;
                  offset[1] = 0;
                  offset[2] = 255;
                }
        }
        SDLWindow::instance()->render(p);
        freePixelBuffer(p);

	 /*
    SDL_Surface *screen1 = SDL_CreateRGBSurfaceFrom(abc.ImgData, abc.ImgWidth, abc.ImgHeight, 24,
     	                                 abc.ImgByteWidth,
                                         0x00FF0000,
                                         0x0000FF00,
                                         0x000000FF,
                                         0xFF000000);
    */    
}

int main()
{
	extern TrueColorImage abc;
	printf("W x H --> (%d,%d)\n",abc.ImgWidth, abc.ImgHeight);
	printf("ImgTotalBytes --> %d\n",abc.ImgTotalBytes);
	printf("ImgTotalPixels --> %d\n",abc.ImgTotalPixels);
	printf("ImgByteWidth --> %d\n",abc.ImgByteWidth);
    Layer* l1 = new Layer("AAA",10,10,100,50,128);
    Layer* l2 = new Layer("BBB",20,20,30,20,255);
    SDLWindow::instance()->init("",640,480);
    SDLWindow::instance()->addLayer(l1);
    SDLWindow::instance()->addLayer(l2);
    //SDLWindow::instance()->resize(abc.ImgWidth,abc.ImgHeight);
    //SDLWindow::instance()->init("ABC",abc.ImgWidth,abc.ImgHeight);
    SDLWindow::instance()->show(updatecb,eventcb);

	//api1();
	//api2();
  return 0;
}
