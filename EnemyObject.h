#pragma once
#include "GameSetting.h"
#include "GameObject.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "Status.h"
#include "MovingComponent.h"
#include <iostream>

class EnemyObject : public GameObject
{
private:

	// Current Animation States
	enum class AnimationState
	{
		kIdle,
		kWalk,
		kRun,
		kJump,
		kSlide
	} m_currentState;

	// gameobject's status
	Status m_status;

private:
	// * ENEMY
	// Width
	static constexpr int s_kWidth = (int)ENEMY_WIDTH;

	// Height
	static constexpr int s_kHeight = (int)ENEMY_HEIGHT;

	// Speed
	static constexpr int s_kSpeed = (int)ENEMY_SPEED;

	// * MOVEMENT
	// Component
	MovingComponent m_movingComponent;

	// Default setting is 1(right)
	// Current direction movement. -1 for left, 1for right.

	// Transform of the object
	SDL_Rect m_transform;


	// * ANIMATION
	// Name Of the Object
	const char* m_pSpriteName;

	// AnimationComponent to play animation
	AnimationComponent m_animation;


	/// * COLLIDER
	ColliderComponent m_collider;


public:
	EnemyObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory,size_t type, const char* name = "Enemy");
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

	// Trigger Enter
	virtual void OnOverlapBegin(ColliderComponent* pCollider) override;

	// Trigger Update
	virtual void OnOverlapUpdate() override;

	// Trigger Exit
	virtual void OnOverlapEnd() override;

	// Get this Object's Status
	virtual Status GetStatus() override { return m_status; }

private:
	///ANIMATION EVENT
	// Play the right animation fallowing current state of gameobject
	void AnimationState();
	// Check current state before play animation.
	void CheckCurrentState();

	void Gravity(double deltaTime);
};

