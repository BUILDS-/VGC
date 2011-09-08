//Compile with g++ test.cc -o test -lSDL

#include "SDL/SDL.h"

int main(int argc, char* argv[]) {
  
  SDL_Surface* hello = NULL;
  SDL_Surface* screen = NULL;

  //Start SDL
  SDL_Init(SDL_INIT_EVERYTHING);

  screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

  hello = SDL_LoadBMP( "images/hello.bmp" );

  SDL_BlitSurface(hello, NULL, screen, NULL);
  
  SDL_Flip(screen);

  SDL_Delay(2000);

  SDL_FreeSurface(hello);

  //Quit SDL
  SDL_Quit();

  return 0;
}
