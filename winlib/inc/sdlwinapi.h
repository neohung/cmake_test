#ifndef __SDLWINAPI_H__
#define __SDLWINAPI_H__

#include <winapi.h>

class SDLWindow : public Singleton<SDLWindow>, public Window
{
public:
   SDLWindow(){printf("First SDLWindow\n");};
  //Override
  void init(const char* title, int w, int h);
  int show(void (*e_cb)(WINEVENT e));
};

#endif
