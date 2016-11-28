#pragma once
#include "Wall.h"
#include <vector>
#include <memory>
#include "Box2D\Box2D.h"

typedef std::vector<std::vector<size_t>> LabirintMatrix;

class CLabirint
{
public:
	CLabirint();
	~CLabirint();
	void SetMatrix(LabirintMatrix const& matrix);
	void Draw();
	void Update(float dt);
	void SetTexture(CTexture2DUniquePtr & texture);
	void SetPhisicsWorld(b2World * phisicsWorld);

	glm::vec2 GetPlayerPos();

	static const std::shared_ptr<LabirintMatrix> CreateMatrixFromBMP(std::string const& pathToFile);
private:
	void UpdateWalls();
	void SetWalls(glm::ivec2 pos, glm::ivec2 maxRange);
	void SetWallPhysics(int x, int y, float w, float h);
	void SetFloor(glm::ivec2 pos);

	LabirintMatrix m_matrix;

	CTexture2DUniquePtr m_pWallTexture;
	CTexture2DUniquePtr m_pFloorTexture;
	CTexture2DUniquePtr m_pRoofTexture;

	std::vector<std::shared_ptr<CWall>> m_wallsArr;
	std::vector<std::shared_ptr<CFloor>> m_floorsSectorsArr;
	std::vector<std::shared_ptr<CFloor>> m_roofSectorsArr;

	b2World * m_phisicsWorldPtr;

	glm::vec2 m_playerPos;
};