//#include "Circle.h"
//
//#include "Utils.h"
//
//void Circle::SetPosition(float x, float y, float ratioX, float ratioY)
//{
//	float size = mShape.getRadius() * 2;
//
//	x -= size * ratioX;
//	y -= size * ratioY;
//
//	mShape.setPosition(x, y);
//
//	//#TODO Optimise
//	if (mTarget.isSet) 
//	{
//		sf::Vector2f position = GetPosition(0.5f, 0.5f);
//		mTarget.distance = Utils::GetDistance(position.x, position.y, mTarget.position.x, mTarget.position.y);
//		GoToDirection(mTarget.position.x, mTarget.position.y);
//		mTarget.isSet = true;
//	}
//}
//
//sf::Vector2f Circle::GetPosition(float ratioX, float ratioY) const
//{
//	float size = mShape.getRadius() * 2;
//	sf::Vector2f position = mShape.getPosition();
//	
//	position.x += size * ratioX;
//	position.y += size * ratioY;
//	
//	return position;
//}
//
//bool Circle::IsColliding(Entity* other) const
//{
//	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);
//	
//	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
//	
//	float radius1 = mShape.getRadius();
//	//a modifier plus tard
//	float radius2 = dynamic_cast<Circle*>(other)->mShape.getRadius();
//	
//	float sqrRadius = (radius1 + radius2) * (radius1 + radius2);
//	
//	return sqrLength < sqrRadius;
//}
//
//bool Circle::IsInside(float x, float y) const
//{
//	sf::Vector2f position = GetPosition(0.5f, 0.5f);
//	
//		float dx = x - position.x;
//		float dy = y - position.y;
//	
//		float radius = mShape.getRadius();
//	
//		return (dx * dx + dy * dy) < (radius * radius);
//}
