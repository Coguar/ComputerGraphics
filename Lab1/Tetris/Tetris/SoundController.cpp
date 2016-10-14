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
	// Позиция слушателя.
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

	// Скорость слушателя.
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

	// Ориентация слушателя. (Первые 3 элемента – направление «на», последние 3 – «вверх»)
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

	// Открываем заданное по умолчанию устройство
	pDevice = alcOpenDevice(NULL);
	// Проверка на ошибки
	if (!pDevice)
	{
		ERRMSG("Default sound device not present");
		return false;
	}
	// Создаем контекст рендеринга
	pContext = alcCreateContext(pDevice, NULL);
	if (!CheckALCError()) return false;

	// Делаем контекст текущим
	alcMakeContextCurrent(pContext);

	// Устанавливаем параметры слушателя
	// Позиция
	alListenerfv(AL_POSITION, ListenerPos);
	// Скорость
	alListenerfv(AL_VELOCITY, ListenerVel);
	// Ориентация
	alListenerfv(AL_ORIENTATION, ListenerOri);
	return true;
}

void DestroyOpenAL()
{
	// Очищаем все буффера
	for (TBuf::iterator i = Buffers.begin(); i != Buffers.end(); i++)
		alDeleteBuffers(1, &i->second.ID);
	// Выключаем текущий контекст
	alcMakeContextCurrent(NULL);
	// Уничтожаем контекст
	alcDestroyContext(pContext);
	// Закрываем звуковое устройство
	alcCloseDevice(pDevice);
}


SoundController::SoundController()
{
}


SoundController::~SoundController()
{
}
