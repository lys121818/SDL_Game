#pragma once
#include "Defines.h"
enum Type
{
	m_Player,
	m_Enemy,
	m_Wall,

	m_BackGround = COLLISIONINDEX,
	m_DamageZone,
	m_HealingZone,
	m_WinZone,
};