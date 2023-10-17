#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "ImageComponent.h"
#include "ColliderComponent.h"
#include "CollisionReferee.h"
class ImageObject : public GameObject
{
	Status m_status;

	// Name Of the Object
	const char* m_pSpriteName;
	// Transform of the object
	SDL_Rect m_transform;

	// Position
	Vector2 m_position;

	// Image Component
	ImageComponent m_imageComponent;

	ColliderComponent m_collider;

public:
	ImageObject(Vector2 position, CollisionReferee* pReferee, int width, int height, const char* directory, const int index, Type type);
	~ImageObject();
	// Inherited via GameObject
	void Update(double deltaTime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

	// GETTER
	SDL_Rect GetTransform() override { return m_transform; }

	const char* GetTextureName() override { return m_pSpriteName; }

	// Return Name of the object
	virtual const char* GetName() { return "UnNamed"; }

	// return current position of object
	Vector2 GetPosition() { return m_position; }

	virtual Status GetStatus() override { return m_status; }

private:
	void SetImage(const int index);

};

