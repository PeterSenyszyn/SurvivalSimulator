
#include "EntityManager.hpp"

namespace SE
{
	void EntityManager::update(sf::Time dt)
	{
		for (const auto& iter : m_entities)
			iter->update(dt);
	}

	void EntityManager::renderEntities(sf::RenderWindow& window)
	{
		for (const auto& iter : m_entities)
		{
			if (iter->hasAttribute("renderable"))
			{
				if (iter->getAttribute<bool>("renderable") == true)
					window.draw(*iter);
			}
		}
	}
}
