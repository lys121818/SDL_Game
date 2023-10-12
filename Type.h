#pragma once
#include "Defines.h"
enum Type
{
	m_Player,
	m_Enemy,
	m_Wall,

	m_DamageZone = COLLISIONINDEX,
	m_HealingZone,
	m_WinZone,
};