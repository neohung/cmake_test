#ifndef __SDLWINAPI_H__
#define __SDLWINAPI_H__

#include <winapi.h>

class SDLWindow : public Window{
public:
  //Override
  void init(const char* title, size_t w, size_t h);
};

#endif
