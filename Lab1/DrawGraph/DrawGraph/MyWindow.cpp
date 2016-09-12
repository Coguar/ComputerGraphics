#include "stdafx.h"
#include "MyWindow.h"

#include <GL/glew.h>
//#include <GL/gl.h>
//#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace
{
	void DrawCoordinateSystem(const glm::ivec2 & size)
	{
		glBegin(GL_LINES);
		glVertex2f(0.0f, size.y / 2);
		glVertex2f(size.x, size.y / 2);

		glVertex2f(size.x / 2, 0.0f);
		glVertex2f(size.x / 2, size.y);
		glEnd();
	}

	void DrawArchimedeanSpiral(float step, float xCentre, float yCentre)
	{
		float max = 10.0f * M_PI;
		glBegin(GL_LINE_STRIP);

		for (float i = 0.0f; i <= max; i += 0.1)
		{
			float rad = step * i;

			float x = rad * std::cos(i) + xCentre;
			float y = rad * ( -1 * std::sin(i)) + yCentre;

			glVertex2f(x, y);
		}
		glEnd();
	}

}

CMyWindow::CMyWindow()
{
}


CMyWindow::~CMyWindow()
{
}

void CMyWindow::OnUpdateWindow(float deltaSeconds)
{
	m_time += deltaSeconds;
}

void CMyWindow::OnDrawWindow(const glm::ivec2 & size)
{
	SetupView(size);
	glColor3f(1, 0, 1);
	DrawCoordinateSystem(size);

	glColor3f(1, 1, 1);
	DrawArchimedeanSpiral(10.0f, size.x / 2, size.y / 2);
}

void CMyWindow::OnWindowEvent(const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_r:
			SetBackgroundColor({ 1, 0, 0, 1 });
			break;
		case SDLK_g:
			SetBackgroundColor({ 0, 1, 0, 1 });
			break;
		case SDLK_b:
			SetBackgroundColor({ 0, 0, 1, 1 });
			break;
		}
	}
}

void CMyWindow::SetupView(const glm::ivec2 & size)
{
	// Матрица ортографического проецирования изображения в трёхмерном пространстве
	// из параллелипипеда с размером, равным (size.X x size.Y x 2).
	const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
	glViewport(0, 0, size.x, size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
}
