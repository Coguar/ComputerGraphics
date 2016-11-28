#include "stdafx.h"
#include "Wall.h"

namespace
{
	const float HEIGHT_OF_WALL = 2.0f;
}

CWall::CWall(glm::vec2 leftPos, glm::vec2 rightPos)
{
	WallFace face;
	face.leftBottomPos = { leftPos.x, 0, leftPos.y };
	face.leftTopPos = { leftPos.x, HEIGHT_OF_WALL, leftPos.y };
	face.rightBottomPos = { rightPos.x, 0, rightPos.y };
	face.rightTopPos = { rightPos.x, HEIGHT_OF_WALL, rightPos.y };
	SetFace(face);
}


CWall::~CWall()
{
}

void CWall::Update(float)
{
	if (m_isDirty)
	{
		Triangulate();
		m_isDirty = false;
	}
}

void CWall::Draw() const
{
	m_mesh.Draw();
}

void CWall::SetFaceTextureRect(CFloatRect & rect)
{
	m_texRect = rect;
	m_isDirty = true;
}

void CWall::SetFace(WallFace const & face)
{
	m_face = face;
	Triangulate();
}

void CWall::Triangulate()
{
	m_mesh.Clear(MeshType::Triangles);

	const glm::vec3 &coord1 = m_face.leftBottomPos;
	const glm::vec3 &coord2 = m_face.leftTopPos;
	const glm::vec3 &coord3 = m_face.rightTopPos;
	const glm::vec3 &coord4 = m_face.rightBottomPos;
	const glm::vec3 normal = glm::normalize(
		glm::cross(coord2 - coord1, coord3 - coord1));

	const SVertexP3NT2 v1 = { coord1, m_texRect.GetTopLeft(), normal };
	const SVertexP3NT2 v2 = { coord2, m_texRect.GetBottomLeft(), normal };
	const SVertexP3NT2 v3 = { coord3, m_texRect.GetBottomRight(), normal };
	const SVertexP3NT2 v4 = { coord4, m_texRect.GetTopRight(), normal };

	const uint32_t fromIndex = uint32_t(m_mesh.m_vertices.size());
	m_mesh.m_vertices.push_back(v1);
	m_mesh.m_vertices.push_back(v2);
	m_mesh.m_vertices.push_back(v3);
	m_mesh.m_vertices.push_back(v4);

	m_mesh.m_indicies.push_back(fromIndex + 0);
	m_mesh.m_indicies.push_back(fromIndex + 1);
	m_mesh.m_indicies.push_back(fromIndex + 2);
	m_mesh.m_indicies.push_back(fromIndex + 0);
	m_mesh.m_indicies.push_back(fromIndex + 2);
	m_mesh.m_indicies.push_back(fromIndex + 3);

}



CFloor::CFloor(glm::vec2 leftTop, glm::vec2 rightBottom, float height)
{
	WallFace face;
	face.leftBottomPos = { leftTop.x, height , rightBottom.y };
	face.leftTopPos = { leftTop.x, height , leftTop.y };
	face.rightBottomPos = { rightBottom.x, height, rightBottom.y };
	face.rightTopPos = { rightBottom.x, height , leftTop.y };
	SetFace(face);
}
