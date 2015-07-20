#include "Container.hpp"
#include "SceneManager.hpp"
#include "Player.hpp"

namespace SE
{
    Container::Container(const std::string& texturePath, const sf::Vector2f& pos, const sf::Vector2f& inventorySize, bool collidable, float radius, const std::string& id) :
    GameObject(id, collidable, radius, pos),
    m_inventorySize(inventorySize)
    {
        m_texture.loadFromFile(texturePath);
        m_sprite.setTexture(m_texture);

        m_sprite.setPosition(pos);
    }

    Container::Ptr Container::create(const std::string& texturePath, const sf::Vector2f& pos, const sf::Vector2f& inventorySize, bool collidable, float radius, const std::string& id)
    {
        Ptr temp(new Container(texturePath, pos, inventorySize, collidable, radius, id));

        return temp;
    }

    void Container::handleEvents(const sf::Event& event)
    {
        switch (event.type)
        {

        }
    }

    void Container::update(sf::Time dt)
    {
        sf::RectangleShape playerRect;

        //int width = SceneManager::getEntityManager().getPlayer()->getBounds().width;
        //int height = SceneManager::getEntityManager().getPlayer()->getBounds().height;


        //playerRect.setSize(sf::Vector2f(width, height));
        //playerRect.setPosition(SceneManager::getEntityManager().getPlayer()->getPosition());

        //playerRect.setSize(sf::Vector2f(SceneManager::getEntityManager().getPlayer()->getTexture().getSize().x, SceneManager::getEntityManager().getPlayer()->getTexture().getSize().y));
        //playerRect.setPosition(SceneManager::getEntityManager().getPlayer()->getPosition());

        //if (intersectsRadius(playerRect))
         //   std::cout << "player is intersecting the circle" << std::endl;
    }

    void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }
}
