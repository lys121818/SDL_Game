#pragma once
#include "GameObject.h"
#include "ImageDirectory.h"
#include "ColliderComponent.h"
#include "AnimationComponent.h"
#include "MovingComponent.h"
#include "SoundComponent.h"

class Bullet : public GameObject
{
    static constexpr int s_kMaxDistance = (int)BULLET_MAXDISTANCE;

private:

    // Current Animation States
    enum class AnimationState
    {
        kOnShoot,
        kMuzzle
    } m_currentState;

    SDL_Rect m_transform;

    ColliderComponent m_collider;

    Status m_status;

    const char* m_pSpriteName;

    AnimationComponent m_animation;

    CollisionReferee* m_pReferee;

    MovingComponent m_moveingComponent;

    // Sound Component
    std::unordered_map<const char*, SoundComponent*> m_mpSounds;

    GameObject* m_pTargetObject;

    Vector2<double> m_targetDirection;

    bool m_isAutoLock = false;

public:
    Bullet(
        GameObject* pOwnerObject,
        SDL_Rect transform,
        CollisionReferee* pReferee,
        size_t type,
        GameObject* pTarget = nullptr,
        bool isAutoLock = true,
        const char* directory = BULLET
    );
	~Bullet();

    void Update(double deltaTime);
    void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture);

    virtual void OnOverlapBegin(ColliderComponent* pCollider) override;

    virtual void TryMove(Vector2<double> deltaDirection = Vector2<double>{0,0}) override;

    // Return Name of the object texture directory
    const char* GetTextureName() override { return m_pSpriteName; }

    // Return the Status of the gameobject
    virtual Status GetStatus() override { return m_status; }

    // Get if the game object is active in game (dead/destroy or live)
    virtual bool GetActive() { return m_status.m_isActive; }

    // Return transform of object
    virtual SDL_Rect GetTransform() override { return m_transform; }

    virtual void SetPosition(Vector2<double> newPosition) override;

    virtual void SetActive(bool active) override { m_status.m_isActive = active; }

private:
    /// ANIMATION EVENTS
    // All the update function for Animation events runs here
    void UpdateAnimationEvent(double deltaTime);

    // Play the right animation fallowing current state of gameobject
    void AnimationState();


    /// SOUNDS
    void AddSound(const char* pDir, const char* pKeyName) override;

    void Destroy();
};

