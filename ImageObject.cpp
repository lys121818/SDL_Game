#include "ImageObject.h"
#include "SDL_image.h"
#include <iostream>

ImageObject::ImageObject(Vector2 position, int width, int height, const char* directory)
	: m_position(position),
	  m_pName(directory)
{
	// Generate m_transform from image
	m_transform.x = m_position.m_x;
	m_transform.y = m_position.m_y;
	m_transform.w = width;
	m_transform.h = height;
}

ImageObject::~ImageObject()
{
}

void ImageObject::Update(double deltatime)
{
}

void ImageObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{

	SDL_RenderCopy(pRenderer, pTexture, nullptr, &m_transform);
}
