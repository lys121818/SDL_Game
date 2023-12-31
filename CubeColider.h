#pragma once
#include "GameObject.h"
#include "Defines.h"
#include "ImageDirectory.h"
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
    enum class AnimationState
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
    // true when Game Over
    bool m_isWin;

    // * PLAYER
    // Width
    static constexpr int s_kWidth = (int)PLAYERWIDTH;

    // Height
    static constexpr int s_kHeight = (int)PLAYERHEIGHT;

    // Health
    static constexpr int s_KMaxHealth = PLAYERMAXHEALTH;


    // * MOVEMENT
    // Speed
    static constexpr int s_kMaxSpeed = (int)PLAYERMAXSPEED;
    static constexpr int s_kSpeed    = (int)PLAYERSPEED;
    static constexpr int s_kMixSpeed = (int)PLAYERMINSPEED;

    static constexpr int s_kMaxJumpPower = (int)1000;

    // Moving Component
    MovingComponent m_movingComponent;



    // Transform of the object
    SDL_Rect m_transform;


    // * IMMUNE SYSTEM
    static constexpr int s_kMaxImmuneTime= IMMUNETIME;

    // Current Immune Timer
    double m_immuneTime;

    // It's On Immune
    bool m_isImmune;

    float m_jumpPower;

    // * ANIMATION SYSTEM
    // Location of Sprite Sheet
    const char* m_pSpriteName;

    // AnimationComponent to play animation	
    AnimationComponent m_animation;


    // * COLLISION SYSTEM
    // Collider for this object
    ColliderComponent m_collider;

    // Collider of Triggered Object
    //ColliderComponent* m_otherCollider;

private:

public:
    CubeColider
    (
        SDL_Rect transform, 
        CollisionReferee* pReferee, 
        size_t type = (size_t)ObjectType::m_Player,
        const char* directory = PLAYERSPRITE
    );
    ~CubeColider();
    
    // Inherited via GameObject
    void Update(double deltaTime) override;
    void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

    // On Collision action
    virtual void OnCollision(ColliderComponent* pCollider) override;

    // Trigger Enter
    virtual void OnOverlapBegin(ColliderComponent* pCollider) override;

    // Trigger Update
    virtual void OnOverlapUpdate() override;

    // Trigger Exit
    virtual void OnOverlapEnd() override;

    //GETTER
    // return the transform of object
    SDL_Rect GetTransform() override { return m_transform; }

    // Return Name of the object
    const char* GetTextureName() override { return m_pSpriteName; }


    // Check if it's able to move
    virtual void TryMove(Vector2 deltaDirection) override;

    // Get this Object's Status
    virtual Status GetStatus() override { return m_status; }

    bool GetWinState() { return m_isWin; }

    void Jump(double deltaTime = 0);

    // Moving
    // Sprint
    void SprintSpeed() { m_status.m_speed = s_kMaxSpeed; }
    void NormalSpeed() { m_status.m_speed = s_kSpeed; }
    void SlowSpeed() { m_status.m_speed = s_kMixSpeed; }

    bool FinishGame() { return m_isWin; }


private:
    /// GAME EVENTS
    void UpdateGameEvent(double deltaTime);



    // Immune Mechanics
    void ImmuneTime(double deltaTime);

    //Gravity Mechanics
    void Gravity(double deltaTime);

    void GetDamaged(int amount);



    /// ANIMATION EVENTS
    // All the update function for Animation events runs here
    void UpdateAnimationEvent(double deltaTime);

    // Play the right animation fallowing current state of gameobject
    void AnimationState();

    // Check current state before play animation.
    void CheckCurrentState();


};

