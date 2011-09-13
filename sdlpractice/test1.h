#ifndef test1h
#define test1h
#include <SDL/SDL.h>
	class test1
 	{
	private:
		bool running;
		SDL_Surface* Surf_Display;
	public:
		test1();
		int onExecute();
		bool onInit();
		void onEvent(SDL_Event* event);
			void onKeyEvent(SDL_Event* event);
			void onMouseEvent(SDL_Event* event);
			void onQuitEvent(SDL_Event* event);
		void onLoop();
		void onRender();
		void onCleanup();
		
	};
#endif
