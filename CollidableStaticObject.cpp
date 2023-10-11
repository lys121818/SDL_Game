#include "CollidableStaticObject.h"


CollidableStaticObject::CollidableStaticObject(SDL_Rect transform, CollisionReferee* pReferee, const char* name)
    :m_transform(transform),
     m_name(name),
     m_collider(this,transform,pReferee),
     m_image(name, &m_transform)
{
}

CollidableStaticObject::~CollidableStaticObject()
{
}

void CollidableStaticObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
    m_image.Render(pRenderer, pTexture);
}
