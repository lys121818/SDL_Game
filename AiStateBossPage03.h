#pragma once
#include "State.h"

class AiStateMachine;
class GameObject;


class AiStateBossPage03 : public State
{
private:
	AiStateMachine* m_pOwner;

	GameObject* m_pTarget;

public:
	AiStateBossPage03(AiStateMachine* pOwner, GameObject* pTarget);
	~AiStateBossPage03();

	virtual void Update(double deltaTime) override;
};