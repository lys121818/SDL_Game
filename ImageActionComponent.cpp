#include "ImageActionComponent.h"
#include "MovingComponent.h"
#include "ImageObject.h"
#include "Defines.h"

ImageActionComponent::ImageActionComponent(SDL_Rect* transform)
	:
	m_OwnerTransform(transform)
{
	m_OwnerSize = Vector2{ (double)transform->w,(double)transform->h };
	m_currentSize = Vector2{ 0,0 };
	m_currentPosition = Vector2{ 0,0 };
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

		Vector2 StartPosition;

		StartPosition.m_x = (int) (m_OwnerTransform->x + (m_OwnerSize.m_x / 2));
		StartPosition.m_y = (int) (m_OwnerTransform->y + (m_OwnerSize.m_y / 2));

		// Set position to middle of the image placement
		m_OwnerTransform->x = (int)StartPosition.m_x;
		m_OwnerTransform->y = (int)StartPosition.m_y;

		// Set size to 0
		m_currentSize = Vector2{ 0,0 };
		m_currentPosition = StartPosition;

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

			deltaSize.m_x = (m_OwnerSize.m_x / 2) * deltaTime;
			deltaSize.m_y = (m_OwnerSize.m_y / 2) * deltaTime;

			// Set poping false when it's done
			if (m_OwnerTransform->w > m_OwnerSize.m_x || m_OwnerTransform->h > m_OwnerSize.m_y)
			{
				m_actionState = ActionState::kNormal;
				return;
			}

			m_currentSize.m_x += deltaSize.m_x;
			m_currentSize.m_y += deltaSize.m_y;

			// Position decrease by half value of size increase
			m_currentPosition.m_x -= (deltaSize.m_x / 2);
			m_currentPosition.m_y -= (deltaSize.m_y / 2);

			// increase size
			//// Set size by increasing delta value size
			m_OwnerTransform->w = (int)m_currentSize.m_x;
			m_OwnerTransform->h = (int)m_currentSize.m_y;

			// change position
			m_OwnerTransform->x = (int)m_currentPosition.m_x;
			m_OwnerTransform->y = (int)m_currentPosition.m_y;


			break;
		}
	default:
		break;
	}


}
