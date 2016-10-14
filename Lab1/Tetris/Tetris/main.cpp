// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "stdafx.h"
#include "MyWindow.h"
#include <glm/vec2.hpp>
#include "Tetris.h"

int main()
{
	CMyWindow window;
	window.Show({ 450, 440 });
	window.DoGameLoop();
	return 0;
}
