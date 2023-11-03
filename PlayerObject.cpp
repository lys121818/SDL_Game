#include "PlayerObject.h"
#include <iostream>
#include "Vector2.h"
#include <assert.h>
#include "ObjectType.h"

PlayerObject::PlayerObject(SDL_Rect transform, CollisionReferee* pReferee, size_t type, const char* directory)
	:
	 m_transform(transform),
	 m_isWin(false),
	 m_animation(directory, 6, 200, 300, &m_transform),
	 m_collider(this, transform, pReferee),
	 m_pSpriteName(directory),
	 m_isImmune(false),
	 m_immuneTime(s_kMaxImmuneTime),
	 m_movingComponent(&m_transform,Vector2{PLAYERPOSITION}, &m_collider)
{

	/// STATUS
	m_status.m_name = "Player";
	m_status.m_type = type;
	m_status.m_health = s_KMaxHealth;	// Player Speed
	m_status.m_speed = s_kSpeed;		// Player Health
	m_status.m_isGrounded = false;
	m_status.m_isOnCollision = false;
	m_status.m_pTargetCollider = nullptr;
	m_status.m_isRight = false;
	m_status.m_attackPower = PLAYERATTACKPOWER;

	m_jumpPower = 0;
	/// TRANSFORM
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
	m_currentState = AnimationState::kIdle;
	

}

PlayerObject::~PlayerObject()
{
}

/*-----------
//  PUBLIC  //
-----------*/

void PlayerObject::Update(double deltaTime)
{
	// All the Updates of Game Event
	UpdateGameEvent(deltaTime);

	// All the Update of Animation Event
	UpdateAnimationEvent(deltaTime);

}

void PlayerObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_animation.Render(pRenderer, pTexture, m_status.m_isRight);
}

// Play the right animation fallowing current state of gameobject
void PlayerObject::AnimationState()
{
	// Check current state before play the animation
	CheckCurrentState();

	// Play animation according to m_crrentState
	switch (m_currentState)
	{
		case PlayerObject::AnimationState::kIdle:
		{
			m_animation.PlayAnimation("idle");
			break;
		}
		case PlayerObject::AnimationState::kWalk:
		{
			m_animation.PlayAnimation("walk");

			break;
		}
		case PlayerObject::AnimationState::kRun:
		{
			m_animation.PlayAnimation("run");

			break;
		}
		case PlayerObject::AnimationState::kJump:
		{
			m_animation.PlayAnimation("jump");

			break;
		}
		case PlayerObject::AnimationState::kSlide:
		{
			m_animation.PlayAnimation("slide");

			break;
		}
		default:
			break;
	}

}

// Check current state before play animation.
void PlayerObject::CheckCurrentState()
{
	// change direction of player is facing
	if (m_status.m_direction.m_x > 0)
	{
		m_status.m_isRight = true;
	}
	else if (m_status.m_direction.m_x < 0)
	{
		m_status.m_isRight = false;
	}

	if (m_status.m_isOnJump || !m_status.m_isGrounded)
	{
		m_currentState = AnimationState::kJump;
	}
	else if (m_status.m_direction.m_x != 0)	// if player is moving x direction
	{
		
		if (m_status.m_speed > PLAYERSPEED)
		{
			m_currentState = AnimationState::kRun;
		}
		else 
		{
			m_currentState = AnimationState::kWalk;
		}
	}
	else
		m_currentState = AnimationState::kIdle;

}

// Gravity mechanics
void PlayerObject::Gravity(double deltaTime)
{
	
	m_status.m_isGrounded = m_movingComponent.TryMove(deltaTime, GRAVITYPOWER, Vector2{ DOWN });
	if (m_status.m_isGrounded)
	{
		m_status.m_isOnJump = false;
		m_jumpPower = 0;
	}

}

// On Collision Event
void PlayerObject::OnCollision(ColliderComponent* pCollider)
{
	Status targetStaus = pCollider->GetOwner()->GetStatus();

	// Only Collidable Object
	assert(targetStaus.m_type < COLLISIONINDEX);

	// Colliding Event
	switch (targetStaus.m_type)
	{
		case (size_t)ObjectType::kEnemy:
		{
			if (!m_isImmune)
			{
				GetDamaged(10);
				m_isImmune = true;
				std::cout << "Health: " << m_status.m_health << std::endl;
			}
			break;
		}
		// Wall and ground do the same
		case (size_t)ObjectType::kWall:
		case (size_t)ObjectType::kGround:
		{
			// if Ground is under player
			if (pCollider->GetTransform().y > m_transform.y)
			{
				if (!m_status.m_isGrounded)
				{
					m_status.m_isGrounded = true;
				}

			}
			else if (pCollider->GetTransform().y + pCollider->GetTransform().h >= m_transform.y && m_status.m_isOnJump)
			{
				m_status.m_isOnJump = false;
			}
			else if (m_status.m_isOnJump)
				m_status.m_isOnJump = false;
			break;
		}


		default:
		{

			break;
		}
	}

 }

