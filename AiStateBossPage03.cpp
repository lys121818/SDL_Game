#include "AiStateBossPage03.h"
#include "AiStateMachineEnemyBoss.h"

AiStateBossPage03::AiStateBossPage03(AiStateMachine* pOwner, GameObject* pTarget)
	:
	m_pOwner(pOwner),
	m_pTarget(pTarget)
{
}

AiStateBossPage03::~AiStateBossPage03()
{
}

void AiStateBossPage03::Update(double deltaTime)
{
}
