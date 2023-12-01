#pragma once
#include "State.h"

class AiStateMachine;
class GameObject;

//==================================================================================================//
/// AI STATE CHASE
/// State feature of chasing behavior
//==================================================================================================//

class AiStateChase : public State
{
private:
	AiStateMachine* m_pOwner;

	GameObject* m_pTarget;

public:
	AiStateChase(AiStateMachine* pOwner, GameObject* pTarget);
	~AiStateChase();

	virtual void Update(double deltaTime) override;
};

