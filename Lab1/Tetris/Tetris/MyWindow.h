#pragma once
#include "AbstractWindow.h"
#include "DispatchEvent.h"
//#include "Tetris.h"
#include "GameController.h"
class CMyWindow :
	public CAbstractInputControlWindow
{
public:
	CMyWindow();
	~CMyWindow();
protected:
	void OnUpdateWindow(float deltaSeconds) override;
	void OnDrawWindow(const glm::ivec2 & size) override;

	void OnDragBegin(const glm::vec2 &pos) override;
	void OnDragMotion(const glm::vec2 &pos) override;
	void OnDragEnd(const glm::vec2 &pos) override;

	virtual void OnKeyDown(const SDL_KeyboardEvent & event) override;
private:
	void SetupView(const glm::ivec2 &size);

	float m_time = 0.0f;
	float deltaTime = 0;
	CGameController m_gameObj;
};

