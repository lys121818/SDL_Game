#pragma once
#include <SDL.h>
#include "Vector2.h"
class GameObject
{
public:
	virtual ~GameObject() {}

	// Gets called by the main loop each frame to update this object's state.
	virtual void Update(double deltatime) = 0;

	// Gets called by the main loop each frame to render this object.
	virtual void Render(SDL_Renderer* pRenderer) = 0;

	// Return transform of object
	virtual SDL_Rect GetTransform() = 0;
};

