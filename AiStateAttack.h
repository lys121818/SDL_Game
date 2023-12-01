#pragma once
#include "State.h"

class AiStateMachine;
class GameObject;

class AiStateAttack : public State
{
private:
	AiStateMachine* m_pOwner;

	GameObject* m_pTarget;

public:
	AiStateAttack(AiStateMachine* pOwner, GameObject* pTarget);
	~AiStateAttack();

	virtual void Update(double deltaTime) override;
};

