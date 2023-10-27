#pragma once
#include "GameSetting.h"


enum class ObjectType
{
	// 0 is empty
	m_Wall = 1,
	m_Ground,

	m_Player,
	m_Enemy,

	m_BackGround = COLLISIONINDEX,
	m_DamageZone,
	m_HealingZone,
	m_WinZone,

	m_UNINIT = 999
};
