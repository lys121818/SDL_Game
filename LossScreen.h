#pragma once
#include "GameState.h"
#include "ImageObject.h"
#include "ButtonObject.h"
#include "SoundComponent.h"


class Platformer;

class LossScreen : public GameState
{
	static constexpr int s_kFirstButtonY = 200;
	static constexpr int s_kDistanceBetweenButtons = 80;

private:
	Platformer* m_pOwner;

	ImageObject m_Background;

	ImageObject m_lossImage;

	std::vector<ButtonObject*> m_vpButtons;

	SoundComponent m_pSound;

	bool isOnAction;

	// Index of selected button
	int m_keyboardButtonIndex;

public:
	LossScreen(Platformer* pOwner);
	~LossScreen();

	// Initializes the scene.
	virtual void Enter() override;

	// Update the scene
	virtual void Update(double deltaTime) override;

	// Render the scene.
	virtual void Render(SDL_Renderer* pRenderer, Textures* pTextures) override;

	// Handles the event in the context of this scene.
	virtual bool HandleEvent(SDL_Event* pEvent) override;


	// Cleans up the state
	virtual void Exit() override;

private:
	// PROCESSING EVENT
	// Every events using mouse works here
	bool ProcessMouseEvent(SDL_MouseButtonEvent* pData);
	// Every events using keyboards works here
	bool ProcessKeyboardEvent(SDL_KeyboardEvent* pData);

	void SetButtons();

	// Destory the pointers
	void Destory();

	// Changes button focus when using keyboard
	void ChangeButtonFocus(int direction);
};

