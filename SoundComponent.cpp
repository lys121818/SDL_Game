#include "SoundComponent.h"
#include "GameStateMachine.h"
#include <iostream>

SoundComponent::SoundComponent()
	:
	m_activeSoundChannel(-1),
	m_masterVolume(MIX_MAX_VOLUME),
	m_isPlaying(false),
	m_pChunk(nullptr)
{
}

SoundComponent::~SoundComponent()
{
	Destory();
}

void SoundComponent::AddSoundChunk(const char* pDir)
{
	m_pChunk = Mix_LoadWAV(pDir);

	if (m_pChunk == nullptr)
		std::cout << "[SoundTest] Failed to load sound. Error: " << SDL_GetError() << std::endl;
	else
		m_pChunk->volume = (Uint8)m_masterVolume;
}

void SoundComponent::PlayChunk(const int& loops, const int& channel)
{
	if (m_pChunk == nullptr)
	{
		std::cout << "[SoundComponent] Failed to play chunk\n";
		return;
	}

	// if chunk is not playing
	if (m_isPlaying == false)
	{
		m_activeSoundChannel = Mix_PlayChannel(channel, m_pChunk, loops);
		m_isPlaying = true;
	}
	// if its not a loop chunk
	else if (loops != -1)
	{
		StopChunk();
		m_activeSoundChannel = Mix_PlayChannel(channel, m_pChunk, loops);
	}

	
}

void SoundComponent::StopChunk()
{
	if (m_isPlaying)
	{
		Mix_HaltChannel(m_activeSoundChannel);
		m_activeSoundChannel = -1;
		m_isPlaying = false;
	}
}

void SoundComponent::Destory()
{
	Mix_FreeChunk(m_pChunk);
	m_pChunk = nullptr;
}
