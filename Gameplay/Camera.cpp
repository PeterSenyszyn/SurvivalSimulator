#include "Camera.hpp"

Camera::Camera(const sf::FloatRect& viewRect, sf::Sprite& spriteToFollow) :
m_view(viewRect),
m_spriteToFollow(&spriteToFollow)
{

}

void Camera::update(sf::Time dt)
{

}

void Camera::render(sf::RenderWindow& window)
{
    m_view.setCenter(m_spriteToFollow->getPosition());
}
