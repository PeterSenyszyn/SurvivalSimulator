#ifndef MENUSTARMANAGER_H
#define MENUSTARMANAGER_H

#include <SFML/System/Thread.hpp>

#include <Application.hpp>

class MenuStarManager
{
public:
    MenuStarManager(int numStars)
    {
        menuStarTexture.loadFromFile("Assets/particle.png");

        for (auto iter = 0; iter <= numStars; ++iter)
            stars.push_back(std::make_shared<MenuStar>(menuStarTexture));
    }

    void update(sf::Time dt)
    {
        for (const auto& iter : stars)
            iter->update(dt);
    }

    void render(sf::RenderWindow& window)
    {
        for (const auto& iter : stars)
            window.draw(*iter);
    }

private:
    struct MenuStar : public sf::Drawable
    {
        MenuStar(sf::Texture& texture) :
        speed(static_cast<float>(randomInt(75, 150)))
        {
            shape.setTexture(&texture);
            shape.setPosition(sf::Vector2f(randomInt(0, Application::getCurrentResolution().x),
                                                    randomInt(0, Application::getCurrentResolution().y)));
            shape.setSize(sf::Vector2f(randomInt(2, 7), randomInt(2, 7)));
        }

        bool offScreen() { return shape.getPosition().x > Application::getCurrentResolution().x; }

        void update(sf::Time dt)
        {
            if (offScreen())
                shape.setPosition(0, randomInt(1, Application::getCurrentResolution().y));

            shape.move(speed * dt.asSeconds(), 0);
        }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(shape, states);
        }

        sf::RectangleShape shape;
        float speed;
    };

private:
    sf::Texture menuStarTexture;

    std::vector<std::shared_ptr<MenuStar> > stars;
};

#endif // MENUSTARMANAGER_H
