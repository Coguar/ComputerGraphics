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

    glm::mat4 GetViewTransform();
	void SetCamDirection(glm::vec3 direction);
	void SetCamCenter(glm::vec3 center);
private:
    float m_rotationRadians = 0;
    float m_distance = 1;
	glm::vec3 m_center = { 0, 0, 0 };
	glm::vec3 m_direction;
    std::set<unsigned> m_keysPressed;

};
