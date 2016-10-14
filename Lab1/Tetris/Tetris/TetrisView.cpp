#include "stdafx.h"
#include "TetrisView.h"
#include "glut.h"

namespace
{
	//TODO: rename normally
	void PrintBitmapString(void* font, std::string const& s)
	{
		for (auto &it : s)
		{
			glutBitmapCharacter(font, it);
		}
	}

	//TODO: rename normally
	void PrintWorld(float x, float y, std::string const& word)
	{
		glColor4f(0.0, 1.0, 0.0, 0.0);
		glRasterPos2f(x, y);
		PrintBitmapString(GLUT_BITMAP_9_BY_15, word);
	}

	//TODO: rename normally
	void DrawSquare(glm::ivec2 const& pos)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2i(pos.x, pos.y);
		glVertex2i(pos.x + SQUARE_HEIGHT, pos.y);
		glVertex2i(pos.x + SQUARE_HEIGHT, pos.y + SQUARE_HEIGHT);
		glVertex2i(pos.x, pos.y + SQUARE_HEIGHT);
		glEnd();

	}

	void SetColorByCode(int id)
	{
		switch (id)
		{
		case 1: glColor3f(0, 0, 0); break;
		case 0: glColor3f(1, 1, 1); break;
		case 2: glColor3f(1, 0, 0); break;
		case 3: glColor3f(0, 1, 0); break;
		case 4: glColor3f(0, 0.5, 1); break;
		case 5: glColor3f(1, 1, 0); break;
		case 6: glColor3f(1, 0, 1); break;
		case 7: glColor3f(0, 1, 1); break;
		case 8: glColor3f(0, 0.5, 0.2); break;
		}
	}

	void DrawItem(CShape const& shape, bool isNeedDrawEmpty)
	{
		matrix block = shape.GetMatrix();
		glm::ivec2 pos = shape.GetPosition();
		int i = 0;
		for (auto &line : block)
		{
			int j = 0;
			for (auto &box : line)
			{
				if (block[i][j] != 0 || isNeedDrawEmpty)
				{
					SetColorByCode(block[i][j]);
					DrawSquare({ (j + pos.x) * SQUARE_HEIGHT, (i + pos.y) * SQUARE_HEIGHT });
				}
				++j;
			}
			++i;
		}
	}

	void DrawTetrisField(Tetris const& tetris)
	{
		matrix field = tetris.GetField();
		int i = 0;
		for (auto &line : field)
		{
			int j = 0;
			for (auto &box : line)
			{
				SetColorByCode(box);
				DrawSquare({ j * SQUARE_HEIGHT, i * SQUARE_HEIGHT });
				++j;
			}
			++i;
		}
		DrawItem(tetris.GetShape(), false);
		DrawItem(tetris.GetNextShape(), true);

	}
}

TetrisView::TetrisView()
{
}


TetrisView::~TetrisView()
{
}

void TetrisView::SetLvlPos(glm::vec2 pos)
{
	m_lvlPos = pos;
}

void TetrisView::SetTargetLinePos(glm::vec2 pos)
{
	m_targetLinePos = pos;
}

void TetrisView::SetCurrentLinePos(glm::vec2 pos)
{
	m_currentLinePos = pos;
}

void TetrisView::SetScorePos(glm::vec2 pos)
{
	m_scorePos = pos;
}

void TetrisView::DrawTetris(Tetris const & tetris, int score, int lvl, int target, int progress)
{
	DrawTetrisField(tetris);
	PrintWorld(m_lvlPos.x, m_lvlPos.y, std::string(LEVEL_STR + std::to_string(lvl)));
	PrintWorld(m_targetLinePos.x, m_targetLinePos.y, std::string(TARGET_STR + std::to_string(target)));
	PrintWorld(m_currentLinePos.x, m_currentLinePos.y, std::string(PROGRESS_STR + std::to_string(progress)));
	PrintWorld(m_scorePos.x, m_scorePos.y, std::string(SCORE_STR + std::to_string(score)));

}

void TetrisView::DrawMenu(int score)
{
	PrintWorld(MENU_LEVEL_STR_POS.x, MENU_LEVEL_STR_POS.y, std::string(SCORE_STR + std::to_string(score)));
	PrintWorld(START_STR_POS.x, START_STR_POS.y, START_STR);
}

void TetrisView::DrawFlashingText(CFlashingText const & fTxt)
{
	if (fTxt.IsVisible())
	{
		glm::vec2 pos = fTxt.GetPosition();
		PrintWorld(pos.x, pos.y, fTxt.GetText());
	}
}


