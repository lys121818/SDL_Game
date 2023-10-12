#pragma once
#include <SDL.h>
#include "Vector2.h"

class ColliderComponent;
class GameObject
{
public:
	virtual ~GameObject() {}

	// Gets called by the main loop each frame to update this object's state.
	virtual void Update(double deltatime) {}

	// Gets called by the main loop each frame to render this object.
	virtual void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) {}

	// Return Name of the Texture
	virtual const char* GetTextureName() { return "UnNamed"; }

	// Return Name of the object
	virtual const char* GetName() { return "UnNamed"; }


	// Callbeck for when a collision occurs.
	virtual void OnCollision(ColliderComponent* pCollider) {}

	// Return transform of object
	virtual SDL_Rect GetTransform() = 0;
};