#include "EnemyObject.h"
#include <iostream>
#include <assert.h>
#include "GameSetting.h"
#include "Type.h"

EnemyObject::EnemyObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, size_t type, const char* name)
    : m_transform(transform),
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
	m_currentState = AnimationState::m_idle;
}

EnemyObject::~EnemyObject()
{

}

/*-----------
//  PUBLIC  //
-----------*/

// TODO: Clean Up Update Function
void EnemyObject::Update(double deltaTime)
{
	Gravity(deltaTime);

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

	if (targetStaus.m_type < COLLISIONINDEX)
	{
		switch (targetStaus.m_type)
		{
			case (size_t)Type::m_Wall:
			{
				m_status.m_direction.m_x *= -1;	// change the direction by multiply negative value
				break;
			}
			case (size_t)Type::m_Player:
			{
				m_status.m_direction.m_x *= -1;	// change the direction by multiply negative value
				break;
			}

			case (size_t)Type::m_Ground:
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
	assert(targetStaus.m_type >= COLLISIONINDEX);

	m_status.m_isOnCollision = true;

	m_status.m_pTargetCollider = pCollider;

}

void EnemyObject::OnOverlapUpdate()
{
	Status targetStaus = m_status.m_pTargetCollider->GetOwner()->GetStatus();
	assert(targetStaus.m_type >= COLLISIONINDEX);
}

void EnemyObject::OnOverlapEnd()
{
	Status targetStaus = m_status.m_pTargetCollider->GetOwner()->GetStatus();
	assert(targetStaus.m_type >= COLLISIONINDEX);

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
		case EnemyObject::AnimationState::m_idle:
		{
			m_animation.PlayAnimation("idle");
			break;
		}
		case EnemyObject::AnimationState::m_walk:
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

		m_currentState = AnimationState::m_walk;
	}
	else
		m_currentState = AnimationState::m_idle;

}

void EnemyObject::Gravity(double deltaTime)
{
	m_movingComponent.TryMove(deltaTime, GRAVITYPOWER, Vector2{ 0,1 });
}
