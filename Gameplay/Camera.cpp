#include "stdafx.h"
#include "Camera.hpp"
#include "WorldCell.hpp"
#include "Application.hpp"
#include "Player.hpp"

Camera::Camera(const sf::FloatRect& viewRect, sf::Sprite& spriteToFollow) :
m_view(viewRect),
m_spriteToFollow(&spriteToFollow),
topLeft({ 1, 1}),
bottomRight({ 1, 1}),
m_playerMappedCoords(0, 0)
{

}

void Camera::update(sf::Time dt)
{
	
}

void Camera::render(sf::RenderWindow& window)
{
	topLeft = window.mapPixelToCoords(sf::Vector2i(0, 0));
	bottomRight = window.mapPixelToCoords(sf::Vector2i(Application::getCurrentResolution()));	

	m_view.setSize(adjustForResX(Application::getCurrentResolution().x), adjustForResY(Application::getCurrentResolution().y));

	setPlayerMappedCoords(window.mapCoordsToPixel(m_spriteToFollow->getPosition()));
}