#include "stdafx.h"
#include "Window.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include "PentakisView.h"
namespace
{

glm::vec3 SummVec(glm::vec3 const& vec1, glm::vec3 const& vec2)
{
	return{ vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z };
}

const glm::vec4 BLACK = {0, 0, 0, 0.5f};
const float CAMERA_INITIAL_ROTATION = 0;
const float CAMERA_INITIAL_DISTANCE = 5.f;

void SetupOpenGLState()
{
    // включаем механизмы трёхмерного мира.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glShadeModel(GL_FLAT);

}
const glm::vec4 WHITE_LIGHT = { 1, 1, 1, 1 };
const glm::vec3 SUNLIGHT_DIRECTION = { 0, 0, 2.7f };
const glm::vec3 LIGHT_POSITION = { 2, 0, 0 };

}

CWindow::CWindow()
    : m_camera(CAMERA_INITIAL_ROTATION, CAMERA_INITIAL_DISTANCE)
	, m_sunlight(GL_LIGHT0)
	, m_light(GL_LIGHT1)
{
    SetBackgroundColor(BLACK);

	m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WHITE_LIGHT);
	m_sunlight.SetAmbient(0.1f * WHITE_LIGHT);

	m_light.SetPosition(LIGHT_POSITION);
	m_light.SetDiffuse(WHITE_LIGHT);
	m_light.SetAmbient(0.1f * WHITE_LIGHT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void CWindow::OnWindowInit(const glm::ivec2 &size)
{
    (void)size;
    SetupOpenGLState();
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_camera.Update(deltaSeconds);

	m_staticPentakis.Update(deltaSeconds);
	m_light.SetPosition(m_camera.GetEyePosition() + LIGHT_POSITION);
	//m_sunlight.SetDirection(m_camera.GetEyeDirection());

}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    SetupView(size);
	//m_sunlight.Setup();
	m_light.Setup();	
	CPentakisView::DrawPentakis(m_staticPentakis);
	//m_staticPentakis.Draw();
}

void CWindow::SetupView(const glm::ivec2 &size)
{
    glViewport(0, 0, size.x, size.y);

    // Матрица вида возвращается камерой и составляет
    // начальное значение матрицы GL_MODELVIEW.
    glLoadMatrixf(glm::value_ptr(m_camera.GetViewTransform()));

    // Матрица перспективного преобразования вычисляется функцией
    // glm::perspective, принимающей угол обзора, соотношение ширины
    // и высоты окна, расстояния до ближней и дальней плоскостей отсечения.
    const float fieldOfView = glm::radians(70.f);
    const float aspect = float(size.x) / float(size.y);
    const float zNear = 0.01f;
    const float zFar = 100.f;
    const glm::mat4 proj = glm::perspective(fieldOfView, aspect, zNear, zFar);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(proj));
    glMatrixMode(GL_MODELVIEW);
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent &event)
{
    m_camera.OnKeyDown(event);
}

void CWindow::OnKeyUp(const SDL_KeyboardEvent &event)
{
    m_camera.OnKeyUp(event);
	if (event.keysym.sym == SDLK_SPACE)
	{
		m_staticPentakis.NextType();
	}
}

void CWindow::OnDragBegin(const glm::vec2 &pos)
{
	m_camera.OnDragBegin(pos);
}
void CWindow::OnDragMotion(const glm::vec2 &pos)
{
	m_camera.OnDragMotion(pos);
}
void CWindow::OnDragEnd(const glm::vec2 &pos)
{
	m_camera.OnDragEnd(pos);
}