#include "stdafx.h"
#include "Shape.h"
#include <ctime>
#include <random>

namespace
{
	int GetRandomNumber(int minVal, int maxVal)
	{
		std::time_t now = std::time(0);
		std::mt19937 gen{ static_cast<std::uint32_t>(now) };
		std::uniform_int_distribution<> dist{ minVal, maxVal };
		return dist(gen);
	}
}

CShape::CShape()
{

}

CShape::CShape(int x, int y)
	: position({x, y})
{
	m_shapeMatrix = SHAPES_LIST[GetRandomNumber(0, SHAPES_LIST.size() - 1)];
}

bool CShape::Move(MoveDirection  direction, matrix const& field)
{
	int dx = 0;
	int dy = 0;
	switch (direction)
	{
	case CShape::Left: dx = -1;
		break;
	case CShape::Right: dx = 1;
		break;
	case CShape::Down: dy = 1;
		break;
	default:
		break;
	}

	if (CheckCollision(direction, field, m_shapeMatrix))
	{
		if (direction == Down)
		{
			return false;
		}
		return true;
	}
	else
	{
		position.x += dx;
		position.y += dy;

		return true;
	}
}

void CShape::WriteIntoField(matrix & field)
{
	for (int i = 0; i < m_shapeMatrix.size(); ++i)
	{
		for (int j = 0; j < m_shapeMatrix.size(); ++j)
		{
			if (m_shapeMatrix[i][j] != 0)
			{
				field[i + position.y][j + position.x] = m_shapeMatrix[i][j];
			}
		}
	}
}

const matrix & CShape::GetMatrix() const
{
	return m_shapeMatrix;
}

const glm::ivec2 & CShape::GetPosition() const
{
	return position;
}

void CShape::RotateShape(matrix const& field)
{
	matrix rotatedShape = ZERO_SHAPE;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rotatedShape[j][3 - i] = m_shapeMatrix[i][j] ;
		}
	}

	if (!CheckCollision(MoveDirection::None, field, rotatedShape))
	{
		m_shapeMatrix = rotatedShape;
	}
}


CShape::~CShape()
{
}

bool CShape::CheckCollision(MoveDirection direction, matrix const& field, matrix const& shapeMatrix)
{
	int dx = 0;
	int dy = 0;
	switch (direction)
	{
	case CShape::Left: dx = -1;
		break;
	case CShape::Right: dx = 1;
		break;
	case CShape::Down: dy = 1;
		break;
	default:
		break;
	}

	for (int i = 0; i < m_shapeMatrix.size(); ++i)
	{
		for (int j = 0; j < m_shapeMatrix.size(); ++j)
		{
			if (shapeMatrix[i][j] != 0 && field[i + position.y + dy][j + position.x + dx] != 0 )
			{
				return true;
			}
		}
	}
	return false;
}

void CShape::SetPosition(glm::ivec2 pos)
{
	position = pos;
}
