#include "CubeColider.h"
#include <iostream>
#include "Vector2.h"
#include <assert.h>

CubeColider::CubeColider(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, SDL_Renderer* pRenderer, Type type)
	:m_transform(transform),
	 m_animation(directory, 6, 200, 300, &m_transform),
	 m_collider(this, transform, pReferee,type),
	 m_isRight(true),
	 m_pSpriteName(directory),
	 m_isOnCollision(false),
	 m_isImmune(false),
	 m_isGame(false)
{
	// Player Starting Settings
	m_direction = Vector2 {0.0, 0.0};

	m_position.m_x = transform.x;	// X position
	m_position.m_y = transform.y;	// Y position
	m_speed = s_kSpeed;	// player Speed
	m_health = s_KMaxHealth;		// player Health
	m_immuneTime = s_kMaxImmuneTime;// player Immune time with an event


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
		deltaPosition * m_direction.m_x, // Move Horizontal
		deltaPosition * m_direction.m_y  // Move Vertical
	};

	// If object is moving, check to if it's trying to move into 
	if (m_direction.m_x != 0 || m_direction.m_y != 0)
	{
		TryMove(deltaDirection);
	}
	if (m_isImmune)
		ImmuneTime(deltatime);

	if (m_isOnCollision)
	{
		// Collision Enter and Update Happens
		m_isOnCollision = m_collider.CollisionCheck();

		if (!m_isOnCollision)
		{
			std::cout << "Collision Exit: " << std::endl;
		}
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
	if (m_direction.m_x > 0)
	{
		m_isRight = true;
	}
	else if (m_direction.m_x < 0)
	{
		m_isRight = false;
	}

	// if player is going down
	if (m_direction.m_y > 0)
	{
		m_currentState = m_slide;
	}
	else if (m_direction.m_y < 0)
	{
		m_currentState = m_jump;
	}
	else if (m_direction.m_x != 0)	// if player is moving x direction
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


void CubeColider::OnCollision(ColliderComponent* pCollider)
{
	// if it's enemy

	// if it's collision
	if (pCollider->GetType() >= COLLISIONINDEX)
	{


		// collision enter
		if (!m_isOnCollision)
		{
			m_isOnCollision = true;
			std::cout << "Collision Enter Type number: " << pCollider->GetType() << std::endl;

		}
		// collision update
		else if (m_isOnCollision)
		{
			//std::cout << "Collision Update" << std::endl;
			// Collision Event Happens
			CollisionEvent(pCollider);
		}

	}
	// if it's collider
	else
	{
		if (pCollider->GetType() == Type::m_Enemy)
		{
			ColliderEvent(pCollider);
			//std::cout << pCollider->GetOwner()->GetTextureName() << std::endl;
		}
		std::cout << pCollider->GetOwner()->GetTextureName() << std::endl;

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

void CubeColider::CollisionEvent(ColliderComponent* pCollider)
{
	assert(pCollider->GetType() >= COLLISIONINDEX);
	switch (pCollider->GetType())
	{
		case m_DamageZone:
		{
			if (!m_isImmune)
			{
				GetDamaged(10);
				m_isImmune = true;
				std::cout << "Health: " << m_health << std::endl;
			}
			break;
		}
		case m_HealingZone:
		{
			if (!m_isImmune)
			{
				GetDamaged(-10);
				m_isImmune = true;
				std::cout << "Health: " << m_health << std::endl;
			}
			break;

		case m_WinZone:
		{
			m_isGame = true;
			break;
		}

		}
		default:
		break;

	}
}

void CubeColider::ColliderEvent(ColliderComponent* pCollider)
{
}

void CubeColider::ImmuneTime(double deltaTime)
{
	if (m_immuneTime <= 0)
	{
		m_isImmune = false;
		m_immuneTime = s_kMaxImmuneTime;
		return;
	}
	//std::cout << "ImmuneTime: " << m_immuneTime << std::endl;
	m_immuneTime -= deltaTime;

}

void CubeColider::GetDamaged(int amount)
{
	m_health -= amount;
	if (m_health <= 0)
		m_isGame = true;
	else if (m_health > s_KMaxHealth)
		m_health = s_KMaxHealth;
}
