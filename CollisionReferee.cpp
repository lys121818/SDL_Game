#include "CollisionReferee.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Defines.h"
#include "GameSetting.h"

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

bool CollisionReferee::CheckForColliderAndNotify(ColliderComponent* pColliderToCheck)
{
	// Allocate a bool for whether any collisions have occurred.
	bool didCollide = false;

	// Check agains every active collider.
	for (ColliderComponent* pOtherCollider : m_activeColliders)
	{
		// Make sure we don't check a collider vs itself.
		if (pColliderToCheck == pOtherCollider)
			continue;
		

		//if we overlap
		if (AABBCollisionCheck(pColliderToCheck, pOtherCollider))
		{
			//if this collider or the other collider is passable
			if (pColliderToCheck->GetOwner()->GetStatus().m_type >= COLLISIONINDEX ||	// this collider is passable
				pOtherCollider->GetOwner()->GetStatus().m_type >= COLLISIONINDEX)		// other collider is passable
			{
				//if the pColliderToCheck did not collide with pOtherCollider previously
				if (pColliderToCheck->GetOwner()->GetStatus().m_pTargetCollider != pOtherCollider)
				{
					//call OnOverlapBegin
					pColliderToCheck->GetOwner()->OnOverlapBegin(pOtherCollider);
					pOtherCollider->GetOwner()->OnOverlapBegin(pColliderToCheck);
				}
				//else
					//call OnOverlapUpdate        	
				else
				{
					pColliderToCheck->GetOwner()->OnOverlapUpdate();
					pOtherCollider->GetOwner()->OnOverlapUpdate();
				}
			}
			//else
				//call OnCollision function
			else
			{
				pColliderToCheck->GetOwner()->OnCollision(pOtherCollider);
				pOtherCollider->GetOwner()->OnCollision(pColliderToCheck);
				didCollide = true;
			}

		}
		//else if no overlap
		else if (!AABBCollisionCheck(pColliderToCheck, pOtherCollider))
		{
			//if this collider or the other collider is passable
			if (pColliderToCheck->GetOwner()->GetStatus().m_type >= COLLISIONINDEX ||	// this collider is passable
				pOtherCollider->GetOwner()->GetStatus().m_type >= COLLISIONINDEX)		// other collider is passable
			{
				//if the pColliderToCheck did collide with pOtherCollider previously
				if (pColliderToCheck->GetOwner()->GetStatus().m_pTargetCollider == pOtherCollider)
				{
					//call OnOverlapEnd
					pColliderToCheck->GetOwner()->OnOverlapEnd();
					pOtherCollider->GetOwner()->OnOverlapEnd();
				}
			}
		}

	}

	// Return whether any collision occurred.
	return didCollide;
}

bool CollisionReferee::AABBCollisionCheck(ColliderComponent* colliderA, ColliderComponent* colliderB)
{
	// Get collider A transform
	SDL_Rect colliderATransform = colliderA->GetTransform();
	int left_A = colliderATransform.x;
	int right_A = left_A + colliderATransform.w;
	int top_A = colliderATransform.y;
	int bottom_A = top_A + colliderATransform.h;

	// Get collider B transform
	SDL_Rect colliderBTransform = colliderB->GetTransform();
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

// Collision Between circles
bool CollisionReferee::CircleCollisionCheck(ColliderComponent* colliderA, ColliderComponent* colliderB)
{
	SDL_Rect circleA, circleB;

	circleA = colliderA->GetTransform();
	circleB = colliderB->GetTransform();

	// Radius
	float radiusA, radiusB;

	radiusA = (float)circleA.w / 2.0f;
	radiusB = (float)circleB.w / 2.0f;

	// Set Position dot to middle of the object
	circleA.x += (int)radiusA;
	circleA.y += (int)radiusA;

	circleB.x += (int)radiusB;
	circleB.y += (int)radiusB;

	// Distance between
	float distanceBetweenObjects =
	(float)(circleB.x - circleA.x) * (float)(circleB.x - circleA.x) +	// circles.x^2
	(float)(circleB.y - circleA.y) * (float)(circleB.y - circleA.y);	// circles.y^2

	// On Collision
	if (distanceBetweenObjects < (radiusA + radiusB) * (radiusA + radiusB))
	{
		return true;
	}

	return false;
}
