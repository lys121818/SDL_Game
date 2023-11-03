#include "ImageActionComponent.h"
#include "MovingComponent.h"
#include "ImageObject.h"
#include "Defines.h"

ImageActionComponent::ImageActionComponent(ImageObject* pOwner, SDL_Rect* transform)
	:
	m_pOwner(pOwner),
	m_OwnerTransform(transform)
{
	m_OwnerSize = Vector2{ (double)transform->w,(double)transform->h };
	m_currentSize = Vector2{ 0,0 };

	m_actionState = ActionState::kNormal;
}

ImageActionComponent::~ImageActionComponent()
{
}

void ImageActionComponent::Update(double deltaTime)
{
	UpdateImageAction(deltaTime);
}

void ImageActionComponent::SetAction(ActionState action)
{
	switch (action)
	{
	case ImageActionComponent::ActionState::kNormal:
	{
		break;
	}
	case ImageActionComponent::ActionState::kPoping:
	{
		m_actionState = ActionState::kPoping;

		// Set position to middle of the image placement
		m_OwnerTransform->x = (int)(m_OwnerSize.m_x / 2);
		m_OwnerTransform->y = (int)(m_OwnerSize.m_y / 2);

		// Set size to 0
		m_currentSize = Vector2{ 0,0 };

		m_OwnerTransform->w = 0;
		m_OwnerTransform->h = 0;

		break;
	}
	default:
		break;
	}


}

void ImageActionComponent::UpdateImageAction(double deltaTime)
{
	switch (m_actionState)
	{
		case ActionState::kNormal:
		{

			break;
		}
		case ActionState::kPoping:
		{
			Vector2 deltaSize;

			deltaSize.m_x = m_OwnerSize.m_x * deltaTime;
			deltaSize.m_y = m_OwnerSize.m_y * deltaTime;

			// Set poping false when it's done
			if (m_OwnerTransform->w > m_OwnerSize.m_x || m_OwnerTransform->h > m_OwnerSize.m_y)
			{
				m_actionState = ActionState::kNormal;
				return;
			}

			m_currentSize.m_x += deltaSize.m_x;
			m_currentSize.m_y += deltaSize.m_y;


			// delta position = speed * delta time (speed is going to be size of the image
			// increase size

			//// Set size by increasing delta value size
			m_OwnerTransform->w = (int)m_currentSize.m_x;
			m_OwnerTransform->h = (int)m_currentSize.m_y;



			break;
		}
	default:
		break;
	}


}
