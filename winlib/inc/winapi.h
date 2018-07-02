#ifndef __WINAPI_H__
#define __WINAPI_H__

#include <vector>

#define STATE_RELEASED 0
#define STATE_PRESSED	1
#define MOUSE_BUTTON_LEFT 1
#define MOUSE_BUTTON_MIDDLE 2
#define MOUSE_BUTTON_RIGHT 3

#define KEY_PLUS 87 // "+"
#define KEY_MINUS 86 // "-"
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_RIGHT 79
#define KEY_LEFT 80
#define KEY_DOWN 81
#define KEY_UP 82
#define KEY_w 119
#define KEY_s 115
#define KEY_a 97
#define KEY_d 100
#define KEY_e 101
#define KEY_q 113
#define KEY_z 122
#define KEY_c 99
#define KEY_x 120

#include <smath.h>
#include <math.h>

typedef enum {
       NOEVENT = 0,			
       KEYDOWN,	
       KEYUP,
       MOUSEMOTION,
       MOUSEBUTTONDOWN,	
       MOUSEBUTTONUP,
       QUIT,
       NUMEVENTS = 32
} EventType;

typedef struct{
  unsigned char type; //1:KEYUP or 2:KEYDOWN
  unsigned char state; //Press / Release
  unsigned char keysym;
} KEvent;

typedef struct{
  unsigned char type; //3:MOTION
  unsigned char state; //Button state, 1:r_mouse , 2: l_mouse
  unsigned short x, y;
} MEvent;

typedef struct{
  unsigned char type; //4:MOUSE_BTN_UP, 5:MOUSE_BTN_DOWN
  unsigned char state; //Button state, Press / Release
  unsigned char button; // 1:r_mouse , 2: l_mouse
  unsigned short x, y;
} BEvent;

typedef struct{
  unsigned char type; //6: Expose
} EEvent;

typedef struct{
  unsigned char type; //7: Resize
  unsigned short w, h;
} REvent;

typedef struct{
  unsigned char type; //8: Quit
} QEvent;

typedef union{
  unsigned char type;
  KEvent key;
  MEvent motion;
  BEvent button;
  REvent resize;
  EEvent expose;
  QEvent quit;
} WINEVENT;


typedef struct{
  unsigned short w;
  unsigned short h;
  unsigned char colors;
  unsigned short bytesperline;
  unsigned long int size;
  void* freePtr;
  void* pixels;
} PixelBuffer;

PixelBuffer* createPixelBuffer(unsigned short w, unsigned short h, unsigned char colorbit);
void freePixelBuffer(PixelBuffer* pb);

typedef SVector2 Position2D;

typedef SVector3 Position3D;

typedef SFLOAT PFLOAT;

typedef struct {
  PFLOAT slop;
  PFLOAT bias;
}Fomula1D;

class DrawBase
{
public:
  DrawBase():is_skip(false),type(0), is_fill(false){};
  DrawBase(unsigned char t):is_skip(false),type(t){};
  inline PFLOAT size() {return s;};
  inline unsigned int color() {return c;};
  inline bool skip() {return is_skip;};
  inline bool fill() {return is_fill;};
  inline Position2D POS() {return pos;};
  unsigned char getType() {return type;};
  void setSize(PFLOAT size) { s=size;};
  void setColor(unsigned int color) { c=color;};
  void setSkip(bool skip) { is_skip=skip;};
  void setFill(bool fill) { is_fill=fill;};
  virtual void draw(PixelBuffer* pb){};
  void translation(Position2D p)
  {
    pos += p;
    int i;
    for(int i=0;i<v.size();i++){
      v[i] += p;
    }
  };
  void rotation(PFLOAT degree){
    // [cos -sin]
    // [sin  cos]
    PFLOAT rad = degree*SMATH_DEGREE_TO_RAD;
    PFLOAT m[] = {cos(rad),-sin(rad),sin(rad),cos(rad)};
    SMatrix2x2 m22 = SMatrix2x2();
    m22.fromArray(m);    
    for(int i=0;i<v.size();i++){
      v[i] -= pos;
      v[i] *= m22;
      v[i] += pos;
      //v[i] = m22 * (v[i] - pos) + pos;
      //v[i] = (v[i] - pos) * m22 + pos;
    }
  }
  inline PFLOAT x() {return pos.x();};
  inline PFLOAT y() {return pos.y();};
  void setPos(Position2D p) { 
    Position2D dist = p - pos;
    translation(dist);
  };
  void findBound(Position2D* p, PFLOAT* w, PFLOAT* h);
  inline bool inBuffer(PixelBuffer* pb,int i, int j){
    if ((i>=0)&&(j>=0)){
      if ((i<pb->w)&&(j<pb->h)){
        return true;
      }
    }
    return false;
  };
protected:
  void drawFill(PixelBuffer* pb);
  void drawBound(PixelBuffer* pb);
  std::vector<Position2D> v;
  Position2D pos;
  bool is_fill;
private:
  unsigned char type;
  bool is_skip;
  PFLOAT s;
  unsigned int c;
};

