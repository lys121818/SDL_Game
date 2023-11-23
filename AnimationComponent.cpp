#include "AnimationComponent.h"
#include "SDL_image.h"
#include <iostream>

AnimationComponent::AnimationComponent(const char* pSpriteSheetPath, double frameRate, SDL_Rect* transform)
	: 
	m_kFrameRate(frameRate),
	m_transform(transform)
{
	m_currentFrame = -1;	// Set current frame to unvalid value

	// SOURCE TRANSFORM
	// Position
	m_sourceTransform.x = m_transform->x;
	m_sourceTransform.y = m_transform->y;

	// Size
	m_sourceTransform.w = m_transform->w;
	m_sourceTransform.h = m_transform->h;

	// Reset on build
	ResetFrameTime();
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::AddAnimationSequence(std::string name, Vector2<int> size)
{
	// Create animation sequence.
	m_allAnimations[name] = AnimationSequence{ name, size};
}

void AnimationComponent::PlayAnimation(std::string sequenceName)
{
	// If this particular sequencce is already playing or hasn't been added, skip.
	if (sequenceName == m_currentSequenceName ||
		m_allAnimations.find(sequenceName) == m_allAnimations.end())
	{
		return;
	}

	m_currentFrame = 0;

	// Update current sequence name, frame time, and source transform.
	m_currentSequenceName = sequenceName;

	ResetFrameTime();

	UpdateSourceTransform();
}

void AnimationComponent::ResetFrameTime()
{
	// How many seconds the current frame.
	m_frameTime = 1. / m_kFrameRate;
}

void AnimationComponent::UpdateSourceTransform()
{
	//  Calculate Position of source transform from the sprite sheet
	Vector2<int> colAndRows = m_allAnimations[m_currentSequenceName].m_colRows;
	Vector2<int> size = m_allAnimations[m_currentSequenceName].m_size;

	// set rect animation to load
	m_sourceTransform.x = colAndRows.m_x * size.m_x;
	m_sourceTransform.y = colAndRows.m_y * size.m_y;
}

void AnimationComponent::Update(double deltaTime)
{
	// TODO: Working on animation 
	

	// See if an animation is playing.
	if (m_currentFrame == -1)
		return;

	// Access the current animation sequence.
	AnimationSequence& currentSequence = m_allAnimations[m_currentSequenceName];

	// Allocate a dirty flag to see if the frame number changes.
	bool frameIsDirty = false;

	// As long as delta time is large, update the frame.
	while (deltaTime > m_frameTime)
	{
		frameIsDirty = true;

		deltaTime -= m_frameTime;
		ResetFrameTime();

		//Check for loop
		if (currentSequence.m_lastFrame == m_currentFrame)	// if on the last frame
		{
			m_currentFrame = currentSequence.m_firstFrame;	// loop back to first frame
		}
		else
		{
			++m_currentFrame;
		}

	}
	// After the frame has been updated, subtract delta time.
	m_frameTime -= deltaTime;

	// If the frame is dirty, update source transform. 
	if (frameIsDirty)
	{
		UpdateSourceTransform();
	}
}

// Have Set the default value to Right
void AnimationComponent::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture,bool isRight)
{
	// Render sprite sheet according to direction Object is facing at
	if (isRight)
	{
		SDL_RenderCopy(pRenderer, pTexture, &m_sourceTransform, m_transform);
	}
	else
	{
		SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
		SDL_RenderCopyEx(pRenderer, pTexture, &m_sourceTransform, m_transform, double(0.0), nullptr, flip);
	}
}
