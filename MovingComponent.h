#pragma once
#include "ColliderComponent.h"
#include "Vector2.h"
#include <SDL.h>

//==================================================================================================//
/// MOVING COMPONENT
/// This is the Component for GameObject to change the transform on moving
//==================================================================================================//


class MovingComponent
{
private:
	// The collider of the Game Object
	ColliderComponent* m_objectCollider;

	// Transform of Game Object
	SDL_Rect* m_transform;

	// Position to check if the move is valid
	Vector2 m_position;


public:
	MovingComponent(SDL_Rect* transform, Vector2 position, ColliderComponent* objectCollider = nullptr);
	~MovingComponent();

	bool TryMove(double deltaTime, double speed, Vector2 direction);
	void SetPosition(Vector2 position) { m_position = position; }
private:
};

