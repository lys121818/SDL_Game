#pragma once
#include <SDL.h>
#include "Vector2.h"

class ImageObject;

class ImageActionComponent
{
public:
	enum class ActionState
	{
		kNormal,
		kPoping
	}m_actionState;
private:
	ImageObject* m_pOwner;

	Vector2 m_OwnerSize;

	Vector2 m_currentSize;

	SDL_Rect* m_OwnerTransform;

public:
	ImageActionComponent(ImageObject* pOwner, SDL_Rect* transform);
	~ImageActionComponent();

	void Update(double deltaTime);

	void SetAction(ActionState action);

private:
	void UpdateImageAction(double deltaTime);
};

