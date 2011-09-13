#include "test1.h"
void test1::onEvent(SDL_Event* event)
{
	switch(event->type)
	{
	case SDL_KEYDOWN:
		onKeyEvent(event);
		break;
	case SDL_MOUSEBUTTONDOWN:
		onMouseEvent(event);
		break;
	case SDL_QUIT:
		onQuitEvent(event);
		break;	
	}

}
void test1::onKeyEvent(SDL_Event* event)
{
	switch(event->key.keysym.sym)
	{
		case SDLK_UP:
			
		break;
		
		case SDLK_DOWN:
		
		break;
		
		case SDLK_LEFT:
		
		break;
		
		case SDLK_RIGHT:
		
		break;
		
	}
	return;
}
void test1::onMouseEvent(SDL_Event* event)
{
	return; //filler for now
}
void test1::onQuitEvent(SDL_Event* event)
{
	running = false;
}
