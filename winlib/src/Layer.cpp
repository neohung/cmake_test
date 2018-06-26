#include <stdio.h>
//#include <main.h>
//#include <testapi.h>
//#include <tcimg.h>

#include <winapi.h>
#include <SDL.h>
#include <assert.h>
Layer::Layer()
{
}

Layer::~Layer()
{
}

void Layer::update()
{
 int i;
 for(i=0;i<components.size();i++){
  components[i]->draw(pixelbuf);
  /*
   switch (components[i]->getType()){
     case 0:
       printf("0\n");
       break;
     case 1:
       printf("1\n");
       break;
     default:
       break;
   //components[i]->draw(pb);
   }
   */
 }
}

void Layer::setPos(unsigned short x, unsigned short y)
{
  PosX = x;
  PosY = y;
}

void Layer::setPos(Position2D p)
{
  PosX = p.x();
  PosY = p.y();
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

DrawBase* Layer::add(DrawBase* db)
{
  components.push_back(db);
  return db;
}
//====================

void DrawBase::findBound(Position2D* p, PFLOAT* w, PFLOAT* h)
{
  //Do sorting
  std::vector<Position2D> xsort_vector;
  std::vector<Position2D> ysort_vector;
  xsort_vector.assign(v.begin(), v.end());
  ysort_vector.assign(v.begin(), v.end());  
  int i,j;
  for(i=0;i<v.size()-1;i++){
    for(j=i;j<v.size();j++){
      
      if (xsort_vector[i].x() > xsort_vector[j].x()){
         std::swap(xsort_vector[i],xsort_vector[j]);
        }
      if (ysort_vector[i].y() > ysort_vector[j].y())
         std::swap(ysort_vector[i],ysort_vector[j]);
    }
  }
  p->setX(xsort_vector[0].x());
  p->setY(ysort_vector[0].y());
  *w = xsort_vector[v.size()-1].x() - xsort_vector[0].x();
  *h = ysort_vector[v.size()-1].y() - ysort_vector[0].y();
}
void DrawBase::drawBound(PixelBuffer* pb)
{
  Position2D bp = Position2D();
  PFLOAT bw,bh;
  findBound(&bp, &bw, &bh);
  int i,j;
  int x1 = bp.x();
  int x2 = bp.x() + bw;
  int y1 = bp.y();
  int y2 = bp.y() + bh;
  unsigned char* offset1 = (unsigned char*)pb->pixels + (y1 *  pb->bytesperline) + (pb->colors*x1);
  unsigned char* offset2 = (unsigned char*)pb->pixels + (y2 *  pb->bytesperline) + (pb->colors*x1);
  offset1--;
  offset2--;
  for(i=0;i<bw;i++){
    *(offset1++) = 128;
    *(offset1++) = 128; //G
    *(offset1++) = 128; //R
    *(offset2++) = 128;
    *(offset2++) = 128; //G
    *(offset2++) = 128; //R
  }
  for(j=0;j<bh;j++){
    offset1 = (unsigned char*)pb->pixels + ((j+y1) *  pb->bytesperline) + (pb->colors*x1);
    offset2 = (unsigned char*)pb->pixels + ((j+y1) *  pb->bytesperline) + (pb->colors*x2);
    *(offset1) = 128;
    *(offset1+1) = 128; //G
    *(offset1+2) = 128; //R
    *(offset2) = 128;
    *(offset2+1) = 128; //G
    *(offset2+2) = 128; //R
  }
}

void DrawBase::drawFill(PixelBuffer* pb)
{
  Position2D bp = Position2D();
  PFLOAT bw,bh;
  findBound(&bp, &bw, &bh);
  int i,j;
  int li = bp.x();
  int ri = bp.x()+bw;
  int uj = bp.y();
  int dj = bp.y()+bh;
  unsigned char b = 0x0000ff & color();
  unsigned char g = (0x00ff00 & color()) >> 8;
  unsigned char r = (0xff0000 & color()) >> 16;
  std::vector<Fomula1D> fomulas;
  Fomula1D fomula;
  int y2 = v[0].y();
  int x2 = v[0].x();
  int y1 = v[v.size()-1].y();
  int x1 = v[v.size()-1].x();
  double slop1 = double(y2-y1)/double(x2-x1);
  double bb1 = double(y2*x1-y1*x2)/double(x1-x2);
  fomula.slop = slop1;
  fomula.bias = bb1;
  fomulas.push_back(fomula);
  for(i=0;i<v.size()-1;i++){
    y2 = v[i+1].y();
    x2 = v[i+1].x();
    y1 = v[i].y();
    x1 = v[i].x();
    slop1 = double(y2-y1)/double(x2-x1);
    bb1 = double(y2*x1-y1*x2)/double(x1-x2);
    fomula.slop = slop1;
    fomula.bias = bb1;
    fomulas.push_back(fomula);
  }
  int k;
  //cal pos
  PFLOAT center_val = 1;
  for(k=0;k<fomulas.size();k++){
    center_val *= fomulas[k].slop*POS().x()+fomulas[k].bias-POS().y();
  }
  for(i=li;i<ri;i++){
    for(j=uj;j<dj;j++){
       PFLOAT check_val = 1;
       for(k=0;k<fomulas.size();k++){
        check_val *= fomulas[k].slop*i+fomulas[k].bias-j;
       }
       if (check_val*center_val > 0){
         unsigned char* offset = (unsigned char*)pb->pixels + (j *  pb->bytesperline) + (pb->colors*i);
         *offset = b;
         *(offset+1) = g; //G
         *(offset+2) = r; //R
       }
    }
  }
}

void Point::draw(PixelBuffer* pb)
{
  unsigned char b = 0x0000ff & color();
  unsigned char g = (0x00ff00 & color()) >> 8;
  unsigned char r = (0xff0000 & color()) >> 16;
  
  int li,ri,uj,dj;
  unsigned short posx = x();
  unsigned short posy = y();
  li = posx - size();
  ri = posx + size();
  uj = posy - size();
  dj = posy + size();
  
  if (li < 0) li = 0;
  if (ri > (pb->w-1)) ri = pb->w-1;
  if (uj < 0) uj = 0;
  if (dj > (pb->h-1)) dj = pb->h-1;
  
  int size2 = size()*size();
  int i,j;
  for(j=uj;j<dj;j++){
    for(i=li;i<ri;i++){
      int dist2 = (j-posy)*(j-posy)+(i-posx)*(i-posx);
      if (dist2 < size2){
        unsigned char* offset = (unsigned char*)pb->pixels + (j *  pb->bytesperline) + (pb->colors*i);
        *offset = b;
        *(offset+1) = g; //G
        *(offset+2) = r; //R
      }
    }
  } 
}
void Line::draw(PixelBuffer* pb)
{
  //size should be 2
  assert(v.size()==2);
  //printf("Draw LLine\n");
  unsigned char b = 0x0000ff & color();
  unsigned char g = (0x00ff00 & color()) >> 8;
  unsigned char r = (0xff0000 & color()) >> 16;
  unsigned short x2 = v[1].x();
  unsigned short x1 = v[0].x();
  unsigned short y2 = v[1].y();
  unsigned short y1 = v[0].y();
  //printf("(%d,%d)-(%d,%d), size=%f\n",x1,y1,x2,y2,size());
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
    for(k=-size();k<size();k++){
      int j;
      for(j=y1;j<y2;j++){
        int i = x1+k;
        unsigned char* offset = (unsigned char*)pb->pixels + (j *  pb->bytesperline) + (pb->colors*i);
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
    for(k=-size();k<size();k++){
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
          unsigned char* offset = (unsigned char*)pb->pixels + (j *  pb->bytesperline) + (pb->colors*i);
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
          unsigned char* offset = (unsigned char*)pb->pixels + (j *  pb->bytesperline) + (pb->colors*i);
          *offset = b;
          *(offset+1) = g; //G
          *(offset+2) = r;
        }
      }
    }
  }
}

void Triangle::draw(PixelBuffer* pb)
{
   assert(v.size()==3);
   Line l1 = Line(v[0], v[1],size(), color());
   Line l2 = Line(v[1], v[2],size(), color());
   Line l3 = Line(v[0], v[2],size(), color());
   l1.draw(pb);
   l2.draw(pb);
   l3.draw(pb);
   if (fill()){
     drawFill(pb);  
   }
   //drawBound(pb);
}

void Rectangle::draw(PixelBuffer* pb)
{
   assert(v.size()==4);
   Position2D p0 = v[0];
   Position2D p1 = v[1];
   Position2D p2 = v[2];
   Position2D p3 = v[3];
   Line l1 = Line(p0, p1, size(), color());
   Line l2 = Line(p1, p2, size(), color());
   Line l3 = Line(p2, p3, size(), color());
   Line l4 = Line(p0, p3, size(), color());
   l1.draw(pb);
   l2.draw(pb);
   l3.draw(pb);
   l4.draw(pb);
   if (fill()){
     drawFill(pb);  
   }
   //drawBound(pb);
}
