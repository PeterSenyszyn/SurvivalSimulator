#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

namespace SE
{
	const float PI = 3.14159265f;

	const sf::Vector2f lerp(float t, const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return (a * (1 - t) + b * t);
	}
}