#pragma once
#include "SoundSource.h"
#include <vector>
#include <memory>
#include <random>

class CRandomSoundPlayer
{
public:
	CRandomSoundPlayer();
	~CRandomSoundPlayer();

	void AddSound(std::string const & fileName);
	void PlayingRandomSound(bool play);
	void SetDeltaTime(float time);
	void Update(float dt);
private:
	std::vector<std::unique_ptr<CSoundSource>> m_sounds;
	std::mt19937 m_rng;
	float m_deltaTime;
	float m_currentDeltaTime;
	bool m_isPlaying;
};

