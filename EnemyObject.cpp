#include "EnemyObject.h"
#include <iostream>

EnemyObject::EnemyObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, const int kspeed, Type type)
    : m_transform(transform),
	  m_animation(directory, 6, 200, 300, &m_transform),
	  m_collider(this, transform,pReferee),
	  m_directionX(1),
	  m_pSpriteName(directory),
	  m_movingComponent(&m_transform, Vector2{ (double)transform.x,(double)transform.y },&m_collider)
{
	// Set animation sequence before game start.
	m_animation.AddAnimationSequence("idle", 0, 14);
	m_animation.AddAnimationSequence("walk", 20, 29);
	m_animation.AddAnimationSequence("attack", 30, 37);

	// Set Moving Component

	//m_position.m_x = transform.x;
	//m_position.m_y = transform.y;
	
	// Set Status of the object
	m_status.m_name = "Enemy";
	m_status.m_type = type;
	m_status.m_health = 100;
	m_status.m_speed = s_kSpeed;
	m_status.m_isOnCollision = false;
	m_status.m_isRight = false;

	// initialize starting transform information for player
	m_transform.x = transform.x;
	m_transform.y = transform.y;
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
	double deltaPosition = deltaTime * m_status.m_speed;
	// if it's moving
	if (m_status.m_speed > 0)
	{
		// Check if it's able to move
		//TryMove(Vector2{ deltaPosition * (double)m_directionX,0 });
		if(m_status.m_isRight)
			m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2{ RIGHT });
		else
			m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2{ LEFT });

	}

	if (m_transform.x > ( WINDOWWIDTH - m_transform.w )|| m_transform.x < 0)
	{
		m_directionX *= -1;
	}
		//OnCollision(&m_collider);

	m_animation.Update(deltaTime);
	AnimationState();


}

void EnemyObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_collider.DrawColliderBox(pRenderer);
	m_animation.Render(pRenderer, pTexture, m_status.m_isRight);

}

void EnemyObject::OnCollision(ColliderComponent* pCollider)
{
	
	m_status.m_isRight = !m_status.m_isRight;		// change direction it's looking
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



void EnemyObject::TryMove(Vector2 deltaPosition)
{

	/*
	// Have the collider component try to move.
	bool didMove = m_collider.TryMove(deltaPosition);

	// If the collider successfully moved, update all components.
	if (didMove)
	{
		m_position.m_x += deltaPosition.m_x;
		m_transform.x = (int)m_position.m_x;
	}

	// Return whether the movement was successful.
	//return didMove;
	*/
}