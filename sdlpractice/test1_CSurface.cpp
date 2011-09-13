#include "test1_CSurface.h"

	CSurface::CSurface()
	{
	}
	
	SDL_Surface* CSurface::onLoad(char* file)
	{
		SDL_Surface* temp = NULL;
		SDL_Surface* ret = NULL;
		
		if ((temp = SDL_LoadBMP(file)) == NULL) //Loads file into temp, and returns null if the load fails
		{
			return NULL
		}
		ret = SDL_DisplayFormat(temp); //Formats surface for display (makes shit faster later)
		SDL_FreeSurface(temp); //Free the old, unformatted surface
		return ret;
	}
	bool CSurface::onDraw(SDL_Surface* sdest, SDL_Surface* ssrc, int x, int y)
	{
		SDL_Rect targetRect;
		targetRect.x = x;
		targetRect.y = y;
		SDL_BlitSurface(ssrc, NULL, sdest, &targetRect);
		return true;
	}

	
