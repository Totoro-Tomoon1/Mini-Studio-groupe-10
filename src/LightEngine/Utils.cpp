#include <SFML/System/Vector2.hpp>

#include <cmath>
#include "Utils.h"

#include <algorithm>

namespace Utils 
{
    bool Normalize(sf::Vector2f& vector)
    {
        float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

		if (magnitude != 0)
		{
			vector.x /= magnitude;
			vector.y /= magnitude;
		
			return true;
		}

		return false;
    }

	float GetDistance(int x1, int y1, int x2, int y2)
	{
		int x = x2 - x1;
		int y = y2 - y1;

		return std::sqrt(x * x + y * y);
	}

	float GetAngleDegree(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		float dot = v1.x * v2.x + v1.y * v2.y;
		float det = v1.x * v2.y - v1.y * v2.x;

		return std::atan2(det, dot) * 180 / 3.14159265;
	}
	int Utils::GetFace(const AABBCollider& c1, const AABBCollider& c2)
	{
		float overlapX = std::min(c1.xMax, c2.xMax) - std::max(c1.xMin, c2.xMin);

		float overlapY = std::min(c1.yMax, c2.yMax) - std::max(c1.yMin, c2.yMin);

		if (overlapX > overlapY)
		{
			if (c1.yMin > c2.yMax && c1.yMin < c2.yMin)
				return 1;
			else if (c1.yMax > c2.yMin && c1.yMax < c2.yMax)
				return 3; 
		}
		else
		{
			if (c1.xMax < c2.xMax && c1.xMax > c2.xMin)
				return 2;
			else if (c1.xMin < c2.xMax && c1.xMin > c2.xMin)
				return 4;
		}

		return 0;
	}
}