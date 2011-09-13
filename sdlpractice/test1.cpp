#include "test1.h"

test1::test1()
{
	Surf_Display = NULL;
	running = true;
}

	int test1::onExecute()
	{
		if(!onInit())
			return -1;
	
		SDL_Event event;
	
		while(running)
		{
			while(SDL_PollEvent(&event))
			{
				onEvent(&event);
			}
			
			onLoop();
			onRender();
		}
		onCleanup();
		return 0;
	}
	void test1::onLoop()
	{

	}
	void test1::onRender()
	{
	
	}
	void test1::onCleanup()
	{
		SDL_Quit();
	}
	int main(int argc, char* argv[])
	{
		test1 t1;
		return t1.onExecute();
	}

