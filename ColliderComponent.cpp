#include <iostream>
#include "ColliderComponent.h"
#include "CollisionReferee.h"
#include "Defines.h"

ColliderComponent::ColliderComponent(GameObject* pOwner, SDL_Rect transform, CollisionReferee* pReferee, Type type)
	: m_pOwner(pOwner),
	  m_transform(transform),
	  m_pReferee(pReferee),
	  m_type(type)
{
	if (pReferee != nullptr)
	{
		pReferee->AddActiveCollider(this);
	}

	m_position.m_x = transform.x;
	m_position.m_y = transform.y;

}

ColliderComponent::~ColliderComponent()
{
	if (m_pReferee != nullptr)
		m_pReferee->RemoveActiveCollider(this);
}

void ColliderComponent::SetPosition(Vector2 newPosition)
{
	m_transform.x = (int)newPosition.m_x;
	m_transform.y = (int)newPosition.m_y;
}

void ColliderComponent::SetSize(Vector2 newSize)
{
	m_transform.w = (int)newSize.m_x;
	m_transform.h = (int)newSize.m_y;
}

bool ColliderComponent::TryMove(Vector2 deltaPosition)
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

bool ColliderComponent::CollisionCheck()
{
	bool onCollision = false;

	// return when pReferee is not assigned
	if (m_pReferee == nullptr)
	{
		return onCollision;
	}
	onCollision = m_pReferee->CheckForCollisionAndNotify(this);

	return onCollision;
}

// Draw colliderbox for test purpose
void ColliderComponent::DrawColliderBox(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, GREEN);
	SDL_RenderFillRect(pRenderer, &m_transform);
}
