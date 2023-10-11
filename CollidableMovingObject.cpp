#include "CollidableMovingObject.h"
#include <iostream>

CollidableMovingObject::CollidableMovingObject(SDL_Rect transform, CollisionReferee* pReferee, const char* name)
	:m_name(name),
	 m_transform(transform),
	 m_collider(this,transform,pReferee),
	 m_image(name,&m_transform)
{
}

CollidableMovingObject::~CollidableMovingObject()
{
}

void CollidableMovingObject::Update(double deltatime)
{

}

void CollidableMovingObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	m_image.Render(pRenderer, pTexture);
}

void CollidableMovingObject::OnCollision(ColliderComponent* pCollider)
{
	// TODO
	const char* colliderName = pCollider->GetOwner()->GetName();
	std::cout << "Collided with " << colliderName << std::endl;
}

// Attempts to move this object.
bool CollidableMovingObject::TryMove(Vector2 deltaPosition)
{
	// Have the collider component try to move.
	bool didMove = m_collider.TryMove(deltaPosition);

	// If the collider successfully moved, update all components.
	if (didMove)
	{
		m_transform.x += deltaPosition.m_x;
		m_transform.y += deltaPosition.m_y;
	}

	// Return whether the movement was successful.
	return didMove;
}
