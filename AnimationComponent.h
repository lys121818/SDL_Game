#pragma once
#include <SDL.h>
#include <string>
#include <map>
class AnimationComponent
{
private:
	struct AnimationSequence
	{
	public:
		std::string m_name;
		int m_firstFrame;
		int m_lastFrame;
	};
private:
	const double m_kFrameRate;	// how fast the animation goes

	int m_numSpriteSheetColums;	// how manay frames in a single row

	SDL_Texture* m_pSpriteSheet;	// the sprite sheet itself

	SDL_Rect m_transform;		// object's location on screen

	SDL_Rect m_sourceTransform;	// area of the sprite to render

	std::map<std::string, AnimationSequence> m_allAnimations;

	std::string m_currentSequenceName;

	int m_currentFrame;

	double m_frameTime;

public:
	AnimationComponent(const char* pSpriteSheetPath, double frameRate, int frameWidth, int frameHeight, int frameCount, SDL_Renderer* pRenderer);
	~AnimationComponent();

	void AddAnimationSequence(std::string name, int firstFrame, int lastFrame);

	void PlayAnimation(std::string sequenceName);

	void ResetFrameTime();

	void UpdateSourceTransform();

	void Update(double deltaTime);

	void Render(SDL_Renderer* pRenderer);
};

