#pragma once
#include "GameObject.h"
#include "MovingComponent.h"
#include "AnimationComponent.h"
#include "SoundComponent.h"
#include <unordered_map>
#include <functional>

class BossEnemy : public GameObject
{
	enum class AnimationState
	{
		kIdle,
	} m_currentState;

private:

	// * ANIMATION
	// Name Of the Object
	const char* m_pSpriteName;

	/// * COLLIDER
	ColliderComponent m_collider;

	bool m_isRage = false;

	double m_attackTimer;

public:
	BossEnemy(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, size_t type, const char* name = "Boss");
	~BossEnemy();


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

	// Trigger Enter
	virtual void OnOverlapBegin(ColliderComponent* pCollider) override;

	virtual Status GetStatus() override { return m_status; }

	bool GetRage() { return m_isRage; }

protected:
	// AnimationComponent to play animation
	AnimationComponent m_animation;

	// player object
	GameObject* m_pTargetObject;

	// Transform of the object
	SDL_Rect m_transform;

	// callback on death
	std::unordered_map<const char*, std::function<void()>> m_mCallback;


	// * MOVEMENT
	// Component
	MovingComponent m_movingComponent;

	double m_distanceToPlayer;

	double m_timerSet;

	// Sound Component
	std::unordered_map<const char*, SoundComponent*> m_mpSounds;

	// Play sound effect of the enemy
	void PlaySounds();

	///ANIMATION EVENT
	// Play the right animation fallowing current state of gameobject
	void AnimationState();

	void AttackUpdate(double deltaTime);

	void MovementUpdate(double deltaTime);

	// gameobject's status
	Status m_status;

	void SetCallback(const char* pName, std::function<void()> callback);

	void SetRage() { m_isRage = true; }

	void SetAttackTimer(double time) { m_timerSet = time; }

	void OnCallBack(const char* name);

	void SetSpeed(const int& speed) { m_status.m_speed = speed; }

private:
	void AddSound(const char* pDir, const char* pKeyName) override;

};

