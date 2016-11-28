#pragma once
#include "src\Camera.h"
#include "Box2D\Box2D.h"
class CPlayer
{
public:
	CPlayer();
	CPlayer(CCamera * camera, b2World * phisicsWorld, glm::vec2 pos);
	~CPlayer();

	enum DIRECTION
	{
		Forward = 0,
		Backward,
		Left,
		Right,
		Stay,
	};
	bool IsMoving();

	void SetPhisicsWorld(b2World * phisicsWorld);
	void Update(float dt);

	bool OnKeyDown(const SDL_KeyboardEvent &event);
	bool OnKeyUp(const SDL_KeyboardEvent &event);

	void OnDragMotion(const glm::vec2 & pos);
	void OnDragBegin(const glm::vec2 &pos);
	void OnDragEnd(const glm::vec2 &pos);

	glm::vec2 GetPosition();
	glm::vec2 GetGazeDirection();

private:
	void Move(DIRECTION dir);
	void Rotate(float angle);
	void SetCam();

	glm::vec2 m_position;
	glm::vec2 m_direction;
	float m_rotation;
	CCamera * m_camera;
	b2Body * m_pBody;
	b2World * m_phisicsWorldPtr;

	std::set<unsigned> m_keysPressed;

	glm::ivec2 m_mousePos;
	bool m_isRotated;
};

