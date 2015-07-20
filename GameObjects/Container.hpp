#ifndef CONTAINER_H
#define CONTAINER_H

#include <list>

#include "Item.hpp"
#include "GameObject.hpp"

namespace SE
{
    class Container : public GameObject
    {
    public:
        virtual ~Container() {};

        typedef std::shared_ptr<Container> Ptr;

        static Ptr create(const std::string& texturePath, const sf::Vector2f& pos, const sf::Vector2f& inventorySize, bool collidable, float radius, const std::string& id);

        virtual void handleEvents(const sf::Event& event);
        virtual void update(sf::Time dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        Container(const std::string& texturePath, const sf::Vector2f& pos, const sf::Vector2f& inventorySize, bool collidable, float radius, const std::string& id);

        std::list<Item::Ptr> m_items;

        sf::Texture m_texture;
        sf::Sprite m_sprite;

        sf::Vector2f m_inventorySize;
    };
}

#endif // Container_H
