#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

namespace Ataxia
{
	class TileMap : public sf::Drawable, public sf::Transformable
	{
	public:
		struct Tile
		{
			Tile(const sf::FloatRect& bounds, int tileType) : bounds(bounds), tileType(tileType) {};

			sf::FloatRect bounds;
			int tileType;
		};

		void load(const std::string& tileset, sf::Vector2u tileSize, int* tiles,
			unsigned int width, unsigned int height)
		{
			// load the tileset texture
			m_tileset.loadFromFile(tileset);

			 // resize the vertex array to fit the level size
            m_vertices.setPrimitiveType(sf::Quads);
            m_vertices.resize(width * height * 4);

            // populate the vertex array, with one quad per tile
            for (unsigned int i = 0; i < width; ++i)
                for (unsigned int j = 0; j < height; ++j)
                {
                    // get the current tile number
                    int tileNumber = tiles[i + j * width];

                    // find its position in the tileset texture
                    int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                    int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                    // get a pointer to the current tile's quad
                    sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                    // define its 4 corners
                    quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                    quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                    quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                    quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                    // define its 4 texture coordinates
                    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

                    Tile temp(sf::FloatRect(quad[0].position.x, quad[0].position.y, quad[1].position.x - quad[0].position.x, quad[2].position.y - quad[0].position.y), tileNumber);

                    m_tiles.push_back(temp);
                }
        }

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

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			states.texture = &m_tileset;
			target.draw(m_vertices, states);
		}

		sf::VertexArray m_vertices;
		sf::Texture m_tileset;

		std::vector<Tile> m_tiles;
	};
}
