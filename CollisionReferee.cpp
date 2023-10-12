#include "CollisionReferee.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Defines.h"

CollisionReferee::CollisionReferee()
{
}

CollisionReferee::~CollisionReferee()
{
}

/////////////////////////////////////////////////////////////////////////
// Register a new collider.
/////////////////////////////////////////////////////////////////////////
void CollisionReferee::AddActiveCollider(ColliderComponent* pCollider)
{
	// Make sure it's not already present.
	if (std::find(m_activeColliders.begin(), m_activeColliders.end(), pCollider) == m_activeColliders.end())
	{
		// If it's not already present, add in to the vector
		m_activeColliders.push_back(pCollider);
	}
}

/////////////////////////////////////////////////////////////////////////
// Unregister a collider.
/////////////////////////////////////////////////////////////////////////
void CollisionReferee::RemoveActiveCollider(ColliderComponent* pCollider)
{
	// Find the collider
	auto location = std::find(m_activeColliders.begin(),m_activeColliders.end(),pCollider);

	// If it's found, erase it from the vector.
	if (location != m_activeColliders.end())
	{
		m_activeColliders.erase(location);
	}

}
/////////////////////////////////////////////////////////////////////////
// Finds all colliders that overlap and notify them of any collision.
// Returns whether or not a collision occurred.
/////////////////////////////////////////////////////////////////////////
bool CollisionReferee::CheckForCollisionAndNotify(ColliderComponent* pColliderToCheck)
{
	// Allocate a bool for whether any collisions have occurred.
	bool didCollide = false;

	// Get pColliderToCheck's transform.
	SDL_Rect colliderTransform = pColliderToCheck->GetTransform();

	// Calculate bounds.
	int left = colliderTransform.x;
	int right = left + colliderTransform.w;
	int top = colliderTransform.y;
	int bottom = top + colliderTransform.h;

	// Check agains every active collider.
	for(ColliderComponent* pOtherCollider : m_activeColliders)
	{
		// Make sure we don't check a collider vs itself.
		if (pColliderToCheck == pOtherCollider)
			continue;
		//Get other collider's transform.
		SDL_Rect otherColliderTransform = pOtherCollider->GetTransform();

		// Calculate the bounds of the other collider.
		int otherLeft = otherColliderTransform.x;
		int otherRight = otherLeft + otherColliderTransform.w;
		int otherTop = otherColliderTransform.y;
		int otherBottom = otherTop + otherColliderTransform.h;

		// Check if they overlap horizontally.
		bool xOverlap = left < otherRight && right > otherLeft;

		// Check if they overlap vertically.
		bool yOverlap = top < otherBottom && bottom > otherTop;

		// If both x and y are true, they collide.
		if(xOverlap && yOverlap)
		{
			// Only return true when it's collider to collider
			didCollide = true;

			// A collision has occured.
			// Notify both colliders' owner of the collision.
			pColliderToCheck->GetOwner()->OnCollision(pOtherCollider);	// notify object A
			pOtherCollider->GetOwner()->OnCollision(pColliderToCheck);	// notify object B

		}
	}

	// Return whether any collision occurred.
	return didCollide;
}

bool CollisionReferee::CheckForColliderAndNotify(ColliderComponent* pColliderToCheck)
{
	// Allocate a bool for whether any collisions have occurred.
	bool didCollide = false;

	// Get pColliderToCheck's transform.
	SDL_Rect colliderTransform = pColliderToCheck->GetTransform();

	// Calculate bounds.
	int left = colliderTransform.x;
	int right = left + colliderTransform.w;
	int top = colliderTransform.y;
	int bottom = top + colliderTransform.h;

	// Check agains every active collider.
	for (ColliderComponent* pOtherCollider : m_activeColliders)
	{
		// Make sure we don't check a collider vs itself.
		if (pColliderToCheck == pOtherCollider)
			continue;
		//Get other collider's transform.
		SDL_Rect otherColliderTransform = pOtherCollider->GetTransform();

		// Calculate the bounds of the other collider.
		int otherLeft = otherColliderTransform.x;
		int otherRight = otherLeft + otherColliderTransform.w;
		int otherTop = otherColliderTransform.y;
		int otherBottom = otherTop + otherColliderTransform.h;

		// Check if they overlap horizontally.
		bool xOverlap = left < otherRight && right > otherLeft;

		// Check if they overlap vertically.
		bool yOverlap = top < otherBottom && bottom > otherTop;

		// If both x and y are true, they collide.
		if (xOverlap && yOverlap)
		{
			pColliderToCheck->GetOwner()->OnCollision(pOtherCollider);	// notify object A
			pOtherCollider->GetOwner()->OnCollision(pColliderToCheck);	// notify object B
			// Only return true when it's collider to collider

			if (pColliderToCheck->GetType() < COLLISIONINDEX &&	// when this object is collider
				pOtherCollider->GetType() < COLLISIONINDEX		// when compared object is collider
				)
			{
				// A collision has occured.
				// Notify both colliders' owner of the collision.
					didCollide = true;
			}
		}
	}

	// Return whether any collision occurred.
	return didCollide;
}
