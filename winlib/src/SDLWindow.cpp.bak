#include <stdio.h>
//#include <main.h>
//#include <testapi.h>
//#include <tcimg.h>

#include <winapi.h>
#include <SDL.h>

//For Singleton the static need to init first
SDLWindow* SDLWindow::s_instance = 0;

void SDLWindow::init(const char* title, unsigned short w, unsigned short h)
{
	Width=w;
	Height=h;
	DELAYTIME=10;
	MouseX = 100;
	MouseY = 100;
	//extern TrueColorImage abc;
	//INIT SDL
	if (SDL_Init( SDL_INIT_VIDEO)  < 0 ){
    fprintf(stderr, "Unable to initialize SDL: %s\n",SDL_GetError());
      exit(1);
    }
    //
    atexit(SDL_Quit);
    SDL_Window* win = SDL_CreateWindow(title,
                              //SDL_WINDOWPOS_UNDEFINED,
                              //SDL_WINDOWPOS_UNDEFINED,
    	                      SDL_WINDOWPOS_CENTERED,
    	                      SDL_WINDOWPOS_CENTERED,
                              Width, Height,
                              //SDL_WINDOW_FULLSCREEN | 
                              SDL_WINDOW_OPENGL);
    Window.handle = win;
    SDL_GetWindowSize( (SDL_Window*)Window.handle, &Window.w, &Window.h);
    SDL_GetWindowPosition( (SDL_Window*)Window.handle, &Window.posx, &Window.posy);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);   
    //EVERY TIME RESIZE NEED TO GET SCREEN AGAIN
    //SDL_SetWindowSize(Window,abc.ImgWidth,abc.ImgHeight);
    SDL_Surface* sf = SDL_GetWindowSurface((SDL_Window*)Window.handle);
    Screen.freePtr = (void*)sf;
    Screen.pixels = sf->pixels;
    Screen.w = sf->w;
    Screen.h = sf->h;
    Screen.bytesperline = sf->pitch;
    Screen.colors = sf->pitch/sf->w;
    Screen.size = sf->pitch* sf->h;
}

