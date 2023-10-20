#pragma once
#include <string>
#include "Vector2.h"
#include "Type.h"
#include "ColliderComponent.h"

struct Status
{
	std::string m_name = "UnNamed";
	size_t m_type = (size_t)Type::m_UNINIT;
	Vector2 m_position = Vector2{ 0.0, 0.0 };
	Vector2 m_direction = Vector2{ 0.0,0.0 };
	int m_health = 0;
	double m_speed = 0;
	bool m_isGrounded = false;
	bool m_isRight = true;

	bool m_isOnCollision = false;
	ColliderComponent* m_pTargetCollider = nullptr;

};