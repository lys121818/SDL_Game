#include "AiStateAttack.h"
#include "AiStateMachine.h"
#include "BossEnemy.h"
AiStateAttack::AiStateAttack(AiStateMachine* pOwner, GameObject* pTarget)
	:
	m_pOwner(pOwner),
	m_pTarget(pTarget)
{

}

AiStateAttack::~AiStateAttack()
{
}

void AiStateAttack::Update(double deltaTime)
{
}