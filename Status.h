#pragma once
#include <string>
#include "Type.h"
struct Status
{
	// TODO
	// add position
	std::string m_name;
	Type m_type;
	int m_health;
	double m_speed;
	bool m_isRight;
	bool m_isOnCollision;

};