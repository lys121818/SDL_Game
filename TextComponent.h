#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Vector2.h"

class GameObject;

class TextComponent
{
public:
	// Placement of the text according to the object
	enum class Placement
	{
		kTop,
		kMiddle,
		kBottm
	}m_textPlacemenet;

private:
	// Transform of the text
	SDL_Rect m_transform;

	// Transform of the owner object
	SDL_Rect* m_pObjectTransform;

	SDL_Texture* m_pTexture;

	// Size of the text using font
	Vector2 m_textSize;


public:
	TextComponent(SDL_Rect* transform);
	~TextComponent();

	void Update();

	void Render(SDL_Renderer* pRenderer);

	// Set Transform by 
	void SetTransform(SDL_Rect transform) { m_transform = transform; }

	// Set placement
	void SetTextPlacement(Placement placement) { m_textPlacemenet = placement; }

	// Set Text
	void SetText(TTF_Font* pFont, const char* pText, SDL_Color color, SDL_Renderer* pRenderer);

	// Draw box around the text
	void DrawTextBox(SDL_Renderer* pRenderer, SDL_Color color);
};

