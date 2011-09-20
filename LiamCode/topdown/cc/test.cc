//Compile with g++ test.cc -o test -lSDL

#include "SDL/SDL.h"
#include <string>


//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface *hello = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

SDL_Surface *load_image(std::string filename) {

  //Temporary storage for the image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized image that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = SDL_LoadBMP(filename.c_str());

  //If nothing went wrong in loading the image
  if(loadedImage != NULL) {
	//Create an optimize image
	optimizedImage = SDL_DisplayFormat(loadedImage);
	//Free the old image
	SDL_FreeSurface(loadedImage);
  }

  return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
  
  //Make a temporary rectangle to hold the offset
  SDL_Rect offset;

  //Give the offsets to the rectangle
  offset.x = x;
  offset.y = y;

  //Blit surface. surface ????, picture    , target
  SDL_BlitSurface(source, NULL, destination, &offset);


}


int main(int argc, char* argv[]) {

  //Start SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
	return 1;
  }


  //Creates screen
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  if(screen == NULL) {
	return 1;
  }

  //Sets the widnow caption
  SDL_WM_SetCaption("VGC", NULL);

  hello = SDL_LoadBMP( "images/hello.bmp" );
  background = load_image("background.bmp");

  //Apply the background to the screen
  apply_surface(0, 0, background, screen);

  apply_surface(320,   0, background, screen);
  apply_surface(  0, 240, background, screen);
  apply_surface(320, 240, background, screen);

  //Apply the massage to the screen.
  apply_surface(180, 140, hello, screen);

  //Update the screen
  if(SDL_Flip(screen) == -1) {
	return 1;
  }

  //Wait 2 seconds
  SDL_Delay(2000);
  
  //Free the surfaces
  SDL_FreeSurface(hello);
  SDL_FreeSurface(background);
  
  //Quit SDL
  SDL_Quit();

  return 0;
}
