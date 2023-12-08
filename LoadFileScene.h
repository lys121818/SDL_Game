#pragma once
#include "GameState.h"
#include "ImageObject.h"
#include "ButtonObject.h"

class Platformer;

class LoadFileScene : public GameState
{
private:
	Platformer* m_pOwner;

	ImageObject m_background_1;
	ImageObject m_background_2;

	// Vectors of buttons
	std::vector<ButtonObject*> m_vpButtons;

	// Index of selected button
	int m_keyboardButtonIndex;

	size_t loadIndex;
public:
	LoadFileScene(Platformer* pOwner);
	~LoadFileScene();

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
	// PROCESSING EVENT
	// Every events using mouse works here
	bool ProcessMouseEvent(SDL_MouseButtonEvent* pData);
	// Every events using keyboards works here
	bool ProcessKeyboardEvent(SDL_KeyboardEvent* pData);

	// Button Settings
	void SetButtons();

	// Updates for background
	void BackgroundUpdates(double deltaTime);

	void ButtonUpdates(double deltaTime);

	// Destory the pointers
	void Destory();

	// Changes button focus when using keyboard
	void ChangeButtonFocus(int direction);

	void SetSceneOnLoad(size_t level, size_t fileNumber);

	// Load Data
	size_t LoadSaveFile(size_t index);
};

