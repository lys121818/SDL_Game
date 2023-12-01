#pragma once
#include "GameSetting.h"


enum class ObjectType
{
	// 0 is empty
	kWall = 1,
	kGround,
	kPlayer,
	kEnemy,

	kBackGround = COLLISION_INDEX,
	kDamageZone,
	kHealingZone,
	kWinZone,
	kPlayerBullet,
	kEnemeyBullet,
	kUNINIT = 999
};
