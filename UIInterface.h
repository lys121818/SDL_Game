#pragma once
#include <SDL.h>
#include "Textures.h"


class UIInterface
{
public:
	virtual ~UIInterface() {}

	virtual void InitUI() = 0;

	// Update Function call
	virtual void UpdateUI() = 0;

	virtual void Render(SDL_Renderer*, Textures*) = 0;

	virtual bool HandleEvent(SDL_Event*) { return false; }

};