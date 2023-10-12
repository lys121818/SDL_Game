#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Type.h"

class GameObject;
class CollisionReferee;
////////////////////////////////////////////////////////////////////////////
// An anti-aligened bounding box (AABB) collider.
////////////////////////////////////////////////////////////////////////////
class ColliderComponent
{
private:
	Type m_type;
	// Pointer to GameObject that owns this collider.
	GameObject* m_pOwner;

	// Poisition and dimensions.
	SDL_Rect m_transform;

	Vector2 m_position;

	// Pointer to referee for registering and collision checking.
	CollisionReferee* m_pReferee;
public:
	ColliderComponent(GameObject* pOwner, SDL_Rect transform, CollisionReferee* pReferee, Type type);
	~ColliderComponent();

	// Return pointer to this collider's owner.
	GameObject* GetOwner() { return m_pOwner; }

	// Return position and dimensions.
	SDL_Rect GetTransform() { return m_transform; }

	// Return Type of the collider
	Type GetType() { return m_type; }

	// Updates position.
	void SetPosition(Vector2 newPosition);

	// Updates size
	void SetSize(Vector2 newSize);
	// Attempts to move by the given amount.
	// Return whether the collision was successful.
	bool TryMove(Vector2 deltaPosition);

	// Check for collision Check
	bool CollisionCheck();

	// Draw colliderbox for test purpose
	void DrawColliderBox(SDL_Renderer* pRenderer);
};

