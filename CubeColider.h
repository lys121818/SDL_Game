#pragma once
#include "GameObject.h"
#include "Defines.h"
#include "GameSetting.h"
#include "Vector2.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
class CubeColider : public GameObject
{
private:

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
    static constexpr int s_kWidth = (int)PLAYERWIDTH;

    // Height
    static constexpr int s_kHeight = (int)PLAYERHEIGHT;

    // Speed
    static constexpr int s_kMaxSpeed = (int)PLAYERMAXSPEED;
    static constexpr int s_kSpeed    = (int)PLAYERSPEED;
    static constexpr int s_kMixSpeed = (int)PLAYERMINSPEED;

    // Health
    static constexpr int s_KMaxHealth = PLAYERMAXHEALTH;

    // Immune system time
    static constexpr int s_kMaxImmuneTime= IMMUNETIME;

    // true when Game Over
    bool m_isGame;

    // Name Of the Object
    const char* m_pSpriteName;

    // Current Speed
    double m_speed;

    // Immune Time
    double m_immuneTime;

    // Current player Health
    int m_health;

    // Current position
    Vector2 m_position;

    // Current direction.x movement. -1 for left, 1for right.
    // Current direction.y movement. -1 for down, 1 for up.
    Vector2 m_direction;

    // The direction object is facing
    bool m_isRight;

    // True if it's on collision
    bool m_isOnCollision;

    // Player Immune time
    bool m_isImmune;


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
    CubeColider(SDL_Rect transform, CollisionReferee* pReferee, const char* directory, SDL_Renderer* pRenderer, Type type);
    ~CubeColider();
    

    // Inherited via GameObject
    void Update(double deltaTime) override;
    void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

    // On Collision action
    virtual void OnCollision(ColliderComponent* pCollider);

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

    //void SetTrigger(bool isTrigger) { m_isOnCollision = isTrigger; }
    // Moving
    // Sprint
    void SprintSpeed() { m_speed = s_kMaxSpeed; }
    void NormalSpeed() { m_speed = s_kSpeed; }
    void SlowSpeed() { m_speed = s_kMixSpeed; }

    void MoveLeft() { --m_direction.m_x; }
    void MoveRight() { ++m_direction.m_x; }
    void MoveUp() { --m_direction.m_y; }
    void MoveDown() { ++m_direction.m_y; }

    void StopLeft() { ++m_direction.m_x; }
    void StopRight() { --m_direction.m_x; }
    void StopUp() { ++m_direction.m_y; }
    void StopDown() { --m_direction.m_y; }

    bool FinishGame() { return m_isGame; }
private:
    // All the update function for game events runs here
    void UpdateGameEvent(double deltaTime);

    // All the update function for Animation events runs here
    void UpdateAnimationEvent(double deltaTime);

    // Check if it's able to move
    bool TryMove(Vector2 deltaPosition);

    // Check if the object is on collision
    void CheckForCollision();

    // Event happen with collision
    void CollisionEvent(ColliderComponent* pCollider);
    // Event happen with collider
    void ColliderEvent(ColliderComponent* pCollider);

    void GetDamaged(int amount);

    void ImmuneTime(double deltaTime);

};

