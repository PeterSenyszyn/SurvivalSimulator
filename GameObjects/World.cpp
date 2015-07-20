
#include "World.hpp"

namespace Ataxia
{
	//TileManager World::m_tileManager;

	void World::setCurrentCell(const std::string& id)
	{
		for (const auto& iter : m_worldCells)
		{
			if (iter->getId() == id)
			{
				m_currentCell = iter;

				return;
			}
		}
	}

	void World::pushWorldCell(WorldCell::Ptr cell)
	{
		for (const auto& iter : m_worldCells)
		{
			if (iter->getId() == cell->getId())
				return;
		}

		m_worldCells.push_back(cell);
	}

	void World::update(sf::Time dt)
	{
		for (const auto& iter : m_worldCells)
		{
			if (iter->getIfCurrentCell() || iter->getIfUpdate())
				iter->update(dt);
		}
	}

	void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(*m_currentCell, states);
	}
}
