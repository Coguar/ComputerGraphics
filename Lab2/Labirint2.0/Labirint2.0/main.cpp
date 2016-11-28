#include "stdafx.h"
#include "WindowClient.h"
#include <SDL2/SDL.h>

int main(int, char *[])
{
	try
	{
		if (alutInit(nullptr, nullptr) != AL_TRUE)
		{
			throw std::runtime_error("OpenAL initialization failed");
		}
		alGetError();
		CWindow window;
		window.Show("Maze 2.0", { 800, 600 });
		CWindowClient client(window);
		window.DoMainLoop();
	}
	catch (const std::exception &ex)
	{
		const char *title = "Fatal Error";
		const char *message = ex.what();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
	}
	alutExit();
	return 0;
}
