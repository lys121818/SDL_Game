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
		kAttack,

		// BOSS
		kPage01 = 5,
		kPage02,
		kPage03

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

	size_t GetState() { return (size_t)m_currentStateName; }

	GameObject* GetOwner() { return m_pOwner; }

};
