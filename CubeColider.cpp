#include "CubeColider.h"
#include <iostream>
#include "Vector2.h"
#include <assert.h>

CubeColider::CubeColider(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, SDL_Renderer* pRenderer, Type type)
	:m_transform(transform),
	 m_animation(directory, 6, 200, 300, &m_transform),
	 m_collider(this, transform, pReferee),
	 m_pSpriteName(directory),
	 m_isImmune(false),
	 m_isGame(false),
	 m_otherCollider(nullptr),
	 m_movingComponent(&m_transform,Vector2{PLAYERPOSITION}, &m_collider)
{
	
	// Player Starting Settings
	m_direction = Vector2 {0.0, 0.0};

	m_immuneTime = s_kMaxImmuneTime;// player Immune time with an event

	// Set starting position of object moving component

	// Set animation sequence before game start.
	m_animation.AddAnimationSequence("idle", 0, 9);
	m_animation.AddAnimationSequence("walk", 10, 19);
	m_animation.AddAnimationSequence("run", 20, 27);
	m_animation.AddAnimationSequence("jump", 30, 39);
	m_animation.AddAnimationSequence("slide", 40, 49);
	
	// initialize starting transform information for player
	m_transform.x = transform.x;
	m_transform.y = transform.y;
	m_transform.w = s_kWidth;
	m_transform.h = s_kHeight;

	// defualt animation will be idle
	m_currentState = m_idle;
	
	//Starting Status
	m_status.m_name = "Player";
	m_status.m_type = type;
	m_status.m_health = s_KMaxHealth;	// Player Speed
	m_status.m_speed = s_kSpeed;		// Player Health
	m_status.m_isOnCollision = false;
	m_status.m_isRight = false;

}

CubeColider::~CubeColider()
{
}

void CubeColider::Update(double deltaTime)
{
	UpdateGameEvent(deltaTime);
	UpdateAnimationEvent(deltaTime);

}

void CubeColider::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_collider.DrawColliderBox(pRenderer);
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
	// Get status of colliding object
	Status targetStaus = pCollider->GetOwner()->GetStatus();

	// if it's collision
	if (targetStaus.m_type >= COLLISIONINDEX)
	{
		m_otherCollider = pCollider;


		// collision enter
		if (!m_status.m_isOnCollision)
		{
			m_status.m_isOnCollision = true;
			std::cout << "Collision Enter Type number: " << targetStaus.m_type << std::endl;

		}
		// collision update
		else if (m_status.m_isOnCollision)
		{
			//std::cout << "Collision Update" << std::endl;
			// Collision Event Happens
			CollisionEvent(pCollider);
		}

	}
	// if it's collider
	else
	{
		if (targetStaus.m_type == Type::m_Enemy)
		{
			ColliderEvent(pCollider);
		}
	}

 }

///////////////////////
// GAME UPDATE EVENT //////////////////////////////////
// All the update function for game events runs here //
void CubeColider::UpdateGameEvent(double deltaTime)
{
	// Move deltaPosition
	
	// Check if object is moving and move when it's able to move
	
	// chekc for Horizontal
	if (m_direction.m_x != 0)
		m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2{ m_direction.m_x,0 });
	// chekc for Vertical
	if(m_direction.m_y != 0)
		m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2{ 0,m_direction.m_y });

	// decrease time
	if (m_isImmune)
		ImmuneTime(deltaTime);

	// If the object is on collision to something check and play the event
	if (m_otherCollider != nullptr)
	{
		//std::cout << "not Empty " << deltaTime << std::endl;
		CheckForCollision();
	}
}

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
	m_status.m_health -= amount;
	if (m_status.m_health <= 0)
	{
		std::cout << "You died \n";
		m_isGame = true;
	}
	else if (m_status.m_health > s_KMaxHealth)
	{
		std::cout << "Your Health is already Full \n";
		m_status.m_health = s_KMaxHealth;
	}
}


////////////////////////////
// ANIMATION UPDATE EVENT //////////////////////////////////
// All the update function for Animation events runs here //
void CubeColider::UpdateAnimationEvent(double deltaTime)
{
	m_animation.Update(deltaTime);
	AnimationState();
}


/////////////////////////////
// OBJECT COLLISION EVENTS //
void CubeColider::CheckForCollision()
{
	if(m_otherCollider != nullptr)
		m_status.m_isOnCollision = m_collider.CollisionCheck(m_otherCollider);

	// Event when collision Exit
	if (!m_status.m_isOnCollision)
	{
		m_otherCollider = nullptr;
		std::cout << "Collision Exit" << std::endl;
	}
	else
		OnCollision(m_otherCollider);
}

void CubeColider::CollisionEvent(ColliderComponent* pCollider)
{
	// Get status of colliding object
	Status targetStaus = pCollider->GetOwner()->GetStatus();

	assert(targetStaus.m_type >= COLLISIONINDEX);
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

void CubeColider::ColliderEvent(ColliderComponent* pCollider)
{
	Status targetStaus = pCollider->GetOwner()->GetStatus();

	assert(targetStaus.m_type < COLLISIONINDEX);
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
	
		default:
			break;

	}
}


