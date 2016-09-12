// SpaceShip.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyWindow.h"
#include <glm/vec2.hpp>

int main()
{
	CMyWindow window;
	window.Show({ 800, 600 });
	window.DoGameLoop();   
	return 0;
}

