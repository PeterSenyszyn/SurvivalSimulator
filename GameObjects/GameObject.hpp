#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>

#include <SFML/Graphics.hpp>

namespace SE
{
    class GameObject : public sf::Drawable
    {
    public:
        virtual ~GameObject() {};

        typedef std::shared_ptr<GameObject> Ptr;

        virtual void handleEvents(const sf::Event& event) = 0;
        virtual void update(sf::Time dt) = 0;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

        const std::string& getId() const { return m_id; }

    protected:
        GameObject(const std::string& id, bool collidable, float radius, const sf::Vector2f& pos) : m_id(id), m_collidable(collidable)
        {
            m_interactRadius.setRadius(radius);
            m_interactRadius.setFillColor(sf::Color::Transparent);
            m_interactRadius.setOutlineColor(sf::Color::White);
            m_interactRadius.setPosition(pos);
        };

        const void setCollidable(bool collidable) { m_collidable = collidable; }

        const bool getCollidable() const { return m_collidable; }
        sf::CircleShape& getInteractRadius() { return m_interactRadius; }

        bool intersectsRadius(sf::RectangleShape rectangle);

    private:
        std::string m_id;

        bool m_collidable;

        sf::CircleShape m_interactRadius;
    };
}

#endif // GAMEOBJECT_H
