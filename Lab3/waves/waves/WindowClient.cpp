#include "stdafx.h"
#include "WindowClient.h"

namespace
{
const glm::vec2 QUAD_TOPLEFT = { -200, -200 };
const glm::vec2 QUAD_SIZE = { 400, 400 };

const float SHADER_CENTRE = 2.f;
const float LENGTH_RATIO = 100.f;
const glm::vec2 WINDOW_SIZE = glm::vec2(800.f, 600.f);

void SetupOpenGLState()
{
    // включаем механизмы трёхмерного мира.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}
}

CWindowClient::CWindowClient(CWindow &window)
	: CAbstractWindowClient(window)
	, m_quadObj(QUAD_TOPLEFT, QUAD_SIZE)
	, m_time(0)
	, m_isStarted(false)
	, m_waveCentre(glm::vec2(2.0f))
{
    const glm::vec4 GREEN = { 0.15f, 0.4f, 0.15f, 1.f };
    GetWindow().SetBackgroundColor(GREEN);
    CheckOpenGLVersion();
    SetupOpenGLState();

    const std::string vertexShader = CFilesystemUtils::LoadFileAsString("res/wave.vert");
    const std::string pictureShader = CFilesystemUtils::LoadFileAsString("res/wave.frag");

	CTexture2DLoader loader;
	std::string path = "res/img/first.jpg";
	m_firstWaveTex = loader.Load(path);
	path = "res/img/second.jpg";
	m_secondWaveTex = loader.Load(path);

    m_waveProg.CompileShader(vertexShader, ShaderType::Vertex);
	m_waveProg.CompileShader(pictureShader, ShaderType::Fragment);
	
	m_waveProg.Link();

	


    m_programQueue = { &m_waveProg };
}

void CWindowClient::OnUpdateWindow(float deltaSeconds)
{
    (void)deltaSeconds;

    SetupView(GetWindow().GetWindowSize());

	// переключаемся на текстурный слот #1
	glActiveTexture(GL_TEXTURE1);
	m_firstWaveTex->Bind();
	// переключаемся обратно на текстурный слот #0
	// перед началом рендеринга активным будет именно этот слот.
	glActiveTexture(GL_TEXTURE0);
	m_secondWaveTex->Bind();

	if (m_isStarted)
	{
		m_time += deltaSeconds;
	}
		m_programQueue.front()->Use();

		m_waveProg.FindUniform("colormap") = 0; // GL_TEXTURE0
		m_waveProg.FindUniform("replaceColormap") = 1; // GL_TEXTURE1
		m_waveProg.FindUniform("timer") = m_time;
		m_waveProg.FindUniform("CENTRE") = m_waveCentre;

    m_quadObj.Draw();
}

void CWindowClient::OnKeyUp(const SDL_KeyboardEvent &event)
{
    // Передвигаем очередь программ,
    // если была нажата и отпущена клавиша "Пробел"
    if (event.keysym.sym == SDLK_SPACE)
    {
        std::rotate(m_programQueue.begin(), m_programQueue.begin() + 1, m_programQueue.end());
    }
	if (event.keysym.sym == SDLK_z)
	{
		m_time = 0;
	}

}

void CWindowClient::OnDragEnd(const glm::vec2 & pos)
{
	glm::vec2 position = glm::vec2(pos.x - WINDOW_SIZE.x / 2, pos.y - WINDOW_SIZE.y / 2);
	if (m_quadObj.HitTest(position))
	{
		m_waveCentre = glm::vec2(position.x / LENGTH_RATIO + SHADER_CENTRE, -position.y / LENGTH_RATIO + SHADER_CENTRE);
		m_isStarted = true;
		m_time = 0;
	}
	else
	{
		m_isStarted = false;
	}
}

void CWindowClient::CheckOpenGLVersion()
{
    // В OpenGL 2.0 шейдерные программы вошли в спецификацию API.
    if (!GLEW_VERSION_2_0)
    {
        throw std::runtime_error("Sorry, but OpenGL 3.2 is not available");
    }
}

void CWindowClient::SetupView(const glm::ivec2 &size)
{
    // Матрица ортографического проецирования изображения в трёхмерном пространстве
    // из параллелипипеда с размером, равным (size.X x size.Y x 2).
    const float halfWidth = float(size.x) * 0.5f;
    const float halfHeight = float(size.y) * 0.5f;
    const glm::mat4 matrix = glm::ortho<float>(-halfWidth, halfWidth, -halfHeight, halfHeight);
    glViewport(0, 0, size.x, size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}
