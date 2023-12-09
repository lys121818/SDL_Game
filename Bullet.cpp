#include "Bullet.h"
#include <iostream>

Bullet::Bullet(GameObject* pOwnerObject, SDL_Rect transform, CollisionReferee* pReferee,size_t type, GameObject* pTarget,bool isAutoLock, const char* directory)
	:
	m_pSpriteName(directory),
	m_transform(transform),
	m_pReferee(pReferee),
	m_collider(this,m_transform,pReferee),
	m_animation(directory,6,&m_transform),
	m_moveingComponent(& m_transform, Vector2<double>{(double)m_transform.x, (double)m_transform.y}, & m_collider),
	m_isAutoLock(isAutoLock),
	m_pTargetObject(pTarget)
{
	// default on create
	m_currentState = AnimationState::kOnShoot;

	m_status.m_attackPower = (int)BULLET_POWER;

	m_status.m_speed = (int)BULLET_SPEED;

	m_status.m_cirtChace = pOwnerObject->GetStatus().m_cirtChace;

	m_status.m_type = type;

	m_status.m_name = "Bullet";

	m_status.m_cirtChace = pOwnerObject->GetStatus().m_cirtChace;

	m_animation.AddAnimationSequence("onShoot", Vector2<int>{170, 139}, Vector2<int>{5, 0}, 5);
	m_animation.AddAnimationSequence("muzzle", Vector2<int>{170, 139}, Vector2<int>{5, 1}, 5, 1.0f, false);

	m_animation.SetCallback([this]() {
		SetActive(false);
		});

	// has the target but not chasing the target
	if (m_pTargetObject != nullptr && !m_isAutoLock)
	{
		m_targetDirection = Vector2{ (double)m_pTargetObject->GetTransform().x,(double)m_pTargetObject->GetTransform().y };
		
		Vector2 position = Vector2{ (double)m_transform.x,(double)m_transform.y };

		m_targetDirection = m_targetDirection - position;

		m_targetDirection = m_targetDirection.Normalized();
	}
	


}

Bullet::~Bullet()
{
}

void Bullet::Update(double deltaTime)
{
	using Vector2 = Vector2<double>;

	UpdateAnimationEvent(deltaTime);

	if (m_currentState == AnimationState::kOnShoot)
	{
		if (m_pTargetObject != nullptr)
		{
			Vector2 pathToTarget;
			if (m_isAutoLock)
			{
				Vector2 targetPosition = Vector2{ (double)m_pTargetObject->GetTransform().x,(double)m_pTargetObject->GetTransform().y };
				Vector2 position = Vector2{ (double)m_transform.x,(double)m_transform.y };

				pathToTarget = targetPosition - position;

				pathToTarget = pathToTarget.Normalized();

			}
			else
			{
				pathToTarget = m_targetDirection;
			}
			m_moveingComponent.TryMove(deltaTime, m_status.m_speed, pathToTarget);

		}
		else
		{
				m_moveingComponent.TryMove(deltaTime, m_status.m_speed, m_status.m_direction);
		}
	}
}

void Bullet::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_animation.Render(pRenderer, pTexture, m_status.m_isRight);
}

void Bullet::OnOverlapBegin(ColliderComponent* pCollider)
{
	size_t objectType = pCollider->GetOwner()->GetStatus().m_type;

	switch (m_status.m_type)
	{
		case (size_t)ObjectType::kPlayerBullet:
		{
			if (objectType < 10 && objectType != (size_t)ObjectType::kPlayer)
			{
				m_collider.SetCollider(false);
				m_currentState = AnimationState::kMuzzle;

				if (objectType == (size_t)ObjectType::kEnemy)
				{
					bool isCirt = false;
					int damage = BULLET_POWER;

					// get crit chance
					if (m_rng.GetRand(0,10) < m_status.m_cirtChace)
						isCirt = true;
					
					// set damage
					if (isCirt)
					{
						std::cout << "CRIT";
						damage *= 2;
					}

					m_callback((size_t)ObjectType::kEnemy,Vector2<float>{(float)m_transform.x,(float)m_transform.y});

					pCollider->GetOwner()->Damaged(damage);
				}

				m_callback((size_t)ObjectType::kWall, Vector2<float>{(float)m_transform.x, (float)m_transform.y});

			}
			break;
		}
		case (size_t)ObjectType::kEnemeyBullet:
		{
			if (objectType < 10 && objectType != (size_t)ObjectType::kEnemy)
			{
				m_collider.SetCollider(false);
				m_currentState = AnimationState::kMuzzle;

				if (objectType == (size_t)ObjectType::kPlayer)
				{
					bool isCirt = false;
					int damage = BULLET_POWER;

					// get crit chance
					if (m_rng.GetRand(0, 10) < m_status.m_cirtChace)
						isCirt = true;

					// set damage
					if (isCirt)
					{
						std::cout << "CRIT";
						damage *= 2;
					}

					m_callback((size_t)ObjectType::kPlayer, Vector2<float>{(float)m_transform.x, (float)m_transform.y});

					pCollider->GetOwner()->Damaged(damage);
				}

				m_callback((size_t)ObjectType::kWall, Vector2<float>{(float)m_transform.x, (float)m_transform.y});

			}
			break;
		}
	default:
		break;
	}

}

void Bullet::TryMove(Vector2<double> deltaDirection)
{
	// Set direction to move
	m_status.m_direction = deltaDirection;

	// set 
	if (deltaDirection.m_x > 0)
		m_status.m_isRight = true;
	else
		m_status.m_isRight = false;
}

void Bullet::UpdateAnimationEvent(double deltaTime)
{
	AnimationState();

	m_animation.Update(deltaTime);
}

void Bullet::AnimationState()
{
	switch (m_currentState)
	{
	case Bullet::AnimationState::kOnShoot:
	{
		m_animation.PlayAnimation("onShoot");
		break;
	}
	case Bullet::AnimationState::kMuzzle:
	{
		m_animation.PlayAnimation("muzzle");
		break;
	}
	default:
		break;
	}
}

void Bullet::AddSound(const char* pDir, const char* pKeyName)
{
	std::pair<const char*, SoundComponent*> pair;

	pair.second = new SoundComponent();

	pair.first = pKeyName;
	pair.second->AddSoundChunk(pDir);

	m_mpSounds.insert(pair);
}

void Bullet::Destroy()
{
	for (auto& element : m_mpSounds)
	{
		delete element.second;
	}
}

void Bullet::SetPosition(Vector2<double> newPosition)
{
	m_transform.x = (int)newPosition.m_x; 
	m_transform.y = (int)newPosition.m_y;
}
