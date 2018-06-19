#ifndef __WINAPI_H__
#define __WINAPI_H__

#include <vector>

#define STATE_RELEASED 0
#define STATE_PRESSED	1
#define MOUSE_BUTTON_LEFT 1
#define MOUSE_BUTTON_MIDDLE 2
#define MOUSE_BUTTON_RIGHT 3

#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_RIGHT 79
#define KEY_LEFT 80
#define KEY_DOWN 81
#define KEY_UP 82

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

typedef struct{
  int x;
  int y;
} Vec2;

typedef struct{
  int x;
  int y;
  int z;
} Vec3;

typedef struct{
  int x;
  int y;
  unsigned int w;
  unsigned int h;
} Rect;

typedef struct{
  Vec2 v1;
  Vec2 v2;
} Line;

typedef struct{
  Vec2 v1;
  Vec2 v2;
  Vec2 v3;
} Triangle;

class Layer
{
  protected:
  public:
    char* Name;
    unsigned short PosX;
    unsigned short PosY;
    unsigned short Width;
    unsigned short Height;
    unsigned char order;
    bool IsSkip;
    PixelBuffer* pixelbuf;
    Layer();
    Layer(const char* name,unsigned short x, unsigned short y, unsigned short w, unsigned short h,unsigned int color);
    ~Layer();
    void setPos(unsigned short x, unsigned short y);
    void update(PixelBuffer* pb);
    void draw_line(unsigned short x1,unsigned short y1, unsigned short x2,unsigned short y2,unsigned int color, unsigned char size);
    void draw_point(unsigned short x,unsigned short y, unsigned int color, unsigned char size);
    void draw_tri(Triangle tri,unsigned int color, unsigned char size, bool is_fill);
    void clearDraw();
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
