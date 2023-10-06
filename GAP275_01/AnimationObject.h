#pragma once
#include "GameObject.h"
#include "AnimationComponent.h"

// GameObject implementation with animation
class AnimationObject : public GameObject
{
private:
	AnimationComponent m_animation;
	SDL_Rect m_transform;
	Vector2 m_position;
public:
	AnimationObject(SDL_Renderer* pRenderer, Vector2 position, int width, int height);
	~AnimationObject();

	// Inherited via GameObject
	void Update(double deltatime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;
	SDL_Rect GetTransform() override { return m_transform; }

	AnimationComponent* GetAnimationComponent() { return &m_animation; }
};

