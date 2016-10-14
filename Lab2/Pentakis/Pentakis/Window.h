#pragma once
#include "libchapter2.h"
#include "Bodies.h"
#include "Light.h"
#include <vector>

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    // CAbstractWindow interface
    void OnWindowInit(const glm::ivec2 &size) override;
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 &size) override;

    // IInputEventAcceptor interface
    void OnKeyDown(const SDL_KeyboardEvent &) override;
    void OnKeyUp(const SDL_KeyboardEvent &) override;
	void OnDragBegin(const glm::vec2 &pos) override;
	void OnDragMotion(const glm::vec2 &pos) override;
	void OnDragEnd(const glm::vec2 &pos) override;
private:
    void SetupView(const glm::ivec2 &size);

	CDirectedLightSource m_sunlight;
	CPositionLightSource m_light;

	CPentakis m_staticPentakis;
    CCamera m_camera;
};
