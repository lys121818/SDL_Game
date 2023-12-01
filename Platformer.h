#pragma once
#include "GameStateMachine.h"
#include "BackgroundMusicComponent.h"
#include <SDL_ttf.h>

class GameDemo;
class GameState;


class Platformer : public GameStateMachine
{
public:
	enum class SceneName
	{
		kMainMenu = 0,
		kGamePlay,
		kVictory,
		kLoss,
		kCredit,
		kBoss
	}m_currentScene;
private:
	// GameDemo object that is running this state machine.
	GameDemo* m_pOwner;

	// Currently active scene.
	GameState* m_pCurrentState;

	// Any State waiting to be loaded on the next frame.
	GameState* m_pNextState;

	BackgroundMusicComponent m_musicComponent;

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

	void SetBGMusic(const char* pFirstMusic, const char* pSecondMusic = nullptr) override;

	void ToggleMusic();
private:
	// delete all the pointers
	void Destory();
};

