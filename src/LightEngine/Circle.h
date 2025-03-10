//#pragma once
//#include "Entity.h"
//
//class Circle : public Entity
//{
//protected:
//	sf::CircleShape mShape;
//
//public:
//	void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f) override;
//	sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const override;
//
//	float GetRadius() const { return mShape.getRadius(); }
//
//	bool IsColliding(Entity* other) const override;
//	bool IsInside(float x, float y) const override;
//
//	template<typename T>
//	T* CreateCircle(float radius, const sf::Color& color);
//
//private:
//	void Initialize() override;
//};
