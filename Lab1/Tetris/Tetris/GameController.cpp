#include "stdafx.h"
#include "GameController.h"

namespace
{
	int GetScoreForLines(int lineCount)
	{
		switch (lineCount)
		{
		case 1: return SCORE_FOR_1;
		case 2: return SCORE_FOR_2;
		case 3: return SCORE_FOR_3;
		case 4: return SCORE_FOR_4;
		default: return 0;
		}
	}
}
CGameController::CGameController()
{
	m_pauseTxt = CFlashingText(PAUSE_FLASHING_TIME, PAUSE_STR_POS, PAUSE_STR);
	m_view.SetLvlPos(LEVEL_STR_POS);
	m_view.SetTargetLinePos(TARGET_STR_POS);
	m_view.SetCurrentLinePos(PROGRESS_STR_POS);
	m_view.SetScorePos(SCORE_STR_POS);
}


CGameController::~CGameController()
{

}

const Tetris & CGameController::GetTetris() const
{
	return *m_tetris;
}

void CGameController::StartNewLevel()
{
	++m_level;
	m_targetLines = START_DIFFICULTY_LEVEL * m_level;
	if (m_speed > MAX_SPEED)
	{
		m_speed -= BOOST_FOR_LEVEL;
	}
	m_currentLines = 0;
	m_score += m_tetris->GetEmptyLinesCount() * SCORE_BY_EMPTY_LINE;
	m_tetris = std::make_unique<Tetris>(*this);
}

void CGameController::UpdateTetris(float deltaSeconds)
{
	if (m_state == GameState::Game)
	{
		if (!m_isPaused)
		{
			m_currentDelay += deltaSeconds;
			if (m_currentDelay >= m_speed)
			{
				m_currentDelay = 0;
				m_tetris->MoveShape(CShape::MoveDirection::Down);
			}
		}
		else
		{
			m_pauseTxt.Update(deltaSeconds);
		}
	}
}

void CGameController::OnKeyboardEvent(const SDL_KeyboardEvent & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.keysym.sym == SDLK_p)
		{
			ChangePauseState();
		}
		else if (!m_isPaused)
		{
			switch (event.keysym.sym)
			{
			case SDLK_LEFT:
				m_tetris->MoveShape(CShape::Left);
				break;
			case SDLK_RIGHT:
				m_tetris->MoveShape(CShape::Right);
				break;
			case SDLK_DOWN:
				m_tetris->MoveShape(CShape::Down);
				break;
			case SDLK_UP:
				m_tetris->RotateShape();
				break;
			case SDLK_SPACE:
				StartGame();
				break;
			}
		}
	}
}

const CGameController::GameState CGameController::GetState() const
{
	return m_state;
}

const int CGameController::GetScore() const
{
	return m_score;
}

const int CGameController::GetCurrentLines() const
{
	return m_currentLines;
}

const int CGameController::GetTargetLines() const
{
	return m_targetLines;
}

void CGameController::StartGame()
{
	if (m_state == GameState::Menu)
	{
		m_tetris = std::make_unique<Tetris>(*this);
		m_score = 0;
		m_targetLines = START_DIFFICULTY_LEVEL;
		m_currentLines = 0;
		m_speed = START_SPEED;
		m_level = 1;
		m_currentDelay = 0;

		m_state = GameState::Game;
	}
}

void CGameController::DrawGame()
{
	if (m_state == GameState::Game)
	{
		m_view.DrawTetris(*m_tetris, m_score, m_level, m_targetLines, m_currentLines);
		if (m_isPaused)
		{
			m_view.DrawFlashingText(m_pauseTxt);
		}
	}
	else
	{
		m_view.DrawMenu(m_score);
	}
}

void CGameController::ChangePauseState()
{
	if (m_state == GameState::Game)
	{
		m_isPaused = !m_isPaused;
	}
}

void CGameController::onLosed()
{
	m_state = GameState::Menu;
}

void CGameController::onScoreAdded(size_t score)
{
	AddScores(score);
}

void CGameController::CheckLevelProgress()
{
	if (m_currentLines >= m_targetLines)
	{
		StartNewLevel();
	}
}

void CGameController::AddScores(int progress)
{
	if (progress != -1)
	{
		m_score += GetScoreForLines(progress);
		m_currentLines += progress;
		CheckLevelProgress();
	}
	else
	{
		m_state = GameState::Menu;
	}
}
