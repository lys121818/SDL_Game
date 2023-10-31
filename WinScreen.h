#pragma once
#include "GameState.h"
#include "ImageObject.h"
#include "ButtonObject.h"
#include "PopupImageObject.h"
class Platformer;

class WinScreen : public GameState
{
private:
	Platformer* m_pOwner;

	ImageObject m_Background;

	std::vector<ButtonObject*> m_vpButtons;

	PopupImageObject m_testPoping;

	ButtonObject* m_pHoverButton;
public:
	WinScreen(Platformer* pOwner);
	~WinScreen();

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