void PlayerObject::OnOverlapBegin(ColliderComponent* pCollider)
{
	m_status.m_pTargetCollider = pCollider;
	Status triggerStatus = pCollider->GetOwner()->GetStatus();

	std::cout << "Entered the Collision Triger with: " << triggerStatus.m_name << std::endl;

	// On Enter Trigger Event
	switch (triggerStatus.m_type)
	{
		case (size_t)ObjectType::kWinZone:
		{
			std::cout << "You Have Entered the Win Zone!" << std::endl;
			m_isWin = true;
			break;
		}
		case (size_t)ObjectType::kDamageZone:
		{
			break;
		}

	default:
	{
		break;
	}
	break;
	}
}

void PlayerObject::OnOverlapUpdate()
{
	// Get status of colliding object
	Status targetStaus = m_status.m_pTargetCollider->GetOwner()->GetStatus();

	// Not collidable Collision Object
	assert(targetStaus.m_type >= COLLISIONINDEX);

	// Trigger Event
	switch (targetStaus.m_type)
	{
	case (size_t)ObjectType::kDamageZone:
	{
		if (!m_isImmune)
		{
			GetDamaged(OBJECTDAMAGE);
			m_isImmune = true;
			std::cout << "Health: " << m_status.m_health << std::endl;
		}
		break;
	}
	case (size_t)ObjectType::kHealingZone:
	{
		if (!m_isImmune)
		{
			GetDamaged(-OBJECTDAMAGE);
			m_isImmune = true;
			std::cout << "Health: " << m_status.m_health << std::endl;
		}
		break;
	}
	case (size_t)ObjectType::kWinZone:
	{
		break;
	}


	default:
		break;

	}
}

void PlayerObject::OnOverlapEnd()
{
	m_status.m_pTargetCollider = nullptr;
}

/*-----------
// PRIVATE //
-----------*/


///////////////////////
// GAME UPDATE EVENT //////////////////////////////////
// All the update function for game events runs here //
void PlayerObject::UpdateGameEvent(double deltaTime)
{


	if (m_status.m_isOnJump)
		Jump(deltaTime);

	// check for Horizontal
	if (m_status.m_direction.m_x != 0)
		m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2{ m_status.m_direction.m_x,0 });

	// check for Vertical
	if(m_status.m_direction.m_y != 0)
		m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2{ 0,m_status.m_direction.m_y });
	

	// Immune System
	if (m_isImmune)
		ImmuneTime(deltaTime);

	// Moving System
	Gravity(deltaTime);
	
}

// Move to the direction
void PlayerObject::TryMove(Vector2 deltaDirection)
{
	m_status.m_direction.m_x += deltaDirection.m_x;
	m_status.m_direction.m_y += deltaDirection.m_y;
}

void PlayerObject::Jump(double deltaTime)
{
	// Set jump
	if (m_status.m_isGrounded)
	{
		m_jumpPower = (float)s_kMaxJumpPower;
		m_status.m_isOnJump = true;
	}

	m_movingComponent.TryMove(deltaTime, (double)m_jumpPower, Vector2{ UP });

	// decrease power of jumping every deltaTime
	m_jumpPower -= float(deltaTime * (double)(s_kMaxJumpPower * 2));

	if (m_jumpPower <= 0)
		m_status.m_isOnJump = false;
}

void PlayerObject::ImmuneTime(double deltaTime)
{
	if (m_immuneTime <= 0)
	{
		m_isImmune = false;
		m_immuneTime = s_kMaxImmuneTime;
		return;
	}
	m_immuneTime -= deltaTime;

}

void PlayerObject::GetDamaged(int amount)
{
	// decrease the health by amount of damage its given
	m_status.m_health -= amount;

	// Game Over
	if (m_status.m_health <= 0)
	{
		std::cout << "You died \n";
		m_isWin = true;

	}
	// Over Healed
	else if (m_status.m_health > s_KMaxHealth)
	{
		std::cout << "Your Health is already Full \n";
		m_status.m_health = s_KMaxHealth;
	}
}


////////////////////////////
// ANIMATION UPDATE EVENT //////////////////////////////////
// All the update function for Animation events runs here //
void PlayerObject::UpdateAnimationEvent(double deltaTime)
{
	m_animation.Update(deltaTime);

	AnimationState();
}