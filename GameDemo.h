#pragma once
// From the passed Assignmnet
/*
#include "GameSceneEditor.h"
*/

#include <vector>
#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Defines.h"
#include "Textures.h"


class GameStateMachine;

class GameDemo
{
private:
	// Game Playing Timer
	double m_CurrentTime;

	// Pointer to the application window managed by SDL.
	SDL_Window* m_pWindow;

	// Pointer to the renderer that can be used to draw output.
	SDL_Renderer* m_pRenderer;

	// Pointer to the state machine for managing game state.
	GameStateMachine* m_pStateMachine;

	// Class that handles Textures
	Textures* m_pTextures;

public:
	// Initializing SDL and return errorCode or 0
	int Init(GameStateMachine* pGameStateMachine);

	// Game mainly Runs in this function
	void Run();

	// Destroys the SDL elements or the pointers
	void Destroy();

	// load texture which are being used in the scene
	void PreloadTexture();

	// Return pointer to the renderer
	SDL_Renderer* GetRenderer() { return m_pRenderer; }
private:

	// Processes events received by SDL. Returns whether or not the game should continue.
	bool ProcessEvents();

	// Draws this program's output
	void DisplayOutput();

	// Updates the state of the game simulation based on the passage of time and any events that were detected.
	void UpdateGameState(double deltaTime);

	// INITIALIZE
	// Create Window
	int CreateWindow();



};