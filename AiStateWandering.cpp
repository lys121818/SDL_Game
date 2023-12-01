#include "AiStateWandering.h"
#include "AiStateMachine.h"
#include "GameObject.h"


AiStateWandering::AiStateWandering(AiStateMachine* pOwner, GameObject* pTarget)
	:
	m_pOwner(pOwner),
	m_pTarget(pTarget)
{
}

AiStateWandering::~AiStateWandering()
{
}

void AiStateWandering::Enter()
{
	m_pOwner->GetOwner()->TryMove(Vector2<double>{ RIGHT });
}

