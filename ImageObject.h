#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "ImageComponent.h"
#include "ColliderComponent.h"
#include "CollisionReferee.h"
#include "MovingComponent.h"
#include "ImageActionComponent.h"

class ImageActionComponent;

class ImageObject : public GameObject
{
	static constexpr int s_kSpeed = 50;

	Status m_status;

	// Name Of the Object
	const char* m_pSpriteName;

	// Transform of the object
	SDL_Rect m_transform;

	// Image Component
	ImageComponent m_imageComponent;

	// Moving Component
	MovingComponent m_movingComponent;

	ColliderComponent m_collider;

	ImageActionComponent m_imageAction;

public:
	ImageObject(Vector2 position, Vector2 size, CollisionReferee* pReferee, const char* directory, const int index = 0, size_t type = 0, const char* name = "UnNamed");
	~ImageObject();



	// Inherited via GameObject
	// Update

	void Update(double deltaTime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

	// Move to the direction
	void TryMove(const Vector2& direction,const int& speed = s_kSpeed);

	// GETTERS
	SDL_Rect GetTransform() override { return m_transform; }

	const char* GetTextureName() override { return m_pSpriteName; }

	// Return Name of the object
	virtual const char* GetName() { return "UnNamed"; }

	virtual Status GetStatus() override { return m_status; }

	ImageActionComponent::ActionState GetActionState() { return m_imageAction.m_actionState; }

	// SETTERS
	virtual void SetPosition(Vector2 position) override;

	void SetTransform(SDL_Rect transform) { m_transform = transform; }

	void SetAction(ImageActionComponent::ActionState state);

private:
	void SetImage(const int index);

};

