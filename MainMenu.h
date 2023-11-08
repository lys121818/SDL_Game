#pragma once
#include <vector>
#include "GameState.h"
#include "ButtonObject.h"
#include "ImageObject.h"
#include "Textures.h"
#include <string>
#include "SDL_ttf.h"
#include "TextObject.h"
#include "MainMenuUI.h"
#include <fstream>

//==================================================================================================//
/// MAIN MENU
/// Game state representing the main menu.
//==================================================================================================//

class Platformer; 

class MainMenu : public GameState
{
private:
	// Pointer to the State Machine running this state.
	Platformer* m_pOwner;

	ImageObject m_background_1;
	ImageObject m_background_2;

	// Vectors of buttons
	std::vector<ButtonObject*> m_vpButtons;

	ButtonObject* m_pHoverButton;

	// Index of selected button
	int m_keyboardButtonIndex;

	MainMenuUI* m_pMainMenuUI;

	bool isSetUI;

public:
	MainMenu(Platformer* pOwner);
	~MainMenu();
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
	// PROCESSING EVENT
	// Every events using mouse works here
	bool ProcessMouseEvent(SDL_MouseButtonEvent* pData);
	// Every events using keyboards works here
	bool ProcessKeyboardEvent(SDL_KeyboardEvent* pData);

	void SetButtons();

	void SetUI();

	// Updates for background
	void BackgroundUpdates(double deltaTime);

	// Destory the pointers
	void Destory();

	// Changes button focus when using keyboard
	void ChangeButtonFocus(int direction);
};

