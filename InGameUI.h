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
	static constexpr Vector2 s_kMaxHealthBarPosition = { HEALTHBAR_POSITION };
	static constexpr Vector2 s_kMaxHealthBarSize = { HEALTBARH_SIZE_VECTOR2 };
private:
	GameObject* m_pPlayer;

	SDL_Renderer* m_pRenderer;

	Fonts* m_pFont;

	UIObject* m_pHealthBar;

	std::vector<GameObject*> m_mpUIObjects;

public:
	InGameUI(GameObject* pPlayer, Fonts* pFonts, SDL_Renderer* pRenderer);
	~InGameUI();

	void InitUI();

	void Render(SDL_Renderer* pRenderer, Textures* pTextures) override;

	void UpdateUI() override;


private:
	void UpdateHealthbar();

	void HealthBarSettings();

	void Destory();
};

