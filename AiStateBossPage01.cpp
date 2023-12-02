#include "AiStateBossPage01.h"
#include "AiStateMachineEnemyBoss.h"

AiStateBossPage01::AiStateBossPage01(AiStateMachine* pOwner, GameObject* pTarget)
	:
	m_pOwner(pOwner),
	m_pTarget(pTarget)
{

}

AiStateBossPage01::~AiStateBossPage01()
{

}

void AiStateBossPage01::Enter()
{

}

void AiStateBossPage01::Update(double deltaTime)
{
	int currentHealth = m_pOwner->GetOwner()->GetStatus().m_health;

	double percentage = (double)currentHealth / (double)BOSS_MAX_HEALTH * 100;

	if (percentage < 60)
		m_pOwner->ChangeToState(AiStateMachine::StateName::kPage02);


}
