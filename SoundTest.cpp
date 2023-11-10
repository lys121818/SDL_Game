#include "SoundTest.h"
#include <SDL_mixer.h>
#include <iostream>

SoundTest::SoundTest(const char* pPath)
	:
	m_pSound(nullptr),
	m_activeSoundChannel(-1)
{
	m_pSound = Mix_LoadWAV(pPath);
	if (m_pSound == nullptr)
		std::cout << "[SoundText] Failed to load sound. Error: " << SDL_GetError() << std::endl;
}

SoundTest::~SoundTest()
{
	if (m_pSound != nullptr)
	{
		Mix_FreeChunk(m_pSound);
		m_pSound = nullptr;
	}
}

void SoundTest::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
		case SDL_KEYDOWN:
		{
			if (m_activeSoundChannel == -1)
			{
				m_activeSoundChannel = Mix_PlayChannel(-1, m_pSound, 0);
			}
			else
			{
				Mix_HaltChannel(m_activeSoundChannel);
				m_activeSoundChannel = -1;
			}
			break;
		}
	default:
		break;
	}
}

Status SoundTest::GetStatus()
{
	return Status();
}

SDL_Rect SoundTest::GetTransform()
{
	return SDL_Rect();
}
