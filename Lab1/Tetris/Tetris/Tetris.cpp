#include "stdafx.h"
#include "Tetris.h"


Tetris::Tetris(ITetrisListener & listener)
	: m_listener(listener)
{
	m_playingField.push_back(BORDER);
	for (int i = 0; i < 20; ++i)
	{
		m_playingField.push_back(CENTER);
	}
	m_playingField.push_back(BORDER);
	m_playingField.push_back(BORDER);
	m_nextItem = CShape(15, 6);
	DropNewShape();
}


Tetris::~Tetris()
{
}

const matrix & Tetris::GetField() const
{
	return m_playingField;
}

const CShape & Tetris::GetShape() const
{
	return m_fallingItem;
}

const CShape & Tetris::GetNextShape() const
{	
	return m_nextItem;
}

//TODO: make Tetris Interface (ITetris listener)
void Tetris::MoveShape(CShape::MoveDirection direction)
{
	size_t score = 0;
	if (!m_fallingItem.Move(direction, m_playingField))
	{
		FrozeOldBlock();
		score = RemoveFullLines();
		if (!DropNewShape())
		{
			m_listener.onLosed();
		}
	}
	m_listener.onScoreAdded(score);
}

int Tetris::GetEmptyLinesCount()
{
	size_t emptyLinesCount = 0;
	for (size_t i = 1; i < m_playingField.size() - 2; ++i)
	{
		if (std::all_of(m_playingField[i].begin() + 2, m_playingField[i].end() - 2, [](int i) {return i == 0; }))
		{
			++emptyLinesCount;
		}
	}
	return emptyLinesCount;
}

void Tetris::RotateShape()
{
	m_fallingItem.RotateShape(m_playingField);
}

bool Tetris::DropNewShape()
{

	m_fallingItem = m_nextItem;
	m_fallingItem.SetPosition({ 5, 1 });
	m_nextItem = CShape(15, 6);

	if (m_fallingItem.CheckCollision(CShape::MoveDirection::None, m_playingField, m_fallingItem.GetMatrix()))
	{
		return false;
	}
	return true;
}

void Tetris::FrozeOldBlock()
{
	m_fallingItem.WriteIntoField(m_playingField);
}

size_t Tetris::RemoveFullLines()
{
	size_t score = 0;
	for (size_t i = 1; i < m_playingField.size() - 2; ++i)
	{
		if (std::all_of(m_playingField[i].begin() + 1, m_playingField[i].end() - 1, [](int i) {return i != 0; }))
		{
			MoveLines(i);
			++score;
		}
	}
	return score;
}

void Tetris::MoveLines(int lineNumber)
{
	for (int i = lineNumber; i > 1; --i)
	{
		m_playingField[i] = m_playingField[i - 1];
	}
	m_playingField[1] = CENTER;
}
