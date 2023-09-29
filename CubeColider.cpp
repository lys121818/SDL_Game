#include "CubeColider.h"
#include <iostream>
#include "Vector2.h"

CubeColider::CubeColider(SDL_Renderer* pRenderer, Vector2 position)
	:m_position(position),
	 m_directionX(0),
	 m_directionY(0),
	 m_pTexture(nullptr)
{


	// Pipeline: image file -> SDL_Surface -> SDL_Texture

	// image file -> SDL_Surface
	SDL_Surface* pImageSurface = SDL_LoadBMP("assets/Pig.bmp");
	if (pImageSurface == nullptr)
	{
		std::cout << "Image loading failed Error: " << SDL_GetError() << std::endl;;
	}

	// SDL_Surface -> SDL_Texture
	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);
	if (pImageSurface == nullptr)
	{
		std::cout << "Texture loading failed Error: " << SDL_GetError() << std::endl;;
	}

	m_transform.x = (int)m_position.m_x;
	m_transform.y = (int)m_position.m_y;
	m_transform.w = s_kWidth;
	m_transform.h = s_kHeight;

	// Free surface from memory as it's no longer needed.
	SDL_FreeSurface(pImageSurface);
}

CubeColider::~CubeColider()
{
	// Destroy the texture to free it from memory.
	SDL_DestroyTexture(m_pTexture);
}

void CubeColider::Update(double deltaTime)
{
	// Move Vertical
	double deltaPositionX = m_Speed * deltaTime;
	m_position.m_x += deltaPositionX * m_directionX;
	m_transform.x = (int)m_position.m_x;

	// Move Horizontal
	double deltaPositionY = m_Speed * deltaTime;
	m_position.m_y += deltaPositionY * m_directionY;
	m_transform.y = (int)m_position.m_y;

}

void CubeColider::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_transform);
}

// Move the object
void CubeColider::SetPosition(Vector2 position)
{
	m_position.m_x = position.m_x;
	m_position.m_y = position.m_y;
}
