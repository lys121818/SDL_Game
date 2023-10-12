#pragma once
#include "GameObject.h"
#include "ColliderComponent.h"
#include "ImageComponent.h"
/////////////////////////////////////////////
// A non-moving object with collider.
/////////////////////////////////////////////

class CollidableStaticObject : public GameObject
{
private:
	// Name of image
	const char* m_pSpriteName;

	// Position and dimensions.
	SDL_Rect m_transform;

	// Collider component for checking.
	ColliderComponent m_collider;


	// Image component
	ImageComponent m_image;

public:
	CollidableStaticObject(SDL_Rect transform,CollisionReferee* pReferee, const char* name);
	~CollidableStaticObject();

	// Return Name of the object
	virtual const char* GetTextureName() { return m_pSpriteName; }

	// Return Name of the object
	virtual const char* GetName() { return "UnNamed"; }

	// Gets called by the main loop each frame to render this object.
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

	SDL_Rect GetTransform() override { return m_transform; }

};

