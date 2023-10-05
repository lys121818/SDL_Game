#pragma once
#include "GameObject.h"
#include "Defines.h"
#include "Vector2.h"
#include "AnimationComponent.h"

class CubeColider : public GameObject
{
    enum AnimationState
    {
        idle,
        walk,
        run,
        jump,
        slide
    } m_currentState;
private:
    // Width
    static constexpr int s_kWidth = 100;
    // Height
    static constexpr int s_kHeight = 150;
    // Speed
    static constexpr int s_kMaxSpeed = 500;
    static constexpr int s_kSpeed = 300;
    static constexpr int s_kMixSpeed = 100;

    // Name Of the Object
    const char* m_pName;
    // Current Speed
    double m_speed = 300;
    // Current position
    Vector2 m_position;

    // Current direction movement. -1 for left, 1for right.
    int m_directionX;
    // Current direction movement. -1 for down, 1 for up.
    int m_directionY;

    // AnimationComponent to play animation
    AnimationComponent m_animation;

    // Current Animation States
    // SDL
    // Transform of the object
    SDL_Rect m_transform;
private:
    // Play the right animation fallowing current state of gameobject
    void AnimationState();
    // Check current state before play animation.
    void CheckCurrentState();


public:
    CubeColider(Vector2 position, const char* directory, SDL_Renderer* pRenderer);
    ~CubeColider();
    

    // Inherited via GameObject
    void Update(double deltatime) override;

    void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;


    //GETTER
    // return position of object
    Vector2 GetPosition() { return m_position; }
    // return the transform of object
    SDL_Rect GetTransform() override { return m_transform; }
    // Return Name of the object
    const char* GetName() override { return m_pName; }
    // return animantion component
    AnimationComponent* GetAnimationComponent() { return &m_animation; }

    //SETTER
    // Change the position of the object 
    void SetPosition(Vector2 position);

    // Moving
    // Sprint
    void SprintSpeed() { m_speed = s_kMaxSpeed; }
    void NormalSpeed() { m_speed = s_kSpeed; }
    void SlowSpeed() { m_speed = s_kMixSpeed; }

    void MoveLeft() { --m_directionX; }
    void MoveRight() { ++m_directionX; }
    void MoveUp() { --m_directionY; }
    void MoveDown() { ++m_directionY; }

    void StopLeft() { ++m_directionX; }
    void StopRight() { --m_directionX; }
    void StopUp() { ++m_directionY; }
    void StopDown() { --m_directionY; }

};

