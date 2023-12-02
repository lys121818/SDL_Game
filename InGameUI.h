#pragma once
#include <SDL.h>
#include "UIInterface.h"
#include <unordered_map>
#include "ImageComponent.h"
#include "UIObject.h"
#include "Fonts.h"
#include <SDL_ttf.h>

// UI controller handles UI of the Game
class GameState;
class GameObject;
class Textures;

class InGameUI : UIInterface
{
private:

	GameObject* m_pGameObject;

	SDL_Renderer* m_pRenderer;

	Fonts* m_pFont;

	UIObject* m_pHealthBar;

	std::vector<GameObject*> m_mpUIObjects;

public:
	InGameUI(GameObject* pObject, Fonts* pFonts, SDL_Renderer* pRenderer);
	~InGameUI();

	void InitUI();

	void Render(SDL_Renderer* pRenderer, Textures* pTextures) override;

	void UpdateUI() override;

	void AddHealthBar(Vector2<double> position, Vector2<double> size);

	void SetGameObject(GameObject* pObject) { m_pGameObject = pObject; }
private:
	void UpdateHealthbar();



	void Destory();
};

