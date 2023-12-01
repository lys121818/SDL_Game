#include "AiStateMachine.h"

#include "State.h"
#include "AiStateChase.h"
#include "AiStateWandering.h"
#include "AiStateAttack.h"

AiStateMachine::AiStateMachine(GameObject* pOwner, GameObject* pTarget, StateName initState)
	:
	m_pOwner(pOwner),
	m_pTarget(pTarget),
	m_pCurrentState(nullptr)
{
	ChangeToState(initState);
}

AiStateMachine::~AiStateMachine()
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
		delete m_pCurrentState;
	}

}

void AiStateMachine::Update(double deltaTime)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Update(deltaTime);
	}
}

void AiStateMachine::ChangeToState(StateName state)
{
	if (m_currentStateName == state)
		return;

	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
		delete m_pCurrentState;
	}

	// TODO: allocate the new state
	switch (state)
	{
	case AiStateMachine::kNone:
		break;
	case AiStateMachine::kIdle:
	{
		m_pCurrentState = new AiStateWandering(this,m_pTarget);
		break;
	}
	case AiStateMachine::kChase:
	{
		m_pCurrentState = new AiStateChase(this, m_pTarget);
		break;
	}
	case AiStateMachine::kAttack:
	{
		m_pCurrentState = new AiStateAttack(this, m_pTarget);
		break;
	}
	default:
		break;
	}

	m_currentStateName = state;

	if (m_pCurrentState != nullptr)
		m_pCurrentState->Enter();
}