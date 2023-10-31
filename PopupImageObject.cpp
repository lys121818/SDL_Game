#include "PopupImageObject.h"
#include "ImageDirectory.h"
#include <iostream>

PopupImageObject::PopupImageObject(Vector2 position, const char* directory, const int index, size_t type, const char* name)
	:m_pSpriteName(directory),
	 m_imageComponent(m_pSpriteName,&m_transform),
	 m_position(position),
	 m_isPoping(true)
{
	m_status.m_type = type;
	m_status.m_name = name;

	// transform of position
	m_transform.x = m_position.m_x - m_transform.w;
	m_transform.y = m_position.m_y - m_transform.h;

	SetImage(index);
}

PopupImageObject::~PopupImageObject()
{
}

void PopupImageObject::Update(double deltaTime)
{
	if (m_isPoping)
		PopingImage(deltaTime);
}

void PopupImageObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_imageComponent.Render(pRenderer, pTexture);
}

void PopupImageObject::TryMove(Vector2 direction)
{
}

void PopupImageObject::SetPosition(Vector2 position)
{
}

void PopupImageObject::SetImage(const int index)
{
	if (index < 0)
	{
		std::cout << "[PopupImageObject] Unvalid frame number \n";
		return;
	}
	else
	{
		if (strcmp(m_pSpriteName, TESTPOPING) == 0)
		{
			m_imageComponent.SetImageFrame("Poping");
		}
	}
}

void PopupImageObject::PopingImage(double deltaTime)
{
	// TODO : Fix poping
	if (m_transform.w < s_kMaxWidth || m_transform.h < s_kMaxHeight)
	{
		int deltaW = deltaTime * s_kMaxWidth;
		int deltaH = deltaTime * s_kMaxHeight;
		if (m_transform.w < s_kMaxWidth)
			m_transform.w += deltaW;
		if (m_transform.h < s_kMaxHeight)
			m_transform.h += deltaH;
		m_transform.x += deltaW / 2;
		m_transform.y += deltaH / 2;
	}
	else
		m_isPoping = false;

}

