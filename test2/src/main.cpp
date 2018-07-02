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

Point pp = Point(Position2D(100,100), 5, 0x00FFFFFF);
Point* ppoint;
Triangle* ttringle;
Rectangle* rrectangle;
Cube3D* cc3d;
int pre_mousex;
int pre_mousey;
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
    case MOUSEMOTION:
    {
      //e.motion.state=1 lmouse, =2 rmouse
      //??? why * -1?
      int dx = pre_mousex - e.motion.x;
      // change y axis
      int dy = pre_mousey - e.motion.y;
      //printf("M: state:%d (%d,%d)\n",e.motion.state,dx,dy);
      if (e.motion.state == 1){
        //if (dx)
        //  cc3d->rotationY(dx);
        //if (dy)
        //  cc3d->rotationX(dy);
      }
      pre_mousex = e.motion.x;
      pre_mousey = e.motion.y;
      //printf("M: state:%d (%d,%d)\n",e.motion.state,e.motion.x,e.motion.y);
      break;
    }
    //case KEYUP:
    case KEYDOWN:
    {
      //printf("K: state:%d,key (%d)\n",e.key.state,e.key.keysym);
      if (e.key.keysym == KEY_ESCAPE){
        exit(0);
      }else if (e.key.keysym == KEY_LEFT){
        //  printf("Press ESC\n");
        //ppoint->translation(Position2D(-5,0));
        //ttringle->translation(Position2D(-5,0));
        //ttringle->rotation(-5);
        //rrectangle->rotation(-5);
        cc3d->translation(Position3D(-5,0,0));
      }else if (e.key.keysym == KEY_RIGHT){
        //ppoint->translation(Position2D(5,0));
        //ttringle->translation(Position2D(5,0));
        //ttringle->rotation(5);
        //rrectangle->rotation(5);
        cc3d->translation(Position3D(5,0,0));
      }else if (e.key.keysym == KEY_UP){
        //ppoint->translation(Position2D(0,-5));
        //ttringle->translation(Position2D(0,-5));
        cc3d->translation(Position3D(0,5,0));
      }else if (e.key.keysym == KEY_DOWN){
        //ppoint->translation(Position2D(0,5));
        //ttringle->translation(Position2D(0,5));
        cc3d->translation(Position3D(0,-5,0));
      }else if (e.key.keysym == KEY_PLUS){
        cc3d->rotationZ(5);
      }else if (e.key.keysym == KEY_MINUS){
        cc3d->rotationZ(-5);
      }else if (e.key.keysym == KEY_w){
        Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
        l->getCamera()->translation(Position3D(0,5,0));
      }else if (e.key.keysym == KEY_s){
        Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
        l->getCamera()->translation(Position3D(0,-5,0));
      }else if (e.key.keysym == KEY_a){
        Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
        l->getCamera()->translation(Position3D(-5,0,0));
      }else if (e.key.keysym == KEY_d){
        Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
        l->getCamera()->translation(Position3D(5,0,0));
      }else if (e.key.keysym == KEY_q){
        Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
        l->getCamera()->translation(Position3D(0,0,5));
      }else if (e.key.keysym == KEY_e){
        Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
        l->getCamera()->translation(Position3D(0,0,-5));

      }else{
        printf("KEY: %d\n", e.key.keysym);
      }
      break;
    }
  }
}

Line* pline;
void updatecb(PixelBuffer screenbuffer)
{
   Layer* l = SDLWindow::instance()->getLayerByName((char*)"BBB");
       l->clearDraw();
    if (mflag == 0){
      lx2 = SDLWindow::instance()->MouseX- l->x();
      ly2 = SDLWindow::instance()->MouseY- l->y();
    }
    if (pline){
      pline->setLinePos(Position2D(lx1,ly1),Position2D(lx2,ly2));
    }
}

//Plane3D* pp3d;
int main()
{
  Camera c = Camera(Position3D(0,0,0),90);
  printf("ca: %f\n",c.angle());
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
  //Point p = Point(Position2D(10,100), 10, 0x000000FF);
  Line l = Line(Position2D(100,100), Position2D(250,200),1, 0x00FFFF00);
  //Triangle t = Triangle(Position2D(100,100), Position2D(50,150),Position2D(150,150),1, 0x00FF00FF, true);
  //Triangle t = Triangle(Position2D(50,150), Position2D(100,100),Position2D(150,150),1, 0x00FF00FF, true);
  //Rectangle r = Rectangle(Position2D(300,100), 100,50,1, 0x00FF0000, true);
  //Plane3D p3d = Plane3D(Position3D(100,100,100), 100,100, 1, 0x00FF0000, true);
  Cube3D c3d = Cube3D(Position3D(100,100,100), 100,100,100, 1, 0x00FF0000, true);
  Cube3D c3d_2 = Cube3D(Position3D(200,200,200), 100,100,100, 1, 0x00FF0000, true);
  //ppoint = (Point*)l2->add(&p);
  pline = (Line*)l2->add(&l);
  //ttringle = (Triangle*)l2->add(&t);
  //rrectangle = (Rectangle*)l2->add(&r);
  ////cc3d = (Cube3D*) l2->add(&c3d);
  ////l2->add(&c3d_2);
  //SDLWindow::instance()->resize(abc.ImgWidth,abc.ImgHeight);
  //SDLWindow::instance()->init("ABC",abc.ImgWidth,abc.ImgHeight);
  SDLWindow::instance()->show(updatecb,eventcb);
  return 0;
}
