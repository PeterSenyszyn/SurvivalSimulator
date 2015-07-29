#include <WorldCell.hpp>

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
    m_worldItems[std::to_string(m_worldItems.size() - 1)] = item;
}

void WorldCell::addWorldContainer(StorageContainer::Ptr container)
{
    m_storageContainers[std::to_string(m_storageContainers.size() - 1)] = container;
}

const bool WorldCell::hasOpenContainer() const
{
    for (const auto& iter : m_storageContainers)
    {
        if (iter.second->menuOpened())
            return true;
    }

    return false;
}

StorageContainer::Ptr WorldCell::getOpenContainer()
{
    for (const auto& iter : m_storageContainers)
    {
        if (iter.second->menuOpened())
            return iter.second;
    }

    return nullptr;
}

bool WorldCell::collidesWithContainer(const sf::FloatRect& rect)
{
    for (const auto& iter : m_storageContainers)
    {
        if (iter.second->getSprite().getGlobalBounds().intersects(rect))
            return true;
    }

    return false;
}

void WorldCell::handleEvents(const sf::Event& event)
{
    for (const auto& iter : m_storageContainers)
        iter.second->handleEvents(event);
}

void WorldCell::update(sf::Time dt, thor::ActionMap<Keys::KeyboardInput>& keyboardMap)
{
    for (const auto& iter : m_storageContainers)
        iter.second->update(dt, keyboardMap);
}

void WorldCell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_tileMap);

    for (const auto& iter : m_storageContainers)
        target.draw(*iter.second);

    for (const auto& iter : m_worldItems)
        target.draw(*iter.second);
}
