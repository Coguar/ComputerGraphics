#include "stdafx.h"
#include <SDL2/SDL.h>
#include "Window.h"
//#include <alut.h>
//#include <al.h>

namespace
{
const glm::ivec2 WINDOW_SIZE = {800, 600};
const char WINDOW_TITLE[] = "Maze";
const char ERROR_TITLE[] = "Fatal Error";
}

int main(int argc, char *argv[])
{
    try
    {
		if (alutInit(&argc, argv) != AL_TRUE)
		{
			throw std::runtime_error("OpenAL initialization failed");
		}
		alGetError();
        CWindow window;
        window.Show(WINDOW_TITLE, WINDOW_SIZE);
        window.DoGameLoop();
		
    }
    catch (const std::exception &ex)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, ERROR_TITLE,
                                 ex.what(), nullptr);
    }
	alutExit();
    return 0;
}
