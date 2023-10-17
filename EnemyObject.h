#pragma once
#include "GameSetting.h"
#include "GameObject.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "Type.h"
#include "Status.h"
#include "MovingComponent.h"
#include <iostream>

class EnemyObject : public GameObject
{
private:
	// Current Animation States
	enum AnimationState
	{
		m_idle,
		m_walk,
		m_run,
		m_jump,
		m_slide
	} m_currentState;

	Status m_status;

private:
	// Width
	static constexpr int s_kWidth = (int)ENEMYWIDTH;

	// Height
	static constexpr int s_kHeight = (int)ENEMYHEIGHT;

	// Speed
	static constexpr int s_kSpeed = (int)ENEMYSPEED;

	// Name Of the Object
	const char* m_pSpriteName;

	// Default setting is 1(right)
	// Current direction movement. -1 for left, 1for right.
	int m_directionX;

	// AnimationComponent to play animation
	AnimationComponent m_animation;

	// Collider
	ColliderComponent m_collider;

	// Movement
	MovingComponent m_movingComponent;

	// SDL
	// Transform of the object
	SDL_Rect m_transform;


public:
	EnemyObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, const int kspeed, Type type);
	~EnemyObject();
	// Inherited via GameObject
	void Update(double deltaTime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

	// GETTER
	SDL_Rect GetTransform() override { return m_transform; }
	// Return Name of the object
	const char* GetTextureName() override { return m_pSpriteName; }

	// Return Name of the object
	virtual const char* GetName() { return "Enemy"; }

	// On Collision action
	virtual void OnCollision(ColliderComponent* pCollider);

	virtual void TryMove(Vector2 deltaPosition) override;

	virtual Status GetStatus() override { return m_status; }

private:
	// Play the right animation fallowing current state of gameobject
	void AnimationState();
	// Check current state before play animation.
	void CheckCurrentState();

	// Movement of the object
};

