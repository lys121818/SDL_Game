#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "TextComponent.h"
#include "MovingComponent.h"
#include "ImageActionComponent.h"


class TextObject : public GameObject
{
	static constexpr int s_kSpeed = 50;
private:
	SDL_Rect m_transform;

	TextComponent m_textComponent;

	MovingComponent m_movingComponent;

	Status m_status;

	ImageActionComponent m_imageAction;

	TTF_Font* m_pFont;

	SDL_Color m_color;

	SDL_Renderer* m_pRenderer;



public:
	TextObject(Vector2<double> position, TTF_Font* pFont, SDL_Color color, SDL_Renderer* pRenderer);
	~TextObject();


	void Update(double deltaTime) override;

	void Render(SDL_Renderer* pRenderer);

	virtual void TryMove(Vector2<int> direction) override;

	void SetText(const char* pText);

	void SetSpeed(int speed) { m_status.m_speed = speed; }

	ImageActionComponent::ActionState GetActionState() { return m_imageAction.m_actionState; }

	void SetAction(ImageActionComponent::ActionState state) { m_imageAction.SetAction(state); }

	// Inherited via GameObject
	Status GetStatus() override { return m_status; }

	SDL_Rect GetTransform() override { return m_transform; }

};

