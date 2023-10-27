#pragma once
#include <vector>
#include <SDL.h>

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

	//Check if the object collision with collider
	bool CheckForColliderAndNotify(ColliderComponent* pColliderToCheck);

	bool AABBCollisionCheck(ColliderComponent* colliderA, ColliderComponent* colliderB);

	bool CircleCollisionCheck(ColliderComponent* colliderA, ColliderComponent* colliderB);
};

