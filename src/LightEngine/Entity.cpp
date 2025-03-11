#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"
#include "Debug.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <algorithm>

//void Entity::Initialize(float radius, const sf::Color& color)
//{
//	mDirection = sf::Vector2f(0.0f, 0.0f);
//
//	mShape.setOrigin(0.f, 0.f);
//	mShape.setRadius(radius);
//	mShape.setFillColor(color);
//	
//	mTarget.isSet = false;
//
//	OnInitialize();
//}

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
	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f); //stocker les positions
	
	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
	float length = std::sqrt(sqrLength);

	/*float radius1 = mShape.getRadius();
	float radius2 = other->mShape.getRadius();

	float overlap = (length - (radius1 + radius2)) * 0.5f;*/
	//sf::Vector2f posMin1 = sf::Vector2f(GetPosition().x, GetPosition().y);
	//sf::Vector2f posMax1 = sf::Vector2f(GetPosition().x + GetSize().x, GetPosition().y + GetSize().y);
	//sf::Vector2f posMin2 = sf::Vector2f(other->GetPosition().x, other->GetPosition().y);
	//sf::Vector2f posMax2 = sf::Vector2f(other->GetPosition().x + other->GetSize().x, other->GetPosition().y + other->GetSize().y);

	AABBCollider col1 = GetAABBCollider();
	AABBCollider col2 = other->GetAABBCollider();

	int left = std::max(col1.xMin, col2.xMin);
	int right = std::min(col1.xMax, col2.xMax);
	int top = std::max(col1.yMin, col2.yMin);
	int bottom = std::min(col1.yMax, col2.yMax);

	sf::Vector2f overlap = sf::Vector2f(right - left, bottom - top);

	sf::Vector2f normal = distance / length;

	sf::Vector2f translation = sf::Vector2f(overlap.x * normal.x, overlap.y * normal.y);

	sf::Vector2f position1 = GetPosition(0.5f, 0.5f) - translation;
	sf::Vector2f position2 = other->GetPosition(0.5f, 0.5f) + translation;

	SetPosition(position1.x, position1.y, 0.5f, 0.5f);
	other->SetPosition(position2.x, position2.y, 0.5f, 0.5f);
}

bool Entity::IsColliding(Entity* other)
{
	/*sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);

	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);

	float radius1 = mShape.getRadius();
	float radius2 = other->mShape.getRadius();

	float sqrRadius = (radius1 + radius2) * (radius1 + radius2);

	return sqrLength < sqrRadius;*/

	AABBCollider c1 = GetAABBCollider();
	AABBCollider c2 = other->GetAABBCollider();

	if (c1.xMax <= c2.xMin || c1.xMin >= c2.xMax || c1.yMin >= c2.yMax || c1.yMax <= c2.yMin)
		return false;

	return true;
}

bool Entity::IsInside(float x, float y)
{
	/*sf::Vector2f position = GetPosition(0.5f, 0.5f);

	float dx = x - position.x;
	float dy = y - position.y;

	float radius = mShape.getRadius();

	return (dx * dx + dy * dy) < (radius * radius);*/

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
	//float size = mShape.getRadius() * 2;
	/*sf::Vector2f size = mShape.getSize();

	x -= size.x * ratioX;
	y -= size.y * ratioY;*/

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
	//float size = mShape.getRadius() * 2;
	/*float sizeX = mShape.getSize().x * 2;
	float sizeY = mShape.getSize().y * 2;*/
	sf::Vector2f position = mShape.getPosition();

	/*position.x += sizeX * ratioX;
	position.y += sizeY * ratioY;*/

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