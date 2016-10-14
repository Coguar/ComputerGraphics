#pragma once
#include "Constants.h"

class CShape
{
public:
	enum MoveDirection 
	{
		Left = 0,
		Right,
		Down,
		None,
	};

	CShape();
	CShape(int x, int y);
	bool Move(MoveDirection  direction, matrix const& field);
	void WriteIntoField(matrix & field);
	const matrix & GetMatrix() const;
	const glm::ivec2 & GetPosition() const;
	void RotateShape(matrix const& field);
	bool CheckCollision(MoveDirection direction, matrix const& field, matrix const& shapeMatrix);
	void SetPosition(glm::ivec2 pos);
	~CShape();
private:
	matrix m_shapeMatrix;
	glm::ivec2 position;
};