class Point : public DrawBase
{
public:
  Point(Position2D p, PFLOAT size, unsigned int color):
  DrawBase(1)
  { 
    setPos(p);
    setSize(size);
    setColor(color);
    v.clear();
    v.push_back(p);
  };
  virtual void draw(PixelBuffer* pb);
private:
};

class Line : public DrawBase
{
public:
  Line(Position2D p1,Position2D p2, PFLOAT size, unsigned int color):
  DrawBase(2)
  { 
    setPos((p1+p2)*0.5);
    setSize(size);
    setColor(color);
    v.clear();
    v.push_back(p1);
    v.push_back(p2);
  };
  void setLinePos(Position2D p1,Position2D p2) { 
    setPos((p1+p2)*0.5);
    v.clear();
    v.push_back(p1);
    v.push_back(p2);
  };
  virtual void draw(PixelBuffer* pb);
private:
};

class Triangle : public DrawBase
{
public:
  Triangle(Position2D p1,Position2D p2, Position2D p3 , PFLOAT size, unsigned int color, bool fill):
  DrawBase(3)
  {
    setFill(fill);
    setPos((((p1+p2)*0.5)+p3)*0.5);
    setSize(size);
    setColor(color);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    //is_fill=fill;
  };
  void setTriPos(Position2D p1, Position2D p2, Position2D p3) {
    setPos((((p1+p2)*0.5)+p3)*0.5);
    v.clear();
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
  }
  virtual void draw(PixelBuffer* pb);
  //Overwrite drawFill()
  void drawFill(PixelBuffer* pb);
private:
};

class Rectangle : public DrawBase
{
public:
  Rectangle(Position2D p0, PFLOAT width, PFLOAT height , PFLOAT size, unsigned int color, bool fill):
  DrawBase(4), w(width), h(height)
  {
    setFill(fill);
    Position2D p1 = p0 + Position2D(0,h);
    Position2D p2 = p1 + Position2D(w,0);
    Position2D p3 = p0 + Position2D(w,0);
    setPos((p0+p2)*0.5);
    setSize(size);
    setColor(color);
    v.push_back(p0);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
  }
  inline PFLOAT width() {return w;};
  inline PFLOAT height() {return h;};
  inline void setHieght(PFLOAT height) {h = height;};
  inline void setWidth(PFLOAT width) {w = width;};
  virtual void draw(PixelBuffer* pb);
private:
  PFLOAT w;
  PFLOAT h;
};

