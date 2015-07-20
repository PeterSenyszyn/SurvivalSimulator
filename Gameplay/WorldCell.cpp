#include "WorldCell.hpp"

TileMap WorldCell::m_tileMap;

WorldCell::WorldCell(const std::string& id, bool current) :
    m_id(id),
    m_current(current)
{

}

WorldCell::Ptr WorldCell::create(const std::string& id, bool current)
{
    Ptr temp(new WorldCell(id, current));

    return temp;
}

void WorldCell::addWorldItem(Item::Ptr item)
{
    item->setActive(true);
    m_worldItems[std::to_string(m_worldItems.size()-1)] = item;
}

void WorldCell::update(sf::Time dt)
{

}

void WorldCell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_tileMap);

    for (const auto& iter : m_worldItems)
        target.draw(*iter.second);
}
