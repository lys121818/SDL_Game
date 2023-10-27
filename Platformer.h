#pragma once
#include "GameStateMachine.h"

class GameDemo;
class GameState;


class Platformer : public GameStateMachine
{
public:
	enum class SceneName
	{
		m_MainMenu = 0,
		m_GamePlay,
		m_Victory,
		m_Dead
	}m_currentScene;
private:
	// GameDemo object that is running this state machine.
	GameDemo* m_pOwner;

	// Currently active scene.
	GameState* m_pCurrentState;

	// Any State waiting to be loaded on the next frame.
	GameState* m_pNextState;



public:
	Platformer(GameDemo* pOwner);
	~Platformer();

	GameDemo* GetGame() { return m_pOwner; }

	// Inherited via GameStateMachine
	// Update the current game state.
	void UpdateCurrentState(double deltaTime) override;

	// Render the current state.
	void RenderCurrentState(SDL_Renderer* pRenderer, Textures* pTextures) override;

	// Handle the given event within the current state.
	bool HandleEvent(SDL_Event* pEvent) override;

	// Exit the current state and enters new state.
	void ChangeState(GameState* pNewState) override;

	// Load the given scene.
	void LoadScene(SceneName scene);

	size_t GetScene() override { return (size_t)m_currentScene; }
private:
	// delete all the pointers
	void Destory();
};

