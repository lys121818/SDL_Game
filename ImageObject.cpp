#include "ImageObject.h"
#include "SDL_image.h"
#include <iostream>

ImageObject::ImageObject(Vector2 position, int width, int height, const char* directory, const int frame)
	: m_position(position),
	  m_pSpriteName(directory),
	  m_imageComponent(directory, &m_transform)
{
	// Generate m_transform from image
	m_transform.x = (int)m_position.m_x;
	m_transform.y = (int)m_position.m_y;
	m_transform.w = width;
	m_transform.h = height;

	//DEFAULT SETTING
	m_imageComponent.AddImageFrame("Ground1", 0, 0, 128, 128);
	m_imageComponent.AddImageFrame("Ground2", 1, 0, 128, 128);
	m_imageComponent.AddImageFrame("Ground3", 2, 0, 128, 128);

	m_imageComponent.AddImageFrame("Sky", 5, 2, 128, 128);

	SetImage(frame);
}

ImageObject::~ImageObject()
{
}

void ImageObject::Update(double deltaTime)
{
}

void ImageObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_imageComponent.Render(pRenderer, pTexture);
	//SDL_RenderCopy(pRenderer, pTexture, nullptr, &m_transform);
}

void ImageObject::SetImage(const int frame)
{
	if (frame < 0)
	{
		std::cout << "Unvalid frame number \n";
		return;
	}
	else
	{
		switch (frame)
		{	
			case 0:
				m_imageComponent.SetImageFrame("Ground1");
				break;
			case 1:
				m_imageComponent.SetImageFrame("Ground2");
				break;
			case 2:
				m_imageComponent.SetImageFrame("Ground3");
				break;
			case 3:
				m_imageComponent.SetImageFrame("Sky");
				break;
		default:
			break;
		}
	}

}
