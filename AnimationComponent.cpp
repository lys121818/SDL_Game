#include "AnimationComponent.h"
#include "SDL_image.h"
#include <iostream>

AnimationComponent::AnimationComponent(const char* pSpriteSheetPath, double frameRate, int frameWidth, int frameHeight, SDL_Rect* transform)
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
	m_sourceTransform.w = frameWidth;
	m_sourceTransform.h = frameHeight;

	// Calculate the number of colums.
	m_numSpriteSheetColums = IMG_Load(pSpriteSheetPath)->w / frameWidth;

	// Reset on build
	ResetFrameTime();
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::AddAnimationSequence(std::string name, int firstFrame, int lastFrame)
{
	// Create animation sequence.
	m_allAnimations[name] = AnimationSequence{ name, firstFrame,lastFrame };
}

void AnimationComponent::PlayAnimation(std::string sequenceName)
{
	// If this particular sequencce is already playing or hasn't been added, skip.
	if (sequenceName == m_currentSequenceName ||
		m_allAnimations.find(sequenceName) == m_allAnimations.end())
	{
		return;
	}

	// Access the sequence with this name and set its first frame.
	AnimationSequence& newSequence = m_allAnimations[sequenceName];

	m_currentFrame = newSequence.m_firstFrame;


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
	int frameX = m_currentFrame % m_numSpriteSheetColums;
	int frameY = m_currentFrame / m_numSpriteSheetColums;

	m_sourceTransform.x = frameX * m_sourceTransform.w;
	m_sourceTransform.y = frameY * m_sourceTransform.h;


}

void AnimationComponent::Update(double deltaTime)
{

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
