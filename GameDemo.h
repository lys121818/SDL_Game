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
#include "GameSetting.h"
#include "CubeColider.h"
#include "GameObject.h"
#include "ImageObject.h"
#include "AnimationComponent.h"
#include "Textures.h"
#include "CollisionReferee.h"

class GameDemo
{
private:
	// Max value of gameobject to be create
	static constexpr size_t s_kMaxGameObjectCount = MAXGAMEOBJECT;

	// Player Information on start
	static constexpr Vector2 s_kPlayerStartingPoisition = Vector2{ PLAYERPOSITION };
	static constexpr Vector2 s_kPlayerStartingSize = Vector2{ PLAYERSIZEVECTOR2 };

	// Background information on start
	static constexpr int s_kBackgroundWidth = BACKGROUNDTILESIZE;
	static constexpr int s_kBackgroundHeight = BACKGROUNDTILESIZE;

	// Game Playing Timer
	double m_CurrentTime;

	// Pointer to the application window managed by SDL.
	SDL_Window* m_pWindow;

	// Pointer to the renderer that can be used to draw output.
	SDL_Renderer* m_pRenderer;

	// Player Object
	CubeColider* m_pPlayer;


	// Class that handles Textures
	Textures* m_pTexture;

	// Referee to manage active colliders.
	CollisionReferee m_collisionReferee;
	


	// Texture representing the appearance of object
	//std::vector<SDL_Texture*> m_vpTextures;
	//std::unordered_map<const char*, SDL_Texture*> m_mpTextures;
	// Vector of gameObjects
	std::vector<GameObject*> m_vpGameObjects;	//Vector contains pointer of gameobjects
	// Vector for background tiles
	std::vector<GameObject*> m_vpBackgrounds;
	
	std::unordered_map<const char*, AnimationComponent*> m_mpAnimations;

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
	void UpdateGameState(double deltaTime);

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

	// Set background
	void InitBackground();

	// Load all the images texture before runs
	void DestoryGameObjects(std::vector<GameObject*> vector);

	// Add additional gameobject to vector
	void AddGameObject(GameObject* object);

};