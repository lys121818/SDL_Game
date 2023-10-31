#pragma once
#include "GameState.h"
#include "ImageObject.h"
#include "Textures.h"
#include "CubeColider.h"
#include "TiledMap.h"
#include "CollisionReferee.h"
#include "AnimationComponent.h"
#include "ImageObject.h"
#include "GameObject.h"
#include "GameSetting.h"

//==================================================================================================//
/// STAGE 01
/// Game state representing the STAGE 01.
//==================================================================================================//

class Platformer;

class Stage01 : public GameState
{
private:
	// Max value of gameobject to be create
	static constexpr size_t s_kMaxGameObjectCount = MAXGAMEOBJECT;

	// Player Information on start
	static constexpr Vector2 s_kPlayerStartingPoisition = Vector2{ PLAYERPOSITION };
	static constexpr Vector2 s_kPlayerStartingSize = Vector2{ PLAYERSIZEVECTOR2 };

	// Game Playing Timer
	double m_CurrentTime;

	// Pointer to the State Machine running this state.
	Platformer* m_pOwner;

	// Player Object
	CubeColider* m_pPlayer;

	// BackGround Image
	ImageObject* m_pBackground;

	// Tile Map
	TiledMap* m_pTiledMap;

	// Referee to manage active colliders.
	CollisionReferee m_collisionReferee;

	// Vector of gameObjects
	std::vector<GameObject*> m_vpGameObjects;	//Vector contains pointer of gameobjects

	// Pair of animation collections
	std::unordered_map<const char*, AnimationComponent*> m_mpAnimations;

public:
	Stage01(Platformer* pOwner);
	~Stage01();
	// Initializes the scene.
	void Enter() override;

	// Update the scene
	void Update(double deltaTime) override;

	// Render the scene.
	void Render(SDL_Renderer* pRenderer, Textures* pTextures) override;

	// Handles the event in the context of this scene.
	bool HandleEvent(SDL_Event* pEvent) override;


private:
	// Init Game settings
	void InitGame();

	// PROCESSING EVENT
	// Every events using keyboards works here
	bool ProcessKeyboardEvent(SDL_KeyboardEvent* pData);
	// Every events using mouse works here
	bool ProcessMouseEvent(SDL_MouseButtonEvent* pData);
	// Every events using Window works here
	bool ProcessWindowEvent(SDL_WindowEvent* pData);

	// Load all the images texture before runs
	void DestoryGameObjects(std::vector<GameObject*> vector);

	// Add additional gameobject to vector
	void AddGameObject(GameObject* object);

	// returns true if the game is over
	bool UpdateGamestate();

	// Cleans up the state
	void Exit() override;
};

