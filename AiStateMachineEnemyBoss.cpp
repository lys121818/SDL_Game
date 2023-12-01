#include "AiStateMachineEnemyBoss.h"

AiStateMachineEnemyBoss::AiStateMachineEnemyBoss(GameObject* pTarget, SDL_Rect transform, CollisionReferee* pReferee, const char* directory, size_t type, const char* name)
	:
	BossEnemy(transform, pReferee, directory, type, name),
	m_stateMachine(this, pTarget, AiStateMachine::StateName::kAttack)
{
	SetAttackTimer(5.0);
}

AiStateMachineEnemyBoss::~AiStateMachineEnemyBoss()
{

}

void AiStateMachineEnemyBoss::Update(double deltaTime)
{
	AttackUpdate(deltaTime);

	m_animation.Update(deltaTime);
	AnimationState();

	BossPage();

	if (m_status.m_health <= 0)
		m_status.m_isActive = false;

	m_stateMachine.Update(deltaTime);


}

void AiStateMachineEnemyBoss::BossPage()
{
	double percentage = (double)m_status.m_health / (double)BOSS_MAX_HEALTH * 100;
	// Page 1
	if (percentage > 70.0)
	{
		
	}
	// Page 2
	else if(percentage > 30.0)
	{

	}
	// Page 3
	else
	{
		SetRage();
	}
}
