#include <iostream>
#include "ColliderComponent.h"
#include "CollisionReferee.h"
#include "Defines.h"
#include "GameObject.h"

ColliderComponent::ColliderComponent(GameObject* pOwner, SDL_Rect transform, CollisionReferee* pReferee)
	: 
	m_pOwner(pOwner),
	m_transform(transform),
	m_pReferee(pReferee)
{
	// Add active collider to the Refferee
	if (pReferee != nullptr)
	{
		pReferee->AddActiveCollider(this);
	}

	// Collider Position
	m_position.m_x = transform.x;
	m_position.m_y = transform.y;
}

ColliderComponent::~ColliderComponent()
{
	if (m_pReferee != nullptr)
		m_pReferee->RemoveActiveCollider(this);
}

// Change position of Collider
void ColliderComponent::SetPosition(Vector2<double> newPosition)
{
	m_position = newPosition;

	m_transform.x = (int)newPosition.m_x;
	m_transform.y = (int)newPosition.m_y;

}

// Change Size of the Collider
void ColliderComponent::SetSize(Vector2<double> newSize)
{
	m_transform.w = (int)newSize.m_x;
	m_transform.h = (int)newSize.m_y;
}

// Check if move is valid
bool ColliderComponent::TryMove(Vector2<double> deltaPosition)
{

	// Make sure there's referee assigned
	if (m_pReferee == nullptr)
	{
		return true;
	}

	// Temporarily update the collider's position
	m_position.m_x += deltaPosition.m_x;
	m_position.m_y += deltaPosition.m_y;

	m_transform.x = (int)m_position.m_x;
	m_transform.y = (int)m_position.m_y;

	// Perform the collision check.
	bool didCollide = m_pReferee->CheckForColliderAndNotify(this);

	// If the move was invalid, undo it.
	if (didCollide)
	{
		m_position.m_x -= deltaPosition.m_x;
		m_position.m_y -= deltaPosition.m_y;

		m_transform.x = (int)m_position.m_x;
		m_transform.y = (int)m_position.m_y;
	}


	// Return whether the move was successful.
	return !didCollide;
}

// Collision Check with certain object
bool ColliderComponent::CollisionCheck(ColliderComponent* collider)
{
	// Return true on Collision
	bool onCollision = false;

	// return when pReferee is not assigned
	if (m_pReferee == nullptr)
	{
		return onCollision;
	}

	onCollision = m_pReferee->AABBCollisionCheck(this,collider);

	return onCollision;
}

// Draw colliderbox for test purpose to check visually
void ColliderComponent::DrawColliderBox(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, GREEN);
	SDL_RenderFillRect(pRenderer, &m_transform);
}

// Add or Remove the collider to referee
void ColliderComponent::SetCollider(bool isActive)
{
	
	if (isActive)
		m_pReferee->AddActiveCollider(this);
	else if (!isActive)
		m_pReferee->RemoveActiveCollider(this);
}
