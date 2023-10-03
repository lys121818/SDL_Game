#include "CubeColider.h"
#include <iostream>
#include "Vector2.h"

CubeColider::CubeColider(Vector2 position, const char* directory)
	:m_position(position),
	 m_directionX(0),
	 m_directionY(0),
	 m_pTexture(nullptr),
	 m_pName(directory)
{

	m_transform.x = (int)m_position.m_x;
	m_transform.y = (int)m_position.m_y;
	m_transform.w = s_kWidth;
	m_transform.h = s_kHeight;

}

CubeColider::~CubeColider()
{
}

void CubeColider::Update(double deltatime)
{
	// Move Vertical
	double deltaPositionX = m_Speed * deltatime;
	m_position.m_x += deltaPositionX * m_directionX;
	m_transform.x = (int)m_position.m_x;

	// Move Horizontal
	double deltaPositionY = m_Speed * deltatime;
	m_position.m_y += deltaPositionY * m_directionY;
	m_transform.y = (int)m_position.m_y;

}

void CubeColider::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	SDL_RenderCopy(pRenderer, pTexture, nullptr, &m_transform);
}

// Move the object
void CubeColider::SetPosition(Vector2 position)
{
	m_position.m_x = position.m_x;
	m_position.m_y = position.m_y;
}
