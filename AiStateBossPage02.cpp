#include "AiStateBossPage02.h"
#include "AiStateMachineEnemyBoss.h"

AiStateBossPage02::AiStateBossPage02(AiStateMachine* pOwner, GameObject* pTarget)
	:
	m_pOwner(pOwner),
	m_pTarget(pTarget)
{
}

AiStateBossPage02::~AiStateBossPage02()
{
}

void AiStateBossPage02::Enter()
{

}

void AiStateBossPage02::Update(double deltaTime)
{
	int currentHealth = m_pOwner->GetOwner()->GetStatus().m_health;

	double percentage = (double)currentHealth / (double)BOSS_MAX_HEALTH * 100;

	if (percentage < 30)
		m_pOwner->ChangeToState(AiStateMachine::StateName::kPage03);

}
