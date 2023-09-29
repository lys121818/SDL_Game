#include "ImageObject.h"
#include "SDL_image.h"
#include <iostream>

ImageObject::ImageObject(SDL_Renderer* pRenderer, Vector2 position, const char* directory)
	:m_pTexture(nullptr),
	 m_position(position)
{
	// Load image
	SDL_Surface* pImageSurface = IMG_Load(directory);
	if (pImageSurface == nullptr)
	{
		std::cout << "Image loading failed Error: " << SDL_GetError() << std::endl;
	}

	// Generate m_transform from image
	m_transform.x = m_position.m_x;
	m_transform.y = m_position.m_y;
	m_transform.w = 200;
	m_transform.h = 200;
	// SDL_Surface -> SDL_Texture
	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);
	if (pImageSurface == nullptr)
	{
		std::cout << "Texture loading failed Error: " << SDL_GetError();
	}

	// Free surface from memory as it's no longer needed.
	SDL_FreeSurface(pImageSurface);
}

ImageObject::~ImageObject()
{
	// Destroy the texture to free it from memory.
	SDL_DestroyTexture(m_pTexture);
}

void ImageObject::Update(double deltatime)
{
}

void ImageObject::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_transform);
}
