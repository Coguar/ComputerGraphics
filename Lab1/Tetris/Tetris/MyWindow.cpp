#include "stdafx.h"
#include "MyWindow.h"


CMyWindow::CMyWindow()
{
	this->SetBackgroundColor({ 0.5, 0.5, 0.5, 1 });
}


CMyWindow::~CMyWindow()
{
}

void CMyWindow::OnUpdateWindow(float deltaSeconds)
{
	m_time += deltaSeconds;
	m_gameObj.UpdateTetris(deltaSeconds);
}

void CMyWindow::OnDrawWindow(const glm::ivec2 & size)
{
	SetupView(size);
	m_gameObj.DrawGame();
}

void CMyWindow::OnDragBegin(const glm::vec2 &pos)
{
}

void CMyWindow::OnDragMotion(const glm::vec2 &pos)
{

}

void CMyWindow::OnDragEnd(const glm::vec2 &pos)
{

}

void CMyWindow::OnKeyDown(const SDL_KeyboardEvent & event)
{
	m_gameObj.OnKeyboardEvent(event);
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
