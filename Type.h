#pragma once
#include "GameSetting.h"


enum class Type
{
	m_Player,
	m_Enemy,
	m_Wall,
	m_Ground,

	m_BackGround = COLLISIONINDEX,
	m_DamageZone,
	m_HealingZone,
	m_WinZone,

	m_UNINIT = 999
};
