#pragma once
#include "ColliderComponent.h"
#include "Vector2.h"
#include <SDL.h>

class MovingComponent
{
private:
	ColliderComponent* m_objectCollider;

	SDL_Rect* m_transform;

	Vector2 m_position;
	Vector2 m_direction;
	bool m_isRight;
	double m_speed;


public:
	MovingComponent(SDL_Rect* transform, Vector2 position, ColliderComponent* objectCollider = nullptr);
	~MovingComponent();

	void TryMove(double deltaTime, double speed, Vector2 direction);

private:
};

