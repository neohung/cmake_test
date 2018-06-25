#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <main.h>
#include <testapi.h>
#include <tcimg.h>
#include <winapi.h>
#include <smath.h>

int mflag = 1;
int lx1=0,ly1=0,lx2=0,ly2=0;
Triangle t = {
                  .v1=Position2D(100,100),
                  .v2=Position2D(50,150),
                  .v3=Position2D(150,150) 
                };

Point pp = Point(Position2D(100,100), 5, 0x00FFFFFF);
void eventcb(WINEVENT e)
{
	switch (e.type)
	{
		case MOUSEBUTTONDOWN:
		{ 
      Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
      mflag = 0;
      lx1 = e.button.x - l->x();
      ly1 = e.button.y - l->y();
      lx2 = e.button.x - l->x();
      ly2 = e.button.y - l->y();
			printf("M: state:%d,button %d (%d,%d)\n",e.button.state,e.button.button,e.button.x,e.button.y);
      //Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
      //l->setPos(e.button.x,e.button.y);
                        break;
		}
    case MOUSEBUTTONUP:
    { 
      Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
      mflag = 1;
      lx2 = e.button.x- l->x();
      ly2 = e.button.y- l->y();
      printf("M: state:%d,button %d (%d,%d)\n",e.button.state,e.button.button,e.button.x,e.button.y);
      break;

    }
		case KEYUP:
		{
			printf("K: state:%d,key (%d)\n",e.key.state,e.key.keysym);
			if (e.key.keysym == KEY_ESCAPE){
			//	printf("Press ESC\n");
				exit(0);
			}else if (e.key.keysym == KEY_LEFT){
      //  printf("Press ESC\n");
      }else if (e.key.keysym == KEY_RIGHT){
      //  printf("Press ESC\n");
      }else if (e.key.keysym == KEY_UP){
      //  printf("Press ESC\n");
      }else if (e.key.keysym == KEY_DOWN){
      //  printf("Press ESC\n");
      }
		        break;
               }
	}
}

void updatecb(PixelBuffer screenbuffer)
{
   Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
       l->clearDraw();
    if (mflag == 0){
      lx2 = SDLWindow::instance()->MouseX- l->x();
      ly2 = SDLWindow::instance()->MouseY- l->y();
    }
    l->draw_line((Line){Position2D(lx1,ly1), Position2D(lx2,ly2)},0xff0000, 2);
    l->draw_point(Position2D(100,200), 0xff0000, 10);
    l->draw_tri(t,0x00ff00, 1, true);

    //l->draw_tri((Triangle){
    //              .v1=Position2D(100,100),
    //              .v2=Position2D(50,150),
    //              .v3=Position2D(150,150) 
    //            },0x00ff00, 1, true);
   //l->setPos(SDLWindow::instance()->MouseX,SDLWindow::instance()->MouseY);
  /*
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
        //SDLWindow::instance()->render(p);
        freePixelBuffer(p);
   */
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
  SFLOAT data[] = {3,2,-5,1,
                   -1,0,-2,1,
                   3,-4,1,1,
                   1,2,3,4};
  //SQuaternion  m33 = SQuaternion(data);
  SQuaternion  m33 = SQuaternion(1,2,3,4);
  //SMatrix3x3 m33 = SMatrix3x3(data);
  //m33.fromArray(data);
  //m22.setAsIdentity();
  //SMatrix3x3 m3_3 = m33;
  //SMatrix3x3 m3_3_3 = m3_3 * m33;
  //m2_2.setAsIdentity();
  m33.display("m33:");
  //a2 = a1;
	extern TrueColorImage abc;
	printf("W x H --> (%d,%d)\n",abc.ImgWidth, abc.ImgHeight);
	printf("ImgTotalBytes --> %d\n",abc.ImgTotalBytes);
	printf("ImgTotalPixels --> %d\n",abc.ImgTotalPixels);
	printf("ImgByteWidth --> %d\n",abc.ImgByteWidth);
    Layer* l1 = new Layer("AAA",0,0,abc.ImgWidth, abc.ImgHeight,0);
    memcpy(l1->pixelbuf->pixels,abc.ImgData,abc.ImgTotalBytes);
    Layer* l2 = new Layer("BBB",50,50,500,300,0);
    SDLWindow::instance()->init("",640,480);
    SDLWindow::instance()->addLayer(l1);
    SDLWindow::instance()->addLayer(l2);
    Point p = Point(Position2D(100,100), 1, 0x00FFFF00);
    l1->add(&p);
    //SDLWindow::instance()->resize(abc.ImgWidth,abc.ImgHeight);
    //SDLWindow::instance()->init("ABC",abc.ImgWidth,abc.ImgHeight);
    SDLWindow::instance()->show(updatecb,eventcb);

	//api1();
	//api2();
  return 0;
}
