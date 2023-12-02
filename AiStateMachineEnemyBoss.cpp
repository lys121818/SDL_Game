#include "AiStateMachineEnemyBoss.h"

AiStateMachineEnemyBoss::AiStateMachineEnemyBoss(GameObject* pTarget, SDL_Rect transform, CollisionReferee* pReferee, const char* directory, size_t type, const char* name)
	:
	BossEnemy(transform, pReferee, directory, type, name),
	m_stateMachine(this, pTarget, AiStateMachine::StateName::kPage01)
{
	SetAttackTimer(BOSS_DEFAULT_TIMER);
	
}

AiStateMachineEnemyBoss::~AiStateMachineEnemyBoss()
{

}

void AiStateMachineEnemyBoss::Update(double deltaTime)
{
	// Basic Attack Setting
	AttackUpdate(deltaTime);

	m_animation.Update(deltaTime);
	AnimationState();

	if (m_status.m_health <= 0)
	{
		m_status.m_isActive = false;
		OnCallBack("Defeat");
	}

	switch (m_stateMachine.GetState())
	{
			//Page 01
			case 5:
			{
				break;
			}
			//Page 02
			case 6:
			{
				SetAttackTimer(2);
				break;
			}
			//Page 03

			case 7:
			{
				SetAttackTimer(1);
				SetRage();
				break;
			}
		default:
			break;
	}

	m_stateMachine.Update(deltaTime);

}