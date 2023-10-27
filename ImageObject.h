#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "ImageComponent.h"
#include "ColliderComponent.h"
#include "CollisionReferee.h"
#include "MovingComponent.h"
class ImageObject : public GameObject
{
	Status m_status;
	// Speed of object
	static constexpr int s_kSpeed = 50;

	// Name Of the Object
	const char* m_pSpriteName;

	// Transform of the object
	SDL_Rect m_transform;

	// Image Component
	ImageComponent m_imageComponent;

	// Moving Component
	MovingComponent m_movingComponent;

	ColliderComponent m_collider;

public:
	ImageObject(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, const int index, size_t type, const char* name = "UnNamed");
	~ImageObject();



	// Inherited via GameObject
	// Update

	void Update(double deltaTime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

	// Move to the direction
	void TryMove(Vector2 direction);

	// GETTERS
	SDL_Rect GetTransform() override { return m_transform; }

	const char* GetTextureName() override { return m_pSpriteName; }

	// Return Name of the object
	virtual const char* GetName() { return "UnNamed"; }

	virtual Status GetStatus() override { return m_status; }


	// SETTERS
	virtual void SetPosition(Vector2 position) override;


private:
	void SetImage(const int index);

};

