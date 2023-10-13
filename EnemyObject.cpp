#include "EnemyObject.h"
#include <iostream>
EnemyObject::EnemyObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, const int kspeed, Type type)
    : m_transform(transform),
	  m_animation(directory, 6, 200, 300, &m_transform),
	  m_collider(this, transform,pReferee,type),
	  m_speed(kspeed),
	  m_isRight(true),
	  m_directionX(1),
	  m_pSpriteName(directory)
{
	// Set animation sequence before game start.
	m_animation.AddAnimationSequence("idle", 0, 14);
	m_animation.AddAnimationSequence("walk", 20, 29);
	m_animation.AddAnimationSequence("attack", 30, 37);

	m_position.m_x = transform.x;
	m_position.m_y = transform.y;
	

	// initialize starting transform information for player
	m_transform.x = (int)m_position.m_x;
	m_transform.y = (int)m_position.m_y;
	m_transform.w = s_kWidth;
	m_transform.h = s_kHeight;

	// defualt animation will be idle
	m_currentState = m_idle;
}

EnemyObject::~EnemyObject()
{

}

void EnemyObject::Update(double deltaTime)
{
	double deltaPosition = deltaTime * m_speed;
	// if it's moving
	if (m_speed > 0)
	{
		// Check if it's able to move
		TryMove(Vector2{ deltaPosition * (double)m_directionX,0 });
	}
	if (m_position.m_x < 0)
		OnCollision(&m_collider);

	m_animation.Update(deltaTime);
	AnimationState();
}

void EnemyObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_collider.DrawColliderBox(pRenderer);
	m_animation.Render(pRenderer, pTexture, m_isRight);

}

void EnemyObject::OnCollision(ColliderComponent* pCollider)
{
	m_isRight = !m_isRight;		// change direction it's looking
	m_directionX *= -1;	// change the direction by multiply negative value
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
		m_isRight = true;
	}
	else if (m_directionX < 0)
	{
		m_isRight = false;
	}
	if (m_speed > 0)	// if player is moving x direction
	{

		m_currentState = m_walk;
	}
	else
		m_currentState = m_idle;

}



bool EnemyObject::TryMove(Vector2 deltaPosition)
{
	// Have the collider component try to move.
	bool didMove = m_collider.TryMove(deltaPosition);

	// If the collider successfully moved, update all components.
	if (didMove)
	{
		m_position.m_x += deltaPosition.m_x;
		m_transform.x = (int)m_position.m_x;
	}

	// Return whether the movement was successful.
	return didMove;
}