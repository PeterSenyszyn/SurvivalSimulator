#pragma once

#include "Entity.hpp"
#include "Player.hpp"

namespace SE
{
	//Each Scene has it's own EntityManager
	class EntityManager
	{
	public:
        template <class T> void pushEntity(std::shared_ptr<T> entity)
        {
            auto iter = findObject(entity->getId());

            if (iter != m_entities.end())
                return;

            m_entities.push_back(std::dynamic_pointer_cast<Entity>(entity));
        }

        Player::Ptr getPlayer()
        {
            auto iter = findObject("player");

            if (iter != m_entities.end())
                return std::dynamic_pointer_cast<Player>(*iter);

            return nullptr;
        }

		void update(sf::Time dt);
		void renderEntities(sf::RenderWindow& window);

	private:
		std::list<Entity::Ptr> m_entities;

		std::list<Entity::Ptr>::iterator findObject(const std::string& id)
        {
            for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter)
            {
                if ((*iter)->getId() == id)
                    return iter;
            }

            return m_entities.end();
        }
	};
}
