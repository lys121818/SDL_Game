#pragma once
#include "GameSetting.h"
#include "GameObject.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "Status.h"
#include "MovingComponent.h"
#include "SoundComponent.h"
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



private:
	// * ENEMY
	// Width
	static constexpr int s_kWidth = (int)ENEMY_WIDTH;

	// Height
	static constexpr int s_kHeight = (int)ENEMY_HEIGHT;

	// Speed
	static constexpr int s_kSpeed = (int)ENEMY_SPEED;


	// Default setting is 1(right)
	// Current direction movement. -1 for left, 1for right.




	// * ANIMATION
	// Name Of the Object
	const char* m_pSpriteName;


	/// * COLLIDER
	ColliderComponent m_collider;


public:
	EnemyObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory,size_t type, const char* name = "Enemy");
	~EnemyObject();

	// Inherited via GameObject
	//void Update(double deltaTime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

	// [GETTERS]
	SDL_Rect GetTransform() override { return m_transform; }
	// Return Name of the object
	const char* GetTextureName() override { return m_pSpriteName; }

	// Return Name of the object
	virtual const char* GetName() { return "Enemy"; }

	virtual bool GetActive() override { return m_status.m_isActive; }

	// [SETTERS]
	virtual void Damaged(int amount) override { m_status.m_health -= amount; }

	virtual void SetActive(bool active) { m_status.m_isActive = active; }

	void SetTargetObject(GameObject* pTargetCollider) override { m_pTargetObject = pTargetCollider; }

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

	virtual void TryMove(Vector2<double> direction) override;

protected:
	static constexpr double s_kMinimumDistanceToHear = 300.0;

	// AnimationComponent to play animation
	AnimationComponent m_animation;

	// player object
	GameObject* m_pTargetObject;

	// Transform of the object
	SDL_Rect m_transform;

	// * MOVEMENT
	// Component
	MovingComponent m_movingComponent;

	double m_distanceToPlayer;

	// Sound Component
	std::unordered_map<const char*, SoundComponent*> m_mpSounds;

	// Play sound effect of the enemy
	void PlaySounds();

	// Update calculate target distance
	void UpdateDistance();

	void Gravity(double deltaTime);
	///ANIMATION EVENT
	// Play the right animation fallowing current state of gameobject
	void AnimationState();

	// Check current state before play animation.
	void CheckCurrentState();

	// gameobject's status
	Status m_status;

private:

	void AddSound(const char* pDir, const char* pKeyName) override;

};

