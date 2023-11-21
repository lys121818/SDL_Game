#pragma once
#include <SDL_mixer.h>
#include <unordered_map>
#include <string>

struct Mix_Chunk;
struct Mix_Channel;

class SoundComponent
{
	Mix_Chunk* m_pChunk;

	// Max Volume value
	size_t m_masterVolume;

	int m_activeSoundChannel;

	bool m_isPlaying;

public:
	SoundComponent();
	~SoundComponent();
	
	// add chunk to map with key value
	void AddSoundChunk(const char* pDir);

	// Play chunk call by key value
	void PlayChunk(const int& loops = 0, const int& channel = -1);
	
	// Stop Playing Chunk
	void StopChunk();

	// Set general Volume
	//void SetVolume(const size_t& volume) { m_masterVolume = volume; }

	// Set channel Volume
	void SetVolume(const size_t& volume) { Mix_Volume(m_activeSoundChannel, (int)GetChunkVolume(volume)); }

	// Set Chunk Volue
	void SetChunkVolume(const size_t& volume) { Mix_VolumeChunk(m_pChunk, (int)GetChunkVolume(volume)); }

	int GetActiveChannel(){ return m_activeSoundChannel; }

private:
	size_t GetChunkVolume(const size_t& volume) { return size_t(((float)volume / (float)MIX_MAX_VOLUME) * m_masterVolume); }

	void Destory();

};