class DrawBase3D
{
public:
  DrawBase3D():is_skip(false),type(0), is_fill(false){};
  DrawBase3D(unsigned char t):is_skip(false),type(t){};
  inline PFLOAT size() {return s;};
  inline unsigned int color() {return c;};
  inline bool skip() {return is_skip;};
  inline bool fill() {return is_fill;};
  inline Position3D POS() {return pos;};
  unsigned char getType() {return type;};
  void setSize(PFLOAT size) { s=size;};
  void setColor(unsigned int color) { c=color;};
  void setSkip(bool skip) { is_skip=skip;};
  void setFill(bool fill) { is_fill=fill;};
  virtual void draw(PixelBuffer* pb){};
  void translation(Position3D p)
  {
    pos += p;
    int i;
    for(int i=0;i<v.size();i++){
      v[i] += p;
    }
  };
  void rotationX(PFLOAT degree){
    // [1    0    0  ]
    // [ 0  cos -sin ]
    // [ 0  sin  cos ]
    // 
    PFLOAT rad = degree*SMATH_DEGREE_TO_RAD;
    PFLOAT m[] = {1,0,0,0,cos(rad),-sin(rad),0,sin(rad),cos(rad)};
    SMatrix3x3 m33 = SMatrix3x3();
    m33.fromArray(m);    
    for(int i=0;i<v.size();i++){
      v[i] -= pos;
      v[i] *= m33;
      v[i] += pos;
      //v[i] = m33 * (v[i] - pos) + pos;
      //v[i] = (v[i] - pos) * m33 + pos;
    }
  }
  void rotationY(PFLOAT degree){
    // [ cos  0 sin ]
    // [  0   1  0  ]
    // [ -sin 0 cos ]
    // 
    PFLOAT rad = degree*SMATH_DEGREE_TO_RAD;
    PFLOAT m[] = {cos(rad),0,sin(rad),0,1,0,-sin(rad),0,cos(rad)};
    SMatrix3x3 m33 = SMatrix3x3();
    m33.fromArray(m);
    for(int i=0;i<v.size();i++){
      v[i] -= pos;
      v[i] *= m33;
      v[i] += pos;
      //v[i] = m33 * (v[i] - pos) + pos;
      //v[i] = (v[i] - pos) * m33 + pos;
    }
  }
  void rotationZ(PFLOAT degree){
    // [ cos -sin  0 ]
    // [ sin  cos  0 ]
    // [  0    0   1 ]
    // 
    PFLOAT rad = degree*SMATH_DEGREE_TO_RAD;
    PFLOAT m[] = {cos(rad),-sin(rad),0,sin(rad),cos(rad),0,0,0,1};
    SMatrix3x3 m33 = SMatrix3x3();
    m33.fromArray(m);
    for(int i=0;i<v.size();i++){
      v[i] -= pos;
      v[i] *= m33;
      v[i] += pos;
      //v[i] = m33 * (v[i] - pos) + pos;
      //v[i] = (v[i] - pos) * m33 + pos;
    }
  }
  inline PFLOAT x() {return pos.x();};
  inline PFLOAT y() {return pos.y();};
  inline PFLOAT z() {return pos.z();};
  void setPos(Position3D p) { 
    Position3D dist = p - pos;
    translation(dist);
  };
  //void findBound(Position2D* p, PFLOAT* w, PFLOAT* h);
  std::vector<Position2D> v2d;
  std::vector<Position3D> v;
protected:
  Position3D pos;
  bool is_fill;
private:
  unsigned char type;
  bool is_skip;
  PFLOAT s;
  unsigned int c;
};

class Plane3D : public DrawBase3D
{
public:
  Plane3D(Position3D p0, PFLOAT width,PFLOAT height,PFLOAT size, unsigned int color, bool fill)
  {
    setFill(fill);
    setHieght(height);
    setWidth(width);
    //PFLOAT z = p0.z();
    Position3D p1 = p0 + Position3D(0,h,0);
    Position3D p2 = p1 + Position3D(w,0,0);
    Position3D p3 = p0 + Position3D(w,0,0);
    setPos((p0+p2)*0.5);
    setSize(size);
    setColor(color);
    v.push_back(p0);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
  };
  virtual void draw(PixelBuffer* pb);
  inline PFLOAT width() {return w;};
  inline PFLOAT height() {return h;};
  inline void setHieght(PFLOAT height) {h = height;};
  inline void setWidth(PFLOAT width) {w = width;};
private:
  PFLOAT w;
  PFLOAT h;
};

