#pragma once
#include "Constants.h"
#include "Shape.h"
#include "ITetrisInterface.h"


class Tetris
{
public:
	Tetris() = default;
	Tetris(ITetrisListener & listener);
	~Tetris();

	const matrix & GetField() const;
	const CShape & GetShape() const;
	const CShape & GetNextShape() const;

	void MoveShape(CShape::MoveDirection direction);
	int GetEmptyLinesCount();
	void RotateShape();
private:
	matrix m_playingField;
	CShape m_fallingItem;
	CShape m_nextItem;

	ITetrisListener &m_listener;
	bool DropNewShape();
	void FrozeOldBlock();
	size_t RemoveFullLines();
	void MoveLines(int lineNumber);
	bool isCreateNewBlock = false;
};

