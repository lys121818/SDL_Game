#pragma once
#include <SDL.h>
#include <string>
#include <map>
#include "Vector2.h"
#include <functional>

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

		// size of sprite frame
		Vector2<int> m_size{0,0};

		// x is col count and row is starting row
		Vector2<int> m_colRows;

		// multiply to actual rendering size
		float m_timesToWidthSize;

		int m_maxFrame;

		bool m_isLoop;
	};

private:
	// Speed of the animation play
	const double m_kFrameRate;	

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

	std::function<void()> m_callback;

public:
	AnimationComponent(
		const char* pSpriteSheetPath,	// Location of the Sprite Sheet
		double frameRate, 
		SDL_Rect* transform				// GameObject's Transform information
	);
	~AnimationComponent();

	void Update(double deltaTime);

	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture, bool isRight);

	void AddAnimationSequence(std::string name, Vector2<int> size, Vector2<int> colRow, int maxFrame, float widthMultyplier = 1.0, bool isLoop = true);

	void PlayAnimation(std::string sequenceName);

	void ResetFrameTime();

	void SetCallback(std::function<void()> func) { m_callback = func; }

	void UpdateSourceTransform();

};

