#include "EnemyObject.h"
#include <iostream>
EnemyObject::EnemyObject(Vector2 position, const char* directory, const int kspeed)
    : m_animation(directory, 6, 200, 300, &m_transform),
	  m_speed(kspeed),
	  m_isRight(true),
	  m_directionX(1),
	  m_position(position),
	  m_pName(directory),
	  m_counter(s_kSetCounter)
{
	// Set animation sequence before game start.
	m_animation.AddAnimationSequence("idle", 0, 14);
	m_animation.AddAnimationSequence("walk", 20, 29);
	m_animation.AddAnimationSequence("attack", 30, 37);

	

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

void EnemyObject::Update(double deltatime)
{
	// counter times decrease
	m_counter -= deltatime;
	// change direction when timer is 0
	if (m_counter <= 0)
	{
		m_isRight = !m_isRight;		// change direction it's looking
		m_counter = s_kSetCounter;	// reset timer
		m_directionX *= -1;	// change the direction by multiply negative value
	}
	
	double deltaPosition = deltatime * m_speed;
	m_position.m_x += deltaPosition * m_directionX;
	m_transform.x = (int)m_position.m_x;

	m_animation.Update(deltatime);
	AnimationState();
}

void EnemyObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_animation.Render(pRenderer, pTexture, m_isRight);
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


