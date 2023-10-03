#pragma once
#include "GameObject.h"
#include "AnimationComponent.h"

// GameObject implementation with animation
class AnimationObject : public GameObject
{
private:
	AnimationComponent m_animation;

public:
	AnimationObject(SDL_Renderer* pRenderer);
	~AnimationObject();

	// Inherited via GameObject
	void Update(double deltatime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;
	SDL_Rect GetTransform() override;

	AnimationComponent* GetAnimationComponent() { return &m_animation; }
};

