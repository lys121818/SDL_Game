#include "EnemyObject.h"
#include <iostream>
#include <assert.h>

EnemyObject::EnemyObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, const int kspeed, Type type, const char* name)
    : m_transform(transform),
	  m_animation(directory, 6, 200, 300, &m_transform),
	  m_collider(this, transform,pReferee),
	  m_directionX(1),
	  m_pSpriteName(directory),
	  m_movingComponent(&m_transform, Vector2{ (double)transform.x,(double)transform.y },&m_collider)
{
	
	/// STATUS
	m_status.m_name = name;
	m_status.m_type = type;
	m_status.m_position.m_x = transform.x;
	m_status.m_position.m_y = transform.y;
	m_status.m_health = 100;
	m_status.m_speed = s_kSpeed;
	m_status.m_isGrounded = false;
	m_status.m_isOnCollision = false;
	m_status.m_isRight = false;

	/// TRANSFORM
	// Position
	m_transform.x = (int)m_status.m_position.m_x;
	m_transform.y = (int)m_status.m_position.m_y;

	// Size
	m_transform.w = s_kWidth;
	m_transform.h = s_kHeight;

	/// ANIMATION
	// Animation sequence
	m_animation.AddAnimationSequence("idle", 0, 14);
	m_animation.AddAnimationSequence("walk", 20, 29);
	m_animation.AddAnimationSequence("attack", 30, 37);

	// Animation Default setting
	m_currentState = m_idle;
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

	double deltaPosition = deltaTime * m_status.m_speed;

	// if it's moving
	if (m_status.m_speed > 0)
	{
		// Check if it's able to move
		if(m_status.m_isRight)
			m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2{ RIGHT });
		else
			m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2{ LEFT });

	}

	if (m_transform.x > ( WINDOWWIDTH - m_transform.w )|| m_transform.x < 0)
	{
		m_directionX *= -1;
	}


	if (m_otherCollider != nullptr)
		ColliderEvent();

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
	// Get status of colliding object
	Status targetStaus = pCollider->GetOwner()->GetStatus();
	if (targetStaus.m_type != m_Ground)
		m_otherCollider = pCollider;

	// if it's collision
	if (targetStaus.m_type >= COLLISIONINDEX)
	{
		// collision enter
		if (!m_status.m_isOnCollision)
		{
			m_status.m_isOnCollision = true;
			CollisionEnter();
		}
		// collision update
		else if (m_status.m_isOnCollision)
		{
			// Collision Event Happens
			CollisionEvent();
		}

	}
	// if it's collider
	else
	{

		if (targetStaus.m_type == m_Ground)
			m_status.m_isGrounded = true;
		else
		{
			ColliderEvent();
		}
	}

}

// Play the right animation fallowing current state of gameobject
void EnemyObject::AnimationState()
{
	// Check current state before play the animation
	CheckCurrentState();

	// Play animation according to m_crrentState
	switch ((int)m_currentState)
	{
	case EnemyObject::m_idle:
	{
		m_animation.PlayAnimation("idle");
		break;
	}
	case EnemyObject::m_walk:
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
	if (m_directionX > 0)
	{
		m_status.m_isRight = true;
	}
	else if (m_directionX < 0)
	{
		m_status.m_isRight = false;
	}
	if (m_status.m_speed > 0)	// if player is moving x direction
	{

		m_currentState = m_walk;
	}
	else
		m_currentState = m_idle;

}

void EnemyObject::ColliderEvent()
{
	Status targetStaus = m_otherCollider->GetOwner()->GetStatus();

	if (targetStaus.m_type < COLLISIONINDEX)
	{
		m_status.m_isRight = !m_status.m_isRight;		// change direction it's looking
		m_directionX *= -1;	// change the direction by multiply negative value
	}
	m_otherCollider = nullptr;

}

void EnemyObject::CollisionEvent()
{
	Status targetStaus = m_otherCollider->GetOwner()->GetStatus();
	assert(targetStaus.m_type >= COLLISIONINDEX);

}

void EnemyObject::CollisionEnter()
{
	Status targetStaus = m_otherCollider->GetOwner()->GetStatus();
	assert(targetStaus.m_type >= COLLISIONINDEX);

}

void EnemyObject::CollisionExit()
{
	Status targetStaus = m_otherCollider->GetOwner()->GetStatus();
	assert(targetStaus.m_type >= COLLISIONINDEX);

}

void EnemyObject::Gravity(double deltaTime)
{
	m_movingComponent.TryMove(deltaTime, GRAVITYPOWER, Vector2{ 0,1 });
}
