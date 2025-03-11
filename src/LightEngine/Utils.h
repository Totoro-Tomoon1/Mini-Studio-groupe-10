#pragma once

#include <SFML/System/Vector2.hpp>
#include "Entity.h"

namespace Utils
{
	bool Normalize(sf::Vector2f& vector);
	float GetDistance(int x1, int y1, int x2, int y2);
	float GetAngleDegree(const sf::Vector2f& v1, const sf::Vector2f& v2);
	int GetFace(const AABBCollider& c1, const AABBCollider& c2); //a utiliser que si collision
}