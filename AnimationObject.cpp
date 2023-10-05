#include "AnimationObject.h"

AnimationObject::AnimationObject(SDL_Renderer* pRenderer, Vector2 position, int width, int height)
	: m_animation("assets/Pumpkin.png",12,100,190,pRenderer,&m_transform),
	  m_position(position)
{
	// Add the animation
	// Play the initiali animation
	
	m_transform.x = (int)m_position.m_x;
	m_transform.y = (int)m_position.m_y;
	m_transform.w = width;
	m_transform.h = height;
}

AnimationObject::~AnimationObject()
{
}

void AnimationObject::Update(double deltatime)
{
	m_animation.Update(deltatime);

	// other behavior goes here
}

void AnimationObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_animation.Render(pRenderer);
}
