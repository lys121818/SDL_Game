#pragma once
#include <string>
#include "Vector2.h"
#include "ObjectType.h"
#include "ColliderComponent.h"

struct Status
{

	std::string m_name = "UnNamed";

	size_t m_type = (size_t)ObjectType::m_UNINIT;

	// Current direction.x movement. -1 for left, 1for right.
	// Current direction.y movement. -1 for down, 1 for up.
	Vector2 m_direction = Vector2{ 0.0,0.0 };

	// Game Object Status
	int m_health = 0;
	double m_speed = 0;
	bool m_isGrounded = false;
	bool m_isRight = true;
	bool m_isOnJump = false;

	// Collision Info
	bool m_isOnCollision = false;
	ColliderComponent* m_pTargetCollider = nullptr;

};