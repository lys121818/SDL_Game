#pragma once
#include <vector>
#include "GameState.h"
#include "ButtonObject.h"
#include "ImageObject.h"
#include "Textures.h"
#include "SDL_ttf.h"


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
	bool ProcessMouseEvent(SDL_MouseButtonEvent* pData);

	void SetButtons();

	// Updates for background
	void BackgroundUpdates(double deltaTime);

	// Destory the pointers
	void Destory();
};

