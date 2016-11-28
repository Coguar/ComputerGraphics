#pragma once
#include "libchapter3.h"
#include <vector>
#include "IBody.h"
#include "Lights.h"
#include "Labirint.h"
#include "RandomSoundPlayer.h"
#include "Player.h"

class CWindowClient : public CAbstractWindowClient
{
public:
    CWindowClient(CWindow &window);

protected:
    // IWindowClient interface
    void OnUpdateWindow(float deltaSeconds) override;
	void OnDrawWindow(const glm::ivec2 &size) override;

    void OnKeyDown(const SDL_KeyboardEvent &) override;
    void OnKeyUp(const SDL_KeyboardEvent &) override;

	void OnDragMotion(const glm::vec2 &pos) override;
	void OnDragBegin(const glm::vec2 &pos) override;
	void OnDragEnd(const glm::vec2 &pos) override;
private:
    void CheckOpenGLVersion();
    void SetupView(const glm::ivec2 &size);

	CPlayer m_player;

	CPhongModelMaterial m_material;

	CTexture2DUniquePtr m_pWallTexture;
	CWall				m_wall;
	CLabirint m_labirint;
	CCamera m_camera;
	CSpotlightSource m_lamp;
	b2World m_phisicsWorld;

	CSoundSource m_stepsSource;
	CRandomSoundPlayer m_randomSoundPlayer;
	CSoundSource m_scarySource;

	CShaderProgram m_phongFrag;
	CShaderProgram m_texFrag;

};
