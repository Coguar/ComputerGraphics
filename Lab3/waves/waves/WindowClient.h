#pragma once
#include "libchapter3.h"
#include "Quad.h"
#include <vector>

class CWindowClient : public CAbstractWindowClient
{
public:
    CWindowClient(CWindow &window);

protected:
    // IWindowClient interface
    void OnUpdateWindow(float deltaSeconds) override;
    void OnKeyUp(const SDL_KeyboardEvent &) override;

	void OnDragEnd(const glm::vec2 &pos) override;
private:
    void CheckOpenGLVersion();
    void SetupView(const glm::ivec2 &size);

    CQuad m_quadObj;
	CShaderProgram m_waveProg;

	CTexture2DUniquePtr m_firstWaveTex;
	CTexture2DUniquePtr m_secondWaveTex;

	bool m_isStarted;
	float m_time;
	glm::vec2 m_waveCentre;

    std::vector<CShaderProgram *> m_programQueue;
};
