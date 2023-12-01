#include "TextComponent.h"
#include "Defines.h"
#include <assert.h>
#include <iostream>

TextComponent::TextComponent(SDL_Rect* transform)
	:
	m_pObjectTransform(transform),
	m_transform(SDL_Rect{0,0,0,0}),
	m_pTexture(nullptr),
	m_textSize(Vector2<int>(0,0)),
	m_textPlacemenet(Placement::kMiddle)
{
}

TextComponent::~TextComponent()
{
	SDL_DestroyTexture(m_pTexture);
}

void TextComponent::Update()
{
	// [Position Placement to render Text]
	switch (m_textPlacemenet)
	{
		// Top middle of the object
		case TextComponent::Placement::kTop:
		{
			m_transform.x = (int)(m_pObjectTransform->x + (m_pObjectTransform->w / 2) - (m_textSize.m_x / 2));
			m_transform.y = (int)(m_pObjectTransform->y - m_textSize.m_y);

			break;
		}

		// Center of the object
		case TextComponent::Placement::kMiddle:
		{
			// Set text to the middle of object
			m_transform.x = (int)(m_pObjectTransform->x + (m_pObjectTransform->w / 2) - (m_textSize.m_x / 2));
			m_transform.y = (int)(m_pObjectTransform->y + (m_pObjectTransform->h / 2) - (m_textSize.m_y / 2));
			break;
		}

		// Bottom middle of the object
		case TextComponent::Placement::kBottm:
		{
			m_transform.x = (int)(m_pObjectTransform->x + (m_pObjectTransform->w / 2) - (m_textSize.m_x / 2));
			m_transform.y = (int)(m_pObjectTransform->y + (m_pObjectTransform->h));

			break;
		}
	default:
		break;
	}
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

void TextComponent::SetText(TTF_Font* pFont, const char* pText, SDL_Color color, SDL_Renderer* pRenderer)
{
	assert(pFont);

	SDL_Surface* pTextSurface = TTF_RenderText_Solid(pFont, pText, color);
	if (pTextSurface == nullptr)
	{
		std::cout << "[TextComponent] Text loading failed Error: " << SDL_GetError() << std::endl;
	}

	assert(pTextSurface);

	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pTextSurface);

	// Error when it fails to load the texture and return
	if (m_pTexture == nullptr)
	{
		std::cout << "[TextComponent] Texture loading failed Error: " << SDL_GetError();

		// free surface before it returns
		SDL_FreeSurface(pTextSurface);
		return;
	}
	
	m_textSize.m_x = pTextSurface->w;
	m_textSize.m_y = pTextSurface->h;

	// Setting text to the middle of object
	if (pTextSurface != nullptr)
	{
		m_transform.w = pTextSurface->w;
		m_transform.h = pTextSurface->h;

		Vector2 objectMiddlePosition{	(double)m_pObjectTransform->x + (m_pObjectTransform->w / 2) ,
										(double)m_pObjectTransform->y + (m_pObjectTransform->h / 2) };

		m_transform.x = (int)(objectMiddlePosition.m_x - (pTextSurface->w / 2));
		m_transform.y = (int)(objectMiddlePosition.m_y - (pTextSurface->h / 2));
	}


	SDL_FreeSurface(pTextSurface);
}

void TextComponent::DrawTextBox(SDL_Renderer* pRenderer, SDL_Color color)
{
	SDL_SetRenderDrawColor(pRenderer, color.r,color.g,color.b,color.a);
	SDL_RenderFillRect(pRenderer, &m_transform);
}

