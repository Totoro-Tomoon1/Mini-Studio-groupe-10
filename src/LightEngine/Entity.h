#pragma once

#include <SFML/System/Vector2.hpp>
//#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

struct AABBCollider
{
	float xMin, yMin;
	float xMax, yMax;
};

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:
	sf::RectangleShape mShape;
    sf::Vector2f mDirection;
	Target mTarget;
    float mSpeed = 0.f;
    bool mToDestroy = false;
    int mTag = -1;
	bool mRigidBody = false;
	bool mIsStatic = false;

public:
	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    virtual void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetDirection(float x, float y, float speed = -1.f);
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(int tag) { mTag = tag; }
	void SetStatic(bool stati) { mIsStatic = stati; }
	//float GetRadius() const { return mShape.getRadius(); }
	sf::Vector2f GetSize() const { return mShape.getSize(); }
	void SetRigidBody(bool isRigitBody) { mRigidBody = isRigitBody; }
	bool IsRigidBody() const { return mRigidBody; }

    sf::Vector2f GetPosition(float ratioX = 0.f, float ratioY = 0.f) const;
	sf::Shape* GetShape() { return &mShape; }

	bool IsTag(int tag) const { return mTag == tag; }
    bool IsColliding(Entity* other);
	bool IsInside(float x, float y);

    void Destroy();
	bool ToDestroy() const { return mToDestroy; }

	AABBCollider GetAABBCollider();
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

    /*template<typename T>
    T* CreateEntity(float radius, const sf::Color& color);*/

	template<typename T>
	T* CreateEntity(sf::Vector2f size, const sf::Color& color);

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
	virtual void OnFixedUpdate(float deltaTime) {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	
private:
    void Update();
	void FixedUpdate(float deltaTime);
	void Initialize(sf::Vector2f size, const sf::Color& color);
	void Repulse(Entity* other);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"