#pragma once
#include "State.h"

class AiStateMachine;
class GameObject;

class AiStateBossPage01 : public State
{
private:
	AiStateMachine* m_pOwner;

	GameObject* m_pTarget;

public:
	AiStateBossPage01(AiStateMachine* pOwner, GameObject* pTarget);
	~AiStateBossPage01();

	virtual void Enter() override;
	virtual void Update(double deltaTime) override;
};

