#pragma once
#include "BossEnemy.h"
#include "AiStateMachine.h"
#include <functional>
class AiStateMachineEnemyBoss : public BossEnemy
{
private:
	AiStateMachine m_stateMachine;


public:

	AiStateMachineEnemyBoss(GameObject* pTarget, SDL_Rect transform, CollisionReferee* pReferee, const char* directory, size_t type, const char* name = "Enemy");
	~AiStateMachineEnemyBoss();

	virtual void Update(double deltaTime) override;

	void SetCallBack(std::function<void()> func) { BossEnemy::SetCallback(func); }

private:
	void BossPage();
};

