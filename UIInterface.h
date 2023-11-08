#pragma once
#include <SDL.h>
#include "Textures.h"


class UIInterface
{
public:
	virtual ~UIInterface() {}

	// Initialize
	virtual void InitUI() = 0;

	// Update Function on call
	virtual void UpdateUI() = 0;

	// Update Function constantly
	virtual void UpdateUI(double) {};

	// Render UI
	virtual void Render(SDL_Renderer*, Textures*) = 0;

	// Event handle in UI
	virtual bool HandleEvent(SDL_Event*) { return false; }

};