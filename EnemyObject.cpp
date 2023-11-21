#include "EnemyObject.h"
#include <iostream>
#include <assert.h>
#include <math.h>
#include "GameSetting.h"
#include "ObjectType.h"
#include "SoundDirectory.h"

EnemyObject::EnemyObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, size_t type, const char* name)
    : 
	m_transform(transform),
	m_animation(directory, 6, 200, 300, &m_transform),
	m_collider(this, transform,pReferee),
	m_pSpriteName(directory),
	m_movingComponent(&m_transform, Vector2{ (double)transform.x,(double)transform.y },&m_collider)
{
	
	/// STATUS
	m_status.m_name = name;
	m_status.m_type = type;
	m_status.m_health = 100;
	m_status.m_speed = s_kSpeed;
	m_status.m_direction = Vector2{ RIGHT };
	m_status.m_isGrounded = false;
	m_status.m_isOnCollision = false;
	m_status.m_pTargetCollider = nullptr;
	m_status.m_isRight = false;

	/// TRANSFORM
	// Size
	m_transform.w = s_kWidth;
	m_transform.h = s_kHeight;

	/// ANIMATION
	// Animation sequence
	m_animation.AddAnimationSequence("idle", 0, 14);
	m_animation.AddAnimationSequence("walk", 20, 29);
	m_animation.AddAnimationSequence("attack", 30, 37);

	// Animation Default setting
	m_currentState = AnimationState::kIdle;

	AddSound(ZOMBIE1_SOUND, "Zombie_1");

}

EnemyObject::~EnemyObject()
{
	for (auto& element : m_mpSounds)
	{
		delete element.second;
	}
}

/*-----------
//  PUBLIC  //
-----------*/

void EnemyObject::Update(double deltaTime)
{
	Gravity(deltaTime);

	// Play Sounds according to object actions
	UpdateDistance();

	// if it's moving
	if (m_status.m_speed > 0)
	{
		// Check if it's able to move
		m_movingComponent.TryMove(deltaTime, m_status.m_speed, m_status.m_direction);

	}

	if (m_transform.x > ( WINDOWWIDTH - m_transform.w )|| m_transform.x < 0)
	{
		m_status.m_direction.m_x *= -1;	// change the direction by multiply negative value
	}

	m_animation.Update(deltaTime);
	AnimationState();


}

void EnemyObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	//m_collider.DrawColliderBox(pRenderer);

	m_animation.Render(pRenderer, pTexture, m_status.m_isRight);

}

void EnemyObject::OnCollision(ColliderComponent* pCollider)
{
	Status targetStaus = pCollider->GetOwner()->GetStatus();

	if (targetStaus.m_type < COLLISION_INDEX)
	{
		switch (targetStaus.m_type)
		{
			case (size_t)ObjectType::kWall:
			{
				m_status.m_direction.m_x *= -1;	// change the direction by multiply negative value
				break;
			}
			case (size_t)ObjectType::kPlayer:
			{
				m_status.m_direction.m_x *= -1;	// change the direction by multiply negative value
				break;
			}

			case (size_t)ObjectType::kGround:
			{
				m_status.m_isGrounded = true;
				break;
			}
			default:
			break;
		}
	}

}


void EnemyObject::OnOverlapBegin(ColliderComponent* pCollider)
{
	Status targetStaus = pCollider->GetOwner()->GetStatus();
	assert(targetStaus.m_type >= COLLISION_INDEX);

	m_status.m_isOnCollision = true;

	m_status.m_pTargetCollider = pCollider;

}

void EnemyObject::OnOverlapUpdate()
{
	Status targetStaus = m_status.m_pTargetCollider->GetOwner()->GetStatus();
	assert(targetStaus.m_type >= COLLISION_INDEX);
}

void EnemyObject::OnOverlapEnd()
{
	Status targetStaus = m_status.m_pTargetCollider->GetOwner()->GetStatus();
	assert(targetStaus.m_type >= COLLISION_INDEX);

	m_status.m_pTargetCollider = nullptr;
	m_status.m_isOnCollision = false;
}

// Play the right animation fallowing current state of gameobject
void EnemyObject::AnimationState()
{
	// Check current state before play the animation
	CheckCurrentState();

	// Play animation according to m_crrentState
	switch (m_currentState)
	{
		case EnemyObject::AnimationState::kIdle:
		{
			m_animation.PlayAnimation("idle");
			break;
		}
		case EnemyObject::AnimationState::kWalk:
		{
			m_animation.PlayAnimation("walk");
			break;
		}
	default:
		break;
	}

}

// Check current state before play animation.
void EnemyObject::CheckCurrentState()
{

	// change direction of gameobject is facing 
	if (m_status.m_direction.m_x > 0)
	{
		m_status.m_isRight = true;
	}
	else if (m_status.m_direction.m_x < 0)
	{
		m_status.m_isRight = false;
	}
	if (m_status.m_speed > 0)	// if player is moving x direction
	{

		m_currentState = AnimationState::kWalk;
	}
	else
		m_currentState = AnimationState::kIdle;

}

void EnemyObject::Gravity(double deltaTime)
{
	m_movingComponent.TryMove(deltaTime, GRAVITY_POWER, Vector2{ 0,1 });
}

void EnemyObject::PlaySounds()
{
	// find distance to player
	if (m_mpSounds["Zombie_1"]->GetActiveChannel() == -1)
	{
		// play in loop
		m_mpSounds["Zombie_1"]->PlayChunk(-1);
	}

}

void EnemyObject::UpdateDistance()
{
	Vector2 targetPosition;
	Vector2 thisPosition;

	targetPosition.m_x = (double)m_pTargetObject->GetTransform().x;
	targetPosition.m_y = (double)m_pTargetObject->GetTransform().y;

	thisPosition.m_x = (double)m_transform.x;
	thisPosition.m_y = (double)m_transform.y;

	m_distanceToPlayer = Vector2::Distance(targetPosition, thisPosition);

	// If Player is in distance to hear the sound
	if (m_distanceToPlayer < s_kMinimumDistanceToHear)
	{
		// Play Sounds if sounds is not playing
		PlaySounds();

		// Set volume by distance to the target
		int volumeSize = (int)((1.0 - (m_distanceToPlayer / s_kMinimumDistanceToHear)) * MAXVOLUME);
		m_mpSounds["Zombie_1"]->SetChunkVolume(volumeSize);

	}
	else
	{
		// if the loop sound is playing
		if (m_mpSounds["Zombie_1"]->GetActiveChannel() != -1)
		{
			m_mpSounds["Zombie_1"]->StopChunk();
		}
	}
	
}

void EnemyObject::AddSound(const char* pDir, const char* pKeyName)
{
	std::pair<const char*, SoundComponent*> pair;

	pair.second = new SoundComponent();

	pair.first = pKeyName;
	pair.second->AddSoundChunk(pDir);

	m_mpSounds.insert(pair);
}
