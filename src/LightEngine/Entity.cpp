#include "Entity.h"
#include <iostream>
#include "GameManager.h"
#include "Utils.h"
#include "Debug.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <algorithm>

void Entity::Initialize(sf::Vector2f size, const sf::Color& color)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);

	mShape.setOrigin(0.f, 0.f);
	mShape.setSize(size);
	mShape.setFillColor(color);

	mTarget.isSet = false;

	OnInitialize();
}

void Entity::Repulse(Entity* other)
{
	AABBCollider c1 = GetAABBCollider();
	AABBCollider c2 = other->GetAABBCollider();

	float overlapX = std::min(c1.xMax, c2.xMax) - std::max(c1.xMin, c2.xMin);
	float overlapY = std::min(c1.yMax, c2.yMax) - std::max(c1.yMin, c2.yMin);
	float changeX = 0;
	float changeY = 0;

	if (overlapX > 0)
	{
		if (overlapX >= overlapY) 
		{
			int face = Utils::GetFace(c1, c2);
			if (face == 3)
				overlapY = -overlapY;
		
			if (c2.xMax > c1.xMin) 
			{
				changeY = -overlapY;
			}
			else 
			{
				changeY = overlapY;
			}
		}
	}

	if (overlapY > 0) 
	{
		if (overlapY >= overlapX) 
		{
			AABBCollider c1 = GetAABBCollider();
			AABBCollider c2 = other->GetAABBCollider();

			int face = Utils::GetFace(c1, c2);
			if (face == 4)
				overlapX = -overlapX;

			if (c2.yMax > c1.yMin) 
			{
				changeX = overlapX;
			}
			else 
			{
				changeX = overlapX;
			}
		}
	}

	sf::Vector2f position1 = sf::Vector2f(mShape.getPosition().x - changeX, mShape.getPosition().y - changeY);
	sf::Vector2f position2 = sf::Vector2f(other->GetPosition().x + changeX, other->GetPosition().y + changeY);

	if (!mIsStatic)
		mShape.setPosition(position1.x, position1.y);

	if (!other->mIsStatic)
		other->SetPosition(position2.x, position2.y);
}

bool Entity::IsColliding(Entity* other)
{
	AABBCollider c1 = GetAABBCollider();
	AABBCollider c2 = other->GetAABBCollider();

	if (c1.xMax <= c2.xMin || c1.xMin >= c2.xMax || c1.yMin >= c2.yMax || c1.yMax <= c2.yMin)
		return false;

	return true;
}

bool Entity::IsInside(float x, float y)
{
	AABBCollider c = GetAABBCollider();

	if (x >= c.xMin && x <= c.xMax && y >= c.yMin && y <= c.yMax)
		return true;

	return false;
}

void Entity::Destroy()
{
	mToDestroy = true;

	OnDestroy();
}

AABBCollider Entity::GetAABBCollider()
{
	AABBCollider collider;
	collider.xMin = GetPosition().x;
	collider.xMax = GetPosition().x + GetSize().x;
	collider.yMin = GetPosition().y;
	collider.yMax = GetPosition().y + GetSize().y;

	return collider;
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{

	mShape.setPosition(x, y);

	//#TODO Optimise
	if (mTarget.isSet) 
	{
		sf::Vector2f position = GetPosition(0.5f, 0.5f);
		mTarget.distance = Utils::GetDistance(position.x, position.y, mTarget.position.x, mTarget.position.y);
		GoToDirection(mTarget.position.x, mTarget.position.y);
		mTarget.isSet = true;
	}
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	float sizeX = mShape.getSize().x / 2;
	float sizeY = mShape.getSize().y / 2;
	sf::Vector2f position = mShape.getPosition();

	position.x += sizeX * ratioX;
	position.y += sizeY * ratioY;

	return position;
}

bool Entity::GoToDirection(int x, int y, float speed)
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	SetDirection(direction.x, direction.y, speed);

	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
	mTarget.isSet = false;
}

void Entity::Update()
{

	OnUpdate();
}

void Entity::FixedUpdate(float deltaTime)
{
	float dt = GetDeltaTime();
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
	mShape.move(translation);

	if (mTarget.isSet)
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	OnFixedUpdate(deltaTime);
}

Scene* Entity::GetScene() const
{
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}