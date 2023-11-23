#include "AiStateMachine.h"
#include "State.h"

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

	m_currentStateName = state;
	m_pCurrentState->Enter();
}
