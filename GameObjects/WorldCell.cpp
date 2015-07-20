
#include "WorldCell.hpp"
#include "Engine.hpp"

namespace Ataxia
{
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

	void WorldCell::update(sf::Time dt)
	{

	}

	void WorldCell::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_tileMap);
	}
}
