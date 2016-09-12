#include "stdafx.h"
#include "MyWindow.h"

namespace
{
	void DrawContour(CItem const& item, const glm::vec2 &pos)
	{
		glColor3f(0, 0, 0);
		glLineWidth(3);
		glBegin(GL_LINE_STRIP);
		for (auto & point : item.GetContour())
		{
			glVertex2f(point.x + pos.x, point.y + pos.y);

		}
		glEnd();
	}

	void DrawComplexItem(ComplexItem const& item)
	{
		glm::vec2 position = item.GetPosition();
		for (auto &it : item.GetItemsList())
		{
			DrawContour(it, position);
			if (it.GetType() != CItem::type::Line)
			{
				auto color = it.GetColor();
				glColor3f(color.r, color.g, color.b);
				glBegin(GL_TRIANGLE_FAN);
				for (auto &point : it.GetContour())
				{
					glVertex2f(point.x + position.x, point.y + position.y);
				}
				glEnd();
			}
		}
	}

}

CMyWindow::CMyWindow()
{
	m_item = CFileReader::ReadFromJsonFile("input.txt");
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
	DrawComplexItem(m_item);
}

void CMyWindow::OnDragBegin(const glm::vec2 &pos)
{
	if (m_item.HitTest(pos))
	{
		m_dragOffset = pos - m_item.GetPosition();
		isMoving = true;
	}
}

void CMyWindow::OnDragMotion(const glm::vec2 &pos)
{
	if (isMoving)
	{
		m_item.SetPosition(pos - m_dragOffset);
	}
}

void CMyWindow::OnDragEnd(const glm::vec2 &pos)
{
	if (isMoving)
	{
		m_item.SetPosition(pos - m_dragOffset);
		isMoving = false;
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
