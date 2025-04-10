#pragma once

#include <SFML/Graphics/View.hpp>

class Camera
{
	sf::View mView;

public:
	Camera();

	void SetPosition(const sf::Vector2f& pos)
	{
		mView.setCenter(pos);
	}

	sf::View& GetView()
	{
		return mView;
	}
};