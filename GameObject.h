#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Status.h"

class ColliderComponent;

class GameObject
{
public:
	virtual ~GameObject() {}

	// Gets called by the main loop each frame to update this object's state.
	virtual void Update(double) {}

	// Gets called by the main loop each frame to render this object.
	virtual void Render(SDL_Renderer*, SDL_Texture*) {}


	// Callback for when a collision occurs.
	virtual void OnCollision(ColliderComponent*) {}

	virtual void OnOverlapBegin(ColliderComponent*) {}

	virtual void OnOverlapUpdate() {}

	virtual void OnOverlapEnd() {}

	virtual void TryMove(Vector2<double>) {}

	// Handles this even in the context of this object
	virtual void HandleEvent(SDL_Event*) {}


	//GETTERS
	// Return Name of the Texture
	virtual const char* GetTextureName() { return "UnNamed"; }

	// Return Name of the object
	virtual const char* GetName() { return "UnNamed"; }

	// Return the Status of the gameobject
	virtual Status GetStatus() { return Status(); }

	// Return transform of object
	virtual SDL_Rect GetTransform() { return SDL_Rect(); }

	// Get if the game object is active in game (dead/destroy or live)
	virtual bool GetActive() { return true; }

	// SETTERS

	virtual void SetPosition(Vector2<double>) {}

	virtual void SetTargetObject(GameObject*) {}

	virtual void Damaged(int) {}

	virtual void SetActive(bool) {}

	virtual void SetHealth(int) {}

private:
	virtual void AddSound(const char*, const char*) {}
};