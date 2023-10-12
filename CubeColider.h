#pragma once
#include "GameObject.h"
#include "Defines.h"
#include "Vector2.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"

class CubeColider : public GameObject
{
private:
    struct PlayerStatus
    {
    public:
        std::string m_name; // Player Name
        int m_health;       // Player Health
        double m_speed;     // Player Speed
        bool m_isRight;     // side player is facing
    };
    // Current Animation States
    enum AnimationState
    {
        m_idle,
        m_walk,
        m_run,
        m_jump,
        m_slide
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
    const char* m_pSpriteName;
    // Current Speed
    double m_speed = 300;
    // Current position
    Vector2 m_position;

    // Current direction movement. -1 for left, 1for right.
    int m_directionX;
    // Current direction movement. -1 for down, 1 for up.
    int m_directionY;

    // The direction object is facing
    bool m_isRight;
    // AnimationComponent to play animation
    AnimationComponent m_animation;

    ColliderComponent m_collider;
    // SDL
    // Transform of the object
    SDL_Rect m_transform;
private:
    // Play the right animation fallowing current state of gameobject
    void AnimationState();
    // Check current state before play animation.
    void CheckCurrentState();

public:
    CubeColider(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, SDL_Renderer* pRenderer);
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
    const char* GetTextureName() override { return m_pSpriteName; }

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

private:
    bool TryMove(Vector2 deltaPosition);

};

