#pragma once
#include <glm/vec2.hpp>
#include <vector>

// Вершина с двумерной позицией и 2D координатами текстуры.
struct SVertexP2T2
{
    glm::vec2 position;
    glm::vec2 texCoord;
};

struct SRect
{
	glm::vec2 m_topLeft;
	glm::vec2 m_size;
};

class CQuad
{
public:
    CQuad(const glm::vec2 &leftTop, const glm::vec2 &size);

    void Draw()const;

	bool HitTest(glm::vec2 const& position);
private:
	SRect m_rect;

    std::vector<SVertexP2T2> m_vertices;
    std::vector<uint8_t> m_indicies;
};
