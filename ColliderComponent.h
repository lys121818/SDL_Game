#pragma once
#include <SDL.h>
#include "Vector2.h"


//==================================================================================================//
/// COLLIDER COMPONENT
/// This is the Component for GameObject to have collider box of its own.
//==================================================================================================//

/// FORWARD DECLARE
class GameObject;
class CollisionReferee;

class ColliderComponent
{

private:

	// Pointer to GameObject that owns this collider.
	GameObject* m_pOwner;

	// Poisition and dimensions.
	SDL_Rect m_transform;

	Vector2 m_position;

	// Pointer to referee for registering and collision checking.
	CollisionReferee* m_pReferee;

public:
	ColliderComponent(
		GameObject* pOwner,
		SDL_Rect transform,				// GameObject Transform
		CollisionReferee* pReferee
	);
	~ColliderComponent();

	// Return pointer to this collider's owner.
	GameObject* GetOwner() { return m_pOwner; }

	// Return position and dimensions.
	SDL_Rect GetTransform() { return m_transform; }

	// Updates position.
	void SetPosition(Vector2 newPosition);

	// Updates size
	void SetSize(Vector2 newSize);

	// Attempts to move by the given amount.
	// Return whether the collision was successful.
	bool TryMove(Vector2 deltaPosition);

	// Check for collision Check
	bool CollisionCheck(ColliderComponent* collider);

	// Draw colliderbox for test purpose
	void DrawColliderBox(SDL_Renderer* pRenderer);

	// Set Collision box active or disactive
	void SetCollider(bool isActive);
};

