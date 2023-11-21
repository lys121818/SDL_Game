#pragma once
#include <SDL_mixer.h>
struct _Mix_Music;

class BackgroundMusicComponent
{

	_Mix_Music* m_pCurrentBackgroundMusic;
	_Mix_Music* m_pNextBackgroundMusic;

	// Directory of the music
	const char* m_currentBGMusic;

	bool m_isPlaying;
public:
	BackgroundMusicComponent();
	~BackgroundMusicComponent();

	void UpdateBGMusic();

	void SetBGMusic(const char* pFisrtDir, const char* pSecondDir);

	void ToggleMusic();

	void Destroy();

};

