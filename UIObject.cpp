#include "UIObject.h"
#include "ImageDirectory.h"
#include <iostream>

UIObject::UIObject(SDL_Rect transform, const char* spriteName, size_t index)
	:
	m_transform(transform),
	m_image(spriteName,&m_transform),
	m_pSpriteName(spriteName)

{
	SetUIImage((int)index);
}

UIObject::~UIObject()
{
}


void UIObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
    m_image.Render(pRenderer, pTexture);
}

void UIObject::SetUIImage(const int index)
{
	if (index < 0)
	{
		std::cout << "[ImageObject] Unvalid frame number \n";
		return;
	}
	else
	{
		if (strcmp(m_pSpriteName, HEALTHUI) == 0)
		{
			switch (index)
			{
				case 0:
				{
					m_image.SetImageFrame("Bar");
					m_status.m_name = "Bar";
					break;
				}
				case 1:
				{
					m_image.SetImageFrame("Health_Long");
					m_status.m_name = "Health_Long";
					break;
				}
				case 2:
				{
					m_image.SetImageFrame("BlankHealth");
					m_status.m_name = "BlankHealth";
					break;
				}
				case 3:
				{
					m_image.SetImageFrame("HealthSymbol");
					m_status.m_name = "HealthSymbol";
					break;
				}
				case 4:
				{
					m_image.SetImageFrame("Health_Short");
					m_status.m_name = "Health_Short";
					break;
				}
			default:
				break;
			}
		}
	}
}
