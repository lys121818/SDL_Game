#pragma once
#include <SDL.h>
#include "UIInterface.h"
#include <unordered_map>
#include "ImageComponent.h"
#include "UIObject.h"
#include "Fonts.h"
#include "GameState.h"
#include <SDL_ttf.h>

// UI controller handles UI of the Game
class GameState;
class GameObject;
class ButtonObject;
class Textures;

class InGameUI : UIInterface
{
private:

	GameObject* m_pGameObject;

	SDL_Renderer* m_pRenderer;

	GameState* m_pOwner;

	Fonts* m_pFont;

	UIObject* m_pHealthBar;

	SDL_Rect m_menuBox;

	std::vector<GameObject*> m_vpUIObjects;

	std::vector<ButtonObject*> m_vpButtons;

	bool m_isPause;

	int m_keyboardButtonIndex;

public:
	InGameUI(GameState* pOwner, GameObject* pObject, Fonts* pFonts, SDL_Renderer* pRenderer);
	~InGameUI();

	void InitUI();

	void Render(SDL_Renderer* pRenderer, Textures* pTextures) override;

	void UpdateUI() override;

	virtual void UpdateUI(double deltaTime) override;

	void AddHealthBar(Vector2<double> position, Vector2<double> size);

	void SetGameObject(GameObject* pObject) { m_pGameObject = pObject; }

	void TogglePause() { m_isPause = !m_isPause; }

	bool HandleEvent(SDL_Event* pEvent) override;
private:
	void UpdateHealthbar();

	void SetPauseMenu();

	void UpdatePauseMenu(double deltaTime);

	// Changes button focus when using keyboard
	void ChangeButtonFocus(int direction);

	void Destory();
};

