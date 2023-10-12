#pragma once
#include "GameObject.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "Type.h"
#include <iostream>
class EnemyObject : public GameObject
{

	// Current Animation States
	enum AnimationState
	{
		m_idle,
		m_walk,
		m_run,
		m_jump,
		m_slide
	} m_currentState;
private:
	static constexpr double s_kSetCounter = (double)1.0;

	// Width
	static constexpr int s_kWidth = 100;
	// Height
	static constexpr int s_kHeight = 150;
	// Speed
	static constexpr int s_kSpeed = 500;
	// Name Of the Object
	const char* m_pSpriteName;

	// Current Speed of the object
	const int m_speed;

	// Current position
	Vector2 m_position;

	// Default setting is 1(right)
	// Current direction movement. -1 for left, 1for right.
	int m_directionX;

	// The direction object is facing
	bool m_isRight;



	// AnimationComponent to play animation
	AnimationComponent m_animation;

	// Collider
	ColliderComponent m_collider;

	// SDL
	// Transform of the object
	SDL_Rect m_transform;


public:
	EnemyObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, const int kspeed, Type type);
	~EnemyObject();
	// Inherited via GameObject
	void Update(double deltatime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

	// GETTER
	SDL_Rect GetTransform() override { return m_transform; }
	// Return Name of the object
	const char* GetTextureName() override { return m_pSpriteName; }

	// Return Name of the object
	virtual const char* GetName() { return "Enemy"; }

	// On Collision action
	virtual void OnCollision(ColliderComponent* pCollider);
private:
	// Play the right animation fallowing current state of gameobject
	void AnimationState();
	// Check current state before play animation.
	void CheckCurrentState();

	// Movement of the object
	bool TryMove(Vector2 deltaPosition);
};

