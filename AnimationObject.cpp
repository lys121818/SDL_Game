#include "AnimationObject.h"

AnimationObject::AnimationObject(SDL_Renderer* pRenderer)
	: m_animation("assets/Sprite1.png",12,100,200,7,pRenderer)
{
	// Add the animation
	m_animation.AddAnimationSequence("idle", 0, 0);
	m_animation.AddAnimationSequence("run", 1, 25);
	m_animation.AddAnimationSequence("skid", 4, 4);
	m_animation.AddAnimationSequence("jump", 5, 5);

	// Play the initiali animation
	m_animation.PlayAnimation("idle");
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

SDL_Rect AnimationObject::GetTransform()
{
	return SDL_Rect();
}
