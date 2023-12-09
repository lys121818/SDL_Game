#include "BossEnemy.h"
#include <assert.h>
#include <iostream>
#include "RNG.h"

BossEnemy::BossEnemy(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, size_t type, const char* name)
	:
	m_transform(transform),
	m_animation(directory, 6, &m_transform),
	m_collider(this, transform, pReferee),
	m_pSpriteName(directory),
	m_movingComponent(&m_transform, Vector2{ (double)transform.x,(double)transform.y }, & m_collider),
	m_attackTimer(BOSS_DEFAULT_TIMER)
{
	/// STATUS
	m_status.m_name = name;
	m_status.m_type = type;
	m_status.m_health = BOSS_MAX_HEALTH;
	m_status.m_maxHealth = BOSS_MAX_HEALTH;
	m_status.m_speed = 0;
	m_status.m_direction = Vector2<double>{ UP };

	m_animation.AddAnimationSequence("idle", Vector2<int>{200, 200}, Vector2<int>{10, 0}, 20);

	// Dead animation
	m_animation.SetCallback([this]() {
		m_status.m_isActive = false;
		});

	// Animation Default setting
	m_currentState = AnimationState::kIdle;


}

BossEnemy::~BossEnemy()
{
	for (auto& element : m_mpSounds)
	{
		delete element.second;
	}
}

void BossEnemy::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_collider.DrawColliderBox(pRenderer);

	m_animation.Render(pRenderer, pTexture, m_status.m_isRight);
}

void BossEnemy::OnOverlapBegin(ColliderComponent* pCollider)
{
	Status targetStaus = pCollider->GetOwner()->GetStatus();
	assert(targetStaus.m_type >= COLLISION_INDEX);

	switch (targetStaus.m_type)
	{
	default:
		break;
	}

}

void BossEnemy::AnimationState()
{
	// Check current state before play the animation
	//CheckCurrentState();

	// Play animation according to m_crrentState
	switch (m_currentState)
	{
		case BossEnemy::AnimationState::kIdle:
		{
			m_animation.PlayAnimation("idle");
			break;
		}
	default:
		break;
	}

}

void BossEnemy::AttackUpdate(double deltaTime)
{
	m_attackTimer -= deltaTime;
	if (m_attackTimer < 0.0)
	{
		m_attackTimer = m_timerSet;
		m_mCallback["Attack"]();
	}
}

void BossEnemy::MovementUpdate(double deltaTime)
{
	m_movingComponent.TryMove(deltaTime, m_status.m_speed, m_status.m_direction);
}

void BossEnemy::SetCallback(const char* pName, std::function<void()> callback)
{
	std::pair<const char*, std::function<void()>> pair;

	pair.first = pName;

	pair.second = callback;

	m_mCallback.insert(pair);
}

void BossEnemy::OnCallBack(const char* name)
{
	if (m_mCallback[name])
		m_mCallback[name]();

}

void BossEnemy::AddSound(const char* pDir, const char* pKeyName)
{
	std::pair<const char*, SoundComponent*> pair;

	pair.second = new SoundComponent();

	pair.first = pKeyName;
	pair.second->AddSoundChunk(pDir);

	m_mpSounds.insert(pair);
}

