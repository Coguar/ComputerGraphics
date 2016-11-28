#include "stdafx.h"
#include "WindowClient.h"

namespace
{
	const std::string STEPS_SOUND_PATH = "./res/Footsteps.wav";
	const std::string SCARY_SOUND_PATH1 = "./res/scary1.wav";
	const std::string SCARY_SOUND_PATH2 = "./res/scary2.wav";
	const std::string SCARY_SOUND_PATH3 = "./res/scary3.wav";
	const std::string SCARY_SOUND_PATH4 = "./res/scary4.wav";
	const std::string SCARY_SOUND_PATH5 = "./res/scary5.wav";
	const std::string SCARY_SOUND_PATH = "./res/scary.wav";

	const std::string MAP_PATH = "./res/map.bmp";

	const float CAMERA_INITIAL_ROTATION = 0.f;
	const float CAMERA_INITIAL_DISTANCE = 0.f;

	const glm::vec4 BLACK = { 0, 0, 0, 1 };
	const float MATERIAL_SHININESS = 0.f;
	const glm::vec4 FADED_WHITE_RGBA = { 0.3f, 0.3f, 0.3f, 1.f };
	const unsigned SPHERE_PRECISION = 40;

	void SetupFog()
	{
		const float density = 0.2f;
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogfv(GL_FOG_COLOR, glm::value_ptr(BLACK));
		glFogf(GL_FOG_DENSITY, density);
	}

	void SetupOpenGLState()
	{
		// включаем механизмы трёхмерного мира.
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		// включаем систему освещения
		glEnable(GL_LIGHTING);

		// включаем текстурирование в старом стиле (OpenGL 1.1)
		glEnable(GL_TEXTURE_2D);

		SetupFog();
	}
}

CWindowClient::CWindowClient(CWindow &window)
    : CAbstractWindowClient(window)
    , m_camera(CAMERA_INITIAL_ROTATION, CAMERA_INITIAL_DISTANCE)
	, m_lamp(GL_LIGHT0)
	, m_phisicsWorld(b2World({ 0, 0 }))
{
	const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };

	m_material.SetAmbient(glm::vec4(0.2f));
	m_material.SetDiffuse(WHITE_RGBA);
	m_material.SetSpecular(FADED_WHITE_RGBA * 0.1f);
	m_material.SetShininess(30);

	m_lamp.SetPosition({ 0, 0 ,0 });
	m_lamp.SetDiffuse(WHITE_RGBA);
	m_lamp.SetAmbient(0.1f * WHITE_RGBA);
	m_lamp.SetSpecular(WHITE_RGBA);

	m_stepsSource.SetupSource(STEPS_SOUND_PATH, true);

	m_scarySource.SetupSource(SCARY_SOUND_PATH, true);
	CSoundSource sound;
	sound.SetupSource(SCARY_SOUND_PATH, true);

	m_randomSoundPlayer.AddSound(SCARY_SOUND_PATH);
	m_randomSoundPlayer.AddSound(SCARY_SOUND_PATH1);
	m_randomSoundPlayer.AddSound(SCARY_SOUND_PATH2);
	m_randomSoundPlayer.AddSound(SCARY_SOUND_PATH3);
	m_randomSoundPlayer.AddSound(SCARY_SOUND_PATH4);
	m_randomSoundPlayer.AddSound(SCARY_SOUND_PATH5);

	m_randomSoundPlayer.PlayingRandomSound(true);

	const std::string vertexShader = CFilesystemUtils::LoadFileAsString("res/lambert-phong.vert");
	const std::string phongShader = CFilesystemUtils::LoadFileAsString("res/phong.frag");

	m_phongFrag.CompileShader(vertexShader, ShaderType::Vertex);
	m_phongFrag.CompileShader(phongShader, ShaderType::Fragment);
	m_phongFrag.Link();

	const std::string copyVertShader = CFilesystemUtils::LoadFileAsString("res/fog.vert");
	const std::string copyFragShader = CFilesystemUtils::LoadFileAsString("res/fog.frag");

	m_texFrag.CompileShader(copyVertShader, ShaderType::Vertex);
	m_texFrag.CompileShader(copyFragShader, ShaderType::Fragment);
	m_texFrag.Link();

	SetupOpenGLState();


	CTexture2DLoader loader;
	loader.SetWrapMode(TextureWrapMode::REPEAT);
	m_labirint.SetPhisicsWorld(&m_phisicsWorld);
	m_labirint.SetMatrix(*CLabirint::CreateMatrixFromBMP(MAP_PATH).get());
	m_player = CPlayer(&m_camera, &m_phisicsWorld, m_labirint.GetPlayerPos());

	GetWindow().SetBackgroundColor(BLACK);
	CheckOpenGLVersion();
}

void CWindowClient::OnUpdateWindow(float deltaSeconds)
{
	m_phisicsWorld.Step(1 / 60.f, 8, 3);
	m_camera.Update(deltaSeconds);
	m_labirint.Update(deltaSeconds);

	m_player.Update(deltaSeconds);
	auto pos = m_player.GetPosition();
	m_stepsSource.SetSourcePosition({ pos.x, 0.f, pos.y });
	m_stepsSource.Update(deltaSeconds);
	m_randomSoundPlayer.Update(deltaSeconds);
}

void CWindowClient::OnDrawWindow(const glm::ivec2 & size)
{
	SetupView(size);
	//m_texFrag.Use();
	
	auto pos = m_player.GetPosition();
	auto dir = m_player.GetGazeDirection();

	m_lamp.SetPosition({ pos.x, 0.5f, pos.y });
	m_lamp.SetDirection({ dir.x, 0.f, dir.y });
	m_lamp.Setup();
	m_material.Setup();
	m_phongFrag.Use();

	m_labirint.Draw();
}


void CWindowClient::OnKeyDown(const SDL_KeyboardEvent &event)
{
	m_player.OnKeyDown(event);
	if (m_player.IsMoving())
	{
		m_stepsSource.Play();
	}
}

void CWindowClient::OnKeyUp(const SDL_KeyboardEvent &event)
{
	m_player.OnKeyUp(event);
	if (!m_player.IsMoving())
	{
		m_stepsSource.Stop();
	}
}

void CWindowClient::OnDragMotion(const glm::vec2 & pos)
{
	m_player.OnDragMotion(pos);
}

void CWindowClient::OnDragBegin(const glm::vec2 & pos)
{
	m_player.OnDragBegin(pos);
}

void CWindowClient::OnDragEnd(const glm::vec2 & pos)
{
	m_player.OnDragEnd(pos);
}

void CWindowClient::CheckOpenGLVersion()
{
    // В OpenGL 2.0 шейдерные программы вошли в спецификацию API.
    if (!GLEW_VERSION_3_2)
    {
        throw std::runtime_error("Sorry, but OpenGL 3.2 is not available");
    }
}

void CWindowClient::SetupView(const glm::ivec2 &size)
{
    glViewport(0, 0, size.x, size.y);
    const glm::mat4 mv = m_camera.GetViewTransform();
    glLoadMatrixf(glm::value_ptr(mv));

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
