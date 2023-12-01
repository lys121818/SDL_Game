#pragma once
#include <functional>

class GameObject;
class State;


//==================================================================================================//
/// AI STATE MACHINE
/// A basic state machine for AI
//==================================================================================================//

class AiStateMachine
{
public:
	enum StateName
	{
		kNone,
		kIdle,
		kChase,
		kAttack
	};

private:
	GameObject* m_pOwner;

	GameObject* m_pTarget;

	State* m_pCurrentState;

	StateName m_currentStateName;

public:
	AiStateMachine(GameObject* pOwner, GameObject* pTarget, StateName initState);
	~AiStateMachine();

	void Update(double deltaTime);

	void ChangeToState(StateName state);

	GameObject* GetOwner() { return m_pOwner; }

};