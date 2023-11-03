#pragma once
#include <SDL.h>
#include <unordered_map>
#include "ImageComponent.h"
#include "UIObject.h"

// UI controller handles UI of the Game
class GameState;
class GameObject;
class Textures;

class UIController
{
	static constexpr Vector2 s_kMaxHealthBarPosition = { 50, 50 };
	static constexpr Vector2 s_kMaxHealthBarSize = { 200, 50 };
private:
	GameState* m_pOwner;

	GameObject* m_pPlayer;

	UIObject* m_pHealthBar;

	std::vector<UIObject*> m_mpUIObjects;

public:
	UIController(GameState* pOwner, GameObject* pPlayer);
	~UIController();

	void InitUI();

	void Update();

	void Render(SDL_Renderer* pRenderer, Textures* pTextures);

	void AddUIImage(SDL_Rect* pTransform, const char* spriteName);

	void UpdateHealthUI();

	void HealthBarSettings();
};

