#include "ColliderComponent.h"
#include "CollisionReferee.h"

ColliderComponent::ColliderComponent(GameObject* pOwner, SDL_Rect transform, CollisionReferee* pReferee)
	: m_pOwner(pOwner),
	  m_transform(transform),
	  m_pReferee(pReferee)
{
	if (pReferee != nullptr)
	{
		pReferee->AddActiveCollider(this);
	}

}

ColliderComponent::~ColliderComponent()
{
	if (m_pReferee != nullptr)
		m_pReferee->RemoveActiveCollider(this);
}

void ColliderComponent::SetPosition(Vector2 newPosition)
{
	m_transform.x = newPosition.m_x;
	m_transform.y = newPosition.m_y;
}

bool ColliderComponent::TryMove(Vector2 deltaPosition)
{
	// Make sure there's referee assigned
	if (m_pReferee == nullptr)
	{
		return true;
	}
	// Temporarily update the collider's position
	m_transform.x += deltaPosition.m_x;
	m_transform.y += deltaPosition.m_y;

	// Perform the collision check.
	bool didCollide = m_pReferee->CheckForCollisionAndNotify(this);

	// If the move was invalid, undo it.
	if (didCollide)
	{
		m_transform.x -= deltaPosition.m_x;
		m_transform.y -= deltaPosition.m_y;
	}

	// Return whether the move was successful.
	return !didCollide;
}
