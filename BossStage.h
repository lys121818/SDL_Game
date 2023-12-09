#pragma once
#include "GameState.h"
#include "PlayerObject.h"
#include "GameObject.h"
#include "Textures.h"
#include "ImageObject.h"
#include "CollisionReferee.h"
#include "AnimationComponent.h"
#include "AiStateMachineEnemyBoss.h"
#include "TiledMap.h"
#include "InGameUI.h"

class Platformer;

class BossStage : public GameState
{
private:

	static constexpr size_t s_kMaxBulletCount = MAX_BULLET;

	// Player Information on start
	static constexpr Vector2 s_kPlayerStartingPoisition = Vector2{ PLAYER_POSITION };
	static constexpr Vector2 s_kPlayerStartingSize = Vector2{ PLAYER_SIZE_VECTOR2 };

private:

	// Game Playing Timer
	double m_CurrentTime;

	double m_loadingTime;

	// number of times the file has been overwrite
	size_t m_saves;

	// togle for pause game
	bool m_isPause;

	// file to load
	size_t m_fileIndex;

	// Pointer to the State Machine running this state.
	Platformer* m_pOwner;

	// Player Object
	PlayerObject* m_pPlayer;

	AiStateMachineEnemyBoss* m_pBossEnemy;

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

	std::vector<GameObject*> m_vpBossBullets;

	// Controlls the UI
	InGameUI* m_pInGameUI;

	InGameUI* m_pBossUI;

public:
	BossStage(Platformer* pOwner, size_t fileIndex = 0);
	~BossStage();

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

	// Every events using Window works here
	bool ProcessWindowEvent(SDL_WindowEvent* pData);

	void DestoryGameObjects();

	// Add additional gameobject to vector
	void AddGameObject(GameObject* object);

	void CreateGameObject(const SDL_Rect& transform, size_t objectType, const char* pSpriteName, int health = 0, const char* pPlayerName = "");

	// returns true if the game is over
	bool UpdateGamestate(double deltaTime);

	void SpawnBullets();

	void SpawnBossBullet(SDL_Rect spawnTransform);

	void UpdateGameObjects(double deltaTime);

	// Attempts to the save the game state.
	virtual bool Save(size_t index) override;

	// fuctions to save actual data into files
	bool SaveDataIntoFiles(const char* folderName);

	virtual bool Load(size_t index) override;

	bool LoadDataFromFiles(const char* folderName);

	void AddParticleEffect(Vector2<float> position, int size, int particleCount, float particleSpeed, float radious, bool loop, const char* textureName = nullptr, SDL_Color color = { BLACK });

};

