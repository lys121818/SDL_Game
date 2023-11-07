#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Vector2.h"

class GameObject;

class TextComponent
{
private:
	SDL_Rect m_transform;
	SDL_Rect* m_pObjectTransform;

	SDL_Texture* m_pTexture;

public:
	TextComponent(SDL_Rect* transform);
	~TextComponent();

	void Update();

	void Render(SDL_Renderer* pRenderer);

	void SetTransform(SDL_Rect transform);

	void SetText(TTF_Font* pFont, const char* pText, SDL_Color color, SDL_Renderer* pRenderer);
};

