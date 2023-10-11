#pragma once
#include <SDL.h>
#include "Vector2.h"

class GameObject;
class CollisionReferee;
////////////////////////////////////////////////////////////////////////////
// An anti-aligened bounding box (AABB) collider.
////////////////////////////////////////////////////////////////////////////
class ColliderComponent
{
private:
	// Pointer to GameObject that owns this collider.
	GameObject* m_pOwner;

	// Poisition and dimensions.
	SDL_Rect m_transform;

	// Pointer to referee for registering and collision checking.
	CollisionReferee* m_pReferee;
public:
	ColliderComponent(GameObject* pOwner, SDL_Rect transform, CollisionReferee* pReferee);
	~ColliderComponent();

	// Return pointer to this collider's owner.
	GameObject* GetOwner() { return m_pOwner; }

	// Return position and dimensions.
	SDL_Rect GetTransform() { return m_transform; }

	// Updates position.
	void SetPosition(Vector2 newPosition);

	// Attempts to move by the given amount.
	// Return whether the collision was successful.
	bool TryMove(Vector2 deltaPosition);
};

