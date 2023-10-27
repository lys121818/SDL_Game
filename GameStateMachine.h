#pragma once
#include <SDL.h>

//==================================================================================================//
/// GAME STATE MACHINE
/// An Interfave for handling game states / scene
//==================================================================================================//

class GameState;

class GameStateMachine
{
public:
	virtual ~GameStateMachine() {}

	// Update the current state.
	virtual void UpdateCurrentState(double) = 0;

	// Render the current state.
	virtual void RenderCurrentState(SDL_Renderer*) = 0;

	// Handle the given event within the current state.
	virtual bool HandleEvent(SDL_Event*) = 0;

	virtual void ChangeState(GameState*) = 0;
	 

};

