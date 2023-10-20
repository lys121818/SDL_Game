#pragma once
#include <string>
#include "Type.h"
#include "Vector2.h"
struct Status
{
	std::string m_name = "UnNamed";
	Type m_type = m_UNINIT;
	Vector2 m_position = Vector2{ 0.0, 0.0 };
	int m_health = 0;
	double m_speed = 0;
	bool m_isGrounded = false;
	bool m_isRight = true;
	bool m_isOnCollision = false;

};