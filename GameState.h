#pragma once
#include <SDL.h>

//==================================================================================================//
/// GAME STATE
/// A Game State / Scene interface
//==================================================================================================//
class Textures;

class GameState
{
public:
	virtual ~GameState() {}

	// Initializes the scene.
	virtual void Enter() {}

	// Update the scene
	virtual void Update(double) {}

	// Render the scene.
	virtual void Render(SDL_Renderer*, Textures*) {}

	// Handles the event in the context of this scene.
	virtual bool HandleEvent(SDL_Event*) { return false; }

	// Cleans up the state
	virtual void Exit() {}
};

