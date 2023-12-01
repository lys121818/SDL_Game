#include "AiStateMachineEnemy.h"


AiStateMachineEnemy::AiStateMachineEnemy(GameObject* pTarget, SDL_Rect transform, CollisionReferee* pReferee, const char* directory, size_t type, const char* name)
	:
	EnemyObject(transform,pReferee,directory,type,name),
	m_stateMachine(this,pTarget,AiStateMachine::StateName::kNone)
{
}

AiStateMachineEnemy::~AiStateMachineEnemy()
{
}

void AiStateMachineEnemy::Update(double deltaTime)
{
	Gravity(deltaTime);

	UpdateDistance();

	if ( m_status.m_health <= 0)
		m_status.m_isActive = false;

	m_animation.Update(deltaTime);
	AnimationState();

	if (m_distanceToPlayer < s_kMinimumDistanceToHear)
	{
		m_stateMachine.ChangeToState(AiStateMachine::StateName::kChase);
	}
	else
	{
		m_stateMachine.ChangeToState(AiStateMachine::StateName::kIdle);
	}

	if (m_status.m_direction.m_x != 0)
	{
		// Check if it's able to move
		m_movingComponent.TryMove(deltaTime, m_status.m_speed, m_status.m_direction);
	}

	m_stateMachine.Update(deltaTime);
}
