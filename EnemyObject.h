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

	// gameobject's status
	Status m_status;

private:
	// * ENEMY
	// Width
	static constexpr int s_kWidth = (int)ENEMYWIDTH;

	// Height
	static constexpr int s_kHeight = (int)ENEMYHEIGHT;

	// Speed
	static constexpr int s_kSpeed = (int)ENEMYSPEED;

	// * MOVEMENT
	// Component
	MovingComponent m_movingComponent;

	// Default setting is 1(right)
	// Current direction movement. -1 for left, 1for right.
	int m_directionX;

	// Transform of the object
	SDL_Rect m_transform;


	// * ANIMATION
	// Name Of the Object
	const char* m_pSpriteName;

	// AnimationComponent to play animation
	AnimationComponent m_animation;


	/// * COLLIDER
	ColliderComponent m_collider;

	ColliderComponent* m_otherCollider;



public:
	EnemyObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, const int kspeed, Type type, const char* name = "Enemy");
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

	// Move to the direction
	virtual void TryMove(Vector2 deltaPosition) override {};

	// Get this Object's Status
	virtual Status GetStatus() override { return m_status; }

private:
	///ANIMATION EVENT
	// Play the right animation fallowing current state of gameobject
	void AnimationState();
	// Check current state before play animation.
	void CheckCurrentState();


	///GAME EVENT
	// Event happen with Collide
	void ColliderEvent();

	// Event happen with Trigger
	void CollisionEnter();
	void CollisionEvent();
	void CollisionExit();

	void Gravity(double deltaTime);
};

