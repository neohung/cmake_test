#include <stdio.h>
#include <main.h>
#include <testapi.h>
#include <tcimg.h>

#include <SDL.h>
//#include <SDL2/SDL.h>

class SDLWindow
{
public:
	SDLWindow(const char* title, unsigned short w, unsigned short h, void (* e_cb)(SDL_Event e));
	~SDLWindow();
	int show();
protected:
	unsigned int DELAYTIME;
	unsigned short Width;
	unsigned short Height;
	unsigned short MouseX;
	unsigned short MouseY;
	void (* event_cb)(SDL_Event e);
	SDL_Window* Window;
	SDL_Surface* Screen;

};

SDLWindow::SDLWindow(const char* title, unsigned short w, unsigned short h, void (*e_cb)(SDL_Event e)):
Width(w), Height(h), DELAYTIME(10), event_cb(e_cb)
{
	extern TrueColorImage abc;
	//INIT SDL
	if (SDL_Init( SDL_INIT_VIDEO)  < 0 ){
    fprintf(stderr, "Unable to initialize SDL: %s\n",SDL_GetError());
      exit(1);
    }
    //
    atexit(SDL_Quit);
    //
    Window = SDL_CreateWindow(title,
                              //SDL_WINDOWPOS_UNDEFINED,
                              //SDL_WINDOWPOS_UNDEFINED,
    	                      SDL_WINDOWPOS_CENTERED,
    	                      SDL_WINDOWPOS_CENTERED,
                              Width, Height,
                              //SDL_WINDOW_FULLSCREEN | 
                              SDL_WINDOW_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    /*
    SDL_Surface *screen1 = SDL_CreateRGBSurfaceFrom(abc.ImgData, abc.ImgWidth, abc.ImgHeight, 24,
     	                                 abc.ImgByteWidth,
                                         0x00FF0000,
                                         0x0000FF00,
                                         0x000000FF,
                                         0xFF000000);
    */

    SDL_Surface *screen2 = SDL_CreateRGBSurface(0, abc.ImgWidth, abc.ImgHeight, 24,  
    	                                 0x00FF0000,
                                         0x0000FF00,
                                         0x000000FF,
                                         0xFF000000);
    memcpy(screen2->pixels,abc.ImgData,abc.ImgTotalBytes);
    //SDL_Surface *screen2 = SDL_CreateRGBSurface(0, Width, Height, 32, 255, 255, 255, 0);
    //SDL_LockSurface( Screen );
    //EVERY TIME RESIZE NEED TO GET SCREEN AGAIN
    SDL_SetWindowSize(Window,abc.ImgWidth,abc.ImgHeight);
    Screen = SDL_GetWindowSurface(Window);
    SDL_BlitSurface(screen2, NULL, Screen, NULL); // blit it to the screen
    //SDL_UnlockSurface( Screen );
    SDL_FreeSurface(screen2);
    SDL_UpdateWindowSurface(Window);

}

SDLWindow::~SDLWindow()
{

}

int SDLWindow::show()
{
	while (1)
	{
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
		 			break;
		 		}
		 		case SDL_QUIT:
		 		{
		 		//printf("Trigger SDL_QUIT\n");
		 			goto QUITPOINT;
		 			break;
		 		}
		 		default:
		 		{
		 			//printf("EVENT e %d\n", event.type);
		 			if (event_cb)
		 				event_cb(event);
		 				//printf("EVENT e %d\n", event.type);
		 			break;
		 		}
		 	}
		 }
	} 
	QUITPOINT:
	return EXIT_SUCCESS;
	exit(0);
}

void eventcb(SDL_Event e)
{
	switch (e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{ 
			printf("M: %d,%d\n",e.button.x,e.button.y);
		}
		case SDL_KEYUP:
		{
			if (e.key.keysym.sym == SDLK_ESCAPE){
				//SDL_DestroyWindow(window);
				//SDL_Quit();
				printf("Press ESC\n");
				exit(0);
			}
			break;
       }
	}
}

int main()
{
	extern TrueColorImage abc;
	printf("W x H --> (%d,%d)\n",abc.ImgWidth, abc.ImgHeight);
	printf("ImgTotalBytes --> %d\n",abc.ImgTotalBytes);
	printf("ImgTotalPixels --> %d\n",abc.ImgTotalPixels);
	printf("ImgByteWidth --> %d\n",abc.ImgByteWidth);

	SDLWindow win = SDLWindow("",640,480, eventcb);
	win.show();
    


	api1();
	api2();
  return 0;
}
