#pragma once

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>
#include <boost/noncopyable.hpp>


typedef glm::vec3 Vertex;

class CPentakis
{
public:
	enum Type {
		DODECAHEDRON = 0,
		PENTAKIS,
		STAR,
	};

	CPentakis();
	void Update(float deltaTime);
	void NextType();

	const std::vector<Vertex> & GetVerticies() const;
	const std::vector<uint16_t> & GetFaces() const;
	const Type GetType() const;
	const std::vector<uint16_t> & GetEdgesFaces() const;

	std::function<glm::vec4()> GetColoroid() const;
private:
	void InitPentakis();
	void CheckType();
	void SetColor(size_t & currentColor, size_t & count);
	void SetSpeed();
	void SetPickLvl();
	std::vector<Vertex> m_verticies;
	std::vector<Vertex> m_sourceVerticies;

	std::vector<uint16_t> m_pentakisFaces;
	Type m_type = DODECAHEDRON;
	bool typeWasChanged = true;
	float m_animSpeed;
	float m_currentPickLvl = 1;
};
