#pragma once
#include "State.h"

class AiStateMachine;
class GameObject;


class AiStateBossPage02 : public State
{
private:
	AiStateMachine* m_pOwner;

	GameObject* m_pTarget;

public:
	AiStateBossPage02(AiStateMachine* pOwner, GameObject* pTarget);
	~AiStateBossPage02();

	virtual void Enter() override;

	virtual void Update(double deltaTime) override;
};

