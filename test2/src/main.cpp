#include <stdio.h>
#include <main.h>
#include <testapi.h>
#include <tcimg.h>

#include <SDL.h>

class SDLWindow
{
  protected:
	static SDLWindow *s_instance;
	unsigned int DELAYTIME;
	void (* event_cb)(SDL_Event e);
	void (* update_cb)(SDL_Surface* screenbuffer);
	SDL_Window* Window;
public:
	unsigned short MouseX;
	unsigned short MouseY;
	unsigned short Width;
	unsigned short Height;
	SDLWindow(){};
	void init(const char* title, unsigned short w, unsigned short h);
	~SDLWindow();
	int show(void (*u_cb)(SDL_Surface* screenbuffer),void (*e_cb)(SDL_Event e));
	void resize(unsigned short w, unsigned short h);
	SDL_Surface* Screen;
	static SDLWindow *instance(void)
    {	
        if (!s_instance)
          s_instance = new SDLWindow;
        return s_instance;
    }
};
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
    //EVERY TIME RESIZE NEED TO GET SCREEN AGAIN
    //SDL_SetWindowSize(Window,abc.ImgWidth,abc.ImgHeight);
    Screen = SDL_GetWindowSurface(Window);
}

SDLWindow::~SDLWindow()
{

}

int SDLWindow::show(void (*u_cb)(SDL_Surface* screenbuffer),void (*e_cb)(SDL_Event e))
{
	event_cb=e_cb;
	update_cb=u_cb;
	while (1)
	{
		if (update_cb)
			update_cb(Screen);
		SDL_UpdateWindowSurface(Window);
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

int c=0;
void updatecb(SDL_Surface* screenbuffer)
{
	extern TrueColorImage abc;
	 /*
    SDL_Surface *screen1 = SDL_CreateRGBSurfaceFrom(abc.ImgData, abc.ImgWidth, abc.ImgHeight, 24,
     	                                 abc.ImgByteWidth,
                                         0x00FF0000,
                                         0x0000FF00,
                                         0x000000FF,
                                         0xFF000000);
    */    
	SDL_Surface *screen2 = SDL_CreateRGBSurface(0, abc.ImgWidth, abc.ImgHeight, 24,  0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	memcpy(screen2->pixels,abc.ImgData,abc.ImgTotalBytes);
        c++;
        if (c > 255) c= 0;
 
	int i,j;
	for (j=-20;j<20;j++)
	  for (i=-20;i<20;i++){
                int jj = SDLWindow::instance()->MouseY+j;
                int ii = SDLWindow::instance()->MouseX+i;
                if ((jj > 5) && (ii > 5) && (jj < SDLWindow::instance()->Height-5) && (ii < SDLWindow::instance()->Width-5)){
	  	  unsigned char* offset = (unsigned char*)(screen2->pixels) + (((SDLWindow::instance()->MouseY+j) * screen2->pitch)+ 3*(SDLWindow::instance()->MouseX+i));
	  	  offset[0] = 0;
	  	  offset[1] = 0;
	  	  offset[2] = 255;
                }
	  }
	//memcpy(screen2->pixels,screenbuffer,abc.ImgTotalBytes);
	SDL_BlitSurface(screen2, NULL, screenbuffer, NULL); // blit it to the screen
	//SDL_UnlockSurface( screenbuffer );
	//SDL_LockSurface( screenbuffer );
	
	SDL_FreeSurface(screen2);
}

int main()
{
	extern TrueColorImage abc;
	printf("W x H --> (%d,%d)\n",abc.ImgWidth, abc.ImgHeight);
	printf("ImgTotalBytes --> %d\n",abc.ImgTotalBytes);
	printf("ImgTotalPixels --> %d\n",abc.ImgTotalPixels);
	printf("ImgByteWidth --> %d\n",abc.ImgByteWidth);

    //SDLWindow::instance()->init("",640,480);
    SDLWindow::instance()->init("ABC",abc.ImgWidth,abc.ImgHeight);
    SDLWindow::instance()->show(updatecb,eventcb);

	//api1();
	//api2();
  return 0;
}
