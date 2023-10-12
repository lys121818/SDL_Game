#include "ImageObject.h"
#include "SDL_image.h"
#include <iostream>

ImageObject::ImageObject(Vector2 position, int width, int height, const char* directory)
	: m_position(position),
	  m_pSpriteName(directory),
	  m_imageComponent(directory, &m_transform)
{
	// Generate m_transform from image
	m_transform.x = (int)m_position.m_x;
	m_transform.y = (int)m_position.m_y;
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
	m_imageComponent.Render(pRenderer, pTexture);
	//SDL_RenderCopy(pRenderer, pTexture, nullptr, &m_transform);
}
