#include "Bullet.h"

Bullet::Bullet(Vector2 position, const char* directory)
    : m_position(position),
      m_pSpriteName(directory)
{
    m_transform.w = s_kWidth;
    m_transform.h = s_kHeight;
    m_transform.x = (int)m_position.m_x;
    m_transform.y = (int)m_position.m_y;

}

Bullet::~Bullet()
{
}

void Bullet::Update(double deltatime)
{
    // bullet will always move toward up
    double deltaPosition = s_kSpeed * deltatime;
    m_position.m_y += deltaPosition * -1;
    m_transform.y = (int)m_position.m_y;

}

void Bullet::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
    SDL_RenderCopy(pRenderer, pTexture, nullptr, &m_transform);
}