void SDLWindow::resize(unsigned short w,unsigned short h)
{
    SDL_SetWindowSize((SDL_Window*)Window.handle,w,h);
    SDL_Surface* sf = SDL_GetWindowSurface((SDL_Window*)Window.handle);
    Screen.freePtr = (void*)sf;
    Screen.pixels = sf->pixels;
    Screen.w = sf->w;
    Screen.h = sf->h;
    Screen.bytesperline = sf->pitch;
    Screen.colors = sf->pitch/sf->w;
    Screen.size = sf->pitch* sf->h;
}
SDLWindow::~SDLWindow()
{

}
int SDLWindow::show(void (*u_cb)(PixelBuffer screenbuffer),void (*e_cb)(WINEVENT e))
{
	event_cb=e_cb;
	update_cb=u_cb;
	while (1)
	{
		if (update_cb)
			update_cb(Screen);
                //
                if (layers.size() > 0){
                  //printf("%dx%d %d, %d, %d\n",Width, Height, Screen.size, Screen.bytesperline, Screen.h);
                  PixelBuffer*  p = createPixelBuffer(Width , Height, 24);
                  SDL_BlitSurface((SDL_Surface*)Screen.freePtr, NULL, (SDL_Surface*)p->freePtr, NULL);
                  int i;
                  for(i=0;i<layers.size();i++){
                  //Layer* l = layers[0];
                     layers[i]->update();
                     int j = 0;
                     unsigned char* dst_offset = (unsigned char*)p->pixels + (layers[i]->y() * p->bytesperline )+ (layers[i]->pixelbuf->colors*layers[i]->x());
                     unsigned char* src_offset = (unsigned char*)layers[i]->pixelbuf->pixels;
                     while(j<layers[i]->Height){
                       dst_offset += p->bytesperline;
                       src_offset += layers[i]->pixelbuf->bytesperline;
                       //memcpy(p->pixels, layers[i]->pixelbuf->pixels , layers[i]->pixelbuf->size);
                       memcpy(dst_offset, src_offset , layers[i]->pixelbuf->bytesperline);
                       j++;
                     }
                    //render(layers[i]->pixelbuf);    
                  }
                  render(p);    
                  freePixelBuffer(p);            
                }
                //
		SDL_UpdateWindowSurface((SDL_Window*)Window.handle);
		SDL_Delay(DELAYTIME);
		 SDL_Event event;
		 while (SDL_PollEvent(&event)){
		 	switch (event.type)
		 	{
		 		case SDL_MOUSEMOTION:
		 		{ 
		 			int x,y;
		 			SDL_GetMouseState( &x, &y );
		 			MouseX = x;
		 			MouseY = y;
                                        //
                                        if (event_cb){
                                           WINEVENT wine;
                                           wine.motion.type = MOUSEMOTION;
                                           wine.motion.state = event.motion.state; //0 lmouse, 1 rmouse
                                           wine.motion.x = event.motion.x;
                                           wine.motion.y = event.motion.y;
                                           event_cb(wine);
                                        }
		 			break;
		 		}
		 		case SDL_QUIT:
		 		{
		 		//printf("Trigger SDL_QUIT\n");
		 			goto QUITPOINT;
		 			break;
		 		}
                                case SDL_MOUSEBUTTONDOWN:
                                {
                                        if (event_cb){
                                           WINEVENT wine;
                                           wine.button.type = MOUSEBUTTONDOWN;
                                           wine.button.state = event.button.state;
                                           wine.button.button = event.button.button; 
                                           wine.button.x = event.button.x; 
                                           wine.button.y = event.button.y; 
                                           event_cb(wine);
                                        }
                                        break;
                                }
                                case SDL_MOUSEBUTTONUP:
                                {
                                        if (event_cb){
                                           WINEVENT wine;
                                           wine.button.type = MOUSEBUTTONUP;
                                           wine.button.state = event.button.state;
                                           wine.button.button = event.button.button; 
                                           wine.button.x = event.button.x; 
                                           wine.button.y = event.button.y; 
                                           event_cb(wine);
                                        }
                                        break;
                                }
                                case SDL_KEYUP:
                                {
                                       if (event_cb){
                                           WINEVENT wine;
                                           wine.key.type = KEYUP;
                                           wine.key.state = event.key.state;
                                           wine.key.keysym = event.key.keysym.sym;
                                           event_cb(wine);
                                       }
                                       break;
                                }
                                case SDL_KEYDOWN:
                                {
                                       if (event_cb){
                                           WINEVENT wine;
                                           wine.key.type = KEYDOWN;
                                           wine.key.state = event.key.state;
                                           wine.key.keysym = event.key.keysym.sym;
                                           event_cb(wine);
                                       }
                                       break;
                                }

		 		default:
		 		{
		 			break;
		 		}
		 	}
		 }
	} 
	QUITPOINT:
	return EXIT_SUCCESS;
	exit(0);
}


Layer* SDLWindow::getLayerByName(char* n)
{
  int i;
  for(i=0;i<layers.size();i++){
    if (strcmp (n,layers[i]->Name) == 0)
      return layers[i];
  }
  return NULL;
}

void SDLWindow::render(PixelBuffer* pb){
  SDL_Surface* sf = SDL_GetWindowSurface((SDL_Window*)Window.handle);
  SDL_BlitSurface((SDL_Surface*)pb->freePtr, NULL, sf, NULL);
}


void SDLWindow::addLayer(Layer* l)
{
  //printf("Add Layer\n");
  layers.push_back(l);
}


PixelBuffer* createPixelBuffer(unsigned short w, unsigned short h, unsigned char colorbit){
  
 //colorbit = 24;a
 PixelBuffer *pb = (PixelBuffer *) malloc(sizeof(PixelBuffer));
 SDL_Surface *tmp = SDL_CreateRGBSurface(0, w, h, colorbit,  0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
 //printf("tmp->pitch=%d, (%d,%d)\n",tmp->pitch,tmp->w,tmp->h);
 pb->freePtr = (void*)tmp;
 pb->pixels = tmp->pixels;
 pb->w = tmp->w;
 pb->h = tmp->h;
 pb->bytesperline = tmp->pitch;
 pb->colors = tmp->pitch/tmp->w;
 pb->size = tmp->pitch* tmp->h;
 //printf("pb (%d,%d) perline %d , size %d\n",pb->w, pb->h, pb->bytesperline, pb->size);
 return pb;   
}
void freePixelBuffer(PixelBuffer* pb){
   SDL_FreeSurface((SDL_Surface*)pb->freePtr);
   free(pb);
}
