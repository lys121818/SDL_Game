#include "PlayerObject.h"
#include <iostream>
#include "Vector2.h"
#include <assert.h>
#include "ObjectType.h"
#include "SoundDirectory.h"
#include <fstream>

PlayerObject::PlayerObject(SDL_Rect transform, CollisionReferee* pReferee, size_t type, const char* directory)
	:
	 m_transform(transform),
	 m_isGame(false),
	 m_animation(directory, 6, &m_transform),
	 m_collider(this, transform, pReferee),
	 m_pSpriteName(directory),
	 m_isImmune(false),
	 m_immuneTime(s_kMaxImmuneTime),
	 m_movingComponent(&m_transform, Vector2<double>{(double)transform.x,(double)transform.y}, & m_collider),
	 m_nameText(&m_transform)
{
	// Get Name from the file
	std::ifstream file(PLAYER_INFO);
	file >> m_status.m_name;
	file.close();

	// Set NameText to under player
	m_nameText.SetTextPlacement(TextComponent::Placement::kBottm);

	/// STATUS
	m_status.m_type = type;
	m_status.m_health = s_KMaxHealth;	// Player Speed
	m_status.m_speed = s_kSpeed;		// Player Health
	m_status.m_isGrounded = false;
	m_status.m_isOnCollision = false;
	m_status.m_pTargetCollider = nullptr;
	m_status.m_isRight = false;
	m_status.m_attackPower = PLAYER_ATTACK_POWER;

	m_jumpPower = 0;
	/// TRANSFORM
	// Size
	m_transform.w = s_kWidth;
	m_transform.h = s_kHeight;

	/// ANIMATION
	// Animation sequence
	m_animation.AddAnimationSequence("idle", Vector2<int>{175, 300}, Vector2<int>{10, 0},10);
	m_animation.AddAnimationSequence("walk", Vector2<int>{250, 300}, Vector2<int>{8, 2}, 8, 1.5);
	m_animation.AddAnimationSequence("jump", Vector2<int>{250, 300}, Vector2<int>{10, 1},10, 1.5);
	m_animation.AddAnimationSequence("attack_melee", Vector2<int>{300, 300}, Vector2<int>{8, 3},8);

	m_animation.SetCallback([this]() {
		m_status.m_isActive = false;
		});

	// Animation Default setting
	m_currentState = AnimationState::kIdle;
	
	/// SOUNDS
	AddSound(JUMP_SOUND, "Jump");
	AddSound(DEAD_SOUND, "GameOver");
	AddSound(WIN_SOUND, "Victory");
	AddSound(FOOTSTEP_SOUND, "Step");
	AddSound(HURT_SOUND, "Hurt");
}

PlayerObject::~PlayerObject()
{
	for (auto& element : m_mpSounds)
	{
		delete element.second;
	}
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
	int blink = (int)(m_immuneTime * 100);

	m_collider.DrawColliderBox(pRenderer);

	// Blink when it's on Immune
	if(!m_isImmune ||( (blink % 2) != 0))
		m_animation.Render(pRenderer, pTexture, m_status.m_isRight);

	// Render NameTag
	m_nameText.DrawTextBox(pRenderer, SDL_Color(GRAY));
	m_nameText.Render(pRenderer);

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
		
		if (m_status.m_speed > PLAYER_SPEED)
		{
			m_currentState = AnimationState::kRun;
		}
		else 
		{
			m_currentState = AnimationState::kWalk;
		}
	}
	else
	{
		m_currentState = AnimationState::kIdle;
	}

}

