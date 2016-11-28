#pragma once
#include "IBody.h"
#include "MeshP3NT2.h"
#include "libchapter2.h"

struct WallFace
{
	glm::vec3 leftBottomPos;
	glm::vec3 leftTopPos;
	glm::vec3 rightTopPos;
	glm::vec3 rightBottomPos;
};

class CWall :
	public IBody
{
public:
	CWall() = default;
	CWall(glm::vec2 leftPos, glm::vec2 rightPos);
	~CWall();
	void Update(float) final;
	void Draw()const final;

	void SetFaceTextureRect(CFloatRect &rect);

protected:
	void SetFace(WallFace const& face);

private:
	void Triangulate();
	WallFace m_face;
	SMeshP3NT2 m_mesh;
	CFloatRect m_texRect;
	bool m_isDirty;
};

class CFloor :
	public CWall

{
public:
	CFloor() = default;
	CFloor(glm::vec2 leftTop, glm::vec2 rightBottom, float height);
};