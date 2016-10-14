#pragma once
#include "Tetris.h"
#include "FlashingText.h"

class TetrisView
{
public:
	TetrisView();
	~TetrisView();
	
	void SetLvlPos(glm::vec2 pos);
	void SetTargetLinePos(glm::vec2 pos);
	void SetCurrentLinePos(glm::vec2 pos);
	void SetScorePos(glm::vec2 pos);
	void DrawTetris(Tetris const& tetris, int score, int lvl, int target, int progress);
	void DrawMenu(int score);
	void DrawFlashingText(CFlashingText const& fTxt);
private:
	glm::vec2 m_lvlPos;
	glm::vec2 m_targetLinePos;
	glm::vec2 m_currentLinePos;
	glm::vec2 m_scorePos;
};

