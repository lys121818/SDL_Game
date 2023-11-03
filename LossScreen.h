#pragma once
#include "GameState.h"
#include "ImageObject.h"
#include "ButtonObject.h"


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

	ButtonObject* m_pHoverButton;

	bool isOnAction;
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
	bool ProcessMouseEvent(SDL_MouseButtonEvent* pData);

	void SetButtons();

	// Destory the pointers
	void Destory();
};