class Cube3D : public DrawBase3D
{
public:
  Cube3D(Position3D p0, PFLOAT width,PFLOAT height,PFLOAT length,PFLOAT size, unsigned int color, bool fill)
  {
    setFill(fill);
    setHieght(height);
    setWidth(width);
    setLength(length);
    //PFLOAT z = p0.z();
    Position3D p1 = p0 + Position3D(w,0,0);
    Position3D p2 = p1 + Position3D(0,h,0);
    Position3D p3 = p2 + Position3D(-w,0,0);
    Position3D p4 = p0 + Position3D(0,0,l);
    Position3D p5 = p4 + Position3D(w,0,0);
    Position3D p6 = p5 + Position3D(0,h,0);
    Position3D p7 = p6 + Position3D(-w,0,0);
    setPos((p0+p1+p2+p3+p4+p5+p6+p7)*0.125);
    setSize(size);
    setColor(color);
    v.push_back(p0);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);
    v.push_back(p6);
    v.push_back(p7);
  };
  virtual void draw(PixelBuffer* pb);
  inline PFLOAT width() {return w;};
  inline PFLOAT height() {return h;};
  inline PFLOAT length() {return l;};
  inline void setHieght(PFLOAT height) {h = height;};
  inline void setWidth(PFLOAT width) {w = width;};
  inline void setLength(PFLOAT length) {l = length;};
private:
  PFLOAT w;
  PFLOAT h;
  PFLOAT l;
};

typedef struct Camera{
  Position3D pos;
  PFLOAT theta;
  Camera(){};
  //use degree
  Camera(Position3D p, PFLOAT angle){
    pos = p;
    theta = angle*SMATH_DEGREE_TO_RAD;
  }
  inline PFLOAT angle(){return theta;};
  inline PFLOAT x(){return pos.x();};
  inline PFLOAT y(){return pos.y();};
  inline PFLOAT z(){return pos.z();};
  inline void setCamera(Position3D p,  PFLOAT angle){
    pos = p;
    theta = angle*SMATH_DEGREE_TO_RAD;
  };
  inline void translation(Position3D p)
  {
    pos += p;
  };
} _Camera;

typedef struct{
  Position2D pos;
  PFLOAT w;
  PFLOAT h;
} Rect;

class Layer
{
  protected:
  public:
    char* Name;
    unsigned short Width;
    unsigned short Height;
    unsigned char order;
    bool IsSkip;
    PixelBuffer* pixelbuf;
    Layer();
    Layer(const char* name,unsigned short x, unsigned short y, unsigned short w, unsigned short h,unsigned int color);
    ~Layer();
    void setPos(unsigned short x, unsigned short y);
    void setPos(Position2D p);
    void update();
    void clearDraw();
    inline unsigned short x() {return PosX;};
    inline unsigned short y() {return PosY;};
    DrawBase* add(DrawBase* db);
    DrawBase3D* add(DrawBase3D* db);
    void update_perspective_projection(DrawBase3D* db3);
    Camera* getCamera(){return &camera;};
  private:
     Camera camera;
     std::vector<DrawBase*> components;
     std::vector<DrawBase3D*> components3D;
     unsigned short PosX;
     unsigned short PosY;
};


typedef struct{
  int w;
  int h;
  int posx;
  int posy;
  void* handle;
} WINDOW;

//typedef void * SCREEN;
//typedef void * WINDOW;

class SDLWindow
{
  protected:
        static SDLWindow *s_instance;
        unsigned int DELAYTIME;
        void (* event_cb)(WINEVENT e);
        void (* update_cb)(PixelBuffer screenbuffer);
        //SDL_Window* Window;
        WINDOW Window;
public:
        std::vector<Layer*> layers;
        void addLayer(Layer* l);
        unsigned short MouseX;
        unsigned short MouseY;
        unsigned short Width;
        unsigned short Height;
        SDLWindow(){};
        void init(const char* title, unsigned short w, unsigned short h);
        ~SDLWindow();
        int show(void (*u_cb)(PixelBuffer screenbuffer),void (*e_cb)(WINEVENT e));
        void render(PixelBuffer* pb);
        //void resize(unsigned short w, unsigned short h);
        void resize(unsigned short w,unsigned short h);
        Layer* getLayerByName(char* n);
        //SDL_Surface* Screen;
        PixelBuffer Screen;
        static SDLWindow *instance(void)
        {
          if (!s_instance)
            s_instance = new SDLWindow;
          return s_instance;
        }
};
//For Singleton the static need to init first
//SDLWindow* SDLWindow::s_instance = 0;

#endif
