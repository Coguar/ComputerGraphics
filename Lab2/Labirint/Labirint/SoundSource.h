#pragma once
//#include <al.h>
#include <alut.h>
#include "src\Vector3D.h"

class CSoundSource
{
public:
	CSoundSource();
	~CSoundSource();
	bool SetupSource(std::string const & fileName, bool isLoop);
	void Play();
	void Stop();
	void SetSourcePosition(glm::vec3 const & position);
	void SetSourceVelocity(glm::vec3 const & velocity);
	void Update(float dt);
private:
	ALuint m_buffer;
	ALuint m_source;                            // source of sound
	
	Vector3D  m_sourcePos = { 0, 0, 2 };          // source position
	Vector3D  m_sourceVel = { 0, 0, 0 };          // source velocity (used for Doppler effect)

	bool m_isPlaying;
	bool m_loop;
};

