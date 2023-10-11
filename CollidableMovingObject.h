#pragma once
#include "GameObject.h"
#include "ColliderComponent.h"
#include "ImageComponent.h"
///////////////////////////////////////////////////////////////
// A moving object with collider.
///////////////////////////////////////////////////////////////
class CollidableMovingObject : public GameObject
{
private:
	// Name of image
	const char* m_name;

	// Position and dimensions.
	SDL_Rect m_transform;

	// Collider component for checking.
	ColliderComponent m_collider;

	// Image component
	ImageComponent m_image;
public:
	CollidableMovingObject(SDL_Rect transform, CollisionReferee* pReferee, const char* name);
	~CollidableMovingObject();

	// Gets called by the main loop each frame to update this object's state.
	void Update(double deltatime) override;

	// Gets called by the main loop each frame to render this object.
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

	// Return Name of the object
	virtual const char* GetName() { return m_name; }

	// Callbeck for when a collision occurs.
	virtual void OnCollision(ColliderComponent* pCollider) override;

	// Attempts to move this object.
	bool TryMove(Vector2 deltaPosition);

	SDL_Rect GetTransform() override { return m_transform; }
};

