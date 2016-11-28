#include "stdafx.h"
#include "Player.h"
#include "src\Vector3D.h"
#include <alut.h>
const float SPEED = 0.05f;
const float ROTATION_SPEED = 0.01f;
namespace
{
	bool ShouldTrackKeyPressed(const SDL_Keysym &key)
	{
		switch (key.sym)
		{
		case SDLK_LEFT:
		case SDLK_RIGHT:
		case SDLK_UP:
		case SDLK_DOWN:
		case SDLK_w:
		case SDLK_a:
		case SDLK_s:
		case SDLK_d:
			return true;
		}
		return false;
	}

	CPlayer::DIRECTION GetDirection(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_UP) || keysPressed.count(SDLK_w))
		{
			return CPlayer::DIRECTION::Forward;
		}
		if (keysPressed.count(SDLK_DOWN) || keysPressed.count(SDLK_s))
		{
			return CPlayer::DIRECTION::Backward;
		}
		if (keysPressed.count(SDLK_RIGHT) || keysPressed.count(SDLK_d))
		{
			return CPlayer::DIRECTION::Right;
		}
		if (keysPressed.count(SDLK_LEFT) || keysPressed.count(SDLK_a))
		{
			return CPlayer::DIRECTION::Left;
		}
		return CPlayer::DIRECTION::Stay;
	}
}

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(CCamera * camera, b2World * phisicsWorld, glm::vec2 pos)
	: m_camera(camera)
	, m_position(pos)
	, m_direction({ 0, 1 })
	, m_rotation (0)
	, m_isRotated(false)
	, m_phisicsWorldPtr(phisicsWorld)
{
	b2BodyDef bdef;
	bdef.type = b2_dynamicBody;
	bdef.position.Set(m_position.x, m_position.y);
	b2CircleShape circle;
	circle.m_radius = 0.02f;;
	m_pBody = m_phisicsWorldPtr->CreateBody(&bdef);
	m_pBody->CreateFixture(&circle, 2);
}


CPlayer::~CPlayer()
{
}

bool CPlayer::IsMoving()
{
	return m_keysPressed.size() > 0;
}

void CPlayer::SetPhisicsWorld(b2World * phisicsWorld)
{
	m_phisicsWorldPtr = phisicsWorld;
}

bool CPlayer::OnKeyDown(const SDL_KeyboardEvent &event)
{
	if (ShouldTrackKeyPressed(event.keysym))
	{
		m_keysPressed.insert(unsigned(event.keysym.sym));
		return true;
	}
	return false;
}

bool CPlayer::OnKeyUp(const SDL_KeyboardEvent &event)
{
	if (ShouldTrackKeyPressed(event.keysym))
	{
		m_keysPressed.erase(unsigned(event.keysym.sym));
		return true;
	}
	return false;
}

void CPlayer::OnDragMotion(const glm::vec2 & pos)
{
	if (m_isRotated)
	{
		// TODO: fix warning
		float offset = pos.x - m_mousePos.x;
		Rotate(offset / 100.0);
	}
	m_mousePos = pos;

}

void CPlayer::OnDragBegin(const glm::vec2 & pos)
{
	m_isRotated = true;
}

void CPlayer::OnDragEnd(const glm::vec2 & pos)
{
	m_isRotated = false;
}

glm::vec2 CPlayer::GetPosition()
{
	return m_position;
}

glm::vec2 CPlayer::GetGazeDirection()
{
	return m_direction;
}

void CPlayer::Update(float dt)
{
	Move(GetDirection(m_keysPressed));
	auto pos = m_pBody->GetPosition();
	m_position = { pos.x, pos.y };
	glm::vec3 center = { m_position.x + m_direction.x, 0.5f, m_position.y + m_direction.y };
	m_camera->SetCamCenter(center);
	m_camera->SetCamDirection({ m_position.x, 0.5f, m_position.y });

	// TODO: setup orientation using camera.
	float 		listenerOri[] = { m_direction.x, 0.5f, m_direction.y,  0, 1, 0 };
	Vector3D position ( m_position.x, 0.5f, m_position.y );
	alListenerfv(AL_POSITION, position);
	alListenerfv(AL_VELOCITY, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);
}

void CPlayer::Move(DIRECTION dir)
{
	glm::vec2 dirVec = { 0, 0 };
	switch (dir)
	{
	case CPlayer::Forward:
		dirVec = { 0, SPEED };
		break;
	case CPlayer::Backward:
		dirVec = { 0, -SPEED };
		break;
	case CPlayer::Left:
		dirVec = { SPEED, 0 };
		break;
	case CPlayer::Right:
		dirVec = { -SPEED, 0 };
		break;
	default:
		break;
	}
	glm::vec2 rDirVec = { 0, 0 };

	rDirVec.x = dirVec.x * cos(m_rotation) - dirVec.y * sin(m_rotation);
	rDirVec.y = dirVec.y * cos(m_rotation) + dirVec.x * sin(m_rotation);
	m_pBody->SetLinearVelocity({ rDirVec.x * 50, rDirVec.y * 50 });

}

void CPlayer::Rotate(float angle)
{
	m_rotation += angle;
	auto oldDir = m_direction;
	m_direction.x = oldDir.x * cos(angle) - oldDir.y * sin(angle);
	m_direction.y = oldDir.y * cos(angle) + oldDir.x * sin(angle);
}

void CPlayer::SetCam()
{

}
