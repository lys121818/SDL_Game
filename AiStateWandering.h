#pragma once
#include "State.h"

class AiStateMachine;
class GameObject;


//==================================================================================================//
/// AI STATE WANDERING
/// State feature of wandering behavior
//==================================================================================================//

class AiStateWandering : public State
{
private:
	AiStateMachine* m_pOwner;

	GameObject* m_pTarget;

public:
	AiStateWandering(AiStateMachine* pOwner, GameObject* pTarget);
	~AiStateWandering();

	virtual void Enter() override;

};
