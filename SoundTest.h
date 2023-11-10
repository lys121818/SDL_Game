#pragma once
#include "GameObject.h"

struct Mix_Chunk;
struct Mix_Channel;

class SoundTest : public GameObject
{

private:

	Mix_Chunk* m_pSound;

	int m_activeSoundChannel;

public:
	SoundTest(const char* pPath);
	~SoundTest();

	virtual void HandleEvent(SDL_Event* pEvent)override;

	// Inherited via GameObject
	Status GetStatus() override;
	SDL_Rect GetTransform() override;
};

