#pragma once
#include "GameSetting.h"


enum class ObjectType
{
	// 0 is empty
	kWall = 1,
	kGround,

	kPlayer,
	kEnemy,

	kBackGround = COLLISIONINDEX,
	kDamageZone,
	kHealingZone,
	kWinZone,

	kUNINIT = 999
};
