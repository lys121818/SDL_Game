#pragma once

class GameObject;
class State;

class AiStateMachine
{
public:
	enum StateName
	{
		None
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