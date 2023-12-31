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
#include "TextComponent.h"
#include "SoundComponent.h"
#include <unordered_map>
#include <functional>



class PlayerObject : public GameObject
{
private:

    // Current Animation States
    enum class AnimationState
    {
        kIdle,
        kWalk,
        kRun,
        kJump,
        kSlide
    } m_currentState;

    // gameobject's status
    Status m_status;

private:
    // true when Game Over
    bool m_isGame;

    // * PLAYER
    // Width
    static constexpr int s_kWidth = (int)PLAYER_WIDTH;

    // Height
    static constexpr int s_kHeight = (int)PLAYER_HEIGHT;

    // Health
    static constexpr int s_KMaxHealth = PLAYER_MAX_HEALTH;


    // * MOVEMENT
    // Speed
    static constexpr int s_kMaxSpeed = (int)PLAYER_MAX_SPEED;
    static constexpr int s_kSpeed    = (int)PLAYER_SPEED;
    static constexpr int s_kMixSpeed = (int)PLAYER_MIN_SPEED;

    static constexpr int s_kMaxJumpPower = (int)PLAYER_JUMP_POWER;

    // Moving Component
    MovingComponent m_movingComponent;

    // Text Component
    TextComponent m_nameText;

    // Sound Component
    std::unordered_map<const char*, SoundComponent*> m_mpSounds;

    // Transform of the object
    SDL_Rect m_transform;

    // Trigger to update function such as UI update
    std::unordered_map<const char*, std::function<void()>> m_mpTriggers;

    // * IMMUNE SYSTEM
    static constexpr int s_kMaxImmuneTime= IMMUNE_TIME;

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

private:

public:
    PlayerObject
    (
        SDL_Rect transform,
        CollisionReferee* pReferee,
        size_t type = (size_t)ObjectType::kPlayer,
        const char* directory = PLAYER_SPRITE,
        const char* name = ""
    );
    ~PlayerObject();
    
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

    // Return Name of the object texture directory
    const char* GetTextureName() override { return m_pSpriteName; }

    virtual const char* GetName() override { return m_status.m_name.c_str(); }

    // Check if it's able to move
    virtual void TryMove(Vector2<double> deltaDirection) override;

    // Get this Object's Status
    virtual Status GetStatus() override { return m_status; }

    bool GetWinState() { return m_isGame; }

    virtual bool GetActive() override { return m_status.m_isActive; }

    // SETTER
    // add trigger function with key of name
    void SetTriggerFunction(const char* name, std::function<void()> func);

    void SetNameTag(TTF_Font* pFont, SDL_Color color, SDL_Renderer* pRenderer);

    void Damaged(int amount) override;

    virtual void SetHealth(int value) override { m_status.m_health = value; }

    virtual void SetActive(bool active) override { m_status.m_isActive = active; }

    virtual void SetPosition(Vector2<double> position) override;


    // Moving
    // Sprint
    void SprintSpeed() { m_status.m_speed = s_kMaxSpeed; }
    void NormalSpeed() { m_status.m_speed = s_kSpeed; }
    void SlowSpeed() { m_status.m_speed = s_kMixSpeed; }

    void SetJump() {if (m_status.m_isGrounded)	m_status.m_isOnJump = true; }
    
    bool FinishGame() { return m_isGame; }



private:
    /// GAME EVENTS
    void UpdateGameEvent(double deltaTime);

    // Immune Mechanics
    void OnImmune(double deltaTime);

    //Gravity Mechanics
    void Gravity(double deltaTime);


    void Jump(double deltaTime, double jumpPower = s_kMaxJumpPower);

    /// ANIMATION EVENTS
    // All the update function for Animation events runs here
    void UpdateAnimationEvent(double deltaTime);

    // Play the right animation fallowing current state of gameobject
    void AnimationState();

    // Check current state before play animation.
    void CheckCurrentState();

    /// SOUNDS
    void SoundPlayOnMotion();

    void AddSound(const char* pDir, const char* pKeyName) override;

};

