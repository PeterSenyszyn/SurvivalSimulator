#include "stdafx.h"
#include "TileMap.hpp"

unsigned int TileMap::m_xSize = 0;
unsigned int TileMap::m_ySize = 0;

TileMap::TileMap() :
	m_active(false)
{
	m_tileEntityRef.push_back(TileEntityRef::Ptr(new TileEntityRef(13, "Tree", false, true)));
}

bool TileMap::load(const std::string& filepath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
	// load the tileset texture
	if (!m_tileset.loadFromFile(filepath))
		return false;

	m_tileset.setSmooth(true);
	m_tileset.setRepeated(true);

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	m_xSize = tileSize.x * width;
	m_ySize = tileSize.y * height;

	//std::cout << m_xSize

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
	{
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

			int xDiff = (quad[1].position.x - quad[0].position.x) / 2;
			int yDiff = (quad[2].position.y - quad[0].position.y) / 2;

			Tile temp(sf::FloatRect(quad[0].position.x, quad[0].position.y, quad[1].position.x - quad[0].position.x, quad[2].position.y - quad[0].position.y),
				sf::Vector2f(quad[0].position.x + 32, quad[0].position.y + 32), tileNumber);

			m_tiles.push_back(temp);
		}
	}

	return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//apply the transform
	states.transform *= getTransform();

	//apply the tileset texture
	states.texture = &m_tileset;

	//draw the vertex array
	target.draw(m_vertices, states);
}
