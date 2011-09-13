#ifndef CSURFACE_H
#define CSURFACE_H
#include <SDL.h>

	class CSurface
	{
		public:
		CSurface();
		
		static SDL_Surface* onLoad(char* file);
		static bool onDraw(SDL_Surface* sdest, SDL_Surface* ssrc, int x, int y);		
	};
