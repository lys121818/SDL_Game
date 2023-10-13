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

	// Check agains every active collider.
	for(ColliderComponent* pOtherCollider : m_activeColliders)
	{
		// Make sure we don't check a collider vs itself.
		if (pColliderToCheck == pOtherCollider)
			continue;
		//Get other collider's transform.
		SDL_Rect otherColliderTransform = pOtherCollider->GetTransform();

		// If both x and y are true, they collide.
		if(AABBCollisionCheck(colliderTransform, otherColliderTransform))
		{
			// Allocate a bool for whether any collisions have occurred.
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

	// Check agains every active collider.
	for (ColliderComponent* pOtherCollider : m_activeColliders)
	{
		// Make sure we don't check a collider vs itself.
		if (pColliderToCheck == pOtherCollider)
			continue;
		//Get other collider's transform.
		SDL_Rect otherColliderTransform = pOtherCollider->GetTransform();

		// Calculate the bounds of the other collider.

		// If both x and y are true, they collide.
		if (AABBCollisionCheck(colliderTransform,otherColliderTransform))
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

bool CollisionReferee::AABBCollisionCheck(SDL_Rect& colliderATransform, SDL_Rect& colliderBTransform)
{
	int left_A = colliderATransform.x;
	int right_A = left_A + colliderATransform.w;
	int top_A = colliderATransform.y;
	int bottom_A = top_A + colliderATransform.h;

	int left_B = colliderBTransform.x;
	int right_B = left_B + colliderBTransform.w;
	int top_B = colliderBTransform.y;
	int bottom_B = top_B + colliderBTransform.h;

	// Check if they overlap horizontally.
	bool xOverlap = left_A < right_B && right_A > left_B;

	// Check if they overlap vertically.
	bool yOverlap = top_A < bottom_B && bottom_A > top_B;

	return xOverlap && yOverlap;
}
