#pragma once
#include <vector>
#include "GameState.h"
#include "GameObject.h"
#include "TextObject.h"
#include "ImageObject.h"

class Platformer;

class CreditsScene : public GameState
{
	static constexpr Vector2 s_kStartingPosition = Vector2{ (WINDOWWIDTH / 2), (WINDOWHEIGHT + 100) };
private:
	Platformer* m_pOwner;

	// Credit text
	std::vector<TextObject*> m_vpCreditsText;
	
	// Skip Info Text
	TextObject m_skipInfo_1;
	TextObject m_skipInfo_2;

	// Image for background
	ImageObject m_background_1;
	ImageObject m_background_2;
public:
	CreditsScene(Platformer* pOwner);
	~CreditsScene();

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
	void InitCreditScene();

	// PROCESSING EVENT
	// Every events using keyboards works here
	bool ProcessKeyboardEvent(SDL_KeyboardEvent* pData);

	void UpdateBackgrounds(double deltaTime);

	void Destory();
};

