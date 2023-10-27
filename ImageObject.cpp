#include "ImageObject.h"
#include "SDL_image.h"
#include <iostream>
#include "Type.h"


ImageObject::ImageObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, const int frame, size_t type, const char* name)
	: m_transform(transform),
	  m_pSpriteName(directory),
	  m_imageComponent(directory, &m_transform),
	  m_collider(this,m_transform,pReferee)
{
	m_status.m_type = type;
	m_status.m_name = name;

	SetImage(frame);
}

ImageObject::~ImageObject()
{
}


void ImageObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_imageComponent.Render(pRenderer, pTexture);
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
		if (strcmp(m_pSpriteName, BACKGROUND) == 0)
		{
			m_imageComponent.SetImageFrame("BackGround");
		}
		else if (strcmp(m_pSpriteName, TILES) == 0)
		{
			switch (frame)
			{	
				case 0:
				{
					m_imageComponent.SetImageFrame("Ground1");
					break;
				}
				case 1:
				{
					m_imageComponent.SetImageFrame("Ground2");
					break;
				}
				case 2:
				{
					m_imageComponent.SetImageFrame("Ground3");
					break;
				}
				case 3:
				{
					m_imageComponent.SetImageFrame("Sky");
					break;
				}
			default:
				break;
			}
		}
		else if (strcmp(m_pSpriteName, OBJECTS) == 0)
		{
			switch (frame)
			{
				case 0:
				{
					m_imageComponent.SetImageFrame("SmallBush1");
					break;
				}
				case 1:
				{
					m_imageComponent.SetImageFrame("SmallBush2");
					break;
				}
				case 2:
				{
					m_imageComponent.SetImageFrame("BigBush1");
					break;
				}
				case 3:
				{
					m_imageComponent.SetImageFrame("BigBush2");
					break;
				}
				case 4:
				{
					m_imageComponent.SetImageFrame("Tree1");
					break;
				}
				case 5:
				{
					m_imageComponent.SetImageFrame("Tree2");
					break;
				}
				case 6:
				{
					m_imageComponent.SetImageFrame("Mushroom1");
					break;
				}
				case 7:
				{
					m_imageComponent.SetImageFrame("Mushroom2");
					break;
				}
				case 8:
				{
					m_imageComponent.SetImageFrame("Box");
					break;
				}
				case 9:
				{
					m_imageComponent.SetImageFrame("Sign1");
					break;
				}
				case 10:
				{
					m_imageComponent.SetImageFrame("Sign2");
					break;
				}
				case 11:
				{
					m_imageComponent.SetImageFrame("Rock");
					break;
				}
				default:
					break;
			}
		}
	}

}
