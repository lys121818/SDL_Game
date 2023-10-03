#include "AnimationComponent.h"
#include "SDL_image.h"
#include <iostream>
AnimationComponent::AnimationComponent(const char* pSpriteSheetPath, 
	double frameRate, int frameWidth, int frameHeight, 
	int frameCount, SDL_Renderer* pRenderer)
	: m_kFrameRate(frameRate),
	  m_pSpriteSheet(nullptr),
	  m_currentFrame(-1)
{
	// Attemp to load the image to a surface.
	SDL_Surface* pSpriteSheetSurface = IMG_Load(pSpriteSheetPath);
	// Error check
	if (pSpriteSheetPath == nullptr)
	{
		std::cout << " Image loading failed Error: " << SDL_GetError() << std::endl;
	}

	// Calculate the number of colums.
	m_numSpriteSheetColums = pSpriteSheetSurface->w / frameWidth;

	// Initialize the tansform.
	m_transform.x = 0;
	m_transform.y = 0;
	m_transform.w = frameWidth;
	m_transform.h = frameHeight;

	// Initialize the source transform.
	m_sourceTransform = m_transform;

	// Create the texture.
	m_pSpriteSheet = SDL_CreateTextureFromSurface(pRenderer, pSpriteSheetSurface);
	// Error check
	if (m_pSpriteSheet == nullptr)
	{
		std::cout << " Texture loading failed Error: " << SDL_GetError() << std::endl;
	}

	// Free the surface.
	SDL_FreeSurface(pSpriteSheetSurface);

	ResetFrameTime();
}

AnimationComponent::~AnimationComponent()
{
	// Destory the texture.
	SDL_DestroyTexture(m_pSpriteSheet);
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
	//  
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

void AnimationComponent::Render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, m_pSpriteSheet, &m_sourceTransform, &m_transform);
}
