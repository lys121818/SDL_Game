#pragma once
#include <vector>

class ColliderComponent;
////////////////////////////////////////////////////////////////////////////
// Maintains references to all colliders and checks their collisions.
////////////////////////////////////////////////////////////////////////////
class CollisionReferee
{
private:
	// All currently active colliders.
	std::vector<ColliderComponent*> m_activeColliders;
public:
	CollisionReferee();
	~CollisionReferee();

	// Register a new collider.
	void AddActiveCollider(ColliderComponent* pCollider);

	// Unregister a collider.
	void RemoveActiveCollider(ColliderComponent* pCollider);

	// Finds all colliders that overlap and notify them of any collision.
	// Returns whether or not a collision occurred.
	bool CheckForCollisionAndNotify(ColliderComponent* pColliderToCheck);

	//Check if the object collision with collider
	bool CheckForColliderAndNotify(ColliderComponent* pColliderToCheck);
};

