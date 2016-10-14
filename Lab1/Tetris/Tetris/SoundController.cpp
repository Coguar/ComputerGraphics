#include "stdafx.h"
#include "SoundController.h"
#include <al.h>
#include <alc.h>
#include <alu.h>
#include <alut.h>
#include <alBuffer.h>
#include <alError.h>
#include <al>
//#pragma comment(lib, "libalut.lib")
//#pragma comment(lib, "OpenAL32.lib")

ALCdevice * pDevice;
ALCcontext * pContext;

bool InitializeOpenAL()
{
	// ������� ���������.
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

	// �������� ���������.
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

	// ���������� ���������. (������ 3 �������� � ����������� ���, ��������� 3 � �������)
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

	// ��������� �������� �� ��������� ����������
	pDevice = alcOpenDevice(NULL);
	// �������� �� ������
	if (!pDevice)
	{
		ERRMSG("Default sound device not present");
		return false;
	}
	// ������� �������� ����������
	pContext = alcCreateContext(pDevice, NULL);
	if (!CheckALCError()) return false;

	// ������ �������� �������
	alcMakeContextCurrent(pContext);

	// ������������� ��������� ���������
	// �������
	alListenerfv(AL_POSITION, ListenerPos);
	// ��������
	alListenerfv(AL_VELOCITY, ListenerVel);
	// ����������
	alListenerfv(AL_ORIENTATION, ListenerOri);
	return true;
}

void DestroyOpenAL()
{
	// ������� ��� �������
	for (TBuf::iterator i = Buffers.begin(); i != Buffers.end(); i++)
		alDeleteBuffers(1, &i->second.ID);
	// ��������� ������� ��������
	alcMakeContextCurrent(NULL);
	// ���������� ��������
	alcDestroyContext(pContext);
	// ��������� �������� ����������
	alcCloseDevice(pDevice);
}


SoundController::SoundController()
{
}


SoundController::~SoundController()
{
}
