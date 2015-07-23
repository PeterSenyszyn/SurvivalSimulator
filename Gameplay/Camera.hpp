#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera(const sf::FloatRect& viewRect, sf::Sprite& spriteToFollow);

    void setRect(const sf::FloatRect& viewRect) { m_view.reset(viewRect); }
    void setSpriteToFollow(sf::Sprite& spriteToFollow) { m_spriteToFollow = &spriteToFollow; }

    void update(sf::Time dt);
    void render(sf::RenderWindow& window);

    sf::View& getView() { return m_view; }

private:
    sf::View m_view;

    sf::Sprite* m_spriteToFollow;
};

#endif // CAMERA_H
