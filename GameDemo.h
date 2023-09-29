#pragma once
// From the passed Assignmnet
/*
#include "GameSceneEditor.h"
*/

#include <vector>
#include <SDL.h>
#include <iostream>
#include "ColorDefine.h"
#include "CubeColider.h"
#include "GameObject.h"
#include "ImageObject.h"
class GameDemo
{

private:
	static constexpr size_t s_kMaxGameObjectCount = 10;
	// Game Playing Timer
	double m_CurrentTime;

	// Pointer to the application window managed by SDL.
	SDL_Window* m_pWindow;


	// Pointer to the renderer that can be used to draw output.
	SDL_Renderer* m_pRenderer;

	// Background Image
	ImageObject* m_pBackground;

	// Player Object
	CubeColider* m_pPlayer;

	// Vector of gameObjects
	std::vector<GameObject*> m_vpGameObjects;	//Vector contains pointer of gameobjects

	
public:
	// Initializing SDL and return errorCode or 0
	int Init();

	// Game mainly Runs in this function
	void Run();

	// Destroys the SDL elements or the pointers
	void Destroy();

private:
	
	// Processes events received by SDL. Returns whether or not the game should continue.
	bool ProcessEvents();
	
	// Draws this program's output
	void DisplayOutput();

	// Updates the state of the game simulation based on the passage of time and any events that were detected.
	void UpdateGameState(double deltatime);

	// PROCESSING EVENT
	// Every events using keyboards works here
	bool ProcessKeyboardEvent(SDL_KeyboardEvent* pData);
	// Every events using mouse works here
	bool ProcessMouseEvent(SDL_MouseButtonEvent* pData);
	// Every events using Window works here
	bool ProcessWindowEvent(SDL_WindowEvent* pData);

	// INITIALIZE
	// Create Window
	int CreateWindow();

	// Init Game settings
	void InitGame();

	void AddGameObject(GameObject* object);

};

