#include "stdafx.h"
#include "SoundSource.h"
#include <iostream>
// Disable deprecated warning
#pragma warning (disable:4996)

CSoundSource::CSoundSource()
	: m_isPlaying(false)
{
	alGenBuffers(1, &m_buffer);          // create buffer
	alGenSources(1, &m_source);          // create source
}


CSoundSource::~CSoundSource()
{
	alDeleteBuffers(1, &m_buffer);
	alDeleteSources(1, &m_source);
}

bool CSoundSource::SetupSource(std::string const & fileName, bool isLoop)
{
	m_loop = isLoop;
	ALenum      format = 0;
	ALsizei     size = 0;
	ALvoid    * data = nullptr;
	ALsizei     freq = 0;
	ALboolean   loop = AL_TRUE;


	// load .wav data using alut
	
	//m_buffer = alutCreateBufferFromFile(fileName.c_str());

	if (alutGetError() != ALUT_ERROR_NO_ERROR)
		return false;
	alutLoadWAVFile((ALbyte *)fileName.c_str(), &format, &data, &size, &freq, &loop);
	alBufferData(m_buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	// setup source params
	alSourcei(m_source, AL_BUFFER, m_buffer);
	alSourcef(m_source, AL_PITCH, 1.0f);
	alSourcef(m_source, AL_GAIN, 1.0f);
	alSourcefv(m_source, AL_POSITION, m_sourcePos);
	alSourcefv(m_source, AL_VELOCITY, m_sourceVel);
	if(m_loop)
		loop = AL_TRUE;
	alSourcei(m_source, AL_LOOPING, loop);

	return true;
}

void CSoundSource::Play()
{
	if (!m_isPlaying || !m_loop)
	{
		m_isPlaying = true;
		alSourcePlay(m_source);
	}
}

void CSoundSource::Stop()
{
	m_isPlaying = false;
	alSourceStop(m_source);
}

void CSoundSource::SetSourcePosition(glm::vec3 const & position)
{
	m_sourcePos.x = position.x;
	m_sourcePos.y = position.y;
	m_sourcePos.z = position.z;

}

void CSoundSource::SetSourceVelocity(glm::vec3 const & velocity)
{
	m_sourceVel.x = velocity.x;
	m_sourceVel.y = velocity.y;
	m_sourceVel.z = velocity.z;

}

void CSoundSource::Update(float dt)
{
	alSourcefv(m_source, AL_POSITION, m_sourcePos);
	alSourcefv(m_source, AL_VELOCITY, m_sourceVel);
}

