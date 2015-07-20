#include "World.hpp"

WorldCell::Ptr World::m_currentCell = nullptr;

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
    if (m_active)
    {
        for (const auto& iter : m_worldCells)
        {
            if (iter->getIfCurrentCell() || iter->getIfUpdate())
                iter->update(dt);
        }
    }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_active)
        target.draw(*m_currentCell, states);
}
