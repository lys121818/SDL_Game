#include "TextObject.h"

TextObject::TextObject(Vector2<double> position, TTF_Font* pFont, SDL_Color color, SDL_Renderer* pRenderer)
	:
	m_pFont(pFont),
	m_color(color),
	m_pRenderer(pRenderer),
	m_transform(SDL_Rect{ (int)position.m_x,(int)position.m_y,0,0 }),
	m_textComponent(&m_transform),
	m_movingComponent(&m_transform,position),
	m_imageAction(&m_transform)
{
	m_status.m_direction = { ZERO };
	m_status.m_speed = s_kSpeed;
}

TextObject::~TextObject()
{

}

void TextObject::Update(double deltaTime)
{
	if (m_status.m_speed != 0 || m_status.m_direction != Vector2{ ZERO })
	{
		m_movingComponent.TryMove(deltaTime, m_status.m_speed, m_status.m_direction);
		m_textComponent.Update();
	}
}

void TextObject::Render(SDL_Renderer* pRenderer)
{
	m_textComponent.Render(pRenderer);
}

void TextObject::TryMove(Vector2<int> direction)
{
	m_status.m_direction = direction;
}

void TextObject::SetText(const char* pText)
{
	m_textComponent.SetText(m_pFont, pText, m_color, m_pRenderer);
}

