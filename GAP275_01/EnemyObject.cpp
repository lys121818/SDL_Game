#include "EnemyObject.h"
#include <iostream>
EnemyObject::EnemyObject(Vector2 position, const char* directory)
    : m_animation(directory, 6, 200, 300, &m_transform),
	  m_isRight(true),
	  m_directionX(1),
	  m_position(position),
	  m_pName(directory),
	  m_counter(s_kSetCounter)
{
	// Set animation sequence before game start.
	m_animation.AddAnimationSequence("idle", 0, 9);
	m_animation.AddAnimationSequence("walk", 10, 19);
	m_animation.AddAnimationSequence("run", 20, 27);
	m_animation.AddAnimationSequence("jump", 30, 39);
	m_animation.AddAnimationSequence("slide", 40, 49);

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
	std::cout << m_counter << std::endl;
	// counter times decrease
	m_counter -= deltatime;
	// change direction when timer is 0
	if (m_counter <= 0)
	{
		m_isRight = !m_isRight;		// change direction it's looking
		m_counter = s_kSetCounter;	// reset timer
		m_directionX *= -1;	// change the direction by multiply negative value
	}
	
	double deltaPosition = deltatime * s_kSpeed;
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
	switch (m_currentState)
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
	case EnemyObject::m_run:
	{
		m_animation.PlayAnimation("run");

		break;
	}
	case EnemyObject::m_jump:
	{
		m_animation.PlayAnimation("jump");

		break;
	}
	case EnemyObject::m_slide:
	{
		m_animation.PlayAnimation("slide");

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
	if (m_directionX != 0)	// if player is moving x direction
	{

		if (s_kSpeed > 300)
		{
			m_currentState = m_run;
		}
		else
		{
			m_currentState = m_walk;
		}
	}
	else
		m_currentState = m_idle;

}


