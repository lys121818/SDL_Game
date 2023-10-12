#include "CollidableMovingObject.h"
#include <iostream>

CollidableMovingObject::CollidableMovingObject(SDL_Rect transform, CollisionReferee* pReferee, const char* name)
	:m_pSpriteName(name),
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
	// Show right action of this object when it collide or collision with other object
	// Will it get Name? 
	// Should I tag each object with string?


	// Get name from collider which had collision with owner object
	const char* colliderName = pCollider->GetOwner()->GetTextureName();
	// Print the name of the object which is collision with.
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