// On Collision Event
void PlayerObject::OnCollision(ColliderComponent* pCollider)
{
	Status targetStaus = pCollider->GetOwner()->GetStatus();

	// Only Collidable Object
	assert(targetStaus.m_type < COLLISION_INDEX);

	// Colliding Event
	switch (targetStaus.m_type)
	{
		case (size_t)ObjectType::kEnemy:
		{
			if (!m_isImmune)
			{
				Damaged(10);
				m_isImmune = true;
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
			else if (pCollider->GetTransform().y + pCollider->GetTransform().h > m_transform.y && m_status.m_isOnJump)
			{
				m_status.m_isOnJump = false;
			}
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

	// On Enter Trigger Event
	switch (triggerStatus.m_type)
	{
		case (size_t)ObjectType::kWinZone:
		{
			std::cout << "You Have Entered the Win Zone!" << std::endl;

			if(m_mpSounds["Step"]->GetActiveChannel() != -1)
				m_mpSounds["Step"]->StopChunk();	// stop loop playing

			m_mpSounds["Victory"]->PlayChunk();

			m_isGame = true;
			break;
		}
		case (size_t)ObjectType::kHealingZone:
		{
			if (!m_isImmune && m_status.m_health < s_KMaxHealth)
			{
				Damaged(-OBJECT_DAMAGE);
				std::cout << "Health: " << m_status.m_health << std::endl;
			}
			break;
		}
		case (size_t)ObjectType::kEnemeyBullet:
		{
			if (!m_isImmune)
			{
				Damaged(BULLET_POWER);
				std::cout << "Health: " << m_status.m_health << std::endl;
			}
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
	assert(targetStaus.m_type >= COLLISION_INDEX);

	// Trigger Event
	switch (targetStaus.m_type)
	{
	case (size_t)ObjectType::kDamageZone:
	{
		if (!m_isImmune)
		{
			Damaged(OBJECT_DAMAGE);
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


void PlayerObject::Damaged(int amount)
{
	// decrease the health by amount of damage its given
	m_status.m_health -= amount;

	std::cout << m_status.m_health << std::endl;

	if (amount > 0)
	{
		m_mpSounds["Hurt"]->PlayChunk();
		m_isImmune = true;
	}

	// Game Over
	if (m_status.m_health <= 0)
	{
		m_mpSounds["GameOver"]->PlayChunk();
		std::cout << "You died \n";
		m_isGame = true;

	}
	// Over Healed
	else if (m_status.m_health > s_KMaxHealth)
	{
		std::cout << "Your Health is already Full \n";
		m_status.m_health = s_KMaxHealth;
	}

	// if trigger key has allocated in m_mpTriggers
	if (m_mpTriggers[HEALTHBAR_UI_FUNCTION] != nullptr)
		m_mpTriggers[HEALTHBAR_UI_FUNCTION]();
}


/*-----------
// PRIVATE //
-----------*/


///////////////////////
// GAME UPDATE EVENT //////////////////////////////////
// All the update function for game events runs here //
void PlayerObject::UpdateGameEvent(double deltaTime)
{
	// Sound play
	SoundPlayOnMotion();

	// Nametag
	m_nameText.Update();

	// Check for jump
	// check for Vertical
	if (m_status.m_isOnJump)
		Jump(deltaTime);

	// Immune System
	if (m_isImmune)
	{
		OnImmune(deltaTime);
	}

	// check for Horizontal
	if (m_status.m_direction.m_x != 0)
		m_movingComponent.TryMove(deltaTime, m_status.m_speed, Vector2<double>{ m_status.m_direction.m_x,0 });

	// Moving System
	Gravity(deltaTime);
	
}

// Move to the direction
void PlayerObject::TryMove(Vector2<double> deltaDirection)
{
	m_status.m_direction.m_x += deltaDirection.m_x;
	m_status.m_direction.m_y += deltaDirection.m_y;
}

void PlayerObject::SetTriggerFunction(const char* name, std::function<void()> func)
{
	std::pair<const char*, std::function<void()>> pair;

	pair.first = name;

	pair.second = func;

	m_mpTriggers.insert(pair);
}

void PlayerObject::SetNameTag(TTF_Font* pFont, SDL_Color color, SDL_Renderer* pRenderer)
{
	m_nameText.SetText(pFont, m_status.m_name.c_str(), color, pRenderer);
}

void PlayerObject::Jump(double deltaTime, double jumpPower)
{
	// Set jump
	if (m_status.m_isGrounded)
	{
		m_jumpPower = (float)s_kMaxJumpPower;
		m_status.m_isOnJump = true;
		m_mpSounds["Jump"]->PlayChunk();
	}
	

	// Check if the horizontal movmenet is valid
	m_movingComponent.TryMove(deltaTime, (double)m_jumpPower, Vector2{ UP });

	// decrease power of jumping every deltaTime
	m_jumpPower -= float(deltaTime * (double)(s_kMaxJumpPower * 2));


	if (m_jumpPower <= 0)
		m_status.m_isOnJump = false;

}

void PlayerObject::OnImmune(double deltaTime)
{
	// Doesn't get damaged while Immune is set
	if (m_immuneTime <= 0)
	{

		m_isImmune = false;
		m_immuneTime = s_kMaxImmuneTime;
		return;
	}
	
	m_immuneTime -= deltaTime;
}

void PlayerObject::SoundPlayOnMotion()
{
	if (m_currentState == AnimationState::kWalk || m_currentState == AnimationState::kRun)
		m_mpSounds["Step"]->PlayChunk(-1);
	else
	{
		if (m_mpSounds["Step"]->GetActiveChannel() != -1)
		{

			m_mpSounds["Step"]->StopChunk();
		}
	}
}

void PlayerObject::AddSound(const char* pDir, const char* pKeyName)
{
	std::pair<const char*, SoundComponent*> pair;

	pair.second = new SoundComponent();

	pair.first = pKeyName;
	pair.second->AddSoundChunk(pDir);

	m_mpSounds.insert(pair);
}

// Gravity mechanics
void PlayerObject::Gravity(double deltaTime)
{

	m_status.m_isGrounded = m_movingComponent.TryMove(deltaTime, GRAVITY_POWER, Vector2{ DOWN });
	if (m_status.m_isGrounded)
	{
		m_status.m_isOnJump = false;
		m_jumpPower = 0;
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

