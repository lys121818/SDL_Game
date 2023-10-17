#pragma once
#include "GameObject.h"
#include "Defines.h"
#include "GameSetting.h"
#include "Vector2.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "MovingComponent.h"
#include "Status.h"

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

    // gameobject's status
    Status m_status;

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

    // Immune Time
    double m_immuneTime;

    // Name Of the Object
    const char* m_pSpriteName;

    // Current direction.x movement. -1 for left, 1for right.
    // Current direction.y movement. -1 for down, 1 for up.
    Vector2 m_direction;

    // Player Immune time
    bool m_isImmune;


    // AnimationComponent to play animation	
    AnimationComponent m_animation;

    // Moving Component
    MovingComponent m_movingComponent;

    // collider for this object
    ColliderComponent m_collider;

    // collider of colliding object
    ColliderComponent* m_otherCollider;

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
    virtual void OnCollision(ColliderComponent* pCollider) override;

    //GETTER
    // return position of object
    //Vector2 GetPosition() { return m_position; }
    // return the transform of object
    SDL_Rect GetTransform() override { return m_transform; }
    // Return Name of the object
    const char* GetTextureName() override { return m_pSpriteName; }

    //SETTER
    // Change the position of the object 
    //void SetPosition(Vector2 position);

    // Check if it's able to move
    virtual void TryMove(Vector2 deltaDirection) override;

    virtual Status GetStatus() override { return m_status; }

    //void SetTrigger(bool isTrigger) { m_isOnCollision = isTrigger; }
    // Moving
    // Sprint
    void SprintSpeed() { m_status.m_speed = s_kMaxSpeed; }
    void NormalSpeed() { m_status.m_speed = s_kSpeed; }
    void SlowSpeed() { m_status.m_speed = s_kMixSpeed; }

    bool FinishGame() { return m_isGame; }
private:
    // All the update function for game events runs here
    void UpdateGameEvent(double deltaTime);

    // All the update function for Animation events runs here
    void UpdateAnimationEvent(double deltaTime);


    // Check if the object is on collision
    void CheckForCollision();

    // Event happen with collision
    void CollisionEvent(ColliderComponent* pCollider);
    // Event happen with collider
    void ColliderEvent(ColliderComponent* pCollider);

    void GetDamaged(int amount);

    void ImmuneTime(double deltaTime);

};

