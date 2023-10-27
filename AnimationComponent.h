#pragma once
#include <SDL.h>
#include <string>
#include <map>

//==================================================================================================//
/// ANIMATION COMPONENT
/// This is the Component for GameObject to Create sequence of animation from the sprtie sheet 
/// and render the current animation it's supposed to appear on the screen
//==================================================================================================//


class AnimationComponent
{
private:
	// Struct for animation
	struct AnimationSequence
	{
	public:
		std::string m_name;
		int m_firstFrame;
		int m_lastFrame;
	};

private:
	// Speed of the animation play
	const double m_kFrameRate;	

	// Frames in a single row
	int m_numSpriteSheetColums;

	// Object's location on screen
	SDL_Rect* m_transform;		

	// Area of the sprite to render
	SDL_Rect m_sourceTransform;	

	// Sequence
	std::map<std::string, AnimationSequence> m_allAnimations;
	std::string m_currentSequenceName;

	// Frame
	int m_currentFrame;
	double m_frameTime;

public:
	AnimationComponent(
		const char* pSpriteSheetPath,	// Location of the Sprite Sheet
		double frameRate, 
		int frameWidth, int frameHeight,
		SDL_Rect* transform				// GameObject's Transform information
	);
	~AnimationComponent();

	void Update(double deltaTime);

	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture, bool isRight);

	void AddAnimationSequence(std::string name, int firstFrame, int lastFrame);

	void PlayAnimation(std::string sequenceName);

	void ResetFrameTime();

	void UpdateSourceTransform();

};

