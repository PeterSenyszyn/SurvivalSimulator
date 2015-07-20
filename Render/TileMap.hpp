#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <memory>
#include <map>
#include <iostream>

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    struct Tile
    {
        Tile(const sf::FloatRect& bounds, const sf::Vector2f pos, int tileType) : bounds(bounds), pos(pos), tileType(tileType) {};

        sf::FloatRect bounds;
        sf::Vector2f pos;
        int tileType;
    };

    struct TileEntityRef
    {
        typedef std::shared_ptr<TileEntityRef> Ptr;

        TileEntityRef(int tileType, const std::string& tileName, bool pickUppable, bool collectable) :
        tileType(tileType), tileName(tileName), pickUppable(pickUppable), collectable(collectable) {};

        int tileType;
        sf::Vector2f pos;
        std::string tileName;

        bool pickUppable;
        bool collectable;
    };

public:
    TileMap();

    const bool getActive() const { return m_active; }
    const void setActive(const bool active) { m_active = active; }

    bool load(const std::string& filepath, sf::Vector2u tileSize, const int* tiles, unsigned width, unsigned int height);

    bool collidesWithType(int tileType, const sf::FloatRect& bounds)
    {
        for (auto& iter : m_tiles)
        {
            if (iter.tileType == tileType)
            {
                if (bounds.intersects(iter.bounds))
                    return true;
            }
        }

        return false;
    }

    TileEntityRef::Ptr getTileMouseOver(sf::Vector2i& mouseCoords)
    {
        for (auto& iter : m_tiles)
        {
            for (auto& iter2 : m_tileEntityRef)
            {
                if (iter.tileType == iter2->tileType && iter.bounds.contains(mouseCoords.x, mouseCoords.y))
                {
                    iter2->pos = iter.pos;

                    return iter2;
                }
            }
        }

        return nullptr;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool m_active;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    std::vector<Tile> m_tiles;
    std::vector<TileEntityRef::Ptr> m_tileEntityRef;
};

#endif // TILEMAP_H
