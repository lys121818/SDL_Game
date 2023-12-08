#pragma once
#include "GameState.h"
#include "ImageObject.h"
#include "Textures.h"
#include "PlayerObject.h"
#include "TiledMap.h"
#include "CollisionReferee.h"
#include "AnimationComponent.h"
#include "GameObject.h"
#include "GameSetting.h"
#include "InGameUI.h"
#include <fstream>

//============================================================//
/// STAGE 01
/// Game state representing the STAGE 01.
//============================================================//

class Platformer;

class Stage01 : public GameState
{
private:

	static constexpr int s_kMaxEnemyObjectCount = 2;

	// Max value of gameobject to be create
	static constexpr size_t s_kMaxGameObjectCount = MAX_GAMEOBJECT;

	static constexpr size_t s_kMaxBulletCount = MAX_BULLET;

	// Player Information on start
	static constexpr Vector2 s_kPlayerStartingPoisition = Vector2{ PLAYER_POSITION };
	static constexpr Vector2 s_kPlayerStartingSize = Vector2{ PLAYER_SIZE_VECTOR2 };

	// Game Playing Timer
	double m_CurrentTime;

	double m_loadingTime;

	// number of times the file has been overwrite
	size_t m_saves;

	// togle for pause game
	bool m_isPause;

	// file to load
	size_t m_fileIndex;

	// Enemy count
	int m_enemyCount = s_kMaxGameObjectCount;

	// Pointer to the State Machine running this state.
	Platformer* m_pOwner;

	// Player Object
	PlayerObject* m_pPlayer;

	// BackGround Image
	ImageObject* m_pBackground;

	// Tile Map
	TiledMap* m_pTiledMap;

	// Referee to manage active colliders.
	CollisionReferee m_collisionReferee;

	// Vector of gameObjects
	std::vector<GameObject*> m_vpGameObjects;	//Vector contains pointer of gameobjects

	// Vector of Bullets
	std::vector<GameObject*> m_vpBullets;

	// Controlls the UI
	InGameUI* m_pInGameUI;

public:
	Stage01(Platformer* pOwner, size_t fileIndex = 0);
	~Stage01();
	// Initializes the scene.
	void Enter() override;

	// Update the scene
	void Update(double deltaTime) override;

	// Render the scene.
	void Render(SDL_Renderer* pRenderer, Textures* pTextures) override;

	// Handles the event in the context of this scene.
	bool HandleEvent(SDL_Event* pEvent) override;

	// Cleans up the state
	void Exit() override;


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

	void DestoryGameObjects();

	// Add additional gameobject to vector
	void AddGameObject(GameObject* object);

	void CreateGameObject(const SDL_Rect& transform, size_t objectType, const char* spriteName, int health = 0);

	// returns true if the game is over
	bool UpdateGamestate(double deltaTime);

	void SpawnBullets();

	void UpdateGameObjects(double deltaTime);

	// Attempts to the save the game state.
	virtual bool Save(size_t index) override;

	// fuctions to save actual data into files
	bool SaveDataIntoFiles(const char* folderName);

	virtual bool Load(size_t index) override;

	bool LoadDataFromFiles(const char* folderName);
};

