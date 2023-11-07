#include "TextComponent.h"
#include <assert.h>
#include <iostream>

TextComponent::TextComponent(SDL_Rect* transform)
	:
	m_pObjectTransform(transform),
	m_transform(SDL_Rect{0,0,0,0}),
	m_pTexture(nullptr)
{
}

TextComponent::~TextComponent()
{
	SDL_DestroyTexture(m_pTexture);
}

void TextComponent::Update()
{
	m_transform.x = m_pObjectTransform->x - (m_transform.w / 2);
	m_transform.y = m_pObjectTransform->y - (m_transform.h / 2);
}

void TextComponent::Render(SDL_Renderer* pRenderer)
{
	if (m_pTexture == nullptr)
	{
		std::cout << "[TextComponent]The Texture hasn't been set up";
		return;
	}

	SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_transform);
}

void TextComponent::SetTransform(SDL_Rect transform)
{
	m_transform = transform;
}

void TextComponent::SetText(TTF_Font* pFont, const char* pText, SDL_Color color, SDL_Renderer* pRenderer)
{
	assert(pFont);

	SDL_Surface* pTextSurface = TTF_RenderText_Solid(pFont, pText, color);
	if (pTextSurface == nullptr)
	{
		std::cout << "[TextComponent] Text loading failed Error: " << SDL_GetError() << std::endl;
	}

	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pTextSurface);

	// Error when it fails to load the texture
	if (m_pTexture == nullptr)
	{
		std::cout << "[TextComponent] Texture loading failed Error: " << SDL_GetError();
	}
	
	// Setting text to the middle of object
	if (pTextSurface != nullptr)
	{
		m_transform.w = pTextSurface->w;
		m_transform.h = pTextSurface->h;

		Vector2 objectMiddlePosition{	m_pObjectTransform->x + (m_pObjectTransform->w / 2) ,
										m_pObjectTransform->y + (m_pObjectTransform->h / 2) };

		m_transform.x = objectMiddlePosition.m_x - (pTextSurface->w / 2);
		m_transform.y = objectMiddlePosition.m_y - (pTextSurface->h / 2);
	}


	SDL_FreeSurface(pTextSurface);
}

