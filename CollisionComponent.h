#pragma once
#include <SDL.h>
#include "Vector2.h"

class GameObject;
class CollisionReferee;

class CollisionComponent
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
	CollisionComponent(GameObject* pOwner, SDL_Rect transform, CollisionReferee* pReferee);
	~CollisionComponent();
};

