#include "CubeColider.h"
#include <iostream>
#include "Vector2.h"

CubeColider::CubeColider(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, SDL_Renderer* pRenderer)
	:m_transform(transform),
	 m_animation(directory,6,200,300, &m_transform),
	 m_collider(this, transform, pReferee),
	 m_isRight(true),
	 m_directionX(0),
	 m_directionY(0),
	 m_pSpriteName(directory)
{
	m_position.m_x = transform.x;
	m_position.m_y = transform.y;
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

CubeColider::~CubeColider()
{
}

void CubeColider::Update(double deltatime)
{
	// Move deltaPosition
	double deltaPosition = m_speed * deltatime;
	Vector2 deltaDirection
	{ 
		deltaPosition * (double)m_directionX, // Move Horizontal
		deltaPosition * (double)m_directionY  // Move Vertical
	};

	if (m_directionX != 0 || m_directionY != 0)
	{
		TryMove(deltaDirection);
	}

	m_animation.Update(deltatime);
	AnimationState();
}

void CubeColider::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_collider.DrawColliderBox(pRenderer);
	m_animation.Render(pRenderer, pTexture, m_isRight);
}
// Play the right animation fallowing current state of gameobject
void CubeColider::AnimationState()
{
	// Check current state before play the animation
	CheckCurrentState();
	// Play animation according to m_crrentState
	switch ((int)m_currentState)
	{
		case CubeColider::m_idle:
		{
			m_animation.PlayAnimation("idle");
			break;
		}
		case CubeColider::m_walk:
		{
			m_animation.PlayAnimation("walk");

			break;
		}
		case CubeColider::m_run:
		{
			m_animation.PlayAnimation("run");

			break;
		}
		case CubeColider::m_jump:
		{
			m_animation.PlayAnimation("jump");

			break;
		}
		case CubeColider::m_slide:
		{
			m_animation.PlayAnimation("slide");

			break;
		}
		default:
			break;
	}

}

// Check current state before play animation.
void CubeColider::CheckCurrentState()
{
	// change direction of player is facing 
	if (m_directionX > 0)
	{
		m_isRight = true;
	}
	else if (m_directionX < 0)
	{
		m_isRight = false;
	}

	// if player is going down
	if (m_directionY > 0)
	{
		m_currentState = m_slide;
	}
	else if (m_directionY < 0)
	{
		m_currentState = m_jump;
	}
	else if (m_directionX != 0)	// if player is moving x direction
	{
		
		if (m_speed > 300)
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

	if (m_currentState == m_slide)
	{
		//m_collider.SetPosition(Vector2{ m_position.m_x,m_position.m_y + s_kHeight / 2.1 });
		//m_collider.SetSize(Vector2{ s_kWidth,s_kHeight / 2.1 });
	}
	else
	{
		//m_collider.SetPosition(Vector2{ m_position.m_x,m_position.m_y});
		//m_collider.SetSize(Vector2{ s_kWidth,s_kHeight});
	}

}


// Move the object
void CubeColider::SetPosition(Vector2 position)
{
	m_position.m_x = position.m_x;
	m_position.m_y = position.m_y;
}

/////////////
// PRIVATE //
/////////////

bool CubeColider::TryMove(Vector2 deltaPosition)
{
	bool didMove = m_collider.TryMove(deltaPosition);

	// If the collider successfully moved, update all components.
	if (didMove)
	{
		// Horizontal Movement
		m_position.m_x += deltaPosition.m_x;
		m_transform.x = (int)m_position.m_x;
		// Vertical Movement
		m_position.m_y += deltaPosition.m_y;
		m_transform.y = (int)m_position.m_y;
	}
	// Return whether the movement was successful.
	return didMove;
}