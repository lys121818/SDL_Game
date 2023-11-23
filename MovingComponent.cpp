#include "MovingComponent.h"
#include "ColliderComponent.h"

MovingComponent::MovingComponent(SDL_Rect* transform, Vector2<double> position, ColliderComponent* objectCollider)
	:m_transform(transform),
	 m_objectCollider(objectCollider),
	 m_position(position)
{
}

MovingComponent::~MovingComponent()
{

}

bool MovingComponent::TryMove(double deltaTime, double speed, Vector2<int> direction)
{

	// Amount of position its moving
	double deltaPosition = speed * deltaTime;

	// Check if the move is valid
	bool isAble = false;

	// Direction of position its moving
	Vector2<double> deltaDirection
	{
		deltaPosition * direction.m_x, // Move Horizontal
		deltaPosition * direction.m_y  // Move Vertical
	};

	// Horizontal Movement
	m_position.m_x += deltaDirection.m_x;
	m_transform->x = (int)m_position.m_x;

	// Vertical Movement
	m_position.m_y += deltaDirection.m_y;
	m_transform->y = (int)m_position.m_y;

	// If object has colliderComponent
	if (m_objectCollider != nullptr)
	{
		isAble = m_objectCollider->TryMove(deltaDirection);
		// If object moving has failed.
		// Back to position of where it was
		if (!isAble)
		{
			// Horizontal Movement
			m_position.m_x -= deltaDirection.m_x;
			m_transform->x = (int)m_position.m_x;

			// Vertical Movement
			m_position.m_y -= deltaDirection.m_y;
			m_transform->y = (int)m_position.m_y;
		}
	}
	return !isAble;
}