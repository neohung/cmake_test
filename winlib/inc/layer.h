#ifndef __LAYER_H__
#define __LAYER_H__

//#include <winapi.h>

typedef struct{
  unsigned short w;
  unsigned short h;
  unsigned char colors;
  unsigned short bytesperline;
  unsigned long int size;
  void* freePtr;
  void* pixels;
} PixelBuffer;

class Layer
{
  protected:
  public:
    char* Name;
    size_t Width;
    size_t Height;
    unsigned char order;
    bool IsSkip;
    PixelBuffer* pixelbuf;
    Layer();
    Layer(const char* name,int x, int y, size_t w, size_t h,unsigned int color);
    ~Layer();
    void setPos(int x, int y);
    //void setPos(Position2D p);
    void update();
    void clearDraw();
    inline int x() {return PosX;};
    inline int y() {return PosY;};
    //DrawBase* add(DrawBase* db);
    //DrawBase3D* add(DrawBase3D* db);
    //void update_perspective_projection(DrawBase3D* db3);
    //Camera* getCamera(){return &camera;};
    void setPixel(int x, int y,int color);
  private:
     //Camera camera;
     //std::vector<DrawBase*> components;
     //std::vector<DrawBase3D*> components3D;
     int PosX;
     int PosY;
};

#endif
