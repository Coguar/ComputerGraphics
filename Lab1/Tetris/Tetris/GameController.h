#pragma once
#include "TetrisView.h"
#include "ITetrisInterface.h"
#include <memory>

class CGameController : public ITetrisListener
{
public:
	CGameController();
	~CGameController();

	enum GameState
	{
		Menu = 0,
		Game,
	};

	const Tetris & GetTetris() const;
	void StartNewLevel();
	void UpdateTetris(float deltaSeconds);
	void OnKeyboardEvent(const SDL_KeyboardEvent & event);
	const GameState GetState() const;
	const int GetScore() const;
	const int GetCurrentLines() const;
	const int GetTargetLines() const;
	void StartGame();

	void DrawGame();

	void ChangePauseState();

	void onLosed() override;
	void onScoreAdded(size_t score) override;
private:
	void CheckLevelProgress();
	void AddScores(int progress);

	std::unique_ptr<Tetris> m_tetris;
	TetrisView m_view;
	CFlashingText m_pauseTxt;

	int m_score = 0;
	int m_targetLines = START_DIFFICULTY_LEVEL;
	int m_currentLines = 0;
	float m_speed = START_SPEED;
	int m_level = 1;
	float m_currentDelay = 0;

	bool m_isPaused = false;

	GameState m_state = GameState::Menu;
};

