#include "ObjectManager.hpp"

namespace SE
{
    void ObjectManager::pushObject(GameObject::Ptr object)
    {
        auto iter = findObject(object->getId());

        if (iter != m_objects.end())
            return;

        m_objects.push_back(object);
    }

    void ObjectManager::removeObject(const std::string& id)
    {
        auto iter = findObject(id);

        if (iter != m_objects.end())
            m_objects.erase(iter);
    }

    void ObjectManager::handleEvents(const sf::Event& event)
    {
        for (const auto& iter : m_objects)
            iter->handleEvents(event);
    }

    void ObjectManager::update(sf::Time dt)
    {
        for (const auto& iter : m_objects)
            iter->update(dt);
    }

    void ObjectManager::render(sf::RenderWindow& window)
    {
        for (const auto& iter : m_objects)
            window.draw(*iter);
    }
}
