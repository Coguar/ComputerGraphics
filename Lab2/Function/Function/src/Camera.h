#pragma once

#include <glm/fwd.hpp>
#include <SDL2/SDL_events.h>
#include <boost/noncopyable.hpp>
#include <set>

class CCamera : private boost::noncopyable
{
public:
    explicit CCamera(float rotationRadians, float distance);

    void Update(float deltaSec);
    bool OnKeyDown(const SDL_KeyboardEvent &event);
    bool OnKeyUp(const SDL_KeyboardEvent &event);
	void OnDragBegin(const glm::vec2 &pos) ;
	void OnDragMotion(const glm::vec2 &pos) ;
	void OnDragEnd(const glm::vec2 &pos) ;
    glm::mat4 GetViewTransform();

	const glm::vec3 & GetEyePosition() const;
	const glm::vec3 & GetEyeDirection() const;
private:
    float m_rotationRadians = 0;
    float m_distance = 1;
    std::set<unsigned> m_keysPressed;

	glm::vec3 m_direction;
	glm::vec3 m_position;

	bool isRotated = false;
	float xPos;
	float offset;
};
