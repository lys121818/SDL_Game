#include "AiStateChase.h"
#include "AiStateMachine.h"
#include "GameObject.h"
#include "Vector2.h"

AiStateChase::AiStateChase(AiStateMachine* pOwner, GameObject* pTarget)
	:
	m_pOwner(pOwner),
	m_pTarget(pTarget)
{
}

AiStateChase::~AiStateChase()
{
}

void AiStateChase::Update(double deltaTime)
{
	if (m_pTarget->GetTransform().x > m_pOwner->GetOwner()->GetTransform().x)
	{
		m_pOwner->GetOwner()->TryMove(Vector2<double>{ RIGHT });
	}
	else
	{
		m_pOwner->GetOwner()->TryMove(Vector2<double>{ LEFT });
	}

		
}
