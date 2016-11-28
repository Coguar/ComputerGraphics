#include "stdafx.h"
#include "RandomSoundPlayer.h"
namespace
{
	const float DEFAULT_DELTA_TIME = 20.0f;

	size_t GetRandomNumber(std::mt19937 * rng, size_t max)
	{
		std::uniform_int_distribution<>num(0, 5);
		return num(*rng);
	}
}

CRandomSoundPlayer::CRandomSoundPlayer()
	: m_deltaTime(DEFAULT_DELTA_TIME)
	, m_currentDeltaTime(DEFAULT_DELTA_TIME)
	, m_isPlaying(false)
{
}


CRandomSoundPlayer::~CRandomSoundPlayer()
{
}

void CRandomSoundPlayer::AddSound(std::string const & fileName)
{
	m_sounds.push_back(std::make_unique<CSoundSource>());
	m_sounds.back()->SetupSource(fileName, false);
}

void CRandomSoundPlayer::PlayingRandomSound(bool play)
{
	m_isPlaying = play;
}

void CRandomSoundPlayer::SetDeltaTime(float time)
{
	m_deltaTime = time;
}

void CRandomSoundPlayer::Update(float dt)
{
	m_currentDeltaTime += dt;
	if (m_currentDeltaTime >= m_deltaTime && m_sounds.size() > 0 && m_isPlaying)
	{
		auto id = GetRandomNumber(&m_rng, m_sounds.size() - 1);
		m_sounds[id]->Play();
		m_currentDeltaTime = 0;
	}
}
