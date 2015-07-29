#pragma once

#include <Utility.hpp>
#include <TileMap.hpp>
#include <StorageContainer.hpp>

class WorldCell : public sf::Drawable, public sf::Transformable
{
public:
    typedef std::shared_ptr<WorldCell> Ptr;

    static Ptr create(const std::string& id, bool current);

    void handleEvents(const sf::Event& event);

    void update(sf::Time dt, thor::ActionMap<Keys::KeyboardInput>& keyboardMap);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    const void setId(const std::string& id) { m_id = id; }
    const std::string& getId() const { return m_id; }

    const void setIfCurrentCell(bool current) { m_current = current; }
    const bool getIfCurrentCell() const { return m_current; }

    //Getter and setter for update
    //If true, then this cell will update even if not current
    const void setIfUpdate(bool update) { m_update = update; }
    const bool getIfUpdate() const { return m_update; }

    static TileMap& getTileMap() { return m_tileMap; }

    std::map<std::string, Item::Ptr>& getWorldItems() { return m_worldItems; }
    std::map<std::string, StorageContainer::Ptr>& getWorldContainers() { return m_storageContainers; }

    const bool hasOpenContainer() const;
    StorageContainer::Ptr getOpenContainer();

    void addWorldItem(Item::Ptr item);
    void addWorldContainer(StorageContainer::Ptr container);

    bool collidesWithContainer(const sf::FloatRect& rect);

private:
    WorldCell(const std::string& id, bool current);

    std::string m_id;
    std::string m_world_data;

    static TileMap m_tileMap;

    std::map<std::string, Item::Ptr> m_worldItems;
    std::map<std::string, StorageContainer::Ptr> m_storageContainers;

    bool m_current;
    bool m_update;
};
