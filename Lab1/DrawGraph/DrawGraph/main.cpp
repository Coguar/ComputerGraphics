// DrawGraph.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include "AbstractWindow.h"
#include "MyWindow.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <SDL2/SDL.h>

// Выключаем макроподмену main на SDL_main,
// т.к. приложение собирается c SUBSYSTEM:CONSOLE
#ifdef _WIN32
#undef main
#endif

int main()
{
	CMyWindow window;
	window.Show({ 800, 600 });
	window.DoGameLoop();

	return 0;
}
