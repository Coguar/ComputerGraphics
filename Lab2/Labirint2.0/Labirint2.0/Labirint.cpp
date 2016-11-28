#include "stdafx.h"
#include "Labirint.h"
#include <fstream>
#include <ios>

namespace
{
	const float WALL_WIDTH = 1.f;
	const char WALL_TEX_PATH[] = "res/Wall1.jpg";
	const char FLOOR_TEX_PATH[] = "res/F1.jpg";
	const char ROOF_TEX_PATH[] = "res/roof.jpg";
	const unsigned int SPACE_CODE = 0xFFFFFF;
	const unsigned int PLAYER_CODE = 0xFF0000;

	const unsigned int MAX_CODE = 0xFF;

	const size_t WALL_SYMB = 1;
	const size_t SPACE_SYMB = 0;
	const size_t PLAYER_SYMB = 2;

}
CLabirint::CLabirint()
	: m_playerPos({1, 1})
{


}

CLabirint::~CLabirint()
{
}

void CLabirint::SetMatrix(LabirintMatrix const & matrix)
{
	m_matrix = matrix;
	UpdateWalls();
	glEnable(GL_TEXTURE_2D);

	CTexture2DLoader loader;
	loader.SetWrapMode(TextureWrapMode::REPEAT);
	m_pWallTexture = loader.Load(WALL_TEX_PATH);
	m_pFloorTexture = loader.Load(FLOOR_TEX_PATH);
	m_pRoofTexture = loader.Load(ROOF_TEX_PATH);

}

void CLabirint::Draw()
{

	for (auto &it : m_wallsArr)
	{
		m_pWallTexture->DoWhileBinded([&] {
			it->Draw();
		});
	}
	for (auto &it : m_floorsSectorsArr)
	{
		m_pFloorTexture->DoWhileBinded([&] {
			it->Draw();
		});
	}
	for (auto &it : m_roofSectorsArr)
	{
		m_pRoofTexture->DoWhileBinded([&] {
			it->Draw();
		});
	}
}

void CLabirint::Update(float dt)
{
	for (auto &it : m_wallsArr)
	{
		it->Update(dt);
	}
	for (auto &it : m_floorsSectorsArr)
	{
		it->Update(dt);
	}
	for (auto &it : m_roofSectorsArr)
	{
		it->Update(dt);
	}
}

void CLabirint::SetTexture(CTexture2DUniquePtr & texture)
{
	m_pWallTexture = std::move(texture);
}

void CLabirint::SetPhisicsWorld(b2World * phisicsWorld)
{
	m_phisicsWorldPtr = phisicsWorld;
}

glm::vec2 CLabirint::GetPlayerPos()
{
	return m_playerPos;
}

const std::shared_ptr<LabirintMatrix> CLabirint::CreateMatrixFromBMP(std::string const & pathToFile)
{
	unsigned pixelsOffset = 0;
	unsigned width = 0;
	unsigned height = 0;
	unsigned short bitsPerPixel = 0;
	std::ifstream file(pathToFile, std::ios::in | std::ios::binary);
	file.exceptions(std::ios::badbit | std::ios::failbit);

	file.seekg(10, std::ios::beg);
	file.read((char*)&pixelsOffset, sizeof(unsigned));
	file.seekg(18, std::ios::beg);
	file.read((char*)&width, sizeof(unsigned));
	file.read((char*)&height, sizeof(unsigned));
	file.seekg(28, std::ios::beg);
	file.read((char*)&bitsPerPixel, sizeof(short unsigned));
	file.seekg(size_t(pixelsOffset), std::ios::beg);

	LabirintMatrix matrix;
	matrix.resize(size_t(height));

	unsigned RGBByteSize = 3;
	std::vector<unsigned> bgr;
	bgr.resize(RGBByteSize);

	for (size_t y = 0; y < size_t(height); ++y)
	{
		for (size_t x = 0; x < size_t(width); ++x)
		{
			for (unsigned i = 0; i < RGBByteSize; ++i)
			{
				file.read((char*)&bgr[i], 1);
			}
			if (bgr[1] == MAX_CODE)
			{
				matrix[y].push_back(SPACE_SYMB);
			}
			else if (bgr[2] == MAX_CODE)
			{
				matrix[y].push_back(PLAYER_SYMB);
			}
			else
			{
				matrix[y].push_back(WALL_SYMB);
			}
		}
	}
	return std::make_shared<LabirintMatrix>(matrix);
}

void CLabirint::SetWalls(glm::ivec2 pos, glm::ivec2 maxRange)
{
	if (pos.x != 0 && m_matrix[pos.x - 1][pos.y] != 1)
	{
		m_wallsArr.push_back(std::make_shared<CWall>(CWall({ pos.x, pos.y + WALL_WIDTH }, { pos.x, pos.y })));
	}
	if (pos.x != maxRange.x - 1 && m_matrix[pos.x + 1][pos.y] != 1)
	{
		m_wallsArr.push_back(std::make_shared<CWall>(CWall({ pos.x + WALL_WIDTH, pos.y }, { pos.x + WALL_WIDTH, pos.y + WALL_WIDTH })));
	}
	if (pos.y != 0 && m_matrix[pos.x][pos.y - 1] != 1)
	{
		m_wallsArr.push_back(std::make_shared<CWall>(CWall({ pos.x, pos.y }, { pos.x + WALL_WIDTH , pos.y})));
	}
	if (pos.y != maxRange.y - 1 && m_matrix[pos.x ][pos.y + 1] != 1)
	{
		m_wallsArr.push_back(std::make_shared<CWall>(CWall({ pos.x + WALL_WIDTH, pos.y + WALL_WIDTH } ,{ pos.x, pos.y + WALL_WIDTH  })));
	}
}


void CLabirint::UpdateWalls()
{
	for (size_t x = 0; x < m_matrix.size(); ++x)
	{
		for (size_t y = 0; y < m_matrix[x].size(); ++y)
		{
			if (m_matrix[x][y] == WALL_SYMB)
			{
				SetWalls({ x, y }, { m_matrix.size() , m_matrix[x].size() });
				SetWallPhysics(x, y, WALL_WIDTH / 2, WALL_WIDTH / 2);
			}
			else
			{
				if (m_matrix[x][y] == PLAYER_SYMB)
				{
					m_playerPos = { x, y };
				}
				SetFloor({ x, y });
			}
		}
	}
	for (auto &it : m_wallsArr)
	{
		it->SetFaceTextureRect(CFloatRect({ 0,0 }, { 1,1 }));
	}
	for (auto &it : m_floorsSectorsArr)
	{
		it->SetFaceTextureRect(CFloatRect({ 0,0 }, { 1,1 }));
	}
	for (auto &it : m_roofSectorsArr)
	{
		it->SetFaceTextureRect(CFloatRect({ 0,0 }, { 1,1 }));
	}
}

void CLabirint::SetWallPhysics(int x, int y, float w, float h)
{
	b2PolygonShape gr;
	gr.SetAsBox(w, h);

	b2BodyDef bdef;
	bdef.position.Set(x + w, y + h);

	b2Body *b_ground = m_phisicsWorldPtr->CreateBody(&bdef);
	b_ground->CreateFixture(&gr, 1);
}

void CLabirint::SetFloor(glm::ivec2 pos)
{
	m_floorsSectorsArr.push_back(std::make_shared<CFloor>(CFloor( { pos.x + 1, pos.y }, { pos.x, pos.y + 1 }, 0.f)));
	m_roofSectorsArr.push_back(std::make_shared<CFloor>(CFloor({ pos.x + 1, pos.y + 1 }, pos, 2.f)));

}
