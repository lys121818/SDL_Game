#include "CubeColider.h"
#include <iostream>
#include "Vector2.h"

CubeColider::CubeColider(Vector2 position, const char* directory, SDL_Renderer* pRenderer)
	:m_animation("assets/Pumpkin.png",6,200,300, pRenderer,&m_transform),
	 m_position(position),
	 m_directionX(0),
	 m_directionY(0),
	 m_pName(directory)
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
	m_currentState = idle;
	
}

CubeColider::~CubeColider()
{
}

void CubeColider::Update(double deltatime)
{
	// Move Vertical
	double deltaPositionX = m_speed * deltatime;
	m_position.m_x += deltaPositionX * m_directionX;
	m_transform.x = (int)m_position.m_x;

	// Move Horizontal
	double deltaPositionY = m_speed * deltatime;
	m_position.m_y += deltaPositionY * m_directionY;
	m_transform.y = (int)m_position.m_y;

	m_animation.Update(deltatime);
	AnimationState();
}

void CubeColider::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_animation.Render(pRenderer);
}
// Play the right animation fallowing current state of gameobject
void CubeColider::AnimationState()
{
	// Check current state before play the animation
	CheckCurrentState();
	// Play animation according to m_crrentState
	switch (m_currentState)
	{
		case CubeColider::idle:
		{
			m_animation.PlayAnimation("idle");
			break;
		}
		case CubeColider::walk:
		{
			m_animation.PlayAnimation("walk");

			break;
		}
		case CubeColider::run:
		{
			m_animation.PlayAnimation("run");

			break;
		}
		case CubeColider::jump:
		{
			m_animation.PlayAnimation("jump");

			break;
		}
		case CubeColider::slide:
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
	// if player is going down
	if (m_directionY > 0)
		m_currentState = slide;
	else if (m_directionX != 0)	// if player is moving x direction
	{
		if (m_speed > 300)
		{
			m_currentState = run;
		}
		else 
		{
			m_currentState = walk;
		}
	}
	else
		m_currentState = idle;

}

// Move the object
void CubeColider::SetPosition(Vector2 position)
{
	m_position.m_x = position.m_x;
	m_position.m_y = position.m_y;
}
