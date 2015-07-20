#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

//Note: don't forgot to implement culling for items that the player can't see on the screen
//Each cell will have their own ObjectManager

#include "Container.hpp"

namespace SE
{
    class ObjectManager
    {
    public:
        void pushObject(GameObject::Ptr object);
        void removeObject(const std::string& id);

        void handleEvents(const sf::Event& event);

        void update(sf::Time dt);
        void render(sf::RenderWindow& window);

    private:
        std::list<GameObject::Ptr>::iterator findObject(const std::string& id)
        {
            for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
            {
                if ((*iter)->getId() == id)
                    return iter;
            }

            return m_objects.end();
        }

        GameObject::Ptr findObjectWithId(const std::string& id)
        {
            for (const auto& iter : m_objects)
            {
                if (iter->getId() == id)
                    return iter;
            }

            return nullptr;
        }

        //List of all the objects in the cell
        std::list<GameObject::Ptr> m_objects;
    };
}

#endif // OBJECTMANAGER_H
