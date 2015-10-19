#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

class Player;

class Camera
{
public:
	Camera(const sf::FloatRect& viewRect, sf::Sprite& spriteToFollow);

	void setRect(const sf::FloatRect& viewRect) { m_view.reset(viewRect); }
	void setSpriteToFollow(sf::Sprite& spriteToFollow) { m_spriteToFollow = &spriteToFollow; }

	void update(sf::Time dt);
	void render(sf::RenderWindow& window);

	sf::View& getView() { return m_view; }

	sf::Vector2f topLeft, bottomRight;

	void setPlayerMappedCoords(sf::Vector2i& coords) { m_playerMappedCoords = coords; }
	sf::Vector2i& getPlayerMappedCoords() { return m_playerMappedCoords; }

private:
	sf::View m_view;

	sf::Sprite* m_spriteToFollow;

	sf::Vector2i m_playerMappedCoords;
};