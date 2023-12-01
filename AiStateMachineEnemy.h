#pragma once
#include "EnemyObject.h"
#include "AiStateMachine.h"

class AiStateMachineEnemy : public EnemyObject
{
private:
	AiStateMachine m_stateMachine;

public:

	AiStateMachineEnemy(GameObject* pTarget, SDL_Rect transform, CollisionReferee* pReferee, const char* directory, size_t type, const char* name = "Enemy");
	~AiStateMachineEnemy();

	virtual void Update(double deltaTime) override;

};

