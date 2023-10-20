#include "CubeColider.h"
#include <iostream>
#include "Vector2.h"
#include <assert.h>

CubeColider::CubeColider(SDL_Rect transform, CollisionReferee* pReferee, SDL_Renderer* pRenderer, Type type, const char* directory)
	:
	 m_transform(transform),
	 m_isGame(false),
	 m_animation(directory, 6, 200, 300, &m_transform),
	 m_collider(this, transform, pReferee),
	 m_pSpriteName(directory),
	 m_isImmune(false),
	 m_immuneTime(s_kMaxImmuneTime),
	 m_direction(Vector2{0.0, 0.0}),
	 m_otherCollider(nullptr),
	 m_movingComponent(&m_transform,Vector2{PLAYERPOSITION}, &m_collider)
{
	/// STATUS
	m_status.m_name = "Player";
	m_status.m_type = type;
	m_status.m_position.m_x = transform.x;
	m_status.m_position.m_y = transform.y;
	m_status.m_health = s_KMaxHealth;	// Player Speed
	m_status.m_speed = s_kSpeed;		// Player Health
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
	m_animation.AddAnimationSequence("idle", 0, 9);
	m_animation.AddAnimationSequence("walk", 10, 19);
	m_animation.AddAnimationSequence("run", 20, 27);
	m_animation.AddAnimationSequence("jump", 30, 39);
	m_animation.AddAnimationSequence("slide", 40, 49);

	// Animation Default setting
	m_currentState = m_idle;
	

}

CubeColider::~CubeColider()
{
}

/*-----------
//  PUBLIC  //
-----------*/

void CubeColider::Update(double deltaTime)
{
	// All the Updates of Game Event
	UpdateGameEvent(deltaTime);

	// All the Update of Animation Event
	UpdateAnimationEvent(deltaTime);

}

void CubeColider::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_animation.Render(pRenderer, pTexture, m_status.m_isRight);
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
		m_status.m_isRight = true;
	}
	else if (m_direction.m_x < 0)
	{
		m_status.m_isRight = false;
	}

	// if player is going down
	if (m_direction.m_y > 0)
	{
		m_currentState = m_slide;
	}
	else if (m_direction.m_y < 0)
	{
		m_status.m_isGrounded = false;
		m_currentState = m_jump;
	}
	else if (m_direction.m_x != 0)	// if player is moving x direction
	{
		
		if (m_status.m_speed > 300)
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

// Gravity mechanics
void CubeColider::Gravity(double deltaTime)
{

	m_movingComponent.TryMove(deltaTime, GRAVITYPOWER, Vector2{ 0,1 });
}

// On Collision Event
void CubeColider::OnCollision(ColliderComponent* pCollider)
{
	// Get status of colliding object
	Status targetStaus = pCollider->GetOwner()->GetStatus();

	// if it's collision
	if (targetStaus.m_type >= COLLISIONINDEX)
	{
		// Set current triggered object
		m_otherCollider = pCollider;

		// collision enter
		if (!m_status.m_isOnCollision)
		{
			m_status.m_isOnCollision = true;
			CollisionEnter();
		}
		// collision update
		else if (m_status.m_isOnCollision)
		{
			//std::cout << "Collision Update" << std::endl;
			// Collision Event Happens
			CollisionEvent();
		}

	}
	// if it's collider
	else
	{
		ColliderEvent(pCollider);
	}

 }

/*-----------
// PRIVATE //
-----------*/

///////////////////////
// GAME UPDATE EVENT //////////////////////////////////
// All the update function for game events runs here //
void CubeColider::UpdateGameEvent(double deltaTime)
{
	// Moving System
	// check for Horizontal
	if (m_direction.m_x != 0)
		m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2{ m_direction.m_x,0 });

	// check for Vertical
	if(m_direction.m_y != 0)
		m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2{ 0,m_direction.m_y });
	
	// Gravity System
	if (!m_status.m_isGrounded)
		Gravity(deltaTime);

	// Immune System
	if (m_isImmune)
		ImmuneTime(deltaTime);

	// On Collision System
	if (m_otherCollider != nullptr)
	{
		CheckForCollision();
	}

}

// Move to the direction
void CubeColider::TryMove(Vector2 deltaDirection)
{
	m_direction.m_x += deltaDirection.m_x;
	m_direction.m_y += deltaDirection.m_y;
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
	// decrease the health by amount of damage its given
	m_status.m_health -= amount;

	// Game Over
	if (m_status.m_health <= 0)
	{
		std::cout << "You died \n";
		m_isGame = true;
	}
	// Over Healed
	else if (m_status.m_health > s_KMaxHealth)
	{
		std::cout << "Your Health is already Full \n";
		m_status.m_health = s_KMaxHealth;
	}
}


/////////////////////////////
// OBJECT COLLISION EVENTS //
void CubeColider::CheckForCollision()
{
	// Check if it's on collision with targeted object
	if(m_otherCollider != nullptr)
		m_status.m_isOnCollision = m_collider.CollisionCheck(m_otherCollider);

	// Collision Exit Event
	if (!m_status.m_isOnCollision)
	{
		m_otherCollider = nullptr;
		std::cout << "Collision Exit" << std::endl;
	}
	// Collision Update
	else
	{
		CollisionEvent();
	}
}

void CubeColider::ColliderEvent(ColliderComponent* pCollider)
{
	Status targetStaus = pCollider->GetOwner()->GetStatus();

	// Only Collidable Object
	assert(targetStaus.m_type < COLLISIONINDEX);

	// Colliding Event
	switch (targetStaus.m_type)
	{
		case m_Enemy:
		{
			if (!m_isImmune)
			{
				GetDamaged(10);
				m_isImmune = true;
				std::cout << "Health: " << m_status.m_health << std::endl;
			}
			break;
		}
		case m_Ground:
		{
			if (!m_status.m_isGrounded)
			{
				std::cout << "Ground! " << std::endl;
				m_status.m_isGrounded = true;
			}
			break;
		}
	
		default:
		{

			break;
		}
	}
}

void CubeColider::CollisionEnter()
{
	Status triggerStatus = m_otherCollider->GetOwner()->GetStatus();
	std::cout << "Entered the Collision Triger with: " << triggerStatus.m_name << std::endl;

	// On Enter Trigger Event
	switch (triggerStatus.m_type)
	{
		case m_WinZone:
		{
			std::cout << "You Have Entered the Win Zone!" << std::endl;
			break;
		}

		default:
		{
			break;
		}
	}
}

void CubeColider::CollisionEvent()
{
	// Get status of colliding object
	Status targetStaus = m_otherCollider->GetOwner()->GetStatus();

	// Not collidable Collision Object
	assert(targetStaus.m_type >= COLLISIONINDEX);

	// Trigger Event
	switch (targetStaus.m_type)
	{
		case m_DamageZone:
		{
			if (!m_isImmune)
			{
				GetDamaged(10);
				m_isImmune = true;
				std::cout << "Health: " << m_status.m_health << std::endl;
			}
			break;
		}
		case m_HealingZone:
		{
			if (!m_isImmune)
			{
				GetDamaged(-10);
				m_isImmune = true;
				std::cout << "Health: " << m_status.m_health << std::endl;
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

void CubeColider::CollisionExit()
{

}


////////////////////////////
// ANIMATION UPDATE EVENT //////////////////////////////////
// All the update function for Animation events runs here //
void CubeColider::UpdateAnimationEvent(double deltaTime)
{
	m_animation.Update(deltaTime);

	AnimationState();
}